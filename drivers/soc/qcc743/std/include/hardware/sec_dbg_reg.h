#ifndef __SEC_DBG_REG_H__
#define __SEC_DBG_REG_H__

#include "qcc743.h"

/* 0x0 : sd_chip_id_low */
#define SEC_DBG_SD_CHIP_ID_LOW_OFFSET (0x0)
#define SEC_DBG_SD_CHIP_ID_LOW        SEC_DBG_SD_CHIP_ID_LOW
#define SEC_DBG_SD_CHIP_ID_LOW_POS    (0U)
#define SEC_DBG_SD_CHIP_ID_LOW_LEN    (32U)
#define SEC_DBG_SD_CHIP_ID_LOW_MSK    (((1U << SEC_DBG_SD_CHIP_ID_LOW_LEN) - 1) << SEC_DBG_SD_CHIP_ID_LOW_POS)
#define SEC_DBG_SD_CHIP_ID_LOW_UMSK   (~(((1U << SEC_DBG_SD_CHIP_ID_LOW_LEN) - 1) << SEC_DBG_SD_CHIP_ID_LOW_POS))

/* 0x4 : sd_chip_id_high */
#define SEC_DBG_SD_CHIP_ID_HIGH_OFFSET (0x4)
#define SEC_DBG_SD_CHIP_ID_HIGH        SEC_DBG_SD_CHIP_ID_HIGH
#define SEC_DBG_SD_CHIP_ID_HIGH_POS    (0U)
#define SEC_DBG_SD_CHIP_ID_HIGH_LEN    (32U)
#define SEC_DBG_SD_CHIP_ID_HIGH_MSK    (((1U << SEC_DBG_SD_CHIP_ID_HIGH_LEN) - 1) << SEC_DBG_SD_CHIP_ID_HIGH_POS)
#define SEC_DBG_SD_CHIP_ID_HIGH_UMSK   (~(((1U << SEC_DBG_SD_CHIP_ID_HIGH_LEN) - 1) << SEC_DBG_SD_CHIP_ID_HIGH_POS))

/* 0x8 : sd_dbg_pwd_low */
#define SEC_DBG_SD_DBG_PWD_LOW_OFFSET (0x8)
#define SEC_DBG_SD_DBG_PWD_LOW        SEC_DBG_SD_DBG_PWD_LOW
#define SEC_DBG_SD_DBG_PWD_LOW_POS    (0U)
#define SEC_DBG_SD_DBG_PWD_LOW_LEN    (32U)
#define SEC_DBG_SD_DBG_PWD_LOW_MSK    (((1U << SEC_DBG_SD_DBG_PWD_LOW_LEN) - 1) << SEC_DBG_SD_DBG_PWD_LOW_POS)
#define SEC_DBG_SD_DBG_PWD_LOW_UMSK   (~(((1U << SEC_DBG_SD_DBG_PWD_LOW_LEN) - 1) << SEC_DBG_SD_DBG_PWD_LOW_POS))

/* 0xC : sd_dbg_pwd_high */
#define SEC_DBG_SD_DBG_PWD_HIGH_OFFSET (0xC)
#define SEC_DBG_SD_DBG_PWD_HIGH        SEC_DBG_SD_DBG_PWD_HIGH
#define SEC_DBG_SD_DBG_PWD_HIGH_POS    (0U)
#define SEC_DBG_SD_DBG_PWD_HIGH_LEN    (32U)
#define SEC_DBG_SD_DBG_PWD_HIGH_MSK    (((1U << SEC_DBG_SD_DBG_PWD_HIGH_LEN) - 1) << SEC_DBG_SD_DBG_PWD_HIGH_POS)
#define SEC_DBG_SD_DBG_PWD_HIGH_UMSK   (~(((1U << SEC_DBG_SD_DBG_PWD_HIGH_LEN) - 1) << SEC_DBG_SD_DBG_PWD_HIGH_POS))

/* 0x10 : sd_dbg_pwd2_low */
#define SEC_DBG_SD_DBG_PWD2_LOW_OFFSET (0x10)
#define SEC_DBG_SD_DBG_PWD2_LOW        SEC_DBG_SD_DBG_PWD2_LOW
#define SEC_DBG_SD_DBG_PWD2_LOW_POS    (0U)
#define SEC_DBG_SD_DBG_PWD2_LOW_LEN    (32U)
#define SEC_DBG_SD_DBG_PWD2_LOW_MSK    (((1U << SEC_DBG_SD_DBG_PWD2_LOW_LEN) - 1) << SEC_DBG_SD_DBG_PWD2_LOW_POS)
#define SEC_DBG_SD_DBG_PWD2_LOW_UMSK   (~(((1U << SEC_DBG_SD_DBG_PWD2_LOW_LEN) - 1) << SEC_DBG_SD_DBG_PWD2_LOW_POS))

