#ifndef __QCC74x_PORT_BOOT2_H__
#define __QCC74x_PORT_BOOT2_H__

#include "qcc74x_efuse.h"
#include "qcc743_glb.h"
#include "qcc743_common.h"

#define QCC74x_TCM_BASE           QCC743_TCM_BASE
#define QCC74x_SYS_CLK_PLL        GLB_SYS_CLK_PLL160M
#define QCC74x_SFLASH_CLK         GLB_SFLASH_CLK_80M
#define HAL_PLL_CFG_MAGICCODE "PCFG"

#define HAL_BOOT2_PK_HASH_SIZE  256 / 8
#define HAL_BOOT2_IMG_HASH_SIZE 256 / 8
#define HAL_BOOT2_ECC_KEYXSIZE  256 / 8
#define HAL_BOOT2_ECC_KEYYSIZE  256 / 8
#define HAL_BOOT2_SIGN_MAXSIZE  (2048 / 8)
#define HAL_BOOT2_DEADBEEF_VAL  0xdeadbeef
#define HAL_BOOT2_CPU0_MAGIC    "BFNP"
#define HAL_BOOT2_CPU1_MAGIC    "BFAP"
#define HAL_BOOT2_CP_FLAG       0x02
#define HAL_BOOT2_MP_FLAG       0x01
#define HAL_BOOT2_SP_FLAG       0x00

#define HAL_BOOT2_SUPPORT_DECOMPRESS          1 /* 1 support decompress, 0 not support */
#define HAL_BOOT2_SUPPORT_USB_IAP             0 /* 1 support decompress, 0 not support */
#define HAL_BOOT2_SUPPORT_EFLASH_LOADER_RAM   0 /* 1 support decompress, 0 not support */
#define HAL_BOOT2_SUPPORT_EFLASH_LOADER_FLASH 0 /* 1 support decompress, 0 not support */
#define HAL_BOOT2_SUPPORT_SIGN_ENCRYPT        1 /* 1 support sign and encrypt, 0 not support */

#define HAL_BOOT2_CPU_GROUP_MAX     1
#define HAL_BOOT2_CPU_MAX           1
#define HAL_BOOT2_RAM_IMG_COUNT_MAX 2

#define HAL_BOOT2_FW_IMG_OFFSET_AFTER_HEADER 4 * 1024
#define HAL_BOOT2_MFG_START_REQUEST_OFFSET   8 * 1024

#define HAL_BOOT2_PSRAM_ID1_WINBOND_4MB  0x5f
#define HAL_BOOT2_PSRAM_ID2_WINBOND_32MB 0xe86
#define HAL_BOOT2_PSRAM_ID3_WINBOND_16MB 0xc96
#define HAL_BOOT2_PSRAM_ID4_WINBOND_8MB  0xc86

#define HAL_BOOT2_PSRAM_INFO_MASK (0x3000000)
#define HAL_BOOT2_PSRAM_INFO_POS  (24)

#define HAL_BOOT2_FLASH_XIP_BASE QCC743_FLASH_XIP_BASE

#define HAL_BOOT2_UINT32_BIT_LEN               (32)
#define HAL_BOOT2_UINT64_BIT_LEN               (64)
#define HAL_BOOT2_UINT96_BIT_LEN               (96)
#define HAL_BOOT2_UINT128_BIT_LEN              (128)

#define HAL_APP_NO_ENCRYPT                    0b0000 /*!< app no encrypt */
#define HAL_APP_ENCRYPT_SAME_AS_BOOT2         0b0001 /*!< app use the same AES key as boot2,see 0x00[3:0] */
#define HAL_APP_ENCRYPT_INDIVIDUAL_AES128     0b0010 /*!< app use its own AES-128 key */
#define HAL_APP_ENCRYPT_INDIVIDUAL_AES256     0b0100 /*!< app use its own AES-256key */
#define HAL_APP_ENCRYPT_INDIVIDUAL_AES128_XTS 0b1010 /*!< app use its own AES-128 key with XTS mode */

#define HAL_APP_NO_SIGN                       0b00   /*!< app no sign */
#define HAL_APP_SIGN_SAME_AS_BOOT2            0b01   /*!< app use the same sign key as boot2 */
#define HAL_APP_SIGN_INDIVIDUAL               0b10   /*!< app use its own sign key */

