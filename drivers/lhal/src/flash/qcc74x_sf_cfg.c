#include "qcc74x_sf_ctrl.h"
#include "qcc74x_sf_cfg.h"
#include "qcc74x_xip_sflash.h"

/** @addtogroup  SF_CFG
 *  @{
 */

/** @defgroup  SF_CFG_Private_Macros
 *  @{
 */

/*@} end of group SF_CFG_Private_Macros */

/** @defgroup  SF_CFG_Private_Types
 *  @{
 */
typedef struct
{
    uint32_t jedec_id;
    char *name;
    const spi_flash_cfg_type *cfg;
} flash_info_t;

/*@} end of group SF_CFG_Private_Types */

/** @defgroup  SF_CFG_Private_Variables
 *  @{
 */
#ifndef CONFIG_NOT_SUPPORT_0X13_0X14_0X15_0X16_FLASH
static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_winb_80dv = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xef,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 0,
    .c_read_mode = 0xFF,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3d,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 3,
    .qe_data = 0,
};
#endif

__UNUSED static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_winb_16jv = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xef,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01, /*Q08BV,Q16DV: 0x02.Q32FW,Q32FV: 0x01 */
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3d,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 3,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_winb_80ew_16fw_32jw_32fw_32fv = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xef,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xa0,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 400,
    .time_e_32k = 1600,
    .time_e_64k = 2000,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 3,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_winb_128jw_128jv = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xef,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 0,
    .c_read_mode = 0xFF,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 400,
    .time_e_32k = 1600,
    .time_e_64k = 2000,
    .time_page_pgm = 5,
    .time_ce = 33 * 1000,
    .pd_delay = 3,
    .qe_data = 0,
};

__UNUSED static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_issi = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0x9d,

    .de_burst_wrap_cmd = 0xC0,
    .de_burst_wrap_cmd_dmy_clk = 0x00,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_1_LINE,
    .de_burst_wrap_data = 0x00,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0,
    .qe_bit = 0x06,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xA0,

    .burst_wrap_cmd = 0xC0,
    .burst_wrap_cmd_dmy_clk = 0x00,
    .burst_wrap_data_mode = SF_CTRL_DATA_1_LINE,
    .burst_wrap_data = 0x06,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 5,
    .qe_data = 0,
};

#ifndef CONFIG_NOT_SUPPORT_0X13_0X14_0X15_0X16_FLASH
static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_gd_md_40d = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0x51,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 0,
    .c_read_mode = 0xA0,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_DO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};
#endif

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_gd_lq08c_le16c_lq32d_wq32e = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xc8,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};

__UNUSED static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_gd_q80e_q16e = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xc8,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xA0,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};

#ifndef CONFIG_NOT_SUPPORT_0X13_0X14_0X15_0X16_FLASH
static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_gd_wq80e_wq16e = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xc8,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 32 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xA0,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 8 / 8,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 20,
    .qe_data = 0x12,
};
#endif

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_gd_q32e_q128e = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xc8,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 33 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_mxic = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xC2,

    .de_burst_wrap_cmd = 0xC0,
    .de_burst_wrap_cmd_dmy_clk = 0x00,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_1_LINE,
    .de_burst_wrap_data = 0x10,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0,
    .qe_bit = 0x06,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xA5,

    .burst_wrap_cmd = 0xC0,
    .burst_wrap_cmd_dmy_clk = 0x00,
    .burst_wrap_data_mode = SF_CTRL_DATA_1_LINE,
    .burst_wrap_data = 0x02,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x38,
    .qpp_addr_mode = SF_CTRL_ADDR_4_LINES,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/

    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 45,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_mxic_1635f = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xC2,

    .de_burst_wrap_cmd = 0xC0,
    .de_burst_wrap_cmd_dmy_clk = 0x00,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_1_LINE,
    .de_burst_wrap_data = 0x10,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0,
    .qe_bit = 0x06,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xA5,

    .burst_wrap_cmd = 0xC0,
    .burst_wrap_cmd_dmy_clk = 0x00,
    .burst_wrap_data_mode = SF_CTRL_DATA_1_LINE,
    .burst_wrap_data = 0x02,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x38,
    .qpp_addr_mode = SF_CTRL_ADDR_4_LINES,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 33 * 1000,
    .pd_delay = 45,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_mxic_25l256 = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xc2,

    .de_burst_wrap_cmd = 0xC0,
    .de_burst_wrap_cmd_dmy_clk = 0x00,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_1_LINE,
    .de_burst_wrap_data = 0x10,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0,
    .qe_bit = 0x06,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x15,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xA5,

    .burst_wrap_cmd = 0xC0,
    .burst_wrap_cmd_dmy_clk = 0x00,
    .burst_wrap_data_mode = SF_CTRL_DATA_1_LINE,
    .burst_wrap_data = 0x02,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x38,
    .qpp_addr_mode = SF_CTRL_ADDR_4_LINES,

    .io_mode = (SF_CTRL_QIO_MODE | 0x20),
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 400,
    .time_e_32k = 1000,
    .time_e_64k = 2000,
    .time_page_pgm = 5,
    .time_ce = 33 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_xtx = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0x0B,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0x01,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,
    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 6000,
    .time_e_32k = 4000,
    .time_e_64k = 4000,
    .time_page_pgm = 5,
    .time_ce = 65 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_puya_q80l_q80h_q16h = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0x85,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0x01,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3d,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,
    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 450,
    .time_e_32k = 1200,
    .time_e_64k = 1800,
    .time_page_pgm = 5,
    .time_ce = 65 * 1000,
    .pd_delay = 8,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_puya_q32h = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0x85,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0x01,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,
    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 8,
    .qe_data = 0,
};

#ifndef CONFIG_NOT_SUPPORT_0X13_0X14_0X15_0X16_FLASH
static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_boya40 = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0x68,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 0,
    .c_read_mode = 0xA0,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_DO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};
#endif

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_boya = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0x68,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0x01,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = SF_CTRL_QIO_MODE,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,
    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 33 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};

#ifndef CONFIG_NOT_SUPPORT_0X13_0X14_0X15_0X16_FLASH
static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_mx_kh25 = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xc2,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x00,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x00,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 0,
    .c_read_mode = 0x20,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = (SF_CTRL_DO_MODE | 0x10),
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 20 * 1000,
    .pd_delay = 20,
    .qe_data = 0,
};
#endif

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_winb_256fv = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0xef,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 1,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x01,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x31,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xa0,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = 0x24,
    .clk_delay = 1,
    .clk_invert = 0x3f,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 400,
    .time_e_32k = 1600,
    .time_e_64k = 2000,
    .time_page_pgm = 5,
    .time_ce = 33 * 1000,
    .pd_delay = 3,
    .qe_data = 0,
};

