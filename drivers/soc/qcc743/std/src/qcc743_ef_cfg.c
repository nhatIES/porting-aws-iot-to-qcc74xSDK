#include "qcc74x_efuse.h"
#include "qcc743_ef_cfg.h"
#include "hardware/ef_data_reg.h"
#include "hardware/glb_reg.h"

static const qcc74x_ef_ctrl_com_trim_cfg_t trim_list[] = {
    {
        .name = "ldo15",
        .en_addr = 0x68 * 8 + 31,
        .parity_addr = 0x68 * 8 + 30,
        .value_addr = 0x68 * 8 + 27,
        .value_len = 3,
    },
    {
        .name = "iptat",
        .en_addr = 0x74 * 8 + 31,
        .parity_addr = 0x74 * 8 + 30,
        .value_addr = 0x68 * 8 + 22,
        .value_len = 5,
    },
    {
        .name = "icx",
        .en_addr = 0x74 * 8 + 29,
        .parity_addr = 0x74 * 8 + 28,
        .value_addr = 0x74 * 8 + 22,
        .value_len = 6,
    },
    {
        .name = "dcdc_trim",
        .en_addr = 0x78 * 8 + 31,
        .parity_addr = 0x78 * 8 + 30,
        .value_addr = 0x78 * 8 + 26,
        .value_len = 4,
    },
    {
        .name = "ldo18_sel",
        .en_addr = 0x78 * 8 + 25,
        .parity_addr = 0x78 * 8 + 24,
        .value_addr = 0x78 * 8 + 20,
        .value_len = 4,
    },
    {
        .name = "ldo18_trim",
        .en_addr = 0x78 * 8 + 19,
        .parity_addr = 0x78 * 8 + 18,
        .value_addr = 0x78 * 8 + 14,
        .value_len = 4,
    },
    {
        .name = "ldo33_trim",
        .en_addr = 0x78 * 8 + 13,
        .parity_addr = 0x78 * 8 + 12,
        .value_addr = 0x78 * 8 + 8,
        .value_len = 4,
    },
    {
        .name = "ldo11_tirm",
        .en_addr = 0x78 * 8 + 7,
        .parity_addr = 0x78 * 8 + 6,
        .value_addr = 0x78 * 8 + 2,
        .value_len = 4,
    },
    {
        .name = "rc32m",
        .en_addr = 0x78 * 8 + 1,
        .parity_addr = 0x78 * 8 + 0,
        .value_addr = 0x7C * 8 + 4,
        .value_len = 8,
    },
    {
        .name = "hp_poffset0",
        .en_addr = 0xCC * 8 + 26,
        .parity_addr = 0xC0 * 8 + 15,
        .value_addr = 0xC0 * 8 + 0,
        .value_len = 15,
    },
    {
        .name = "hp_poffset1",
        .en_addr = 0xCC * 8 + 27,
        .parity_addr = 0xC0 * 8 + 31,
        .value_addr = 0xC0 * 8 + 16,
        .value_len = 15,
    },
    {
        .name = "hp_poffset2",
        .en_addr = 0xCC * 8 + 28,
        .parity_addr = 0xC4 * 8 + 15,
        .value_addr = 0xC4 * 8 + 0,
        .value_len = 15,
    },
    {
        .name = "lp_poffset0",
        .en_addr = 0xCC * 8 + 29,
        .parity_addr = 0xC4 * 8 + 31,
        .value_addr = 0xC4 * 8 + 16,
        .value_len = 15,
    },
    {
        .name = "lp_poffset1",
        .en_addr = 0xCC * 8 + 30,
        .parity_addr = 0xC8 * 8 + 15,
        .value_addr = 0xC8 * 8 + 0,
        .value_len = 15,
    },
    {
        .name = "lp_poffset2",
        .en_addr = 0xCC * 8 + 31,
        .parity_addr = 0xC8 * 8 + 31,
        .value_addr = 0xC8 * 8 + 16,
        .value_len = 15,
    },
    {
        .name = "bz_poffset0",
        .en_addr = 0xD0 * 8 + 26,
        .parity_addr = 0xCC * 8 + 25,
        .value_addr = 0xCC * 8 + 0,
        .value_len = 25,
    },
    {
        .name = "bz_poffset1",
        .en_addr = 0xD0 * 8 + 27,
        .parity_addr = 0xD0 * 8 + 25,
        .value_addr = 0xD0 * 8 + 0,
        .value_len = 25,
    },
    {
        .name = "bz_poffset2",
        .en_addr = 0xD0 * 8 + 28,
        .parity_addr = 0xD4 * 8 + 25,
        .value_addr = 0xD4 * 8 + 0,
        .value_len = 25,
    },
    {
        .name = "tmp_mp0",
        .en_addr = 0xD8 * 8 + 9,
        .parity_addr = 0xD8 * 8 + 8,
        .value_addr = 0xD8 * 8 + 0,
        .value_len = 8,
    },
    {
        .name = "tmp_mp1",
        .en_addr = 0xD8 * 8 + 19,
        .parity_addr = 0xD8 * 8 + 18,
        .value_addr = 0xD8 * 8 + 10,
        .value_len = 8,
    },
    {
        .name = "tmp_mp2",
        .en_addr = 0xD8 * 8 + 29,
        .parity_addr = 0xD8 * 8 + 28,
        .value_addr = 0xD8 * 8 + 20,
        .value_len = 8,
    },
    {
        .name = "auadc_gain",
        .en_addr = 0xDC * 8 + 25,
        .parity_addr = 0xDC * 8 + 24,
        .value_addr = 0xDC * 8 + 0,
        .value_len = 24,
    },
    {
        .name = "auadc_offset",
        .en_addr = 0xE0 * 8 + 25,
        .parity_addr = 0xE0 * 8 + 24,
        .value_addr = 0xE0 * 8 + 0,
        .value_len = 24,
    },
    {
        .name = "psram_trim",
        .en_addr = 0xE8 * 8 + 12,
        .parity_addr = 0xE8 * 8 + 11,
        .value_addr = 0xE8 * 8 + 0,
        .value_len = 11,
    },
    {
        .name = "rc32k",
        .en_addr = 0xEC * 8 + 19,
        .parity_addr = 0xEC * 8 + 18,
        .value_addr = 0xEC * 8 + 8,
        .value_len = 10,
    },
    {
        .name = "xtal0",
        .en_addr = 0xEC * 8 + 7,
        .parity_addr = 0xEC * 8 + 6,
        .value_addr = 0xEC * 8 + 0,
        .value_len = 6,
    },
    {
        .name = "xtal1",
        .en_addr = 0xF0 * 8 + 31,
        .parity_addr = 0xF0 * 8 + 30,
        .value_addr = 0xF4 * 8 + 26,
        .value_len = 6,
    },
    {
        .name = "xtal2",
        .en_addr = 0xF0 * 8 + 29,
        .parity_addr = 0xF0 * 8 + 28,
        .value_addr = 0xF4 * 8 + 20,
        .value_len = 6,
    },
    {
        .name = "gpadc_gain",
        .en_addr = 0xF0 * 8 + 27,
        .parity_addr = 0xF0 * 8 + 26,
        .value_addr = 0xF0 * 8 + 14,
        .value_len = 12,
    },
    {
        .name = "tsen",
        .en_addr = 0xF0 * 8 + 13,
        .parity_addr = 0xF0 * 8 + 12,
        .value_addr = 0xF0 * 8 + 0,
        .value_len = 12,
    },
    {
        .name = "dcdc_dis",
        .en_addr = 0xF4 * 8 + 19,
        .parity_addr = 0xF4 * 8 + 18,
        .value_addr = 0xF4 * 8 + 17,
        .value_len = 1,
    },
    {
        .name = "dcdc_vout",
        .en_addr = 0xF4 * 8 + 16,
        .parity_addr = 0xF4 * 8 + 15,
        .value_addr = 0xF4 * 8 + 10,
        .value_len = 5,
    },
    {
        .name = "ldo18_bypass",
        .en_addr = 0xF4 * 8 + 9,
        .parity_addr = 0xF4 * 8 + 8,
        .value_addr = 0xF4 * 8 + 4,
        .value_len = 1,
    },
    {
        .name = "usb20",
        .en_addr = 0xF8 * 8 + 15,
        .parity_addr = 0xF8 * 8 + 14,
        .value_addr = 0xF8 * 8 + 8,
        .value_len = 6,
    }
};

