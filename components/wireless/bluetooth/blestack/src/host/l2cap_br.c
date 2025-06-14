/* l2cap_br.c - L2CAP BREDR oriented handling */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <string.h>
#include <bt_errno.h>
#include <atomic.h>
#include <byteorder.h>
#include <util.h>

#include <hci_host.h>
#include <bluetooth.h>
#include <conn.h>
#include <hci_driver.h>

#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BT_DEBUG_L2CAP)
#define LOG_MODULE_NAME bt_l2cap_br
#include "bt_log.h"

#include "hci_core.h"
#include "conn_internal.h"
#include "l2cap_internal.h"
#include "sdp.h"
#include "a2dp.h"
#include "hfp_hf.h"
#include "spp.h"
#include "avctp.h"
#include "avrcp.h"
#include "rfcomm.h"

#define BR_CHAN(_ch) CONTAINER_OF(_ch, struct bt_l2cap_br_chan, chan)
#define BR_CHAN_RTX(_w) CONTAINER_OF(_w, struct bt_l2cap_br_chan, chan.rtx_work)

#define L2CAP_BR_PSM_START	0x0001
#define L2CAP_BR_PSM_END	0xffff

#define L2CAP_BR_CID_DYN_START	0x0040
#define L2CAP_BR_CID_DYN_END	0xffff
#define L2CAP_BR_CID_IS_DYN(_cid) \
	(_cid >= L2CAP_BR_CID_DYN_START && _cid <= L2CAP_BR_CID_DYN_END)

#define L2CAP_BR_MIN_MTU	48
#define L2CAP_BR_DEFAULT_MTU	672

#define L2CAP_BR_PSM_SDP	0x0001

#define L2CAP_BR_INFO_TIMEOUT		K_SECONDS(4)
#define L2CAP_BR_CFG_TIMEOUT		K_SECONDS(4)
#define L2CAP_BR_DISCONN_TIMEOUT	K_SECONDS(1)
#define L2CAP_BR_CONN_TIMEOUT		K_SECONDS(40)

/*
 * L2CAP extended feature mask:
 * BR/EDR fixed channel support enabled
 */
#define L2CAP_FEAT_FIXED_CHAN_MASK	0x00000080

enum {
	/* Connection oriented channels flags */
	L2CAP_FLAG_CONN_LCONF_DONE,	/* local config accepted by remote */
	L2CAP_FLAG_CONN_RCONF_DONE,	/* remote config accepted by local */
	L2CAP_FLAG_CONN_ACCEPTOR,	/* getting incoming connection req */
	L2CAP_FLAG_CONN_PENDING,	/* remote sent pending result in rsp */

	/* Signaling channel flags */
	L2CAP_FLAG_SIG_INFO_PENDING,	/* retrieving remote l2cap info */
	L2CAP_FLAG_SIG_INFO_DONE,	/* remote l2cap info is done */

	/* fixed channels flags */
	L2CAP_FLAG_FIXED_CONNECTED,		/* fixed connected */
};

static sys_slist_t br_servers;
static uint8_t ident;
#if defined(QCC74x_BR_DISABLE_STATIC_CHANNEL)
static sys_slist_t br_channels;
#endif

/* Pool for outgoing BR/EDR signaling packets, min MTU is 48 */
#if !defined(QCC74x_DYNAMIC_ALLOC_MEM)
NET_BUF_POOL_FIXED_DEFINE(br_sig_pool, CONFIG_BT_MAX_CONN,
			  BT_L2CAP_BUF_SIZE(L2CAP_BR_MIN_MTU), NULL);
#else
struct net_buf_pool br_sig_pool;
#endif

/* BR/EDR L2CAP signalling channel specific context */
struct bt_l2cap_br {
	/* The channel this context is associated with */
	struct bt_l2cap_br_chan	chan;
	uint8_t			info_ident;
	uint8_t			info_fixed_chan;
	uint32_t			info_feat_mask;
};

static struct bt_l2cap_br bt_l2cap_br_pool[CONFIG_BT_MAX_CONN];

struct bt_l2cap_chan *bt_l2cap_br_lookup_rx_cid(struct bt_conn *conn,
						uint16_t cid)
{
	struct bt_l2cap_chan *chan;

	SYS_SLIST_FOR_EACH_CONTAINER(&conn->channels, chan, node) {
		if (BR_CHAN(chan)->rx.cid == cid) {
			return chan;
		}
	}

	return NULL;
}

struct bt_l2cap_chan *bt_l2cap_br_lookup_tx_cid(struct bt_conn *conn,
						uint16_t cid)
{
	struct bt_l2cap_chan *chan;

	SYS_SLIST_FOR_EACH_CONTAINER(&conn->channels, chan, node) {
		if (BR_CHAN(chan)->tx.cid == cid) {
			return chan;
		}
	}

	return NULL;
}

static struct bt_l2cap_br_chan*
l2cap_br_chan_alloc_cid(struct bt_conn *conn, struct bt_l2cap_chan *chan)
{
	struct bt_l2cap_br_chan *ch = BR_CHAN(chan);
	uint16_t cid;

	/*
	 * No action needed if there's already a CID allocated, e.g. in
	 * the case of a fixed channel.
	 */
	if (ch->rx.cid > 0) {
		return ch;
	}

	/*
	 * L2CAP_BR_CID_DYN_END is 0xffff so we don't check against it since
	 * cid is uint16_t, just check against uint16_t overflow
	 */
	for (cid = L2CAP_BR_CID_DYN_START; cid; cid++) {
		if (!bt_l2cap_br_lookup_rx_cid(conn, cid)) {
			ch->rx.cid = cid;
			return ch;
		}
	}

	return NULL;
}

static void l2cap_br_chan_cleanup(struct bt_l2cap_chan *chan)
{
	bt_l2cap_chan_remove(chan->conn, chan);
	bt_l2cap_chan_del(chan);
}

static void l2cap_br_chan_destroy(struct bt_l2cap_chan *chan)
{
	BT_DBG("chan %p cid 0x%04x", BR_CHAN(chan), BR_CHAN(chan)->rx.cid);

	/* Cancel ongoing work */
	k_delayed_work_cancel(&chan->rtx_work);

	atomic_clear(BR_CHAN(chan)->flags);
}

static void l2cap_br_rtx_timeout(struct k_work *work)
{
	struct bt_l2cap_br_chan *chan = BR_CHAN_RTX(work);

	BT_WARN("chan %p timeout", chan);

	if (chan->rx.cid == BT_L2CAP_CID_BR_SIG) {
		BT_DBG("Skip BR/EDR signalling channel ");
		atomic_clear_bit(chan->flags, L2CAP_FLAG_SIG_INFO_PENDING);
		return;
	}

	BT_DBG("chan %p %s scid 0x%04x", chan,
	       bt_l2cap_chan_state_str(chan->chan.state),
	       chan->rx.cid);

	switch (chan->chan.state) {
	case BT_L2CAP_CONFIG:
		bt_l2cap_br_chan_disconnect(&chan->chan);
		break;
	case BT_L2CAP_DISCONNECT:
	case BT_L2CAP_CONNECT:
		l2cap_br_chan_cleanup(&chan->chan);
		break;
	default:
		break;
	}
}

static bool l2cap_br_chan_add(struct bt_conn *conn, struct bt_l2cap_chan *chan,
			      bt_l2cap_chan_destroy_t destroy)
{
	struct bt_l2cap_br_chan *ch = l2cap_br_chan_alloc_cid(conn, chan);

	if (!ch) {
		BT_DBG("Unable to allocate L2CAP CID");
		return false;
	}

	k_delayed_work_init(&chan->rtx_work, l2cap_br_rtx_timeout);
	bt_l2cap_chan_add(conn, chan, destroy);

	return true;
}