typedef enum {
    HAL_REBOOT_AS_BOOTPIN,     /*!< reboot as bootpin level */
    HAL_REBOOT_FROM_INTERFACE, /*!< reboot from interface, download mode */
    HAL_REBOOT_FROM_MEDIA,     /*!< reboot from media, running mode */
    HAL_REBOOT_MAX             /*!< reboot max value */
} hal_reboot_cfg_t;

struct __attribute__((packed, aligned(4))) boot_efuse_sw_cfg0_t {
    uint32_t bootrom_protect   : 1; /* ef_sw_usage_0 bit [0] */
    uint32_t uart_log_disable  : 1; /* ef_sw_usage_0 bit [1] */
    uint32_t boot_pin_cfg      : 1; /* ef_sw_usage_0 bit [2] */
    uint32_t mediaboot_disable : 1; /* ef_sw_usage_0 bit [3] */

    uint32_t uartboot_disable : 1; /* ef_sw_usage_0 bit [4] */
    uint32_t usbboot_enable   : 1; /* ef_sw_usage_0 bit [5] */
    uint32_t uart_log_reopen  : 1; /* ef_sw_usage_1 bit [6] */
    uint32_t sign_cfg         : 1; /* ef_sw_usage_0 bit [7] */

    uint32_t dcache_disable : 1; /* ef_sw_usage_0 bit [8] */
    uint32_t jtag_cfg       : 3; /* ef_sw_usage_0 bit [11:9] */

    uint32_t fix_key_sel : 1; /* ef_sw_usage_0 bit [12] */

    uint32_t sdh_en     : 1; /* ef_sw_usage_1 bit [13] */
    uint32_t sf_pin_cfg : 6; /* ef_sw_usage_0 bit [19:14] */

    uint32_t boot_pin_dly       : 2; /* ef_sw_usage_0 bit [21:20] */
    uint32_t power_trim_disable : 1; /* ef_sw_usage_0 bit [22] */
    uint32_t trim_enable        : 1; /* ef_sw_usage_0 bit [23] */

    uint32_t flash_power_delay : 2; /* ef_sw_usage_0 bit [25:24] */
    uint32_t boot_level_revert : 1; /* ef_sw_usage_0 bit [26] */
    uint32_t tz_boot           : 1; /* ef_sw_usage_0 bit [27] */

    uint32_t usb_desc_cfg         : 1; /* ef_sw_usage_0 bit [28] */
    uint32_t hbn_check_sign       : 1; /* ef_sw_usage_0 bit [29] */
    uint32_t keep_dbg_port_closed : 1; /* ef_sw_usage_0 bit [30] */
    uint32_t hbn_jump_disable     : 1; /* ef_sw_usage_0 bit [31] */
};

struct __attribute__((packed, aligned(4))) boot_efuse_sw_cfg1_t {
    uint32_t xtal_type  : 3; /* ef_sw_usage_1 bit [2:0] */
    uint32_t wifipll_pu : 1; /* ef_sw_usage_1 bit [3] */

    uint32_t aupll_pu        : 1; /* ef_sw_usage_1 bit [4] */
    uint32_t product_id      : 2; /* ef_sw_usage_1 bit [6:5] */
    uint32_t sdioboot_enable : 1; /* ef_sw_usage_1 bit [7] */

    uint32_t mcu_clk     : 3; /* ef_sw_usage_1 bit [10:8] */
    uint32_t mcu_clk_div : 1; /* ef_sw_usage_1 bit [11] */

    uint32_t mcu_pbclk_div       : 2; /* ef_sw_usage_1 bit [13:12] */
    uint32_t uart_download_cfg   : 2; /* ef_sw_usage_1 bit [15:14] */
    uint32_t pin_func_0_init     : 1; /* ef_sw_usage_1 bit [16] */
    uint32_t always_uart         : 1; /* ef_sw_usage_1 bit [17] */
    uint32_t abt_shake_hands_dis : 1; /* ef_sw_usage_1 bit [18] */
    uint32_t no_hd_boot_en       : 1; /* ef_sw_usage_1 bit [19] */

    uint32_t ocram_way_dis_cfg : 2; /* ef_sw_usage_1 bit [21:20] */
    uint32_t xtal_level_revert : 1; /* ef_sw_usage_1 bit [22] */
    uint32_t flash_clk_type    : 3; /* ef_sw_usage_1 bit [25:23] */
    uint32_t flash_clk_div     : 1; /* ef_sw_usage_1 bit [26] */
    uint32_t ldo18io_cfg_dis   : 1; /* ef_sw_usage_1 bit [27] */