/****************************************************************************/ /**
 * @brief  Efuse get trim list
 *
 * @param  trim_list: Trim list pointer
 *
 * @return Trim list count
 *
*******************************************************************************/
uint32_t qcc74x_ef_ctrl_get_common_trim_list(const qcc74x_ef_ctrl_com_trim_cfg_t **ptrim_list)
{
    *ptrim_list = &trim_list[0];
    return sizeof(trim_list) / sizeof(trim_list[0]);
}

static char * ATTR_TCM_SECTION qcc74x_efuse_print_number(char *buffer, uint8_t number)
{
    uint8_t i = 0;

    if (number >= 100) {
        buffer[i++] = '1';
        buffer[i++] = '0';
        buffer[i++] = '0';
    } else if (number >= 10) {
        buffer[i++] = number / 10 + '0';
        buffer[i++] = number % 10 + '0';
    } else { /* (number < 10) */
        buffer[i++] = number + '0';
    }

    return buffer + i;
}

/****************************************************************************/ /**
 * @brief  Efuse read device info
 *
 * @param  device_info: info pointer
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION qcc74x_efuse_get_device_info(qcc74x_efuse_device_info_type *device_info)
{
    uint32_t tmpval;
    char *idx;

    qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_WIFI_MAC_HIGH_OFFSET, &tmpval, 1, 1);
    device_info->package = (tmpval >> 22) & 3;
    device_info->flash_info = (tmpval >> 26) & 7;
    device_info->psram_info = (tmpval >> 24) & 3;
    device_info->version = (tmpval >> 29) & 7;

    switch (device_info->package) {
        case 0:
            device_info->package_name = "QFN40";
            break;
        case 1:
            device_info->package_name = "QFN40M";
            break;
        case 2:
            device_info->package_name = "QFN56";
            break;
        default:
            device_info->package_name = "ERROR";
            break;
    }
    switch (device_info->flash_info) {
        case 0:
            device_info->flash_info_name = "NO";
            break;
        case 1:
            device_info->flash_info_name = "2MB";
            break;
        case 2:
            device_info->flash_info_name = "4MB";
            break;
        case 3:
            device_info->flash_info_name = "6MB";
            break;
        case 4:
            device_info->flash_info_name = "8MB";
            break;
        default:
            device_info->flash_info_name = "ERROR";
            break;
    }
    switch (device_info->psram_info) {
        case 0:
            device_info->psram_info_name = "NO";
            break;
        case 1:
            device_info->psram_info_name = "WB_4MB";
            break;
        case 2:
            device_info->psram_info_name = "WB_8MB";
            break;
        case 3:
            device_info->psram_info_name = "WB_16MB";
            break;
        default:
            device_info->psram_info_name = "ERROR";
    }

    QCC74x_WR_REG(GLB_BASE, GLB_PROC_MON, 0x00000401);
    arch_delay_us(110);
    QCC74x_WR_REG(GLB_BASE, GLB_PROC_MON, 0x00000403);
    arch_delay_us(110);
    QCC74x_WR_REG(GLB_BASE, GLB_PROC_MON, 0x00000413);
    arch_delay_us(110);
    QCC74x_WR_REG(GLB_BASE, GLB_PROC_MON, 0x00000433);
    arch_delay_us(1100);
    tmpval = QCC74x_RD_REG(GLB_BASE, GLB_PROC_MON);
    tmpval = QCC74x_GET_REG_BITS_VAL(tmpval, GLB_RING_FREQ);
    device_info->process_corner = tmpval;
    idx = device_info->process_corner_name;
    if (device_info->process_corner <= 480) {
        arch_memcpy(device_info->process_corner_name, "SS", sizeof("SS"));
    } else if (device_info->process_corner < 540) {
        uint16_t ss, tt;
        ss = ((device_info->process_corner - 480) * 100 + 30) / 60;
        tt = 100 - ss;
        idx = qcc74x_efuse_print_number(device_info->process_corner_name, ss);
        arch_memcpy(idx, "%TT+", sizeof("%TT+"));
        idx = qcc74x_efuse_print_number(idx + sizeof("%TT+") - 1, tt);
        arch_memcpy(idx, "%SS", sizeof("%SS"));
    } else if (device_info->process_corner == 540) {
        arch_memcpy(device_info->process_corner_name, "TT", 3);
    } else if (device_info->process_corner < 610) {
        uint16_t tt, ff;
        tt = ((device_info->process_corner - 540) * 100 + 35) / 70;
        ff = 100 - tt;
        idx = qcc74x_efuse_print_number(device_info->process_corner_name, ff);
        arch_memcpy(idx, "%TT+", sizeof("%TT+"));
        idx = qcc74x_efuse_print_number(idx + sizeof("%TT+") - 1, tt);
        arch_memcpy(idx, "%FF", sizeof("%FF"));
    } else { /* >= 610 */
        arch_memcpy(device_info->process_corner_name, "FF", 3);
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read chip identification
 *
 * @param  chipid: id pointer
 *
 * @return 0 or -1
 *
