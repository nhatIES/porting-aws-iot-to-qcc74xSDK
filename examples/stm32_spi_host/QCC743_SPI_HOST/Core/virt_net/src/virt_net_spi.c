#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include <lwip/api.h>
#include <lwip/opt.h>
#include <lwip/def.h>
#include <lwip/mem.h>
#include <lwip/pbuf.h>
#include <lwip/tcpip.h>
#include <lwip/dns.h>
#include <lwip/etharp.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include "bitset.h"

#include "virt_net_spi.h"
#include "pkg_protocol.h"
#include "spi.h"
#include "at_host.h"

struct virt_net_spi;
struct spi_custom_pbuf {
  struct pbuf_custom p;
  struct spi_buffer *spbuf;
  struct virt_net_spi *sobj;
};

void debug_print_ethernet_packet(struct pbuf *p_buf) {
    if (p_buf == NULL || p_buf->payload == NULL) {
        printf("pbuf is NULL or has no payload\n");
        return;
    }

    struct eth_hdr *ethhdr = (struct eth_hdr *)p_buf->payload;
    uint16_t payload_len = p_buf->tot_len - sizeof(struct eth_hdr);
    uint8_t *payload = (uint8_t *)p_buf->payload + sizeof(struct eth_hdr);

    printf("\r\n==== Ethernet Frame ====\r\n");

    printf("Destination MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
           ethhdr->dest.addr[0], ethhdr->dest.addr[1], ethhdr->dest.addr[2],
           ethhdr->dest.addr[3], ethhdr->dest.addr[4], ethhdr->dest.addr[5]);

    printf("Source MAC: %02X:%02X:%02X:%02X:%02:%02X\r\n",
           ethhdr->src.addr[0], ethhdr->src.addr[1], ethhdr->src.addr[2],
           ethhdr->src.addr[3], ethhdr->src.addr[4], ethhdr->src.addr[5]);

    printf("EtherType: 0x%04X\n", ntohs(ethhdr->type));

    switch (ntohs(ethhdr->type)) {
        case ETHTYPE_IP:
            printf("Payload Type: IPv4\r\n");
            break;
        case ETHTYPE_ARP:
            printf("Payload Type: ARP\r\n");
            break;
        case ETHTYPE_IPV6:
            printf("Payload Type: IPv6\r\n");
            break;
        default:
            printf("Payload Type: Unknown (0x%04X)\r\n", ntohs(ethhdr->type));
            break;
    }

    payload_len = p_buf->len;
    payload = (uint8_t *)p_buf->payload;

    printf("tot_len: %d bytes\r\n", payload_len);

//    uint16_t len = (payload_len < 128) ? payload_len : 128;
    uint16_t len = payload_len;
    for (uint16_t i = 0; i < len; i++) {
        printf("%02X ", payload[i]);
        if ((i + 1) % 16 == 0) printf("\r\n");
    }

//    if (payload_len > 128) {
//    	printf("...\n");
//        uint8_t *payload_end = payload + payload_len - 128;
//        for (uint16_t i = 0; i < 128; i++) {
//            printf("%02X ", payload_end[i]);
//            if ((i + 1) % 16 == 0) printf("\n");
//        }
//    }
    printf("\r\n========================\r\n");
}

static err_t net_if_output(struct netif *net_if, struct pbuf *p_buf)
{
    err_t status = ERR_BUF;
    struct pbuf *q;
    int ret;
    struct virt_net *obj = (struct virt_net *)net_if->state;
	struct spi_msg_control ctrl;
	uint8_t traffic = SPI_MSG_CTRL_TRAFFIC_NETWORK;
	struct spi_msg m;

	if (obj->netmode == VIRTNET_NET_MODE_NCP) {
		return ERR_OK;
	}

	SPI_MSG_CONTROL_INIT(ctrl, SPI_MSG_CTRL_TRAFFIC_TYPE,
		SPI_MSG_CTRL_TRAFFIC_TYPE_LEN, &traffic);

	for (q = p_buf; q != NULL; q = q->next) {
		SPI_MSG_INIT(m, SPI_MSG_OP_DATA, &ctrl, 0);
		m.data = (void *)q->payload;
		m.data_len = q->len;
		ret = spi_write(&m, pdMS_TO_TICKS(10000));
#if 0
		debug_print_ethernet_packet(q);
#endif
	}

	status = ERR_OK;

    return (status);
}