#ifndef CONFIG_NOT_SUPPORT_0X13_0X14_0X15_0X16_FLASH
static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flashcfg_xtx_q80b_f16b = {
    .reset_c_read_cmd = 0xff,
    .reset_c_read_cmd_size = 3,
    .mid = 0x85,

    .de_burst_wrap_cmd = 0x77,
    .de_burst_wrap_cmd_dmy_clk = 0x3,
    .de_burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .de_burst_wrap_data = 0xF0,

    /*reg*/
    .write_enable_cmd = 0x06,
    .wr_enable_index = 0x00,
    .wr_enable_bit = 0x01,
    .wr_enable_read_reg_len = 0x01,

    .qe_index = 0x01,
    .qe_bit = 0x01,
    .qe_write_reg_len = 0x02,
    .qe_read_reg_len = 0x1,

    .busy_index = 0,
    .busy_bit = 0x00,
    .busy_read_reg_len = 0x1,
    .release_powerdown = 0xab,

    .read_reg_cmd[0] = 0x05,
    .read_reg_cmd[1] = 0x35,
    .write_reg_cmd[0] = 0x01,
    .write_reg_cmd[1] = 0x01,

    .fast_read_qio_cmd = 0xeb,
    .fr_qio_dmy_clk = 16 / 8,
    .c_read_support = 1,
    .c_read_mode = 0xa0,

    .burst_wrap_cmd = 0x77,
    .burst_wrap_cmd_dmy_clk = 0x3,
    .burst_wrap_data_mode = SF_CTRL_DATA_4_LINES,
    .burst_wrap_data = 0x40,
    /*erase*/
    .chip_erase_cmd = 0xc7,
    .sector_erase_cmd = 0x20,
    .blk32_erase_cmd = 0x52,
    .blk64_erase_cmd = 0xd8,
    /*write*/
    .page_program_cmd = 0x02,
    .qpage_program_cmd = 0x32,
    .qpp_addr_mode = SF_CTRL_ADDR_1_LINE,

    .io_mode = 0x14,
    .clk_delay = 1,
    .clk_invert = 0x01,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,
    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    .qpi_jedec_id_cmd = 0x9f,
    .qpi_jedec_id_cmd_dmy_clk = 0x00,
#else
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
#endif
    .sector_size = 4,
    .page_size = 256,

    /*read*/
    .fast_read_cmd = 0x0b,
    .fr_dmy_clk = 8 / 8,
    .qpi_fast_read_cmd = 0x0b,
    .qpi_fr_dmy_clk = 8 / 8,
    .fast_read_do_cmd = 0x3b,
    .fr_do_dmy_clk = 8 / 8,
    .fast_read_dio_cmd = 0xbb,
    .fr_dio_dmy_clk = 0,
    .fast_read_qo_cmd = 0x6b,
    .fr_qo_dmy_clk = 8 / 8,

    .qpi_fast_read_qio_cmd = 0xeb,
    .qpi_fr_qio_dmy_clk = 16 / 8,
    .qpi_page_program_cmd = 0x02,
    .write_vreg_enable_cmd = 0x50,

    /* qpi mode */
    .enter_qpi = 0x38,
    .exit_qpi = 0xff,

    /*AC*/
    .time_e_sector = 300,
    .time_e_32k = 1200,
    .time_e_64k = 1200,
    .time_page_pgm = 5,
    .time_ce = 33000,
    .pd_delay = 20,
    .qe_data = 0,
};
#endif

