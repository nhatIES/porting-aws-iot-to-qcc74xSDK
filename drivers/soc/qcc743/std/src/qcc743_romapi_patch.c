#include "qcc743_romapi_patch.h"
#include "qcc743_romdriver_e907.h"

/* WiFi PLL Config*/
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_32M_38P4M_40M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 0,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 0,        /*!< pll_icp_1u */
    .clkpllIcp5u = 2,        /*!< pll_icp_5u */
    .clkpllRz = 3,           /*!< pll_rz */
    .clkpllCz = 1,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 1,      /*!< pll_r4_short */
    .clkpllC4En = 0,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 1,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 1,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_24M = {
    .clkpllRefdivRatio = 1,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 0,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 0,        /*!< pll_icp_1u */
    .clkpllIcp5u = 2,        /*!< pll_icp_5u */
    .clkpllRz = 3,           /*!< pll_rz */
    .clkpllCz = 1,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 1,      /*!< pll_r4_short */
    .clkpllC4En = 0,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 1,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 1,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION wifiPllBasicCfg_26M = {
    .clkpllRefdivRatio = 1,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};

const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION wifiPllCfg_960M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 0 },                                 /*!< XTAL is None */
    { &wifiPllBasicCfg_24M, 0x1400000, 0 },           /*!< XTAL is 24M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1E00000, 0 }, /*!< XTAL is 32M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1900000, 0 }, /*!< XTAL is 38.4M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1800000, 0 }, /*!< XTAL is 40M */
    { &wifiPllBasicCfg_26M, 0x1276276, 0 },           /*!< XTAL is 26M */
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1E00000, 0 }, /*!< XTAL is RC32M */
};

const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION wifiPllCfg_960M_Fast[1] = {
    { &wifiPllBasicCfg_32M_38P4M_40M, 0x1800000, 0 }, /*!< XTAL is 40M */
};

/* Audio PLL Config*/
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPllBasicCfg_24M_26M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPllBasicCfg_32M_38P4M_40M = {
    .clkpllRefdivRatio = 4,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 3,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_491P52M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 20 },                                /*!< XTAL is None */
    { &audioPllBasicCfg_24M_26M, 0x147AE, 20 },       /*!< XTAL is 24M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1EB85, 20 }, /*!< XTAL is 32M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x19999, 20 }, /*!< XTAL is 38.4M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x18937, 20 }, /*!< XTAL is 40M */
    { &audioPllBasicCfg_24M_26M, 0x12E79, 20 },       /*!< XTAL is 26M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1EB85, 20 }, /*!< XTAL is RC32M */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_451P58M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 20 },                                /*!< XTAL is None */
    { &audioPllBasicCfg_24M_26M, 0x12D0D, 20 },       /*!< XTAL is 24M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1C394, 20 }, /*!< XTAL is 32M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x17851, 20 }, /*!< XTAL is 38.4M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x16943, 20 }, /*!< XTAL is 40M */
    { &audioPllBasicCfg_24M_26M, 0x115E5, 20 },       /*!< XTAL is 26M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x1C394, 20 }, /*!< XTAL is RC32M */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_400M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 8 },                                /*!< XTAL is None */
    { &audioPllBasicCfg_24M_26M, 0x10AAA, 8 },       /*!< XTAL is 24M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x19000, 8 }, /*!< XTAL is 32M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x14D55, 8 }, /*!< XTAL is 38.4M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x14000, 8 }, /*!< XTAL is 40M */
    { &audioPllBasicCfg_24M_26M, 0xF627, 8 },        /*!< XTAL is 26M */
    { &audioPllBasicCfg_32M_38P4M_40M, 0x19000, 8 }, /*!< XTAL is RC32M */
};

/* Audio PLL Config*/
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll384BasicCfg_24M_26M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll384BasicCfg_32M_38P4M_40M = {
    .clkpllRefdivRatio = 4,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 2,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_384M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 8 },                                   /*!< XTAL is None */
    { &audioPll384BasicCfg_24M_26M, 0x10000, 8 },       /*!< XTAL is 24M */
    { &audioPll384BasicCfg_32M_38P4M_40M, 0x18000, 8 }, /*!< XTAL is 32M */
    { &audioPll384BasicCfg_32M_38P4M_40M, 0x14000, 8 }, /*!< XTAL is 38.4M */
    { &audioPll384BasicCfg_32M_38P4M_40M, 0x13333, 8 }, /*!< XTAL is 40M */
    { &audioPll384BasicCfg_24M_26M, 0xEC4E, 8 },        /*!< XTAL is 26M */
    { &audioPll384BasicCfg_32M_38P4M_40M, 0x18000, 8 }, /*!< XTAL is RC32M */
};

/* Audio PLL Config*/
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll240BasicCfg_24M_26M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 0, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 0,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll240BasicCfg_32M_38P4M_40M = {
    .clkpllRefdivRatio = 4,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 0,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_240M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 8 },                                   /*!< XTAL is None */
    { &audioPll240BasicCfg_24M_26M, 0xA000, 8 },        /*!< XTAL is 24M */
    { &audioPll240BasicCfg_32M_38P4M_40M, 0xF000, 8 },  /*!< XTAL is 32M */
    { &audioPll240BasicCfg_32M_38P4M_40M, 0xC800, 8 },  /*!< XTAL is 38.4M */
    { &audioPll240BasicCfg_32M_38P4M_40M, 0xC000, 8 },  /*!< XTAL is 40M */
    { &audioPll240BasicCfg_24M_26M, 0x93B1, 8 },        /*!< XTAL is 26M */
    { &audioPll240BasicCfg_32M_38P4M_40M, 0xF000, 8 },  /*!< XTAL is RC32M */
};

/* Audio PLL Config*/
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll245P76BasicCfg_24M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 0,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll245P76BasicCfg_26M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 0, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 0,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION audioPll245P76BasicCfg_32M_38P4M_40M = {
    .clkpllRefdivRatio = 4,  /*!< pll_refdiv_ratio */
    .clkpllIntFracSw = 1,    /*!< pll_int_frac_sw */
    .clkpllIcp1u = 1,        /*!< pll_icp_1u */
    .clkpllIcp5u = 0,        /*!< pll_icp_5u */
    .clkpllRz = 5,           /*!< pll_rz */
    .clkpllCz = 2,           /*!< pll_cz */
    .clkpllC3 = 2,           /*!< pll_c3 */
    .clkpllR4Short = 0,      /*!< pll_r4_short */
    .clkpllC4En = 1,         /*!< pll_r4_en */
    .clkpllSelSampleClk = 1, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 0,     /*!< pll_vco_speed */
    .clkpllSdmCtrlHw = 0,    /*!< pll_sdm_ctrl_hw */
    .clkpllSdmBypass = 0,    /*!< pll_sdm_bypass */
};
const GLB_WA_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION audioPllCfg_245P76M[GLB_XTAL_MAX] = {
    { NULL, 0x0, 8 },                                       /*!< XTAL is None */
    { &audioPll245P76BasicCfg_24M, 0xA3D7, 8 },             /*!< XTAL is 24M */
    { &audioPll245P76BasicCfg_32M_38P4M_40M, 0xF5C2, 8 },   /*!< XTAL is 32M */
    { &audioPll245P76BasicCfg_32M_38P4M_40M, 0xCCCC, 8 },   /*!< XTAL is 38.4M */
    { &audioPll245P76BasicCfg_32M_38P4M_40M, 0xC49B, 8 },   /*!< XTAL is 40M */
    { &audioPll245P76BasicCfg_26M, 0x973C, 8 },             /*!< XTAL is 26M */
    { &audioPll245P76BasicCfg_32M_38P4M_40M, 0xF5C2, 8 },   /*!< XTAL is RC32M */
};

const GLB_SLAVE_GRP_0_TBL_Type ATTR_CLOCK_CONST_SECTION glb_slave_grp_0_table[GLB_SLAVE_GRP_0_MAX] = {
    { GLB_ADC_CFG0_OFFSET, GLB_GPADC_32M_DIV_EN_POS, GLB_GPADC_32M_CLK_SEL_POS, GLB_GPADC_32M_CLK_DIV_POS, GLB_GPADC_32M_DIV_EN_LEN, GLB_GPADC_32M_CLK_SEL_LEN, GLB_GPADC_32M_CLK_DIV_LEN },
    { GLB_IR_CFG0_OFFSET, GLB_IR_CLK_EN_POS, 0, GLB_IR_CLK_DIV_POS, GLB_IR_CLK_EN_LEN, 0, GLB_IR_CLK_DIV_LEN },
    { GLB_I2C_CFG0_OFFSET, GLB_I2C_CLK_EN_POS, GLB_I2C_CLK_SEL_POS, GLB_I2C_CLK_DIV_POS, GLB_I2C_CLK_EN_LEN, GLB_I2C_CLK_SEL_LEN, GLB_I2C_CLK_DIV_LEN },
    { GLB_SPI_CFG0_OFFSET, GLB_SPI_CLK_EN_POS, GLB_SPI_CLK_SEL_POS, GLB_SPI_CLK_DIV_POS, GLB_SPI_CLK_EN_LEN, GLB_SPI_CLK_SEL_LEN, GLB_SPI_CLK_DIV_LEN },
    { GLB_DBI_CFG0_OFFSET, GLB_DBI_CLK_EN_POS, GLB_DBI_CLK_SEL_POS, GLB_DBI_CLK_DIV_POS, GLB_DBI_CLK_EN_LEN, GLB_DBI_CLK_SEL_LEN, GLB_DBI_CLK_DIV_LEN },
    { GLB_AUDIO_CFG0_OFFSET, GLB_REG_AUDIO_AUTO_DIV_EN_POS, 0, 0, GLB_REG_AUDIO_AUTO_DIV_EN_LEN, 0, 0 },
    { GLB_AUDIO_CFG0_OFFSET, GLB_REG_AUDIO_ADC_CLK_EN_POS, 0, GLB_REG_AUDIO_ADC_CLK_DIV_POS, GLB_REG_AUDIO_ADC_CLK_EN_LEN, 0, GLB_REG_AUDIO_ADC_CLK_DIV_LEN },
    { GLB_AUDIO_CFG1_OFFSET, GLB_REG_AUDIO_SOLO_CLK_EN_POS, 0, GLB_REG_AUDIO_SOLO_CLK_DIV_POS, GLB_REG_AUDIO_SOLO_CLK_EN_LEN, 0, GLB_REG_AUDIO_SOLO_CLK_DIV_LEN },
    { GLB_CAM_CFG0_OFFSET, GLB_REG_CAM_REF_CLK_EN_POS, GLB_REG_CAM_REF_CLK_SRC_SEL_POS, GLB_REG_CAM_REF_CLK_DIV_POS, GLB_REG_CAM_REF_CLK_EN_LEN, GLB_REG_CAM_REF_CLK_SRC_SEL_LEN, GLB_REG_CAM_REF_CLK_DIV_LEN },
    { GLB_SDH_CFG0_OFFSET, GLB_REG_SDH_CLK_EN_POS, GLB_REG_SDH_CLK_SEL_POS, GLB_REG_SDH_CLK_DIV_POS, GLB_REG_SDH_CLK_EN_LEN, GLB_REG_SDH_CLK_SEL_LEN, GLB_REG_SDH_CLK_DIV_LEN },
    { GLB_PSRAM_CFG0_OFFSET, GLB_REG_PSRAMB_CLK_EN_POS, GLB_REG_PSRAMB_CLK_SEL_POS, GLB_REG_PSRAMB_CLK_DIV_POS, GLB_REG_PSRAMB_CLK_EN_LEN, GLB_REG_PSRAMB_CLK_SEL_LEN, GLB_REG_PSRAMB_CLK_DIV_LEN },
};