/* 0x14 : sd_dbg_pwd2_high */
#define SEC_DBG_SD_DBG_PWD2_HIGH_OFFSET (0x14)
#define SEC_DBG_SD_DBG_PWD2_HIGH        SEC_DBG_SD_DBG_PWD2_HIGH
#define SEC_DBG_SD_DBG_PWD2_HIGH_POS    (0U)
#define SEC_DBG_SD_DBG_PWD2_HIGH_LEN    (32U)
#define SEC_DBG_SD_DBG_PWD2_HIGH_MSK    (((1U << SEC_DBG_SD_DBG_PWD2_HIGH_LEN) - 1) << SEC_DBG_SD_DBG_PWD2_HIGH_POS)
#define SEC_DBG_SD_DBG_PWD2_HIGH_UMSK   (~(((1U << SEC_DBG_SD_DBG_PWD2_HIGH_LEN) - 1) << SEC_DBG_SD_DBG_PWD2_HIGH_POS))

/* 0x18 : sd_status */
#define SEC_DBG_SD_STATUS_OFFSET        (0x18)
#define SEC_DBG_SD_DBG_PWD_BUSY         SEC_DBG_SD_DBG_PWD_BUSY
#define SEC_DBG_SD_DBG_PWD_BUSY_POS     (0U)
#define SEC_DBG_SD_DBG_PWD_BUSY_LEN     (1U)
#define SEC_DBG_SD_DBG_PWD_BUSY_MSK     (((1U << SEC_DBG_SD_DBG_PWD_BUSY_LEN) - 1) << SEC_DBG_SD_DBG_PWD_BUSY_POS)
#define SEC_DBG_SD_DBG_PWD_BUSY_UMSK    (~(((1U << SEC_DBG_SD_DBG_PWD_BUSY_LEN) - 1) << SEC_DBG_SD_DBG_PWD_BUSY_POS))
#define SEC_DBG_SD_DBG_PWD_TRIG         SEC_DBG_SD_DBG_PWD_TRIG
#define SEC_DBG_SD_DBG_PWD_TRIG_POS     (1U)
#define SEC_DBG_SD_DBG_PWD_TRIG_LEN     (1U)
#define SEC_DBG_SD_DBG_PWD_TRIG_MSK     (((1U << SEC_DBG_SD_DBG_PWD_TRIG_LEN) - 1) << SEC_DBG_SD_DBG_PWD_TRIG_POS)
#define SEC_DBG_SD_DBG_PWD_TRIG_UMSK    (~(((1U << SEC_DBG_SD_DBG_PWD_TRIG_LEN) - 1) << SEC_DBG_SD_DBG_PWD_TRIG_POS))
#define SEC_DBG_SD_DBG_CCI_READ_EN      SEC_DBG_SD_DBG_CCI_READ_EN
#define SEC_DBG_SD_DBG_CCI_READ_EN_POS  (2U)
#define SEC_DBG_SD_DBG_CCI_READ_EN_LEN  (1U)
#define SEC_DBG_SD_DBG_CCI_READ_EN_MSK  (((1U << SEC_DBG_SD_DBG_CCI_READ_EN_LEN) - 1) << SEC_DBG_SD_DBG_CCI_READ_EN_POS)
#define SEC_DBG_SD_DBG_CCI_READ_EN_UMSK (~(((1U << SEC_DBG_SD_DBG_CCI_READ_EN_LEN) - 1) << SEC_DBG_SD_DBG_CCI_READ_EN_POS))
#define SEC_DBG_SD_DBG_CCI_CLK_SEL      SEC_DBG_SD_DBG_CCI_CLK_SEL
#define SEC_DBG_SD_DBG_CCI_CLK_SEL_POS  (3U)
#define SEC_DBG_SD_DBG_CCI_CLK_SEL_LEN  (1U)
#define SEC_DBG_SD_DBG_CCI_CLK_SEL_MSK  (((1U << SEC_DBG_SD_DBG_CCI_CLK_SEL_LEN) - 1) << SEC_DBG_SD_DBG_CCI_CLK_SEL_POS)
#define SEC_DBG_SD_DBG_CCI_CLK_SEL_UMSK (~(((1U << SEC_DBG_SD_DBG_CCI_CLK_SEL_LEN) - 1) << SEC_DBG_SD_DBG_CCI_CLK_SEL_POS))
#define SEC_DBG_SD_DBG_PWD_CNT          SEC_DBG_SD_DBG_PWD_CNT
#define SEC_DBG_SD_DBG_PWD_CNT_POS      (4U)
#define SEC_DBG_SD_DBG_PWD_CNT_LEN      (20U)
#define SEC_DBG_SD_DBG_PWD_CNT_MSK      (((1U << SEC_DBG_SD_DBG_PWD_CNT_LEN) - 1) << SEC_DBG_SD_DBG_PWD_CNT_POS)
#define SEC_DBG_SD_DBG_PWD_CNT_UMSK     (~(((1U << SEC_DBG_SD_DBG_PWD_CNT_LEN) - 1) << SEC_DBG_SD_DBG_PWD_CNT_POS))
#define SEC_DBG_SD_DBG_MODE             SEC_DBG_SD_DBG_MODE
#define SEC_DBG_SD_DBG_MODE_POS         (24U)
#define SEC_DBG_SD_DBG_MODE_LEN         (4U)
#define SEC_DBG_SD_DBG_MODE_MSK         (((1U << SEC_DBG_SD_DBG_MODE_LEN) - 1) << SEC_DBG_SD_DBG_MODE_POS)
#define SEC_DBG_SD_DBG_MODE_UMSK        (~(((1U << SEC_DBG_SD_DBG_MODE_LEN) - 1) << SEC_DBG_SD_DBG_MODE_POS))
#define SEC_DBG_SD_DBG_ENA              SEC_DBG_SD_DBG_ENA
#define SEC_DBG_SD_DBG_ENA_POS          (28U)
#define SEC_DBG_SD_DBG_ENA_LEN          (4U)
#define SEC_DBG_SD_DBG_ENA_MSK          (((1U << SEC_DBG_SD_DBG_ENA_LEN) - 1) << SEC_DBG_SD_DBG_ENA_POS)
#define SEC_DBG_SD_DBG_ENA_UMSK         (~(((1U << SEC_DBG_SD_DBG_ENA_LEN) - 1) << SEC_DBG_SD_DBG_ENA_POS))