__UNUSED static const ATTR_TCM_CONST_SECTION flash_info_t flash_infos[] = {
#ifndef CONFIG_NOT_SUPPORT_0X13_0X14_0X15_0X16_FLASH
    {
        .jedec_id = 0x134051,
        //.name="gd_md04d_04_33",
        .cfg = &flash_cfg_gd_md_40d,
    },
    {
        .jedec_id = 0x1320c2,
        //.name="mx_kh40_04_33",
        .cfg = &flash_cfg_mx_kh25,
    },
    {
        .jedec_id = 0x13400b,
        //.name="xt_25f04d_04_33",
        .cfg = &flash_cfg_xtx,
    },
    {
        .jedec_id = 0x134068,
        //.name="boya_q04b_04_33",
        .cfg = &flash_cfg_boya40,
    },
    {
        .jedec_id = 0x13325e,
        //.name="zbit_04_33",
        .cfg = &flash_cfg_mx_kh25,
    },
    {
        .jedec_id = 0x13605e,
        //.name="zbit_04_33",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x1440ef,
        //.name="winb_80dv_08_33",
        .cfg = &flash_cfg_winb_80dv,
    },
    {
        .jedec_id = 0x1460ef,
        //.name="winb_80ew_08_18",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x1440c8,
        //.name="gd_q08e_08_33",
        .cfg = &flash_cfg_gd_q80e_q16e,
    },
    {
        .jedec_id = 0x1460c8,
        //.name="gd_lq08c_08_18",
        .cfg = &flash_cfg_gd_lq08c_le16c_lq32d_wq32e,
    },
    {
        .jedec_id = 0x1465c8,
        //.name="gd_wq80e_80_33",
        .cfg = &flash_cfg_gd_wq80e_wq16e,
    },
    {
        .jedec_id = 0x1420c2,
        //.name="mx_kh80_08_33",
        .cfg = &flash_cfg_mx_kh25,
    },
    {
        .jedec_id = 0x14600b,
        //.name="xt_25q80b_08_18",
        .cfg = &flashcfg_xtx_q80b_f16b,
    },
    {
        .jedec_id = 0x144068,
        //.name="boya_q08b_08_33",
        .cfg = &flash_cfg_boya,
    },
    {
        .jedec_id = 0x14325e,
        //.name="zbit_08_33",
        .cfg = &flash_cfg_mx_kh25,
    },
    {
        .jedec_id = 0x14605e,
        //.name="zbit_08_33",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x144020,
        //.name="xm_qh80_08_33",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x1440a1,
        //.name="fm25q80_80_33",
        .cfg = &flash_cfg_gd_q80e_q16e,
    },
    {
        .jedec_id = 0x146085,
        //.name="puya_q80l/h_08_18/33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x14609d,
        //.name="issi_08_33",
        .cfg = &flash_cfg_issi,
    },
    {
        .jedec_id = 0x14709d,
        //.name="issi_08_18",
        .cfg = &flash_cfg_issi,
    },
    {
        .jedec_id = 0x1460cd,
        //.name="th25q80_80_33",
        .cfg = &flash_cfg_gd_lq08c_le16c_lq32d_wq32e,
    },
    {
        .jedec_id = 0x142085,
        //.name="py25q80hb_80_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x1540ef,
        //.name="winb_16dv_16_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x1570ef,
        //.name="wb_16jv_16_33",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x1560ef,
        //.name="winb_16fw_16_18",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x1540c8,
        //.name="gd_q16e_16_33",
        .cfg = &flash_cfg_gd_q80e_q16e,
    },
    {
        .jedec_id = 0x1560c8,
        //.name="gd_le16c_16_18",
        .cfg = &flash_cfg_gd_lq08c_le16c_lq32d_wq32e,
    },
    {
        .jedec_id = 0x1565c8,
        //.name="gd_wq16e_16_33",
        .cfg = &flash_cfg_gd_wq80e_wq16e,
    },
    {
        .jedec_id = 0x1520c2,
        //.name="mx_kh16_16_33",
        .cfg = &flash_cfg_mx_kh25,
    },
    {
        .jedec_id = 0x15400b,
        //.name="xt_25f16b_16_33",
        .cfg = &flashcfg_xtx_q80b_f16b,
    },
    {
        .jedec_id = 0x15650b,
        //.name="xt_25w08f_08_1833",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x154068,
        //.name="boya_q16b_16_33",
        .cfg = &flash_cfg_boya,
    },
    {
        .jedec_id = 0x15345e,
        //.name="zb_wq16a_16_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x15605e,
        //.name="zb_vq16_16_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x15405e,
        //.name="zb_16b_16_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x154020,
        //.name="xm_qh16_16_33",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x1540a1,
        //.name="fm25q16a_16_33",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x156085,
        //.name="puya_q16h_16_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x152085,
        //.name="py25q16hb_16_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x15609d,
        //.name="issi_16_33",
        .cfg = &flash_cfg_issi,
    },
    {
        .jedec_id = 0x15709d,
        //.name="issi_16_18",
        .cfg = &flash_cfg_issi,
    },
    {
        .jedec_id = 0x1560eb,
        //.name="th25q16_16_33",
        .cfg = &flash_cfg_gd_q80e_q16e,
    },
    {
        .jedec_id = 0x1560ba,
        //.name="zd25a16_16_33",
        .cfg = &flashcfg_xtx_q80b_f16b,
    },
    {
        .jedec_id = 0x1560c4,
        //.name="gt25q16_16_33",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x162085,
        //.name="py25q32hb_32_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x1640ef,
        //.name="winb_32fv_32_33",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x1660ef,
        //.name="winb_32fw_32_18",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x1680ef,
        //.name="winb_32jw_32_18",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x1640c8,
        //.name="gd_q32c_32_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x1660c8,
        //.name="gd_lq32d_32_18",
        .cfg = &flash_cfg_gd_lq08c_le16c_lq32d_wq32e,
    },
    {
        .jedec_id = 0x1665c8,
        //.name="gd_wq32e_32_33",
        .cfg = &flash_cfg_gd_lq08c_le16c_lq32d_wq32e,
    },
    {
        .jedec_id = 0x16400b,
        //.name="xt_25f32b_32_33",
        .cfg = &flash_cfg_xtx,
    },
    {
        .jedec_id = 0x16600b,
        //.name="xt_25q32b_32_18",
        .cfg = &flash_cfg_xtx,
    },
    {
        .jedec_id = 0x164068,
        //.name="boya_q32b_32_33",
        .cfg = &flash_cfg_boya,
    },
    {
        .jedec_id = 0x16405e,
        //.name="zb_32b_32_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x164020,
        //.name="xm_qh32_32_33",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x165020,
        //.name="xm_lu32_32_18",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x1640a1,
        //.name="fm25q32_32_33",
        .cfg = &flash_cfg_gd_q80e_q16e,
    },
    {
        .jedec_id = 0x166085,
        //.name="puya_q32h_32_33",
        .cfg = &flash_cfg_puya_q32h,
    },
    {
        .jedec_id = 0x16609d,
        //.name="issi_32_33",
        .cfg = &flash_cfg_issi,
    },
    {
        .jedec_id = 0x16709d,
        //.name="issi_32_18",
        .cfg = &flash_cfg_issi,
    },
    {
        .jedec_id = 0x1660c4,
        //.name="gt25q32_32_33",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x166125,
        //.name="sk25e032_32_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
#endif
    {
        .jedec_id = 0x176085,
        //.name="puya_q64h_64_33",
        .cfg = &flash_cfg_puya_q32h,
    },
    {
        .jedec_id = 0x1740ef,
        //.name="wb_64jv_64_33",
        .cfg = &flash_cfg_winb_128jw_128jv,
    },
    {
        .jedec_id = 0x1740a1,
        //.name="fm25q64_64_33",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x172085,
        //.name="py25q64ha_64_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x1760ef,
        //.name="wb_64jw_64_18",
        .cfg = &flash_cfg_winb_128jw_128jv,
    },
    {
        .jedec_id = 0x1740c8,
        //.name="gd_64e_64_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x1760c8,
        //.name="gd_lq64e_64_18",
        .cfg = &flash_cfg_gd_lq08c_le16c_lq32d_wq32e,
    },
    {
        .jedec_id = 0x17400b,
        //.name="xt_f64b_64_33",
        .cfg = &flash_cfg_xtx,
    },
    {
        .jedec_id = 0x174068,
        //.name="boya_q64a_64_33",
        .cfg = &flash_cfg_boya,
    },
    {
        .jedec_id = 0x17405e,
        //.name="zb_vq64_64_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x174020,
        //.name="xm_qh64_64_33",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x174220,
        //.name="xm_qw64_64_1833",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x1760c4,
        //.name="gt25q64_64_33",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x1840a1,
        //.name="fm25q128_128_33",
        .cfg = &flash_cfg_winb_80ew_16fw_32jw_32fw_32fv,
    },
    {
        .jedec_id = 0x182085,
        //.name="py25q128ha_128_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x1840ef,
        //.name="winb_128jv_128_33",
        .cfg = &flash_cfg_winb_128jw_128jv,
    },
    {
        .jedec_id = 0x1870ef,
        //.name="winb_128jv_128_33",
        .cfg = &flash_cfg_winb_128jw_128jv,
    },
    {
        .jedec_id = 0x1860ef,
        //.name="winb_128jw_128_18",
        .cfg = &flash_cfg_winb_128jw_128jv,
    },
    {
        .jedec_id = 0x1880ef,
        //.name="winb_128jw_128_18",
        .cfg = &flash_cfg_winb_128jw_128jv,
    },
    {
        .jedec_id = 0x1840c8,
        //.name="gd_q128e_128_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x1860c8,
        //.name="gd_lq128e_128_18",
        .cfg = &flash_cfg_gd_lq08c_le16c_lq32d_wq32e,
    },
    {
        .jedec_id = 0x1865C8,
        //.name="gd_wq128e_128_1833",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x1820c2,
        //.name="mx_25l128_128_33",
        .cfg = &flash_cfg_mxic_1635f,
    },
    {
        .jedec_id = 0x18400b,
        //.name="xt_25f128b_128_33",
        .cfg = &flash_cfg_xtx,
    },
    {
        .jedec_id = 0x184068,
        //.name="boya_q128a_128_33",
        .cfg = &flash_cfg_boya,
    },
    {
        .jedec_id = 0x184020,
        //.name="xm_qh128_128_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x18405e,
        //.name="zb_vq128_128_33",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x1828a1,
        //.name="fm25w_128_128_1833",
        .cfg = &flash_cfg_winb_16jv,
    },
    {
        .jedec_id = 0x186085,
        //.name="puya_q128h_128_33",
        .cfg = &flash_cfg_puya_q32h,
    },
    {
        .jedec_id = 0x1940ef,
        //.name="wb_256fv_256_33",
        .cfg = &flash_cfg_winb_256fv,
    },
    {
        .jedec_id = 0x192085,
        //.name="py25q256hb_256_33",
        .cfg = &flash_cfg_puya_q80l_q80h_q16h,
    },
    {
        .jedec_id = 0x1920c2,
        //.name="mx_25l256_256_33",
        .cfg = &flash_cfg_mxic_25l256,
    },
    {
        .jedec_id = 0x3425c2,
        //.name="mx_25v80_08_18",
        .cfg = &flash_cfg_mxic,
    },
    {
        .jedec_id = 0x3525c2,
        //.name="mx_25u16_35_18",
        .cfg = &flash_cfg_mxic_1635f,
    },
    {
        .jedec_id = 0x3625c2,
        //.name="mx_25v32_32_18",
        .cfg = &flash_cfg_mxic,
    },
    {
        .jedec_id = 0x3925c2,
        //.name="mx_u25643g_256_18",
        .cfg = &flash_cfg_mxic_25l256,
    },
    {
        .jedec_id = 0x1765C8,
        //.name="gd_wq64e_64_1833",
        .cfg = &flash_cfg_gd_q32e_q128e,
    },
    {
        .jedec_id = 0x1460c4,
        //.name="gt25q80_08_33",
        .cfg = &flash_cfg_winb_16jv,
    },
};

/*@} end of group SF_CFG_Private_Variables */

/** @defgroup  SF_CFG_Global_Variables
 *  @{
 */

/*@} end of group SF_CFG_Global_Variables */

/** @defgroup  SF_CFG_Private_Fun_Declaration
 *  @{
 */

#if defined(QCC74x_undef) || defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
/**
 * @brief Error type definition
 */
typedef enum {
    SUCCESS = 0,
    ERROR = 1,
    TIMEOUT = 2,
    INVALID = 3, /* invalid arguments */
    NORESC = 4   /* no resource or resource temperary unavailable */
} QCC74x_Err_Type;
#endif
#if defined(QCC74x_undef) || defined(QCC74x_undef)
extern QCC74x_Err_Type GLB_Set_Flash_IO_PARM(uint8_t sel_embedded, uint8_t swap);
#elif defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef)
extern QCC74x_Err_Type GLB_Set_SFlash_IO_PARM(uint8_t sel_embedded, uint8_t swapIo3Io0, uint8_t swapIo2Cs);
extern QCC74x_Err_Type GLB_Set_SFlash2_IO_PARM(uint8_t swapIo3Io0);
#elif defined(QCC74x_undef)
extern QCC74x_Err_Type GLB_Set_Embedded_FLash_IO_PARM(uint8_t reverse, uint8_t swapIo3Io0, uint8_t swapIo2Cs);
#elif defined(QCC74x_undef)
extern void qcc74x_glb_set_sflash_io_parm(uint8_t sel_embedded, uint8_t swap_io3_io0, uint8_t swap_io2_cs);
extern void qcc74x_glb_set_sflash2_io_parm(uint8_t swap_io3_io0);
#elif defined(QCC74x_undef)
extern QCC74x_Err_Type GLB_Select_Internal_Flash(void);
extern QCC74x_Err_Type GLB_Select_External_Flash(void);
extern QCC74x_Err_Type GLB_Deswap_Flash_Pin(void);
extern QCC74x_Err_Type GLB_Swap_Flash_Pin(void);
#endif

/*@} end of group SF_CFG_Private_Fun_Declaration */

/** @defgroup  SF_CFG_Private_Functions
 *  @{
 */

#if defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  Embedded flash set input function enable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION qcc74x_sf_cfg_init_internal_flash_gpio(void)
{
#define GLB_BASE_ADDR        0x40000000
#define GLB_GPIO_OFFSET_ADDR 0x100
    uint32_t regval;
    uint32_t gpio_pin;
    uint32_t pin_offset;

    for (gpio_pin = 32; gpio_pin < 38; gpio_pin++) {
        pin_offset = (gpio_pin >> 1) << 2;
        regval = *(uint32_t *)(GLB_BASE_ADDR + GLB_GPIO_OFFSET_ADDR + pin_offset);
        if (gpio_pin % 2 == 0) {
            /* [0] is ie */
            regval |= (1 << 0);
        } else {
            /* [16] is ie */
            regval |= (1 << 16);
        }
        *(uint32_t *)(GLB_BASE_ADDR + GLB_GPIO_OFFSET_ADDR + pin_offset) = regval;
    }
}
#elif defined(QCC74x_undef) || defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  Init internal flash GPIO
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION qcc74x_sf_cfg_init_internal_flash_gpio(void)
{
    struct qcc74x_device_s *gpio;
    uint8_t gpio_pins[6];
    uint8_t i = 0;

    gpio = qcc74x_device_get_by_name("gpio");
    for (i = 0; i < sizeof(gpio_pins); i++) {
        gpio_pins[i] = 23 + i;
        qcc74x_gpio_init(gpio, gpio_pins[i],
                       QCC74x_GPIO_FUNC_SF | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    }
}
#endif

#if defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  Restore GPIO17 function
 *
 * @param  fun: GPIO17 function
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION qcc74x_sf_cfg_restore_gpio17_fun(uint8_t fun)
{
    struct qcc74x_device_s *gpio;

    gpio = qcc74x_device_get_by_name("gpio");
    qcc74x_gpio_init(gpio, GPIO_PIN_17,
                   fun | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
}
#endif

/****************************************************************************/ /**
 * @brief  Init external flash GPIO according to flash GPIO config
 *
 * @param  ext_flash_pin: Flash GPIO config
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_init_ext_flash_gpio(uint8_t ext_flash_pin)
{
#ifdef romapi_qcc74x_sf_cfg_init_ext_flash_gpio
    return romapi_qcc74x_sf_cfg_init_ext_flash_gpio(ext_flash_pin);
#else
    struct qcc74x_device_s *gpio;
    uint8_t gpio_pins[6];
    uint8_t i = 0;

    gpio = qcc74x_device_get_by_name("gpio");
    if (ext_flash_pin == 0) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK0_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS0_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA00_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA10_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA20_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA30_GPIO;
#if defined(QCC74x_undef) || defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef)
    } else if (ext_flash_pin == 1) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK1_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS1_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA01_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA11_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA21_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA31_GPIO;
#elif defined(QCC74x_undef)
    } else if (ext_flash_pin == 1) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK1_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS1_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA01_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA11_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA21_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA31_GPIO;
    } else if (ext_flash_pin == 2) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK2_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS2_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA02_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA12_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA22_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA32_GPIO;
#elif defined(QCC74x_undef)
    } else if (ext_flash_pin == 1) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK1_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS1_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA01_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA11_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA21_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA31_GPIO;
#endif
    } else {
        return -1;
    }

    for (i = 0; i < sizeof(gpio_pins); i++) {
        qcc74x_gpio_init(gpio, gpio_pins[i],
                       QCC74x_GPIO_FUNC_SF | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    }

    return 0;
#endif
}

/****************************************************************************/ /**
 * @brief  Deinit external flash GPIO according to flash GPIO config
 *
 * @param  ext_flash_pin: Flash GPIO config
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_deinit_ext_flash_gpio(uint8_t ext_flash_pin)
{
#ifdef romapi_qcc74x_sf_cfg_deinit_ext_flash_gpio
    return romapi_qcc74x_sf_cfg_deinit_ext_flash_gpio(ext_flash_pin);
#else
    struct qcc74x_device_s *gpio;
    uint8_t gpio_pins[6];
    uint8_t i = 0;

    gpio = qcc74x_device_get_by_name("gpio");
    if (ext_flash_pin == 0) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK0_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS0_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA00_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA10_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA20_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA30_GPIO;
#if defined(QCC74x_undef) || defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef)
    } else if (ext_flash_pin == 1) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK1_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS1_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA01_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA11_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA21_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA31_GPIO;
#elif defined(QCC74x_undef)
    } else if (ext_flash_pin == 1) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK1_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS1_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA01_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA11_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA21_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA31_GPIO;
    } else if (ext_flash_pin == 2) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK2_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS2_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA02_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA12_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA22_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA32_GPIO;
#elif defined(QCC74x_undef)
    } else if (ext_flash_pin == 1) {
        gpio_pins[0] = QCC74x_EXTFLASH_CLK1_GPIO;
        gpio_pins[1] = QCC74x_EXTFLASH_CS1_GPIO;
        gpio_pins[2] = QCC74x_EXTFLASH_DATA01_GPIO;
        gpio_pins[3] = QCC74x_EXTFLASH_DATA11_GPIO;
        gpio_pins[4] = QCC74x_EXTFLASH_DATA21_GPIO;
        gpio_pins[5] = QCC74x_EXTFLASH_DATA31_GPIO;
#endif
    } else {
        return -1;
    }

    for (i = 0; i < sizeof(gpio_pins); i++) {
        qcc74x_gpio_init(gpio, gpio_pins[i], GPIO_INPUT | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
    }

    return 0;
#endif
}

/*@} end of group SF_CFG_Private_Functions */

/** @defgroup  SF_CFG_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Init flash GPIO according to flash Pin config
 *
 * @param  flash_pin_cfg: Specify flash Pin config
 * @param  restore_default: Wether to restore default setting
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
#if defined(QCC74x_undef) || defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef)
int ATTR_TCM_SECTION qcc74x_sf_cfg_init_flash_gpio(uint8_t flash_pin_cfg, uint8_t restore_default)
{
#ifdef romapi_qcc74x_sf_cfg_init_flash_gpio
    return romapi_qcc74x_sf_cfg_init_flash_gpio(flash_pin_cfg, restore_default);
#else
    uint8_t sel_embedded = 0;
    uint8_t swap_io2_cs = 0;
    uint8_t swap_io3_io0 = 0;

    if (restore_default) {
        /* Set Default first */
#if defined(QCC74x_undef)
        qcc74x_glb_set_sflash_io_parm(1, 1, 0);
#else
        GLB_Set_SFlash_IO_PARM(1, 1, 0);
#endif
        qcc74x_sf_ctrl_select_pad(SF_IO_EMB_SWAP_IO3IO0);

        /* Default is set, so return */
        if (flash_pin_cfg == SF_IO_EMB_SWAP_IO3IO0) {
            return 0;
        }
    }

    if (flash_pin_cfg & (1 << 2)) {
#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
        /* Init sf2 gpio */
        qcc74x_sf_cfg_init_flash2_gpio(!((flash_pin_cfg >> 5) & 1));
#endif
        sel_embedded = 0;
    } else if (flash_pin_cfg & (1 << 3)) {
        /* Init sf3 gpio */
        qcc74x_sf_cfg_init_ext_flash_gpio(1);
        sel_embedded = 0;
    } else {
        sel_embedded = 1;
    }
    /* if pin select dual flash, embedded is default */
    if ((flash_pin_cfg & (1 << 4))) {
        sel_embedded = 1;
    }

    swap_io3_io0 = ((flash_pin_cfg >> 1) & 1);
    swap_io3_io0 = (!swap_io3_io0);
    swap_io2_cs = ((flash_pin_cfg >> 0) & 1);
#if defined(QCC74x_undef)
    qcc74x_glb_set_sflash_io_parm(sel_embedded, swap_io3_io0, swap_io2_cs);
#else
    GLB_Set_SFlash_IO_PARM(sel_embedded, swap_io3_io0, swap_io2_cs);
#endif
    qcc74x_sf_ctrl_select_pad(flash_pin_cfg);

    return 0;
#endif
}
#elif defined(QCC74x_undef) || defined(QCC74x_undef)
int ATTR_TCM_SECTION qcc74x_sf_cfg_init_flash_gpio(uint8_t flash_pin_cfg, uint8_t restore_default)
{
    uint8_t sel_embedded = 0;
    uint8_t swap = 0;

    if ((flash_pin_cfg & (1 << 3)) > 0) {
        return ERROR;
    }

    if (restore_default) {
        /* Set Default first */
        GLB_Set_Flash_IO_PARM(1, 1);
        qcc74x_sf_ctrl_select_pad(SF_IO_EMB_SWAP_IO0_IO3);

        /* Default is set, so return */
        if (flash_pin_cfg == SF_IO_EMB_SWAP_IO0_IO3) {
            return SUCCESS;
        }
    }

    if (flash_pin_cfg & (1 << 2)) {
        /* Init sf2 gpio */
        qcc74x_sf_cfg_init_ext_flash_gpio(0);
        sel_embedded = 0;
    } else {
        sel_embedded = 1;
    }
    /* if pin select dual flash, embedded is default */
    if ((flash_pin_cfg & (1 << 4))) {
        sel_embedded = 1;
    }

    swap = ((flash_pin_cfg >> 1) & 1);
    swap = (!swap);
    GLB_Set_Flash_IO_PARM(sel_embedded, swap);
    qcc74x_sf_ctrl_select_pad(flash_pin_cfg);

    return SUCCESS;
}
#elif defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  Init flash GPIO according to flash Pin config
 *
 * @param  flash_pin_cfg: Specify flash Pin config
 * @param  restore_default: Wether to restore default setting
 *
 * @return None
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_init_flash_gpio(uint8_t flash_pin_cfg, uint8_t restore_default)
{
    if (restore_default) {
        GLB_Set_Embedded_FLash_IO_PARM(0, 0, 0);

        qcc74x_sf_cfg_init_internal_flash_gpio();
        qcc74x_sf_ctrl_select_pad(SF_CTRL_PAD1);

        /* Default is set, so return */
        if (flash_pin_cfg == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_NONE) {
            return 0;
        }
    }

    if (flash_pin_cfg == SF_CTRL_SEL_EXTERNAL_FLASH) {
        qcc74x_sf_cfg_init_ext_flash_gpio(0);
        qcc74x_sf_ctrl_select_pad(SF_CTRL_PAD2);
    } else {
        if (flash_pin_cfg == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_NONE) {
            GLB_Set_Embedded_FLash_IO_PARM(0, 0, 0);
        } else if (flash_pin_cfg == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_CSIO2) {
            GLB_Set_Embedded_FLash_IO_PARM(0, 0, 1);
        } else if (flash_pin_cfg == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_IO0IO3) {
            GLB_Set_Embedded_FLash_IO_PARM(0, 1, 0);
        } else if (flash_pin_cfg == SF_CTRL_SEL_INTERNAL_FLASH_SWAP_BOTH) {
            GLB_Set_Embedded_FLash_IO_PARM(0, 1, 1);
        } else if (flash_pin_cfg == SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_NONE) {
            GLB_Set_Embedded_FLash_IO_PARM(1, 0, 0);
        } else if (flash_pin_cfg == SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_CSIO2) {
            GLB_Set_Embedded_FLash_IO_PARM(1, 0, 1);
        } else if (flash_pin_cfg == SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_IO0IO3) {
            GLB_Set_Embedded_FLash_IO_PARM(1, 1, 0);
        } else {
            GLB_Set_Embedded_FLash_IO_PARM(1, 1, 1);
        }

        qcc74x_sf_cfg_init_internal_flash_gpio();
        qcc74x_sf_ctrl_select_pad(SF_CTRL_PAD1);
    }

    return 0;
}
#elif defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  Init flash GPIO according to flash Pin config
 *
 * @param  flash_pin_cfg: Specify flash Pin config
 * @param  restore_default: Wether to restore default setting
 *
 * @return None
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_init_flash_gpio(uint8_t flash_pin_cfg, uint8_t restore_default)
{
#define GLB_BASE_ADDR                      0x40000000
#define GLB_PARM_OFFSET_ADDR               0x80
#define GLB_GPIO_USE_PSRAM__IO_OFFSET_ADDR 0x88
    uint8_t flash_cfg;
    uint8_t swap_cfg;
    uint32_t regval;

    flash_cfg = (flash_pin_cfg >> 2) & 0x03;
    swap_cfg = flash_pin_cfg & 0x03;

    if (restore_default) {
        /* Set Default first */
        regval = getreg32(GLB_BASE_ADDR + GLB_GPIO_USE_PSRAM__IO_OFFSET_ADDR);

        /* Bit0~5 is sf io select */
        if ((regval & 0x3F) == 0x00) {
            qcc74x_sf_cfg_init_ext_flash_gpio(1);
        }

        regval = getreg32(GLB_BASE_ADDR + GLB_PARM_OFFSET_ADDR);
        /* Bit9 is flash2 swap cs with io2 */
        regval &= ~(1 << 9);
        /* Bit8 is flash2 swap io0 with io3 */
        regval &= ~(1 << 8);
        putreg32(regval, GLB_BASE_ADDR + GLB_PARM_OFFSET_ADDR);

        qcc74x_sf_ctrl_select_pad(SF_CTRL_SEL_SF2);

        /* Default is set, so return */
        if (flash_cfg == QCC74x_FLASH_CFG_SF2_EXT_23_28 && swap_cfg == QCC74x_SF2_SWAP_NONE) {
            return 0;
        }
    }

    if (flash_cfg == QCC74x_FLASH_CFG_SF1_EXT_17_22) {
        qcc74x_sf_cfg_init_ext_flash_gpio(0);
        qcc74x_sf_ctrl_select_pad(SF_CTRL_SEL_SF1);
    } else {
        regval = getreg32(GLB_BASE_ADDR + GLB_GPIO_USE_PSRAM__IO_OFFSET_ADDR);

        /* Bit0~5 is sf io select */
        if ((regval & 0x3F) == 0x00) {
            qcc74x_sf_cfg_init_ext_flash_gpio(1);
        }

        regval = getreg32(GLB_BASE_ADDR + GLB_PARM_OFFSET_ADDR);
        if (swap_cfg == QCC74x_SF2_SWAP_NONE) {
            /* Bit9 is flash2 swap cs with io2 */
            regval &= ~(1 << 9);
            /* Bit8 is flash2 swap io0 with io3 */
            regval &= ~(1 << 8);
        } else if (swap_cfg == QCC74x_SF2_SWAP_CS_IO2) {
            /* Bit9 is flash2 swap cs with io2 */
            regval |= (1 << 9);
            /* Bit8 is flash2 swap io0 with io3 */
            regval &= ~(1 << 8);
        } else if (swap_cfg == QCC74x_SF2_SWAP_IO0_IO3) {
            /* Bit9 is flash2 swap cs with io2 */
            regval &= ~(1 << 9);
            /* Bit8 is flash2 swap io0 with io3 */
            regval |= (1 << 8);
        } else {
            /* Bit9 is flash2 swap cs with io2 */
            regval |= (1 << 9);
            /* Bit8 is flash2 swap io0 with io3 */
            regval |= (1 << 8);
        }
        putreg32(regval, GLB_BASE_ADDR + GLB_PARM_OFFSET_ADDR);

        qcc74x_sf_ctrl_select_pad(SF_CTRL_SEL_SF2);
    }

    return 0;
}
#elif defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  Init flash GPIO according to flash Pin config
 *
 * @param  flash_pin_cfg: Specify flash Pin config
 * @param  restore_default: Wether to restore default setting
 *
 * @return None
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_init_flash_gpio(uint8_t flash_pin_cfg, uint8_t restore_default)
{
    if (restore_default) {
        /* Set Default first */
        qcc74x_sf_ctrl_select_pad(SF_CTRL_EMBEDDED_SEL);
        GLB_Select_Internal_Flash();
        GLB_Swap_Flash_Pin();
        //SF_Cfg_Deinit_Ext_Flash_Gpio(0);
        qcc74x_sf_cfg_deinit_ext_flash_gpio(1);
        qcc74x_sf_cfg_init_internal_flash_gpio();
    }

    if (flash_pin_cfg > 0) {
        /*01: deswap flash PIN
            10: use ext flash 1(GPIO17-22)
            11: use ext flash 0(GPIO0-2, 20-22)
        */
        if (flash_pin_cfg == QCC74x_FLASH_CFG_DESWAP) {
            qcc74x_sf_ctrl_select_pad(SF_CTRL_EMBEDDED_SEL);
            /*DONOT Swap flash PIN*/
            GLB_Deswap_Flash_Pin();
        } else {
            qcc74x_sf_ctrl_select_pad(flash_pin_cfg - 1);
            GLB_Select_External_Flash();
            qcc74x_sf_cfg_init_ext_flash_gpio(flash_pin_cfg - QCC74x_FLASH_CFG_EXT0_17_22);
        }
    }

    return 0;
}
#endif

#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
/****************************************************************************/ /**
 * @brief  Init flash2 GPIO
 *
 * @param  swap: Select embedded flash2 swap io3 with io0
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_init_flash2_gpio(uint8_t swap)
{
#ifdef romapi_qcc74x_sf_cfg_init_flash2_gpio
    return romapi_qcc74x_sf_cfg_init_flash2_gpio(swap);
#else
    qcc74x_sf_cfg_init_ext_flash_gpio(0);
#if defined(QCC74x_undef)
    qcc74x_glb_set_sflash2_io_parm(swap);
#elif defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef)
    GLB_Set_SFlash2_IO_PARM(swap);
#endif

    return 0;
#endif
}
#endif

/****************************************************************************/ /**
 * @brief  Identify one flash
 *
 * @param  call_from_flash: code run at flash or ram
 * @param  flash_pin_cfg: Bit 7: auto_scan, Bit6-0: flash GPIO config
 * @param  restore_default: Wether restore default flash GPIO config
 * @param  p_flash_cfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return Flash ID
 *
*******************************************************************************/
__WEAK
uint32_t ATTR_TCM_SECTION qcc74x_sf_cfg_flash_identify(uint8_t call_from_flash, uint8_t flash_pin_cfg, uint8_t restore_default,
                                                     spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank)
{
#ifdef romapi_qcc74x_sf_cfg_flash_identify
    return romapi_qcc74x_sf_cfg_flash_identify(call_from_flash, flash_pin_cfg, restore_default, p_flash_cfg, group, bank);
#else
    uint8_t auto_scan = 0;
    uint8_t flash_pin = 0;
    uint32_t jedec_id = 0;
    uint32_t i = 0;
    uint32_t offset = 0;
    uint8_t stat = 0;
#if defined(QCC74x_undef)
    uint8_t gpio17_fun = 0;
#endif

    auto_scan = ((flash_pin_cfg >> 7) & 1);
    flash_pin = (flash_pin_cfg & 0x7F);

    arch_memcpy_fast(p_flash_cfg, &flash_cfg_winb_16jv, sizeof(spi_flash_cfg_type));

    if (call_from_flash == 1) {
        stat = qcc74x_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

        if (stat != 0) {
            qcc74x_sf_ctrl_set_owner(SF_CTRL_OWNER_IAHB);
            return 0;
        }
    }

    if (auto_scan) {
        flash_pin = 0;
        do {
#if defined(QCC74x_undef) || defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef)
            if (!IS_SF_CTRL_PIN_SELECT(flash_pin)) {
                flash_pin++;
                continue;
            }
            if (bank == SF_CTRL_FLASH_BANK1) {
#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
                if (flash_pin > SF_IO_EMB_SWAP_IO2CS_AND_SF2) {
                    jedec_id = 0;
                    break;
                }
                if (flash_pin < SF_IO_EXT_SF3) {
                    flash_pin = SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0;
                }
                if (flash_pin == SF_IO_EXT_SF2) {
                    flash_pin++;
                }
                qcc74x_sf_cfg_init_flash2_gpio(!((flash_pin >> 5) & 1));
#endif
            } else {
                if (flash_pin > SF_IO_EXT_SF2) {
                    jedec_id = 0;
                    break;
                }
                if (flash_pin > SF_IO_EXT_SF3) {
                    flash_pin = SF_IO_EXT_SF2;
                }
                qcc74x_sf_cfg_init_flash_gpio(flash_pin, restore_default);
            }
#elif defined(QCC74x_undef) || defined(QCC74x_undef)
            if (flash_pin > SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
                jedec_id = 0;
                break;
            }
            if (!IS_SF_CTRL_PIN_SELECT(flash_pin) || (flash_pin & (1 << 3)) > 0) {
                flash_pin++;
                continue;
            }
            qcc74x_sf_cfg_init_flash_gpio(flash_pin, restore_default);
#elif defined(QCC74x_undef)
            if (flash_pin > SF_CTRL_SEL_INTERNAL_FLASH_REVERSE_SWAP_BOTH) {
                jedec_id = 0;
                break;
            }
            qcc74x_sf_cfg_init_flash_gpio(flash_pin, restore_default);
#elif defined(QCC74x_undef)
            if (flash_pin > 0x0f) {
                jedec_id = 0;
                break;
            }
            qcc74x_sf_cfg_init_flash_gpio(flash_pin, restore_default);
#elif defined(QCC74x_undef)
#define GLB_BASE_ADDR          0x40000000
#define GLB_GPIO17_OFFSET_ADDR 0x120
            if (flash_pin > QCC74x_FLASH_CFG_EXT1_0_2_20_22) {
                jedec_id = 0;
                break;
            }

            if (flash_pin > QCC74x_FLASH_CFG_EXT0_17_22) {
                /*flash_pin=2 has make gpio17 into jtag,but not success*/
                qcc74x_sf_cfg_restore_gpio17_fun(gpio17_fun);
            }

            /* select media gpio */
            if (flash_pin == QCC74x_FLASH_CFG_EXT0_17_22) {
                gpio17_fun = ((getreg32(GLB_BASE_ADDR + GLB_GPIO17_OFFSET_ADDR) >> 24) & 0xf);
            }

            qcc74x_sf_cfg_init_flash_gpio(flash_pin, restore_default);
#endif
            qcc74x_sflash_release_powerdown(p_flash_cfg);
            qcc74x_sflash_reset_continue_read(p_flash_cfg);
            qcc74x_sflash_disable_burst_wrap(p_flash_cfg);
            jedec_id = 0;
            qcc74x_sflash_get_jedecid(p_flash_cfg, (uint8_t *)&jedec_id);
            qcc74x_sflash_disable_burst_wrap(p_flash_cfg);
            jedec_id = jedec_id & 0xffffff;
            flash_pin++;
        } while ((jedec_id & 0x00ffff) == 0 || (jedec_id & 0xffff00) == 0 || (jedec_id & 0x00ffff) == 0xffff || (jedec_id & 0xffff00) == 0xffff00);
    } else {
        /* select media gpio */
#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
        if (bank == SF_CTRL_FLASH_BANK1) {
            qcc74x_sf_cfg_init_flash2_gpio(!((flash_pin >> 5) & 1));
        } else {
            qcc74x_sf_cfg_init_flash_gpio(flash_pin, restore_default);
        }
#else
        qcc74x_sf_cfg_init_flash_gpio(flash_pin, restore_default);
#endif
        qcc74x_sflash_release_powerdown(p_flash_cfg);
        qcc74x_sflash_reset_continue_read(p_flash_cfg);
        qcc74x_sflash_disable_burst_wrap(p_flash_cfg);
        qcc74x_sflash_get_jedecid(p_flash_cfg, (uint8_t *)&jedec_id);
        qcc74x_sflash_disable_burst_wrap(p_flash_cfg);
        jedec_id = jedec_id & 0xffffff;
    }

    for (i = 0; i < sizeof(flash_infos) / sizeof(flash_infos[0]); i++) {
        if (flash_infos[i].jedec_id == jedec_id) {
            arch_memcpy_fast(p_flash_cfg, flash_infos[i].cfg, sizeof(spi_flash_cfg_type));
            break;
        }
    }

    if (i == sizeof(flash_infos) / sizeof(flash_infos[0])) {
        if (call_from_flash == 1) {
            qcc74x_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
        }

        return jedec_id;
    } else {
        if (call_from_flash == 1) {
            qcc74x_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
        }

        return (jedec_id | QCC74x_FLASH_ID_VALID_FLAG);
    }
#endif
}

#if defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  Identify one flash patch
 *
 * @param  call_from_flash: code run at flash or ram
 * @param  flash_pin_cfg: Bit 7: auto_scan, Bit6-0: flash GPIO config
 * @param  restore_default: Wether restore default flash GPIO config
 * @param  p_flash_cfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return Flash ID
 *
*******************************************************************************/
__WEAK
uint32_t ATTR_TCM_SECTION qcc74x_sf_cfg_flash_identify_ext(uint8_t call_from_flash, uint8_t flash_pin_cfg,
                                                         uint8_t restore_default, spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank)
{
    return qcc74x_sf_cfg_flash_identify(call_from_flash, flash_pin_cfg, restore_default, p_flash_cfg, group, bank);
}
#endif

/****************************************************************************/ /**
 * @brief  Get flash config according to flash ID
 *
 * @param  flash_id: Flash ID
 * @param  p_flash_cfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_get_flash_cfg_need_lock(uint32_t flash_id, spi_flash_cfg_type *p_flash_cfg,
                                                         uint8_t group, uint8_t bank)
{
#ifdef romapi_qcc74x_sf_cfg_get_flash_cfg_need_lock
    return romapi_qcc74x_sf_cfg_get_flash_cfg_need_lock(flash_id, p_flash_cfg, group, bank);
#else
    uint32_t i = 0;
    uint8_t buf[sizeof(spi_flash_cfg_type) + 8];
    uint32_t crc = 0, *p_crc;
    uint32_t xip_offset = 0;
    char flash_cfg_magic[] = "FCFG";

    if (flash_id == 0) {
        xip_offset = qcc74x_sf_ctrl_get_flash_image_offset(group, bank);
        qcc74x_sf_ctrl_set_flash_image_offset(0, group, bank);
        qcc74x_xip_sflash_read_via_cache_need_lock(8 + QCC74x_FLASH_XIP_BASE, buf, sizeof(spi_flash_cfg_type) + 8, group, bank);
        qcc74x_sf_ctrl_set_flash_image_offset(xip_offset, group, bank);

        if (arch_memcmp(buf, flash_cfg_magic, 4) == 0) {
            crc = qcc74x_soft_crc32((uint8_t *)buf + 4, sizeof(spi_flash_cfg_type));
            p_crc = (uint32_t *)(buf + 4 + sizeof(spi_flash_cfg_type));

            if (*p_crc == crc) {
                arch_memcpy_fast(p_flash_cfg, (uint8_t *)buf + 4, sizeof(spi_flash_cfg_type));
                return 0;
            }
        }
    } else {
        for (i = 0; i < sizeof(flash_infos) / sizeof(flash_infos[0]); i++) {
            if (flash_infos[i].jedec_id == flash_id) {
                arch_memcpy_fast(p_flash_cfg, flash_infos[i].cfg, sizeof(spi_flash_cfg_type));
                return 0;
            }
        }
    }

    return -1;
#endif
}

#if defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  Get flash config according to flash ID patch
 *
 * @param  flash_id: Flash ID
 * @param  p_flash_cfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_get_flash_cfg_need_lock_ext(uint32_t flash_id, spi_flash_cfg_type *p_flash_cfg,
                                                             uint8_t group, uint8_t bank)
{
    return qcc74x_sf_cfg_get_flash_cfg_need_lock(flash_id, p_flash_cfg, group, bank);
}
#endif

#if defined(QCC74x_undef) || defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  SF Cfg flash init
 *
 * @param  sel: SF pin select
 * @param  p_sf_ctrl_cfg: Serial flash controller configuration pointer
 * @param  p_bank2_cfg: Serial flash2 controller configuration pointer
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_flash_init(uint8_t sel, const struct sf_ctrl_cfg_type *p_sf_ctrl_cfg,
                                            const struct sf_ctrl_bank2_cfg *p_bank2_cfg)
{
#ifdef romapi_qcc74x_sf_cfg_flash_init
    return romapi_qcc74x_sf_cfg_flash_init(sel, p_sf_ctrl_cfg, p_bank2_cfg);
#else
    uint8_t sel_embedded = 0;
    uint8_t swap_io2_cs = 0;
    uint8_t swap_io3_io0 = 0;

    if (sel > SF_IO_EMB_SWAP_IO2CS_AND_SF2) {
        return -1;
    }

    if (sel & (1 << 2)) {
#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
        qcc74x_sf_cfg_init_flash2_gpio(!((sel >> 5) & 1));
#endif
        sel_embedded = 0;
    } else if (sel & (1 << 3)) {
        qcc74x_sf_cfg_init_ext_flash_gpio(1);
        sel_embedded = 0;
    } else {
        sel_embedded = 1;
    }
    /* If pin select dual flash, embedded is default */
    if ((sel & (1 << 4))) {
        sel_embedded = 1;
    }

    swap_io3_io0 = ((sel >> 1) & 1);
    swap_io3_io0 = (!swap_io3_io0);
    swap_io2_cs = ((sel >> 0) & 1);
#if defined(QCC74x_undef)
    qcc74x_glb_set_sflash_io_parm(sel_embedded, swap_io3_io0, swap_io2_cs);
#else
    GLB_Set_SFlash_IO_PARM(sel_embedded, swap_io3_io0, swap_io2_cs);
#endif
    qcc74x_sf_ctrl_select_pad(sel);

    if (sel <= SF_IO_EMB_SWAP_IO2CS) {
        /* Embedded pad1 io delay set */
        if (p_sf_ctrl_cfg != NULL) {
            qcc74x_sf_ctrl_set_io_delay(SF_CTRL_PAD1, p_sf_ctrl_cfg->do_delay, p_sf_ctrl_cfg->di_delay, p_sf_ctrl_cfg->oe_delay);
        }
    } else if (sel <= SF_IO_EXT_SF3 || sel == SF_IO_EXT_SF2) {
        /* Pad2 or pad3 io delay set */
        if (p_sf_ctrl_cfg != NULL) {
            qcc74x_sf_ctrl_set_io_delay(((sel & 0xf) >> 2), p_sf_ctrl_cfg->do_delay, p_sf_ctrl_cfg->di_delay, p_sf_ctrl_cfg->oe_delay);
        }
    } else if ((sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2_SWAP_IO3IO0) || (sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2)) {
        /* Dual flash mode, embedded pad1 and pad2 io delay set */
        if (p_sf_ctrl_cfg != NULL) {
            qcc74x_sf_ctrl_set_io_delay(SF_CTRL_PAD1, p_sf_ctrl_cfg->do_delay, p_sf_ctrl_cfg->di_delay, p_sf_ctrl_cfg->oe_delay);
        }
        if (p_bank2_cfg != NULL) {
            qcc74x_sf_ctrl_set_io_delay(SF_CTRL_PAD2, p_bank2_cfg->do_delay, p_bank2_cfg->di_delay, p_bank2_cfg->oe_delay);
        }
    }

#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
    if (p_bank2_cfg != NULL) {
        if (p_bank2_cfg->sbus2_select) {
            if ((sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2_SWAP_IO3IO0) || (sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2)) {
                /* Default sbus2 replace opt flash2 */
                qcc74x_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
            }
        }
    }
#endif

    qcc74x_sflash_init(p_sf_ctrl_cfg, p_bank2_cfg);

    return 0;
#endif
}