typedef struct
{
    uint32_t jedec_id;
    char *name;
    const spi_flash_cfg_type *cfg;
} Flash_Info_t;

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_GD_LQ64E = {
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
    .clk_invert = 0x3d,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
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
    .time_e_sector = 3000,
    .time_e_32k = 4000,
    .time_e_64k = 4000,
    .time_page_pgm = 5,
    .time_ce = 65 * 1000,
    .pd_delay = 3,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_GD_Q64E = {
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
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
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

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_Winb_16JV = {
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
    .clk_invert = 0x3d,

    .reset_en_cmd = 0x66,
    .reset_cmd = 0x99,
    .c_rexit = 0xff,
    .wr_enable_write_reg_len = 0x00,

    /*id*/
    .jedec_id_cmd = 0x9f,
    .jedec_id_cmd_dmy_clk = 0,
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
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
    .pd_delay = 20,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_Winb_64JV = {
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
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
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

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_Winb_256FV = {
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
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
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

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_Mxic_25U256 = {
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
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
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

static const ATTR_TCM_CONST_SECTION spi_flash_cfg_type flash_cfg_Puya_Q32H = {
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
    .enter_32bits_addr_cmd = 0xb7,
    .exit_32bits_addr_cmd = 0xe9,
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
    .pd_delay = 8,
    .qe_data = 0,
};

static const ATTR_TCM_CONST_SECTION Flash_Info_t flash_infos[] = {
    {
        .jedec_id = 0x1740ef,
        //.name="WB_64JV_64_33",
        .cfg = &flash_cfg_Winb_64JV,
    },
    {
        .jedec_id = 0x1940ef,
        //.name="WB_256FV_256_33",
        .cfg = &flash_cfg_Winb_256FV,
    },
    {
        .jedec_id = 0x1760ef,
        //.name="WB_64JW_64_18",
        .cfg = &flash_cfg_Winb_64JV,
    },
    {
        .jedec_id = 0x1570ef,
        //.name="WB_16JV_16_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x1740c8,
        //.name="GD_64E_64_33",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x1760c8,
        //.name="GD_LQ64E_64_18",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x1860c8,
        //.name="GD_LQ128E_128_18",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x1865C8,
        //.name="GD_WQ128E_128_1833",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x15345e,
        //.name="ZB_WQ16A_16_33",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x15405e,
        //.name="ZB_16B_16_33",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x16405e,
        //.name="ZB_32B_32_33",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x17405e,
        //.name="ZB_VQ64_64_33",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x18405e,
        //.name="ZB_VQ128_128_33",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x15605e,
        //.name="ZB_VQ16_16_33",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x3925c2,
        //.name="MX_U25643G_256_18",
        .cfg = &flash_cfg_Mxic_25U256,
    },
    {
        .jedec_id = 0x144020,
        //.name="XM_QH80_08_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x154020,
        //.name="XM_QH16_16_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x164020,
        //.name="XM_QH32_32_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x174020,
        //.name="XM_QH64_64_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x184020,
        //.name="XM_QH128C_128_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x165020,
        //.name="xm_lu32_32_18",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x174220,
        //.name="XM_QW64_64_1833",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x17400b,
        //.name="XT_F64B_64_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x18400b,
        //.name="xt_25f128b_128_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x176085,
        //.name="Puya_Q64H_64_33",
        .cfg = &flash_cfg_Puya_Q32H,
    },
    {
        .jedec_id = 0x186085,
        //.name="Puya_Q128H_128_33",
        .cfg = &flash_cfg_Puya_Q32H,
    },
    {
        .jedec_id = 0x142085,
        //.name="py25q80hb_80_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x152085,
        //.name="py25q16hb_16_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x162085,
        //.name="py25q32hb_32_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x172085,
        //.name="py25q64ha_64_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x182085,
        //.name="py25q128ha_128_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x192085,
        //.name="py25q256hb_256_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x1540a1,
        //.name="FM25Q_16A_16_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x1640a1,
        //.name="FM25Q_32_32_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x1740a1,
        //.name="FM25Q_64_64_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x1840a1,
        //.name="FM25Q_128_128_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x1828a1,
        //.name="FM25W_128_128_1833",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x1660c4,
        //.name="gt25q32_32_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x1560c4,
        //.name="gt25q16_16_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x1760c4,
        //.name="gt25q64_64_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
    {
        .jedec_id = 0x166125,
        //.name="sk25e032_32_33",
        .cfg = &flash_cfg_GD_LQ64E,
    },
    {
        .jedec_id = 0x1765C8,
        //.name="GD_WQ64E_64_1833",
        .cfg = &flash_cfg_GD_Q64E,
    },
    {
        .jedec_id = 0x1460c4,
        //.name="gt25q80_08_33",
        .cfg = &flash_cfg_Winb_16JV,
    },
};

//CLOCK
//EFUSE
//PDS

//FLASH
/****************************************************************************/ /**
 * @brief  Erase flash one 32K block
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  blk_num: flash 32K block number
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_sflash_blk32_erase(spi_flash_cfg_type *flash_cfg, uint32_t blk_num)
{
    uint32_t cnt = 0;
    uint8_t is_32bits_addr = 0;
    struct sf_ctrl_cmd_cfg_type flash_cmd;
    int stat = qcc74x_sflash_write_enable(flash_cfg);

    if (stat != 0) {
        return stat;
    }

    if (((uintptr_t)&flash_cmd) % 4 == 0) {
        ARCH_MemSet4((uint32_t *)&flash_cmd, 0, sizeof(flash_cmd) / 4);
    } else {
        ARCH_MemSet(&flash_cmd, 0, sizeof(flash_cmd));
    }

    is_32bits_addr = (flash_cfg->io_mode & 0x20);
    /* rw_flag don't care */
    flash_cmd.rw_flag = SF_CTRL_READ;
    flash_cmd.addr_size = 3;

    if (is_32bits_addr > 0) {
        flash_cmd.addr_size++;
        flash_cmd.cmd_buf[0] = (flash_cfg->blk32_erase_cmd << 24) | ((QCC74x_SPIFLASH_BLK32K_SIZE * blk_num) >> 8);
        flash_cmd.cmd_buf[1] = ((QCC74x_SPIFLASH_BLK32K_SIZE * blk_num) << 24);
    } else {
        flash_cmd.cmd_buf[0] = (flash_cfg->blk32_erase_cmd << 24) | (QCC74x_SPIFLASH_BLK32K_SIZE * blk_num);
    }

    qcc74x_sf_ctrl_sendcmd(&flash_cmd);

    while (SET == qcc74x_sflash_busy(flash_cfg)) {
        arch_delay_us(500);
        cnt++;

        if (cnt > flash_cfg->time_e_32k * 3) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  flash_cfg: Serial flash parameter configuration pointer
 * @param  start_addr: start address to erase
 * @param  end_addr: end address(include this address) to erase
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_sflash_erase(spi_flash_cfg_type *flash_cfg, uint32_t start_addr, uint32_t end_addr)
{
    uint32_t len = 0;
    uint32_t erase_len = 0;
    int ret = 0;

    if (start_addr > end_addr) {
        return -1;
    }

    while (start_addr <= end_addr) {
        len = end_addr - start_addr + 1;

        if (flash_cfg->blk64_erase_cmd != QCC74x_SPIFLASH_CMD_INVALID &&
            (start_addr & (QCC74x_SPIFLASH_BLK64K_SIZE - 1)) == 0 &&
            len > (QCC74x_SPIFLASH_BLK64K_SIZE - flash_cfg->sector_size * 1024)) {
            /* 64K margin address,and length > 64K-sector size, erase one first */
            ret = qcc74x_sflash_blk64_erase(flash_cfg, start_addr / QCC74x_SPIFLASH_BLK64K_SIZE);
            erase_len = QCC74x_SPIFLASH_BLK64K_SIZE;
        } else if (flash_cfg->blk32_erase_cmd != QCC74x_SPIFLASH_CMD_INVALID &&
                   (start_addr & (QCC74x_SPIFLASH_BLK32K_SIZE - 1)) == 0 &&
                   len > (QCC74x_SPIFLASH_BLK32K_SIZE - flash_cfg->sector_size * 1024)) {
            /* 32K margin address,and length > 32K-sector size, erase one first */
            ret = qcc74x_sflash_blk32_erase(flash_cfg, start_addr / QCC74x_SPIFLASH_BLK32K_SIZE);
            erase_len = QCC74x_SPIFLASH_BLK32K_SIZE;
        } else {
            /* Sector erase */
            start_addr = ((start_addr) & (~(flash_cfg->sector_size * 1024 - 1)));
            ret = qcc74x_sflash_sector_erase(flash_cfg, start_addr / flash_cfg->sector_size / 1024);
            erase_len = flash_cfg->sector_size * 1024;
        }

        start_addr += erase_len;

        if (ret != 0) {
            return -1;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Clear flash status register
 *
 * @param  flash_cfg: Flash configuration pointer
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_SFlash_Clear_Status_Register(spi_flash_cfg_type *flash_cfg)
{
    uint32_t ret = 0;
    uint32_t qe_value = 0;
    uint32_t reg_value = 0;
    uint32_t read_value = 0;
    uint8_t read_reg_value0 = 0;
    uint8_t read_reg_value1 = 0;

    if ((flash_cfg->io_mode & 0xf) == SF_CTRL_QO_MODE || (flash_cfg->io_mode & 0xf) == SF_CTRL_QIO_MODE) {
        qe_value = 1;
    }

    qcc74x_sflash_read_reg(flash_cfg, 0, (uint8_t *)&read_reg_value0, 1);
    qcc74x_sflash_read_reg(flash_cfg, 1, (uint8_t *)&read_reg_value1, 1);
    read_value = (read_reg_value0 | (read_reg_value1 << 8));
    if ((read_value & (~((1 << (flash_cfg->qe_index * 8 + flash_cfg->qe_bit)) |
                         (1 << (flash_cfg->busy_index * 8 + flash_cfg->busy_bit)) |
                         (1 << (flash_cfg->wr_enable_index * 8 + flash_cfg->wr_enable_bit))))) == 0) {
        return 0;
    }

    ret = qcc74x_sflash_write_enable(flash_cfg);
    if (0 != ret) {
        return -1;
    }
    if (flash_cfg->qe_write_reg_len == 2) {
        reg_value = (qe_value << (flash_cfg->qe_index * 8 + flash_cfg->qe_bit));
        qcc74x_sflash_write_reg(flash_cfg, 0, (uint8_t *)&reg_value, 2);
    } else {
        if (flash_cfg->qe_index == 0) {
            reg_value = (qe_value << flash_cfg->qe_bit);
        } else {
            reg_value = 0;
        }
        qcc74x_sflash_write_reg(flash_cfg, 0, (uint8_t *)&reg_value, 1);
        ret = qcc74x_sflash_write_enable(flash_cfg);
        if (SUCCESS != ret) {
            return -1;
        }
        if (flash_cfg->qe_index == 1) {
            reg_value = (qe_value << flash_cfg->qe_bit);
        } else {
            reg_value = 0;
        }
        qcc74x_sflash_write_reg(flash_cfg, 1, (uint8_t *)&reg_value, 1);
    }
    return 0;
}

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
int ATTR_TCM_SECTION qcc74x_sf_cfg_get_flash_cfg_need_lock_ext(uint32_t flash_id, spi_flash_cfg_type *p_flash_cfg,
                                                             uint8_t group, uint8_t bank)
{
    uint32_t i;
    uint8_t buf[sizeof(spi_flash_cfg_type) + 8];
    uint32_t crc, *p_crc;
    uint32_t xip_offset;
    char flash_cfg_magic[] = "FCFG";

    if (flash_id == 0) {
        xip_offset = qcc74x_sf_ctrl_get_flash_image_offset(group, bank);
        qcc74x_sf_ctrl_set_flash_image_offset(0, group, bank);
        qcc74x_xip_sflash_read_via_cache_need_lock(8 + QCC743_FLASH_XIP_BASE, buf, sizeof(spi_flash_cfg_type) + 8, group, bank);
        qcc74x_sf_ctrl_set_flash_image_offset(xip_offset, group, bank);

        if (ARCH_MemCmp(buf, flash_cfg_magic, 4) == 0) {
            crc = QCC74x_Soft_CRC32((uint8_t *)buf + 4, sizeof(spi_flash_cfg_type));
            p_crc = (uint32_t *)(buf + 4 + sizeof(spi_flash_cfg_type));

            if (*p_crc == crc) {
                arch_memcpy_fast(p_flash_cfg, (uint8_t *)buf + 4, sizeof(spi_flash_cfg_type));
                return 0;
            }
        }
    } else {
        if (RomDriver_SF_Cfg_Get_Flash_Cfg_Need_Lock(flash_id, p_flash_cfg) == 0) {
            return 0;
        }
        for (i = 0; i < sizeof(flash_infos) / sizeof(flash_infos[0]); i++) {
            if (flash_infos[i].jedec_id == flash_id) {
                arch_memcpy_fast(p_flash_cfg, flash_infos[i].cfg, sizeof(spi_flash_cfg_type));
                return 0;
            }
        }
    }

    return -1;
}

/****************************************************************************/ /**
 * @brief  Identify one flash patch
 *
 * @param  call_from_flash: code run at flash or ram
 * @param  flash_pin_cfg: Bit 7: autoscan, Bit6-0: flash GPIO config
 * @param  restore_default: Wether restore default flash GPIO config
 * @param  p_flash_cfg: Flash config pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return Flash ID
 *
*******************************************************************************/
uint32_t ATTR_TCM_SECTION qcc74x_sf_cfg_flash_identify_ext(uint8_t call_from_flash, uint8_t flash_pin_cfg,
                                                         uint8_t restore_default, spi_flash_cfg_type *p_flash_cfg, uint8_t group, uint8_t bank)
{
    uint32_t jedec_id = 0;
    uint32_t i = 0;
    uint32_t ret = 0;

    ret = qcc74x_sf_cfg_flash_identify(call_from_flash, flash_pin_cfg, restore_default, p_flash_cfg, group, bank);
    if (call_from_flash) {
        qcc74x_sflash_set_xip_cfg(p_flash_cfg, p_flash_cfg->io_mode & 0xf, 1, 0, 32, bank);
    }
    if ((ret & QCC74x_FLASH_ID_VALID_FLAG) != 0) {
        return ret;
    }

    jedec_id = (ret & 0xffffff);
    for (i = 0; i < sizeof(flash_infos) / sizeof(flash_infos[0]); i++) {
        if (flash_infos[i].jedec_id == jedec_id) {
            arch_memcpy_fast(p_flash_cfg, flash_infos[i].cfg, sizeof(spi_flash_cfg_type));
            break;
        }
    }
    if (i == sizeof(flash_infos) / sizeof(flash_infos[0])) {
        return jedec_id;
    } else {
        return (jedec_id | QCC74x_FLASH_ID_VALID_FLAG);
    }
}

/****************************************************************************/ /**
 * @brief  Read data from flash via XIP
 *
 * @param  addr: flash read start address
 * @param  data: data pointer to store data read from flash
 * @param  len: data length to read
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_xip_sflash_read_via_cache_need_lock(uint32_t addr, uint8_t *data, uint32_t len,
                                                              uint8_t group, uint8_t bank)
{
    uint32_t offset;

    addr = addr & (QCC743_FLASH_XIP_END - QCC743_FLASH_XIP_BASE - 1);
    addr |= QCC743_FLASH_XIP_BASE;

    offset = qcc74x_sf_ctrl_get_flash_image_offset(group, bank);
    qcc74x_sf_ctrl_set_flash_image_offset(0, group, bank);
    /* Flash read */
    arch_memcpy_fast(data, (void *)(uintptr_t)(addr - qcc74x_sf_ctrl_get_flash_image_offset(group, bank)), len);
    qcc74x_sf_ctrl_set_flash_image_offset(offset, group, bank);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Save flash controller state
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  offset: CPU XIP flash offset pointer
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_xip_sflash_state_save(spi_flash_cfg_type *p_flash_cfg, uint32_t *offset,
                                                uint8_t group, uint8_t bank)
{
    /* XIP_SFlash_Delay */
    volatile uint32_t i = 32 * 2;

    while (i--)
        ;

#ifdef QCC74x_SF_CTRL_SBUS2_ENABLE
    if (bank == SF_CTRL_FLASH_BANK1) {
        qcc74x_sf_ctrl_sbus2_replace(SF_CTRL_PAD2);
    }
#endif
    qcc74x_sf_ctrl_set_owner(SF_CTRL_OWNER_SAHB);
    /* Exit form continous read for accepting command */
    qcc74x_sflash_reset_continue_read(p_flash_cfg);
    /* For disable command that is setting register instaed of send command, we need write enable */
    qcc74x_sflash_disable_burst_wrap(p_flash_cfg);
    /* Enable 32Bits addr mode again in case reset command make it reset */
    qcc74x_sflash_set_32bits_addr_mode(p_flash_cfg, 1);
    if ((p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QO_MODE || (p_flash_cfg->io_mode & 0x0f) == SF_CTRL_QIO_MODE) {
        /* Enable QE again in case reset command make it reset */
        qcc74x_sflash_qspi_enable(p_flash_cfg);
    }
    /* Deburst again to make sure */
    qcc74x_sflash_disable_burst_wrap(p_flash_cfg);

    /* Clear offset setting*/
    *offset = qcc74x_sf_ctrl_get_flash_image_offset(group, bank);
    qcc74x_sf_ctrl_set_flash_image_offset(0, group, bank);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Erase flash one region
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  start_addr: start address to erase
 * @param  len: data length to erase
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_xip_sflash_erase_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t start_addr,
                                                     int len, uint8_t group, uint8_t bank)
{
    int stat;
    uint32_t offset;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    qcc74x_xip_sflash_opt_enter(&aes_enable);
    stat = qcc74x_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        qcc74x_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat = qcc74x_sflash_erase(p_flash_cfg, start_addr, start_addr + len - 1);
        qcc74x_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    qcc74x_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Program flash one region
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  addr: start address to be programed
 * @param  data: data pointer to be programed
 * @param  len: data length to be programed
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_xip_sflash_write_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *data,
                                                     uint32_t len, uint8_t group, uint8_t bank)
{
    int stat;
    uint32_t offset;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    qcc74x_xip_sflash_opt_enter(&aes_enable);
    stat = qcc74x_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        qcc74x_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat = qcc74x_sflash_program(p_flash_cfg, io_mode, addr, data, len);
        qcc74x_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    qcc74x_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Read data from flash
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  addr: flash read start address
 * @param  data: data pointer to store data read from flash
 * @param  len: data length to read
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_xip_sflash_read_need_lock(spi_flash_cfg_type *p_flash_cfg, uint32_t addr, uint8_t *data,
                                                    uint32_t len, uint8_t group, uint8_t bank)
{
    int stat;
    uint32_t offset;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    qcc74x_xip_sflash_opt_enter(&aes_enable);
    stat = qcc74x_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        qcc74x_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        stat = qcc74x_sflash_read(p_flash_cfg, io_mode, 0, addr, data, len);
        qcc74x_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    qcc74x_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Get Flash Jedec ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  data: data pointer to store Jedec ID Read from flash
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_xip_sflash_getjedecid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data,
                                                          uint8_t group, uint8_t bank)
{
    int stat;
    uint32_t offset;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    qcc74x_xip_sflash_opt_enter(&aes_enable);
    stat = qcc74x_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        qcc74x_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        qcc74x_sflash_get_jedecid(p_flash_cfg, data);
        qcc74x_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    qcc74x_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Get Flash Device ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  is_32bits_addr: Is flash addr mode in 32-bits
 * @param  data: data pointer to store Device ID Read from flash
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_xip_sflash_getdeviceid_need_lock(spi_flash_cfg_type *p_flash_cfg, QCC74x_Fun_Type is_32bits_addr,
                                                           uint8_t *data, uint8_t group, uint8_t bank)
{
    int stat;
    uint32_t offset;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    qcc74x_xip_sflash_opt_enter(&aes_enable);
    stat = qcc74x_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != 0) {
        qcc74x_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        qcc74x_sflash_get_deviceid(data, is_32bits_addr);
        qcc74x_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    qcc74x_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  Get Flash Unique ID
 *
 * @param  p_flash_cfg: Flash config pointer
 * @param  data: data pointer to store Device ID Read from flash
 * @param  idLen: Unique id len
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return QCC74x_RET:0 means success and other value means error
 *
*******************************************************************************/
int ATTR_TCM_SECTION qcc74x_xip_sflash_getuniqueid_need_lock(spi_flash_cfg_type *p_flash_cfg, uint8_t *data,
                                                           uint8_t idLen, uint8_t group, uint8_t bank)
{
    int stat;
    uint32_t offset;
    uint8_t aes_enable = 0;
    uint8_t io_mode = p_flash_cfg->io_mode & 0xf;

    qcc74x_xip_sflash_opt_enter(&aes_enable);
    stat = qcc74x_xip_sflash_state_save(p_flash_cfg, &offset, group, bank);

    if (stat != SUCCESS) {
        qcc74x_sflash_set_xip_cfg(p_flash_cfg, io_mode, 1, 0, 32, bank);
    } else {
        qcc74x_sflash_get_uniqueid(data, idLen);
        qcc74x_xip_sflash_state_restore(p_flash_cfg, offset, group, bank);
    }

    qcc74x_xip_sflash_opt_exit(aes_enable);

    return stat;
}

/****************************************************************************/ /**
 * @brief  reconfigure WIFIPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Config_WIFI_PLL(uint8_t xtalType, const GLB_WA_PLL_Cfg_Type *pllCfgList)
{
    uint8_t refClk;

    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }

    GLB_Power_Off_WIFIPLL();
    GLB_WIFIPLL_Ref_Clk_Sel(refClk);
    GLB_Power_On_WIFIPLL(&(pllCfgList[xtalType]), 1);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure AUPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL(uint8_t xtalType, const GLB_WA_PLL_Cfg_Type *pllCfgList)
{
    uint8_t refClk;

    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }

    GLB_Power_Off_AUPLL();
    GLB_AUPLL_Ref_Clk_Sel(refClk);
    GLB_Power_On_AUPLL(&(pllCfgList[xtalType]), 1);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 384M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_384M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType = GLB_XTAL_NONE;

    /* we take 384M for CPU use,so set LDO to 1.2V*/
    HBN_Set_Ldo11_All_Vout(HBN_LDO_LEVEL_1P20V);
    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((uint8_t)xtalType, audioPllCfg_384M);
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 400M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_400M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType = GLB_XTAL_NONE;

    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((uint8_t)xtalType, audioPllCfg_400M);
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 451P58M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_451P58M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType = GLB_XTAL_NONE;

    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((uint8_t)xtalType, audioPllCfg_451P58M);
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 491P52M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_491P52M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType = GLB_XTAL_NONE;

    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((uint8_t)xtalType, audioPllCfg_491P52M);
}

/****************************************************************************/ /**
 * @brief  chip clock out0 select
 *
 * @param  clkOutType: chip clock out0 output type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_Chip_Clock_Out0_Sel(uint8_t clkOutType)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    /* set clk out0 output enable */
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_0_EN, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_0_SEL, clkOutType);
    QCC74x_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  chip clock out1 select
 *
 * @param  clkOutType: chip clock out1 output type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_Chip_Clock_Out1_Sel(uint8_t clkOutType)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    /* set clk out1 output enable */
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_1_EN, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_1_SEL, clkOutType);
    QCC74x_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  chip clock out2 select
 *
 * @param  clkOutType: chip clock out2 output type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_Chip_Clock_Out2_Sel(uint8_t clkOutType)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    /* set clk out2 output enable */
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_2_EN, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_2_SEL, clkOutType);
    QCC74x_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  chip clock out3 select
 *
 * @param  clkOutType: chip clock out3 output type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_Chip_Clock_Out3_Sel(uint8_t clkOutType)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_DIG_CLK_CFG2);
    /* set clk out3 output enable */
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_3_EN, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CHIP_CLK_OUT_3_SEL, clkOutType);
    QCC74x_WR_REG(GLB_BASE, GLB_DIG_CLK_CFG2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set flash id value
 *
 * @param  idValue: flash id value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION GLB_Set_Flash_Id_Value(uint32_t idValue)
{
    QCC74x_WR_REG(GLB_BASE, GLB_HW_RSV1, ((idValue&0xFFFFFF)|0x5A000000));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get flash id value
 *
 * @param  None
 *
 * @return flash id
 *
*******************************************************************************/
uint32_t ATTR_TCM_SECTION GLB_Get_Flash_Id_Value(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_HW_RSV1);
    if ((tmpVal&0x7F000000) == 0x5A000000) {
        return (tmpVal&0x00FFFFFF);
    }

    return 0x00000000;
}

/****************************************************************************/ /**
 * @brief  power down LDO18IO vout
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION GLB_Power_Down_Ldo18ioVout(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_LDO18IO);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_PU_LDO18IO);
    QCC74x_WR_REG(GLB_BASE, GLB_LDO18IO, tmpVal);
}


/****************************************************************************/ /**
 * @brief  GLB GET Package Type From EFUSE
 *
 * @param  None
 *
 * @return Package Type
 *
*******************************************************************************/
uint8_t ATTR_TCM_SECTION GLB_Get_Package_Type(void)
{
    uint32_t tmpVal = 0;
    uint8_t package_type = 0;

    /* get device_info[1:0] from efuse */
    tmpVal = QCC74x_RD_REG(EF_DATA_BASE, EF_DATA_EF_WIFI_MAC_HIGH);

    package_type = (uint8_t)((tmpVal >> 22) & 0x3);

    return package_type;
}

/****************************************************************************/ /**
 * @brief  GLB GET Status of PAD Bonging to GND
 *
 * @param  None
 *
 * @return status of pad bonding to GND
 *
*******************************************************************************/
QCC74x_Sts_Type ATTR_TCM_SECTION GLB_Get_PAD_Bonging_to_GND_Sts(void)
{
    uint32_t tmpVal = 0;
    uint8_t package_cfg = 0;

    /* get package_cfg[2:0] from efuse */
    tmpVal = QCC74x_RD_REG(EF_DATA_BASE, EF_DATA_EF_KEY_SLOT_10_W0);

    package_cfg = (uint8_t)((tmpVal >> 28) & 0x7);

    if (0 == package_cfg) {
        return RESET;
    } else {
        return SET;
    }
}

/****************************************************************************/ /**
 * @brief  GLB GPIO CHECK PAD Whether Lead Out no not
 *
 * @param  None
 *
 * @return RESET or SET
 *
*******************************************************************************/
QCC74x_Sts_Type ATTR_TCM_SECTION GLB_GPIO_Pad_LeadOut_Sts(uint8_t gpioPin)
{
    uint8_t package_type;

    package_type = GLB_Get_Package_Type();

    if ( GLB_PACKAGE_TYPE_QFN56 == package_type ){
        return SET;
    }

    /* */
    if ((( gpioPin >= GLB_GPIO_PIN_0) && (gpioPin < GLB_GPIO_PIN_4))
    || (( gpioPin > GLB_GPIO_PIN_9) && (gpioPin < GLB_GPIO_PIN_18))
    || (( gpioPin > GLB_GPIO_PIN_19) && (gpioPin < GLB_GPIO_PIN_23))
    || (( gpioPin > GLB_GPIO_PIN_26) && (gpioPin < GLB_GPIO_PIN_31))) {
        return SET;
    }

    return RESET;

}

/****************************************************************************/ /**
 * @brief  set gpio pad pull type in pds
 *
 * @param  pad: gpio type
 * @param  pu: power up
 * @param  pd: power down
 * @param  ie: Active IE (interrupt)
 *
 * @return SUCCESS or ERROR
 *
 * @note   Pu and Pd not depend on IE
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION PDS_Set_GPIO_Pad_Pn_Pu_Pd_Ie(uint8_t grp, uint8_t pu, uint8_t pd, uint8_t ie)
{
    uint32_t tmpVal;
    uint32_t tmpValPu;
    uint32_t tmpValPd;
    uint32_t tmpValIe;

    CHECK_PARAM(IS_PDS_GPIO_GROUP_SET_TYPE(grp));

    /* pu/pd/ie config */
    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_GPIO_I_SET);
    tmpValPu = QCC74x_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_PU_SET);
    if (pu) {
        if (GLB_PACKAGE_TYPE_QFN56 != GLB_Get_Package_Type()) {
            if (SET == GLB_Get_PAD_Bonging_to_GND_Sts()) {
                /* IF it is 40 PACKAGE TYPE and PAD Bonging to GND, Pull-UP is forbidden */
                tmpValPu &= ~(1 << grp);
            } else {
                tmpValPu |= (1 << grp);
            }
        } else {
            tmpValPu |= (1 << grp);
        }
    } else {
        tmpValPu &= ~(1 << grp);
    }
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_PU_SET, tmpValPu);
    tmpValPd = QCC74x_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_PD_SET);
    if (pd) {
        tmpValPd |= (1 << grp);
    } else {
        tmpValPd &= ~(1 << grp);
    }
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_PD_SET, tmpValPd);
    tmpValIe = QCC74x_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_IE_SET);
    if (ie) {
        tmpValIe |= (1 << grp);
    } else {
        tmpValIe &= ~(1 << grp);
    }
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_IE_SET, tmpValIe);
    QCC74x_WR_REG(PDS_BASE, PDS_GPIO_I_SET, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable PDS power on PLL
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION PDS_Pu_PLL_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, PDS_CR_PDS_PU_CLKPLL_SFREG);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, PDS_CR_PDS_PU_CLKPLL);
    QCC74x_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable PDS power on PLL
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION PDS_Pu_PLL_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_PU_CLKPLL_SFREG);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_PU_CLKPLL);
    QCC74x_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable power down sleep
 *
 * @param  cfg: power down sleep configuration 1
 * @param  cfg4: power down sleep configuration 2
 * @param  pdsSleepCnt: power down sleep count cycle
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION PDS_Enable(PDS_CTL_Type *cfg, PDS_CTL4_Type *cfg4, uint32_t pdsSleepCnt)
{
    uint32_t tmpVal = 0;
    /* sleepForever set 1, chip will sleep forever */
    /* PDS sleep time 1~PDS_WARMUP_LATENCY_CNT <=> error */
    /* PDS sleep time >PDS_WARMUP_LATENCY_CNT <=> correct */
    if ((pdsSleepCnt) && (pdsSleepCnt <= PDS_WARMUP_LATENCY_CNT)) {
        return ERROR;
    } else if (pdsSleepCnt > PDS_WARMUP_LATENCY_CNT) {
        QCC74x_WR_REG(PDS_BASE, PDS_TIME1, pdsSleepCnt - PDS_WARMUP_LATENCY_CNT);
    } else {
    }

    /* PDS_CTL4 config */
    QCC74x_WR_REG(PDS_BASE, PDS_CTL4, *(uint32_t *)cfg4);

    /* PDS_CTL config */
    if (cfg->pdsStart) {
        /* clear pds int */
        tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_INT);
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, PDS_CR_PDS_INT_CLR);
        QCC74x_WR_REG(PDS_BASE, PDS_INT, tmpVal);

        tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_INT);
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_INT_CLR);
        QCC74x_WR_REG(PDS_BASE, PDS_INT, tmpVal);

        QCC74x_WR_REG(PDS_BASE, PDS_CTL, (*(uint32_t *)cfg & ~(1 << 0)));
        QCC74x_WR_REG(PDS_BASE, PDS_CTL, (*(uint32_t *)cfg | (1 << 0)));
    } else {
        QCC74x_WR_REG(PDS_BASE, PDS_CTL, *(uint32_t *)cfg);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power down sleep force configure
 *
 * @param  defaultLvCfg: power down sleep default level configuration
 * @param  ramCfg: ram configuration
 * @param  pdsSleepCnt: power down sleep time count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION PDS_Default_Level_Config(PDS_DEFAULT_LV_CFG_Type *defaultLvCfg, uint32_t pdsSleepCnt)
{
    PDS_Force_Config((PDS_CTL2_Type *)&(defaultLvCfg->pdsCtl2), (PDS_CTL3_Type *)&(defaultLvCfg->pdsCtl3), (PDS_CTL5_Type *)&(defaultLvCfg->pdsCtl5));
    PDS_Enable((PDS_CTL_Type *)&(defaultLvCfg->pdsCtl), (PDS_CTL4_Type *)&(defaultLvCfg->pdsCtl4), pdsSleepCnt);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  USB Ctrl Register Reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type PDS_Reset_Low_Power_USB_Ctrl(void)
{
    uint32_t tmpVal = 0;

    /* 2000E000[19]    = 0 */
    /* 2000E00C[18:17] = 0 */
    /* 2000E014[29]    = 0 */
    /* 2000E018[21:20] = 0 */
    /* 2000E024[8]     = 0 */

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_CTL);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_CTRL_USBPLL_PD);
    QCC74x_WR_REG(PDS_BASE, PDS_CTL, tmpVal);

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_INT);
    tmpVal &= ~(0x3<<17);
    QCC74x_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_CTL3);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_USB_ISO_EN);
    QCC74x_WR_REG(PDS_BASE, PDS_CTL3, tmpVal);

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_CTL4);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_USB_PWR_OFF);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_USB_RESET);
    QCC74x_WR_REG(PDS_BASE, PDS_CTL4, tmpVal);

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_CTL5);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_CTRL_USB33);
    QCC74x_WR_REG(PDS_BASE, PDS_CTL5, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get Xtal value
 *
 * @param  xtalVal:Xtal value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION HBN_Get_Xtal_Value(uint32_t *xtalVal)
{
    uint32_t tmpVal = 0;
    uint8_t xtalType = 0;

    if (NULL == xtalVal) {
        return ERROR;
    }

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_RSV3);
    if (HBN_XTAL_FLAG_VALUE == QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_XTAL_STS)) {
        xtalType = QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_XTAL_TYPE);
        switch (xtalType) {
            case GLB_XTAL_NONE:
                *xtalVal = 0;
                break;
            case GLB_XTAL_24M:
                *xtalVal = 24000000;
                break;
            case GLB_XTAL_32M:
                *xtalVal = 32000000;
                break;
            case GLB_XTAL_38P4M:
                *xtalVal = 38400000;
                break;
            case GLB_XTAL_40M:
                *xtalVal = 40000000;
                break;
            case GLB_XTAL_26M:
                *xtalVal = 26000000;
                break;
            case GLB_XTAL_RC32M:
                *xtalVal = 32000000;
                break;
            default:
                *xtalVal = 0;
                break;
        }
        return SUCCESS;
    }

    *xtalVal = 0;
    return ERROR;
}

