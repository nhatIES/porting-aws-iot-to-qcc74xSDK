#ifndef _QCC74x_L1C_H
#define _QCC74x_L1C_H

#include "stdint.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup L1C
  * @{
  */

#if (defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)) && !defined(CPU_LP)
#if ((defined(QCC74x_undef) || defined(QCC74x_undef)) && defined(CPU_D0))
#define QCC74x_CACHE_LINE_SIZE 64
#else
#define QCC74x_CACHE_LINE_SIZE 32
#endif
#endif

/**
 * @brief
 *
 */
void qcc74x_l1c_icache_enable(void);

/**
 * @brief
 *
 */
void qcc74x_l1c_icache_disable(void);

/**
 * @brief
 *
 */
void qcc74x_l1c_icache_invalid_all(void);

/**
 * @brief
 *
 */
void qcc74x_l1c_dcache_enable(void);

/**
 * @brief
 *
 */
void qcc74x_l1c_dcache_disable(void);

/**
 * @brief
 *
 */
void qcc74x_l1c_dcache_clean_all(void);

/**
 * @brief
 *
 */
void qcc74x_l1c_dcache_invalidate_all(void);

/**
 * @brief
 *
 */
void qcc74x_l1c_dcache_clean_invalidate_all(void);

/**
 * @brief
 *
 * @param [in] addr
 * @param [in] size
 */
void qcc74x_l1c_dcache_clean_range(void *addr, uint32_t size);

/**
 * @brief
 *
 * @param [in] addr
 * @param [in] size
 */
void qcc74x_l1c_dcache_invalidate_range(void *addr, uint32_t size);

/**
 * @brief
 *
 * @param [in] addr
 * @param [in] size
 */
void qcc74x_l1c_dcache_clean_invalidate_range(void *addr, uint32_t size);

void qcc74x_l1c_hit_count_get(uint32_t *hit_count_low, uint32_t *hit_count_high);
uint32_t qcc74x_l1c_miss_count_get(void);
void qcc74x_l1c_cache_write_set(uint8_t wt_en, uint8_t wb_en, uint8_t wa_en);

/**
  * @}
  */

/**
  * @}
  */

#endif