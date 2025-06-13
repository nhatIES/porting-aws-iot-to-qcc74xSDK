#ifndef _QCC74x_SEC_GMAC_H
#define _QCC74x_SEC_GMAC_H

#include "qcc74x_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup SEC_GMAC
  * @{
  */

/** @defgroup GMAC_MODE GMAC mode definition
  * @{
  */

/**
  * @}
  */

/** @defgroup GMAC_LINK_KEYBITS GMAC link mode keybits definition
  * @{
  */

/**
  * @}
  */

/**
 *  @brief SEC_ENG GMAC link config structure type definition
 */
struct qcc74x_sec_gmac_link_s {
    uint32_t                : 9;  /*!< [8:0]reserved */
    uint32_t gmac_int_clear : 1;  /*!< [9]Clear interrupt */
    uint32_t gmac_int_set   : 1;  /*!< [10]Set interrupt */
    uint32_t                : 5;  /*!< [15:11]reserved */
    uint32_t gmac_msg_len   : 16; /*!< [31:16]Number of 128-bit block */
    uint32_t gmac_src_addr;       /*!< Message source address */
    uint32_t gmac_key0;           /*!< GMAC key */
    uint32_t gmac_key1;           /*!< GMAC key */
    uint32_t gmac_key2;           /*!< GMAC key */
    uint32_t gmac_key3;           /*!< GMAC key */
    uint32_t result[4];           /*!< Result of GMAC */
} __attribute__((aligned(4)));

#ifdef __cplusplus
extern "C" {
#endif

void qcc74x_sec_gmac_le_enable(struct qcc74x_device_s *dev);
void qcc74x_sec_gmac_link_enable(struct qcc74x_device_s *dev, uint8_t enable);
int qcc74x_sec_gmac_link_work(struct qcc74x_device_s *dev, uint32_t addr, const uint8_t *in, uint32_t len, uint8_t *out);
void qcc74x_group0_request_gmac_access(struct qcc74x_device_s *dev);
void qcc74x_group0_release_gmac_access(struct qcc74x_device_s *dev);

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