/****************************************************************************/ /**
 * @brief  HBN enable ACOMP interrupt
 *
 * @param  acompId: HBN Acomp ID
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Enable_AComp_IRQ(uint8_t acompId, uint8_t edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_AON_ACOMP_ID_TYPE(acompId));
    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    if (acompId == AON_ACOMP0_ID) {
        tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
        tmpVal2 = QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN);
        tmpVal2 = tmpVal2 | edge;
        tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN, tmpVal2);
        QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);
    } else if (acompId == AON_ACOMP1_ID) {
        tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
        tmpVal2 = QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN);
        tmpVal2 = tmpVal2 | edge;
        tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN, tmpVal2);
        QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable ACOMP interrupt
 *
 * @param  acompId: HBN Acomp ID
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Disable_AComp_IRQ(uint8_t acompId, uint8_t edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_AON_ACOMP_ID_TYPE(acompId));
    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    if (acompId == (uint8_t)AON_ACOMP0_ID) {
        tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
        tmpVal2 = QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN);
        tmpVal2 = tmpVal2 & (~edge);
        tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN, tmpVal2);
        QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);
    } else if (acompId == (uint8_t)AON_ACOMP1_ID) {
        tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
        tmpVal2 = QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN);
        tmpVal2 = tmpVal2 & (~edge);
        tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN, tmpVal2);
        QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN select 32K
 *
 * @param  clkType: HBN 32k clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION HBN_32K_Sel(uint8_t clkType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_HBN_32K_CLK_TYPE(clkType));

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_F32K_SEL, clkType);
    QCC74x_WR_REG(HBN_BASE, HBN_GLB, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set ADC clock
 *
 * @param  enable: enable frequency divider or not
 * @param  clkSel: ADC clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_ADC_CLK(uint8_t enable, uint8_t clkSel, uint8_t div)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_ADC_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3F));

    /* disable ADC clock first */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_ADC_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_ADC_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_ADC_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_GPADC_32M_CLK_DIV, div);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_GPADC_32M_CLK_SEL, clkSel);
    QCC74x_WR_REG(GLB_BASE, GLB_ADC_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_ADC_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_GPADC_32M_DIV_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_ADC_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set IR clock divider
 *
 * @param  enable: enable or disable IR clock
 * @param  clkSel: IR clock type
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_IR_CLK(uint8_t enable, uint8_t clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_IR_CLK_SRC_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3F));

    (void)clkSel;

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_IR_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_IR_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_IR_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_IR_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_IR_CLK_DIV, div);
    QCC74x_WR_REG(GLB_BASE, GLB_IR_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_IR_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_IR_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_IR_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_IR_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set I2C clock
 *
 * @param  enable: Enable or disable I2C clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_I2C_CLK(uint8_t enable, uint8_t clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_I2C_CLK_TYPE(clkSel));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_I2C_CLK_SEL, clkSel);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_I2C_CLK_DIV, div);
    QCC74x_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set SPI clock
 *
 * @param  enable: Enable or disable SPI clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_SPI_CLK(uint8_t enable, uint8_t clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_SPI_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x1F));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_SPI_CLK_DIV, div);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_SPI_CLK_SEL, clkSel);
    QCC74x_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set DBI clock
 *
 * @param  enable: Enable or disable DBI clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_DBI_CLK(uint8_t enable, uint8_t clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DBI_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x1F));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_DBI_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_DBI_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_DBI_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_DBI_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_DBI_CLK_DIV, div);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_DBI_CLK_SEL, clkSel);
    QCC74x_WR_REG(GLB_BASE, GLB_DBI_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_DBI_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_DBI_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_DBI_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_DBI_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set audio auto clock
 *
 * @param  divEn: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_Audio_AUTO_CLK(uint8_t divEn)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    if (divEn) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_AUTO_DIV_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_AUTO_DIV_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set audio ADC clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_Audio_ADC_CLK(uint8_t enable, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0x3F));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_ADC_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_AUDIO_ADC_CLK_DIV, div);
    QCC74x_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_AUDIO_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_ADC_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_ADC_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_AUDIO_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set audio SOLO clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: divider
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_Audio_SOLO_CLK(uint8_t enable, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((div <= 0xFF));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_SOLO_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_AUDIO_SOLO_CLK_DIV, div);
    QCC74x_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_AUDIO_CFG1);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_REG_AUDIO_SOLO_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_AUDIO_SOLO_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_AUDIO_CFG1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set CAM clock
 *
 * @param  enable: Enable or disable CAM clock
 * @param  clkSel: CAM clock type
 * @param  div: clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_CAM_CLK(uint8_t enable, uint8_t clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_CAM_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_CAM_REF_CLK_SRC_SEL, clkSel);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_CAM_REF_CLK_DIV, div);
    QCC74x_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set SDH clock
 *
 * @param  enable: Enable or disable
 * @param  clkSel: SDH clock type
 * @param  div: clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_SDH_CLK(uint8_t enable, uint8_t clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_SDH_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x7));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SDH_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_SDH_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_SDH_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SDH_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_SDH_CLK_SEL, clkSel);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_SDH_CLK_DIV, div);
    QCC74x_WR_REG(GLB_BASE, GLB_SDH_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SDH_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_REG_SDH_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_SDH_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_SDH_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set PSRAMB clock
 *
 * @param  enable: Enable or disable
 * @param  clkSel: PSRAMB clock type
 * @param  div: clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_Set_PSRAMB_CLK_Sel(uint8_t enable, uint8_t clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_PSRAMB_PLL_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_PSRAM_CFG0);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_PSRAMB_CLK_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_PSRAM_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_PSRAM_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_PSRAMB_CLK_SEL, clkSel);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_PSRAMB_CLK_DIV, div);
    QCC74x_WR_REG(GLB_BASE, GLB_PSRAM_CFG0, tmpVal);

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_PSRAM_CFG0);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_REG_PSRAMB_CLK_EN);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, GLB_REG_PSRAMB_CLK_EN);
    }
    QCC74x_WR_REG(GLB_BASE, GLB_PSRAM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enter HBN
 *
 * @param  cfg: HBN APP Config
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION HBN_Mode_Enter(HBN_APP_CFG_Type *cfg)
{
    uint32_t valLow = 0, valHigh = 0;
    uint64_t val;

    if (cfg->useXtal32k) {
        HBN_32K_Sel(HBN_32K_XTAL);
    } else {
        HBN_32K_Sel(HBN_32K_RC);
        HBN_Power_Off_Xtal_32K();
    }

    /* always disable HBN pin pull up/down to reduce PDS/HBN current, 0x4000F014[16]=0 */
    HBN_Hw_Pu_Pd_Cfg(DISABLE);

    HBN_Pin_WakeUp_Mask(~(cfg->gpioWakeupSrc));
    if (cfg->gpioWakeupSrc != 0) {
        HBN_GPIO_INT_Enable(cfg->gpioTrigType);
    }

    /* HBN RTC config and enable */
    HBN_Clear_RTC_Counter();
    if (cfg->sleepTime != 0) {
        HBN_Get_RTC_Timer_Val(&valLow, &valHigh);
        val = valLow + ((uint64_t)valHigh << 32);
        val += cfg->sleepTime;
        HBN_Set_RTC_Timer(HBN_RTC_INT_DELAY_0T, val & 0xffffffff, val >> 32, HBN_RTC_COMP_BIT0_39);
        HBN_Enable_RTC_Counter();
    }

    HBN_Power_Down_Flash(cfg->flashCfg);

    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_RC32M);

    HBN_Enable(cfg->gpioWakeupSrc, cfg->ldoLevel, cfg->hbnLevel, cfg->dcdcPuSeq);
}

