/*
 * spi.h
 *
 *  Created on: Nov 6, 2024
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include <stdint.h>

#define SPI_MSG_F_TRUNCATED	0x1

#define SPI_MSG_CTRL_TRAFFIC_TYPE		0x1
#define SPI_MSG_CTRL_TRAFFIC_TYPE_LEN	1
#define SPI_MSG_CTRL_TRAFFIC_AT_CMD		0
#define SPI_MSG_CTRL_TRAFFIC_NETWORK	1
#define SPI_MSG_CTRL_TRAFFIC_TYPE_MAX   2

struct spi_msg_control {
	/* Ref SPI_MSG_CTRL_xxx */
	uint8_t type;
	/* Length of the following control data. */
	uint8_t len;
	void *val;
};

#define SPI_MSG_OP_DATA        0
#define SPI_MSG_OP_BUFFER      1
#define SPI_MSG_OP_BUFFER_PTR  2

struct spi_msg {
	union {
		/* For spi_write and spi_read. */
		struct {
			void *data;
			unsigned int data_len;
		};
		/* For spi_write_buffer. */
		struct spi_buffer *buffer;
		/* For spi_read_buffer */
		struct spi_buffer **buffer_ptr;
	};
	struct spi_msg_control *ctrl;
	unsigned int flags;
	unsigned char op_type;
};

struct spi_stat {
	unsigned long tx_pkts;
	unsigned long tx_bytes;
	unsigned long rx_pkts;
	unsigned long rx_bytes;
	unsigned long rx_drop;
	unsigned long io_err;
	unsigned long hdr_err;
	unsigned long wait_txn_timeouts;
	unsigned long wait_msg_xfer_timeouts;
	unsigned long wait_hdr_ack_timeouts;
	unsigned long mem_err;
	unsigned long rx_stall;
};

#define SPI_MSG_CONTROL_INIT(c, t, l, v)	do {	\
	struct spi_msg_control *_c = &(c);				\
	_c->type = t;									\
	_c->len = l;									\
	_c->val = v;									\
} while (0)

#define SPI_MSG_INIT(m, t, c, f)		do {	\
	struct spi_msg *_m = &(m);					\
	_m->op_type = t;							\
	_m->ctrl = c;								\
	_m->flags = f;								\
} while (0)

struct spi_buffer {
	void *data;
	/* Length of the data. */
	unsigned int len;
	/* Capacity of the buffer, >= len. */
	unsigned int cap;
	unsigned int flags;
	/* Control block for private data. */
	unsigned char cb[16];
};

int spi_transaction_init(void);

struct spi_buffer *spi_buffer_alloc(unsigned int size, unsigned int reserve);

struct spi_buffer *spi_tx_buffer_alloc(unsigned int size);

void spi_buffer_free(struct spi_buffer *buf);

static inline void *spi_buffer_data(struct spi_buffer *buf)
{
	return buf->data;
}

static inline unsigned int spi_buffer_len(struct spi_buffer *buf)
{
	return buf->len;
}

int spi_bind(unsigned char type, int rxq_size);

int spi_read(struct spi_msg *msg, int timeout_ms);

int spi_write(struct spi_msg *msg, int timeout_ms);

void spi_show_throuput_enable(int en);

int spi_on_transaction_ready(void);

int spi_on_txn_data_ready(void);

int spi_on_header_ack(void);

void spi_dump(void);

int spi_get_stats(struct spi_stat *stat);

#endif /* INC_SPI_H_ */
