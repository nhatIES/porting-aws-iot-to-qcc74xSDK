#ifndef _QCC74x_KYS_H
#define _QCC74x_KYS_H

#include "qcc74x_core.h"

struct qcc74x_kys_config_s {
    uint8_t col;           /* Col of keyboard,max:8 */
    uint8_t row;           /* Row of keyboard,max:8 */
    uint8_t deglitch_en;   /* Disable deglitch function */
    uint8_t deglitch_cnt;  /* Deglitch count */
    uint8_t idle_duration; /* Idle duration between column scans */
    uint8_t ghost_en;      /* Disable ghost key event detection */
};

/* keyscan interrupt enable define */
#if defined(QCC74x_undef)
#define KEYSCAN_INT_EN (0x1 << 0)
#else
#define KEYSCAN_INT_EN_DONE          (0x1 << 7)
#define KEYSCAN_INT_EN_FIFOFULL      (0x1 << 8)
#define KEYSCAN_INT_EN_FIFOHALF      (0x1 << 9)
#define KEYSCAN_INT_EN_FIFOQUARTER   (0x1 << 10)
#define KEYSCAN_INT_EN_FIFO_NONEMPTY (0x1 << 11)
#define KEYSCAN_INT_EN_GHOST         (0x1 << 12)
#endif

/* keyscan interrupt clear */
#if defined(QCC74x_undef)
#define KEYSCAN_INT_CLR_DONE  (0x1 << 7)
#define KEYSCAN_INT_CLR_FIFO  (0x1 << 8)
#define KEYSCAN_INT_CLR_GHOST (0x1 << 12)
#endif

#if defined(QCC74x_undef)
/* keyscan keycode status and clear */
#define KEYSCAN_STS_KEYCODE0 (0x1 << 0)
#define KEYSCAN_STS_KEYCODE1 (0x1 << 1)
#define KEYSCAN_STS_KEYCODE2 (0x1 << 2)
#define KEYSCAN_STS_KEYCODE3 (0x1 << 3)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void qcc74x_kys_init(struct qcc74x_device_s *dev, const struct qcc74x_kys_config_s *config);
void qcc74x_kys_enable(struct qcc74x_device_s *dev);
void qcc74x_kys_disable(struct qcc74x_device_s *dev);
void qcc74x_kys_int_enable(struct qcc74x_device_s *dev, uint32_t flag, bool enable);
void qcc74x_kys_int_clear(struct qcc74x_device_s *dev, uint32_t flag);
uint32_t qcc74x_kys_get_int_status(struct qcc74x_device_s *dev);
#if defined(QCC74x_undef)
void qcc74x_kys_get_fifo_info(struct qcc74x_device_s *dev, uint8_t *fifo_head, uint8_t *fifo_tail, uint8_t *fifo_valid_cnt);
#endif
uint8_t qcc74x_kys_read_keyvalue(struct qcc74x_device_s *dev, uint8_t index);

#ifdef __cplusplus
}
#endif

#endif
