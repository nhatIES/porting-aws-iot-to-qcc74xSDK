#include "qcc74x_core.h"
#include "partition.h"

/** @addtogroup  QCC74x_Common_Driver
 *  @{
 */

/** @addtogroup  PARTITION
 *  @{
 */

/** @defgroup  PARTITION_Private_Macros
 *  @{
 */

/*@} end of group PARTITION_Private_Macros */

/** @defgroup  PARTITION_Private_Types
 *  @{
 */

/*@} end of group PARTITION_Private_Types */

/** @defgroup  PARTITION_Private_Variables
 *  @{
 */
p_pt_table_flash_erase gp_pt_table_flash_erase = NULL;
p_pt_table_flash_write gp_pt_table_flash_write = NULL;
p_pt_table_flash_read gp_pt_table_flash_read = NULL;
pt_table_iap_param_type p_iap_param;

/*@} end of group PARTITION_Private_Variables */

/** @defgroup  PARTITION_Global_Variables
 *  @{
 */
extern int main(void);

/*@} end of group PARTITION_Global_Variables */

/** @defgroup  PARTITION_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PARTITION_Private_Fun_Declaration */

/** @defgroup  PARTITION_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Judge partition table valid
 *
 * @param  ptStuff: Partition table stuff pointer
 *
 * @return 0 for invalid and 1 for valid
 *
*******************************************************************************/
uint8_t pt_table_valid(pt_table_stuff_config *pt_stuff)
{
    pt_table_config *pt_table = &pt_stuff->pt_table;
    pt_table_entry_config *pt_entries = pt_stuff->pt_entries;
    uint32_t *p_crc32;
    uint32_t entriesLen = sizeof(pt_table_entry_config) * pt_table->entryCnt;

    if (pt_table->magicCode == QCC74x_PT_MAGIC_CODE) {
        if (pt_table->entryCnt > PT_ENTRY_MAX) {
            // BOOT2_MSG("PT Entry Count Error\r\n");
            return 0;
        }

        if (pt_table->crc32 !=
            QCC74x_Soft_CRC32((uint8_t *)pt_table, sizeof(pt_table_config) - 4)) {
            // BOOT2_MSG("PT CRC Error\r\n");
            return 0;
        }

        p_crc32 = (uint32_t *)((uintptr_t)pt_entries + entriesLen);

        if (*p_crc32 != QCC74x_Soft_CRC32((uint8_t *)pt_entries, entriesLen)) {
            // BOOT2_MSG("PT Entry CRC Error\r\n");
            return 0;
        }

        return 1;
    }

    return 0;
}

/*@} end of group PARTITION_Private_Functions */

/** @defgroup  PARTITION_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Register partition flash read write erase fucntion
 *
 * @param  erase: Flash erase function
 * @param  write: Flash write function
 * @param  read: Flash read function
 *
 * @return None
 *
*******************************************************************************/
void pt_table_set_flash_operation(p_pt_table_flash_erase erase, p_pt_table_flash_write write, p_pt_table_flash_read read)
{
    gp_pt_table_flash_erase = erase;
    gp_pt_table_flash_write = write;
    gp_pt_table_flash_read = read;
}

/****************************************************************************/ /**
 * @brief  Get active partition table whole stuff
 *
 * @param  ptStuff[2]: Partition table stuff pointer
 *
 * @return Active partition table ID
 *
*******************************************************************************/
pt_table_id_type pt_table_get_active_partition_need_lock(pt_table_stuff_config ptStuff[2])
{
    uint32_t pt_valid[2] = { 0, 0 };
    pt_table_id_type activePtID;

    if (ptStuff == NULL) {
        return PT_TABLE_ID_INVALID;
    }

    activePtID = PT_TABLE_ID_INVALID;

    gp_pt_table_flash_read(QCC74x_PT_TABLE0_ADDRESS, (uint8_t *)&ptStuff[0], sizeof(pt_table_stuff_config));
    pt_valid[0] = pt_table_valid(&ptStuff[0]);

    gp_pt_table_flash_read(QCC74x_PT_TABLE1_ADDRESS, (uint8_t *)&ptStuff[1], sizeof(pt_table_stuff_config));
    pt_valid[1] = pt_table_valid(&ptStuff[1]);

    if (pt_valid[0] == 1 && pt_valid[1] == 1) {
        if (ptStuff[0].pt_table.age >= ptStuff[1].pt_table.age) {
            activePtID = PT_TABLE_ID_0;
        } else {
            activePtID = PT_TABLE_ID_1;
        }
    } else if (pt_valid[0] == 1) {
        activePtID = PT_TABLE_ID_0;
    } else if (pt_valid[1] == 1) {
        activePtID = PT_TABLE_ID_1;
    }

    return activePtID;
}

