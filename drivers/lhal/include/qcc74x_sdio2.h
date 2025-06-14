#ifndef _QCC74x_SDIO2_H
#define _QCC74x_SDIO2_H

#include "qcc74x_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup SDIO2
  * @{
  */

/* SDIO2 buffer size */
#ifndef SDIO2_DEFAULT_SIZE_MAX
#define SDIO2_DEFAULT_SIZE_MAX (2 * 1024)
#endif

#ifndef SDIO2_MAX_PORT_NUM
#define SDIO2_MAX_PORT_NUM 16
#endif

#ifndef SDIO2_SIZE_CONSULT_MULTIPLE
#define SDIO2_SIZE_CONSULT_MULTIPLE (64)
#endif

#define SDIO2_BYTE_MOD_SIZE_MAX (512)

#if (SDIO2_MAX_PORT_NUM & (SDIO2_MAX_PORT_NUM - 1) != 0)
#error "sdio2 port num error, must be 2^n"
#else
#define SDIO2_MAX_PORT_MASK (SDIO2_MAX_PORT_NUM - 1)
#endif

/* support sdio2 soft reset */
#if defined(QCC743) || defined(QCC74x_undef)
#define SDIO2_SOFT_RST_INT_SUP (1)
#define SDIO2_SOFT_RST_IRQ_NUM (19)
#endif

/** @defgroup SDIO2_STA_FLAG sdio system status and mode type.
  * @{
  */
#define SDIO2_STA_FLAG_NOT_SDIO_BOOT       (1 << 7)
#define SDIO2_STA_FLAG_APP_RUN             (1 << 6)
#define SDIO2_STA_FLAG_RD_LEN_COMPRESS_SUP (1 << 5)
/**
  * @}
  */

/** @defgroup SDIO2_HOST_INT_EVENT sdio2 card2host event type.
  * @{
  */
#define SDIO2_HOST_INT_EVENT_DNLD_RDY      (1 << 0)
#define SDIO2_HOST_INT_EVENT_UPLD_RDY      (1 << 1)
#define SDIO2_HOST_INT_EVENT_CIS_RDY       (1 << 2)
#define SDIO2_HOST_INT_EVENT_IO_RDY        (1 << 3)
/**
  * @}
  */

/** @defgroup SDIO2_IRQ_EVENT sdio2 irq callback event type.
  * @{
  */
#if defined(SDIO2_SOFT_RST_INT_SUP)
#define SDIO2_IRQ_EVENT_SOFT_RESET (1) /* soft reset  */
#endif
#define SDIO2_IRQ_EVENT_DNLD_CPL           (2) /* Dnld complete  */
#define SDIO2_IRQ_EVENT_UPLD_CPL           (3) /* Upld complete  */

#define SDIO2_IRQ_EVENT_ERR_CRC            (4) /* CRC error  */
#define SDIO2_IRQ_EVENT_ERR_ABORT          (5) /* transfer abort error */
#define SDIO2_IRQ_EVENT_ERR_UNKNOW         (6) /* other error */
/**
  * @}
  */

/** @defgroup SDIO2_CMD sdio2 feature_control cmd.
  * @{
  */
#define SDIO2_CMD_GET_BUS_WIDTH            (1) /* get bus width */
#define SDIO2_CMD_GET_FUNC_HOST_READY      (2) /* get func ready sta */
#define SDIO2_CMD_GET_FUNC_BLK_SIZE        (3) /* get func block size */
#define SDIO2_CMD_GET_DNLD_MAX_SIZE        (4) /* get func dnld max size */
#define SDIO2_CMD_GET_UPLD_MAX_SIZE        (5) /* get func upld max size */
#define SDIO2_CMD_GET_DNLD_QUEUE_WAIT_NUM  (6) /*  */
#define SDIO2_CMD_GET_DNLD_QUEUE_AVAILABLE (7) /*  */
#define SDIO2_CMD_GET_UPLD_QUEUE_WAIT_NUM  (8) /*  */
#define SDIO2_CMD_GET_UPLD_QUEUE_AVAILABLE (9) /*  */
/**
  * @}
  */

/* trans desc */
typedef struct
{
    uint16_t buff_len;
    uint16_t data_len;
    void *buff;
    void *user_arg;
} qcc74x_sdio2_trans_desc_t;

typedef void (*qcc74x_sdio2_irq_cb_t)(void *arg, uint32_t irq_event, qcc74x_sdio2_trans_desc_t *trans_desc);

#ifdef __cplusplus
extern "C" {
#endif

/* initialization */
int qcc74x_sdio2_init(struct qcc74x_device_s *dev, uint32_t dnld_size_max);
int qcc74x_sdio2_deinit(struct qcc74x_device_s *dev);

/* attach dnld/upld buff */
int qcc74x_sdio2_dnld_port_push(struct qcc74x_device_s *dev, qcc74x_sdio2_trans_desc_t *trans_desc);
int qcc74x_sdio2_upld_port_push(struct qcc74x_device_s *dev, qcc74x_sdio2_trans_desc_t *trans_desc);

/* pop dnld/upld queue, can only be used after reset, and before reinit */
int qcc74x_sdio2_dnld_port_pop(struct qcc74x_device_s *dev, qcc74x_sdio2_trans_desc_t *trans_desc);
int qcc74x_sdio2_upld_port_pop(struct qcc74x_device_s *dev, qcc74x_sdio2_trans_desc_t *trans_desc);

/* feature control */
int qcc74x_sdio2_feature_control(struct qcc74x_device_s *dev, int cmd, uintptr_t arg);

/* isr callback attach */
int qcc74x_sdio2_irq_attach(struct qcc74x_device_s *dev, qcc74x_sdio2_irq_cb_t irq_event_cb, void *arg);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

/**
  * @}
  */

#endif /* _QCC74x_SDIO2_H */