*******************************************************************************/
int qcc74x_efuse_get_chipid(uint8_t chipid[8])
{
    chipid[6] = 0;
    chipid[7] = 0;

    return qcc74x_efuse_read_mac_address_opt(0, chipid, 1);
}

/****************************************************************************/ /**
 * @brief  Whether MAC address slot is empty
 *
 * @param  slot: MAC address slot
 * @param  reload: whether  reload to check
 *
 * @return 0 for all slots full,1 for others
 *
*******************************************************************************/
uint8_t qcc74x_efuse_is_mac_address_slot_empty(uint8_t slot, uint8_t reload)
{
    uint32_t tmp1 = 0xffffffff, tmp2 = 0xffffffff;
    uint32_t part1Empty = 0, part2Empty = 0;

    if (slot == 0) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_WIFI_MAC_LOW_OFFSET, &tmp1, 1, reload);
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_WIFI_MAC_HIGH_OFFSET, &tmp2, 1, reload);
    } else if (slot == 1) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_SW_USAGE_2_OFFSET, &tmp1, 1, reload);
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_SW_USAGE_3_OFFSET, &tmp2, 1, reload);
    } else if (slot == 2) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_KEY_SLOT_11_W1_OFFSET, &tmp1, 1, reload);
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_KEY_SLOT_11_W2_OFFSET, &tmp2, 1, reload);
    }

    part1Empty = (qcc74x_ef_ctrl_is_all_bits_zero(tmp1, 0, 32));
    part2Empty = (qcc74x_ef_ctrl_is_all_bits_zero(tmp2, 0, 22));

    return (part1Empty && part2Empty);
}