/****************************************************************************/ /**
 * @brief  Get partition entry according to entry ID
 *
 * @param  ptStuff: Partition table stuff pointer
 * @param  type: Type of partition entry
 * @param  ptEntry: Partition entry pointer to store read data
 *
 * @return PT_ERROR_SUCCESS or PT_ERROR_ENTRY_NOT_FOUND or PT_ERROR_PARAMETER
 *
*******************************************************************************/
pt_table_error_type pt_table_get_active_entries_by_id(pt_table_stuff_config *pt_stuff,
                                                      pt_table_entry_type type,
                                                      pt_table_entry_config *pt_entry)
{
    uint32_t i = 0;

    if (pt_stuff == NULL || pt_entry == NULL) {
        return PT_ERROR_PARAMETER;
    }

    for (i = 0; i < pt_stuff->pt_table.entryCnt; i++) {
        if (pt_stuff->pt_entries[i].type == type) {
            arch_memcpy_fast(pt_entry, &pt_stuff->pt_entries[i], sizeof(pt_table_entry_config));
            return PT_ERROR_SUCCESS;
        }
    }

    return PT_ERROR_ENTRY_NOT_FOUND;
}

/****************************************************************************/ /**
 * @brief  Get partition entry according to entry name
 *
 * @param  ptStuff: Partition table stuff pointer
 * @param  name: Name of partition entry
 * @param  ptEntry: Partition entry pointer to store read data
 *
 * @return PT_ERROR_SUCCESS or PT_ERROR_ENTRY_NOT_FOUND or PT_ERROR_PARAMETER
 *
*******************************************************************************/
pt_table_error_type pt_table_get_active_entries_by_name(pt_table_stuff_config *pt_stuff,
                                                        uint8_t *name,
                                                        pt_table_entry_config *pt_entry)
{
    uint32_t i = 0;
    uint32_t len = strlen((char *)name);

    if (pt_stuff == NULL || pt_entry == NULL) {
        return PT_ERROR_PARAMETER;
    }

    for (i = 0; i < pt_stuff->pt_table.entryCnt; i++) {
        if (strlen((char *)pt_stuff->pt_entries[i].name) == len &&
            memcmp((char *)pt_stuff->pt_entries[i].name, (char *)name, len) == 0) {
            arch_memcpy_fast(pt_entry, &pt_stuff->pt_entries[i], sizeof(pt_table_entry_config));
            return PT_ERROR_SUCCESS;
        }
    }

    return PT_ERROR_ENTRY_NOT_FOUND;
}