static uint8_t l2cap_br_get_ident(void)
{
	ident++;
	/* handle integer overflow (0 is not valid) */
	if (!ident) {
		ident++;
	}

	return ident;
}

static void l2cap_br_chan_send_req(struct bt_l2cap_br_chan *chan,
				   struct net_buf *buf, s32_t timeout)
{
	/* BLUETOOTH SPECIFICATION Version 4.2 [Vol 3, Part A] page 126:
	 *
	 * The value of this timer is implementation-dependent but the minimum
	 * initial value is 1 second and the maximum initial value is 60
	 * seconds. One RTX timer shall exist for each outstanding signaling
	 * request, including each Echo Request. The timer disappears on the
	 * final expiration, when the response is received, or the physical
	 * link is lost.
	 */
	k_delayed_work_submit(&chan->chan.rtx_work, timeout);

	bt_l2cap_send(chan->chan.conn, BT_L2CAP_CID_BR_SIG, buf);
}

static void l2cap_br_get_info(struct bt_l2cap_br *l2cap, uint16_t info_type)
{
	struct bt_l2cap_info_req *info;
	struct net_buf *buf;
	struct bt_l2cap_sig_hdr *hdr;

	BT_DBG("info type %u", info_type);

	if (atomic_test_bit(l2cap->chan.flags, L2CAP_FLAG_SIG_INFO_PENDING)) {
		return;
	}

	switch (info_type) {
	case BT_L2CAP_INFO_FEAT_MASK:
	case BT_L2CAP_INFO_FIXED_CHAN:
		break;
	default:
		BT_WARN("Unsupported info type %u", info_type);
		return;
	}

	buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	atomic_set_bit(l2cap->chan.flags, L2CAP_FLAG_SIG_INFO_PENDING);
	l2cap->info_ident = l2cap_br_get_ident();

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_L2CAP_INFO_REQ;
	hdr->ident = l2cap->info_ident;
	hdr->len = sys_cpu_to_le16(sizeof(*info));

	info = net_buf_add(buf, sizeof(*info));
	info->type = sys_cpu_to_le16(info_type);

	l2cap_br_chan_send_req(&l2cap->chan, buf, L2CAP_BR_INFO_TIMEOUT);
}

static void connect_fixed_channel(struct bt_l2cap_br_chan *chan)
{
	if (atomic_test_and_set_bit(chan->flags, L2CAP_FLAG_FIXED_CONNECTED)) {
		return;
	}

	if (chan->chan.ops && chan->chan.ops->connected) {
		chan->chan.ops->connected(&chan->chan);
	}
}

static void connect_optional_fixed_channels(struct bt_l2cap_br *l2cap)
{
	/* can be change to loop if more BR/EDR fixed channels are added */
	if (l2cap->info_fixed_chan & BIT(BT_L2CAP_CID_BR_SMP)) {
		struct bt_l2cap_chan *chan;

		chan = bt_l2cap_br_lookup_rx_cid(l2cap->chan.chan.conn,
						 BT_L2CAP_CID_BR_SMP);
		if (chan) {
			connect_fixed_channel(BR_CHAN(chan));
		}
	}
}

static int l2cap_br_info_rsp(struct bt_l2cap_br *l2cap, uint8_t ident,
			     struct net_buf *buf)
{
	struct bt_l2cap_info_rsp *rsp;
	uint16_t type, result;
	int err = 0;

	if (atomic_test_bit(l2cap->chan.flags, L2CAP_FLAG_SIG_INFO_DONE)) {
		return 0;
	}

	if (atomic_test_and_clear_bit(l2cap->chan.flags,
				      L2CAP_FLAG_SIG_INFO_PENDING)) {
		/*
		 * Release RTX timer since got the response & there's pending
		 * command request.
		 */
		k_delayed_work_cancel(&l2cap->chan.chan.rtx_work);
	}

	if (buf->len < sizeof(*rsp)) {
		BT_ERR("Too small info rsp packet size");
		err = -EINVAL;
		goto done;
	}

	if (ident != l2cap->info_ident) {
		BT_WARN("Idents mismatch");
		err = -EINVAL;
		goto done;
	}

	rsp = net_buf_pull_mem(buf, sizeof(*rsp));
	result = sys_le16_to_cpu(rsp->result);
	if (result != BT_L2CAP_INFO_SUCCESS) {
		BT_WARN("Result unsuccessful");
		err = -EINVAL;
		goto done;
	}

	type = sys_le16_to_cpu(rsp->type);

	switch (type) {
	case BT_L2CAP_INFO_FEAT_MASK:
		l2cap->info_feat_mask = net_buf_pull_le32(buf);
		BT_DBG("remote info mask 0x%08x", l2cap->info_feat_mask);

		if (!(l2cap->info_feat_mask & L2CAP_FEAT_FIXED_CHAN_MASK)) {
			break;
		}

		l2cap_br_get_info(l2cap, BT_L2CAP_INFO_FIXED_CHAN);
		return 0;
	case BT_L2CAP_INFO_FIXED_CHAN:
		l2cap->info_fixed_chan = net_buf_pull_u8(buf);
		BT_DBG("remote fixed channel mask 0x%02x",
		       l2cap->info_fixed_chan);

		connect_optional_fixed_channels(l2cap);

		break;
	default:
		BT_WARN("type 0x%04x unsupported", type);
		err = -EINVAL;
		break;
	}
done:
	atomic_set_bit(l2cap->chan.flags, L2CAP_FLAG_SIG_INFO_DONE);
	l2cap->info_ident = 0U;
	return err;
}

