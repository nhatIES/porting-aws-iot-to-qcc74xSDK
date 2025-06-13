#ifndef _QCC74x_EMAC_H
#define _QCC74x_EMAC_H

#include "qcc74x_core.h"

#if defined(QCC74x_undef) || defined(QCC74x_undef)
#define EMAC_SPEED_10M_SUPPORT (1)
#else
#define EMAC_SPEED_10M_SUPPORT (0)
#endif

#ifndef EMAC_TX_BD_BUM_MAX
#define EMAC_TX_BD_BUM_MAX (64)
#endif

#ifndef EMAC_RX_BD_BUM_MAX
#define EMAC_RX_BD_BUM_MAX (64)
#endif

#if (EMAC_TX_BD_BUM_MAX & (EMAC_TX_BD_BUM_MAX - 1) != 0) || EMAC_TX_BD_BUM_MAX > 64
#error "emac tx bd num error, must be 2^n and <= 64"
#else
#define EMAC_TX_BD_BUM_MASK (EMAC_TX_BD_BUM_MAX - 1)
#endif

#if (EMAC_RX_BD_BUM_MAX & (EMAC_RX_BD_BUM_MAX - 1) != 0) || EMAC_RX_BD_BUM_MAX > 64
#error "emac tx bd num error, must be 2^n and <= 64"
#else
#define EMAC_RX_BD_BUM_MASK (EMAC_RX_BD_BUM_MAX - 1)
#endif

/* feature CMD */
#define EMAC_CMD_SET_TX_EN              (0)
#define EMAC_CMD_SET_TX_AUTO_PADDING    (1)
#define EMAC_CMD_SET_TX_CRC_FIELD_EN    (2)
#define EMAC_CMD_SET_TX_PREAMBLE        (3)
#define EMAC_CMD_SET_TX_GAP_CLK         (4)
#define EMAC_CMD_SET_TX_COLLISION       (5)
#define EMAC_CMD_SET_TX_MAXRET          (6)
#define EMAC_CMD_SET_RX_EN              (7)
#define EMAC_CMD_SET_RX_SMALL_FRAME     (8)
#define EMAC_CMD_SET_RX_HUGE_FRAME      (9)
#define EMAC_CMD_SET_RX_GAP_CHECK       (10)
#define EMAC_CMD_SET_RX_PROMISCUOUS     (11)
#define EMAC_CMD_SET_RX_BROADCASE       (12)
#define EMAC_CMD_SET_FULL_DUPLEX        (13)
#define EMAC_CMD_SET_SPEED_100M         (14)
#if (EMAC_SPEED_10M_SUPPORT)
#define EMAC_CMD_SET_SPEED_10M          (15)
#endif
#define EMAC_CMD_SET_MAC_RX_CLK_INVERT  (16)
#define EMAC_CMD_GET_TX_DB_AVAILABLE    (20)
#define EMAC_CMD_GET_RX_DB_AVAILABLE    (21)
#define EMAC_CMD_GET_TX_BD_PTR          (22)
#define EMAC_CMD_GET_RX_BD_PTR          (23)

/* irq callback event */
#define EMAC_IRQ_EVENT_RX_BUSY       (1)
#define EMAC_IRQ_EVENT_RX_FRAME      (2)
#define EMAC_IRQ_EVENT_RX_CTRL_FRAME (3)
#define EMAC_IRQ_EVENT_RX_ERR_FRAME  (4)
#define EMAC_IRQ_EVENT_TX_FRAME      (5)
#define EMAC_IRQ_EVENT_TX_ERR_FRAME  (6)

/* tx attribute flag */
#define EMAC_TX_FLAG_FRAGMENT        (1 << 0) /* This BD does not contain EoF and controller will proceed to read out the next BD */
#define EMAC_TX_FLAG_NO_INT          (1 << 1) /* No interrupt is generated after the transmission */
#define EMAC_TX_FLAG_NO_CRC          (1 << 2) /* CRC would not be attached to the end of the packet */
#define EMAC_TX_FLAG_NO_PAD          (1 << 3) /* No padding is appended to the end of the short packet */
/* tx done err status */
#define EMAC_TX_STA_ERR_COLLISION    (1 << 0) /* Late Collision */
#define EMAC_TX_STA_ERR_CS           (1 << 1) /* Carrier Sense Lost */
#define EMAC_TX_STA_ERR_RETRY_LIMIT  (1 << 2) /* Retransmission Limit*/
#define EMAC_TX_STA_ERR_FIFO         (1 << 3)

/* rx attribute flag */
#define EMAC_RX_FLAG_NO_INT          (1 << 1)
/* rx done err status */
#define EMAC_RX_STA_ERR_CRC          (1 << 0)
#define EMAC_RX_STA_ERR_COLLISION    (1 << 1)
#define EMAC_RX_STA_ERR_LONG_FRAME   (1 << 2)
#define EMAC_RX_STA_ERR_FIFO         (1 << 3)

/* Buffer hardware descriptor table:
 * |---------------------|-------------------|---------------------------|
 * |   Address field     |       Length      |         Attribute         |
 * |---------------------|-------------------|---------------------------|
 * |63                 32|31               16|15                       00|
 * |---------------------|-------------------|---------------------------|
 * |   32-bit address    |   16-bit length   | 16-bit control and status |
 * |---------------------|-------------------|---------------------------|
 *
*/
struct qcc74x_emac_hw_buff_desc_s {
    uint16_t attribute; /* The control and status field. */
    uint16_t length;    /* The length field. */
    uint32_t address;   /* The address field. */
};

struct qcc74x_emac_trans_desc_s {
    void *buff_addr;    /* buff address */
    uint16_t data_len;  /* data len */
    uint8_t attr_flag;  /* attribute flag */
    uint8_t err_status; /* err_status */
};

struct qcc74x_emac_config_s {
    uint8_t mac_addr[6];
    bool clk_internal_mode;
    uint8_t md_clk_div;
    uint16_t min_frame_len;
    uint16_t max_frame_len;
};

typedef void (*qcc74x_emac_irq_cb_t)(void *arg, uint32_t irq_event, struct qcc74x_emac_trans_desc_s *trans_desc);

#ifdef __cplusplus
extern "C" {
#endif

int qcc74x_emac_init(struct qcc74x_device_s *dev, const struct qcc74x_emac_config_s *config);
int qcc74x_emac_deinit(struct qcc74x_device_s *dev);

int qcc74x_emac_md_read(struct qcc74x_device_s *dev, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);
int qcc74x_emac_md_write(struct qcc74x_device_s *dev, uint8_t phy_addr, uint8_t reg_addr, uint16_t data);

int qcc74x_emac_bd_ctrl_clean(struct qcc74x_device_s *dev);
int qcc74x_emac_queue_tx_push(struct qcc74x_device_s *dev, struct qcc74x_emac_trans_desc_s *tx_desc);
int qcc74x_emac_queue_rx_push(struct qcc74x_device_s *dev, struct qcc74x_emac_trans_desc_s *rx_desc);

int qcc74x_emac_feature_control(struct qcc74x_device_s *dev, int cmd, size_t arg);

int qcc74x_emac_irq_attach(struct qcc74x_device_s *dev, qcc74x_emac_irq_cb_t irq_event_cb, void *arg);

#ifdef __cplusplus
}
#endif

#endif