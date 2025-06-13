/*
 * spi_iface.c
 *
 *  Created on: Dec 10, 2024
 */

#include <stdio.h>
#include <string.h>
#include "spi.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "semphr.h"
#include "main.h"
#include "dwt.h"

#define SPI_WAIT_TXN_TIMEOUT_MS			2000
#define SPI_WAIT_MSG_XFER_TIMEOUT_MS	500
#define SPI_WAIT_HDR_ACK_TIMEOUT_MS		100

#define SPI_HEADER_MAGIC_CODE	0x55AA

#define SPI_XFER_MTU_BYTES	6 * 1024

/* Transfer with size greater than this value should use DMA. */
#define SPI_DMA_XFER_SIZE_THRESHOLD	8

struct spi_header {
	uint16_t magic;
	uint16_t len;
	uint8_t version : 2;
	/* Peer RX is stalled. */
	uint8_t rx_stall : 1;
	uint8_t flags : 5;
	uint8_t type;
	uint16_t rsvd;
} __attribute__((packed));

#define spi_header_init(h, _type, _len)	do {	\
	(h)->magic = SPI_HEADER_MAGIC_CODE;	\
	(h)->type = _type;		\
	(h)->version = 0;		\
	(h)->rx_stall = 0;		\
	(h)->flags = 0;			\
	(h)->len = _len;		\
	(h)->rsvd = 0;			\
} while (0)

/* SPI transfer state. */
enum {
	SPI_XFER_STATE_IDLE,
	SPI_XFER_STATE_FIRST_PART,
	SPI_XFER_STATE_SECOND_PART,
	SPI_XFER_STATE_TXN_DONE,
};

enum {
	SPI_EVT_TXN_PENDING = 0x1,
	SPI_EVT_TXN_RDY = 0x2,
	SPI_EVT_HDR_ACKED = 0x4,
	SPI_EVT_HW_XFER_DONE = 0x8,
};

enum {
	SPI_XFER_F_SKIP_FIRST_TXN_WAIT = 0x1,
};

#define SPI_STAT_INC(stat, mb, val)	(stat)->mb += (val)

#define SPI_TXQ_LEN	8
#define SPI_RXQ_LEN	8

/**
 * SPI transfer engine structure
 * 
 * This structure manages the state and resources for SPI communication,
 * including support for multiple receive queues bound to different message types.
 */
struct spi_xfer_engine {
    /* Transfer task handle */
    osThreadId_t task;
    /* Stop flag for clean shutdown */
    int stop;
    /* Initialization flag */
    int inited;
    /* Event flags for synchronization */
    EventGroupHandle_t event;
    /* Current transfer state */
    int state;
    /* Slave RX is stalled */
    int rx_stall;
    /* Single transmit queue */
    QueueHandle_t txq;
    /* Array of receive queues by type */
    QueueHandle_t rxq[SPI_MSG_CTRL_TRAFFIC_TYPE_MAX];
    /* Bitmap of bound traffic types */
    uint8_t rxq_bound;
    /* Current transmit buffer */
    struct spi_buffer *txbuf;
    /* Transfer statistics */
    struct spi_stat stat;
};

extern SPI_HandleTypeDef hspi1;
static struct spi_xfer_engine xfer_engine;
#define SPI_BUF_ALIGN_MASK	(0x3)

/* SPI transfer trace points. */
enum {
	SPI_TP_NONE = 0,
	SPI_TP_WRITE = 1,
	SPI_TP_ASSERT_CS = 2,
	SPI_TP_SLAVE_TXN_RDY = 3,
	SPI_TP_FIRST_TXN_START = 4,
	SPI_TP_FIRST_TXN_END = 5,
	SPI_TP_SECOND_TXN_START = 6,
	SPI_TP_SECOND_TXN_END = 7,
	SPI_TP_WAIT_HDR_ACK_START = 8,
	SPI_TP_HDR_ACKED = 9,
	SPI_TP_WAIT_HDR_ACK_END = 10,
	SPI_TP_DEASSERT_CS = 11,
	SPI_TP_READ = 12,
	SPI_TP_NUM = 12,
};

//#define spi_log	printf
#define spi_log(...)

#define spi_trace(e, m, ...) do {	\
	if (e)							\
		ITM_SendChar(e);			\
	spi_log(m, ##__VA_ARGS__);		\
} while (0)

//#define spi_trace(...)

static inline void spi_buffer_set_traffic_type(struct spi_buffer *buf, uint8_t type)
{
	buf->cb[0] = type;
}

static inline uint8_t spi_buffer_get_traffic_type(struct spi_buffer *buf)
{
	return buf->cb[0];
}

/* For prepending data like header. */
static inline void *spi_buffer_push(struct spi_buffer *buf, unsigned long size)
{
	char *p, *start, *data;

	if (!buf)
		return NULL;

	if (!size)
		return buf->data;

	p = (char *)buf;
	data = buf->data;
	start = p + sizeof(struct spi_buffer);
	if (data - size < start) {
		printf("Illegal try of spi buffer push!\r\n");
		return NULL;
	}

	buf->data = data - size;
	buf->len += size;
	return buf->data;
}

/* For removing leading data like header. */
static inline void *spi_buffer_pull(struct spi_buffer *buf, unsigned long size)
{
	char *p, *end, *data;

	if (!buf)
		return NULL;

	if (!size)
		return buf->data;

	p = (char *)buf;
	data = buf->data;
	end = p + sizeof(struct spi_buffer) + buf->cap;
	if (data + size > end) {
		printf("Illegal try of spi buffer pull\r\n");
		return NULL;
	}

	buf->data = data + size;
	buf->len -= size;
	return buf->data;
}