/****************************************************************************/ /**
 * @brief  power down and switch clock
 *
 * @param  flashCfg: None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION HBN_Power_Down_Flash(spi_flash_cfg_type *flashCfg)
{
    spi_flash_cfg_type bhFlashCfg;

    if (flashCfg == NULL) {
        L1C_DCache_Invalid_By_Addr(QCC743_FLASH_XIP_BASE + 8 + 4, sizeof(spi_flash_cfg_type));
        qcc74x_xip_sflash_read_via_cache_need_lock(QCC743_FLASH_XIP_BASE + 8 + 4, (uint8_t *)(&bhFlashCfg), sizeof(spi_flash_cfg_type), 0, 0);
        L1C_DCache_Invalid_By_Addr(QCC743_FLASH_XIP_BASE + 8 + 4, sizeof(spi_flash_cfg_type));

        qcc74x_sf_ctrl_set_owner(SF_CTRL_OWNER_SAHB);
        qcc74x_sflash_reset_continue_read(&bhFlashCfg);
    } else {
        qcc74x_sf_ctrl_set_owner(SF_CTRL_OWNER_SAHB);
        qcc74x_sflash_reset_continue_read(flashCfg);
    }

    qcc74x_sflash_powerdown();
}

/****************************************************************************/ /**
 * @brief  Enable HBN mode
 *
 * @param  aGPIOIeCfg: AON GPIO input enable config. Bit(s) of Wakeup GPIO(s) must not be set to
 *                     0(s),say when use GPIO7 as wake up pin,aGPIOIeCfg should be 0x01.
 * @param  ldoLevel: LDO volatge level
 * @param  hbnLevel: HBN work level
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION HBN_Enable(uint32_t aGPIOIeCfg, uint8_t ldoLevel, uint8_t hbnLevel, uint8_t dcdcPuSeq)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_LDO_LEVEL_TYPE(ldoLevel));
    CHECK_PARAM(IS_HBN_LEVEL_TYPE(hbnLevel));

    /* Setting from guide */
    /* HBN_SRAM Retion */
    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_SRAM);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_RETRAM_RET);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_RETRAM_SLP);
    QCC74x_WR_REG(HBN_BASE, HBN_SRAM, tmpVal);

    /* AON GPIO IE */
    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_PD);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    /* HBN mode LDO level */
    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_CTL);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_LDO11_AON_VOUT_SEL, ldoLevel);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_LDO11_RT_VOUT_SEL, ldoLevel);
    QCC74x_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* power on dcdc18 sequence  */
    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_CTL);
    if (dcdcPuSeq) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_PU_DCDC18_AON);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_PU_DCDC18_AON);
    }
    QCC74x_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Select RC32M */
    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL, 0);
    QCC74x_WR_REG(HBN_BASE, HBN_GLB, tmpVal);
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    /* Set HBN flag */
    QCC74x_WR_REG(HBN_BASE, HBN_RSV0, HBN_STATUS_ENTER_FLAG);

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_CTL);
    /* Set HBN level, (HBN_PWRDN_HBN_RAM not use) */
    switch (hbnLevel) {
        case HBN_LEVEL_0:
            tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
            break;

        case HBN_LEVEL_1:
            tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
            break;

        default:
            break;
    }
    /* Set power on option:0 for por reset twice for robust 1 for reset only once*/
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_PWR_ON_OPTION);
    QCC74x_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Enable HBN mode */
    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_CTL);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_MODE);
    QCC74x_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    while (1) {
        arch_delay_ms(1000);
    }
}