/****************************************************************************/ /**
 * @brief  Efuse write optional MAC address
 *
 * @param  slot: MAC address slot
 * @param  mac[6]: MAC address buffer
 * @param  program: Whether program
 *
 * @return 0 or -1
 *
*******************************************************************************/
int qcc74x_efuse_write_mac_address_opt(uint8_t slot, uint8_t mac[6], uint8_t program)
{
    uint8_t *maclow = (uint8_t *)mac;
    uint8_t *machigh = (uint8_t *)(mac + 4);
    uint32_t tmpval;
    uint32_t i = 0, cnt;

    if (slot >= 3) {
        return -1;
    }

    /* Change to local order */
    for (i = 0; i < 3; i++) {
        tmpval = mac[i];
        mac[i] = mac[5 - i];
        mac[5 - i] = tmpval;
    }

    /* The low 32 bits */
    tmpval = QCC74x_RDWD_FRM_BYTEP(maclow);

    if (slot == 0) {
        qcc74x_ef_ctrl_write_direct(NULL, EF_DATA_EF_WIFI_MAC_LOW_OFFSET, &tmpval, 1, program);
    } else if (slot == 1) {
        qcc74x_ef_ctrl_write_direct(NULL, EF_DATA_EF_SW_USAGE_2_OFFSET, &tmpval, 1, program);
    } else if (slot == 2) {
        qcc74x_ef_ctrl_write_direct(NULL, EF_DATA_EF_KEY_SLOT_11_W1_OFFSET, &tmpval, 1, program);
    }

    /* The high 16 bits */
    tmpval = machigh[0] + (machigh[1] << 8);
    cnt = 0;

    for (i = 0; i < 6; i++) {
        cnt += qcc74x_ef_ctrl_get_byte_zero_cnt(mac[i]);
    }

    tmpval |= ((cnt & 0x3f) << 16);

    if (slot == 0) {
        qcc74x_ef_ctrl_write_direct(NULL, EF_DATA_EF_WIFI_MAC_HIGH_OFFSET, &tmpval, 1, program);
    } else if (slot == 1) {
        qcc74x_ef_ctrl_write_direct(NULL, EF_DATA_EF_SW_USAGE_3_OFFSET, &tmpval, 1, program);
    } else if (slot == 2) {
        qcc74x_ef_ctrl_write_direct(NULL, EF_DATA_EF_KEY_SLOT_11_W2_OFFSET, &tmpval, 1, program);
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Efuse read optional MAC address
 *
 * @param  slot: MAC address slot
 * @param  mac[6]: MAC address buffer
 * @param  reload: Whether reload
 *
 * @return 0 or -1
 *
*******************************************************************************/
int qcc74x_efuse_read_mac_address_opt(uint8_t slot, uint8_t mac[6], uint8_t reload)
{
    uint8_t *maclow = (uint8_t *)mac;
    uint8_t *machigh = (uint8_t *)(mac + 4);
    uint32_t tmpval = 0;
    uint32_t i = 0;
    uint32_t cnt = 0;

    if (slot >= 3) {
        return -1;
    }

    if (slot == 0) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_WIFI_MAC_LOW_OFFSET, &tmpval, 1, reload);
    } else if (slot == 1) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_SW_USAGE_2_OFFSET, &tmpval, 1, reload);
    } else if (slot == 2) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_KEY_SLOT_11_W1_OFFSET, &tmpval, 1, reload);
    }

    QCC74x_WRWD_TO_BYTEP(maclow, tmpval);

    if (slot == 0) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_WIFI_MAC_HIGH_OFFSET, &tmpval, 1, reload);
    } else if (slot == 1) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_SW_USAGE_3_OFFSET, &tmpval, 1, reload);
    } else if (slot == 2) {
        qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_KEY_SLOT_11_W2_OFFSET, &tmpval, 1, reload);
    }

    machigh[0] = tmpval & 0xff;
    machigh[1] = (tmpval >> 8) & 0xff;

    /* Check parity */
    for (i = 0; i < 6; i++) {
        cnt += qcc74x_ef_ctrl_get_byte_zero_cnt(mac[i]);
    }

    if ((cnt & 0x3f) == ((tmpval >> 16) & 0x3f)) {
        /* Change to network order */
        for (i = 0; i < 3; i++) {
            tmpval = mac[i];
            mac[i] = mac[5 - i];
            mac[5 - i] = tmpval;
        }
        return 0;
    } else {
        return -1;
    }
}