struct spi_buffer *spi_buffer_alloc(unsigned int size, unsigned int reserve)
{
	unsigned int cap, extra;
	struct spi_buffer *buf;
	int desc_size = sizeof(struct spi_buffer);

	cap = (size + reserve + SPI_BUF_ALIGN_MASK) & ~SPI_BUF_ALIGN_MASK;
	buf = pvPortMalloc(cap + desc_size);
	if (!buf)
		return NULL;

	buf->flags = 0;
	buf->len = size;
	buf->cap = cap;
	buf->data = (char *)buf + desc_size + reserve;
	memset(buf->cb, 0, sizeof(buf->cb));
	/* Fill in the debug pattern. */
	extra = cap - size - reserve;
	while (extra) {
		uint8_t *p = (uint8_t *)buf + desc_size;

		p[cap - extra] = 0x88;
		extra--;
	}
	return buf;
}

struct spi_buffer *spi_tx_buffer_alloc(unsigned int size)
{
	return spi_buffer_alloc(size, sizeof(struct spi_header));
}

void spi_buffer_free(struct spi_buffer *buf)
{
	if (buf)
		vPortFree(buf);
}

/* Get tx buffer from in non-blocking mode. */
static struct spi_buffer *spi_get_txbuf(struct spi_xfer_engine *engine)
{
	struct spi_buffer *buf;
	BaseType_t ret;

	if (engine->txbuf)
		return engine->txbuf;

	ret = xQueueReceive(engine->txq, &buf, 0);
	if (ret != pdTRUE)
		buf = NULL;

	engine->txbuf = buf;
	if (buf) {
		SPI_STAT_INC(&engine->stat, tx_pkts, 1);
		SPI_STAT_INC(&engine->stat, tx_bytes, buf->len);
	}
	return buf;
}

/* return 1 if the header is valid. */
static int inline spi_header_validate(struct spi_header *hdr)
{
	if (hdr->magic != SPI_HEADER_MAGIC_CODE) {
		printf("Invalid magic 0x%x\r\n", hdr->magic);
		return 0;
	}

	if (hdr->len > SPI_XFER_MTU_BYTES) {
		printf("invalid len %d\r\n", hdr->len);
		return 0;
	}
	return 1;
}

static int inline spi_wait_event(struct spi_xfer_engine *engine, uint32_t event,
									int timeout_ms)
{
    EventBits_t bits;
    TickType_t ticks;

    if (timeout_ms >= 0) {
    	ticks = pdMS_TO_TICKS(timeout_ms);
    } else {
    	ticks = portMAX_DELAY;
    }

	bits = xEventGroupWaitBits(engine->event, event, pdTRUE, pdFALSE, ticks);
	if (bits & event)
		return 1;

	return 0;
}

static int inline spi_clear_event(struct spi_xfer_engine *engine, uint32_t event)
{
	xEventGroupClearBits(engine->event, event);
	return 0;
}

static int spi_txrx(struct spi_xfer_engine *engine, void *tx_buf, void *rx_buf, uint16_t len)
{
    HAL_StatusTypeDef status;

    if (!engine || !tx_buf || !rx_buf)
    	return -1;

    if (!len)
    	return 0;

    /* It is a waste of time to setup DMA for short transfer. */
    if (len <= SPI_DMA_XFER_SIZE_THRESHOLD) {
        status = HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, len, 100);
        if (status != HAL_OK) {
    		printf("spi_txrx failed, %d\r\n", status);
    		SPI_STAT_INC(&engine->stat, io_err, 1);
    		return -2;
    	}
    	return 0;
    }

    status = HAL_SPI_TransmitReceive_DMA(&hspi1, tx_buf, rx_buf, len);
	if (status != HAL_OK) {
		printf("spi_txrx failed, %d\r\n", status);
		SPI_STAT_INC(&engine->stat, io_err, 1);
		return -2;
	}

	/* Wait for spi transaction completion. */
	if (!spi_wait_event(engine, SPI_EVT_HW_XFER_DONE, SPI_WAIT_MSG_XFER_TIMEOUT_MS)) {
		printf("spi txrx transaction timeouted\r\n");
		SPI_STAT_INC(&engine->stat, wait_msg_xfer_timeouts, 1);
		return -3;
	}

	return 0;
}

#ifdef SPI_TX_ENABLE
static int spi_tx(struct spi_xfer_engine *engine, void *tx_buf, uint16_t len)
{
    HAL_StatusTypeDef status;

    if (!engine || !tx_buf)
    	return -1;

    if (!len)
    	return 0;

    status = HAL_SPI_Transmit_DMA(&hspi1, tx_buf, len);
	if (status != HAL_OK) {
		printf("spi_tx failed, %d\r\n", status);
		SPI_STAT_INC(&engine->stat, io_err, 1);
		return -2;
	}

	/* Wait for spi transaction completion. */
	if (!spi_wait_event(engine, SPI_EVT_HW_XFER_DONE, SPI_WAIT_MSG_XFER_TIMEOUT_MS)) {
		printf("spi tx transaction timeouted\r\n");
		SPI_STAT_INC(&engine->stat, wait_body_txn_timeouts, 1);
		return -3;
	}

	return 0;
}
/* SPI_TX_ENABLE */
#endif

