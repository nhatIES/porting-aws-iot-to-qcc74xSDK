#ifndef _QCC74x_DAC_H
#define _QCC74x_DAC_H

#include "qcc74x_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup DAC
  * @{
  */

/** @defgroup DAC_CLK_DIV dac clock div definition
  * @{
  */
#define DAC_CLK_DIV_16    0
#define DAC_CLK_DIV_32    1
#define DAC_CLK_DIV_64    3
#define DAC_CLK_DIV_1     4
/**
  * @}
  */

/** @defgroup DAC_CHANNEL dac channel select
  * @{
  */
#define DAC_CHANNEL_A     (1 << 0)
#define DAC_CHANNEL_B     (1 << 1)
/**
  * @}
  */

/** @defgroup DAC_VREF dac voltage reference select
 * 
  * @{
  */
/* output Voltage (0.2V~1.8V) = (1.8V-0.2V) * digital_val/x + 0.2V
 * x = 1024 (QCC74x_undef/QCC74x_undef/QCC74x_undef), x = 4096(QCC743)
*/

#define DAC_VREF_INTERNAL 0

/* output Voltage (0.1vref~0.9vref) = (0.9vref-0.1vref) * digital_val/x + 0.1vref 
 *
 * x = 1024 (QCC74x_undef/QCC74x_undef/QCC74x_undef), x = 4096(QCC743)
 * 
 * QCC74x_undef/QCC74x_undef/QCC74x_undef using GPIO7
 * QCC743/QCC744 using GPIO28
*/
#define DAC_VREF_EXTERNAL 1
/**
  * @}
  */

/** @defgroup DAC_DMA_FORMAT dac format in dma mode
 * 
  * @{
  */
#define DAC_DMA_FORMAT_0  /*!< {A0},{A1},{A2},... */
#define DAC_DMA_FORMAT_1  /*!< {B0,A0},{B1,A1},{B2,A2},... */
/**
  * @}
  */

// clang-format off
#define IS_DAC_CLK_DIV(type)   (((type) == DAC_CLK_DIV_16) || \
                                  ((type) == DAC_CLK_DIV_32) || \
                                  ((type) == DAC_CLK_DIV_64) || \
                                  ((type) == DAC_CLK_DIV_1))

// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize dac frequence. Dac clk = 512K/clk_div, source clock must be 512K
 *
 * @param [in] dev device handle
 * @param [in] frequence dac clock div, use @ref DAC_CLK_DIV
 */
void qcc74x_dac_init(struct qcc74x_device_s *dev, uint8_t clk_div);

/**
 * @brief Deinitialize dac.
 *
 * @param [in] dev device handle
 */
void qcc74x_dac_deinit(struct qcc74x_device_s *dev);

/**
 * @brief Enable dac tx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void qcc74x_dac_link_txdma(struct qcc74x_device_s *dev, bool enable);

/**
 * @brief Set dac format in dma mode.
 *
 * @param [in] dev device handle
 * @param [in] format format type
 */
void qcc74x_dac_set_dma_format(struct qcc74x_device_s *dev, uint8_t format);

/**
 * @brief Enable dac channel.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void qcc74x_dac_channel_enable(struct qcc74x_device_s *dev, uint8_t ch);

/**
 * @brief Disable dac channel.
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 */
void qcc74x_dac_channel_disable(struct qcc74x_device_s *dev, uint8_t ch);

/**
 * @brief Set dac output value
 *
 * @param [in] dev device handle
 * @param [in] ch channel number
 * @param [in] value output value
 */
void qcc74x_dac_set_value(struct qcc74x_device_s *dev, uint8_t ch, uint16_t value);

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