static uint8_t get_fixed_channels_mask(void)
{
	uint8_t mask = 0U;

	#if defined(QCC74x_BR_DISABLE_STATIC_CHANNEL)
	struct bt_l2cap_br_fixed_chan *fchan;
	SYS_SLIST_FOR_EACH_CONTAINER(&br_channels, fchan, node) {
	#else
	/* this needs to be enhanced if AMP Test Manager support is added */
	Z_STRUCT_SECTION_FOREACH(bt_l2cap_br_fixed_chan, fchan) {
	#endif
		mask |= BIT(fchan->cid);
	}

	return mask;
}

static int l2cap_br_info_req(struct bt_l2cap_br *l2cap, uint8_t ident,
			     struct net_buf *buf)
{
	struct bt_conn *conn = l2cap->chan.chan.conn;
	struct bt_l2cap_info_req *req = (void *)buf->data;
	struct bt_l2cap_info_rsp *rsp;
	struct net_buf *rsp_buf;
	struct bt_l2cap_sig_hdr *hdr_info;
	uint16_t type;

	if (buf->len < sizeof(*req)) {
		BT_ERR("Too small info req packet size");
		return -EINVAL;
	}

	rsp_buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	type = sys_le16_to_cpu(req->type);
	BT_DBG("type 0x%04x", type);

	hdr_info = net_buf_add(rsp_buf, sizeof(*hdr_info));
	hdr_info->code = BT_L2CAP_INFO_RSP;
	hdr_info->ident = ident;

	rsp = net_buf_add(rsp_buf, sizeof(*rsp));

	switch (type) {
	case BT_L2CAP_INFO_FEAT_MASK:
		rsp->type = sys_cpu_to_le16(BT_L2CAP_INFO_FEAT_MASK);
		rsp->result = sys_cpu_to_le16(BT_L2CAP_INFO_SUCCESS);
		net_buf_add_le32(rsp_buf, L2CAP_FEAT_FIXED_CHAN_MASK);
		hdr_info->len = sys_cpu_to_le16(sizeof(*rsp) + sizeof(uint32_t));
		break;
	case BT_L2CAP_INFO_FIXED_CHAN:
		rsp->type = sys_cpu_to_le16(BT_L2CAP_INFO_FIXED_CHAN);
		rsp->result = sys_cpu_to_le16(BT_L2CAP_INFO_SUCCESS);
		/* fixed channel mask protocol data is 8 octets wide */
		(void)memset(net_buf_add(rsp_buf, 8), 0, 8);
		rsp->data[0] = get_fixed_channels_mask();

		hdr_info->len = sys_cpu_to_le16(sizeof(*rsp) + 8);
		break;
	default:
		rsp->type = req->type;
		rsp->result = sys_cpu_to_le16(BT_L2CAP_INFO_NOTSUPP);
		hdr_info->len = sys_cpu_to_le16(sizeof(*rsp));
		break;
	}

	bt_l2cap_send(conn, BT_L2CAP_CID_BR_SIG, rsp_buf);

	return 0;
}

void bt_l2cap_br_connected(struct bt_conn *conn)
{
	struct bt_l2cap_chan *chan;

	#if defined(QCC74x_BR_DISABLE_STATIC_CHANNEL)
	struct bt_l2cap_br_fixed_chan *fchan;
	SYS_SLIST_FOR_EACH_CONTAINER(&br_channels, fchan, node) {
	#else
	Z_STRUCT_SECTION_FOREACH(bt_l2cap_br_fixed_chan, fchan) {
	#endif
		struct bt_l2cap_br_chan *ch;

		if (!fchan->accept) {
			continue;
		}

		if (fchan->accept(conn, &chan) < 0) {
			continue;
		}

		ch = BR_CHAN(chan);

		ch->rx.cid = fchan->cid;
		ch->tx.cid = fchan->cid;

		if (!l2cap_br_chan_add(conn, chan, NULL)) {
			return;
		}

		/*
		 * other fixed channels will be connected after Information
		 * Response is received
		 */
		if (fchan->cid == BT_L2CAP_CID_BR_SIG) {
			struct bt_l2cap_br *sig_ch;

			connect_fixed_channel(ch);

			/* reset l2cap signaling channel identifier */
			ident = 0;
			sig_ch = CONTAINER_OF(ch, struct bt_l2cap_br, chan);
			l2cap_br_get_info(sig_ch, BT_L2CAP_INFO_FEAT_MASK);
		}
	}
}

static struct bt_l2cap_server *l2cap_br_server_lookup_psm(uint16_t psm)
{
	struct bt_l2cap_server *server;

	SYS_SLIST_FOR_EACH_CONTAINER(&br_servers, server, node) {
		if (server->psm == psm) {
			return server;
		}
	}

	return NULL;
}

static void l2cap_br_conf_add_mtu(struct net_buf *buf, const uint16_t mtu)
{
	net_buf_add_u8(buf, BT_L2CAP_CONF_OPT_MTU);
	net_buf_add_u8(buf, sizeof(mtu));
	net_buf_add_le16(buf, mtu);
}

static void l2cap_br_conf(struct bt_l2cap_chan *chan)
{
	struct bt_l2cap_sig_hdr *hdr;
	struct bt_l2cap_conf_req *conf;
	struct net_buf *buf;

	buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_L2CAP_CONF_REQ;
	hdr->ident = l2cap_br_get_ident();
	conf = net_buf_add(buf, sizeof(*conf));
	(void)memset(conf, 0, sizeof(*conf));

	conf->dcid = sys_cpu_to_le16(BR_CHAN(chan)->tx.cid);
	/*
	 * Add MTU option if app set non default BR/EDR L2CAP MTU,
	 * otherwise sent empty configuration data meaning default MTU
	 * to be used.
	 */
	if (BR_CHAN(chan)->rx.mtu != L2CAP_BR_DEFAULT_MTU) {
		l2cap_br_conf_add_mtu(buf, BR_CHAN(chan)->rx.mtu);
	}

	hdr->len = sys_cpu_to_le16(buf->len - sizeof(*hdr));

	/*
	 * TODO:
	 * might be needed to start tracking number of configuration iterations
	 * on both directions
	 */
	l2cap_br_chan_send_req(BR_CHAN(chan), buf, L2CAP_BR_CFG_TIMEOUT);
}

enum l2cap_br_conn_security_result {
	L2CAP_CONN_SECURITY_PASSED,
	L2CAP_CONN_SECURITY_REJECT,
	L2CAP_CONN_SECURITY_PENDING
};

/*
 * Security helper against channel connection.
 * Returns L2CAP_CONN_SECURITY_PASSED if:
 * - existing security on link is applicable for requested PSM in connection,
 * - legacy (non SSP) devices connecting with low security requirements,
 * Returns L2CAP_CONN_SECURITY_PENDING if:
 * - channel connection process is on hold since there were valid security
 *   conditions triggering authentication indirectly in subcall.
 * Returns L2CAP_CONN_SECURITY_REJECT if:
 * - bt_conn_set_security API returns < 0.
 */

static enum l2cap_br_conn_security_result
l2cap_br_conn_security(struct bt_l2cap_chan *chan, const uint16_t psm)
{
	int check;

	/* For SDP PSM there's no need to change existing security on link */
	if (chan->required_sec_level == BT_SECURITY_L0) {
		return L2CAP_CONN_SECURITY_PASSED;
	}

	/*
	 * No link key needed for legacy devices (pre 2.1) and when low security
	 * level is required.
	 */
	if (chan->required_sec_level == BT_SECURITY_L1 &&
	    !BT_FEAT_HOST_SSP(chan->conn->br.features)) {
		return L2CAP_CONN_SECURITY_PASSED;
	}

	switch (chan->required_sec_level) {
	case BT_SECURITY_L4:
	case BT_SECURITY_L3:
	case BT_SECURITY_L2:
		break;
	default:
		/*
		 * For non SDP PSM connections GAP's Security Mode 4 requires at
		 * least unauthenticated link key and enabled encryption if
		 * remote supports SSP before any L2CAP CoC traffic. So preset
		 * local to MEDIUM security to trigger it if needed.
		 */
		if (BT_FEAT_HOST_SSP(chan->conn->br.features)) {
			chan->required_sec_level = BT_SECURITY_L2;
		}
		break;
	}

	check = bt_conn_set_security(chan->conn, chan->required_sec_level);

	/*
	 * Check case when on existing connection security level already covers
	 * channel (service) security requirements against link security and
	 * bt_conn_set_security API returns 0 what implies also there was no
	 * need to trigger authentication.
	 */
	if (check == 0 &&
	    chan->conn->sec_level >= chan->required_sec_level) {
		return L2CAP_CONN_SECURITY_PASSED;
	}

	/*
	 * If 'check' still holds 0, it means local host just sent HCI
	 * authentication command to start procedure to increase link security
	 * since service/profile requires that.
	 */
	if (check == 0) {
		return L2CAP_CONN_SECURITY_PENDING;
	};

	/*
	 * For any other values in 'check' it means there was internal
	 * validation condition forbidding to start authentication at this
	 * moment.
	 */
	return L2CAP_CONN_SECURITY_REJECT;
}

static void l2cap_br_send_conn_rsp(struct bt_conn *conn, uint16_t scid,
				  uint16_t dcid, uint8_t ident, uint16_t result)
{
	struct net_buf *buf;
	struct bt_l2cap_conn_rsp *rsp;
	struct bt_l2cap_sig_hdr *hdr;

	buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_L2CAP_CONN_RSP;
	hdr->ident = ident;
	hdr->len = sys_cpu_to_le16(sizeof(*rsp));

	rsp = net_buf_add(buf, sizeof(*rsp));
	rsp->dcid = sys_cpu_to_le16(dcid);
	rsp->scid = sys_cpu_to_le16(scid);
	rsp->result = sys_cpu_to_le16(result);

	if (result == BT_L2CAP_BR_PENDING) {
		rsp->status = sys_cpu_to_le16(BT_L2CAP_CS_AUTHEN_PEND);
	} else {
		rsp->status = sys_cpu_to_le16(BT_L2CAP_CS_NO_INFO);
	}

	bt_l2cap_send(conn, BT_L2CAP_CID_BR_SIG, buf);
}

static int l2cap_br_conn_req_reply(struct bt_l2cap_chan *chan, uint16_t result)
{
	/* Send response to connection request only when in acceptor role */
	if (!atomic_test_bit(BR_CHAN(chan)->flags, L2CAP_FLAG_CONN_ACCEPTOR)) {
		return -ESRCH;
	}

	l2cap_br_send_conn_rsp(chan->conn, BR_CHAN(chan)->tx.cid,
			       BR_CHAN(chan)->rx.cid, chan->ident, result);
	chan->ident = 0U;

	return 0;
}

static void l2cap_br_conn_req(struct bt_l2cap_br *l2cap, uint8_t ident,
			      struct net_buf *buf)
{
	struct bt_conn *conn = l2cap->chan.chan.conn;
	struct bt_l2cap_chan *chan;
	struct bt_l2cap_server *server;
	struct bt_l2cap_conn_req *req = (void *)buf->data;
	uint16_t psm, scid, result;

	if (buf->len < sizeof(*req)) {
		BT_ERR("Too small L2CAP conn req packet size");
		return;
	}

	psm = sys_le16_to_cpu(req->psm);
	scid = sys_le16_to_cpu(req->scid);

	BT_DBG("psm 0x%02x scid 0x%04x", psm, scid);

	/* Check if there is a server registered */
	server = l2cap_br_server_lookup_psm(psm);
	if (!server) {
		result = BT_L2CAP_BR_ERR_PSM_NOT_SUPP;
		goto no_chan;
	}

	/*
	 * Report security violation for non SDP channel without encryption when
	 * remote supports SSP.
	 */
	if (server->sec_level != BT_SECURITY_L0 &&
	    BT_FEAT_HOST_SSP(conn->br.features) && !conn->encrypt) {
		result = BT_L2CAP_BR_ERR_SEC_BLOCK;
		goto no_chan;
	}

	if (!L2CAP_BR_CID_IS_DYN(scid)) {
		result = BT_L2CAP_BR_ERR_INVALID_SCID;
		goto no_chan;
	}

	chan = bt_l2cap_br_lookup_tx_cid(conn, scid);
	if (chan) {
		/*
		 * we have a chan here but this is due to SCID being already in
		 * use so it is not channel we are suppose to pass to
		 * l2cap_br_conn_req_reply as wrong DCID would be used
		 */
		result = BT_L2CAP_BR_ERR_SCID_IN_USE;
		goto no_chan;
	}

	/*
	 * Request server to accept the new connection and allocate the
	 * channel. If no free channels available for PSM server reply with
	 * proper result and quit since chan pointer is uninitialized then.
	 */
	if (server->accept(conn, &chan) < 0) {
		result = BT_L2CAP_BR_ERR_NO_RESOURCES;
		goto no_chan;
	}

	chan->required_sec_level = server->sec_level;

	l2cap_br_chan_add(conn, chan, l2cap_br_chan_destroy);
	BR_CHAN(chan)->tx.cid = scid;
	chan->ident = ident;
	bt_l2cap_chan_set_state(chan, BT_L2CAP_CONNECT);
	atomic_set_bit(BR_CHAN(chan)->flags, L2CAP_FLAG_CONN_ACCEPTOR);

	/* Disable fragmentation of l2cap rx pdu */
	BR_CHAN(chan)->rx.mtu = MIN(BR_CHAN(chan)->rx.mtu,
				    CONFIG_BT_L2CAP_RX_MTU);

	switch (l2cap_br_conn_security(chan, psm)) {
	case L2CAP_CONN_SECURITY_PENDING:
		result = BT_L2CAP_BR_PENDING;
		/* TODO: auth timeout */
		break;
	case L2CAP_CONN_SECURITY_PASSED:
		result = BT_L2CAP_BR_SUCCESS;
		break;
	case L2CAP_CONN_SECURITY_REJECT:
	default:
		result = BT_L2CAP_BR_ERR_SEC_BLOCK;
		break;
	}
	/* Reply on connection request as acceptor */
	l2cap_br_conn_req_reply(chan, result);

	if (result != BT_L2CAP_BR_SUCCESS) {
		/* Disconnect link when security rules were violated */
		if (result == BT_L2CAP_BR_ERR_SEC_BLOCK) {
			if(conn->type == BT_CONN_TYPE_BR){
				extern void bt_keys_link_key_clear_addr(const bt_addr_t *addr);
				bt_keys_link_key_clear_addr(&conn->br.dst);
			}
			bt_conn_disconnect(conn, BT_HCI_ERR_AUTH_FAIL);
		}

		return;
	}

	bt_l2cap_chan_set_state(chan, BT_L2CAP_CONFIG);
	l2cap_br_conf(chan);
	return;

no_chan:
	l2cap_br_send_conn_rsp(conn, scid, 0, ident, result);
	if (result == BT_L2CAP_BR_ERR_SEC_BLOCK)
	{
		#if DISABLE_BREDR_INVALID_ENC_KEY_TEST
		bt_conn_disconnect(conn, BT_HCI_ERR_AUTH_FAIL);
		#endif
	}
}

static void l2cap_br_conf_rsp(struct bt_l2cap_br *l2cap, uint8_t ident,
			      uint16_t len, struct net_buf *buf)
{
	struct bt_conn *conn = l2cap->chan.chan.conn;
	struct bt_l2cap_chan *chan;
	struct bt_l2cap_conf_rsp *rsp = (void *)buf->data;
	uint16_t scid, result;

	if (buf->len < sizeof(*rsp)) {
		BT_ERR("Too small L2CAP conf rsp packet size");
		return;
	}

	scid = sys_le16_to_cpu(rsp->scid);
	result = sys_le16_to_cpu(rsp->result);

	BT_DBG("scid 0x%04x flags 0x%02x result 0x%02x len %u", scid, sys_le16_to_cpu(rsp->flags),
		result, (len - sizeof(*rsp)));

	chan = bt_l2cap_br_lookup_rx_cid(conn, scid);
	if (!chan) {
		BT_ERR("channel mismatch!");
		return;
	}

	/* Release RTX work since got the response */
	k_delayed_work_cancel(&chan->rtx_work);

	/*
	 * TODO: handle other results than success and parse response data if
	 * available
	 */
	switch (result) {
	case BT_L2CAP_CONF_SUCCESS:
		atomic_set_bit(BR_CHAN(chan)->flags, L2CAP_FLAG_CONN_LCONF_DONE);

		if (chan->state == BT_L2CAP_CONFIG &&
		    atomic_test_bit(BR_CHAN(chan)->flags,
				    L2CAP_FLAG_CONN_RCONF_DONE)) {
			BT_DBG("scid 0x%04x rx MTU %u dcid 0x%04x tx MTU %u",
			       BR_CHAN(chan)->rx.cid, BR_CHAN(chan)->rx.mtu,
			       BR_CHAN(chan)->tx.cid, BR_CHAN(chan)->tx.mtu);

			bt_l2cap_chan_set_state(chan, BT_L2CAP_CONNECTED);
			if (chan->ops && chan->ops->connected) {
				chan->ops->connected(chan);
			}
		}
		break;
	default:
		/* currently disconnect channel on non success result */
		bt_l2cap_chan_disconnect(chan);
		break;
	}
}

int bt_l2cap_br_server_register(struct bt_l2cap_server *server)
{
	if (server->psm < L2CAP_BR_PSM_START || !server->accept) {
		return -EINVAL;
	}

	/* PSM must be odd and lsb of upper byte must be 0 */
	if ((server->psm & 0x0101) != 0x0001) {
		return -EINVAL;
	}

	if (server->sec_level > BT_SECURITY_L4) {
		return -EINVAL;
	} else if (server->sec_level == BT_SECURITY_L0 &&
		   server->psm != L2CAP_BR_PSM_SDP) {
		server->sec_level = BT_SECURITY_L1;
	}

	/* Check if given PSM is already in use */
	if (l2cap_br_server_lookup_psm(server->psm)) {
		BT_DBG("PSM already registered");
		return -EADDRINUSE;
	}

	BT_DBG("PSM 0x%04x", server->psm);

	sys_slist_append(&br_servers, &server->node);

	return 0;
}

static void l2cap_br_send_reject(struct bt_conn *conn, uint8_t ident,
				 uint16_t reason, void *data, uint8_t data_len)
{
	struct bt_l2cap_cmd_reject *rej;
	struct bt_l2cap_sig_hdr *hdr;
	struct net_buf *buf;

	buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_L2CAP_CMD_REJECT;
	hdr->ident = ident;
	hdr->len = sys_cpu_to_le16(sizeof(*rej) + data_len);

	rej = net_buf_add(buf, sizeof(*rej));
	rej->reason = sys_cpu_to_le16(reason);

	/*
	 * optional data if available must be already in little-endian format
	 * made by caller.and be compliant with Core 4.2 [Vol 3, Part A, 4.1,
	 * table 4.4]
	 */
	if (data) {
		net_buf_add_mem(buf, data, data_len);
	}

	bt_l2cap_send(conn, BT_L2CAP_CID_BR_SIG, buf);
}

static uint16_t l2cap_br_conf_opt_mtu(struct bt_l2cap_chan *chan,
				   struct net_buf *buf, size_t len)
{
	uint16_t mtu, result = BT_L2CAP_CONF_SUCCESS;

	/* Core 4.2 [Vol 3, Part A, 5.1] MTU payload length */
	if (len != 2) {
		BT_ERR("tx MTU length %zu invalid", len);
		result = BT_L2CAP_CONF_REJECT;
		goto done;
	}

	/* pulling MTU value moves buf data to next option item */
	mtu = net_buf_pull_le16(buf);
	if (mtu < L2CAP_BR_MIN_MTU) {
		result = BT_L2CAP_CONF_UNACCEPT;
		BR_CHAN(chan)->tx.mtu = L2CAP_BR_MIN_MTU;
		BT_DBG("tx MTU %u invalid", mtu);
		goto done;
	}

	BR_CHAN(chan)->tx.mtu = mtu;
	BT_DBG("tx MTU %u", mtu);
done:
	return result;
}

static void l2cap_br_conf_req(struct bt_l2cap_br *l2cap, uint8_t ident,
			      uint16_t len, struct net_buf *buf)
{
	struct bt_conn *conn = l2cap->chan.chan.conn;
	struct bt_l2cap_chan *chan;
	struct bt_l2cap_conf_req *req;
	struct bt_l2cap_sig_hdr *hdr;
	struct bt_l2cap_conf_rsp *rsp;
	struct bt_l2cap_conf_opt *opt = NULL;

	uint16_t flags, dcid, opt_len, hint, result = BT_L2CAP_CONF_SUCCESS;

	if (buf->len < sizeof(*req)) {
		BT_ERR("Too small L2CAP conf req packet size");
		return;
	}

	req = net_buf_pull_mem(buf, sizeof(*req));
	flags = sys_le16_to_cpu(req->flags);
	dcid = sys_le16_to_cpu(req->dcid);
	opt_len = len - sizeof(*req);

	BT_DBG("dcid 0x%04x flags 0x%02x len %u", dcid, flags, opt_len);

	chan = bt_l2cap_br_lookup_rx_cid(conn, dcid);
	if (!chan) {
		BT_ERR("rx channel mismatch!");
		struct bt_l2cap_cmd_reject_cid_data data = {.scid = req->dcid,
							    .dcid = 0,
							   };

		l2cap_br_send_reject(conn, ident, BT_L2CAP_REJ_INVALID_CID,
				     &data, sizeof(data));
		return;
	}

	if (!opt_len) {
		BT_DBG("tx default MTU %u", L2CAP_BR_DEFAULT_MTU);
		BR_CHAN(chan)->tx.mtu = L2CAP_BR_DEFAULT_MTU;
		goto send_rsp;
	}

	while (buf->len >= sizeof(*opt)) {
		opt = net_buf_pull_mem(buf, sizeof(*opt));

		/* make sure opt object can get safe dereference in iteration */
		if (buf->len < opt->len) {
			BT_ERR("Received too short option data");
			result = BT_L2CAP_CONF_REJECT;
			break;
		}

		hint = opt->type & BT_L2CAP_CONF_HINT;

		switch (opt->type & BT_L2CAP_CONF_MASK) {
		case BT_L2CAP_CONF_OPT_MTU:
			/* getting MTU modifies buf internals */
			result = l2cap_br_conf_opt_mtu(chan, buf, opt->len);
			/*
			 * MTU is done. For now bailout the loop but later on
			 * there can be a need to continue checking next options
			 * that are after MTU value and then goto is not proper
			 * way out here.
			 */
			goto send_rsp;
		default:
			if (!hint) {
				BT_DBG("option %u not handled", opt->type);
                result = BT_L2CAP_CONF_UNKNOWN_OPTIONS;
				goto send_rsp;
			}

			/* Update buffer to point at next option */
			net_buf_pull(buf, opt->len);
			break;
		}
	}

send_rsp:
	buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_L2CAP_CONF_RSP;
	hdr->ident = ident;
	rsp = net_buf_add(buf, sizeof(*rsp));
	(void)memset(rsp, 0, sizeof(*rsp));

	rsp->result = sys_cpu_to_le16(result);
	rsp->scid = sys_cpu_to_le16(BR_CHAN(chan)->tx.cid);
    if(flags)
        rsp->flags = 1;

	/*
	 * TODO: If options other than MTU bacame meaningful then processing
	 * the options chain need to be modified and taken into account when
	 * sending back to peer.
	 */
	if (result == BT_L2CAP_CONF_UNACCEPT) {
		l2cap_br_conf_add_mtu(buf, BR_CHAN(chan)->tx.mtu);
	}

    if(result == BT_L2CAP_CONF_UNKNOWN_OPTIONS){
        uint8_t opt_len = 2 + opt->len;//size:opt->type, opt->len, opt->data
        net_buf_add(buf, opt_len);
        memcpy(rsp->data, opt, opt_len);
    }
	hdr->len = sys_cpu_to_le16(buf->len - sizeof(*hdr));

	bt_l2cap_send(conn, BT_L2CAP_CID_BR_SIG, buf);

	if (result != BT_L2CAP_CONF_SUCCESS) {
		return;
	}

	atomic_set_bit(BR_CHAN(chan)->flags, L2CAP_FLAG_CONN_RCONF_DONE);

	if (atomic_test_bit(BR_CHAN(chan)->flags, L2CAP_FLAG_CONN_LCONF_DONE) &&
	    chan->state == BT_L2CAP_CONFIG) {
		BT_DBG("scid 0x%04x rx MTU %u dcid 0x%04x tx MTU %u",
		       BR_CHAN(chan)->rx.cid, BR_CHAN(chan)->rx.mtu,
		       BR_CHAN(chan)->tx.cid, BR_CHAN(chan)->tx.mtu);

		bt_l2cap_chan_set_state(chan, BT_L2CAP_CONNECTED);
		if (chan->ops && chan->ops->connected) {
			chan->ops->connected(chan);
		}
	}
}

static struct bt_l2cap_br_chan *l2cap_br_remove_tx_cid(struct bt_conn *conn,
						       uint16_t cid)
{
	struct bt_l2cap_chan *chan;
	sys_snode_t *prev = NULL;

	/* Protect fixed channels against accidental removal */
	if (!L2CAP_BR_CID_IS_DYN(cid)) {
		return NULL;
	}

	SYS_SLIST_FOR_EACH_CONTAINER(&conn->channels, chan, node) {
		if (BR_CHAN(chan)->tx.cid == cid) {
			sys_slist_remove(&conn->channels, prev, &chan->node);
			return BR_CHAN(chan);
		}

		prev = &chan->node;
	}

	return NULL;
}

static void l2cap_br_disconn_req(struct bt_l2cap_br *l2cap, uint8_t ident,
				 struct net_buf *buf)
{
	struct bt_conn *conn = l2cap->chan.chan.conn;
	struct bt_l2cap_br_chan *chan;
	struct bt_l2cap_disconn_req *req = (void *)buf->data;
	struct bt_l2cap_disconn_rsp *rsp;
	struct bt_l2cap_sig_hdr *hdr;
	uint16_t scid;
	if (buf->len < sizeof(*req)) {
		BT_ERR("Too small disconn req packet size");
		return;
	}

	scid = sys_le16_to_cpu(req->scid);

	BT_DBG("scid 0x%04x dcid 0x%04x", scid,sys_le16_to_cpu(req->dcid));

	chan = l2cap_br_remove_tx_cid(conn, scid);
	if (!chan) {
		struct bt_l2cap_cmd_reject_cid_data data;

		data.scid = req->scid;
		data.dcid = req->dcid;
		l2cap_br_send_reject(conn, ident, BT_L2CAP_REJ_INVALID_CID,
				     &data, sizeof(data));
		return;
	}

	buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_L2CAP_DISCONN_RSP;
	hdr->ident = ident;
	hdr->len = sys_cpu_to_le16(sizeof(*rsp));

	rsp = net_buf_add(buf, sizeof(*rsp));
	rsp->dcid = sys_cpu_to_le16(chan->rx.cid);
	rsp->scid = sys_cpu_to_le16(chan->tx.cid);

	bt_l2cap_chan_del(&chan->chan);

	bt_l2cap_send(conn, BT_L2CAP_CID_BR_SIG, buf);
}

static void l2cap_br_connected(struct bt_l2cap_chan *chan)
{
	BT_DBG("ch %p cid 0x%04x", BR_CHAN(chan), BR_CHAN(chan)->rx.cid);
}

static void l2cap_br_disconnected(struct bt_l2cap_chan *chan)
{
	BT_DBG("ch %p cid 0x%04x", BR_CHAN(chan), BR_CHAN(chan)->rx.cid);

	if (atomic_test_and_clear_bit(BR_CHAN(chan)->flags,
				      L2CAP_FLAG_SIG_INFO_PENDING)) {
		/* Cancel RTX work on signal channel */
		k_delayed_work_cancel(&chan->rtx_work);
	}
}

int bt_l2cap_br_chan_disconnect(struct bt_l2cap_chan *chan)
{
	struct bt_conn *conn = chan->conn;
	struct net_buf *buf;
	struct bt_l2cap_disconn_req *req;
	struct bt_l2cap_sig_hdr *hdr;
	struct bt_l2cap_br_chan *ch;

	if (!conn) {
		return -ENOTCONN;
	}

	if (chan->state == BT_L2CAP_DISCONNECT) {
		return -EALREADY;
	}

	ch = BR_CHAN(chan);

	BT_DBG("chan %p scid 0x%04x dcid 0x%04x", chan, ch->rx.cid,
	       ch->tx.cid);

	buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_L2CAP_DISCONN_REQ;
	hdr->ident = l2cap_br_get_ident();
	hdr->len = sys_cpu_to_le16(sizeof(*req));

	req = net_buf_add(buf, sizeof(*req));
	req->dcid = sys_cpu_to_le16(ch->tx.cid);
	req->scid = sys_cpu_to_le16(ch->rx.cid);

	l2cap_br_chan_send_req(ch, buf, L2CAP_BR_DISCONN_TIMEOUT);
	bt_l2cap_chan_set_state(chan, BT_L2CAP_DISCONNECT);

	return 0;
}

static int l2cap_br_echo_req(struct bt_l2cap_br *l2cap, uint8_t ident,
			     struct net_buf *buf)
{
	struct bt_conn *conn = l2cap->chan.chan.conn;
	struct net_buf *rsp_buf;
	struct bt_l2cap_sig_hdr *hdr_info;

	rsp_buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr_info = net_buf_add(rsp_buf, sizeof(*hdr_info));
	hdr_info->code = BT_L2CAP_ECHO_RSP;
	hdr_info->ident = ident;

	bt_l2cap_send(conn, BT_L2CAP_CID_BR_SIG, rsp_buf);
	return 0;
}

static int l2cap_br_echo_resp(struct bt_l2cap_br *l2cap, uint8_t ident,
              struct net_buf *buf)
{
    return 0;
}

static void l2cap_br_disconn_rsp(struct bt_l2cap_br *l2cap, uint8_t ident,
				 struct net_buf *buf)
{
	struct bt_conn *conn = l2cap->chan.chan.conn;
	struct bt_l2cap_br_chan *chan;
	struct bt_l2cap_disconn_rsp *rsp = (void *)buf->data;
	uint16_t dcid;

	if (buf->len < sizeof(*rsp)) {
		BT_ERR("Too small disconn rsp packet size");
		return;
	}

	dcid = sys_le16_to_cpu(rsp->dcid);

	BT_DBG("dcid 0x%04x scid 0x%04x", dcid, sys_le16_to_cpu(rsp->scid));

	chan = l2cap_br_remove_tx_cid(conn, dcid);
	if (!chan) {
		BT_WARN("No dcid 0x%04x channel found", dcid);
		return;
	}

	bt_l2cap_chan_del(&chan->chan);
}

int bt_l2cap_br_chan_connect(struct bt_conn *conn, struct bt_l2cap_chan *chan,
			     uint16_t psm)
{
	struct net_buf *buf;
	struct bt_l2cap_sig_hdr *hdr;
	struct bt_l2cap_conn_req *req;

	if (!psm) {
		return -EINVAL;
	}

	if (chan->psm) {
		return -EEXIST;
	}

	/* PSM must be odd and lsb of upper byte must be 0 */
	if ((psm & 0x0101) != 0x0001) {
		return -EINVAL;
	}

	if (chan->required_sec_level > BT_SECURITY_L4) {
		return -EINVAL;
	} else if (chan->required_sec_level == BT_SECURITY_L0 &&
		   psm != L2CAP_BR_PSM_SDP) {
		chan->required_sec_level = BT_SECURITY_L1;
	}

	switch (chan->state) {
	case BT_L2CAP_CONNECTED:
		/* Already connected */
		return -EISCONN;
	case BT_L2CAP_DISCONNECTED:
		/* Can connect */
		break;
	case BT_L2CAP_CONFIG:
	case BT_L2CAP_DISCONNECT:
	default:
		/* Bad context */
		return -EBUSY;
	}

	if (!l2cap_br_chan_add(conn, chan, l2cap_br_chan_destroy)) {
		return -ENOMEM;
	}

	chan->psm = psm;
	bt_l2cap_chan_set_state(chan, BT_L2CAP_CONNECT);
	atomic_set_bit(BR_CHAN(chan)->flags, L2CAP_FLAG_CONN_PENDING);

	switch (l2cap_br_conn_security(chan, psm)) {
	case L2CAP_CONN_SECURITY_PENDING:
		/*
		 * Authentication was triggered, wait with sending request on
		 * connection security changed callback context.
		 */
		 return 0;
	case L2CAP_CONN_SECURITY_PASSED:
		break;
	case L2CAP_CONN_SECURITY_REJECT:
	default:
		l2cap_br_chan_cleanup(chan);
		return -EIO;
	}

	buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_L2CAP_CONN_REQ;
	hdr->ident = l2cap_br_get_ident();
	hdr->len = sys_cpu_to_le16(sizeof(*req));

	req = net_buf_add(buf, sizeof(*req));
	req->psm = sys_cpu_to_le16(psm);
	req->scid = sys_cpu_to_le16(BR_CHAN(chan)->rx.cid);

	l2cap_br_chan_send_req(BR_CHAN(chan), buf, L2CAP_BR_CONN_TIMEOUT);

	return 0;
}

static void l2cap_br_conn_rsp(struct bt_l2cap_br *l2cap, uint8_t ident,
			      struct net_buf *buf)
{
	struct bt_conn *conn = l2cap->chan.chan.conn;
	struct bt_l2cap_chan *chan;
	struct bt_l2cap_conn_rsp *rsp = (void *)buf->data;
	uint16_t dcid, scid, result;

	if (buf->len < sizeof(*rsp)) {
		BT_ERR("Too small L2CAP conn rsp packet size");
		return;
	}

	dcid = sys_le16_to_cpu(rsp->dcid);
	scid = sys_le16_to_cpu(rsp->scid);
	result = sys_le16_to_cpu(rsp->result);

	BT_DBG("dcid 0x%04x scid 0x%04x result %u status %u", dcid, scid,
	       result, sys_le16_to_cpu(rsp->status));

	chan = bt_l2cap_br_lookup_rx_cid(conn, scid);
	if (!chan) {
		BT_ERR("No scid 0x%04x channel found", scid);
		return;
	}

	/* Release RTX work since got the response */
	k_delayed_work_cancel(&chan->rtx_work);

	if (chan->state != BT_L2CAP_CONNECT) {
		BT_DBG("Invalid channel %p state %s", chan,
		       bt_l2cap_chan_state_str(chan->state));
		return;
	}

	switch (result) {
	case BT_L2CAP_BR_SUCCESS:
		chan->ident = 0U;
		BR_CHAN(chan)->tx.cid = dcid;
		l2cap_br_conf(chan);
		bt_l2cap_chan_set_state(chan, BT_L2CAP_CONFIG);
		atomic_clear_bit(BR_CHAN(chan)->flags, L2CAP_FLAG_CONN_PENDING);
		break;
	case BT_L2CAP_BR_PENDING:
		k_delayed_work_submit(&chan->rtx_work, L2CAP_BR_CONN_TIMEOUT);
		break;
	default:
		l2cap_br_chan_cleanup(chan);
		break;
	}
}

int bt_l2cap_br_chan_send(struct bt_l2cap_chan *chan, struct net_buf *buf)
{
	struct bt_l2cap_br_chan *ch = BR_CHAN(chan);

	if (buf->len > ch->tx.mtu) {
		return -EMSGSIZE;
	}

	bt_l2cap_send(ch->chan.conn, ch->tx.cid, buf);

	return buf->len;
}

static int l2cap_br_recv(struct bt_l2cap_chan *chan, struct net_buf *buf)
{
	struct bt_l2cap_br *l2cap = CONTAINER_OF(chan, struct bt_l2cap_br, chan);
	struct bt_l2cap_sig_hdr *hdr;
	uint16_t len;

	if (buf->len < sizeof(*hdr)) {
		BT_ERR("Too small L2CAP signaling PDU");
		return 0;
	}

    uint16_t remain_len = buf->len;

    //take multi-command in a l2cap packet into consideration.
    while(remain_len >= sizeof(*hdr))
    {
    	hdr = net_buf_pull_mem(buf, sizeof(*hdr));
    	len = sys_le16_to_cpu(hdr->len);
    
    	BT_DBG("Signaling code 0x%02x ident %u len %u", hdr->code,
    	       hdr->ident, len);
    
    	if (buf->len < len) {
    		BT_ERR("L2CAP length mismatch (%u != %u)", buf->len, len);
    		return 0;
    	}
    
    	if (!hdr->ident) {
    		BT_ERR("Invalid ident value in L2CAP PDU");
    		return 0;
    	}
        
    	switch (hdr->code) {
    	case BT_L2CAP_INFO_RSP:
    		l2cap_br_info_rsp(l2cap, hdr->ident, buf);
    		break;
    	case BT_L2CAP_INFO_REQ:
    		l2cap_br_info_req(l2cap, hdr->ident, buf);
    		break;
    	case BT_L2CAP_DISCONN_REQ:
    		l2cap_br_disconn_req(l2cap, hdr->ident, buf);
    		break;
    	case BT_L2CAP_CONN_REQ:
    		l2cap_br_conn_req(l2cap, hdr->ident, buf);
    		break;
    	case BT_L2CAP_CONF_RSP:
    		l2cap_br_conf_rsp(l2cap, hdr->ident, len, buf);
    		break;
    	case BT_L2CAP_CONF_REQ:
    		l2cap_br_conf_req(l2cap, hdr->ident, len, buf);
    		break;
    	case BT_L2CAP_DISCONN_RSP:
    		l2cap_br_disconn_rsp(l2cap, hdr->ident, buf);
    		break;
    	case BT_L2CAP_CONN_RSP:
    		l2cap_br_conn_rsp(l2cap, hdr->ident, buf);
    		break;
    	case BT_L2CAP_ECHO_REQ:
    		l2cap_br_echo_req(l2cap, hdr->ident, buf);
    		break;
        case BT_L2CAP_ECHO_RSP:
            l2cap_br_echo_resp(l2cap, hdr->ident, buf);
            break;
    	default:
    		BT_WARN("Unknown/Unsupported L2CAP PDU code 0x%02x", hdr->code);
    		l2cap_br_send_reject(chan->conn, hdr->ident,
    				     BT_L2CAP_REJ_NOT_UNDERSTOOD, NULL, 0);
    		break;
    	}

        remain_len -= sizeof(*hdr) + len;
        if(remain_len >= sizeof(*hdr))
            net_buf_pull_mem(buf, len);
        else if(remain_len)
            l2cap_br_send_reject(chan->conn, hdr->ident, BT_L2CAP_REJ_NOT_UNDERSTOOD, NULL, 0);
    }
	return 0;
}

static void l2cap_br_conn_pend(struct bt_l2cap_chan *chan, uint8_t status)
{
	struct net_buf *buf;
	struct bt_l2cap_sig_hdr *hdr;
	struct bt_l2cap_conn_req *req;

	if (chan->state != BT_L2CAP_CONNECT) {
		return;
	}

	BT_DBG("chan %p status 0x%02x encr 0x%02x", chan, status,
	       chan->conn->encrypt);

	if (status) {
		/*
		 * Security procedure status is non-zero so respond with
		 * security violation only as channel acceptor.
		 */
		l2cap_br_conn_req_reply(chan, BT_L2CAP_BR_ERR_SEC_BLOCK);

		/* Release channel allocated to outgoing connection request */
		if (atomic_test_bit(BR_CHAN(chan)->flags,
				    L2CAP_FLAG_CONN_PENDING)) {
			l2cap_br_chan_cleanup(chan);
		}

		return;
	}

	if (!chan->conn->encrypt) {
		return;
	}

	/*
	 * For incoming connection state send confirming outstanding
	 * response and initiate configuration request.
	 */
	if (l2cap_br_conn_req_reply(chan, BT_L2CAP_BR_SUCCESS) == 0) {
		bt_l2cap_chan_set_state(chan, BT_L2CAP_CONFIG);
		/*
		 * Initialize config request since remote needs to know
		 * local MTU segmentation.
		 */
		l2cap_br_conf(chan);
	} else if (atomic_test_and_clear_bit(BR_CHAN(chan)->flags,
					     L2CAP_FLAG_CONN_PENDING)) {
		buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

		hdr = net_buf_add(buf, sizeof(*hdr));
		hdr->code = BT_L2CAP_CONN_REQ;
		hdr->ident = l2cap_br_get_ident();
		hdr->len = sys_cpu_to_le16(sizeof(*req));

		req = net_buf_add(buf, sizeof(*req));
		req->psm = sys_cpu_to_le16(chan->psm);
		req->scid = sys_cpu_to_le16(BR_CHAN(chan)->rx.cid);

		l2cap_br_chan_send_req(BR_CHAN(chan), buf,
				       L2CAP_BR_CONN_TIMEOUT);
	}
}

void l2cap_br_encrypt_change(struct bt_conn *conn, uint8_t hci_status)
{
	struct bt_l2cap_chan *chan;

	SYS_SLIST_FOR_EACH_CONTAINER(&conn->channels, chan, node) {
		l2cap_br_conn_pend(chan, hci_status);

		if (chan->ops && chan->ops->encrypt_change) {
			chan->ops->encrypt_change(chan, hci_status);
		}
	}
}

static void check_fixed_channel(struct bt_l2cap_chan *chan)
{
	struct bt_l2cap_br_chan *br_chan = BR_CHAN(chan);

	if (br_chan->rx.cid < L2CAP_BR_CID_DYN_START) {
		connect_fixed_channel(br_chan);
	}
}

void bt_l2cap_br_recv(struct bt_conn *conn, struct net_buf *buf)
{
	struct bt_l2cap_hdr *hdr;
	struct bt_l2cap_chan *chan;
	uint16_t cid;

	if (buf->len < sizeof(*hdr)) {
		BT_ERR("Too small L2CAP PDU received");
		net_buf_unref(buf);
		return;
	}

	hdr = net_buf_pull_mem(buf, sizeof(*hdr));
	cid = sys_le16_to_cpu(hdr->cid);

	chan = bt_l2cap_br_lookup_rx_cid(conn, cid);
	if (!chan) {
		BT_WARN("Ignoring data for unknown CID 0x%04x", cid);
		net_buf_unref(buf);
		return;
	}

	/*
	 * if data was received for fixed channel before Information
	 * Response we connect channel here.
	 */
	check_fixed_channel(chan);

	chan->ops->recv(chan, buf);
	net_buf_unref(buf);
}

static int l2cap_br_accept(struct bt_conn *conn, struct bt_l2cap_chan **chan)
{
	int i;
	static struct bt_l2cap_chan_ops ops = {
		.connected = l2cap_br_connected,
		.disconnected = l2cap_br_disconnected,
		.recv = l2cap_br_recv,
	};

	BT_DBG("conn %p handle %u", conn, conn->handle);

	for (i = 0; i < ARRAY_SIZE(bt_l2cap_br_pool); i++) {
		struct bt_l2cap_br *l2cap = &bt_l2cap_br_pool[i];

		if (l2cap->chan.chan.conn) {
			continue;
		}

		l2cap->chan.chan.ops = &ops;
		*chan = &l2cap->chan.chan;
		atomic_set(l2cap->chan.flags, 0);
		return 0;
	}

	BT_ERR("No available L2CAP context for conn %p", conn);

	return -ENOMEM;
}

BT_L2CAP_BR_CHANNEL_DEFINE(br_fixed_chan, BT_L2CAP_CID_BR_SIG, l2cap_br_accept);

#if defined(QCC74x_BR_DISABLE_STATIC_CHANNEL)
void bt_l2cap_br_fixed_chan_register(struct bt_l2cap_fixed_chan *chan)
{
	BT_DBG("CID 0x%04x", chan->cid);
	sys_slist_append(&br_channels, &chan->node);
}
#endif

void bt_l2cap_br_init(void)
{
	#if defined(QCC74x_BR_DISABLE_STATIC_CHANNEL)
	static struct bt_l2cap_br_fixed_chan chan = {
		.cid	= BT_L2CAP_CID_BR_SIG,
		.accept	= l2cap_br_accept,
	};

	bt_l2cap_br_fixed_chan_register(&chan);
	#endif

#if defined(QCC74x_DYNAMIC_ALLOC_MEM)
	net_buf_init(&br_sig_pool, CONFIG_BT_MAX_CONN, BT_L2CAP_BUF_SIZE(L2CAP_BR_MIN_MTU), NULL);
#endif
	sys_slist_init(&br_servers);

	bt_sdp_init();
	bt_rfcomm_init();

	if (IS_ENABLED(CONFIG_BT_SPP)) {
		bt_spp_init();
	}

	if (IS_ENABLED(CONFIG_BT_HFP)) {
		bt_hfp_hf_init();
	}

	if (IS_ENABLED(CONFIG_BT_A2DP)) {

		#if defined(CONFIG_BT_A2DP_SOURCE)
		bt_dev.br.a2dp_role = BT_A2DP_SOURCE_ROLE;
		#endif
		#if defined(CONFIG_BT_A2DP_SINK)
		bt_dev.br.a2dp_role = BT_A2DP_SINK_ROLE;
		#endif
		
		bt_avdtp_init();
		bt_a2dp_init();
	}

	if (IS_ENABLED(CONFIG_BT_AVRCP)) {
		bt_avctp_init();
		bt_avrcp_init();
	}

}

int bt_l2cap_br_echo_req(struct bt_conn *conn)
{
    struct net_buf *rsp_buf;
	struct bt_l2cap_sig_hdr *hdr_info;

	rsp_buf = bt_l2cap_create_pdu(&br_sig_pool, 0);

	hdr_info = net_buf_add(rsp_buf, sizeof(*hdr_info));
	hdr_info->code = BT_L2CAP_ECHO_REQ;
	hdr_info->ident = ident;

	bt_l2cap_send(conn, BT_L2CAP_CID_BR_SIG, rsp_buf);
	return 0; 
}