/****************************************************************************/ /**
 * @brief  Enable HBN PIR
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_PIR_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_PIR_CFG);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_PIR_EN);
    QCC74x_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable HBN PIR
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_PIR_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_PIR_CFG);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_PIR_EN);
    QCC74x_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Config HBN PIR interrupt
 *
 * @param  pirIntCfg: HBN PIR interrupt configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_PIR_INT_Config(HBN_PIR_INT_CFG_Type *pirIntCfg)
{
    uint32_t tmpVal;
    uint32_t bit4 = 0;
    uint32_t bit5 = 0;
    uint32_t bitVal = 0;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_PIR_CFG);

    /* low trigger interrupt */
    if (pirIntCfg->lowIntEn == ENABLE) {
        bit5 = 0;
    } else {
        bit5 = 1;
    }

    /* high trigger interrupt */
    if (pirIntCfg->highIntEn == ENABLE) {
        bit4 = 0;
    } else {
        bit4 = 1;
    }

    bitVal = bit4 | (bit5 << 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIR_DIS, bitVal);
    QCC74x_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select HBN PIR low pass filter
 *
 * @param  lpf: HBN PIR low pass filter selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_PIR_LPF_Sel(uint8_t lpf)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_PIR_LPF_TYPE(lpf));

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_PIR_CFG);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIR_LPF_SEL, lpf);
    QCC74x_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select HBN PIR high pass filter
 *
 * @param  hpf: HBN PIR high pass filter selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_PIR_HPF_Sel(uint8_t hpf)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_PIR_HPF_TYPE(hpf));

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_PIR_CFG);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIR_HPF_SEL, hpf);
    QCC74x_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set HBN PIR threshold value
 *
 * @param  threshold: HBN PIR threshold value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Set_PIR_Threshold(uint16_t threshold)
{
    uint32_t tmpVal;

    CHECK_PARAM((threshold <= 0x3FFF));

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_PIR_VTH);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIR_VTH, threshold);
    QCC74x_WR_REG(HBN_BASE, HBN_PIR_VTH, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set HBN PIR interval value
 *
 * @param  interval: HBN PIR interval value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Set_PIR_Interval(uint16_t interval)
{
    uint32_t tmpVal;

    CHECK_PARAM((interval <= 0xFFF));

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_PIR_INTERVAL);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIR_INTERVAL, interval);
    QCC74x_WR_REG(HBN_BASE, HBN_PIR_INTERVAL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set HBN bod config
 *
 * @param  enable: ENABLE or DISABLE, if enable, Power up Brown Out Reset
 * @param  threshold: bod threshold
 * @param  mode: bod work mode with por
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Set_BOD_Config(uint8_t enable, uint8_t threshold, uint8_t mode)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_BOD_THRES_TYPE(threshold));
    CHECK_PARAM(IS_HBN_BOD_MODE_TYPE(mode));

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_BOR_CFG);
    if (enable) {
        tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PU_BOD, 1);
    } else {
        tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PU_BOD, 0);
    }
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_BOD_VTH, threshold);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_BOD_SEL, mode);
    QCC74x_WR_REG(HBN_BASE, HBN_BOR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Keep RC32K On during rtc power domain off
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 * @note  Don't turn off rc32k, which move to RTC Domain
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION HBN_Keep_On_RC32K(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_PU_RC32K);
    QCC74x_WR_REG(HBN_BASE, HBN_GLB, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set HBN Gpio Keep
 *
 * @param  gpioKeep:HBN gpio keep reg cfg
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION HBN_Set_Gpio_Keep(uint8_t gpioKeep)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_RSV3);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_GPIO_KEEP_STS, HBN_GPIO_KEEP_FLAG);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_GPIO_KEEP_PIN, gpioKeep);
    QCC74x_WR_REG(HBN_BASE, HBN_RSV3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable GPIO interrupt
 *
 * @param  gpioIntTrigType: HBN GPIO interrupt trigger type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION HBN_GPIO_INT_Enable(uint8_t gpioIntTrigType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_HBN_GPIO_INT_TRIGGER_TYPE(gpioIntTrigType));

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MODE, gpioIntTrigType);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable GPIO interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_GPIO_INT_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MASK, 0);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN aon pad ctrl configuration
 *
 * @param  aonPadCtl1: ctrl value 1
 * @param  aonpadCtl2: ctrl value 2
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION HBN_Aon_Pad_Ctrl(uint32_t aonPadCtl1, uint32_t aonPadCtl2)
{
    QCC74x_WR_REG(HBN_BASE, HBN_PAD_CTRL_0, aonPadCtl1);
    QCC74x_WR_REG(HBN_BASE, HBN_PAD_CTRL_1, aonPadCtl2);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN Set AON_HW control aon pad or not
 *
 * @param  aonPadHwCtrlEn: hw control aon pad enable
 * @param  aonGpio: aon pad number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION HBN_Aon_Pad_Cfg_Set(uint8_t aonPadHwCtrlEn, uint8_t aonGpio)
{
    uint32_t tmpVal;
    uint32_t enAonCtrlGpio;

    /* hbn_pad_ctrl_0 */
    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_PAD_CTRL_0);
    enAonCtrlGpio = QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_REG_EN_AON_CTRL_GPIO);

    if (aonPadHwCtrlEn) {
        enAonCtrlGpio |= (1 << aonGpio);
    } else {
        enAonCtrlGpio &= ~(1 << aonGpio);
    }
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_REG_EN_AON_CTRL_GPIO, enAonCtrlGpio);

    QCC74x_WR_REG(HBN_BASE, HBN_PAD_CTRL_0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable BOD interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Enable_BOD_IRQ(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_IRQ_BOR_EN);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable BOD interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Disable_BOD_IRQ(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_IRQ_BOR_EN);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN aon pad debbug pull config
 *
 * @param  puPdEn: Enable or disable aon pad pull down and pull up
 * @param  ieSmtEn: Enable or disable aon pad IE and SMT
 * @param  trigMode: trigger mode
 * @param  maskVal: int mask
 * @param  dlyEn: Enable or disable aon pad wakeup delay function
 * @param  dlySec: aon pad wakeup delay sec 1 to 7
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Aon_Pad_WakeUpCfg(QCC74x_Fun_Type puPdEn, uint8_t trigMode, uint32_t maskVal, QCC74x_Fun_Type dlyEn, uint8_t dlySec)
{
    uint32_t tmpVal;

    CHECK_PARAM(((dlySec >= 1) && (dlySec <= 7)));
    CHECK_PARAM(IS_HBN_GPIO_INT_TRIGGER_TYPE(trigMode));
    CHECK_PARAM((maskVal <= 0x3FF));

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_EN, dlyEn);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_SEL, dlySec);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_REG_EN_HW_PU_PD, puPdEn);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MASK, maskVal);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MODE, trigMode);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set Reset Reason
 *
 * @param  rstReason:Reset Reason
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION HBN_Set_Reset_Reason(uint16_t rstReason)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_RSV3);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_FLASH_POWER_STS, HBN_RESET_REASON_FLAG);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_FLASH_POWER_DLY, rstReason);
    QCC74x_WR_REG(HBN_BASE, HBN_RSV3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set Reset Reason
 *
 * @param  flashPwrDly:flash power delay
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION HBN_Get_Reset_Reason(uint16_t *rstReason)
{
    uint32_t tmpVal = 0;

    if (NULL == rstReason) {
        return ERROR;
    }

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_RSV3);
    if (HBN_RESET_REASON_FLAG == QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_FLASH_POWER_STS)) {
        *rstReason = QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_FLASH_POWER_DLY);
        return SUCCESS;
    }

    return ERROR;

}