#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
/****************************************************************************/ /**
 * @brief  SF Cfg system bus 2 flash init
 *
 * @param  sel: SF pin select
 * @param  p_bank2_cfg: Serial flash2 controller configuration pointer
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_sbus2_flash_init(uint8_t sel, const struct sf_ctrl_bank2_cfg *p_bank2_cfg)
{
#ifdef romapi_qcc74x_sf_cfg_sbus2_flash_init
    return romapi_qcc74x_sf_cfg_sbus2_flash_init(sel, p_bank2_cfg);
#else
    if (sel < SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0 || sel > SF_IO_EMB_SWAP_IO2CS_AND_SF2) {
        return -1;
    }

    /* Init flash2 gpio */
    if (sel & (1 << 2)) {
        qcc74x_sf_cfg_init_flash2_gpio(!((sel >> 5) & 1));
    }

    /* Set remap for flash2 xip mode */
    qcc74x_sf_ctrl_remap_set(p_bank2_cfg->remap, p_bank2_cfg->remap_lock);

    if ((sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2_SWAP_IO3IO0) || (sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2)) {
        /* Dual flash mode, pad2 io delay set */
        qcc74x_sf_ctrl_set_io_delay(SF_CTRL_PAD2, p_bank2_cfg->do_delay, p_bank2_cfg->di_delay, p_bank2_cfg->oe_delay);
    }
    if (p_bank2_cfg->sbus2_select) {
        if ((sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2_SWAP_IO3IO0) || (sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2)) {
            /* Default sbus2 replace opt flash2 */
            qcc74x_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
        }
    }

    qcc74x_sflash_init(NULL, p_bank2_cfg);

    return 0;