static void netif_status_callback(struct netif *netif) {

	struct virt_net *obj = (struct virt_net *)netif->state;

	if (ip4_addr_isany(netif_ip4_addr(netif))) {
		//printf("disconnect \n");
	} else {
		printf("IP Address: %s\r\n", ipaddr_ntoa(netif_ip4_addr(netif)));
		printf("Netmask:    %s\r\n", ipaddr_ntoa(netif_ip4_netmask(netif)));
		printf("Gateway:    %s\r\n", ipaddr_ntoa(netif_ip4_gw(netif)));
		virt_net_dhcp_done(obj);
	}
}

static err_t virt_netif_init(struct netif *netif)
{
  struct virt_net * obj = (struct virt_net *)netif->state;

  obj->netif.hostname = "spi_eth0";
  
  obj->netif.name[0] = "w";
  obj->netif.name[1] = "l";

  netif->hwaddr_len = ETHARP_HWADDR_LEN;
  memcpy(netif->hwaddr, obj->mac, ETHARP_HWADDR_LEN);

  /* set netif maximum transfer unit */
  netif->mtu = obj->mtu;

#ifdef CFG_IPV6
  netif->flags = NETIF_FLAG_LINK_UP | NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET | NETIF_FLAG_IGMP | NETIF_FLAG_MLD6;
  netif->output_ip6 = ethip6_output;
#else
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
#endif

  netif->output = etharp_output;
  netif->linkoutput = net_if_output;

  /* Set callback to be called when interface is brought up/down or address is changed while up */
  netif_set_status_callback(&obj->netif, netif_status_callback);

  return ERR_OK;
}

static int virt_net_spi_init(virt_net_t obj)
{
  assert(obj != NULL);

  struct virt_net_spi *sobj = (struct virt_net_spi *)obj;

#if 0
  ip4_addr_t ipaddr;
  ip4_addr_t netmask;
  ip4_addr_t gw;

  IP4_ADDR(&ipaddr, 192, 168, 11, 111);
  IP4_ADDR(&netmask, 255, 255, 255, 0);
  IP4_ADDR(&gw, 192, 168, 11, 1);
#endif

  if (netifapi_netif_add(&obj->netif, NULL, NULL, NULL, (void *)obj, virt_netif_init, tcpip_input) != ERR_OK) {
    printf("add spi netif failed\r\n");
    return -1;
  }

  return 0;
}

static int _virl_net_spi_read(struct spi_buffer **spbuf)
{
	int ret;
	uint8_t traffic_type = SPI_MSG_CTRL_TRAFFIC_NETWORK;
	struct spi_msg_control ctrl;
	struct spi_msg m = {0};

	SPI_MSG_CONTROL_INIT(ctrl, SPI_MSG_CTRL_TRAFFIC_TYPE,
		SPI_MSG_CTRL_TRAFFIC_TYPE_LEN, &traffic_type);
	SPI_MSG_INIT(m, SPI_MSG_OP_BUFFER_PTR, &ctrl, 0);
	m.buffer_ptr = spbuf;
	ret = spi_read(&m, pdMS_TO_TICKS(10000));
#if 0
	if (ret > 0) {
		printf("virl_net_read %d\r\n", ret);
	}
#endif
	return ret;
}

int parse_mac(const char *mac_str, uint8_t *mac)
{
    int i;
    for (i = 0; i < 6; i++) {
        unsigned char high = 0, low = 0;

        if (mac_str[0] >= '0' && mac_str[0] <= '9') {
            high = mac_str[0] - '0';
        } else if (mac_str[0] >= 'a' && mac_str[0] <= 'f') {
            high = mac_str[0] - 'a' + 10;
        } else if (mac_str[0] >= 'A' && mac_str[0] <= 'F') {
            high = mac_str[0] - 'A' + 10;
        }

        if (mac_str[1] >= '0' && mac_str[1] <= '9') {
            low = mac_str[1] - '0';
        } else if (mac_str[1] >= 'a' && mac_str[1] <= 'f') {
            low = mac_str[1] - 'a' + 10;
        } else if (mac_str[1] >= 'A' && mac_str[1] <= 'F') {
            low = mac_str[1] - 'A' + 10;
        }
        mac[i] = (high << 4) | low;
        mac_str += 3;
    }
    return 0;
}


