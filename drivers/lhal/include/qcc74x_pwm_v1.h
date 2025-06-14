#ifndef _QCC74x_PWM_V1_H
#define _QCC74x_PWM_V1_H

#include "qcc74x_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup PWM_V1
  * @{
  */

/** @defgroup PWM_CHANNEL pwm channel definition
  * @{
  */
#define PWM_CH0       0
#define PWM_CH1       1
#define PWM_CH2       2
#define PWM_CH3       3
#define PWM_CH4       4
#if defined(QCC74x_undef)
#define PWM_V1_CH_MAX 1
#else
#define PWM_V1_CH_MAX 5
#endif
/**
  * @}
  */

/** @defgroup PWM_INTSTS pwm interrupt status definition
  * @{
  */
#define PWM_INTSTS_REPT_CH0 (1 << 0)
#define PWM_INTSTS_REPT_CH1 (1 << 1)
#define PWM_INTSTS_REPT_CH2 (1 << 2)
#define PWM_INTSTS_REPT_CH3 (1 << 3)
#define PWM_INTSTS_REPT_CH4 (1 << 4)
/**
  * @}
  */

/** @defgroup PWM_INTCLR pwm interrupt clear definition
  * @{
  */
#define PWM_INTCLR_REPT_CH0 (1 << 8)
#define PWM_INTCLR_REPT_CH1 (1 << 9)
#define PWM_INTCLR_REPT_CH2 (1 << 10)
#define PWM_INTCLR_REPT_CH3 (1 << 11)
#define PWM_INTCLR_REPT_CH4 (1 << 12)
/**
  * @}
  */

/** @defgroup PWM_CMD pwm feature control cmd definition
  * @{
  */
#define PWM_CMD_SET_STOP_MODE      (0x01)
#define PWM_CMD_SET_OUT_INVERT     (0x02)
#define PWM_CMD_SET_SW_MODE        (0x03)
#define PWM_CMD_SET_SW_FORCE_VALUE (0x04)
#define PWM_CMD_SET_REPT_COUNT     (0x05)
/**
  * @}
  */

/** @defgroup PWM_STOP_MODE pwm stop mode definition
  * @{
  */
#define PWM_STOP_MODE_ABRUPT   0
#define PWM_STOP_MODE_GRACEFUL 1
/**
  * @}
  */

// clang-format off
#define IS_PWM_CLK_SOURCE(type)   (((type) == QCC74x_SYSTEM_PBCLK) || \
                                  ((type) == QCC74x_SYSTEM_XCLK) || \
                                  ((type) == QCC74x_SYSTEM_32K_CLK))

#define IS_PWM_CLK_DIV(type)   ((type) >= 1)

#define IS_PWM_PERIOD(type)   ((type) >= 2)

// clang-format on

/**
 * @brief PWM configuration structure
 *
 * @param clk_source PWM clock source, use @ref QCC74x_SYSTEM_CLOCK
 * @param clk_div    PWM clock dividor, should be in 1~65535
 * @param period     PWM period count, should be in 2~65535
 */
struct qcc74x_pwm_v1_channel_config_s {
    uint8_t clk_source;
    uint16_t clk_div;
    uint16_t period;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize pwm channel.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] config pointer to save pwm channel config
 */
void qcc74x_pwm_v1_channel_init(struct qcc74x_device_s *dev, uint8_t ch, const struct qcc74x_pwm_v1_channel_config_s *config);

/**
 * @brief Deinitialize pwm channel.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void qcc74x_pwm_v1_channel_deinit(struct qcc74x_device_s *dev, uint8_t ch);

/**
 * @brief Start pwm channel output.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void qcc74x_pwm_v1_start(struct qcc74x_device_s *dev, uint8_t ch);

/**
 * @brief Stop pwm channel output.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void qcc74x_pwm_v1_stop(struct qcc74x_device_s *dev, uint8_t ch);

/**
 * @brief Set pwm channel period to change pwm frequence. Frequcence(hz) = pwm source clock /div/period.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] period pwm period
 */
void qcc74x_pwm_v1_set_period(struct qcc74x_device_s *dev, uint8_t ch, uint16_t period);

/**
 * @brief Set pwm dutycycle. Dutycycle(%) = (high_threhold - low_threhold)/period * 100%.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] low_threhold pwm low threhold
 * @param [in] high_threhold pwm high threhold
 */
void qcc74x_pwm_v1_channel_set_threshold(struct qcc74x_device_s *dev, uint8_t ch, uint16_t low_threhold, uint16_t high_threhold);

/**
 * @brief Enable pwm interrupt.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] enable true means enable, otherwise disable.
 */
void qcc74x_pwm_v1_int_enable(struct qcc74x_device_s *dev, uint8_t ch, bool enable);

/**
 * @brief Get pwm interrupt status.
 *
 * @param [in] dev device handle
 * @return interrupt status, use @ref PWM_INTSTS
 */
uint32_t qcc74x_pwm_v1_get_intstatus(struct qcc74x_device_s *dev);

/**
 * @brief Clear pwm interrupt status.
 *
 * @param [in] dev device handle
 * @param [in] int_clear clear value, use @ref PWM_INTCLR
 */
void qcc74x_pwm_v1_int_clear(struct qcc74x_device_s *dev, uint32_t int_clear);

/**
 * @brief
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] cmd feature command, use @ref PWM_CMD
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */
int qcc74x_pwm_v1_feature_control(struct qcc74x_device_s *dev, uint8_t ch, int cmd, size_t arg);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

/**
  * @}
  */

#endif