float qcc74x_efuse_get_adc_trim(void)
{
    qcc74x_ef_ctrl_com_trim_t trim;
    uint32_t tmp;

    float coe = 1.0;

    qcc74x_ef_ctrl_read_common_trim(NULL, "gpadc_gain", &trim, 1);

    if (trim.en) {
        if (trim.parity == qcc74x_ef_ctrl_get_trim_parity(trim.value, trim.len)) {
            tmp = trim.value;

            if (tmp & 0x800) {
                tmp = ~tmp;
                tmp += 1;
                tmp = tmp & 0xfff;
                coe = (1.0f + ((float)tmp / 2048.0f));
            } else {
                coe = (1.0f - ((float)tmp / 2048.0f));
            }
        }
    }

    return coe;
}

uint32_t qcc74x_efuse_get_adc_tsen_trim(void)
{
    qcc74x_ef_ctrl_com_trim_t trim;

    qcc74x_ef_ctrl_read_common_trim(NULL, "tsen", &trim, 1);
    if (trim.en) {
        if (trim.parity == qcc74x_ef_ctrl_get_trim_parity(trim.value, trim.len)) {
            return trim.value;
        }
    }

    return 2042;
}

void qcc74x_efuse_read_secure_boot(uint8_t *sign, uint8_t *aes)
{
    uint32_t tmpval = 0;

    qcc74x_ef_ctrl_read_direct(NULL, EF_DATA_EF_CFG_0_OFFSET, &tmpval, 1, 1);
    *sign = ((tmpval & EF_DATA_EF_SBOOT_SIGN_MODE_MSK) >> EF_DATA_EF_SBOOT_SIGN_MODE_POS) & 0x01;
    *aes = ((tmpval & EF_DATA_EF_SF_AES_MODE_MSK) >> EF_DATA_EF_SF_AES_MODE_POS);
}

