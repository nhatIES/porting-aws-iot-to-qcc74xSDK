#ifndef _QCC74x_FLASH_SECREG_PORT_H
#define _QCC74x_FLASH_SECREG_PORT_H

#include <stdint.h>
#include <stdbool.h>
#include "qcc74x_flash.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/** @defgroup FLASH_SECREG_API flash secreg api definition
  * @{
  */
#define QCC74x_FLASH_SECREG_API_TYPE_GENERAL 0U
#define QCC74x_FLASH_SECREG_API_TYPE_ISSI    1U
#define QCC74x_FLASH_SECREG_API_TYPE_MXIC    2U
/**
  * @}
  */

#if defined(QCC74x_undef) || defined(QCC74x_undef)
#define QCC74x_SF_CTRL_BUF_BASE ((uint32_t)0x4000B700)
#elif defined(QCC74x_undef)
#define QCC74x_SF_CTRL_BUF_BASE ((uint32_t)0x4000B600)
#elif defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC743) || defined(QCC74x_undef)
#define QCC74x_SF_CTRL_BUF_BASE ((uint32_t)0x2000B600)
#elif defined(QCC74x_undef) || defined(QCC74x_undef)
#define QCC74x_SF_CTRL_BUF_BASE ((uint32_t)0x20082600)
#endif

struct flash_secreg_api {
    int (*read)(const spi_flash_cfg_type *flash_cfg, uint32_t address, void *data, uint32_t len);
    int (*write)(const spi_flash_cfg_type *flash_cfg, uint32_t address, const void *data, uint32_t len);
    int (*erase)(const spi_flash_cfg_type *flash_cfg, uint32_t address);
    int (*get_lock)(const qcc74x_flash_secreg_param_t *param, uint8_t *lb);
    int (*set_lock)(const spi_flash_cfg_type *flash_cfg, const qcc74x_flash_secreg_param_t *param, uint8_t lb);
};

extern const struct flash_secreg_api flash_secreg_apis[];

#endif