static int virt_net_spi_control(virt_net_t obj, int cmd, ...)
{
	int ret = 0;
	char resp[48];
	struct virt_net_spi *sobj = (struct virt_net_spi *)obj;
	va_list args;

	if (osThreadGetId() != sobj->athandle->at_rx_task) {
		osThreadSuspend(sobj->athandle->at_rx_task);
	}

	switch (cmd) {
	case VIRT_NET_CTRL_GET_NETMODE:
		int netmode;
		int *tmp_netmode;
		at_host_send(sobj->athandle, 0, "AT+CWNETMODE?\r\n", strlen("AT+CWNETMODE?\r\n"), (uint32_t)-1);
		// +CWNETMODE:1
		memset(resp, 0, sizeof(resp));
		at_host_read(sobj->athandle, resp, sizeof(resp));
		if (strstr(resp, "+CWNETMODE:") == NULL) {
		  printf("CWNETMODE:%s\r\n", resp);
		  ret = -1;
		  break;
		}
		netmode = atoi(&resp[11]);

		// OK
		at_host_read(sobj->athandle, resp, sizeof(resp));
		if (strstr(resp, "OK\r\n") == NULL) {
		  printf("OK error\r\n");
		  ret = -1;
		  break;
		}

		va_start(args, cmd);
		tmp_netmode = va_arg(args, int *);
		*tmp_netmode = netmode;
		va_end(args);

		break;
	case VIRT_NET_CTRL_GET_MAC:
		char mac[6];
		uint8_t *tmp;
		at_host_send(sobj->athandle, 0, "AT+CIPSTAMAC?\r\n", strlen("AT+CIPSTAMAC?\r\n"), (uint32_t)-1);
		// +CIPSTAMAC:"c4:cc:37:a0:6d:6e"
		memset(resp, 0, sizeof(resp));
		at_host_read(sobj->athandle, resp, sizeof(resp));
		if (strstr(resp, "+CIPSTAMAC:") == NULL) {
		  printf("CIPSTAMAC:%s\r\n", resp);
		  ret = -1;
		  break;
		}
		parse_mac((const char *)&resp[12], mac);
		// OK
		at_host_read(sobj->athandle, resp, sizeof(resp));
		if (strstr(resp, "OK\r\n") == NULL) {
		  printf("OK error\r\n");
		  ret = -1;
		  break;
		}

		va_start(args, cmd);
		tmp = va_arg(args, uint8_t *);
		memcpy(tmp, mac, sizeof(obj->mac));
		va_end(args);

		break;
	}
	if (osThreadGetId() != sobj->athandle->at_rx_task) {
		osThreadResume(sobj->athandle->at_rx_task);
	}
	return ret;
}

static int virt_net_spi_deinit(virt_net_t *obj)
{
	return -1;
}

static void __pbuf_free_custom(struct pbuf *p)
{
	struct spi_custom_pbuf *pbuf_desc = (struct spi_custom_pbuf *)p;

	spi_buffer_free(pbuf_desc->spbuf);
	xQueueSend(pbuf_desc->sobj->txq, &pbuf_desc, 0);
	//printf("free:%p\r\n", pbuf_desc);
}

static void __virt_net_spi_task(void *arg)
{
	int ret;
	struct virt_net_spi *sobj = (struct virt_net_spi *)arg;
    struct spi_custom_pbuf *pbuf_desc = NULL;

	while (1) {
		//printf("%d\r\n", uxQueueMessagesWaiting(sobj->txq));
		xQueueReceive(sobj->txq, &pbuf_desc, portMAX_DELAY);
		//printf("txq:%p\r\n", pbuf_desc);

		ret = _virl_net_spi_read(&pbuf_desc->spbuf);
		if (sobj->vnet.netmode == VIRTNET_NET_MODE_NCP) {
			if (ret > 0) {
				spi_buffer_free(pbuf_desc->spbuf);
			}
			xQueueSend(sobj->txq, &pbuf_desc, 0);
			//printf("111 free:%p\r\n", pbuf_desc);
			continue;
		}
		if (ret > 0) {
			virt_net_spi_input(sobj, (net_buf_t)pbuf_desc, pbuf_desc->spbuf->data, ret, __pbuf_free_custom);
		} else {
			xQueueSend(sobj->txq, &pbuf_desc, 0);
			//printf("222 free:%p\r\n", pbuf_desc);
		}
	}
}