/****************************************************************************/ /**
 * @brief  Set Embedded Flash Pullup enabe or disable
 *
 * @param  cfg: Enable or disable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Set_BOD_Cfg(HBN_BOD_CFG_Type *cfg)
{
    uint32_t tmpVal = 0;

    if (cfg->enableBodInt) {
        HBN_Enable_BOD_IRQ();
    } else {
        HBN_Disable_BOD_IRQ();
    }

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_BOR_CFG);

    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_BOD_VTH, cfg->bodThreshold);
    if (cfg->enablePorInBod) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_BOD_SEL);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_BOD_SEL);
    }

    if (cfg->enableBod) {
        tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_PU_BOD);
    } else {
        tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_PU_BOD);
    }

    QCC74x_WR_REG(HBN_BASE, HBN_BOR_CFG, tmpVal);

    return SUCCESS;
}

#define GLB_CLK_SET_DUMMY_WAIT \
    {                          \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
    }
const uint32_t ATTR_CLOCK_CONST_SECTION usbPllSdmin_12M = 0x28000;
const uint32_t ATTR_CLOCK_CONST_SECTION sscDivSdmin_24M = 0x28000;

void glb_40M_delay_us(uint32_t us)
{
    for (uint32_t i = 0; i < us; i++) {
        GLB_CLK_SET_DUMMY_WAIT;
        GLB_CLK_SET_DUMMY_WAIT;
        GLB_CLK_SET_DUMMY_WAIT;
    }
}

/****************************************************************************/ /**
 * @brief  power on wifipll quickly
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllType: only power on xtal
 *******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Fast_Power_On_WIFIPLL(const GLB_WA_PLL_Cfg_Type *const cfg, uint8_t waitStable)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;

    /* Step1:config parameter */
    /* cfg1:Set wifipll_refclk_sel and wifipll_refdiv_ratio */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_REFDIV_RATIO, cfg->basicCfg->clkpllRefdivRatio);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    /* cfg2:Set wifipll_int_frac_sw,wifipll_icp_1u,wifipll_icp_5u */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 2);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_INT_FRAC_SW, cfg->basicCfg->clkpllIntFracSw);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_ICP_1U, cfg->basicCfg->clkpllIcp1u);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_ICP_5U, cfg->basicCfg->clkpllIcp5u);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 2, tmpVal);

    /* cfg3:Set wifipll_rz,wifipll_cz,wifipll_c3,wifipll_r4_short,wifipll_r4_en */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 3);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_RZ, cfg->basicCfg->clkpllRz);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_CZ, cfg->basicCfg->clkpllCz);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_C3, cfg->basicCfg->clkpllC3);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_R4_SHORT, cfg->basicCfg->clkpllR4Short);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_C4_EN, cfg->basicCfg->clkpllC4En);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 3, tmpVal);

    /* cfg4:Set wifipll_sel_sample_clk */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 4);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SEL_SAMPLE_CLK, cfg->basicCfg->clkpllSelSampleClk);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 4, tmpVal);

    /* cfg5:Set wifipll_vco_speed */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 5);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_VCO_SPEED, cfg->basicCfg->clkpllVcoSpeed);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 5, tmpVal);

    /* cfg6:Set wifipll_sdm_bypass,wifipll_sdmin */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 6);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_CTRL_HW, cfg->basicCfg->clkpllSdmCtrlHw);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_BYPASS, cfg->basicCfg->clkpllSdmBypass);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDMIN, cfg->clkpllSdmin);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 6, tmpVal);

    /* cfg10:always set usbpll_sdmin */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 10);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_USBPLL_SDMIN, usbPllSdmin_12M);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 10, tmpVal);

    /* cfg12:always set sscdiv_sdmin */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 12);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_SSCDIV_SDMIN, sscDivSdmin_24M);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 12, tmpVal);

    /* Step2:config pu */
    /* cfg0 : pu_wifipll_sfreg=1 */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_PU_WIFIPLL_SFREG, 1);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
    glb_40M_delay_us(3);

    /* cfg0 : pu_wifipll=1 */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_PU_WIFIPLL, 1);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
    glb_40M_delay_us(3);

    /* toggle sdm_reset (pulse 0 > 1us) */
    /* cfg0 : wifipll_sdm_reset */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_RSTB, 1);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    glb_40M_delay_us(2);
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_RSTB, 0);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    glb_40M_delay_us(2);
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_RSTB, 1);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* Step3:reset pll */
    /* cfg0 : toggle wifipll_reset_fbdv, pulse 0 > 1us */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_FBDV_RSTB, 1);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    glb_40M_delay_us(2);
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_FBDV_RSTB, 0);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    glb_40M_delay_us(2);
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_FBDV_RSTB, 1);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* Step4:enable output clock */
    /* cfg8 : wifipll clock enable */
    tmpVal = QCC74x_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 8);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV3);
    // tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV4);
    // tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV5);
    // tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV6);
    // tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV8);
    // tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV10);
    // tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV12);
    // tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV20);
    // tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV30);
    QCC74x_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 8, tmpVal);

    if (waitStable) {
        /* Wait 1.5*30us    */
        glb_40M_delay_us(45);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power on xtal and wifipll quickly
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllType: only power on xtal
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Fast_Power_On_XTAL_40M_And_WIFIPLL(void)
{
    uint32_t tmpVal;
    volatile uint8_t refClk;

    refClk = GLB_PLL_REFCLK_XTAL;

    /* power on xtal first */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_TSEN);
    if (!QCC74x_IS_REG_BIT_SET(tmpVal, AON_XTAL_RDY) ){
        AON_Power_On_XTAL();
    }

    // HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
    //HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);

    //HBN_Set_Xtal_Type(GLB_XTAL_40M);

    /* power on wifipll */
    GLB_Power_Off_WIFIPLL();
    GLB_WIFIPLL_Ref_Clk_Sel(refClk);
    GLB_Fast_Power_On_WIFIPLL(&wifiPllCfg_960M_Fast[0], 0);

    glb_40M_delay_us(30);

    /* if power on xtal, always set xclk from xtal */
    // HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_XTAL);

    /* enable all PLL clock output */
    /* GLB reg_pll_en = 1, cannot be zero */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, GLB_REG_PLL_EN);
    QCC74x_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Fast_Set_MCU_System_CLK_Div(uint8_t mcuClkDiv, uint8_t mcuPBclkDiv)
{
    uint32_t tmpVal;
    uint32_t timeout = 1024;

    /* config hclk_div=mcuClkDiv */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV, mcuClkDiv);
    QCC74x_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);

    /* config bclk_div=mcuPBclkDiv */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV, mcuPBclkDiv);
    QCC74x_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);
    /* bclk act pulse */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV_ACT_PULSE, 1);
    QCC74x_WR_REG(GLB_BASE, GLB_SYS_CFG1, tmpVal);

    timeout = 1024;
    do {
        tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG1);
        tmpVal = QCC74x_GET_REG_BITS_VAL(tmpVal, GLB_STS_BCLK_PROT_DONE);
    } while ((--timeout) && (!tmpVal));
    if (!timeout) {
        return ERROR;
    }

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Fast_Set_MCU_System_CLK(uint8_t clkFreq)
{
    uint32_t tmpVal;

    // CHECK_PARAM(IS_GLB_MCU_SYS_CLK_TYPE(clkFreq));

    /* get xclk&&rootclk clock */
    // mcuXclkSel = HBN_Get_MCU_XCLK_Sel();

    // /* change root clock to rc32m */
    // HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
    // HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
    // GLB_Set_MCU_System_CLK_Div(0, 0);

    /* select pll output clock before select root clock */
    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_CPU_CORE_CFG1);