static int spi_rx(struct spi_xfer_engine *engine, void *rx_buf, uint16_t len)
{
    HAL_StatusTypeDef status;

    if (!engine || !rx_buf)
    	return -1;

    if (!len)
    	return 0;

    /* It is a waste of time to setup DMA for short transfer. */
    if (len <= SPI_DMA_XFER_SIZE_THRESHOLD) {
    	status = HAL_SPI_Receive(&hspi1, rx_buf, len, 100);
    	if (status != HAL_OK) {
    		printf("spi_rx failed, %d\r\n", status);
    		SPI_STAT_INC(&engine->stat, io_err, 1);
    		return -2;
    	}
    	return 0;
    }

    status = HAL_SPI_Receive_DMA(&hspi1, rx_buf, len);
	if (status != HAL_OK) {
		printf("spi_rx failed, %d\r\n", status);
		SPI_STAT_INC(&engine->stat, io_err, 1);
		return -2;
	}

	/* Wait for spi transaction completion. */
	if (!spi_wait_event(engine, SPI_EVT_HW_XFER_DONE, SPI_WAIT_MSG_XFER_TIMEOUT_MS)) {
		printf("spi rx transaction timeouted\r\n");
		SPI_STAT_INC(&engine->stat, wait_msg_xfer_timeouts, 1);
		return -3;
	}

	return 0;
}

#if 1
static int spi_xfer_one(struct spi_xfer_engine *engine, struct spi_buffer *txbuf,
							int wait_txn_rdy)
{
    void *txp;
    int ret, err = -1;
    uint16_t xfer_size;
    struct spi_header mh, *pmh, *psh;
    struct spi_buffer *rxbuf = NULL;

    spi_trace(SPI_TP_NONE, "wait_txn_rdy %d\r\n", wait_txn_rdy);
    engine->state = SPI_XFER_STATE_FIRST_PART;
    if (wait_txn_rdy &&
    	!spi_wait_event(engine, SPI_EVT_TXN_RDY, SPI_WAIT_TXN_TIMEOUT_MS)) {
		SPI_STAT_INC(&engine->stat, wait_txn_timeouts, 1);
		printf("waiting for spi txn ready timeouted\r\n");
		return -1;
    }

    /* Re-initialize events in case of pending ones. */
    spi_clear_event(engine, SPI_EVT_HW_XFER_DONE | SPI_EVT_HDR_ACKED);

    /* Yes, this allocation will be wasted if there is no data from slave. */
    rxbuf = spi_buffer_alloc(SPI_XFER_MTU_BYTES, 0);
    if (!rxbuf) {
    	printf("No mem for rxbuf\r\n");
    	SPI_STAT_INC(&engine->stat, mem_err, 1);
    	return -1;
    }

	spi_trace(SPI_TP_FIRST_TXN_START, "start the first transaction\r\n");
    if (txbuf) {
		uint16_t msglen = txbuf->len;
		uint8_t type = spi_buffer_get_traffic_type(txbuf);

    	if (!engine->rx_stall) {
			pmh = txbuf->data;
			msglen = txbuf->len - sizeof(struct spi_header);

			/* Initialize master header. */
			spi_header_init(pmh, type, msglen);
			txp = txbuf->data;
			xfer_size = (txbuf->len + SPI_BUF_ALIGN_MASK) & ~SPI_BUF_ALIGN_MASK;
    	} else {
    		spi_header_init(&mh, 0, 0);
    		txp = &mh;
    		xfer_size = sizeof(struct spi_header);
    	}
    } else {
    	/* Initialize master header. */
    	spi_header_init(&mh, 0, 0);
    	txp = &mh;
    	xfer_size = sizeof(struct spi_header);
    }

    if (spi_txrx(engine, txp, rxbuf->data, xfer_size)) {
    	printf("Failed to do the first transaction\r\n");
        goto out;
    }

	psh = rxbuf->data;
	spi_trace(SPI_TP_FIRST_TXN_END,
			"slave spi header, magic 0x%x, len (%d, 0x%x), version %u, type %x, "
			"flags 0x%x, rsvd 0x%x\r\n",
			psh->magic, psh->len, psh->len, psh->version, psh->type, psh->flags, psh->rsvd);
	ret = spi_header_validate(psh);
	if (!ret) {
		printf("Invalid spi header from peer, magic 0x%x, len (%d, 0x%x), version %u, type %x, "
				"flags 0x%x, rsvd 0x%x\r\n",
				psh->magic, psh->len, psh->len, psh->version, psh->type, psh->flags, psh->rsvd);
		SPI_STAT_INC(&engine->stat, hdr_err, 1);
		goto out;
	}

	int rx_restore = 0;

	if (!engine->rx_stall) {
		if (psh->rx_stall) {
			SPI_STAT_INC(&engine->stat, rx_stall, 1);
			spi_trace(SPI_TP_NONE, "Slave RX stalled\r\n");
		}
	} else if (!psh->rx_stall) {
		rx_restore = 1;
	}
	engine->rx_stall = psh->rx_stall;

	/* Receive the remaining data from slave if any. */
	if (psh->len + sizeof(struct spi_header) > xfer_size) {
		uint8_t *rxp = (uint8_t *)rxbuf->data;
		uint16_t remain = psh->len + sizeof(struct spi_header) - xfer_size;

		spi_trace(SPI_TP_SECOND_TXN_START, "Receiving remaining data\r\n");
		engine->state = SPI_XFER_STATE_SECOND_PART;
		remain = (remain + SPI_BUF_ALIGN_MASK) & ~SPI_BUF_ALIGN_MASK;
		rxp += xfer_size;
		if (spi_rx(engine, rxp, remain)) {
			printf("Failed to receive the remaining bytes\r\n");
			goto out;
		}
		spi_trace(SPI_TP_SECOND_TXN_END, "Remaining transfer completed\r\n");
	}

	/* free txbuf after the message transaction. */
	if (txbuf) {
		if (!engine->rx_stall && !rx_restore) {
			engine->txbuf = NULL;
			spi_buffer_free(txbuf);
		}
	}

	if (psh->len) {
		SPI_STAT_INC(&engine->stat, rx_pkts, 1);
		SPI_STAT_INC(&engine->stat, rx_bytes, psh->len);
		spi_buffer_pull(rxbuf, sizeof(struct spi_header));
		/* rx buffer length fix-up */
		rxbuf->len = psh->len;

		/* Get message type from header and store in buffer's control block */
		uint8_t msg_type = psh->type;
		spi_buffer_set_traffic_type(rxbuf, msg_type);
		
		/* 
		 * Note: Thread safety consideration required here.
		 * If a queue is unbound by another thread while we're accessing it,
		 * or if multiple transfers are accessing rxq_bound bitmap concurrently,
		 * race conditions could occur. Consider using appropriate synchronization.
		 */
		
		/* Select appropriate queue based on type */
		if (msg_type < SPI_MSG_CTRL_TRAFFIC_TYPE_MAX && 
			(engine->rxq_bound & (1 << msg_type))) {
			/* TODO transfer task should not be blocked for specific receiver. */
			ret = xQueueSend(engine->rxq[msg_type], &rxbuf, portMAX_DELAY);
			if (ret != pdTRUE) {
				spi_trace(SPI_TP_NONE, "failed to send to type %d rxq, msg discarded\r\n", msg_type);
				spi_buffer_free(rxbuf);
				SPI_STAT_INC(&engine->stat, rx_drop, 1);
			}
		} else {
			/* No queue bound for this type, discard message */
			spi_trace(SPI_TP_NONE, "No queue bound for type %d, msg discarded\r\n", msg_type);
			spi_buffer_free(rxbuf);
			SPI_STAT_INC(&engine->stat, rx_drop, 1);
		}
	} else if (rxbuf) {
		spi_buffer_free(rxbuf);
	}

	/* Wait until slave acknowledged header. */
	spi_trace(SPI_TP_WAIT_HDR_ACK_START, "waiting for header ack\r\n");
	while (!spi_wait_event(engine, SPI_EVT_HDR_ACKED, SPI_WAIT_HDR_ACK_TIMEOUT_MS)) {
		GPIO_PinState pin_state = HAL_GPIO_ReadPin(SPI_SLAVE_DATA_RDY_GPIO_Port,
		    										SPI_SLAVE_DATA_RDY_Pin);
		if (pin_state == GPIO_PIN_RESET) {
			printf("Since the slave txn/data pin is already low, did we miss that interrupt?\r\n");
			break;
		}

		printf("wait header ack timeouted\r\n");
		SPI_STAT_INC(&engine->stat, wait_hdr_ack_timeouts, 1);
	}
	spi_trace(SPI_TP_WAIT_HDR_ACK_END, "Got header ack\r\n");

	return 0;

out:
	if (rxbuf)
		spi_buffer_free(rxbuf);
	return err;
}