/****************************************************************************/ /**
 * @brief  Update partition entry
 *
 * @param  targetTableID: Target partition table to update
 * @param  ptStuff: Partition table stuff pointer
 * @param  ptEntry: Partition entry pointer to update
 *
 * @return Partition update result
 *
*******************************************************************************/
pt_table_error_type pt_table_update_entry(pt_table_id_type target_table_id,
                                          pt_table_stuff_config *pt_stuff,
                                          pt_table_entry_config *pt_entry)
{
    uint32_t i = 0;
    QCC74x_Err_Type ret;
    uint32_t write_addr;
    uint32_t entries_len;
    pt_table_config *pt_table;
    pt_table_entry_config *pt_entries;
    uint32_t *crc32;

    if (pt_entry == NULL || pt_stuff == NULL) {
        return PT_ERROR_PARAMETER;
    }

    pt_table = &pt_stuff->pt_table;
    pt_entries = pt_stuff->pt_entries;

    if (target_table_id == PT_TABLE_ID_INVALID) {
        return PT_ERROR_TABLE_NOT_VALID;
    }

    if (target_table_id == PT_TABLE_ID_0) {
        write_addr = QCC74x_PT_TABLE0_ADDRESS;
    } else {
        write_addr = QCC74x_PT_TABLE1_ADDRESS;
    }

    for (i = 0; i < pt_table->entryCnt; i++) {
        if (pt_entries[i].type == pt_entry->type) {
            arch_memcpy_fast(&pt_entries[i], pt_entry, sizeof(pt_table_entry_config));
            break;
        }
    }

    if (i == pt_table->entryCnt) {
        /* Not found this entry ,add new one */
        if (pt_table->entryCnt < PT_ENTRY_MAX) {
            arch_memcpy_fast(&pt_entries[pt_table->entryCnt], pt_entry, sizeof(pt_table_entry_config));
            pt_table->entryCnt++;
        } else {
            return PT_ERROR_ENTRY_UPDATE_FAIL;
        }
    }

    /* Prepare write back to flash */
    /* Update age */
    pt_table->age++;
    pt_table->crc32 = QCC74x_Soft_CRC32((uint8_t *)pt_table, sizeof(pt_table_config) - 4);

    /* Update entries CRC */
    entries_len = pt_table->entryCnt * sizeof(pt_table_entry_config);
    crc32 = (uint32_t *)((uintptr_t)pt_entries + entries_len);
    *crc32 = QCC74x_Soft_CRC32((uint8_t *)&pt_entries[0], entries_len);

    /* Write back to flash */
    /* Erase flash first */
    //ret = gp_pt_table_flash_erase(write_addr, write_addr + sizeof(pt_table_config) + entries_len + 4 - 1);
    ret = gp_pt_table_flash_erase(write_addr, sizeof(pt_table_config) + entries_len + 4);

    if (ret != SUCCESS) {
        //LOG_D_ERR("Flash Erase error\r\n");
        return PT_ERROR_FALSH_WRITE;
    }

    /* Write flash */
    ret = gp_pt_table_flash_write(write_addr, (uint8_t *)pt_stuff, sizeof(pt_table_stuff_config));

    if (ret != SUCCESS) {
        //LOG_D_ERR("Flash Write error\r\n");
        return PT_ERROR_FALSH_WRITE;
    }

    return PT_ERROR_SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Create partition entry
 *
 * @param  ptID: Partition table ID
 *
 * @return Partition create result
 *
*******************************************************************************/
pt_table_error_type pt_table_create(pt_table_id_type pt_id)
{
    uint32_t write_addr;
    QCC74x_Err_Type ret;
    pt_table_config pt_table;

    if (pt_id == PT_TABLE_ID_INVALID) {
        return PT_ERROR_TABLE_NOT_VALID;
    }

    if (pt_id == PT_TABLE_ID_0) {
        write_addr = QCC74x_PT_TABLE0_ADDRESS;
    } else {
        write_addr = QCC74x_PT_TABLE1_ADDRESS;
    }

    /* Prepare write back to flash */
    pt_table.magicCode = QCC74x_PT_MAGIC_CODE;
    pt_table.version = 0;
    pt_table.entryCnt = 0;
    pt_table.age = 0;
    pt_table.crc32 = QCC74x_Soft_CRC32((uint8_t *)&pt_table, sizeof(pt_table_config) - 4);
    /* Write back to flash */
    //ret = gp_pt_table_flash_erase(write_addr, write_addr + sizeof(pt_table_config) - 1);
    ret = gp_pt_table_flash_erase(write_addr, sizeof(pt_table_config));

    if (ret != SUCCESS) {
        //LOG_D_ERR("Flash Erase error\r\n");
        return PT_ERROR_FALSH_ERASE;
    }

    ret = gp_pt_table_flash_write(write_addr, (uint8_t *)&pt_table, sizeof(pt_table_config));

    if (ret != SUCCESS) {
        //LOG_D_ERR("Flash Write error\r\n");
        return PT_ERROR_FALSH_WRITE;
    }

    return PT_ERROR_SUCCESS;
}

/****************************************************************************/ /**
 * @brief  create a default partition entry for fw to run
 *
 * @param  pt_stuff: pointer to pt_table_stuff_config
 *
 * @param  fw_addr: dafault fw address to run
 *
 * @return Partition create result
 *
*******************************************************************************/
void pt_table_init_default_fw(pt_table_stuff_config *pt_stuff, uint32_t fw_addr)
{
    pt_table_config *pt_table;
    pt_table_entry_config *pt_entries;

    memset(pt_stuff, 0, sizeof(pt_table_stuff_config));
    pt_table = &pt_stuff->pt_table;
    pt_entries = pt_stuff->pt_entries;

    /* Prepare write back to flash */
    pt_table->magicCode = QCC74x_PT_MAGIC_CODE;
    pt_table->version = 0;
    pt_table->entryCnt = 1;
    pt_table->age = 0;
    pt_table->crc32 = QCC74x_Soft_CRC32((uint8_t *)&pt_table, sizeof(pt_table_config) - 4);
    memcpy(pt_entries[0].name, "FW", 2);
    pt_entries[0].type = 0;
    pt_entries[0].device = 0;
    pt_entries[0].active_index = 0;
    pt_entries[0].start_address[0] = fw_addr;
    pt_entries[0].max_len[0] = 0;
    pt_entries[0].len = 0;
    pt_entries[0].age = 0;
}

pt_table_error_type pt_table_get_iap_para(pt_table_iap_param_type *para)
{
    uint32_t pt_valid[2] = { 0, 0 };
    pt_table_stuff_config pt_stuff[2];
    uint8_t active_index;

    gp_pt_table_flash_read(QCC74x_PT_TABLE0_ADDRESS, (uint8_t *)&pt_stuff[0], sizeof(pt_table_stuff_config));
    pt_valid[0] = pt_table_valid(&pt_stuff[0]);

    gp_pt_table_flash_read(QCC74x_PT_TABLE1_ADDRESS, (uint8_t *)&pt_stuff[1], sizeof(pt_table_stuff_config));
    pt_valid[1] = pt_table_valid(&pt_stuff[1]);

    if ((pt_valid[0] == 1) && (pt_valid[1] == 1)) {
        if (pt_stuff[0].pt_table.age >= pt_stuff[1].pt_table.age) {
            active_index = pt_stuff[0].pt_entries[0].active_index;
            para->iap_write_addr = para->iap_start_addr = pt_stuff[0].pt_entries[0].start_address[!(active_index & 0x01)];
            para->inactive_index = !(active_index & 0x01);
            para->inactive_table_index = 1;

        } else {
            active_index = pt_stuff[1].pt_entries[0].active_index;
            para->iap_write_addr = para->iap_start_addr = pt_stuff[1].pt_entries[0].start_address[!(active_index & 0x01)];
            para->inactive_index = !(active_index & 0x01);
            para->inactive_table_index = 0;
        }

    } else if (pt_valid[1] == 1) {
        active_index = pt_stuff[1].pt_entries[0].active_index;
        para->iap_write_addr = para->iap_start_addr = pt_stuff[1].pt_entries[0].start_address[!(active_index & 0x01)];
        para->inactive_index = !(active_index & 0x01);
        para->inactive_table_index = 0;
    } else if (pt_valid[0] == 1) {
        active_index = pt_stuff[0].pt_entries[0].active_index;
        para->iap_write_addr = para->iap_start_addr = pt_stuff[0].pt_entries[0].start_address[!(active_index & 0x01)];
        para->inactive_index = !(active_index & 0x01);
        para->inactive_table_index = 1;
    } else {
        return PT_ERROR_TABLE_NOT_VALID;
    }

    BOOT2_MSG("inactive_table_index %d, inactive index %d , IAP start addr %x \r\n", para->inactive_table_index, para->inactive_index, para->iap_start_addr);
    return PT_ERROR_SUCCESS;
}

pt_table_error_type pt_table_set_iap_para(pt_table_iap_param_type *para)
{
    pt_table_stuff_config pt_stuff, pt_stuff_write;
    int32_t ret;
    uint32_t *p_crc32;
    uint32_t entries_len;

    if (para->inactive_table_index == 1) {
        gp_pt_table_flash_read(QCC74x_PT_TABLE0_ADDRESS, (uint8_t *)&pt_stuff, sizeof(pt_table_stuff_config));
    } else if (para->inactive_table_index == 0) {
        gp_pt_table_flash_read(QCC74x_PT_TABLE1_ADDRESS, (uint8_t *)&pt_stuff, sizeof(pt_table_stuff_config));
    }

    arch_memcpy_fast((void *)&pt_stuff_write, (void *)&pt_stuff, sizeof(pt_table_stuff_config));
    pt_stuff_write.pt_table.age += 1;
    pt_stuff_write.pt_entries[0].active_index = !(pt_stuff_write.pt_entries[0].active_index & 0x01);
    pt_stuff_write.pt_table.crc32 = QCC74x_Soft_CRC32((uint8_t *)&pt_stuff_write, sizeof(pt_table_config) - 4);
    entries_len = sizeof(pt_table_entry_config) * pt_stuff_write.pt_table.entryCnt;
    //pt_stuff_write.crc32 = QCC74x_Soft_CRC32((uint8_t*)pt_stuff_write.pt_entries,entries_len);
    p_crc32 = (uint32_t *)((uintptr_t)pt_stuff_write.pt_entries + entries_len);
    *p_crc32 = QCC74x_Soft_CRC32((uint8_t *)pt_stuff_write.pt_entries, entries_len);

    if (para->inactive_table_index == 1) {
        //ret = gp_pt_table_flash_erase(QCC74x_PT_TABLE1_ADDRESS, QCC74x_PT_TABLE1_ADDRESS + sizeof(pt_table_stuff_config) - 1);
        ret = gp_pt_table_flash_erase(QCC74x_PT_TABLE1_ADDRESS, sizeof(pt_table_stuff_config));

        if (ret != SUCCESS) {
            //LOG_D_ERR("Flash Erase error\r\n");
            return PT_ERROR_FALSH_ERASE;
        }

        ret = gp_pt_table_flash_write(QCC74x_PT_TABLE1_ADDRESS, (uint8_t *)&pt_stuff_write, sizeof(pt_table_stuff_config));

        if (ret != SUCCESS) {
            //LOG_D_ERR("Flash Write error\r\n");
            return PT_ERROR_FALSH_WRITE;
        }
    } else if (para->inactive_table_index == 0) {
        //ret = gp_pt_table_flash_erase(QCC74x_PT_TABLE0_ADDRESS, QCC74x_PT_TABLE0_ADDRESS + sizeof(pt_table_stuff_config) - 1);
        ret = gp_pt_table_flash_erase(QCC74x_PT_TABLE0_ADDRESS, sizeof(pt_table_stuff_config));

        if (ret != SUCCESS) {
            //LOG_D_ERR("Flash Erase error\r\n");
            return PT_ERROR_FALSH_ERASE;
        }

        ret = gp_pt_table_flash_write(QCC74x_PT_TABLE0_ADDRESS, (uint8_t *)&pt_stuff_write, sizeof(pt_table_stuff_config));

        if (ret != SUCCESS) {
            //LOG_D_ERR("Flash Write error\r\n");
            return PT_ERROR_FALSH_WRITE;
        }
    }

    BOOT2_MSG("Update pt_table suss\r\n");
    return PT_ERROR_SUCCESS;
}

/*@} end of group PARTITION_Public_Functions */

/*@} end of group PARTITION */

/*@} end of group QCC74x_Common_Driver */
