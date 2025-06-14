#ifndef _QCC74x_MTIMER_H
#define _QCC74x_MTIMER_H

#include "stdint.h"
#include "stdio.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup MTIMER
  * @{
  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Config mtimer interrupt.
 *
 * @param [in] ticks ticks to invoke interrupt.
 * @param [in] interruptfun interrupt callback
 */
void qcc74x_mtimer_config(uint64_t ticks, void (*interruptfun)(void));

/**
 * @brief Get mtimer current frequence.
 *
 * @return frequence
 */
uint32_t qcc74x_mtimer_get_freq(void);

/**
 * @brief Mtimer delay with ms.
 *
 * @param [in] time delay time
 */
void qcc74x_mtimer_delay_ms(uint32_t time);

/**
 * @brief Mtimer delay with us.
 *
 * @param [in] time delay time
 */
void qcc74x_mtimer_delay_us(uint32_t time);

/**
 * @brief Get current mtimer time with us.
 *
 * @return time with us
 */
uint64_t qcc74x_mtimer_get_time_us(void);

/**
 * @brief Get current mtimer time with ms.
 *
 * @return time with ms
 */
uint64_t qcc74x_mtimer_get_time_ms(void);

#if defined(QCC74x_undef)
/**
 * @brief Set the value of mtimer.
 *
 * @param [in] val value of mtimer
 */
void qcc74x_mtimer_set_val(uint64_t val);
#endif

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