    uint32_t bootlog_pin_cfg    : 1; /* ef_sw_usage_1 bit [28] */
    uint32_t abt_offset         : 1; /* ef_sw_usage_1 bit [29] */
    uint32_t boot_pull_cfg      : 1; /* ef_sw_usage_1 bit [30] */
    uint32_t usb_if_int_disable : 1; /* ef_sw_usage_1 bit [31] */
};

typedef struct
{
    uint8_t encrypted[HAL_BOOT2_CPU_GROUP_MAX];
    uint8_t sign[HAL_BOOT2_CPU_GROUP_MAX];
    uint8_t hbn_check_sign;
    uint8_t app_encrypt_type;
    uint8_t app_sign_type;
    uint8_t rsvd[1];
    uint8_t chip_id[8];
    uint8_t pk_hash_cpu[HAL_BOOT2_CPU_GROUP_MAX][HAL_BOOT2_PK_HASH_SIZE];
    uint8_t uart_download_cfg;
    uint8_t sf_pin_cfg;
    uint8_t keep_dbg_port_closed;
    uint8_t boot_pin_cfg;
    uint32_t psram_dqs_cfg;
    qcc74x_efuse_device_info_type dev_info;
} boot2_efuse_hw_config;

struct __attribute__((packed, aligned(4))) hal_flash_config {
    uint32_t magicCode; /*'FCFG'*/
    spi_flash_cfg_type cfg;
    uint32_t crc32;
};

struct __attribute__((packed, aligned(4))) hal_sys_clk_config {
    uint8_t xtal_type;
    uint8_t mcu_clk;
    uint8_t mcu_clk_div;
    uint8_t mcu_bclk_div;

    uint8_t mcu_pbclk_div;
    uint8_t emi_clk;
    uint8_t emi_clk_div;
    uint8_t flash_clk_type;

    uint8_t flash_clk_div;
    uint8_t wifipll_pu;
    uint8_t aupll_pu;
    uint8_t rsvd0;
};

typedef struct {
    uint32_t magiccode;
    struct hal_sys_clk_config cfg;
    uint32_t crc32;
} hal_pll_config;

struct __attribute__((packed, aligned(4))) hal_basic_cfg_t {
    uint32_t sign_type          : 2; /* [1: 0]   for sign */
    uint32_t encrypt_type       : 2; /* [3: 2]   for encrypt */
    uint32_t key_sel            : 2; /* [5: 4]   key slot */
    uint32_t xts_mode           : 1; /* [6]      for xts mode */
    uint32_t aes_region_lock    : 1; /* [7]      rsvd */
    uint32_t no_segment         : 1; /* [8]      no segment info */
    uint32_t boot2_enable       : 1; /* [9]      boot2 enable */
    uint32_t boot2_rollback     : 1; /* [10]     boot2 rollback */
    uint32_t cpu_master_id      : 4; /* [14: 11] master id */
    uint32_t notload_in_bootrom : 1; /* [15]     notload in bootrom */
    uint32_t crc_ignore         : 1; /* [16]     ignore crc */
    uint32_t hash_ignore        : 1; /* [17]     hash ignore */
    uint32_t power_on_mm        : 1; /* [18]     power on mm */
    uint32_t em_sel             : 3; /* [21: 19] em_sel */
    uint32_t cmds_en            : 1; /* [22]     command spliter enable */
    uint32_t cmds_wrap_mode     : 2; /* [24: 23] cmds wrap mode */
    uint32_t cmds_wrap_len      : 4; /* [28: 25] cmds wrap len */
    uint32_t icache_invalid     : 1; /* [29] icache invalid */
    uint32_t dcache_invalid     : 1; /* [30] dcache invalid */
    uint32_t fpga_halt_release  : 1; /* [31] FPGA halt release function */

    uint32_t group_image_offset; /* flash controller offset */
    uint32_t aes_region_len;     /* aes region length */

    uint32_t img_len_cnt; /* image length or segment count */
    uint32_t hash[8];     /* hash of the image */
};

struct __attribute__((packed, aligned(4))) hal_cpu_cfg_t {
    uint8_t config_enable;     /* coinfig this cpu */
    uint8_t halt_cpu;          /* halt this cpu */
    uint8_t cache_enable  : 1; /* cache setting */
    uint8_t cache_wa      : 1; /* cache setting */
    uint8_t cache_wb      : 1; /* cache setting */
    uint8_t cache_wt      : 1; /* cache setting */
    uint8_t cache_way_dis : 4; /* cache setting */
    uint8_t rsvd;