#if 0
    switch (clkFreq) {
        // case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV2:
        //     tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 0);
        //     break;
        // case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV1:
        //     tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 1);
        //     break;
        // case GLB_MCU_SYS_CLK_TOP_WIFIPLL_240M:
        //     tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 2);
        //     break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_320M:
            tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 3);
            break;
        default:
            break;
    }
#else
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 3);
#endif
    QCC74x_WR_REG(PDS_BASE, PDS_CPU_CORE_CFG1, tmpVal);

#if 0
    /* select root clock */
    switch (clkFreq) {
        // case GLB_MCU_SYS_CLK_RC32M:
        //     GLB_Set_MCU_System_CLK_Div(0, 0);
        //     HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
        //     HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
        //     break;
        // case GLB_MCU_SYS_CLK_XTAL:
        //     GLB_Set_MCU_System_CLK_Div(0, 0);
        //     HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_XTAL);
        //     HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
        //     break;
        // case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV2:
        //     /* For high speed, set DIV first */
        //     GLB_Set_MCU_System_CLK_Div(0, 2);
        //     /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
        //     /* MCU_MISC_IROM_2T_Access_Set(0); */
        //     /* unuseful for mcu, useful for dsp, just for safe */
        //     GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_AUPLL_DIV2);
        //     HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
        //     /* recover xclk */
        //     HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
        //     break;
        // case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV1:
        //     /* For high speed, set DIV first */
        //     GLB_Set_MCU_System_CLK_Div(1, 2);
        //     /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
        //     /* MCU_MISC_IROM_2T_Access_Set(0); */
        //     /* unuseful for mcu, useful for dsp, just for safe */
        //     GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_AUPLL_DIV1);
        //     HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
        //     /* recover xclk */
        //     HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
        //     break;
        // case GLB_MCU_SYS_CLK_TOP_WIFIPLL_240M:
        //     /* For high speed, set DIV first */
        //     GLB_Set_MCU_System_CLK_Div(0, 2);
        //     /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
        //     /* MCU_MISC_IROM_2T_Access_Set(0); */
        //     /* unuseful for mcu, useful for dsp, just for safe */
        //     GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_WIFIPLL_240M);
        //     HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
        //     /* recover xclk */
        //     HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
        //     break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_320M:
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(3, 0);
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_WIFIPLL_320M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            // HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        default:
            break;
    }
#else
    /* For high speed, set DIV first */
    GLB_Fast_Set_MCU_System_CLK_Div(3, 0);
    /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
    /* MCU_MISC_IROM_2T_Access_Set(0); */
    //GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_WIFIPLL_320M);
    QCC74x_WR_WORD(0x2000058C,QCC74x_RD_WORD(0x2000058C)|(1<<14));
    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
    QCC74x_WR_WORD(0x2000f030,QCC74x_RD_WORD(0x2000f030)|(1<<1));

#endif

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}
/****************************************************************************/ /**
 * @brief  Program data to efuse
 *
 * @param  offset: offset of efuse address to program
 * @param  pword: data pointer to buffer which is aligned to word
 * @param  count: count of data in words to program
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Program_Direct(uint32_t offset, uint32_t *pword, uint32_t count)
{
    uint32_t *pEfuseStart0 = (uint32_t *)(EF_DATA_BASE + offset);

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    /* Add delay for CLK to be stable */
    arch_delay_us(4);

    if (pword != NULL) {
        ARCH_MemCpy4(pEfuseStart0, pword, count);
    }

    EF_Ctrl_Program_Efuse_0();
}

/****************************************************************************/ /**
 * @brief  Read data from efuse
 *
 * @param  offset: offset of efuse address to read
 * @param  pword: data pointer to buffer which is aligned to word
 * @param  count: count of data in words to read
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Direct(uint32_t offset, uint32_t *pword, uint32_t count)
{
    uint32_t *pEfuseStart0 = (uint32_t *)(EF_DATA_BASE + offset);

    EF_Ctrl_Load_Efuse_R0();

    ARCH_MemCpy4(pword, pEfuseStart0, count);
}

/****************************************************************************/ /**
 * @brief  HBN Re-Cal RC32K
 *
 * @param  expected_counter: Expected rtc counter
 * @param  actual_counter: Actual rtc counter
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION HBN_Recal_RC32K(int32_t expected_counter, int32_t actual_counter)
{
    int32_t tmpVal = 0;
    int32_t current = 0;
    int32_t delta = 0;

    delta = actual_counter - expected_counter;

    /* normalize to 1s count */
    delta = (delta * 32768) / expected_counter;

    if ((delta < 32) && (delta > -32)) {
        return -1;
    }
    if (delta < -320) {
        delta = -320;
    } else if (delta > 320) {
        delta = 320;
    }

    if (delta >= 64 || delta <= -64) {
        delta = delta / 64;
    } else {
        delta = delta / 32;
    }

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_RC32K_CTRL0);
    current = QCC74x_GET_REG_BITS_VAL(tmpVal, HBN_RC32K_CODE_FR_EXT);
    current += delta;
    current &= ((1U << HBN_RC32K_CODE_FR_EXT_LEN) - 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_RC32K_CODE_FR_EXT, current);
    QCC74x_WR_REG(HBN_BASE, HBN_RC32K_CTRL0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 240M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_240M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType=GLB_XTAL_NONE;

    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((uint8_t)xtalType,audioPllCfg_240M);
}

/****************************************************************************/ /**
 * @brief  Configure AUPLL clock to 245.76M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Config_AUDIO_PLL_To_245P76M(void)
{
    /* GLB_XTAL_Type */
    uint8_t xtalType=GLB_XTAL_NONE;

    HBN_Get_Xtal_Type(&xtalType);
    return GLB_Config_AUDIO_PLL((uint8_t)xtalType,audioPllCfg_245P76M);
}

/****************************************************************************/ /**
 * @brief  Set mcu System clock Simple
 *
 * @param  clkFreq: mcu system clock type
 * @param  mcuClkDiv: HCLK divider
 * @param  mcuPBclkDiv: BCLK divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Simple_Set_MCU_System_CLK(uint8_t clkFreq, uint8_t mcuClkDiv, uint8_t mcuPBclkDiv)
{
    uint32_t tmpVal;
    uint32_t timeout;

    CHECK_PARAM(IS_GLB_MCU_SYS_CLK_TYPE(clkFreq));

    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);

    /* select pll output clock before select root clock */
    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_CPU_CORE_CFG1);
    switch (clkFreq) {
        case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV2:
            tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 0);
            break;
        case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV1:
            tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 1);
            break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_240M:
            tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 2);
            break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_320M:
            tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, PDS_REG_PLL_SEL, 3);
            break;
        default:
            break;
    }
    QCC74x_WR_REG(PDS_BASE, PDS_CPU_CORE_CFG1, tmpVal);

    /* clock div */
    /* config hclk_div=mcuClkDiv */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_HCLK_DIV, mcuClkDiv);
    QCC74x_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);
    /* config bclk_div=mcuPBclkDiv */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV, mcuPBclkDiv);
    QCC74x_WR_REG(GLB_BASE, GLB_SYS_CFG0, tmpVal);
    /* bclk act pulse */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_BCLK_DIV_ACT_PULSE, 1);
    QCC74x_WR_REG(GLB_BASE, GLB_SYS_CFG1, tmpVal);
    timeout = 1024;
    do {
        tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_SYS_CFG1);
        tmpVal = QCC74x_GET_REG_BITS_VAL(tmpVal, GLB_STS_BCLK_PROT_DONE);
    } while ((--timeout) && (!tmpVal));
    if (!timeout) {
        return ERROR;
    }

    /* select root clock */
    switch (clkFreq) {
        case GLB_MCU_SYS_CLK_RC32M:
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_RC32M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            break;
        case GLB_MCU_SYS_CLK_XTAL:
            HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_XTAL);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XCLK);
            break;
        case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV2:
            /* For high speed, set DIV first */
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_AUPLL_DIV2);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            break;
        case GLB_MCU_SYS_CLK_TOP_AUPLL_DIV1:
            /* For high speed, set DIV first */
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_AUPLL_DIV1);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_240M:
            /* For high speed, set DIV first */
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_WIFIPLL_240M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            break;
        case GLB_MCU_SYS_CLK_TOP_WIFIPLL_320M:
            /* For high speed, set DIV first */
            /* Set IROM 2T Access 0 since we use RC32M, unuseful now */
            /* MCU_MISC_IROM_2T_Access_Set(0); */
            GLB_PLL_CGEN_Clock_UnGate(GLB_PLL_CGEN_TOP_WIFIPLL_320M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            break;
        default:
            break;
    }

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  PDS Power Off PD_WB
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type PDS_Power_Off_WB(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, PDS_CR_PDS_FORCE_WB_ISO_EN);
    QCC74x_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    tmpVal = QCC74x_SET_REG_BIT(tmpVal, PDS_CR_PDS_FORCE_WB_PWR_OFF);
    QCC74x_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  PDS Power On PD_WB
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type PDS_Power_On_WB(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_FORCE_WB_PWR_OFF);
    QCC74x_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, PDS_CR_PDS_FORCE_WB_ISO_EN);
    QCC74x_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    return SUCCESS;
}
/****************************************************************************/ /**
 * @brief  HBN get reset event
 *
 * @param[out]  event
 * [4] : bor_out_ event
 * [3] : pwr_rst_n event
 * [2] : sw_rst event
 * [1] : por_out event
 * [0] : watch dog reset
 *
*******************************************************************************/
void HBN_Get_Reset_Event(uint8_t* event)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_GLB);

    *event = QCC74x_GET_REG_BITS_VAL(tmpVal,HBN_RESET_EVENT);
}