#else
static int spi_xfer_one(struct spi_xfer_engine *engine, struct spi_buffer *txbuf,
							int wait_txn_rdy)
{
    int ret = 0;
    HAL_StatusTypeDef status;
    struct spi_header mh, sh;
    struct spi_buffer *rxbuf = NULL;

    if (txbuf) {
        spi_header_init(&mh, 0, txbuf->len);
    } else {
        spi_header_init(&mh, 0, 0);
    }

    engine->state = SPI_XFER_STATE_FIRST_PART;
    trace("wait_txn_rdy %d\r\n", wait_txn_rdy);
    if (wait_txn_rdy &&
    	!spi_wait_event(engine, SPI_EVT_TXN_RDY, SPI_WAIT_TXN_TIMEOUT_MS)) {
		//SPI_STAT_INC(&engine->stat, wait_hdr_txn_timeouts, 1);
		printf("waiting for spi txn/data ready timeouted\r\n");
		return -1;
    }

	trace("start header transaction\r\n");
	status = HAL_SPI_TransmitReceive(&hspi1, (const uint8_t *)&mh, (uint8_t *)&sh, sizeof(mh), 10);
	if (status != HAL_OK) {
		printf("failed to transmit spi header, %d\r\n", status);
		SPI_STAT_INC(&engine->stat, io_err, 1);
		return -1;
	}

	trace("slave spi header, magic 0x%x, len 0x%x, version %u, type %x, "
			"flags 0x%x, rsvd 0x%x\r\n",
			sh.magic, sh.len, sh.version, sh.type, sh.flags, sh.rsvd);
	ret = spi_header_validate(&sh);
	if (!ret) {
		printf("Invalid spi header from peer, magic 0x%x, len (%d, 0x%x), version %u, type %x, "
				"flags 0x%x, rsvd 0x%x\r\n",
				sh.magic, sh.len, sh.len, sh.version, sh.type, sh.flags, sh.rsvd);
		SPI_STAT_INC(&engine->stat, hdr_err, 1);
		return -1;
	}

	/* Message transfer. */
	trace("master len %u, slave len %u\r\n", mh.len, sh.len);
	uint16_t xfer_size = mh.len > sh.len ? mh.len : sh.len;
	if (!xfer_size) {
		trace("transfer size is 0!\r\n");
		SPI_STAT_INC(&engine->stat, idle_hdr, 1);
		return 0;
	}

	xfer_size = (xfer_size + SPI_BUF_ALIGN_MASK) & ~SPI_BUF_ALIGN_MASK;
	trace("message transfer size %u\r\n", xfer_size);
	/* We do need to set up a spi transfer. */
	if (sh.len) {
		rxbuf = spi_buffer_alloc(xfer_size, 0);
		if (!rxbuf) {
			SPI_STAT_INC(&engine->stat, mem_err, 1);
			return -1;
		}
	}

	trace("start message transaction\r\n");
	engine->state = SPI_XFER_STATE_SECOND_PART;
	if (mh.len && sh.len) {
		uint8_t *txptr;

		/* XXX assuming that tx buffer is shorter than 8192! */
		if (mh.len < sh.len) {
			memcpy(engine->tmp_txbuf, txbuf->data, txbuf->len);
			txptr = engine->tmp_txbuf;
		} else {
			txptr = txbuf->data;
		}

		status = HAL_SPI_TransmitReceive_DMA(&hspi1, txptr, rxbuf->data, xfer_size);
		if (status != HAL_OK) {
			printf("failed to start hal spi txrx, %d\r\n", status);
			SPI_STAT_INC(&engine->stat, io_err, 1);
			goto err_out;
		}
	} else if (mh.len) {
		status = HAL_SPI_Transmit_DMA(&hspi1, txbuf->data, xfer_size);
		if (status != HAL_OK) {
			printf("failed to start spi tx, %d\r\n", status);
			SPI_STAT_INC(&engine->stat, io_err, 1);
			goto err_out;
		}
	} else {
		status = HAL_SPI_Receive_DMA(&hspi1, rxbuf->data, xfer_size);
		if (status != HAL_OK) {
			printf("failed to start spi rx, %d\r\n", status);
			SPI_STAT_INC(&engine->stat, io_err, 1);
			goto err_out;
		}
	}

	trace("waiting for spi transfer completion\r\n");
	/* Wait for spi transaction completion. */
	if (!spi_wait_event(engine, SPI_EVT_HW_XFER_DONE, SPI_WAIT_MSG_XFER_TIMEOUT_MS)) {
		printf("spi body transaction timeouted\r\n");
		//SPI_STAT_INC(&engine->stat, wait_body_txn_timeouts, 1);
		goto err_out;
	}

	trace("spi transfer completed\r\n");
	/* txbuf is free after the message transaction. */
	if (txbuf) {
		engine->txbuf = NULL;
		spi_buffer_free(txbuf);
	}

	if (rxbuf) {
		SPI_STAT_INC(&engine->stat, rx_pkts, 1);
		SPI_STAT_INC(&engine->stat, rx_bytes, sh.len);
		/* rx buffer length fix-up */
		rxbuf->len = sh.len;
		ret = xQueueSend(engine->rxq, &rxbuf, 0);
		if (ret != pdTRUE) {
			trace("failed to send to rxq, the msg is dicarded\r\n");
			spi_buffer_free(rxbuf);
			SPI_STAT_INC(&engine->stat, rx_drop, 1);
		}
	}

	/* Wait until slave acknowledged header. */
	while (!spi_wait_event(engine, SPI_EVT_HDR_ACKED, SPI_WAIT_HDR_ACK_TIMEOUT_MS)) {
		GPIO_PinState pin_state = HAL_GPIO_ReadPin(SPI_SLAVE_DATA_RDY_GPIO_Port,
		    										SPI_SLAVE_DATA_RDY_Pin);
		if (pin_state == GPIO_PIN_RESET) {
			printf("Since the slave txn/data pin is already low, did we miss that interrupt?\r\n");
			break;
		}

		printf("wait header ack timeouted\r\n");
		SPI_STAT_INC(&engine->stat, wait_hdr_ack_timeouts, 1);
	}
	return 0;

err_out:
	if (rxbuf)
		spi_buffer_free(rxbuf);
	return -1;
}
#endif