#endif
}
#endif
#elif defined(QCC74x_undef) || defined(QCC74x_undef)
/****************************************************************************/ /**
 * @brief  SF Cfg flash init
 *
 * @param  sel: SF pin select
 * @param  p_sf_ctrl_cfg: Serial flash controller configuration pointer
 * @param  p_bank2_cfg: Serial flash2 controller configuration pointer
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_flash_init(uint8_t sel, const struct sf_ctrl_cfg_type *p_sf_ctrl_cfg,
                                            const struct sf_ctrl_bank2_cfg *p_bank2_cfg)
{
    uint8_t sel_embedded = 0;
    uint8_t swap = 0;

    if ((sel & (1 << 3)) > 0) {
        return ERROR;
    }

    if (sel & (1 << 2)) {
        qcc74x_sf_cfg_init_ext_flash_gpio(0);
        sel_embedded = 0;
    } else {
        sel_embedded = 1;
    }
    /* If pin select dual flash, embedded is default */
    if ((sel & (1 << 4))) {
        sel_embedded = 1;
    }

    swap = ((sel >> 1) & 1);
    swap = (!swap);
    GLB_Set_Flash_IO_PARM(sel_embedded, swap);
    qcc74x_sf_ctrl_select_pad(sel);

    if (sel <= SF_IO_EMB_SWAP_NONE_DUAL_IO0) {
        /* Embedded pad1 io delay set */
        qcc74x_sf_ctrl_set_io_delay(SF_CTRL_PAD1, p_sf_ctrl_cfg->do_delay, p_sf_ctrl_cfg->di_delay, p_sf_ctrl_cfg->oe_delay);
    } else if (sel <= SF_IO_EXT_SF2) {
        /* Pad2 or pad3 io delay set */
        qcc74x_sf_ctrl_set_io_delay((sel >> 2), p_sf_ctrl_cfg->do_delay, p_sf_ctrl_cfg->di_delay, p_sf_ctrl_cfg->oe_delay);
    } else if (sel >= SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2 && sel <= SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
        /* Dual flash mode, embedded pad1 and pad2 io delay set */
        qcc74x_sf_ctrl_set_io_delay(SF_CTRL_PAD1, p_sf_ctrl_cfg->do_delay, p_sf_ctrl_cfg->di_delay, p_sf_ctrl_cfg->oe_delay);
        qcc74x_sf_ctrl_set_io_delay(SF_CTRL_PAD2, p_bank2_cfg->do_delay, p_bank2_cfg->di_delay, p_bank2_cfg->oe_delay);
    }