/* 0x1C : sd_dbg_reserved */
#define SEC_DBG_SD_DBG_RESERVED_OFFSET (0x1C)
#define SEC_DBG_SD_DBG_RESERVED        SEC_DBG_SD_DBG_RESERVED
#define SEC_DBG_SD_DBG_RESERVED_POS    (0U)
#define SEC_DBG_SD_DBG_RESERVED_LEN    (32U)
#define SEC_DBG_SD_DBG_RESERVED_MSK    (((1U << SEC_DBG_SD_DBG_RESERVED_LEN) - 1) << SEC_DBG_SD_DBG_RESERVED_POS)
#define SEC_DBG_SD_DBG_RESERVED_UMSK   (~(((1U << SEC_DBG_SD_DBG_RESERVED_LEN) - 1) << SEC_DBG_SD_DBG_RESERVED_POS))

struct sec_dbg_reg {
    /* 0x0 : sd_chip_id_low */
    union {
        struct {
            uint32_t sd_chip_id_low : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } sd_chip_id_low;

    /* 0x4 : sd_chip_id_high */
    union {
        struct {
            uint32_t sd_chip_id_high : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } sd_chip_id_high;

    /* 0x8 : sd_dbg_pwd_low */
    union {
        struct {
            uint32_t sd_dbg_pwd_low : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } sd_dbg_pwd_low;

    /* 0xC : sd_dbg_pwd_high */
    union {
        struct {
            uint32_t sd_dbg_pwd_high : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } sd_dbg_pwd_high;

    /* 0x10 : sd_dbg_pwd2_low */
    union {
        struct {
            uint32_t sd_dbg_pwd2_low : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } sd_dbg_pwd2_low;

    /* 0x14 : sd_dbg_pwd2_high */
    union {
        struct {
            uint32_t sd_dbg_pwd2_high : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } sd_dbg_pwd2_high;

    /* 0x18 : sd_status */
    union {
        struct {
            uint32_t sd_dbg_pwd_busy    : 1;  /* [    0],          r,        0x0 */
            uint32_t sd_dbg_pwd_trig    : 1;  /* [    1],        r/w,        0x0 */
            uint32_t sd_dbg_cci_read_en : 1;  /* [    2],        r/w,        0x0 */
            uint32_t sd_dbg_cci_clk_sel : 1;  /* [    3],        r/w,        0x0 */
            uint32_t sd_dbg_pwd_cnt     : 20; /* [23: 4],          r,        0x0 */
            uint32_t sd_dbg_mode        : 4;  /* [27:24],          r,        0x0 */
            uint32_t sd_dbg_ena         : 4;  /* [31:28],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } sd_status;

    /* 0x1C : sd_dbg_reserved */
    union {
        struct {
            uint32_t sd_dbg_reserved : 32; /* [31: 0],        r/w,     0xffff */
        } BF;
        uint32_t WORD;
    } sd_dbg_reserved;
};

typedef volatile struct sec_dbg_reg sec_dbg_reg_t;

#endif /* __SEC_DBG_REG_H__ */