/****************************************************************************/ /**
 * @brief  HBN clear reset event
 *
*******************************************************************************/
void HBN_Clr_Reset_Event(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_GLB);

    tmpVal |= (1<<13);

    QCC74x_WR_REG(HBN_BASE, HBN_GLB, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set PSRAMB clock
 *
 * @param  slave: slave IP
 * @param  enable: enable or disable clock
 * @param  clkSel: clock selection
 * @param  div: clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION GLB_Set_Slave_Grp_0_CLK(uint8_t slave, uint8_t enable, GLB_SLAVE_GRP_0_CLK_SEL_Type clkSel, uint32_t div)
{
    uint32_t tmpVal;
    uint32_t regAddr = GLB_BASE + glb_slave_grp_0_table[slave].clkOffSetAddr;
    uint8_t enPos = glb_slave_grp_0_table[slave].clkEnPos;
    uint8_t selPos = glb_slave_grp_0_table[slave].clkSelPos;
    uint8_t divPos = glb_slave_grp_0_table[slave].clkDivPos;
    uint8_t enLen = glb_slave_grp_0_table[slave].clkEnLen;
    uint8_t selLen = glb_slave_grp_0_table[slave].clkSelLen;
    uint8_t divLen = glb_slave_grp_0_table[slave].clkDivLen;

    CHECK_PARAM(IS_GLB_SLAVE_GRP_0_TYPE(slave));

    /* disable clock first */
    if (enLen) {
        tmpVal = QCC74x_RD_WORD(regAddr);
        tmpVal &= ~(((1ULL << enLen) - 1) << enPos);
        QCC74x_WR_WORD(regAddr, tmpVal);
    }

    /* set clock sel or div */
    tmpVal = QCC74x_RD_WORD(regAddr);
    if (selLen) {
        tmpVal &= ~(((1ULL << selLen) - 1) << selPos);
        tmpVal |= (((clkSel.clkSel) & ((1 << selLen) - 1)) << selPos);
    }
    if (divLen) {
        tmpVal &= ~(((1ULL << divLen) - 1) << divPos);
        tmpVal |= ((div & ((1 << divLen) - 1)) << divPos);
    }
    QCC74x_WR_WORD(regAddr, tmpVal);

    /* enable clock */
    if (enLen && enable) {
        tmpVal = QCC74x_RD_WORD(regAddr);
        tmpVal |= (((1ULL << enLen) - 1) << enPos);
        QCC74x_WR_WORD(regAddr, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  turn GPIO output low
 *
 * @param  gpioPin: GPIO type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_GPIO_Clr(uint8_t gpioPin)
{
    if (gpioPin < GLB_GPIO_PIN_32) {
        QCC74x_WR_WORD(GLB_BASE + GLB_GPIO_CFG140_OFFSET, 1 << gpioPin);
    } else {
        QCC74x_WR_WORD(GLB_BASE + GLB_GPIO_CFG141_OFFSET, 1 << (gpioPin - GLB_GPIO_PIN_32));
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  turn GPIO output high
 *
 * @param  gpioPin: GPIO type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_GPIO_Set(uint8_t gpioPin)
{
    if (RESET == GLB_GPIO_Pad_LeadOut_Sts(gpioPin)) {
        return ERROR;
    }

    if (gpioPin < GLB_GPIO_PIN_32) {
        QCC74x_WR_WORD(GLB_BASE + GLB_GPIO_CFG138_OFFSET, 1 << gpioPin);
    } else {
        QCC74x_WR_WORD(GLB_BASE + GLB_GPIO_CFG139_OFFSET, 1 << (gpioPin - GLB_GPIO_PIN_32));
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable ACOMP0 interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Disable_AComp0_IRQ(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_IRQ_ACOMP0_EN);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable ACOMP1 interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Disable_AComp1_IRQ(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_IRQ_ACOMP1_EN);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable ACOMP0 interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Enable_AComp0_IRQ(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_IRQ_ACOMP0_EN);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable ACOMP1 interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type HBN_Enable_AComp1_IRQ(void)
{
    uint32_t tmpVal;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_IRQ_ACOMP1_EN);
    QCC74x_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Invalid I-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
QCC74x_Err_Type ATTR_TCM_SECTION L1C_ICache_Invalid_By_Addr(uintptr_t addr, uint32_t len)
{
    L1C_ICache_Invalid_All();

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set gpio pad int mask type in pds
 *
 * @param  pad: gpio type
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION PDS_Set_GPIO_Pad_IntMask(uint8_t pad, QCC74x_Mask_Type intMask)
{
    uint32_t tmpVal = 0;
    uint32_t pos = 0;

    /* [15:0] : GPIO0~15   */
    /* [30:16] : GPIO20~34 */
    if (pad <= GLB_GPIO_PIN_15) {
        pos = pad;
    } else if ((pad >= GLB_GPIO_PIN_20) && (pad <= GLB_GPIO_PIN_34)) {
        pos = pad - 4;
    } else {
        return ERROR;
    }

    tmpVal = QCC74x_RD_REG(PDS_BASE, PDS_GPIO_PD_SET);
    if (UNMASK != intMask) {
        /* MASK */
        tmpVal |= (1 << pos);
    } else {
        /* UNMASK */
        tmpVal &= ~(1 << pos);
    }
    QCC74x_WR_REG(PDS_BASE, PDS_GPIO_PD_SET, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get gpio pad int status
 *
 * @param  pad: gpio type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Sts_Type ATTR_TCM_SECTION PDS_Get_GPIO_Pad_IntStatus(uint8_t pad)
{
    uint32_t pos = 0;

    /* [15:0]  : GPIO0~15  */
    /* [30:16] : GPIO20~34 */
    if (pad <= GLB_GPIO_PIN_15) {
        pos = pad;
    } else if ((pad >= GLB_GPIO_PIN_20) && (pad <= GLB_GPIO_PIN_34)) {
        pos = pad - 4;
    } else {
        return RESET;
    }

    return (QCC74x_RD_REG(PDS_BASE, PDS_GPIO_STAT) & (1 << pos)) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  BMX init
 *
 * @param  BmxCfg: BMX config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type GLB_BMX_TO_Init(BMX_TO_Cfg_Type *BmxCfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((BmxCfg->timeoutEn) <= 0xF);
    CHECK_PARAM(IS_BMX_ARB_TYPE(BmxCfg->arbMod));

    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_BMX_CFG0);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_BMX_TIMEOUT_EN, BmxCfg->timeoutEn);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_REG_BMX_ARB_MODE, BmxCfg->arbMod);
    QCC74x_WR_REG(GLB_BASE, GLB_BMX_CFG0, tmpVal);

#ifndef QCC74x_USE_HAL_DRIVER
    Interrupt_Handler_Register(BMX_MCU_TO_IRQn, BMX_TO_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set xtal32k_capbank
 *
 * @param  value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION HBN_Set_Xtal_32K_Capbank(uint8_t value)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_XTAL32K);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_XTAL32K_CAPBANK, value);
    QCC74x_WR_REG(HBN_BASE, HBN_XTAL32K, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set xtal32k's inverter amplify strength
 *
 * @param  value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION HBN_Set_Xtal_32K_Inverter_Amplify_Strength(uint8_t value)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_XTAL32K);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_XTAL32K_INV_STRE, value);
    QCC74x_WR_REG(HBN_BASE, HBN_XTAL32K, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set xtal32k_regulator
 *
 * @param  level
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION HBN_Set_Xtal_32K_Regulator(uint8_t level)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_XTAL32K);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_XTAL32K_REG, level);
    QCC74x_WR_REG(HBN_BASE, HBN_XTAL32K, tmpVal);

    return SUCCESS;
}


/****************************************************************************/ /**
 * @brief  Power on XTAL 32K
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 * @note can't use GPIO16&17 after calling this function
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_CLOCK_SECTION HBN_Power_On_Xtal_32K(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_XTAL32K);

    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, HBN_XTAL32K_HIZ_EN);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, HBN_XTAL32K_INV_STRE, 3);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_PU_XTAL32K);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, HBN_PU_XTAL32K_BUF);
    QCC74x_WR_REG(HBN_BASE, HBN_XTAL32K, tmpVal);

    /* Delay >1s */
    arch_delay_us(1100);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  LDO15_RF Output Float
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_Output_Float_LDO15_RF(void)
{
    uint32_t tmpVal=0;

    /* ldo15rf pulldown select by aon */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_LDO15RF_PULLDOWN_SEL_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    /* ldo15rf float output */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, AON_LDO15RF_PULLDOWN_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief   LDO15_RF Pulldown Output to Groud
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_Output_Pulldown_LDO15_RF(void)
{
    uint32_t tmpVal=0;

    /* ldo15rf pulldown select by aon */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_LDO15RF_PULLDOWN_SEL_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    /* ldo15rf pulldown output to ground */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_LDO15RF_PULLDOWN_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  LDO15_RF Output Pulldown Controlled by PD Signal
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_Output_LDO15_RF_Ctrl_by_Pd(void)
{
    uint32_t tmpVal=0;

    /* output ldo15rf pulldown select by pd signal */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, AON_LDO15RF_PULLDOWN_SEL_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power on mic bias
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_Power_On_MicBias(void)
{
    uint32_t tmpVal = 0;

    /* power on sfreg */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_GPADC_MICBIAS_EN);
    QCC74x_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal);

    arch_delay_us(10);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power off mic bias
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_Power_Off_MicBias(void)
{
    uint32_t tmpVal = 0;

    /* power off sfreg */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, AON_GPADC_MICBIAS_EN);
    QCC74x_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power off the power can be shut down in PDS0
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_LowPower_Enter_PDS0(void)
{
    uint32_t tmpVal = 0;

    /* power off sfreg */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_MISC);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, AON_SW_WB_EN_AON);
    QCC74x_WR_REG(AON_BASE, AON_MISC, tmpVal);

    tmpVal = QCC74x_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, AON_PU_MBG_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    /* gating Clock */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_CGEN_CFG0);
    tmpVal = tmpVal & (~(1 << 6));
    tmpVal = tmpVal & (~(1 << 7));
    QCC74x_WR_REG(GLB_BASE, GLB_CGEN_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power on the power powered down in PDS0
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_LowPower_Exit_PDS0(void)
{
    uint32_t tmpVal = 0;

    tmpVal = QCC74x_RD_REG(AON_BASE, AON_RF_TOP_AON);

    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_PU_MBG_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(20);

    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(60);

    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    QCC74x_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(20);

    /* power on wb */
    tmpVal = QCC74x_RD_REG(AON_BASE, AON_MISC);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_SW_WB_EN_AON);
    QCC74x_WR_REG(AON_BASE, AON_MISC, tmpVal);

    /* ungating Clock */
    tmpVal = QCC74x_RD_REG(GLB_BASE, GLB_CGEN_CFG0);
    tmpVal = tmpVal | ((1 << 6));
    tmpVal = tmpVal | ((1 << 7));
    QCC74x_WR_REG(GLB_BASE, GLB_CGEN_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DCDC18 Pulldown Output to Groud
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_Output_Pulldown_DCDC18(void)
{
    uint32_t tmpVal=0;

    tmpVal = QCC74x_RD_REG(AON_BASE, AON_DCDC_TOP_1);
    tmpVal = QCC74x_SET_REG_BIT(tmpVal, AON_DCDC_PULLDOWN_AON );
    QCC74x_WR_REG(AON_BASE, AON_DCDC_TOP_1, tmpVal);
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  DCDC18 Output Float
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
QCC74x_Err_Type ATTR_TCM_SECTION AON_Output_Float_DCDC18(void)
{
    uint32_t tmpVal=0;

    tmpVal = QCC74x_RD_REG(AON_BASE, AON_DCDC_TOP_1);
    tmpVal = QCC74x_CLR_REG_BIT(tmpVal, AON_DCDC_PULLDOWN_AON );
    QCC74x_WR_REG(AON_BASE, AON_DCDC_TOP_1, tmpVal);

    return SUCCESS;
}