#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
    if (p_bank2_cfg != NULL) {
        if (p_bank2_cfg->sbus2_select) {
            if (sel >= SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2 && sel <= SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
                /* Default sbus2 replace opt flash2 */
                qcc74x_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
            }
        }
    }
#endif

    qcc74x_sflash_init(p_sf_ctrl_cfg, p_bank2_cfg);

    return SUCCESS;
}

#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
/****************************************************************************/ /**
 * @brief  SF Cfg system bus 2 flash init
 *
 * @param  sel: SF pin select
 * @param  p_bank2_cfg: Serial flash2 controller configuration pointer
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
__WEAK
int ATTR_TCM_SECTION qcc74x_sf_cfg_sbus2_flash_init(uint8_t sel, const struct sf_ctrl_bank2_cfg *p_bank2_cfg)
{
    if (sel < SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2 || sel > SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
        return ERROR;
    }

    /* Init flash2 gpio */
    if (sel & (1 << 2)) {
        qcc74x_sf_cfg_init_ext_flash_gpio(0);
    }

    /* Set remap for flash2 xip mode */
    qcc74x_sf_ctrl_remap_set(p_bank2_cfg->remap, p_bank2_cfg->remap_lock);

    /* Dual flash mode, pad2 io delay set */
    qcc74x_sf_ctrl_set_io_delay(SF_CTRL_PAD2, p_bank2_cfg->do_delay, p_bank2_cfg->di_delay, p_bank2_cfg->oe_delay);

    if (p_bank2_cfg->sbus2_select) {
        /* Default sbus2 replace opt flash2 */
        qcc74x_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
    }

    qcc74x_sflash_init(NULL, p_bank2_cfg);

    return SUCCESS;
}
#endif
#endif

/*@} end of group SF_CFG_Public_Functions */

/*@} end of group SF_CFG */