    uint32_t image_address_offset; /* image address on flash */
    uint32_t boot_entry;           /* entry point of the m0 image */
    uint32_t msp_val;              /* msp value */
};

struct __attribute__((packed, aligned(4))) hal_patch_cfg_t {
    uint32_t addr;
    uint32_t value;
};

struct __attribute__((packed, aligned(4))) hal_bootheader_t {
    uint32_t magiccode;
    uint32_t rivison;

    struct hal_flash_config flashCfg;
    hal_pll_config clkCfg;

    struct hal_basic_cfg_t basic_cfg;

    struct hal_cpu_cfg_t cpu_cfg[HAL_BOOT2_CPU_MAX];

    uint32_t boot2_pt_table_0; /* address of partition table 0 */
    uint32_t boot2_pt_table_1; /* address of partition table 1 */

    uint32_t flashCfgTableAddr; /* address of flashcfg table list */
    uint32_t flashCfgTableLen;  /* flashcfg table list len */

    struct hal_patch_cfg_t patch_on_read[3]; /* do patch when read flash */
    struct hal_patch_cfg_t patch_on_jump[3]; /* do patch when jump */

    uint32_t rsvd;

    uint32_t crc32;
};

typedef struct
{
    uint8_t img_valid;
    uint8_t pk_src;
    uint8_t rsvd[2];

    struct hal_basic_cfg_t basic_cfg;

    struct hal_cpu_cfg_t cpu_cfg[HAL_BOOT2_CPU_MAX];

    uint8_t aes_iv[16 + 4]; //iv in boot header

    uint8_t eckye_x[HAL_BOOT2_ECC_KEYXSIZE];  //ec key in boot header
    uint8_t eckey_y[HAL_BOOT2_ECC_KEYYSIZE];  //ec key in boot header
    uint8_t eckey_x2[HAL_BOOT2_ECC_KEYXSIZE]; //ec key in boot header
    uint8_t eckey_y2[HAL_BOOT2_ECC_KEYYSIZE]; //ec key in boot header

    uint8_t signature[HAL_BOOT2_SIGN_MAXSIZE];  //signature in boot header
    uint8_t signature2[HAL_BOOT2_SIGN_MAXSIZE]; //signature in boot header

} boot2_image_config;

extern boot2_efuse_hw_config g_efuse_cfg;
extern uint8_t g_ps_mode;
extern uint32_t g_user_hash_ignored;
extern struct device *dev_check_hash;

uint32_t hal_boot2_custom(void *custom_param);
uint32_t hal_boot2_get_psmode_status(void);
uint32_t hal_boot2_get_user_fw(void);
uint32_t hal_boot2_get_xip_addr(uint32_t flash_addr);
uint32_t hal_boot2_get_grp_count(void);
uint32_t hal_boot2_get_cpu_count(void);
uint32_t hal_boot2_get_feature_flag(void);
uint32_t hal_boot2_get_bootheader_offset(void);
int32_t hal_boot2_get_clk_cfg(hal_pll_config *cfg);
int32_t hal_boot_parse_bootheader(boot2_image_config *boot_img_cfg, uint8_t *data);
int32_t hal_boot2_set_cache(uint8_t cont_read, boot2_image_config *boot_img_cfg);
void hal_reboot_config(hal_reboot_cfg_t rbot);
void hal_boot2_init_clock(void);
void hal_boot2_get_ram_img_cnt(char *img_name[], uint32_t *ram_img_cnt);
void hal_boot2_get_img_info(uint8_t *data, uint32_t *image_offset, uint32_t *img_len, uint8_t **hash);
void hal_boot2_release_cpu(uint32_t core, uint32_t boot_addr);
void hal_boot2_reset_sec_eng(void);
void hal_boot2_sw_system_reset(void);
void hal_boot2_set_psmode_status(uint32_t flag);
void hal_boot2_clr_user_fw(void);
void hal_boot2_get_efuse_cfg(boot2_efuse_hw_config *efuse_cfg);
void hal_boot2_sboot_finish(void);
void hal_boot2_uart_gpio_init(void);
void hal_boot2_debug_uart_gpio_init(void);
void hal_boot2_debug_uart_gpio_deinit(void);
void hal_boot2_clean_cache(void);
#endif