int qcc74x_efuse_enable_aes(uint8_t aes_type, uint8_t xts_mode)
{
    uint32_t tmpval = aes_type;

    if(xts_mode){
        tmpval |= (xts_mode<<2);
    }

    qcc74x_ef_ctrl_write_direct(NULL, 0x00, &tmpval, 1, 1);

    return 0;
}

int qcc74x_efuse_rw_lock_aes_key(uint8_t key_index, uint8_t rd_lock, uint8_t wr_lock)
{
    uint32_t tmpval = 0;

    if(0 == key_index){
        if(wr_lock){
            tmpval |= (1 << 19);
        }
        if(rd_lock){
            tmpval |= (1 << 29);
        }
        qcc74x_ef_ctrl_write_direct(NULL, 0x7C, &tmpval, 1, 1);
    }else if(1 == key_index){
        if(wr_lock){
            tmpval |= (1 << 20);
        }
        if(rd_lock){
            tmpval |= (1 << 30);
        }
        qcc74x_ef_ctrl_write_direct(NULL, 0x7C, &tmpval, 1, 1);
    }else if(2 == key_index){
        if(wr_lock){
            tmpval |= (1 << 15);
        }
        if(rd_lock){
            tmpval |= (1 << 25);
        }
        qcc74x_ef_ctrl_write_direct(NULL, 0xFC, &tmpval, 1, 1);
    }else if(3 == key_index){
        if(wr_lock){
            tmpval |= (1 << 16);
        }
        if(rd_lock){
            tmpval |= (1 << 26);
        }
        qcc74x_ef_ctrl_write_direct(NULL, 0xFC, &tmpval, 1, 1);
    }

    return 0;
}

int qcc74x_efuse_rw_lock_dbg_key(uint8_t rd_lock, uint8_t wr_lock)
{
    uint32_t tmpval = 0;

    if(wr_lock){
        tmpval |= (1 << 15);
    }

    if(rd_lock){
        tmpval |= (1 << 26);
    }

    qcc74x_ef_ctrl_write_direct(NULL, 0x7C, &tmpval, 1, 1);

    return 0;
}

int qcc74x_efuse_write_lock_pk_hash(uint32_t pkhash_len)
{
    uint32_t tmpval = 0;

    if(256 == pkhash_len){
       tmpval = (1 << 17) | (1 << 18);
    }else{
       tmpval = (1 << 17);
    }

    qcc74x_ef_ctrl_write_direct(NULL, 0x7C, &tmpval, 1, 1);

    return 0;
}

int qcc74x_efuse_write_lock_usb_pid_vid(void)
{
    return 0;
}