int virt_net_spi_input(struct virt_net_spi *sobj,
                  net_buf_t net_buf,
                  void *payload,
                  uint16_t length,
		          net_buf_free_fn free_fn)
{
    struct pbuf *p;
    struct spi_custom_pbuf *spi_pbuf = (struct spi_custom_pbuf *)net_buf;

    spi_pbuf->p.custom_free_function = (pbuf_free_custom_fn)free_fn;
    p = pbuf_alloced_custom(PBUF_RAW, length, PBUF_REF | PBUF_TYPE_FLAG_STRUCT_DATA_CONTIGUOUS, &spi_pbuf->p, payload, length);
    assert(p != NULL);

    if (sobj->vnet.netif.input == NULL) {
    	free_fn(net_buf);
    	return -1;
    }
    if (sobj->vnet.netif.input(p, &sobj->vnet.netif))
    {
        free_fn(net_buf);
        return -1;
    }
    return 0;
}

virt_net_t virt_net_spi_create(void)
{
	int ret = -1;
	struct spi_custom_pbuf *tx_desc;
	static const osThreadAttr_t _virt_net_task_attr = {
	  .name = "spi_eth",
	  .priority = (osPriority_t) osPriorityRealtime6,
	  .stack_size = 2048
	};

    struct virt_net_spi *sobj = pvPortMalloc(sizeof(struct virt_net_spi));
    if (sobj == NULL) {
      return NULL;
    }

    memset(sobj, 0, sizeof(struct virt_net_spi));

    sobj->vnet.init = virt_net_spi_init;
    sobj->vnet.deinit = virt_net_spi_deinit;
    sobj->vnet.ctrl = virt_net_spi_control;

    sobj->txq = xQueueCreate(TX_BUFFER_COUNT, sizeof(void *));
    if (!sobj->txq) {
    	return NULL;
    }
    sobj->txbuf_desc = pvPortCalloc(TX_BUFFER_COUNT, sizeof(struct spi_custom_pbuf));
    if (!sobj->txbuf_desc) {
    	vQueueDelete(sobj->txq);
    	return NULL;
    }
    tx_desc = (struct spi_custom_pbuf *)sobj->txbuf_desc;
    for (int i = 0; i < TX_BUFFER_COUNT; i++, tx_desc++) {
    	tx_desc->sobj = sobj;
    	xQueueSend(sobj->txq, &tx_desc, 0);
    }

    spi_bind(SPI_MSG_CTRL_TRAFFIC_NETWORK, 16);

    osThreadNew(__virt_net_spi_task, sobj, &_virt_net_task_attr);

    sobj->athandle = at_spisync_init();

    vTaskDelay(100);

    do {
        ret = sobj->vnet.ctrl(&sobj->vnet, VIRT_NET_CTRL_GET_NETMODE, &sobj->vnet.netmode);
    	if (ret != 0) {
    		vTaskDelay(1000);
    	}

    } while(ret != 0);

    do {
        ret = sobj->vnet.ctrl(&sobj->vnet, VIRT_NET_CTRL_GET_MAC, sobj->vnet.mac);
    	if (ret != 0) {
    		vTaskDelay(1000);
    	}
    } while(ret != 0);

	printf("The device:%02X:%02X:%02X:%02X:%02X:%02X  is work on %s mode.\r\n",
			sobj->vnet.mac[0], sobj->vnet.mac[1], sobj->vnet.mac[2], sobj->vnet.mac[3], sobj->vnet.mac[4], sobj->vnet.mac[5],
			sobj->vnet.netmode?"NCP":"RCP");

    sobj->vnet.mtu = 1500;

    return &sobj->vnet;
}