static inline int spi_set_cs(struct spi_xfer_engine *engine, int assert)
{
    if (assert) {
        HAL_GPIO_WritePin(QCC74X_LP_WAKEUP_GPIO_Port, QCC74X_LP_WAKEUP_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(QCC74X_LP_WAKEUP_GPIO_Port, QCC74X_LP_WAKEUP_Pin, GPIO_PIN_RESET);
    }

    return 0;
}

int spi_do_xfer(struct spi_xfer_engine *engine, int flags)
{
    struct spi_buffer *txbuf;
    int rx_pending;
    int wait_txn_rdy;

    while (1) {
        /* Get txbuf */
        txbuf = spi_get_txbuf(engine);

        /* Read data ready GPIO level */
        rx_pending = HAL_GPIO_ReadPin(SPI_SLAVE_DATA_RDY_GPIO_Port, SPI_SLAVE_DATA_RDY_Pin);

        spi_trace(SPI_TP_NONE, "txbuf %p, rx_pending %d\r\n", txbuf, rx_pending);
        /* Check if txbuf is valid or data is ready for transfer */
        if (txbuf || rx_pending == GPIO_PIN_SET) {
            /* Assert chip select */
        	spi_trace(SPI_TP_ASSERT_CS, "Assert CS\r\n");
            spi_set_cs(engine, 1);

            /* Transfer one packet */
            if (flags & SPI_XFER_F_SKIP_FIRST_TXN_WAIT) {
            	flags &= ~SPI_XFER_F_SKIP_FIRST_TXN_WAIT;
            	wait_txn_rdy = 0;
            } else {
            	wait_txn_rdy = 1;
            }

            spi_xfer_one(engine, txbuf, wait_txn_rdy);

            /* De-assert chip select */
            spi_trace(SPI_TP_DEASSERT_CS, "Deassert CS\r\n");
            spi_set_cs(engine, 0);
            engine->state = SPI_XFER_STATE_TXN_DONE;
        } else {
            /* Neither txbuf nor rx_pending require processing, exit loop */
            break;
        }
    }

    return 0;
}

static void spi_show_stat(struct spi_stat *stat)
{
	printf("tx %lu pkts, %lu bytes, rx %lu pkts, %lu bytes, drop %lu pkts, mem_err %lu, stall %lu\r\n",
			stat->tx_pkts, stat->tx_bytes, stat->rx_pkts, stat->rx_bytes, stat->rx_drop, stat->mem_err,
			stat->rx_stall);
	printf("IO error %lu, header error %lu, wait_txn_timeout %lu, wait_msg_xfer_timeouts %lu, "
			"wait_hdr_ack_timeout %lu\r\n",
			stat->io_err, stat->hdr_err, stat->wait_txn_timeouts, stat->wait_msg_xfer_timeouts,
			stat->wait_hdr_ack_timeouts);
}

static void spi_xfer_engine_task(void *arg)
{
    EventBits_t bits;
    struct spi_xfer_engine *engine = arg;

    /* Wait for events and process them. */
    while (!engine->stop) {
    	engine->state = SPI_XFER_STATE_IDLE;
    	bits = SPI_EVT_TXN_PENDING | SPI_EVT_TXN_RDY;
        bits = xEventGroupWaitBits(engine->event, bits, pdTRUE, pdFALSE,
                                  portMAX_DELAY);
        spi_trace(SPI_TP_NONE, "Got event bits %x\r\n", bits);
        if (bits & SPI_EVT_TXN_RDY) {
            spi_do_xfer(engine, SPI_XFER_F_SKIP_FIRST_TXN_WAIT);
        } else if (bits & SPI_EVT_TXN_PENDING) {
            spi_do_xfer(engine, 0);
        }
    }
}

int spi_transaction_init(void)
{
    int ret;

    osThreadAttr_t task_attr = {
        .name = "spi_xfer_engine",
        .priority = (osPriority_t) osPriorityRealtime7,
        .stack_size = 8 * 1024
    };

    /* Initialize rxq array to NULL and rxq_bound to 0 */
    memset(xfer_engine.rxq, 0, sizeof(xfer_engine.rxq));
    xfer_engine.rxq_bound = 0;

    /* Create event group for SPI transaction */
    xfer_engine.event = xEventGroupCreate();
    if (!xfer_engine.event) {
        printf("Failed to create event group for SPI\r\n");
        ret = -1;
        goto error;
    }
    
    /* Create TX queue */
    xfer_engine.txq = xQueueCreate(SPI_TXQ_LEN, sizeof(void *));
    if (!xfer_engine.txq) {
        printf("Failed to create txq\r\n");
        ret = -1;
        goto error;
    }

    /* Create SPI transfer engine task */
    xfer_engine.stop = 0;
    xfer_engine.task = osThreadNew(spi_xfer_engine_task, &xfer_engine, &task_attr);
    if (!xfer_engine.task) {
        printf("Failed to create spi xfer engine task\r\n");
        ret = -1;
        goto error;
    }

    /* Check the state of the slave data ready pin */
    GPIO_PinState pin_state = HAL_GPIO_ReadPin(SPI_SLAVE_DATA_RDY_GPIO_Port,
                                              SPI_SLAVE_DATA_RDY_Pin);
    if (pin_state == GPIO_PIN_SET) {
        /* Set the TXN event if data is ready */
        xEventGroupSetBits(xfer_engine.event, SPI_EVT_TXN_RDY);
    }

    xfer_engine.rx_stall = 0;
    xfer_engine.inited = 1;
    printf("SPI transaction initialized\r\n");
    return 0;

error:
    /* Clean up resources in case of error */
    if (xfer_engine.txq) {
        vQueueDelete(xfer_engine.txq);
        xfer_engine.txq = NULL;
    }

    if (xfer_engine.event) {
        vEventGroupDelete(xfer_engine.event);
        xfer_engine.event = NULL;
    }

    return ret;
}

/**
 * Read data from the SPI interface
 * 
 * This function handles both raw data and buffer pointer operations based on the
 * message operation type (op_type) field.
 *
 * @param msg         Message structure for receiving data
 * @param timeout_ms  Timeout for queue operations in milliseconds (-1 for infinite)
 * @return            Number of bytes read or negative error code
 */

 int spi_read(struct spi_msg *msg, int timeout_ms)
{
    BaseType_t ret, ticks;
    struct spi_buffer *buf;
    uint8_t traffic_type = SPI_MSG_CTRL_TRAFFIC_AT_CMD; /* Default to AT commands */
    QueueHandle_t targetQ;

    /* Verify message is valid and operation type is supported */
    if (!msg || (msg->op_type != SPI_MSG_OP_DATA && msg->op_type != SPI_MSG_OP_BUFFER_PTR))
        return -1;

    /* Verify appropriate fields based on operation type */
    if (msg->op_type == SPI_MSG_OP_DATA) {
        if (!msg->data || !msg->data_len)
            return -1;
    } else if (msg->op_type == SPI_MSG_OP_BUFFER_PTR) {
        if (!msg->buffer_ptr)
            return -1;
    }

    /* Verify context is initialized */
    if (!xfer_engine.inited) {
        printf("SPI transaction is NOT initialized!\r\n");
        return -2;
    }

    /* Process control information if present */
    if (msg->ctrl) {
    	/* Check for traffic type control information */
    	if (msg->ctrl->type == SPI_MSG_CTRL_TRAFFIC_TYPE) {
    		/* Validate control data length */
            if (msg->ctrl->len == SPI_MSG_CTRL_TRAFFIC_TYPE_LEN && msg->ctrl->val) {
                /* Extract traffic type */
                traffic_type = *((uint8_t *)msg->ctrl->val);
            } else {
                printf("Invalid traffic type control info\r\n");
            }
        }
    }

    /* Verify traffic type is valid and bound */
    if (traffic_type >= SPI_MSG_CTRL_TRAFFIC_TYPE_MAX || 
        !(xfer_engine.rxq_bound & (1 << traffic_type))) {
        printf("Traffic type %d not bound, operation not allowed\r\n", traffic_type);
        return -3;
    }

    /* Get the target queue for this traffic type */
    targetQ = xfer_engine.rxq[traffic_type];
    spi_trace(SPI_TP_READ, "spi_read type %d\r\n", traffic_type);

    /* Set up timeout value */
    if (timeout_ms < 0)
        ticks = portMAX_DELAY;
    else
        ticks = pdMS_TO_TICKS(timeout_ms);

    /* Process based on operation type */
    switch (msg->op_type) {
	case SPI_MSG_OP_DATA:
		/* Receive buffer from queue */
		ret = xQueueReceive(targetQ, &buf, ticks);
		if (ret != pdTRUE) {
			return -4;
		}

		/* Copy data with truncation handling */
		if (msg->data_len >= buf->len) {
			msg->data_len = buf->len;
			msg->flags &= ~SPI_MSG_F_TRUNCATED;
		} else {
			msg->flags |= SPI_MSG_F_TRUNCATED;
		}

		/* Copy data and free buffer */
		memcpy(msg->data, buf->data, msg->data_len);
		spi_buffer_free(buf);
		return msg->data_len;

	case SPI_MSG_OP_BUFFER_PTR:
		/* Receive buffer pointer directly into msg->buffer_ptr */
		ret = xQueueReceive(targetQ, msg->buffer_ptr, ticks);
		if (ret != pdTRUE) {
			return -4;
		}

		return (*(msg->buffer_ptr))->len;
	}

	/* Should never reach here, but just in case */
	return -1;
}

/**
 * Write data to the SPI interface
 *
 * This function handles both raw data and pre-allocated buffers based on the
 * message operation type (op_type) field.
 *
 * @param msg         Message containing data or buffer to send
 * @param timeout_ms  Timeout for queue operations in milliseconds (-1 for infinite)
 * @return            Number of bytes written or negative error code
 */
int spi_write(struct spi_msg *msg, int timeout_ms)
{
    BaseType_t ret;
    struct spi_buffer *buf = NULL;
    BaseType_t ticks;
    uint8_t traffic_type = SPI_MSG_CTRL_TRAFFIC_AT_CMD;
    int data_len = 0;

    /* Verify message is valid and operation type is supported */
    if (!msg || (msg->op_type != SPI_MSG_OP_DATA && msg->op_type != SPI_MSG_OP_BUFFER))
        return -1;

    /* Verify context is initialized */
    if (!xfer_engine.inited) {
        printf("SPI transaction is NOT initialized!\r\n");
        return -2;
    }

    /* Process control information if present */
    if (msg->ctrl) {
        /* Check for traffic type control information */
        if (msg->ctrl->type == SPI_MSG_CTRL_TRAFFIC_TYPE) {
            /* Validate control data length */
            if (msg->ctrl->len == SPI_MSG_CTRL_TRAFFIC_TYPE_LEN && msg->ctrl->val) {
                /* Extract traffic type */
                traffic_type = *((uint8_t *)msg->ctrl->val);
            } else {
                printf("Invalid traffic type control info\r\n");
            }
        }
        /* Additional control types can be handled here in the future */
    }

    /* Process based on operation type */
    switch (msg->op_type) {
    case SPI_MSG_OP_DATA:
        /* Verify data operation has valid data pointer and length */
        if (!msg->data || !msg->data_len)
            return -1;

        /* Allocate buffer for data operation */
        spi_trace(SPI_TP_WRITE, "spi_write data mode\r\n");
        buf = spi_buffer_alloc(msg->data_len, sizeof(struct spi_header));
        if (!buf)
            return -3;

        data_len = msg->data_len;
        memcpy(buf->data, msg->data, msg->data_len);
        break;

    case SPI_MSG_OP_BUFFER:
        /* Verify buffer operation has valid buffer */
        if (!msg->buffer)
            return -1;

        /* Use the provided pre-allocated buffer */
        spi_trace(SPI_TP_WRITE, "spi_write buffer mode\r\n");
        buf = msg->buffer;
        data_len = buf->len;
        break;
    }

    /* Set traffic type for the buffer */
    spi_buffer_set_traffic_type(buf, traffic_type);

    /* Push header space */
    if (spi_buffer_push(buf, sizeof(struct spi_header)) == NULL) {
        printf("Can't push SPI buffer header\r\n");
        if (msg->op_type == SPI_MSG_OP_DATA) {
            spi_buffer_free(buf);
        }
        return -4;
    }

    /* Prepare timeout value */
    if (timeout_ms < 0)
        ticks = portMAX_DELAY;
    else
        ticks = pdMS_TO_TICKS(timeout_ms);

    /* Send buffer to transmission queue */
    ret = xQueueSend(xfer_engine.txq, &buf, ticks);
    if (ret != pdTRUE) {
        /* Free buffer on queue send failure if we allocated it */
        if (msg->op_type == SPI_MSG_OP_DATA) {
            spi_buffer_free(buf);
        }
        return -5;
    }
    
    /* Notify transfer engine about pending data */
    xEventGroupSetBits(xfer_engine.event, SPI_EVT_TXN_PENDING);
    
    /* Return number of bytes queued for transmission */
    return data_len;
}

/**
 * Bind a specific traffic type to a dedicated receive queue
 *
 * @param type      Traffic type to bind (must be < SPI_MSG_CTRL_TRAFFIC_TYPE_MAX)
 * @param rxq_size  Size of receive queue to create (0 for default)
 * @return          0 on success, negative value on error
 * 
 * @note This function should be called during initialization before
 * any SPI transfers start, as it's not fully thread-safe. Multiple
 * concurrent binds or binding while transfers are in progress could
 * lead to race conditions.
 */
int spi_bind(unsigned char type, int rxq_size)
{
    /* Use default queue size if requested size is invalid */
    if (rxq_size <= 0) {
        rxq_size = SPI_RXQ_LEN;
    }
    
    if (!xfer_engine.inited) {
        printf("SPI transaction is NOT initialized!\r\n");
        return -1;
    }
    
    if (type >= SPI_MSG_CTRL_TRAFFIC_TYPE_MAX) {
        printf("Invalid traffic type: %d, max allowed: %d\r\n", 
               type, SPI_MSG_CTRL_TRAFFIC_TYPE_MAX - 1);
        return -2;
    }
    
    /* Check if this type is already bound */
    if (xfer_engine.rxq_bound & (1 << type)) {
        printf("Traffic type %d is already bound\r\n", type);
        return -3;
    }
    
    /* Create a new queue for this type with specified size */
    xfer_engine.rxq[type] = xQueueCreate(rxq_size, sizeof(void *));
    if (!xfer_engine.rxq[type]) {
        printf("Failed to create queue for type %d\r\n", type);
        return -4;
    }
    
    /* Mark this type as bound */
    xfer_engine.rxq_bound |= (1 << type);
    return 0;
}

int spi_get_stats(struct spi_stat *stat)
{
	if (!stat)
		return -1;

	*stat = xfer_engine.stat;
	return 0;
}

int spi_on_txn_data_ready(void)
{
	spi_trace(SPI_TP_SLAVE_TXN_RDY, "slave txn/data ready\r\n");
	if (xPortIsInsideInterrupt()) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		int ret = xEventGroupSetBitsFromISR(xfer_engine.event, SPI_EVT_TXN_RDY, &xHigherPriorityTaskWoken);
		if (ret != pdPASS) {
			printf("event bitset %d error:%d\r\n", SPI_EVT_TXN_RDY, ret);
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	} else {
		xEventGroupSetBits(xfer_engine.event, SPI_EVT_TXN_RDY);
	}
	return 0;
}

int spi_on_header_ack(void)
{
	spi_trace(SPI_TP_HDR_ACKED, "slave header ack\r\n");
	if (xPortIsInsideInterrupt()) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		int ret = xEventGroupSetBitsFromISR(xfer_engine.event, SPI_EVT_HDR_ACKED, &xHigherPriorityTaskWoken);
        if (ret != pdPASS) {
			printf("event bitset %d error:%d\r\n", SPI_EVT_HDR_ACKED, ret);
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	} else {
		xEventGroupSetBits(xfer_engine.event, SPI_EVT_HDR_ACKED);
	}
	return 0;
}

static void spi_on_transaction_complete(void)
{
	spi_trace(SPI_TP_NONE, "hw txn done\r\n");
	if (xPortIsInsideInterrupt()) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		int ret = xEventGroupSetBitsFromISR(xfer_engine.event, SPI_EVT_HW_XFER_DONE, &xHigherPriorityTaskWoken);
		if (ret != pdPASS) {
			printf("event bitset %d error:%d\r\n", SPI_EVT_HW_XFER_DONE, ret);
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	} else {
		xEventGroupSetBits(xfer_engine.event, SPI_EVT_HW_XFER_DONE);
	}
}

static const char *spi_state_str[] = {
	[SPI_XFER_STATE_IDLE] = "Idle",
	[SPI_XFER_STATE_FIRST_PART] = "First Part Transaction",
	[SPI_XFER_STATE_SECOND_PART] = "Second Part Transaction",
	[SPI_XFER_STATE_TXN_DONE] = "Transfer Complete",
};

void spi_dump(void)
{
	EventBits_t bits;
	GPIO_PinState pin_state;

	if (!xfer_engine.inited) {
		printf("spi transaction is NOT initialized!\r\n");
		return;
	}

	printf("Master transfer state %s\r\n", spi_state_str[xfer_engine.state]);

	bits = xEventGroupGetBits(xfer_engine.event);
	printf("SPI pending events %lu ", bits);
	if (bits & SPI_EVT_TXN_RDY)
		puts(", TXN Ready");
	if (bits & SPI_EVT_TXN_PENDING)
		puts(", TXN Pending");
	if (bits & SPI_EVT_HW_XFER_DONE)
		puts(", Hardware Xfer done");
	puts("\r\n");

	pin_state = HAL_GPIO_ReadPin(SPI_SLAVE_DATA_RDY_GPIO_Port, SPI_SLAVE_DATA_RDY_Pin);
	printf("Slave data ready pin %s\r\n", pin_state == GPIO_PIN_SET ? "High" : "Low");

	spi_show_stat(&xfer_engine.stat);

	printf("Number of queue items, TX %lu\r\n",
		uxQueueMessagesWaiting(xfer_engine.txq));

	for (int i = 0; i < SPI_MSG_CTRL_TRAFFIC_TYPE_MAX; i++) {
        if (xfer_engine.rxq_bound & (1 << i)) {
            printf("  RX type %d: %lu items\r\n", i, 
                   uxQueueMessagesWaiting(xfer_engine.rxq[i]));
        }
    }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	spi_on_transaction_complete();
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	spi_on_transaction_complete();
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	spi_on_transaction_complete();
}
