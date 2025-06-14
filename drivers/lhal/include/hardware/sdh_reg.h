#ifndef __SDH_REG_H__
#define __SDH_REG_H__

#if defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
#define SDH_STD_V3
#elif defined(QCC74x_undef) || defined(QCC74x_undef)
#define SDH_STD_V3_SMIH
#endif

#define SDH_SYS_ADDR_LOW_OFFSET                 (0x00)  /* System Address Low Register */
#define SDH_SYS_ADDR_HIGH_OFFSET                (0x02)  /* System Address High Register */
#define SDH_BLOCK_SIZE_OFFSET                   (0x04)  /* Block Size Register */
#define SDH_BLOCK_COUNT_OFFSET                  (0x06)  /* Block Count Register */
#define SDH_ARG_LOW_OFFSET                      (0x08)  /* Argument Low Register */
#define SDH_ARG_HIGH_OFFSET                     (0x0A)  /* Argument High Register */
#define SDH_TRANSFER_MODE_OFFSET                (0x0C)  /* Transfer Mode Register */
#define SDH_CMD_OFFSET                          (0x0E)  /* Command Register */
#define SDH_RESP_0_OFFSET                       (0x10)  /* Response Register 0 */
#define SDH_RESP_1_OFFSET                       (0x12)  /* Response Register 1 */
#define SDH_RESP_2_OFFSET                       (0x14)  /* Response Register 2 */
#define SDH_RESP_3_OFFSET                       (0x16)  /* Response Register 3 */
#define SDH_RESP_4_OFFSET                       (0x18)  /* Response Register 4 */
#define SDH_RESP_5_OFFSET                       (0x1A)  /* Response Register 5 */
#define SDH_RESP_6_OFFSET                       (0x1C)  /* Response Register 6 */
#define SDH_RESP_7_OFFSET                       (0x1E)  /* Response Register 7 */
#define SDH_BUFFER_DATA_PORT_0_OFFSET           (0x20)  /* Buffer Data Port 0 Register */
#define SDH_BUFFER_DATA_PORT_1_OFFSET           (0x22)  /* Buffer Data Port 1 Register */
#define SDH_PRESENT_STATE_1_OFFSET              (0x24)  /* Present State Register 1 */
#define SDH_PRESENT_STATE_2_OFFSET              (0x26)  /* Present State Register 2 */
#define SDH_HOST_CTRL_OFFSET                    (0x28)  /* Host Control Register */
#define SDH_BLOCK_GAP_CTRL_OFFSET               (0x2A)  /* Block Gap Control Register */
#define SDH_CLOCK_CTRL_OFFSET                   (0x2C)  /* Clock Control Register */
#define SDH_TIMEOUT_CTRL_SW_RESET_OFFSET        (0x2E)  /* Timeout Control/Software Reset Register */
#define SDH_NORMAL_INT_STATUS_OFFSET            (0x30)  /* Normal Interrupt Status Register */
#define SDH_ERROR_INT_STATUS_OFFSET             (0x32)  /* Error Interrupt Status Register */
#define SDH_NORMAL_INT_STATUS_EN_OFFSET         (0x34)  /* Normal Interrupt Status Enable Register */
#define SDH_ERROR_INT_STATUS_EN_OFFSET          (0x36)  /* Error Interrupt Status Enable Register */
#define SDH_NORMAL_INT_STATUS_INT_EN_OFFSET     (0x38)  /* Normal Interrupt Status Interrupt Enable Register */
#define SDH_ERROR_INT_STATUS_INT_EN_OFFSET      (0x3A)  /* Error Interrupt Status Interrupt Enable Register */
#define SDH_AUTO_CMD12_ERROR_STATUS_OFFSET      (0x3C)  /* Auto CMD12 Error Status Register */
#define SDH_HOST_CTRL_2_OFFSET                  (0x3e)  /* Host Control 2 Register */
#define SDH_CAPABILITIES_1_OFFSET               (0x40)  /* Capabilities Register 1 */
#define SDH_CAPABILITIES_2_OFFSET               (0x42)  /* Capabilities Register 2 */
#define SDH_CAPABILITIES_3_OFFSET               (0x44)  /* Capabilities Register 3 */
#define SDH_CAPABILITIES_4_OFFSET               (0x46)  /* Capabilities Register 4 */
#define SDH_MAX_CURRENT_1_OFFSET                (0x48)  /* Maximum Current Register 1 */
#define SDH_MAX_CURRENT_2_OFFSET                (0x4A)  /* Maximum Current Register 2 */
#define SDH_MAX_CURRENT_3_OFFSET                (0x4C)  /* Maximum Current Register 3 */
#define SDH_MAX_CURRENT_4_OFFSET                (0x4E)  /* Maximum Current Register 4 */
#define SDH_FORCE_EVENT_AUTO_CMD12_ERROR_OFFSET (0x50)  /* Force Event Auto cmd12 Error Register */
#define SDH_FORCE_EVENT_FOR_ERROR_STATUS_OFFSET (0x52)  /* Force Event for Error Status Register */
#define SDH_ADMA_ERROR_STATUS_OFFSET            (0x54)  /* ADMA Error Status Register */
#define SDH_ADMA_SYS_ADDR_1_OFFSET              (0x58)  /* ADMA System Address Register 1 */
#define SDH_ADMA_SYS_ADDR_2_OFFSET              (0x5A)  /* ADMA System Address Register 2 */
#define SDH_ADMA_SYS_ADDR_3_OFFSET              (0x5C)  /* ADMA System Address Register 3 */
#define SDH_ADMA_SYS_ADDR_4_OFFSET              (0x5E)  /* ADMA System Address Register 4 */
#define SDH_PRESET_VALUE_FOR_INIT_OFFSET        (0x60)  /* Preset Value Register for Initialization */
#define SDH_PRESET_VALUE_FOR_DS_OFFSET          (0x62)  /* Preset Value Register for Default Speed */
#define SDH_PRESET_VALUE_FOR_HS_OFFSET          (0x64)  /* Preset Value Register for High Speed */
#define SDH_PRESET_VALUE_FOR_SDR12_OFFSET       (0x66)  /* Preset Value Register for SDR12 */
#define SDH_PRESET_VALUE_FOR_SDR25_OFFSET       (0x68)  /* Preset Value Register for SDR25 */
#define SDH_PRESET_VALUE_FOR_SDR50_OFFSET       (0x6a)  /* Preset Value Register for SDR50 */
#define SDH_PRESET_VALUE_FOR_SDR104_OFFSET      (0x6c)  /* Preset Value Register for SDR104 */
#define SDH_PRESET_VALUE_FOR_DDR50_OFFSET       (0x6e)  /* Preset Value Register for DDR50 */
#define SDH_SHARED_BUS_CTRL_OFFSET              (0xe0)  /* Shared Bus Control Register */
#define SDH_SLOT_INT_STATUS_OFFSET              (0xFC)  /* Slot Interrupt Status Register */
#define SDH_HOST_CTRL_VER_OFFSET                (0xFE)  /* Host Control Version Register */

#ifdef SDH_STD_V3
#define SDH_CFG_FIFO_PARAM_OFFSET               (0x100) /*: SD Extra Parameters Register */
#define SDH_FIFO_PARAM_OFFSET                   (0x104) /*: FIFO Parameters Register */
#define SDH_SPI_MODE_OFFSET                     (0x108) /*: SPI Mode Register */
#define SDH_CLOCK_AND_BURST_SIZE_SETUP_OFFSET   (0x10a) /*: Clock and Burst Size Setup Register */
#define SDH_CE_ATA_1_OFFSET                     (0x10c) /*: CE-ATA Register 1 */
#define SDH_CE_ATA_2_OFFSET                     (0x10e) /*: CE-ATA Register 2 */
#define SDH_PAD_IO_SETUP_OFFSET                 (0x110) /*: PAD I/O Setup Register */
#define SDH_RX_CFG_REG_OFFSET                   (0x114) /*: RX Configuration Register */
#define SDH_TX_CFG_REG_OFFSET                   (0x118) /*: TX Configuration Register */
#define SDH_TUNING_CFG_REG_OFFSET               (0x11c) /*: TUNING CONFIG Register */
#endif

/* 0x00 : System Address Low Register */
#define SDH_DMA_ADDR_L                          SDH_DMA_ADDR_L
#define SDH_DMA_ADDR_L_POS                      (0U)
#define SDH_DMA_ADDR_L_LEN                      (16U)
#define SDH_DMA_ADDR_L_MSK                      (((1U << SDH_DMA_ADDR_L_LEN) - 1) << SDH_DMA_ADDR_L_POS)
#define SDH_DMA_ADDR_L_UMSK                     (~(((1U << SDH_DMA_ADDR_L_LEN) - 1) << SDH_DMA_ADDR_L_POS))

/* 0x02 : System Address High Register */
#define SDH_DMA_ADDR_H                          SDH_DMA_ADDR_H
#define SDH_DMA_ADDR_H_POS                      (0U)
#define SDH_DMA_ADDR_H_LEN                      (16U)
#define SDH_DMA_ADDR_H_MSK                      (((1U << SDH_DMA_ADDR_H_LEN) - 1) << SDH_DMA_ADDR_H_POS)
#define SDH_DMA_ADDR_H_UMSK                     (~(((1U << SDH_DMA_ADDR_H_LEN) - 1) << SDH_DMA_ADDR_H_POS))

/* 0x04 : Block Size Register */
#define SDH_BLOCK_SIZE                          SDH_BLOCK_SIZE
#define SDH_BLOCK_SIZE_POS                      (0U)
#define SDH_BLOCK_SIZE_LEN                      (12U)
#define SDH_BLOCK_SIZE_MSK                      (((1U << SDH_BLOCK_SIZE_LEN) - 1) << SDH_BLOCK_SIZE_POS)
#define SDH_BLOCK_SIZE_UMSK                     (~(((1U << SDH_BLOCK_SIZE_LEN) - 1) << SDH_BLOCK_SIZE_POS))
#define SDH_HOST_DMA_BDRY                       SDH_HOST_DMA_BDRY
#define SDH_HOST_DMA_BDRY_POS                   (12U)
#define SDH_HOST_DMA_BDRY_LEN                   (3U)
#define SDH_HOST_DMA_BDRY_MSK                   (((1U << SDH_HOST_DMA_BDRY_LEN) - 1) << SDH_HOST_DMA_BDRY_POS)
#define SDH_HOST_DMA_BDRY_UMSK                  (~(((1U << SDH_HOST_DMA_BDRY_LEN) - 1) << SDH_HOST_DMA_BDRY_POS))

/* 0x06 : Block Count Register */
#define SDH_BLOCK_COUNT                         SDH_BLOCK_COUNT
#define SDH_BLOCK_COUNT_POS                     (0U)
#define SDH_BLOCK_COUNT_LEN                     (16U)
#define SDH_BLOCK_COUNT_MSK                     (((1U << SDH_BLOCK_COUNT_LEN) - 1) << SDH_BLOCK_COUNT_POS)
#define SDH_BLOCK_COUNT_UMSK                    (~(((1U << SDH_BLOCK_COUNT_LEN) - 1) << SDH_BLOCK_COUNT_POS))

/* 0x08 : Argument Low Register */
#define SDH_ARG_L                               SDH_ARG_L
#define SDH_ARG_L_POS                           (0U)
#define SDH_ARG_L_LEN                           (16U)
#define SDH_ARG_L_MSK                           (((1U << SDH_ARG_L_LEN) - 1) << SDH_ARG_L_POS)
#define SDH_ARG_L_UMSK                          (~(((1U << SDH_ARG_L_LEN) - 1) << SDH_ARG_L_POS))

/* 0x0A : Argument High Register */
#define SDH_ARG_H                               SDH_ARG_H
#define SDH_ARG_H_POS                           (0U)
#define SDH_ARG_H_LEN                           (16U)
#define SDH_ARG_H_MSK                           (((1U << SDH_ARG_H_LEN) - 1) << SDH_ARG_H_POS)
#define SDH_ARG_H_UMSK                          (~(((1U << SDH_ARG_H_LEN) - 1) << SDH_ARG_H_POS))

/* 0x0C : Transfer Mode Register */
#define SDH_DMA_EN                              SDH_DMA_EN
#define SDH_DMA_EN_POS                          (0U)
#define SDH_DMA_EN_LEN                          (1U)
#define SDH_DMA_EN_MSK                          (((1U << SDH_DMA_EN_LEN) - 1) << SDH_DMA_EN_POS)
#define SDH_DMA_EN_UMSK                         (~(((1U << SDH_DMA_EN_LEN) - 1) << SDH_DMA_EN_POS))
#define SDH_BLK_CNT_EN                          SDH_BLK_CNT_EN
#define SDH_BLK_CNT_EN_POS                      (1U)
#define SDH_BLK_CNT_EN_LEN                      (1U)
#define SDH_BLK_CNT_EN_MSK                      (((1U << SDH_BLK_CNT_EN_LEN) - 1) << SDH_BLK_CNT_EN_POS)
#define SDH_BLK_CNT_EN_UMSK                     (~(((1U << SDH_BLK_CNT_EN_LEN) - 1) << SDH_BLK_CNT_EN_POS))
#define SDH_AUTO_CMD_EN                         SDH_AUTO_CMD_EN
#define SDH_AUTO_CMD_EN_POS                     (2U)
#define SDH_AUTO_CMD_EN_LEN                     (2U)
#define SDH_AUTO_CMD_EN_MSK                     (((1U << SDH_AUTO_CMD_EN_LEN) - 1) << SDH_AUTO_CMD_EN_POS)
#define SDH_AUTO_CMD_EN_UMSK                    (~(((1U << SDH_AUTO_CMD_EN_LEN) - 1) << SDH_AUTO_CMD_EN_POS))
#define SDH_TO_HOST_DIR                         SDH_TO_HOST_DIR
#define SDH_TO_HOST_DIR_POS                     (4U)
#define SDH_TO_HOST_DIR_LEN                     (1U)
#define SDH_TO_HOST_DIR_MSK                     (((1U << SDH_TO_HOST_DIR_LEN) - 1) << SDH_TO_HOST_DIR_POS)
#define SDH_TO_HOST_DIR_UMSK                    (~(((1U << SDH_TO_HOST_DIR_LEN) - 1) << SDH_TO_HOST_DIR_POS))
#define SDH_MULTI_BLK_SEL                       SDH_MULTI_BLK_SEL
#define SDH_MULTI_BLK_SEL_POS                   (5U)
#define SDH_MULTI_BLK_SEL_LEN                   (1U)
#define SDH_MULTI_BLK_SEL_MSK                   (((1U << SDH_MULTI_BLK_SEL_LEN) - 1) << SDH_MULTI_BLK_SEL_POS)
#define SDH_MULTI_BLK_SEL_UMSK                  (~(((1U << SDH_MULTI_BLK_SEL_LEN) - 1) << SDH_MULTI_BLK_SEL_POS))

/* 0x0E : Command Register */
#define SDH_RESP_TYPE                           SDH_RESP_TYPE
#define SDH_RESP_TYPE_POS                       (0U)
#define SDH_RESP_TYPE_LEN                       (2U)
#define SDH_RESP_TYPE_MSK                       (((1U << SDH_RESP_TYPE_LEN) - 1) << SDH_RESP_TYPE_POS)
#define SDH_RESP_TYPE_UMSK                      (~(((1U << SDH_RESP_TYPE_LEN) - 1) << SDH_RESP_TYPE_POS))
#define SDH_CMD_CRC_CHK_EN                      SDH_CMD_CRC_CHK_EN
#define SDH_CMD_CRC_CHK_EN_POS                  (3U)
#define SDH_CMD_CRC_CHK_EN_LEN                  (1U)
#define SDH_CMD_CRC_CHK_EN_MSK                  (((1U << SDH_CMD_CRC_CHK_EN_LEN) - 1) << SDH_CMD_CRC_CHK_EN_POS)
#define SDH_CMD_CRC_CHK_EN_UMSK                 (~(((1U << SDH_CMD_CRC_CHK_EN_LEN) - 1) << SDH_CMD_CRC_CHK_EN_POS))
#define SDH_CMD_INDEX_CHK_EN                    SDH_CMD_INDEX_CHK_EN
#define SDH_CMD_INDEX_CHK_EN_POS                (4U)
#define SDH_CMD_INDEX_CHK_EN_LEN                (1U)
#define SDH_CMD_INDEX_CHK_EN_MSK                (((1U << SDH_CMD_INDEX_CHK_EN_LEN) - 1) << SDH_CMD_INDEX_CHK_EN_POS)
#define SDH_CMD_INDEX_CHK_EN_UMSK               (~(((1U << SDH_CMD_INDEX_CHK_EN_LEN) - 1) << SDH_CMD_INDEX_CHK_EN_POS))
#define SDH_DATA_PRESENT                        SDH_DATA_PRESENT
#define SDH_DATA_PRESENT_POS                    (5U)
#define SDH_DATA_PRESENT_LEN                    (1U)
#define SDH_DATA_PRESENT_MSK                    (((1U << SDH_DATA_PRESENT_LEN) - 1) << SDH_DATA_PRESENT_POS)
#define SDH_DATA_PRESENT_UMSK                   (~(((1U << SDH_DATA_PRESENT_LEN) - 1) << SDH_DATA_PRESENT_POS))
#define SDH_CMD_TYPE                            SDH_CMD_TYPE
#define SDH_CMD_TYPE_POS                        (6U)
#define SDH_CMD_TYPE_LEN                        (2U)
#define SDH_CMD_TYPE_MSK                        (((1U << SDH_CMD_TYPE_LEN) - 1) << SDH_CMD_TYPE_POS)
#define SDH_CMD_TYPE_UMSK                       (~(((1U << SDH_CMD_TYPE_LEN) - 1) << SDH_CMD_TYPE_POS))
#define SDH_CMD_INDEX                           SDH_CMD_INDEX
#define SDH_CMD_INDEX_POS                       (8U)
#define SDH_CMD_INDEX_LEN                       (6U)
#define SDH_CMD_INDEX_MSK                       (((1U << SDH_CMD_INDEX_LEN) - 1) << SDH_CMD_INDEX_POS)
#define SDH_CMD_INDEX_UMSK                      (~(((1U << SDH_CMD_INDEX_LEN) - 1) << SDH_CMD_INDEX_POS))

/* 0x10 : Response Register 0 */
#define SDH_RESP0                               SDH_RESP0
#define SDH_RESP0_POS                           (0U)
#define SDH_RESP0_LEN                           (16U)
#define SDH_RESP0_MSK                           (((1U << SDH_RESP0_LEN) - 1) << SDH_RESP0_POS)
#define SDH_RESP0_UMSK                          (~(((1U << SDH_RESP0_LEN) - 1) << SDH_RESP0_POS))

/* 0x12 : Response Register 1 */
#define SDH_RESP1                               SDH_RESP1
#define SDH_RESP1_POS                           (0U)
#define SDH_RESP1_LEN                           (16U)
#define SDH_RESP1_MSK                           (((1U << SDH_RESP1_LEN) - 1) << SDH_RESP1_POS)
#define SDH_RESP1_UMSK                          (~(((1U << SDH_RESP1_LEN) - 1) << SDH_RESP1_POS))

/* 0x14 : Response Register 2 */
#define SDH_RESP2                               SDH_RESP2
#define SDH_RESP2_POS                           (0U)
#define SDH_RESP2_LEN                           (16U)
#define SDH_RESP2_MSK                           (((1U << SDH_RESP2_LEN) - 1) << SDH_RESP2_POS)
#define SDH_RESP2_UMSK                          (~(((1U << SDH_RESP2_LEN) - 1) << SDH_RESP2_POS))

/* 0x16 : Response Register 3 */
#define SDH_RESP3                               SDH_RESP3
#define SDH_RESP3_POS                           (0U)
#define SDH_RESP3_LEN                           (16U)
#define SDH_RESP3_MSK                           (((1U << SDH_RESP3_LEN) - 1) << SDH_RESP3_POS)
#define SDH_RESP3_UMSK                          (~(((1U << SDH_RESP3_LEN) - 1) << SDH_RESP3_POS))

/* 0x18 : Response Register 4 */
#define SDH_RESP4                               SDH_RESP4
#define SDH_RESP4_POS                           (0U)
#define SDH_RESP4_LEN                           (16U)
#define SDH_RESP4_MSK                           (((1U << SDH_RESP4_LEN) - 1) << SDH_RESP4_POS)
#define SDH_RESP4_UMSK                          (~(((1U << SDH_RESP4_LEN) - 1) << SDH_RESP4_POS))

/* 0x1A : Response Register 5 */
#define SDH_RESP5                               SDH_RESP5
#define SDH_RESP5_POS                           (0U)
#define SDH_RESP5_LEN                           (16U)
#define SDH_RESP5_MSK                           (((1U << SDH_RESP5_LEN) - 1) << SDH_RESP5_POS)
#define SDH_RESP5_UMSK                          (~(((1U << SDH_RESP5_LEN) - 1) << SDH_RESP5_POS))

/* 0x1C : Response Register 6 */
#define SDH_RESP6                               SDH_RESP6
#define SDH_RESP6_POS                           (0U)
#define SDH_RESP6_LEN                           (16U)
#define SDH_RESP6_MSK                           (((1U << SDH_RESP6_LEN) - 1) << SDH_RESP6_POS)
#define SDH_RESP6_UMSK                          (~(((1U << SDH_RESP6_LEN) - 1) << SDH_RESP6_POS))

/* 0x1E : Response Register 7 */
#define SDH_RESP7                               SDH_RESP7
#define SDH_RESP7_POS                           (0U)
#define SDH_RESP7_LEN                           (16U)
#define SDH_RESP7_MSK                           (((1U << SDH_RESP7_LEN) - 1) << SDH_RESP7_POS)
#define SDH_RESP7_UMSK                          (~(((1U << SDH_RESP7_LEN) - 1) << SDH_RESP7_POS))

/* 0x20 : Buffer Data Port 0 Register */
#define SDH_CPU_DATA0                           SDH_CPU_DATA0
#define SDH_CPU_DATA0_POS                       (0U)
#define SDH_CPU_DATA0_LEN                       (16U)
#define SDH_CPU_DATA0_MSK                       (((1U << SDH_CPU_DATA0_LEN) - 1) << SDH_CPU_DATA0_POS)
#define SDH_CPU_DATA0_UMSK                      (~(((1U << SDH_CPU_DATA0_LEN) - 1) << SDH_CPU_DATA0_POS))

/* 0x22 : Buffer Data Port 1 Register */
#define SDH_CPU_DATA1                           SDH_CPU_DATA1
#define SDH_CPU_DATA1_POS                       (0U)
#define SDH_CPU_DATA1_LEN                       (16U)
#define SDH_CPU_DATA1_MSK                       (((1U << SDH_CPU_DATA1_LEN) - 1) << SDH_CPU_DATA1_POS)
#define SDH_CPU_DATA1_UMSK                      (~(((1U << SDH_CPU_DATA1_LEN) - 1) << SDH_CPU_DATA1_POS))

/* 0x24 : Present State Register 1 */
#define SDH_CMD_INHIBIT_CMD                     SDH_CMD_INHIBIT_CMD
#define SDH_CMD_INHIBIT_CMD_POS                 (0U)
#define SDH_CMD_INHIBIT_CMD_LEN                 (1U)
#define SDH_CMD_INHIBIT_CMD_MSK                 (((1U << SDH_CMD_INHIBIT_CMD_LEN) - 1) << SDH_CMD_INHIBIT_CMD_POS)
#define SDH_CMD_INHIBIT_CMD_UMSK                (~(((1U << SDH_CMD_INHIBIT_CMD_LEN) - 1) << SDH_CMD_INHIBIT_CMD_POS))
#define SDH_CMD_INHIBIT_DAT                     SDH_CMD_INHIBIT_DAT
#define SDH_CMD_INHIBIT_DAT_POS                 (1U)
#define SDH_CMD_INHIBIT_DAT_LEN                 (1U)
#define SDH_CMD_INHIBIT_DAT_MSK                 (((1U << SDH_CMD_INHIBIT_DAT_LEN) - 1) << SDH_CMD_INHIBIT_DAT_POS)
#define SDH_CMD_INHIBIT_DAT_UMSK                (~(((1U << SDH_CMD_INHIBIT_DAT_LEN) - 1) << SDH_CMD_INHIBIT_DAT_POS))
#define SDH__DAT_ACTIVE                         SDH__DAT_ACTIVE
#define SDH__DAT_ACTIVE_POS                     (2U)
#define SDH__DAT_ACTIVE_LEN                     (1U)
#define SDH__DAT_ACTIVE_MSK                     (((1U << SDH__DAT_ACTIVE_LEN) - 1) << SDH__DAT_ACTIVE_POS)
#define SDH__DAT_ACTIVE_UMSK                    (~(((1U << SDH__DAT_ACTIVE_LEN) - 1) << SDH__DAT_ACTIVE_POS))
#define SDH_RETUNING_REQ                        SDH_RETUNING_REQ
#define SDH_RETUNING_REQ_POS                    (3U)
#define SDH_RETUNING_REQ_LEN                    (1U)
#define SDH_RETUNING_REQ_MSK                    (((1U << SDH_RETUNING_REQ_LEN) - 1) << SDH_RETUNING_REQ_POS)
#define SDH_RETUNING_REQ_UMSK                   (~(((1U << SDH_RETUNING_REQ_LEN) - 1) << SDH_RETUNING_REQ_POS))
#define SDH_TX_ACTIVE                           SDH_TX_ACTIVE
#define SDH_TX_ACTIVE_POS                       (8U)
#define SDH_TX_ACTIVE_LEN                       (1U)
#define SDH_TX_ACTIVE_MSK                       (((1U << SDH_TX_ACTIVE_LEN) - 1) << SDH_TX_ACTIVE_POS)
#define SDH_TX_ACTIVE_UMSK                      (~(((1U << SDH_TX_ACTIVE_LEN) - 1) << SDH_TX_ACTIVE_POS))
#define SDH_RX_ACTIVE                           SDH_RX_ACTIVE
#define SDH_RX_ACTIVE_POS                       (9U)
#define SDH_RX_ACTIVE_LEN                       (1U)
#define SDH_RX_ACTIVE_MSK                       (((1U << SDH_RX_ACTIVE_LEN) - 1) << SDH_RX_ACTIVE_POS)
#define SDH_RX_ACTIVE_UMSK                      (~(((1U << SDH_RX_ACTIVE_LEN) - 1) << SDH_RX_ACTIVE_POS))
#define SDH_BUFFER_WR_EN                        SDH_BUFFER_WR_EN
#define SDH_BUFFER_WR_EN_POS                    (10U)
#define SDH_BUFFER_WR_EN_LEN                    (1U)
#define SDH_BUFFER_WR_EN_MSK                    (((1U << SDH_BUFFER_WR_EN_LEN) - 1) << SDH_BUFFER_WR_EN_POS)
#define SDH_BUFFER_WR_EN_UMSK                   (~(((1U << SDH_BUFFER_WR_EN_LEN) - 1) << SDH_BUFFER_WR_EN_POS))
#define SDH_BUFFER_RD_EN                        SDH_BUFFER_RD_EN
#define SDH_BUFFER_RD_EN_POS                    (11U)
#define SDH_BUFFER_RD_EN_LEN                    (1U)
#define SDH_BUFFER_RD_EN_MSK                    (((1U << SDH_BUFFER_RD_EN_LEN) - 1) << SDH_BUFFER_RD_EN_POS)
#define SDH_BUFFER_RD_EN_UMSK                   (~(((1U << SDH_BUFFER_RD_EN_LEN) - 1) << SDH_BUFFER_RD_EN_POS))

/* 0x26 : Present State Register 2 */
#define SDH_CARD_INSERTED                       SDH_CARD_INSERTED
#define SDH_CARD_INSERTED_POS                   (0U)
#define SDH_CARD_INSERTED_LEN                   (1U)
#define SDH_CARD_INSERTED_MSK                   (((1U << SDH_CARD_INSERTED_LEN) - 1) << SDH_CARD_INSERTED_POS)
#define SDH_CARD_INSERTED_UMSK                  (~(((1U << SDH_CARD_INSERTED_LEN) - 1) << SDH_CARD_INSERTED_POS))
#define SDH_CARD_STABLE                         SDH_CARD_STABLE
#define SDH_CARD_STABLE_POS                     (1U)
#define SDH_CARD_STABLE_LEN                     (1U)
#define SDH_CARD_STABLE_MSK                     (((1U << SDH_CARD_STABLE_LEN) - 1) << SDH_CARD_STABLE_POS)
#define SDH_CARD_STABLE_UMSK                    (~(((1U << SDH_CARD_STABLE_LEN) - 1) << SDH_CARD_STABLE_POS))
#define SDH_CARD_DET                            SDH_CARD_DET
#define SDH_CARD_DET_POS                        (2U)
#define SDH_CARD_DET_LEN                        (1U)
#define SDH_CARD_DET_MSK                        (((1U << SDH_CARD_DET_LEN) - 1) << SDH_CARD_DET_POS)
#define SDH_CARD_DET_UMSK                       (~(((1U << SDH_CARD_DET_LEN) - 1) << SDH_CARD_DET_POS))
#define SDH_WRITE_PROT                          SDH_WRITE_PROT
#define SDH_WRITE_PROT_POS                      (3U)
#define SDH_WRITE_PROT_LEN                      (1U)
#define SDH_WRITE_PROT_MSK                      (((1U << SDH_WRITE_PROT_LEN) - 1) << SDH_WRITE_PROT_POS)
#define SDH_WRITE_PROT_UMSK                     (~(((1U << SDH_WRITE_PROT_LEN) - 1) << SDH_WRITE_PROT_POS))
#define SDH_DAT_LEVEL                           SDH_DAT_LEVEL
#define SDH_DAT_LEVEL_POS                       (4U)
#define SDH_DAT_LEVEL_LEN                       (4U)
#define SDH_DAT_LEVEL_MSK                       (((1U << SDH_DAT_LEVEL_LEN) - 1) << SDH_DAT_LEVEL_POS)
#define SDH_DAT_LEVEL_UMSK                      (~(((1U << SDH_DAT_LEVEL_LEN) - 1) << SDH_DAT_LEVEL_POS))
#define SDH_CMD_LEVEL                           SDH_CMD_LEVEL
#define SDH_CMD_LEVEL_POS                       (8U)
#define SDH_CMD_LEVEL_LEN                       (1U)
#define SDH_CMD_LEVEL_MSK                       (((1U << SDH_CMD_LEVEL_LEN) - 1) << SDH_CMD_LEVEL_POS)
#define SDH_CMD_LEVEL_UMSK                      (~(((1U << SDH_CMD_LEVEL_LEN) - 1) << SDH_CMD_LEVEL_POS))

/* 0x28 : Host Control Register */
#define SDH_LED_CTRL                            SDH_LED_CTRL
#define SDH_LED_CTRL_POS                        (0U)
#define SDH_LED_CTRL_LEN                        (1U)
#define SDH_LED_CTRL_MSK                        (((1U << SDH_LED_CTRL_LEN) - 1) << SDH_LED_CTRL_POS)
#define SDH_LED_CTRL_UMSK                       (~(((1U << SDH_LED_CTRL_LEN) - 1) << SDH_LED_CTRL_POS))
#define SDH_DATA_WIDTH                          SDH_DATA_WIDTH
#define SDH_DATA_WIDTH_POS                      (1U)
#define SDH_DATA_WIDTH_LEN                      (1U)
#define SDH_DATA_WIDTH_MSK                      (((1U << SDH_DATA_WIDTH_LEN) - 1) << SDH_DATA_WIDTH_POS)
#define SDH_DATA_WIDTH_UMSK                     (~(((1U << SDH_DATA_WIDTH_LEN) - 1) << SDH_DATA_WIDTH_POS))
#define SDH_HI_SPEED_EN                         SDH_HI_SPEED_EN
#define SDH_HI_SPEED_EN_POS                     (2U)
#define SDH_HI_SPEED_EN_LEN                     (1U)
#define SDH_HI_SPEED_EN_MSK                     (((1U << SDH_HI_SPEED_EN_LEN) - 1) << SDH_HI_SPEED_EN_POS)
#define SDH_HI_SPEED_EN_UMSK                    (~(((1U << SDH_HI_SPEED_EN_LEN) - 1) << SDH_HI_SPEED_EN_POS))
#define SDH_DMA_SEL                             SDH_DMA_SEL
#define SDH_DMA_SEL_POS                         (3U)
#define SDH_DMA_SEL_LEN                         (2U)
#define SDH_DMA_SEL_MSK                         (((1U << SDH_DMA_SEL_LEN) - 1) << SDH_DMA_SEL_POS)
#define SDH_DMA_SEL_UMSK                        (~(((1U << SDH_DMA_SEL_LEN) - 1) << SDH_DMA_SEL_POS))
#define SDH_EX_DATA_WIDTH                       SDH_EX_DATA_WIDTH
#define SDH_EX_DATA_WIDTH_POS                   (5U)
#define SDH_EX_DATA_WIDTH_LEN                   (1U)
#define SDH_EX_DATA_WIDTH_MSK                   (((1U << SDH_EX_DATA_WIDTH_LEN) - 1) << SDH_EX_DATA_WIDTH_POS)
#define SDH_EX_DATA_WIDTH_UMSK                  (~(((1U << SDH_EX_DATA_WIDTH_LEN) - 1) << SDH_EX_DATA_WIDTH_POS))
#define SDH_CARD_DET_L                          SDH_CARD_DET_L
#define SDH_CARD_DET_L_POS                      (6U)
#define SDH_CARD_DET_L_LEN                      (1U)
#define SDH_CARD_DET_L_MSK                      (((1U << SDH_CARD_DET_L_LEN) - 1) << SDH_CARD_DET_L_POS)
#define SDH_CARD_DET_L_UMSK                     (~(((1U << SDH_CARD_DET_L_LEN) - 1) << SDH_CARD_DET_L_POS))
#define SDH_CARD_DET_S                          SDH_CARD_DET_S
#define SDH_CARD_DET_S_POS                      (7U)
#define SDH_CARD_DET_S_LEN                      (1U)
#define SDH_CARD_DET_S_MSK                      (((1U << SDH_CARD_DET_S_LEN) - 1) << SDH_CARD_DET_S_POS)
#define SDH_CARD_DET_S_UMSK                     (~(((1U << SDH_CARD_DET_S_LEN) - 1) << SDH_CARD_DET_S_POS))
#define SDH_SD_BUS_POWER                        SDH_SD_BUS_POWER
#define SDH_SD_BUS_POWER_POS                    (8U)
#define SDH_SD_BUS_POWER_LEN                    (1U)
#define SDH_SD_BUS_POWER_MSK                    (((1U << SDH_SD_BUS_POWER_LEN) - 1) << SDH_SD_BUS_POWER_POS)
#define SDH_SD_BUS_POWER_UMSK                   (~(((1U << SDH_SD_BUS_POWER_LEN) - 1) << SDH_SD_BUS_POWER_POS))
#define SDH_SD_BUS_VLT                          SDH_SD_BUS_VLT
#define SDH_SD_BUS_VLT_POS                      (9U)
#define SDH_SD_BUS_VLT_LEN                      (3U)
#define SDH_SD_BUS_VLT_MSK                      (((1U << SDH_SD_BUS_VLT_LEN) - 1) << SDH_SD_BUS_VLT_POS)
#define SDH_SD_BUS_VLT_UMSK                     (~(((1U << SDH_SD_BUS_VLT_LEN) - 1) << SDH_SD_BUS_VLT_POS))

/* 0x2A : Block Gap Control Register */
#define SDH_STOP_AT_BLOCK_GAP_REQ               SDH_STOP_AT_BLOCK_GAP_REQ
#define SDH_STOP_AT_BLOCK_GAP_REQ_POS           (0U)
#define SDH_STOP_AT_BLOCK_GAP_REQ_LEN           (1U)
#define SDH_STOP_AT_BLOCK_GAP_REQ_MSK           (((1U << SDH_STOP_AT_BLOCK_GAP_REQ_LEN) - 1) << SDH_STOP_AT_BLOCK_GAP_REQ_POS)
#define SDH_STOP_AT_BLOCK_GAP_REQ_UMSK          (~(((1U << SDH_STOP_AT_BLOCK_GAP_REQ_LEN) - 1) << SDH_STOP_AT_BLOCK_GAP_REQ_POS))
#define SDH_CONT_REQ                            SDH_CONT_REQ
#define SDH_CONT_REQ_POS                        (1U)
#define SDH_CONT_REQ_LEN                        (1U)
#define SDH_CONT_REQ_MSK                        (((1U << SDH_CONT_REQ_LEN) - 1) << SDH_CONT_REQ_POS)
#define SDH_CONT_REQ_UMSK                       (~(((1U << SDH_CONT_REQ_LEN) - 1) << SDH_CONT_REQ_POS))
#define SDH_RD_WAIT_CTL                         SDH_RD_WAIT_CTL
#define SDH_RD_WAIT_CTL_POS                     (2U)
#define SDH_RD_WAIT_CTL_LEN                     (1U)
#define SDH_RD_WAIT_CTL_MSK                     (((1U << SDH_RD_WAIT_CTL_LEN) - 1) << SDH_RD_WAIT_CTL_POS)
#define SDH_RD_WAIT_CTL_UMSK                    (~(((1U << SDH_RD_WAIT_CTL_LEN) - 1) << SDH_RD_WAIT_CTL_POS))
#define SDH_INT_BLK_GAP                         SDH_INT_BLK_GAP
#define SDH_INT_BLK_GAP_POS                     (3U)
#define SDH_INT_BLK_GAP_LEN                     (1U)
#define SDH_INT_BLK_GAP_MSK                     (((1U << SDH_INT_BLK_GAP_LEN) - 1) << SDH_INT_BLK_GAP_POS)
#define SDH_INT_BLK_GAP_UMSK                    (~(((1U << SDH_INT_BLK_GAP_LEN) - 1) << SDH_INT_BLK_GAP_POS))
#define SDH_W_CARD_INT                          SDH_W_CARD_INT
#define SDH_W_CARD_INT_POS                      (8U)
#define SDH_W_CARD_INT_LEN                      (1U)
#define SDH_W_CARD_INT_MSK                      (((1U << SDH_W_CARD_INT_LEN) - 1) << SDH_W_CARD_INT_POS)
#define SDH_W_CARD_INT_UMSK                     (~(((1U << SDH_W_CARD_INT_LEN) - 1) << SDH_W_CARD_INT_POS))
#define SDH_W_INSERTION                         SDH_W_INSERTION
#define SDH_W_INSERTION_POS                     (9U)
#define SDH_W_INSERTION_LEN                     (1U)
#define SDH_W_INSERTION_MSK                     (((1U << SDH_W_INSERTION_LEN) - 1) << SDH_W_INSERTION_POS)
#define SDH_W_INSERTION_UMSK                    (~(((1U << SDH_W_INSERTION_LEN) - 1) << SDH_W_INSERTION_POS))
#define SDH_W_REMOVAL                           SDH_W_REMOVAL
#define SDH_W_REMOVAL_POS                       (10U)
#define SDH_W_REMOVAL_LEN                       (1U)
#define SDH_W_REMOVAL_MSK                       (((1U << SDH_W_REMOVAL_LEN) - 1) << SDH_W_REMOVAL_POS)
#define SDH_W_REMOVAL_UMSK                      (~(((1U << SDH_W_REMOVAL_LEN) - 1) << SDH_W_REMOVAL_POS))

/* 0x2C : Clock Control Register */
#define SDH_INT_CLK_EN                          SDH_INT_CLK_EN
#define SDH_INT_CLK_EN_POS                      (0U)
#define SDH_INT_CLK_EN_LEN                      (1U)
#define SDH_INT_CLK_EN_MSK                      (((1U << SDH_INT_CLK_EN_LEN) - 1) << SDH_INT_CLK_EN_POS)
#define SDH_INT_CLK_EN_UMSK                     (~(((1U << SDH_INT_CLK_EN_LEN) - 1) << SDH_INT_CLK_EN_POS))
#define SDH_INT_CLK_STABLE                      SDH_INT_CLK_STABLE
#define SDH_INT_CLK_STABLE_POS                  (1U)
#define SDH_INT_CLK_STABLE_LEN                  (1U)
#define SDH_INT_CLK_STABLE_MSK                  (((1U << SDH_INT_CLK_STABLE_LEN) - 1) << SDH_INT_CLK_STABLE_POS)
#define SDH_INT_CLK_STABLE_UMSK                 (~(((1U << SDH_INT_CLK_STABLE_LEN) - 1) << SDH_INT_CLK_STABLE_POS))
#define SDH_SD_CLK_EN                           SDH_SD_CLK_EN
#define SDH_SD_CLK_EN_POS                       (2U)
#define SDH_SD_CLK_EN_LEN                       (1U)
#define SDH_SD_CLK_EN_MSK                       (((1U << SDH_SD_CLK_EN_LEN) - 1) << SDH_SD_CLK_EN_POS)
#define SDH_SD_CLK_EN_UMSK                      (~(((1U << SDH_SD_CLK_EN_LEN) - 1) << SDH_SD_CLK_EN_POS))
#define SDH_CLK_GEN_SEL                         SDH_CLK_GEN_SEL
#define SDH_CLK_GEN_SEL_POS                     (5U)
#define SDH_CLK_GEN_SEL_LEN                     (1U)
#define SDH_CLK_GEN_SEL_MSK                     (((1U << SDH_CLK_GEN_SEL_LEN) - 1) << SDH_CLK_GEN_SEL_POS)
#define SDH_CLK_GEN_SEL_UMSK                    (~(((1U << SDH_CLK_GEN_SEL_LEN) - 1) << SDH_CLK_GEN_SEL_POS))
#define SDH_SD_FREQ_SEL_HI                      SDH_SD_FREQ_SEL_HI
#define SDH_SD_FREQ_SEL_HI_POS                  (6U)
#define SDH_SD_FREQ_SEL_HI_LEN                  (2U)
#define SDH_SD_FREQ_SEL_HI_MSK                  (((1U << SDH_SD_FREQ_SEL_HI_LEN) - 1) << SDH_SD_FREQ_SEL_HI_POS)
#define SDH_SD_FREQ_SEL_HI_UMSK                 (~(((1U << SDH_SD_FREQ_SEL_HI_LEN) - 1) << SDH_SD_FREQ_SEL_HI_POS))
#define SDH_SD_FREQ_SEL_LO                      SDH_SD_FREQ_SEL_LO
#define SDH_SD_FREQ_SEL_LO_POS                  (8U)
#define SDH_SD_FREQ_SEL_LO_LEN                  (8U)
#define SDH_SD_FREQ_SEL_LO_MSK                  (((1U << SDH_SD_FREQ_SEL_LO_LEN) - 1) << SDH_SD_FREQ_SEL_LO_POS)
#define SDH_SD_FREQ_SEL_LO_UMSK                 (~(((1U << SDH_SD_FREQ_SEL_LO_LEN) - 1) << SDH_SD_FREQ_SEL_LO_POS))

/* 0x2E : Timeout Control/Software Reset Register */
#define SDH_TIMEOUT_VALUE                       SDH_TIMEOUT_VALUE
#define SDH_TIMEOUT_VALUE_POS                   (0U)
#define SDH_TIMEOUT_VALUE_LEN                   (4U)
#define SDH_TIMEOUT_VALUE_MSK                   (((1U << SDH_TIMEOUT_VALUE_LEN) - 1) << SDH_TIMEOUT_VALUE_POS)
#define SDH_TIMEOUT_VALUE_UMSK                  (~(((1U << SDH_TIMEOUT_VALUE_LEN) - 1) << SDH_TIMEOUT_VALUE_POS))
#define SDH_SW_RST_ALL                          SDH_SW_RST_ALL
#define SDH_SW_RST_ALL_POS                      (8U)
#define SDH_SW_RST_ALL_LEN                      (1U)
#define SDH_SW_RST_ALL_MSK                      (((1U << SDH_SW_RST_ALL_LEN) - 1) << SDH_SW_RST_ALL_POS)
#define SDH_SW_RST_ALL_UMSK                     (~(((1U << SDH_SW_RST_ALL_LEN) - 1) << SDH_SW_RST_ALL_POS))
#define SDH_SW_RST_CMD                          SDH_SW_RST_CMD
#define SDH_SW_RST_CMD_POS                      (9U)
#define SDH_SW_RST_CMD_LEN                      (1U)
#define SDH_SW_RST_CMD_MSK                      (((1U << SDH_SW_RST_CMD_LEN) - 1) << SDH_SW_RST_CMD_POS)
#define SDH_SW_RST_CMD_UMSK                     (~(((1U << SDH_SW_RST_CMD_LEN) - 1) << SDH_SW_RST_CMD_POS))
#define SDH_SW_RST_DAT                          SDH_SW_RST_DAT
#define SDH_SW_RST_DAT_POS                      (10U)
#define SDH_SW_RST_DAT_LEN                      (1U)
#define SDH_SW_RST_DAT_MSK                      (((1U << SDH_SW_RST_DAT_LEN) - 1) << SDH_SW_RST_DAT_POS)
#define SDH_SW_RST_DAT_UMSK                     (~(((1U << SDH_SW_RST_DAT_LEN) - 1) << SDH_SW_RST_DAT_POS))

/* 0x30 : Normal Interrupt Status Register */
#define SDH_CMD_COMPLETE                        SDH_CMD_COMPLETE
#define SDH_CMD_COMPLETE_POS                    (0U)
#define SDH_CMD_COMPLETE_LEN                    (1U)
#define SDH_CMD_COMPLETE_MSK                    (((1U << SDH_CMD_COMPLETE_LEN) - 1) << SDH_CMD_COMPLETE_POS)
#define SDH_CMD_COMPLETE_UMSK                   (~(((1U << SDH_CMD_COMPLETE_LEN) - 1) << SDH_CMD_COMPLETE_POS))
#define SDH_XFER_COMPLETE                       SDH_XFER_COMPLETE
#define SDH_XFER_COMPLETE_POS                   (1U)
#define SDH_XFER_COMPLETE_LEN                   (1U)
#define SDH_XFER_COMPLETE_MSK                   (((1U << SDH_XFER_COMPLETE_LEN) - 1) << SDH_XFER_COMPLETE_POS)
#define SDH_XFER_COMPLETE_UMSK                  (~(((1U << SDH_XFER_COMPLETE_LEN) - 1) << SDH_XFER_COMPLETE_POS))
#define SDH_BLOCK_GAP_EVT                       SDH_BLOCK_GAP_EVT
#define SDH_BLOCK_GAP_EVT_POS                   (2U)
#define SDH_BLOCK_GAP_EVT_LEN                   (1U)
#define SDH_BLOCK_GAP_EVT_MSK                   (((1U << SDH_BLOCK_GAP_EVT_LEN) - 1) << SDH_BLOCK_GAP_EVT_POS)
#define SDH_BLOCK_GAP_EVT_UMSK                  (~(((1U << SDH_BLOCK_GAP_EVT_LEN) - 1) << SDH_BLOCK_GAP_EVT_POS))
#define SDH_DMA_INT                             SDH_DMA_INT
#define SDH_DMA_INT_POS                         (3U)
#define SDH_DMA_INT_LEN                         (1U)
#define SDH_DMA_INT_MSK                         (((1U << SDH_DMA_INT_LEN) - 1) << SDH_DMA_INT_POS)
#define SDH_DMA_INT_UMSK                        (~(((1U << SDH_DMA_INT_LEN) - 1) << SDH_DMA_INT_POS))
#define SDH_TX_RDY                              SDH_TX_RDY
#define SDH_TX_RDY_POS                          (4U)
#define SDH_TX_RDY_LEN                          (1U)
#define SDH_TX_RDY_MSK                          (((1U << SDH_TX_RDY_LEN) - 1) << SDH_TX_RDY_POS)
#define SDH_TX_RDY_UMSK                         (~(((1U << SDH_TX_RDY_LEN) - 1) << SDH_TX_RDY_POS))
#define SDH_RX_RDY                              SDH_RX_RDY
#define SDH_RX_RDY_POS                          (5U)
#define SDH_RX_RDY_LEN                          (1U)
#define SDH_RX_RDY_MSK                          (((1U << SDH_RX_RDY_LEN) - 1) << SDH_RX_RDY_POS)
#define SDH_RX_RDY_UMSK                         (~(((1U << SDH_RX_RDY_LEN) - 1) << SDH_RX_RDY_POS))
#define SDH_CARD_INS_INT                        SDH_CARD_INS_INT
#define SDH_CARD_INS_INT_POS                    (6U)
#define SDH_CARD_INS_INT_LEN                    (1U)
#define SDH_CARD_INS_INT_MSK                    (((1U << SDH_CARD_INS_INT_LEN) - 1) << SDH_CARD_INS_INT_POS)
#define SDH_CARD_INS_INT_UMSK                   (~(((1U << SDH_CARD_INS_INT_LEN) - 1) << SDH_CARD_INS_INT_POS))
#define SDH_CARD_REM_INT                        SDH_CARD_REM_INT
#define SDH_CARD_REM_INT_POS                    (7U)
#define SDH_CARD_REM_INT_LEN                    (1U)
#define SDH_CARD_REM_INT_MSK                    (((1U << SDH_CARD_REM_INT_LEN) - 1) << SDH_CARD_REM_INT_POS)
#define SDH_CARD_REM_INT_UMSK                   (~(((1U << SDH_CARD_REM_INT_LEN) - 1) << SDH_CARD_REM_INT_POS))
#define SDH_CARD_INT                            SDH_CARD_INT
#define SDH_CARD_INT_POS                        (8U)
#define SDH_CARD_INT_LEN                        (1U)
#define SDH_CARD_INT_MSK                        (((1U << SDH_CARD_INT_LEN) - 1) << SDH_CARD_INT_POS)
#define SDH_CARD_INT_UMSK                       (~(((1U << SDH_CARD_INT_LEN) - 1) << SDH_CARD_INT_POS))
#define SDH_INT_A                               SDH_INT_A
#define SDH_INT_A_POS                           (9U)
#define SDH_INT_A_LEN                           (1U)
#define SDH_INT_A_MSK                           (((1U << SDH_INT_A_LEN) - 1) << SDH_INT_A_POS)
#define SDH_INT_A_UMSK                          (~(((1U << SDH_INT_A_LEN) - 1) << SDH_INT_A_POS))
#define SDH_INT_B                               SDH_INT_B
#define SDH_INT_B_POS                           (10U)
#define SDH_INT_B_LEN                           (1U)
#define SDH_INT_B_MSK                           (((1U << SDH_INT_B_LEN) - 1) << SDH_INT_B_POS)
#define SDH_INT_B_UMSK                          (~(((1U << SDH_INT_B_LEN) - 1) << SDH_INT_B_POS))
#define SDH_INT_C                               SDH_INT_C
#define SDH_INT_C_POS                           (11U)
#define SDH_INT_C_LEN                           (1U)
#define SDH_INT_C_MSK                           (((1U << SDH_INT_C_LEN) - 1) << SDH_INT_C_POS)
#define SDH_INT_C_UMSK                          (~(((1U << SDH_INT_C_LEN) - 1) << SDH_INT_C_POS))
#define SDH_RETUNING_INT                        SDH_RETUNING_INT
#define SDH_RETUNING_INT_POS                    (12U)
#define SDH_RETUNING_INT_LEN                    (1U)
#define SDH_RETUNING_INT_MSK                    (((1U << SDH_RETUNING_INT_LEN) - 1) << SDH_RETUNING_INT_POS)
#define SDH_RETUNING_INT_UMSK                   (~(((1U << SDH_RETUNING_INT_LEN) - 1) << SDH_RETUNING_INT_POS))
#define SDH_ERR_INT                             SDH_ERR_INT
#define SDH_ERR_INT_POS                         (15U)
#define SDH_ERR_INT_LEN                         (1U)
#define SDH_ERR_INT_MSK                         (((1U << SDH_ERR_INT_LEN) - 1) << SDH_ERR_INT_POS)
#define SDH_ERR_INT_UMSK                        (~(((1U << SDH_ERR_INT_LEN) - 1) << SDH_ERR_INT_POS))

/* 0x32 : Error Interrupt Status Register */
#define SDH_CMD_TIMEOUT_ERR                     SDH_CMD_TIMEOUT_ERR
#define SDH_CMD_TIMEOUT_ERR_POS                 (0U)
#define SDH_CMD_TIMEOUT_ERR_LEN                 (1U)
#define SDH_CMD_TIMEOUT_ERR_MSK                 (((1U << SDH_CMD_TIMEOUT_ERR_LEN) - 1) << SDH_CMD_TIMEOUT_ERR_POS)
#define SDH_CMD_TIMEOUT_ERR_UMSK                (~(((1U << SDH_CMD_TIMEOUT_ERR_LEN) - 1) << SDH_CMD_TIMEOUT_ERR_POS))
#define SDH_CMD_CRC_ERR                         SDH_CMD_CRC_ERR
#define SDH_CMD_CRC_ERR_POS                     (1U)
#define SDH_CMD_CRC_ERR_LEN                     (1U)
#define SDH_CMD_CRC_ERR_MSK                     (((1U << SDH_CMD_CRC_ERR_LEN) - 1) << SDH_CMD_CRC_ERR_POS)
#define SDH_CMD_CRC_ERR_UMSK                    (~(((1U << SDH_CMD_CRC_ERR_LEN) - 1) << SDH_CMD_CRC_ERR_POS))
#define SDH_CMD_END_BIT_ERR                     SDH_CMD_END_BIT_ERR
#define SDH_CMD_END_BIT_ERR_POS                 (2U)
#define SDH_CMD_END_BIT_ERR_LEN                 (1U)
#define SDH_CMD_END_BIT_ERR_MSK                 (((1U << SDH_CMD_END_BIT_ERR_LEN) - 1) << SDH_CMD_END_BIT_ERR_POS)
#define SDH_CMD_END_BIT_ERR_UMSK                (~(((1U << SDH_CMD_END_BIT_ERR_LEN) - 1) << SDH_CMD_END_BIT_ERR_POS))
#define SDH_CMD_INDEX_ERR                       SDH_CMD_INDEX_ERR
#define SDH_CMD_INDEX_ERR_POS                   (3U)
#define SDH_CMD_INDEX_ERR_LEN                   (1U)
#define SDH_CMD_INDEX_ERR_MSK                   (((1U << SDH_CMD_INDEX_ERR_LEN) - 1) << SDH_CMD_INDEX_ERR_POS)
#define SDH_CMD_INDEX_ERR_UMSK                  (~(((1U << SDH_CMD_INDEX_ERR_LEN) - 1) << SDH_CMD_INDEX_ERR_POS))
#define SDH_DATA_TIMEOUT_ERR                    SDH_DATA_TIMEOUT_ERR
#define SDH_DATA_TIMEOUT_ERR_POS                (4U)
#define SDH_DATA_TIMEOUT_ERR_LEN                (1U)
#define SDH_DATA_TIMEOUT_ERR_MSK                (((1U << SDH_DATA_TIMEOUT_ERR_LEN) - 1) << SDH_DATA_TIMEOUT_ERR_POS)
#define SDH_DATA_TIMEOUT_ERR_UMSK               (~(((1U << SDH_DATA_TIMEOUT_ERR_LEN) - 1) << SDH_DATA_TIMEOUT_ERR_POS))
#define SDH_RD_DATA_CRC_ERR                     SDH_RD_DATA_CRC_ERR
#define SDH_RD_DATA_CRC_ERR_POS                 (5U)
#define SDH_RD_DATA_CRC_ERR_LEN                 (1U)
#define SDH_RD_DATA_CRC_ERR_MSK                 (((1U << SDH_RD_DATA_CRC_ERR_LEN) - 1) << SDH_RD_DATA_CRC_ERR_POS)
#define SDH_RD_DATA_CRC_ERR_UMSK                (~(((1U << SDH_RD_DATA_CRC_ERR_LEN) - 1) << SDH_RD_DATA_CRC_ERR_POS))
#define SDH_RD_DATA_END_BIT_ERR                 SDH_RD_DATA_END_BIT_ERR
#define SDH_RD_DATA_END_BIT_ERR_POS             (6U)
#define SDH_RD_DATA_END_BIT_ERR_LEN             (1U)
#define SDH_RD_DATA_END_BIT_ERR_MSK             (((1U << SDH_RD_DATA_END_BIT_ERR_LEN) - 1) << SDH_RD_DATA_END_BIT_ERR_POS)
#define SDH_RD_DATA_END_BIT_ERR_UMSK            (~(((1U << SDH_RD_DATA_END_BIT_ERR_LEN) - 1) << SDH_RD_DATA_END_BIT_ERR_POS))
#define SDH_CUR_LIMIT_ERR                       SDH_CUR_LIMIT_ERR
#define SDH_CUR_LIMIT_ERR_POS                   (7U)
#define SDH_CUR_LIMIT_ERR_LEN                   (1U)
#define SDH_CUR_LIMIT_ERR_MSK                   (((1U << SDH_CUR_LIMIT_ERR_LEN) - 1) << SDH_CUR_LIMIT_ERR_POS)
#define SDH_CUR_LIMIT_ERR_UMSK                  (~(((1U << SDH_CUR_LIMIT_ERR_LEN) - 1) << SDH_CUR_LIMIT_ERR_POS))
#define SDH_AUTO_CMD12_ERR                      SDH_AUTO_CMD12_ERR
#define SDH_AUTO_CMD12_ERR_POS                  (8U)
#define SDH_AUTO_CMD12_ERR_LEN                  (1U)
#define SDH_AUTO_CMD12_ERR_MSK                  (((1U << SDH_AUTO_CMD12_ERR_LEN) - 1) << SDH_AUTO_CMD12_ERR_POS)
#define SDH_AUTO_CMD12_ERR_UMSK                 (~(((1U << SDH_AUTO_CMD12_ERR_LEN) - 1) << SDH_AUTO_CMD12_ERR_POS))
#define SDH_ADMA_ERR                            SDH_ADMA_ERR
#define SDH_ADMA_ERR_POS                        (9U)
#define SDH_ADMA_ERR_LEN                        (1U)
#define SDH_ADMA_ERR_MSK                        (((1U << SDH_ADMA_ERR_LEN) - 1) << SDH_ADMA_ERR_POS)
#define SDH_ADMA_ERR_UMSK                       (~(((1U << SDH_ADMA_ERR_LEN) - 1) << SDH_ADMA_ERR_POS))
#define SDH_TUNE_ERR                            SDH_TUNE_ERR
#define SDH_TUNE_ERR_POS                        (10U)
#define SDH_TUNE_ERR_LEN                        (1U)
#define SDH_TUNE_ERR_MSK                        (((1U << SDH_TUNE_ERR_LEN) - 1) << SDH_TUNE_ERR_POS)
#define SDH_TUNE_ERR_UMSK                       (~(((1U << SDH_TUNE_ERR_LEN) - 1) << SDH_TUNE_ERR_POS))
#define SDH_SPI_ERR                             SDH_SPI_ERR
#define SDH_SPI_ERR_POS                         (12U)
#define SDH_SPI_ERR_LEN                         (1U)
#define SDH_SPI_ERR_MSK                         (((1U << SDH_SPI_ERR_LEN) - 1) << SDH_SPI_ERR_POS)
#define SDH_SPI_ERR_UMSK                        (~(((1U << SDH_SPI_ERR_LEN) - 1) << SDH_SPI_ERR_POS))
#define SDH_AXI_RESP_ERR                        SDH_AXI_RESP_ERR
#define SDH_AXI_RESP_ERR_POS                    (13U)
#define SDH_AXI_RESP_ERR_LEN                    (1U)
#define SDH_AXI_RESP_ERR_MSK                    (((1U << SDH_AXI_RESP_ERR_LEN) - 1) << SDH_AXI_RESP_ERR_POS)
#define SDH_AXI_RESP_ERR_UMSK                   (~(((1U << SDH_AXI_RESP_ERR_LEN) - 1) << SDH_AXI_RESP_ERR_POS))
#define SDH_CPL_TIMEOUT_ERR                     SDH_CPL_TIMEOUT_ERR
#define SDH_CPL_TIMEOUT_ERR_POS                 (14U)
#define SDH_CPL_TIMEOUT_ERR_LEN                 (1U)
#define SDH_CPL_TIMEOUT_ERR_MSK                 (((1U << SDH_CPL_TIMEOUT_ERR_LEN) - 1) << SDH_CPL_TIMEOUT_ERR_POS)
#define SDH_CPL_TIMEOUT_ERR_UMSK                (~(((1U << SDH_CPL_TIMEOUT_ERR_LEN) - 1) << SDH_CPL_TIMEOUT_ERR_POS))
#define SDH_CRC_STATUS_ERR                      SDH_CRC_STATUS_ERR
#define SDH_CRC_STATUS_ERR_POS                  (15U)
#define SDH_CRC_STATUS_ERR_LEN                  (1U)
#define SDH_CRC_STATUS_ERR_MSK                  (((1U << SDH_CRC_STATUS_ERR_LEN) - 1) << SDH_CRC_STATUS_ERR_POS)
#define SDH_CRC_STATUS_ERR_UMSK                 (~(((1U << SDH_CRC_STATUS_ERR_LEN) - 1) << SDH_CRC_STATUS_ERR_POS))

/* 0x34 : Normal Interrupt Status Enable Register */
#define SDH_CMD_COMPLETE_EN                     SDH_CMD_COMPLETE_EN
#define SDH_CMD_COMPLETE_EN_POS                 (0U)
#define SDH_CMD_COMPLETE_EN_LEN                 (1U)
#define SDH_CMD_COMPLETE_EN_MSK                 (((1U << SDH_CMD_COMPLETE_EN_LEN) - 1) << SDH_CMD_COMPLETE_EN_POS)
#define SDH_CMD_COMPLETE_EN_UMSK                (~(((1U << SDH_CMD_COMPLETE_EN_LEN) - 1) << SDH_CMD_COMPLETE_EN_POS))
#define SDH_XFER_COMPLETE_EN                    SDH_XFER_COMPLETE_EN
#define SDH_XFER_COMPLETE_EN_POS                (1U)
#define SDH_XFER_COMPLETE_EN_LEN                (1U)
#define SDH_XFER_COMPLETE_EN_MSK                (((1U << SDH_XFER_COMPLETE_EN_LEN) - 1) << SDH_XFER_COMPLETE_EN_POS)
#define SDH_XFER_COMPLETE_EN_UMSK               (~(((1U << SDH_XFER_COMPLETE_EN_LEN) - 1) << SDH_XFER_COMPLETE_EN_POS))
#define SDH_BLOCK_GAP_EVT_EN                    SDH_BLOCK_GAP_EVT_EN
#define SDH_BLOCK_GAP_EVT_EN_POS                (2U)
#define SDH_BLOCK_GAP_EVT_EN_LEN                (1U)
#define SDH_BLOCK_GAP_EVT_EN_MSK                (((1U << SDH_BLOCK_GAP_EVT_EN_LEN) - 1) << SDH_BLOCK_GAP_EVT_EN_POS)
#define SDH_BLOCK_GAP_EVT_EN_UMSK               (~(((1U << SDH_BLOCK_GAP_EVT_EN_LEN) - 1) << SDH_BLOCK_GAP_EVT_EN_POS))
#define SDH_DMA_INT_EN                          SDH_DMA_INT_EN
#define SDH_DMA_INT_EN_POS                      (3U)
#define SDH_DMA_INT_EN_LEN                      (1U)
#define SDH_DMA_INT_EN_MSK                      (((1U << SDH_DMA_INT_EN_LEN) - 1) << SDH_DMA_INT_EN_POS)
#define SDH_DMA_INT_EN_UMSK                     (~(((1U << SDH_DMA_INT_EN_LEN) - 1) << SDH_DMA_INT_EN_POS))
#define SDH_TX_RDY_EN                           SDH_TX_RDY_EN
#define SDH_TX_RDY_EN_POS                       (4U)
#define SDH_TX_RDY_EN_LEN                       (1U)
#define SDH_TX_RDY_EN_MSK                       (((1U << SDH_TX_RDY_EN_LEN) - 1) << SDH_TX_RDY_EN_POS)
#define SDH_TX_RDY_EN_UMSK                      (~(((1U << SDH_TX_RDY_EN_LEN) - 1) << SDH_TX_RDY_EN_POS))
#define SDH_RD_RDY_EN                           SDH_RD_RDY_EN
#define SDH_RD_RDY_EN_POS                       (5U)
#define SDH_RD_RDY_EN_LEN                       (1U)
#define SDH_RD_RDY_EN_MSK                       (((1U << SDH_RD_RDY_EN_LEN) - 1) << SDH_RD_RDY_EN_POS)
#define SDH_RD_RDY_EN_UMSK                      (~(((1U << SDH_RD_RDY_EN_LEN) - 1) << SDH_RD_RDY_EN_POS))
#define SDH_CARD_INS_EN                         SDH_CARD_INS_EN
#define SDH_CARD_INS_EN_POS                     (6U)
#define SDH_CARD_INS_EN_LEN                     (1U)
#define SDH_CARD_INS_EN_MSK                     (((1U << SDH_CARD_INS_EN_LEN) - 1) << SDH_CARD_INS_EN_POS)
#define SDH_CARD_INS_EN_UMSK                    (~(((1U << SDH_CARD_INS_EN_LEN) - 1) << SDH_CARD_INS_EN_POS))
#define SDH_CARD_REM_EN                         SDH_CARD_REM_EN
#define SDH_CARD_REM_EN_POS                     (7U)
#define SDH_CARD_REM_EN_LEN                     (1U)
#define SDH_CARD_REM_EN_MSK                     (((1U << SDH_CARD_REM_EN_LEN) - 1) << SDH_CARD_REM_EN_POS)
#define SDH_CARD_REM_EN_UMSK                    (~(((1U << SDH_CARD_REM_EN_LEN) - 1) << SDH_CARD_REM_EN_POS))
#define SDH_CARD_INT_EN                         SDH_CARD_INT_EN
#define SDH_CARD_INT_EN_POS                     (8U)
#define SDH_CARD_INT_EN_LEN                     (1U)
#define SDH_CARD_INT_EN_MSK                     (((1U << SDH_CARD_INT_EN_LEN) - 1) << SDH_CARD_INT_EN_POS)
#define SDH_CARD_INT_EN_UMSK                    (~(((1U << SDH_CARD_INT_EN_LEN) - 1) << SDH_CARD_INT_EN_POS))
#define SDH_INT_A_INT_EN                        SDH_INT_A_INT_EN
#define SDH_INT_A_INT_EN_POS                    (9U)
#define SDH_INT_A_INT_EN_LEN                    (1U)
#define SDH_INT_A_INT_EN_MSK                    (((1U << SDH_INT_A_INT_EN_LEN) - 1) << SDH_INT_A_INT_EN_POS)
#define SDH_INT_A_INT_EN_UMSK                   (~(((1U << SDH_INT_A_INT_EN_LEN) - 1) << SDH_INT_A_INT_EN_POS))
#define SDH_INT_B_INT_EN                        SDH_INT_B_INT_EN
#define SDH_INT_B_INT_EN_POS                    (10U)
#define SDH_INT_B_INT_EN_LEN                    (1U)
#define SDH_INT_B_INT_EN_MSK                    (((1U << SDH_INT_B_INT_EN_LEN) - 1) << SDH_INT_B_INT_EN_POS)
#define SDH_INT_B_INT_EN_UMSK                   (~(((1U << SDH_INT_B_INT_EN_LEN) - 1) << SDH_INT_B_INT_EN_POS))
#define SDH_INT_C_INT_EN                        SDH_INT_C_INT_EN
#define SDH_INT_C_INT_EN_POS                    (11U)
#define SDH_INT_C_INT_EN_LEN                    (1U)
#define SDH_INT_C_INT_EN_MSK                    (((1U << SDH_INT_C_INT_EN_LEN) - 1) << SDH_INT_C_INT_EN_POS)
#define SDH_INT_C_INT_EN_UMSK                   (~(((1U << SDH_INT_C_INT_EN_LEN) - 1) << SDH_INT_C_INT_EN_POS))
#define SDH_RETUNE_INT_EN                       SDH_RETUNE_INT_EN
#define SDH_RETUNE_INT_EN_POS                   (12U)
#define SDH_RETUNE_INT_EN_LEN                   (1U)
#define SDH_RETUNE_INT_EN_MSK                   (((1U << SDH_RETUNE_INT_EN_LEN) - 1) << SDH_RETUNE_INT_EN_POS)
#define SDH_RETUNE_INT_EN_UMSK                  (~(((1U << SDH_RETUNE_INT_EN_LEN) - 1) << SDH_RETUNE_INT_EN_POS))

/* 0x36 : Error Interrupt Status Enable Register */
#define SDH_CMD_TIMEOUT_ERR_EN                  SDH_CMD_TIMEOUT_ERR_EN
#define SDH_CMD_TIMEOUT_ERR_EN_POS              (0U)
#define SDH_CMD_TIMEOUT_ERR_EN_LEN              (1U)
#define SDH_CMD_TIMEOUT_ERR_EN_MSK              (((1U << SDH_CMD_TIMEOUT_ERR_EN_LEN) - 1) << SDH_CMD_TIMEOUT_ERR_EN_POS)
#define SDH_CMD_TIMEOUT_ERR_EN_UMSK             (~(((1U << SDH_CMD_TIMEOUT_ERR_EN_LEN) - 1) << SDH_CMD_TIMEOUT_ERR_EN_POS))
#define SDH_CMD_CRC_ERR_EN                      SDH_CMD_CRC_ERR_EN
#define SDH_CMD_CRC_ERR_EN_POS                  (1U)
#define SDH_CMD_CRC_ERR_EN_LEN                  (1U)
#define SDH_CMD_CRC_ERR_EN_MSK                  (((1U << SDH_CMD_CRC_ERR_EN_LEN) - 1) << SDH_CMD_CRC_ERR_EN_POS)
#define SDH_CMD_CRC_ERR_EN_UMSK                 (~(((1U << SDH_CMD_CRC_ERR_EN_LEN) - 1) << SDH_CMD_CRC_ERR_EN_POS))
#define SDH_CMD_END_BIT_ERR_EN                  SDH_CMD_END_BIT_ERR_EN
#define SDH_CMD_END_BIT_ERR_EN_POS              (2U)
#define SDH_CMD_END_BIT_ERR_EN_LEN              (1U)
#define SDH_CMD_END_BIT_ERR_EN_MSK              (((1U << SDH_CMD_END_BIT_ERR_EN_LEN) - 1) << SDH_CMD_END_BIT_ERR_EN_POS)
#define SDH_CMD_END_BIT_ERR_EN_UMSK             (~(((1U << SDH_CMD_END_BIT_ERR_EN_LEN) - 1) << SDH_CMD_END_BIT_ERR_EN_POS))
#define SDH_CMD_INDEX_ERR_EN                    SDH_CMD_INDEX_ERR_EN
#define SDH_CMD_INDEX_ERR_EN_POS                (3U)
#define SDH_CMD_INDEX_ERR_EN_LEN                (1U)
#define SDH_CMD_INDEX_ERR_EN_MSK                (((1U << SDH_CMD_INDEX_ERR_EN_LEN) - 1) << SDH_CMD_INDEX_ERR_EN_POS)
#define SDH_CMD_INDEX_ERR_EN_UMSK               (~(((1U << SDH_CMD_INDEX_ERR_EN_LEN) - 1) << SDH_CMD_INDEX_ERR_EN_POS))
#define SDH_DATA_TIMEOUT_ERR_EN                 SDH_DATA_TIMEOUT_ERR_EN
#define SDH_DATA_TIMEOUT_ERR_EN_POS             (4U)
#define SDH_DATA_TIMEOUT_ERR_EN_LEN             (1U)
#define SDH_DATA_TIMEOUT_ERR_EN_MSK             (((1U << SDH_DATA_TIMEOUT_ERR_EN_LEN) - 1) << SDH_DATA_TIMEOUT_ERR_EN_POS)
#define SDH_DATA_TIMEOUT_ERR_EN_UMSK            (~(((1U << SDH_DATA_TIMEOUT_ERR_EN_LEN) - 1) << SDH_DATA_TIMEOUT_ERR_EN_POS))
#define SDH_RD_DATA_CRC_ERR_EN                  SDH_RD_DATA_CRC_ERR_EN
#define SDH_RD_DATA_CRC_ERR_EN_POS              (5U)
#define SDH_RD_DATA_CRC_ERR_EN_LEN              (1U)
#define SDH_RD_DATA_CRC_ERR_EN_MSK              (((1U << SDH_RD_DATA_CRC_ERR_EN_LEN) - 1) << SDH_RD_DATA_CRC_ERR_EN_POS)
#define SDH_RD_DATA_CRC_ERR_EN_UMSK             (~(((1U << SDH_RD_DATA_CRC_ERR_EN_LEN) - 1) << SDH_RD_DATA_CRC_ERR_EN_POS))
#define SDH_RD_DATA_END_BIT_ERR_EN              SDH_RD_DATA_END_BIT_ERR_EN
#define SDH_RD_DATA_END_BIT_ERR_EN_POS          (6U)
#define SDH_RD_DATA_END_BIT_ERR_EN_LEN          (1U)
#define SDH_RD_DATA_END_BIT_ERR_EN_MSK          (((1U << SDH_RD_DATA_END_BIT_ERR_EN_LEN) - 1) << SDH_RD_DATA_END_BIT_ERR_EN_POS)
#define SDH_RD_DATA_END_BIT_ERR_EN_UMSK         (~(((1U << SDH_RD_DATA_END_BIT_ERR_EN_LEN) - 1) << SDH_RD_DATA_END_BIT_ERR_EN_POS))
#define SDH_CUR_LIM_ERR_EN                      SDH_CUR_LIM_ERR_EN
#define SDH_CUR_LIM_ERR_EN_POS                  (7U)
#define SDH_CUR_LIM_ERR_EN_LEN                  (1U)
#define SDH_CUR_LIM_ERR_EN_MSK                  (((1U << SDH_CUR_LIM_ERR_EN_LEN) - 1) << SDH_CUR_LIM_ERR_EN_POS)
#define SDH_CUR_LIM_ERR_EN_UMSK                 (~(((1U << SDH_CUR_LIM_ERR_EN_LEN) - 1) << SDH_CUR_LIM_ERR_EN_POS))
#define SDH_AUTO_CMD12_ERR_EN                   SDH_AUTO_CMD12_ERR_EN
#define SDH_AUTO_CMD12_ERR_EN_POS               (8U)
#define SDH_AUTO_CMD12_ERR_EN_LEN               (1U)
#define SDH_AUTO_CMD12_ERR_EN_MSK               (((1U << SDH_AUTO_CMD12_ERR_EN_LEN) - 1) << SDH_AUTO_CMD12_ERR_EN_POS)
#define SDH_AUTO_CMD12_ERR_EN_UMSK              (~(((1U << SDH_AUTO_CMD12_ERR_EN_LEN) - 1) << SDH_AUTO_CMD12_ERR_EN_POS))
#define SDH_ADMA_ERR_EN                         SDH_ADMA_ERR_EN
#define SDH_ADMA_ERR_EN_POS                     (9U)
#define SDH_ADMA_ERR_EN_LEN                     (1U)
#define SDH_ADMA_ERR_EN_MSK                     (((1U << SDH_ADMA_ERR_EN_LEN) - 1) << SDH_ADMA_ERR_EN_POS)
#define SDH_ADMA_ERR_EN_UMSK                    (~(((1U << SDH_ADMA_ERR_EN_LEN) - 1) << SDH_ADMA_ERR_EN_POS))
#define SDH_TUNING_ERR_EN                       SDH_TUNING_ERR_EN
#define SDH_TUNING_ERR_EN_POS                   (10U)
#define SDH_TUNING_ERR_EN_LEN                   (1U)
#define SDH_TUNING_ERR_EN_MSK                   (((1U << SDH_TUNING_ERR_EN_LEN) - 1) << SDH_TUNING_ERR_EN_POS)
#define SDH_TUNING_ERR_EN_UMSK                  (~(((1U << SDH_TUNING_ERR_EN_LEN) - 1) << SDH_TUNING_ERR_EN_POS))
#define SDH_SPI_ERR_EN                          SDH_SPI_ERR_EN
#define SDH_SPI_ERR_EN_POS                      (12U)
#define SDH_SPI_ERR_EN_LEN                      (1U)
#define SDH_SPI_ERR_EN_MSK                      (((1U << SDH_SPI_ERR_EN_LEN) - 1) << SDH_SPI_ERR_EN_POS)
#define SDH_SPI_ERR_EN_UMSK                     (~(((1U << SDH_SPI_ERR_EN_LEN) - 1) << SDH_SPI_ERR_EN_POS))
#define SDH_AXI_RESP_ERR_EN                     SDH_AXI_RESP_ERR_EN
#define SDH_AXI_RESP_ERR_EN_POS                 (13U)
#define SDH_AXI_RESP_ERR_EN_LEN                 (1U)
#define SDH_AXI_RESP_ERR_EN_MSK                 (((1U << SDH_AXI_RESP_ERR_EN_LEN) - 1) << SDH_AXI_RESP_ERR_EN_POS)
#define SDH_AXI_RESP_ERR_EN_UMSK                (~(((1U << SDH_AXI_RESP_ERR_EN_LEN) - 1) << SDH_AXI_RESP_ERR_EN_POS))
#define SDH_CPL_TIMEOUT_ERR_EN                  SDH_CPL_TIMEOUT_ERR_EN
#define SDH_CPL_TIMEOUT_ERR_EN_POS              (14U)
#define SDH_CPL_TIMEOUT_ERR_EN_LEN              (1U)
#define SDH_CPL_TIMEOUT_ERR_EN_MSK              (((1U << SDH_CPL_TIMEOUT_ERR_EN_LEN) - 1) << SDH_CPL_TIMEOUT_ERR_EN_POS)
#define SDH_CPL_TIMEOUT_ERR_EN_UMSK             (~(((1U << SDH_CPL_TIMEOUT_ERR_EN_LEN) - 1) << SDH_CPL_TIMEOUT_ERR_EN_POS))
#define SDH_CRC_STATUS_ERR_EN                   SDH_CRC_STATUS_ERR_EN
#define SDH_CRC_STATUS_ERR_EN_POS               (15U)
#define SDH_CRC_STATUS_ERR_EN_LEN               (1U)
#define SDH_CRC_STATUS_ERR_EN_MSK               (((1U << SDH_CRC_STATUS_ERR_EN_LEN) - 1) << SDH_CRC_STATUS_ERR_EN_POS)
#define SDH_CRC_STATUS_ERR_EN_UMSK              (~(((1U << SDH_CRC_STATUS_ERR_EN_LEN) - 1) << SDH_CRC_STATUS_ERR_EN_POS))

/* 0x38 : Normal Interrupt Status Interrupt Enable Register */
#define SDH_CMD_COMPLETE_INT_EN                 SDH_CMD_COMPLETE_INT_EN
#define SDH_CMD_COMPLETE_INT_EN_POS             (0U)
#define SDH_CMD_COMPLETE_INT_EN_LEN             (1U)
#define SDH_CMD_COMPLETE_INT_EN_MSK             (((1U << SDH_CMD_COMPLETE_INT_EN_LEN) - 1) << SDH_CMD_COMPLETE_INT_EN_POS)
#define SDH_CMD_COMPLETE_INT_EN_UMSK            (~(((1U << SDH_CMD_COMPLETE_INT_EN_LEN) - 1) << SDH_CMD_COMPLETE_INT_EN_POS))
#define SDH_XFER_COMPLETE_INT_EN                SDH_XFER_COMPLETE_INT_EN
#define SDH_XFER_COMPLETE_INT_EN_POS            (1U)
#define SDH_XFER_COMPLETE_INT_EN_LEN            (1U)
#define SDH_XFER_COMPLETE_INT_EN_MSK            (((1U << SDH_XFER_COMPLETE_INT_EN_LEN) - 1) << SDH_XFER_COMPLETE_INT_EN_POS)
#define SDH_XFER_COMPLETE_INT_EN_UMSK           (~(((1U << SDH_XFER_COMPLETE_INT_EN_LEN) - 1) << SDH_XFER_COMPLETE_INT_EN_POS))
#define SDH_BLOCK_GAP_EVT_INT_EN                SDH_BLOCK_GAP_EVT_INT_EN
#define SDH_BLOCK_GAP_EVT_INT_EN_POS            (2U)
#define SDH_BLOCK_GAP_EVT_INT_EN_LEN            (1U)
#define SDH_BLOCK_GAP_EVT_INT_EN_MSK            (((1U << SDH_BLOCK_GAP_EVT_INT_EN_LEN) - 1) << SDH_BLOCK_GAP_EVT_INT_EN_POS)
#define SDH_BLOCK_GAP_EVT_INT_EN_UMSK           (~(((1U << SDH_BLOCK_GAP_EVT_INT_EN_LEN) - 1) << SDH_BLOCK_GAP_EVT_INT_EN_POS))
#define SDH_DMA_INT_INT_EN                      SDH_DMA_INT_INT_EN
#define SDH_DMA_INT_INT_EN_POS                  (3U)
#define SDH_DMA_INT_INT_EN_LEN                  (1U)
#define SDH_DMA_INT_INT_EN_MSK                  (((1U << SDH_DMA_INT_INT_EN_LEN) - 1) << SDH_DMA_INT_INT_EN_POS)
#define SDH_DMA_INT_INT_EN_UMSK                 (~(((1U << SDH_DMA_INT_INT_EN_LEN) - 1) << SDH_DMA_INT_INT_EN_POS))
#define SDH_TX_RDY_INT_EN                       SDH_TX_RDY_INT_EN
#define SDH_TX_RDY_INT_EN_POS                   (4U)
#define SDH_TX_RDY_INT_EN_LEN                   (1U)
#define SDH_TX_RDY_INT_EN_MSK                   (((1U << SDH_TX_RDY_INT_EN_LEN) - 1) << SDH_TX_RDY_INT_EN_POS)
#define SDH_TX_RDY_INT_EN_UMSK                  (~(((1U << SDH_TX_RDY_INT_EN_LEN) - 1) << SDH_TX_RDY_INT_EN_POS))
#define SDH_RX_RDY_INT_EN                       SDH_RX_RDY_INT_EN
#define SDH_RX_RDY_INT_EN_POS                   (5U)
#define SDH_RX_RDY_INT_EN_LEN                   (1U)
#define SDH_RX_RDY_INT_EN_MSK                   (((1U << SDH_RX_RDY_INT_EN_LEN) - 1) << SDH_RX_RDY_INT_EN_POS)
#define SDH_RX_RDY_INT_EN_UMSK                  (~(((1U << SDH_RX_RDY_INT_EN_LEN) - 1) << SDH_RX_RDY_INT_EN_POS))
#define SDH_CARD_INS_INT_EN                     SDH_CARD_INS_INT_EN
#define SDH_CARD_INS_INT_EN_POS                 (6U)
#define SDH_CARD_INS_INT_EN_LEN                 (1U)
#define SDH_CARD_INS_INT_EN_MSK                 (((1U << SDH_CARD_INS_INT_EN_LEN) - 1) << SDH_CARD_INS_INT_EN_POS)
#define SDH_CARD_INS_INT_EN_UMSK                (~(((1U << SDH_CARD_INS_INT_EN_LEN) - 1) << SDH_CARD_INS_INT_EN_POS))
#define SDH_CARD_REM_INT_EN                     SDH_CARD_REM_INT_EN
#define SDH_CARD_REM_INT_EN_POS                 (7U)
#define SDH_CARD_REM_INT_EN_LEN                 (1U)
#define SDH_CARD_REM_INT_EN_MSK                 (((1U << SDH_CARD_REM_INT_EN_LEN) - 1) << SDH_CARD_REM_INT_EN_POS)
#define SDH_CARD_REM_INT_EN_UMSK                (~(((1U << SDH_CARD_REM_INT_EN_LEN) - 1) << SDH_CARD_REM_INT_EN_POS))
#define SDH_CARD_INT_INT_EN                     SDH_CARD_INT_INT_EN
#define SDH_CARD_INT_INT_EN_POS                 (8U)
#define SDH_CARD_INT_INT_EN_LEN                 (1U)
#define SDH_CARD_INT_INT_EN_MSK                 (((1U << SDH_CARD_INT_INT_EN_LEN) - 1) << SDH_CARD_INT_INT_EN_POS)
#define SDH_CARD_INT_INT_EN_UMSK                (~(((1U << SDH_CARD_INT_INT_EN_LEN) - 1) << SDH_CARD_INT_INT_EN_POS))
#define SDH_INT_A_INT_INT_EN                    SDH_INT_A_INT_INT_EN
#define SDH_INT_A_INT_INT_EN_POS                (9U)
#define SDH_INT_A_INT_INT_EN_LEN                (1U)
#define SDH_INT_A_INT_INT_EN_MSK                (((1U << SDH_INT_A_INT_INT_EN_LEN) - 1) << SDH_INT_A_INT_INT_EN_POS)
#define SDH_INT_A_INT_INT_EN_UMSK               (~(((1U << SDH_INT_A_INT_INT_EN_LEN) - 1) << SDH_INT_A_INT_INT_EN_POS))
#define SDH_INT_B_INT_INT_EN                    SDH_INT_B_INT_INT_EN
#define SDH_INT_B_INT_INT_EN_POS                (10U)
#define SDH_INT_B_INT_INT_EN_LEN                (1U)
#define SDH_INT_B_INT_INT_EN_MSK                (((1U << SDH_INT_B_INT_INT_EN_LEN) - 1) << SDH_INT_B_INT_INT_EN_POS)
#define SDH_INT_B_INT_INT_EN_UMSK               (~(((1U << SDH_INT_B_INT_INT_EN_LEN) - 1) << SDH_INT_B_INT_INT_EN_POS))
#define SDH_INT_C_INT_INT_EN                    SDH_INT_C_INT_INT_EN
#define SDH_INT_C_INT_INT_EN_POS                (11U)
#define SDH_INT_C_INT_INT_EN_LEN                (1U)
#define SDH_INT_C_INT_INT_EN_MSK                (((1U << SDH_INT_C_INT_INT_EN_LEN) - 1) << SDH_INT_C_INT_INT_EN_POS)
#define SDH_INT_C_INT_INT_EN_UMSK               (~(((1U << SDH_INT_C_INT_INT_EN_LEN) - 1) << SDH_INT_C_INT_INT_EN_POS))
#define SDH_RETUNE_INT_INT_EN                   SDH_RETUNE_INT_INT_EN
#define SDH_RETUNE_INT_INT_EN_POS               (12U)
#define SDH_RETUNE_INT_INT_EN_LEN               (1U)
#define SDH_RETUNE_INT_INT_EN_MSK               (((1U << SDH_RETUNE_INT_INT_EN_LEN) - 1) << SDH_RETUNE_INT_INT_EN_POS)
#define SDH_RETUNE_INT_INT_EN_UMSK              (~(((1U << SDH_RETUNE_INT_INT_EN_LEN) - 1) << SDH_RETUNE_INT_INT_EN_POS))

/* 0x3A : Error Interrupt Status Interrupt Enable Register */
#define SDH_CMD_TIMEOUT_ERR_INT_EN              SDH_CMD_TIMEOUT_ERR_INT_EN
#define SDH_CMD_TIMEOUT_ERR_INT_EN_POS          (0U)
#define SDH_CMD_TIMEOUT_ERR_INT_EN_LEN          (1U)
#define SDH_CMD_TIMEOUT_ERR_INT_EN_MSK          (((1U << SDH_CMD_TIMEOUT_ERR_INT_EN_LEN) - 1) << SDH_CMD_TIMEOUT_ERR_INT_EN_POS)
#define SDH_CMD_TIMEOUT_ERR_INT_EN_UMSK         (~(((1U << SDH_CMD_TIMEOUT_ERR_INT_EN_LEN) - 1) << SDH_CMD_TIMEOUT_ERR_INT_EN_POS))
#define SDH_CMD_CRC_ERR_INT_EN                  SDH_CMD_CRC_ERR_INT_EN
#define SDH_CMD_CRC_ERR_INT_EN_POS              (1U)
#define SDH_CMD_CRC_ERR_INT_EN_LEN              (1U)
#define SDH_CMD_CRC_ERR_INT_EN_MSK              (((1U << SDH_CMD_CRC_ERR_INT_EN_LEN) - 1) << SDH_CMD_CRC_ERR_INT_EN_POS)
#define SDH_CMD_CRC_ERR_INT_EN_UMSK             (~(((1U << SDH_CMD_CRC_ERR_INT_EN_LEN) - 1) << SDH_CMD_CRC_ERR_INT_EN_POS))
#define SDH_CMD_END_BIT_ERR_INT_EN              SDH_CMD_END_BIT_ERR_INT_EN
#define SDH_CMD_END_BIT_ERR_INT_EN_POS          (2U)
#define SDH_CMD_END_BIT_ERR_INT_EN_LEN          (1U)
#define SDH_CMD_END_BIT_ERR_INT_EN_MSK          (((1U << SDH_CMD_END_BIT_ERR_INT_EN_LEN) - 1) << SDH_CMD_END_BIT_ERR_INT_EN_POS)
#define SDH_CMD_END_BIT_ERR_INT_EN_UMSK         (~(((1U << SDH_CMD_END_BIT_ERR_INT_EN_LEN) - 1) << SDH_CMD_END_BIT_ERR_INT_EN_POS))
#define SDH_CMD_INDEX_ERR_INT_EN                SDH_CMD_INDEX_ERR_INT_EN
#define SDH_CMD_INDEX_ERR_INT_EN_POS            (3U)
#define SDH_CMD_INDEX_ERR_INT_EN_LEN            (1U)
#define SDH_CMD_INDEX_ERR_INT_EN_MSK            (((1U << SDH_CMD_INDEX_ERR_INT_EN_LEN) - 1) << SDH_CMD_INDEX_ERR_INT_EN_POS)
#define SDH_CMD_INDEX_ERR_INT_EN_UMSK           (~(((1U << SDH_CMD_INDEX_ERR_INT_EN_LEN) - 1) << SDH_CMD_INDEX_ERR_INT_EN_POS))
#define SDH_DATA_TIMEOUT_ERR_INT_EN             SDH_DATA_TIMEOUT_ERR_INT_EN
#define SDH_DATA_TIMEOUT_ERR_INT_EN_POS         (4U)
#define SDH_DATA_TIMEOUT_ERR_INT_EN_LEN         (1U)
#define SDH_DATA_TIMEOUT_ERR_INT_EN_MSK         (((1U << SDH_DATA_TIMEOUT_ERR_INT_EN_LEN) - 1) << SDH_DATA_TIMEOUT_ERR_INT_EN_POS)
#define SDH_DATA_TIMEOUT_ERR_INT_EN_UMSK        (~(((1U << SDH_DATA_TIMEOUT_ERR_INT_EN_LEN) - 1) << SDH_DATA_TIMEOUT_ERR_INT_EN_POS))
#define SDH_RD_DATA_CRC_ERR_INT_EN              SDH_RD_DATA_CRC_ERR_INT_EN
#define SDH_RD_DATA_CRC_ERR_INT_EN_POS          (5U)
#define SDH_RD_DATA_CRC_ERR_INT_EN_LEN          (1U)
#define SDH_RD_DATA_CRC_ERR_INT_EN_MSK          (((1U << SDH_RD_DATA_CRC_ERR_INT_EN_LEN) - 1) << SDH_RD_DATA_CRC_ERR_INT_EN_POS)
#define SDH_RD_DATA_CRC_ERR_INT_EN_UMSK         (~(((1U << SDH_RD_DATA_CRC_ERR_INT_EN_LEN) - 1) << SDH_RD_DATA_CRC_ERR_INT_EN_POS))
#define SDH_RD_DATA_END_BIT_ERR_INT_EN          SDH_RD_DATA_END_BIT_ERR_INT_EN
#define SDH_RD_DATA_END_BIT_ERR_INT_EN_POS      (6U)
#define SDH_RD_DATA_END_BIT_ERR_INT_EN_LEN      (1U)
#define SDH_RD_DATA_END_BIT_ERR_INT_EN_MSK      (((1U << SDH_RD_DATA_END_BIT_ERR_INT_EN_LEN) - 1) << SDH_RD_DATA_END_BIT_ERR_INT_EN_POS)
#define SDH_RD_DATA_END_BIT_ERR_INT_EN_UMSK     (~(((1U << SDH_RD_DATA_END_BIT_ERR_INT_EN_LEN) - 1) << SDH_RD_DATA_END_BIT_ERR_INT_EN_POS))
#define SDH_CUR_LIM_ERR_INT_EN                  SDH_CUR_LIM_ERR_INT_EN
#define SDH_CUR_LIM_ERR_INT_EN_POS              (7U)
#define SDH_CUR_LIM_ERR_INT_EN_LEN              (1U)
#define SDH_CUR_LIM_ERR_INT_EN_MSK              (((1U << SDH_CUR_LIM_ERR_INT_EN_LEN) - 1) << SDH_CUR_LIM_ERR_INT_EN_POS)
#define SDH_CUR_LIM_ERR_INT_EN_UMSK             (~(((1U << SDH_CUR_LIM_ERR_INT_EN_LEN) - 1) << SDH_CUR_LIM_ERR_INT_EN_POS))
#define SDH_AUTO_CMD12_ERR_INT_EN               SDH_AUTO_CMD12_ERR_INT_EN
#define SDH_AUTO_CMD12_ERR_INT_EN_POS           (8U)
#define SDH_AUTO_CMD12_ERR_INT_EN_LEN           (1U)
#define SDH_AUTO_CMD12_ERR_INT_EN_MSK           (((1U << SDH_AUTO_CMD12_ERR_INT_EN_LEN) - 1) << SDH_AUTO_CMD12_ERR_INT_EN_POS)
#define SDH_AUTO_CMD12_ERR_INT_EN_UMSK          (~(((1U << SDH_AUTO_CMD12_ERR_INT_EN_LEN) - 1) << SDH_AUTO_CMD12_ERR_INT_EN_POS))
#define SDH_ADMA_ERR_INT_EN                     SDH_ADMA_ERR_INT_EN
#define SDH_ADMA_ERR_INT_EN_POS                 (9U)
#define SDH_ADMA_ERR_INT_EN_LEN                 (1U)
#define SDH_ADMA_ERR_INT_EN_MSK                 (((1U << SDH_ADMA_ERR_INT_EN_LEN) - 1) << SDH_ADMA_ERR_INT_EN_POS)
#define SDH_ADMA_ERR_INT_EN_UMSK                (~(((1U << SDH_ADMA_ERR_INT_EN_LEN) - 1) << SDH_ADMA_ERR_INT_EN_POS))
#define SDH_TUNE_ERR_INT_EN                     SDH_TUNE_ERR_INT_EN
#define SDH_TUNE_ERR_INT_EN_POS                 (10U)
#define SDH_TUNE_ERR_INT_EN_LEN                 (1U)
#define SDH_TUNE_ERR_INT_EN_MSK                 (((1U << SDH_TUNE_ERR_INT_EN_LEN) - 1) << SDH_TUNE_ERR_INT_EN_POS)
#define SDH_TUNE_ERR_INT_EN_UMSK                (~(((1U << SDH_TUNE_ERR_INT_EN_LEN) - 1) << SDH_TUNE_ERR_INT_EN_POS))
#define SDH_SPI_ERR_INT_EN                      SDH_SPI_ERR_INT_EN
#define SDH_SPI_ERR_INT_EN_POS                  (12U)
#define SDH_SPI_ERR_INT_EN_LEN                  (1U)
#define SDH_SPI_ERR_INT_EN_MSK                  (((1U << SDH_SPI_ERR_INT_EN_LEN) - 1) << SDH_SPI_ERR_INT_EN_POS)
#define SDH_SPI_ERR_INT_EN_UMSK                 (~(((1U << SDH_SPI_ERR_INT_EN_LEN) - 1) << SDH_SPI_ERR_INT_EN_POS))
#define SDH_AXI_RESP_ERR_INT_EN                 SDH_AXI_RESP_ERR_INT_EN
#define SDH_AXI_RESP_ERR_INT_EN_POS             (13U)
#define SDH_AXI_RESP_ERR_INT_EN_LEN             (1U)
#define SDH_AXI_RESP_ERR_INT_EN_MSK             (((1U << SDH_AXI_RESP_ERR_INT_EN_LEN) - 1) << SDH_AXI_RESP_ERR_INT_EN_POS)
#define SDH_AXI_RESP_ERR_INT_EN_UMSK            (~(((1U << SDH_AXI_RESP_ERR_INT_EN_LEN) - 1) << SDH_AXI_RESP_ERR_INT_EN_POS))
#define SDH_CPL_TIMEOUT_ERR_INT_EN              SDH_CPL_TIMEOUT_ERR_INT_EN
#define SDH_CPL_TIMEOUT_ERR_INT_EN_POS          (14U)
#define SDH_CPL_TIMEOUT_ERR_INT_EN_LEN          (1U)
#define SDH_CPL_TIMEOUT_ERR_INT_EN_MSK          (((1U << SDH_CPL_TIMEOUT_ERR_INT_EN_LEN) - 1) << SDH_CPL_TIMEOUT_ERR_INT_EN_POS)
#define SDH_CPL_TIMEOUT_ERR_INT_EN_UMSK         (~(((1U << SDH_CPL_TIMEOUT_ERR_INT_EN_LEN) - 1) << SDH_CPL_TIMEOUT_ERR_INT_EN_POS))
#define SDH_CRC_STATUS_ERR_INT_EN               SDH_CRC_STATUS_ERR_INT_EN
#define SDH_CRC_STATUS_ERR_INT_EN_POS           (15U)
#define SDH_CRC_STATUS_ERR_INT_EN_LEN           (1U)
#define SDH_CRC_STATUS_ERR_INT_EN_MSK           (((1U << SDH_CRC_STATUS_ERR_INT_EN_LEN) - 1) << SDH_CRC_STATUS_ERR_INT_EN_POS)
#define SDH_CRC_STATUS_ERR_INT_EN_UMSK          (~(((1U << SDH_CRC_STATUS_ERR_INT_EN_LEN) - 1) << SDH_CRC_STATUS_ERR_INT_EN_POS))

/* 0x3C : Auto CMD12 Error Status Register */
#define SDH_AUTO_CMD12_NOT_EXE                  SDH_AUTO_CMD12_NOT_EXE
#define SDH_AUTO_CMD12_NOT_EXE_POS              (0U)
#define SDH_AUTO_CMD12_NOT_EXE_LEN              (1U)
#define SDH_AUTO_CMD12_NOT_EXE_MSK              (((1U << SDH_AUTO_CMD12_NOT_EXE_LEN) - 1) << SDH_AUTO_CMD12_NOT_EXE_POS)
#define SDH_AUTO_CMD12_NOT_EXE_UMSK             (~(((1U << SDH_AUTO_CMD12_NOT_EXE_LEN) - 1) << SDH_AUTO_CMD12_NOT_EXE_POS))
#define SDH_AUTO_CMD_TIMEOUT_ERR                SDH_AUTO_CMD_TIMEOUT_ERR
#define SDH_AUTO_CMD_TIMEOUT_ERR_POS            (1U)
#define SDH_AUTO_CMD_TIMEOUT_ERR_LEN            (1U)
#define SDH_AUTO_CMD_TIMEOUT_ERR_MSK            (((1U << SDH_AUTO_CMD_TIMEOUT_ERR_LEN) - 1) << SDH_AUTO_CMD_TIMEOUT_ERR_POS)
#define SDH_AUTO_CMD_TIMEOUT_ERR_UMSK           (~(((1U << SDH_AUTO_CMD_TIMEOUT_ERR_LEN) - 1) << SDH_AUTO_CMD_TIMEOUT_ERR_POS))
#define SDH_AUTO_CMD_CRC_ERR                    SDH_AUTO_CMD_CRC_ERR
#define SDH_AUTO_CMD_CRC_ERR_POS                (2U)
#define SDH_AUTO_CMD_CRC_ERR_LEN                (1U)
#define SDH_AUTO_CMD_CRC_ERR_MSK                (((1U << SDH_AUTO_CMD_CRC_ERR_LEN) - 1) << SDH_AUTO_CMD_CRC_ERR_POS)
#define SDH_AUTO_CMD_CRC_ERR_UMSK               (~(((1U << SDH_AUTO_CMD_CRC_ERR_LEN) - 1) << SDH_AUTO_CMD_CRC_ERR_POS))
#define SDH_AUTO_CMD_END_BIT_ERR                SDH_AUTO_CMD_END_BIT_ERR
#define SDH_AUTO_CMD_END_BIT_ERR_POS            (3U)
#define SDH_AUTO_CMD_END_BIT_ERR_LEN            (1U)
#define SDH_AUTO_CMD_END_BIT_ERR_MSK            (((1U << SDH_AUTO_CMD_END_BIT_ERR_LEN) - 1) << SDH_AUTO_CMD_END_BIT_ERR_POS)
#define SDH_AUTO_CMD_END_BIT_ERR_UMSK           (~(((1U << SDH_AUTO_CMD_END_BIT_ERR_LEN) - 1) << SDH_AUTO_CMD_END_BIT_ERR_POS))
#define SDH_AUTO_CMD_INDEX_ERR                  SDH_AUTO_CMD_INDEX_ERR
#define SDH_AUTO_CMD_INDEX_ERR_POS              (4U)
#define SDH_AUTO_CMD_INDEX_ERR_LEN              (1U)
#define SDH_AUTO_CMD_INDEX_ERR_MSK              (((1U << SDH_AUTO_CMD_INDEX_ERR_LEN) - 1) << SDH_AUTO_CMD_INDEX_ERR_POS)
#define SDH_AUTO_CMD_INDEX_ERR_UMSK             (~(((1U << SDH_AUTO_CMD_INDEX_ERR_LEN) - 1) << SDH_AUTO_CMD_INDEX_ERR_POS))
#define SDH_CMD_NOT_ISSUED                      SDH_CMD_NOT_ISSUED
#define SDH_CMD_NOT_ISSUED_POS                  (7U)
#define SDH_CMD_NOT_ISSUED_LEN                  (1U)
#define SDH_CMD_NOT_ISSUED_MSK                  (((1U << SDH_CMD_NOT_ISSUED_LEN) - 1) << SDH_CMD_NOT_ISSUED_POS)
#define SDH_CMD_NOT_ISSUED_UMSK                 (~(((1U << SDH_CMD_NOT_ISSUED_LEN) - 1) << SDH_CMD_NOT_ISSUED_POS))

/* 0x3e : Host Control 2 Register */
#define SDH_UHS_MODE_SEL                        SDH_UHS_MODE_SEL
#define SDH_UHS_MODE_SEL_POS                    (0U)
#define SDH_UHS_MODE_SEL_LEN                    (3U)
#define SDH_UHS_MODE_SEL_MSK                    (((1U << SDH_UHS_MODE_SEL_LEN) - 1) << SDH_UHS_MODE_SEL_POS)
#define SDH_UHS_MODE_SEL_UMSK                   (~(((1U << SDH_UHS_MODE_SEL_LEN) - 1) << SDH_UHS_MODE_SEL_POS))
#define SDH_SDH_V18_EN                          SDH_SDH_V18_EN
#define SDH_SDH_V18_EN_POS                      (3U)
#define SDH_SDH_V18_EN_LEN                      (1U)
#define SDH_SDH_V18_EN_MSK                      (((1U << SDH_SDH_V18_EN_LEN) - 1) << SDH_SDH_V18_EN_POS)
#define SDH_SDH_V18_EN_UMSK                     (~(((1U << SDH_SDH_V18_EN_LEN) - 1) << SDH_SDH_V18_EN_POS))
#define SDH_DRV_STRENGTH_SEL                    SDH_DRV_STRENGTH_SEL
#define SDH_DRV_STRENGTH_SEL_POS                (4U)
#define SDH_DRV_STRENGTH_SEL_LEN                (2U)
#define SDH_DRV_STRENGTH_SEL_MSK                (((1U << SDH_DRV_STRENGTH_SEL_LEN) - 1) << SDH_DRV_STRENGTH_SEL_POS)
#define SDH_DRV_STRENGTH_SEL_UMSK               (~(((1U << SDH_DRV_STRENGTH_SEL_LEN) - 1) << SDH_DRV_STRENGTH_SEL_POS))
#define SDH_EXE_TUNING                          SDH_EXE_TUNING
#define SDH_EXE_TUNING_POS                      (6U)
#define SDH_EXE_TUNING_LEN                      (1U)
#define SDH_EXE_TUNING_MSK                      (((1U << SDH_EXE_TUNING_LEN) - 1) << SDH_EXE_TUNING_POS)
#define SDH_EXE_TUNING_UMSK                     (~(((1U << SDH_EXE_TUNING_LEN) - 1) << SDH_EXE_TUNING_POS))
#define SDH_SAMPLING_CLK_SEL                    SDH_SAMPLING_CLK_SEL
#define SDH_SAMPLING_CLK_SEL_POS                (7U)
#define SDH_SAMPLING_CLK_SEL_LEN                (1U)
#define SDH_SAMPLING_CLK_SEL_MSK                (((1U << SDH_SAMPLING_CLK_SEL_LEN) - 1) << SDH_SAMPLING_CLK_SEL_POS)
#define SDH_SAMPLING_CLK_SEL_UMSK               (~(((1U << SDH_SAMPLING_CLK_SEL_LEN) - 1) << SDH_SAMPLING_CLK_SEL_POS))
#define SDH_ASYNC_INT_EN                        SDH_ASYNC_INT_EN
#define SDH_ASYNC_INT_EN_POS                    (14U)
#define SDH_ASYNC_INT_EN_LEN                    (1U)
#define SDH_ASYNC_INT_EN_MSK                    (((1U << SDH_ASYNC_INT_EN_LEN) - 1) << SDH_ASYNC_INT_EN_POS)
#define SDH_ASYNC_INT_EN_UMSK                   (~(((1U << SDH_ASYNC_INT_EN_LEN) - 1) << SDH_ASYNC_INT_EN_POS))
#define SDH_PRE_VAL_EN                          SDH_PRE_VAL_EN
#define SDH_PRE_VAL_EN_POS                      (15U)
#define SDH_PRE_VAL_EN_LEN                      (1U)
#define SDH_PRE_VAL_EN_MSK                      (((1U << SDH_PRE_VAL_EN_LEN) - 1) << SDH_PRE_VAL_EN_POS)
#define SDH_PRE_VAL_EN_UMSK                     (~(((1U << SDH_PRE_VAL_EN_LEN) - 1) << SDH_PRE_VAL_EN_POS))

/* 0x40 : Capabilities Register 1 */
#define SDH_TIMEOUT_FREQ                        SDH_TIMEOUT_FREQ
#define SDH_TIMEOUT_FREQ_POS                    (0U)
#define SDH_TIMEOUT_FREQ_LEN                    (6U)
#define SDH_TIMEOUT_FREQ_MSK                    (((1U << SDH_TIMEOUT_FREQ_LEN) - 1) << SDH_TIMEOUT_FREQ_POS)
#define SDH_TIMEOUT_FREQ_UMSK                   (~(((1U << SDH_TIMEOUT_FREQ_LEN) - 1) << SDH_TIMEOUT_FREQ_POS))
#define SDH_TIMEOUT_UNIT                        SDH_TIMEOUT_UNIT
#define SDH_TIMEOUT_UNIT_POS                    (7U)
#define SDH_TIMEOUT_UNIT_LEN                    (1U)
#define SDH_TIMEOUT_UNIT_MSK                    (((1U << SDH_TIMEOUT_UNIT_LEN) - 1) << SDH_TIMEOUT_UNIT_POS)
#define SDH_TIMEOUT_UNIT_UMSK                   (~(((1U << SDH_TIMEOUT_UNIT_LEN) - 1) << SDH_TIMEOUT_UNIT_POS))
#define SDH_BASE_FREQ                           SDH_BASE_FREQ
#define SDH_BASE_FREQ_POS                       (8U)
#define SDH_BASE_FREQ_LEN                       (8U)
#define SDH_BASE_FREQ_MSK                       (((1U << SDH_BASE_FREQ_LEN) - 1) << SDH_BASE_FREQ_POS)
#define SDH_BASE_FREQ_UMSK                      (~(((1U << SDH_BASE_FREQ_LEN) - 1) << SDH_BASE_FREQ_POS))

/* 0x42 : Capabilities Register 2 */
#define SDH_MAX_BLK_LEN                         SDH_MAX_BLK_LEN
#define SDH_MAX_BLK_LEN_POS                     (0U)
#define SDH_MAX_BLK_LEN_LEN                     (2U)
#define SDH_MAX_BLK_LEN_MSK                     (((1U << SDH_MAX_BLK_LEN_LEN) - 1) << SDH_MAX_BLK_LEN_POS)
#define SDH_MAX_BLK_LEN_UMSK                    (~(((1U << SDH_MAX_BLK_LEN_LEN) - 1) << SDH_MAX_BLK_LEN_POS))
#define SDH_EX_DATA_WIDTH_SUPPORT               SDH_EX_DATA_WIDTH_SUPPORT
#define SDH_EX_DATA_WIDTH_SUPPORT_POS           (2U)
#define SDH_EX_DATA_WIDTH_SUPPORT_LEN           (1U)
#define SDH_EX_DATA_WIDTH_SUPPORT_MSK           (((1U << SDH_EX_DATA_WIDTH_SUPPORT_LEN) - 1) << SDH_EX_DATA_WIDTH_SUPPORT_POS)
#define SDH_EX_DATA_WIDTH_SUPPORT_UMSK          (~(((1U << SDH_EX_DATA_WIDTH_SUPPORT_LEN) - 1) << SDH_EX_DATA_WIDTH_SUPPORT_POS))
#define SDH_ADMA2_SUPPORT                       SDH_ADMA2_SUPPORT
#define SDH_ADMA2_SUPPORT_POS                   (3U)
#define SDH_ADMA2_SUPPORT_LEN                   (1U)
#define SDH_ADMA2_SUPPORT_MSK                   (((1U << SDH_ADMA2_SUPPORT_LEN) - 1) << SDH_ADMA2_SUPPORT_POS)
#define SDH_ADMA2_SUPPORT_UMSK                  (~(((1U << SDH_ADMA2_SUPPORT_LEN) - 1) << SDH_ADMA2_SUPPORT_POS))
#define SDH_ADMA1_SUPPORT                       SDH_ADMA1_SUPPORT
#define SDH_ADMA1_SUPPORT_POS                   (4U)
#define SDH_ADMA1_SUPPORT_LEN                   (1U)
#define SDH_ADMA1_SUPPORT_MSK                   (((1U << SDH_ADMA1_SUPPORT_LEN) - 1) << SDH_ADMA1_SUPPORT_POS)
#define SDH_ADMA1_SUPPORT_UMSK                  (~(((1U << SDH_ADMA1_SUPPORT_LEN) - 1) << SDH_ADMA1_SUPPORT_POS))
#define SDH_HI_SPEED_SUPPORT                    SDH_HI_SPEED_SUPPORT
#define SDH_HI_SPEED_SUPPORT_POS                (5U)
#define SDH_HI_SPEED_SUPPORT_LEN                (1U)
#define SDH_HI_SPEED_SUPPORT_MSK                (((1U << SDH_HI_SPEED_SUPPORT_LEN) - 1) << SDH_HI_SPEED_SUPPORT_POS)
#define SDH_HI_SPEED_SUPPORT_UMSK               (~(((1U << SDH_HI_SPEED_SUPPORT_LEN) - 1) << SDH_HI_SPEED_SUPPORT_POS))
#define SDH_SDMA_SUPPORT                        SDH_SDMA_SUPPORT
#define SDH_SDMA_SUPPORT_POS                    (6U)
#define SDH_SDMA_SUPPORT_LEN                    (1U)
#define SDH_SDMA_SUPPORT_MSK                    (((1U << SDH_SDMA_SUPPORT_LEN) - 1) << SDH_SDMA_SUPPORT_POS)
#define SDH_SDMA_SUPPORT_UMSK                   (~(((1U << SDH_SDMA_SUPPORT_LEN) - 1) << SDH_SDMA_SUPPORT_POS))
#define SDH_SUS_RES_SUPPORT                     SDH_SUS_RES_SUPPORT
#define SDH_SUS_RES_SUPPORT_POS                 (7U)
#define SDH_SUS_RES_SUPPORT_LEN                 (1U)
#define SDH_SUS_RES_SUPPORT_MSK                 (((1U << SDH_SUS_RES_SUPPORT_LEN) - 1) << SDH_SUS_RES_SUPPORT_POS)
#define SDH_SUS_RES_SUPPORT_UMSK                (~(((1U << SDH_SUS_RES_SUPPORT_LEN) - 1) << SDH_SUS_RES_SUPPORT_POS))
#define SDH_VLG_33_SUPPORT                      SDH_VLG_33_SUPPORT
#define SDH_VLG_33_SUPPORT_POS                  (8U)
#define SDH_VLG_33_SUPPORT_LEN                  (1U)
#define SDH_VLG_33_SUPPORT_MSK                  (((1U << SDH_VLG_33_SUPPORT_LEN) - 1) << SDH_VLG_33_SUPPORT_POS)
#define SDH_VLG_33_SUPPORT_UMSK                 (~(((1U << SDH_VLG_33_SUPPORT_LEN) - 1) << SDH_VLG_33_SUPPORT_POS))
#define SDH_VLG_30_SUPPORT                      SDH_VLG_30_SUPPORT
#define SDH_VLG_30_SUPPORT_POS                  (9U)
#define SDH_VLG_30_SUPPORT_LEN                  (1U)
#define SDH_VLG_30_SUPPORT_MSK                  (((1U << SDH_VLG_30_SUPPORT_LEN) - 1) << SDH_VLG_30_SUPPORT_POS)
#define SDH_VLG_30_SUPPORT_UMSK                 (~(((1U << SDH_VLG_30_SUPPORT_LEN) - 1) << SDH_VLG_30_SUPPORT_POS))
#define SDH_VLG_18_SUPPORT                      SDH_VLG_18_SUPPORT
#define SDH_VLG_18_SUPPORT_POS                  (10U)
#define SDH_VLG_18_SUPPORT_LEN                  (1U)
#define SDH_VLG_18_SUPPORT_MSK                  (((1U << SDH_VLG_18_SUPPORT_LEN) - 1) << SDH_VLG_18_SUPPORT_POS)
#define SDH_VLG_18_SUPPORT_UMSK                 (~(((1U << SDH_VLG_18_SUPPORT_LEN) - 1) << SDH_VLG_18_SUPPORT_POS))
#define SDH_SYS_BUS_64_SUPPORT                  SDH_SYS_BUS_64_SUPPORT
#define SDH_SYS_BUS_64_SUPPORT_POS              (12U)
#define SDH_SYS_BUS_64_SUPPORT_LEN              (1U)
#define SDH_SYS_BUS_64_SUPPORT_MSK              (((1U << SDH_SYS_BUS_64_SUPPORT_LEN) - 1) << SDH_SYS_BUS_64_SUPPORT_POS)
#define SDH_SYS_BUS_64_SUPPORT_UMSK             (~(((1U << SDH_SYS_BUS_64_SUPPORT_LEN) - 1) << SDH_SYS_BUS_64_SUPPORT_POS))
#define SDH_ASYNC_INT_SUPPORT                   SDH_ASYNC_INT_SUPPORT
#define SDH_ASYNC_INT_SUPPORT_POS               (13U)
#define SDH_ASYNC_INT_SUPPORT_LEN               (1U)
#define SDH_ASYNC_INT_SUPPORT_MSK               (((1U << SDH_ASYNC_INT_SUPPORT_LEN) - 1) << SDH_ASYNC_INT_SUPPORT_POS)
#define SDH_ASYNC_INT_SUPPORT_UMSK              (~(((1U << SDH_ASYNC_INT_SUPPORT_LEN) - 1) << SDH_ASYNC_INT_SUPPORT_POS))
#define SDH_CFG_SLOT_TYPE                       SDH_CFG_SLOT_TYPE
#define SDH_CFG_SLOT_TYPE_POS                   (14U)
#define SDH_CFG_SLOT_TYPE_LEN                   (2U)
#define SDH_CFG_SLOT_TYPE_MSK                   (((1U << SDH_CFG_SLOT_TYPE_LEN) - 1) << SDH_CFG_SLOT_TYPE_POS)
#define SDH_CFG_SLOT_TYPE_UMSK                  (~(((1U << SDH_CFG_SLOT_TYPE_LEN) - 1) << SDH_CFG_SLOT_TYPE_POS))

/* 0x44 : Capabilities Register 3 */
#define SDH_SDR50_SUPPORT                       SDH_SDR50_SUPPORT
#define SDH_SDR50_SUPPORT_POS                   (0U)
#define SDH_SDR50_SUPPORT_LEN                   (1U)
#define SDH_SDR50_SUPPORT_MSK                   (((1U << SDH_SDR50_SUPPORT_LEN) - 1) << SDH_SDR50_SUPPORT_POS)
#define SDH_SDR50_SUPPORT_UMSK                  (~(((1U << SDH_SDR50_SUPPORT_LEN) - 1) << SDH_SDR50_SUPPORT_POS))
#define SDH_SDR104_SUPPORT                      SDH_SDR104_SUPPORT
#define SDH_SDR104_SUPPORT_POS                  (1U)
#define SDH_SDR104_SUPPORT_LEN                  (1U)
#define SDH_SDR104_SUPPORT_MSK                  (((1U << SDH_SDR104_SUPPORT_LEN) - 1) << SDH_SDR104_SUPPORT_POS)
#define SDH_SDR104_SUPPORT_UMSK                 (~(((1U << SDH_SDR104_SUPPORT_LEN) - 1) << SDH_SDR104_SUPPORT_POS))
#define SDH_DDR50_SUPPORT                       SDH_DDR50_SUPPORT
#define SDH_DDR50_SUPPORT_POS                   (2U)
#define SDH_DDR50_SUPPORT_LEN                   (1U)
#define SDH_DDR50_SUPPORT_MSK                   (((1U << SDH_DDR50_SUPPORT_LEN) - 1) << SDH_DDR50_SUPPORT_POS)
#define SDH_DDR50_SUPPORT_UMSK                  (~(((1U << SDH_DDR50_SUPPORT_LEN) - 1) << SDH_DDR50_SUPPORT_POS))
#define SDH_DRV_TYPE_A                          SDH_DRV_TYPE_A
#define SDH_DRV_TYPE_A_POS                      (4U)
#define SDH_DRV_TYPE_A_LEN                      (1U)
#define SDH_DRV_TYPE_A_MSK                      (((1U << SDH_DRV_TYPE_A_LEN) - 1) << SDH_DRV_TYPE_A_POS)
#define SDH_DRV_TYPE_A_UMSK                     (~(((1U << SDH_DRV_TYPE_A_LEN) - 1) << SDH_DRV_TYPE_A_POS))
#define SDH_DRV_TYPE_C                          SDH_DRV_TYPE_C
#define SDH_DRV_TYPE_C_POS                      (5U)
#define SDH_DRV_TYPE_C_LEN                      (1U)
#define SDH_DRV_TYPE_C_MSK                      (((1U << SDH_DRV_TYPE_C_LEN) - 1) << SDH_DRV_TYPE_C_POS)
#define SDH_DRV_TYPE_C_UMSK                     (~(((1U << SDH_DRV_TYPE_C_LEN) - 1) << SDH_DRV_TYPE_C_POS))
#define SDH_DRV_TYPE_D                          SDH_DRV_TYPE_D
#define SDH_DRV_TYPE_D_POS                      (6U)
#define SDH_DRV_TYPE_D_LEN                      (1U)
#define SDH_DRV_TYPE_D_MSK                      (((1U << SDH_DRV_TYPE_D_LEN) - 1) << SDH_DRV_TYPE_D_POS)
#define SDH_DRV_TYPE_D_UMSK                     (~(((1U << SDH_DRV_TYPE_D_LEN) - 1) << SDH_DRV_TYPE_D_POS))
#define SDH_TMR_RETUNE                          SDH_TMR_RETUNE
#define SDH_TMR_RETUNE_POS                      (8U)
#define SDH_TMR_RETUNE_LEN                      (4U)
#define SDH_TMR_RETUNE_MSK                      (((1U << SDH_TMR_RETUNE_LEN) - 1) << SDH_TMR_RETUNE_POS)
#define SDH_TMR_RETUNE_UMSK                     (~(((1U << SDH_TMR_RETUNE_LEN) - 1) << SDH_TMR_RETUNE_POS))
#define SDH_SDR50_TUNE                          SDH_SDR50_TUNE
#define SDH_SDR50_TUNE_POS                      (13U)
#define SDH_SDR50_TUNE_LEN                      (1U)
#define SDH_SDR50_TUNE_MSK                      (((1U << SDH_SDR50_TUNE_LEN) - 1) << SDH_SDR50_TUNE_POS)
#define SDH_SDR50_TUNE_UMSK                     (~(((1U << SDH_SDR50_TUNE_LEN) - 1) << SDH_SDR50_TUNE_POS))
#define SDH_RETUNE_MODES                        SDH_RETUNE_MODES
#define SDH_RETUNE_MODES_POS                    (14U)
#define SDH_RETUNE_MODES_LEN                    (2U)
#define SDH_RETUNE_MODES_MSK                    (((1U << SDH_RETUNE_MODES_LEN) - 1) << SDH_RETUNE_MODES_POS)
#define SDH_RETUNE_MODES_UMSK                   (~(((1U << SDH_RETUNE_MODES_LEN) - 1) << SDH_RETUNE_MODES_POS))

/* 0x46 : Capabilities Register 4 */
#define SDH_CLK_MULTIPLIER                      SDH_CLK_MULTIPLIER
#define SDH_CLK_MULTIPLIER_POS                  (0U)
#define SDH_CLK_MULTIPLIER_LEN                  (8U)
#define SDH_CLK_MULTIPLIER_MSK                  (((1U << SDH_CLK_MULTIPLIER_LEN) - 1) << SDH_CLK_MULTIPLIER_POS)
#define SDH_CLK_MULTIPLIER_UMSK                 (~(((1U << SDH_CLK_MULTIPLIER_LEN) - 1) << SDH_CLK_MULTIPLIER_POS))

/* 0x48 : Maximum Current Register 1 */
#define SDH_MAX_CUR_33                          SDH_MAX_CUR_33
#define SDH_MAX_CUR_33_POS                      (0U)
#define SDH_MAX_CUR_33_LEN                      (8U)
#define SDH_MAX_CUR_33_MSK                      (((1U << SDH_MAX_CUR_33_LEN) - 1) << SDH_MAX_CUR_33_POS)
#define SDH_MAX_CUR_33_UMSK                     (~(((1U << SDH_MAX_CUR_33_LEN) - 1) << SDH_MAX_CUR_33_POS))
#define SDH_MAX_CUR_30                          SDH_MAX_CUR_30
#define SDH_MAX_CUR_30_POS                      (8U)
#define SDH_MAX_CUR_30_LEN                      (8U)
#define SDH_MAX_CUR_30_MSK                      (((1U << SDH_MAX_CUR_30_LEN) - 1) << SDH_MAX_CUR_30_POS)
#define SDH_MAX_CUR_30_UMSK                     (~(((1U << SDH_MAX_CUR_30_LEN) - 1) << SDH_MAX_CUR_30_POS))

/* 0x4A : Maximum Current Register 2 */
#define SDH_MAX_CUR_18                          SDH_MAX_CUR_18
#define SDH_MAX_CUR_18_POS                      (0U)
#define SDH_MAX_CUR_18_LEN                      (8U)
#define SDH_MAX_CUR_18_MSK                      (((1U << SDH_MAX_CUR_18_LEN) - 1) << SDH_MAX_CUR_18_POS)
#define SDH_MAX_CUR_18_UMSK                     (~(((1U << SDH_MAX_CUR_18_LEN) - 1) << SDH_MAX_CUR_18_POS))

/* 0x4C : Maximum Current Register 3 */

/* 0x4E : Maximum Current Register 4 */

/* 0x50 : Force Event Auto cmd12 Error Register */
#define SDH_F_ACMD12_NEXE_ERR                   SDH_F_ACMD12_NEXE_ERR
#define SDH_F_ACMD12_NEXE_ERR_POS               (0U)
#define SDH_F_ACMD12_NEXE_ERR_LEN               (1U)
#define SDH_F_ACMD12_NEXE_ERR_MSK               (((1U << SDH_F_ACMD12_NEXE_ERR_LEN) - 1) << SDH_F_ACMD12_NEXE_ERR_POS)
#define SDH_F_ACMD12_NEXE_ERR_UMSK              (~(((1U << SDH_F_ACMD12_NEXE_ERR_LEN) - 1) << SDH_F_ACMD12_NEXE_ERR_POS))
#define SDH_F_ACMD_TO_ERR                       SDH_F_ACMD_TO_ERR
#define SDH_F_ACMD_TO_ERR_POS                   (1U)
#define SDH_F_ACMD_TO_ERR_LEN                   (1U)
#define SDH_F_ACMD_TO_ERR_MSK                   (((1U << SDH_F_ACMD_TO_ERR_LEN) - 1) << SDH_F_ACMD_TO_ERR_POS)
#define SDH_F_ACMD_TO_ERR_UMSK                  (~(((1U << SDH_F_ACMD_TO_ERR_LEN) - 1) << SDH_F_ACMD_TO_ERR_POS))
#define SDH_F_ACMD_CRC_ERR                      SDH_F_ACMD_CRC_ERR
#define SDH_F_ACMD_CRC_ERR_POS                  (2U)
#define SDH_F_ACMD_CRC_ERR_LEN                  (1U)
#define SDH_F_ACMD_CRC_ERR_MSK                  (((1U << SDH_F_ACMD_CRC_ERR_LEN) - 1) << SDH_F_ACMD_CRC_ERR_POS)
#define SDH_F_ACMD_CRC_ERR_UMSK                 (~(((1U << SDH_F_ACMD_CRC_ERR_LEN) - 1) << SDH_F_ACMD_CRC_ERR_POS))
#define SDH_F__ACMD_EBIT_ERR                    SDH_F__ACMD_EBIT_ERR
#define SDH_F__ACMD_EBIT_ERR_POS                (3U)
#define SDH_F__ACMD_EBIT_ERR_LEN                (1U)
#define SDH_F__ACMD_EBIT_ERR_MSK                (((1U << SDH_F__ACMD_EBIT_ERR_LEN) - 1) << SDH_F__ACMD_EBIT_ERR_POS)
#define SDH_F__ACMD_EBIT_ERR_UMSK               (~(((1U << SDH_F__ACMD_EBIT_ERR_LEN) - 1) << SDH_F__ACMD_EBIT_ERR_POS))
#define SDH_F_ACMD_INDEX_ERR                    SDH_F_ACMD_INDEX_ERR
#define SDH_F_ACMD_INDEX_ERR_POS                (4U)
#define SDH_F_ACMD_INDEX_ERR_LEN                (1U)
#define SDH_F_ACMD_INDEX_ERR_MSK                (((1U << SDH_F_ACMD_INDEX_ERR_LEN) - 1) << SDH_F_ACMD_INDEX_ERR_POS)
#define SDH_F_ACMD_INDEX_ERR_UMSK               (~(((1U << SDH_F_ACMD_INDEX_ERR_LEN) - 1) << SDH_F_ACMD_INDEX_ERR_POS))
#define SDH_F_ACMD12_ISSUE_ERR                  SDH_F_ACMD12_ISSUE_ERR
#define SDH_F_ACMD12_ISSUE_ERR_POS              (7U)
#define SDH_F_ACMD12_ISSUE_ERR_LEN              (1U)
#define SDH_F_ACMD12_ISSUE_ERR_MSK              (((1U << SDH_F_ACMD12_ISSUE_ERR_LEN) - 1) << SDH_F_ACMD12_ISSUE_ERR_POS)
#define SDH_F_ACMD12_ISSUE_ERR_UMSK             (~(((1U << SDH_F_ACMD12_ISSUE_ERR_LEN) - 1) << SDH_F_ACMD12_ISSUE_ERR_POS))

/* 0x52 : Force Event for Error Status Register */
#define SDH_F_CMD_TO_ERR                        SDH_F_CMD_TO_ERR
#define SDH_F_CMD_TO_ERR_POS                    (0U)
#define SDH_F_CMD_TO_ERR_LEN                    (1U)
#define SDH_F_CMD_TO_ERR_MSK                    (((1U << SDH_F_CMD_TO_ERR_LEN) - 1) << SDH_F_CMD_TO_ERR_POS)
#define SDH_F_CMD_TO_ERR_UMSK                   (~(((1U << SDH_F_CMD_TO_ERR_LEN) - 1) << SDH_F_CMD_TO_ERR_POS))
#define SDH_F_CMD_CRC_ERR                       SDH_F_CMD_CRC_ERR
#define SDH_F_CMD_CRC_ERR_POS                   (1U)
#define SDH_F_CMD_CRC_ERR_LEN                   (1U)
#define SDH_F_CMD_CRC_ERR_MSK                   (((1U << SDH_F_CMD_CRC_ERR_LEN) - 1) << SDH_F_CMD_CRC_ERR_POS)
#define SDH_F_CMD_CRC_ERR_UMSK                  (~(((1U << SDH_F_CMD_CRC_ERR_LEN) - 1) << SDH_F_CMD_CRC_ERR_POS))
#define SDH_F_CMD_END_BIT_ERR                   SDH_F_CMD_END_BIT_ERR
#define SDH_F_CMD_END_BIT_ERR_POS               (2U)
#define SDH_F_CMD_END_BIT_ERR_LEN               (1U)
#define SDH_F_CMD_END_BIT_ERR_MSK               (((1U << SDH_F_CMD_END_BIT_ERR_LEN) - 1) << SDH_F_CMD_END_BIT_ERR_POS)
#define SDH_F_CMD_END_BIT_ERR_UMSK              (~(((1U << SDH_F_CMD_END_BIT_ERR_LEN) - 1) << SDH_F_CMD_END_BIT_ERR_POS))
#define SDH_F_CMD_INDEX_ERR                     SDH_F_CMD_INDEX_ERR
#define SDH_F_CMD_INDEX_ERR_POS                 (3U)
#define SDH_F_CMD_INDEX_ERR_LEN                 (1U)
#define SDH_F_CMD_INDEX_ERR_MSK                 (((1U << SDH_F_CMD_INDEX_ERR_LEN) - 1) << SDH_F_CMD_INDEX_ERR_POS)
#define SDH_F_CMD_INDEX_ERR_UMSK                (~(((1U << SDH_F_CMD_INDEX_ERR_LEN) - 1) << SDH_F_CMD_INDEX_ERR_POS))
#define SDH_F_DAT_TO_ERR                        SDH_F_DAT_TO_ERR
#define SDH_F_DAT_TO_ERR_POS                    (4U)
#define SDH_F_DAT_TO_ERR_LEN                    (1U)
#define SDH_F_DAT_TO_ERR_MSK                    (((1U << SDH_F_DAT_TO_ERR_LEN) - 1) << SDH_F_DAT_TO_ERR_POS)
#define SDH_F_DAT_TO_ERR_UMSK                   (~(((1U << SDH_F_DAT_TO_ERR_LEN) - 1) << SDH_F_DAT_TO_ERR_POS))
#define SDH_F_DAT_CRC_ERR                       SDH_F_DAT_CRC_ERR
#define SDH_F_DAT_CRC_ERR_POS                   (5U)
#define SDH_F_DAT_CRC_ERR_LEN                   (1U)
#define SDH_F_DAT_CRC_ERR_MSK                   (((1U << SDH_F_DAT_CRC_ERR_LEN) - 1) << SDH_F_DAT_CRC_ERR_POS)
#define SDH_F_DAT_CRC_ERR_UMSK                  (~(((1U << SDH_F_DAT_CRC_ERR_LEN) - 1) << SDH_F_DAT_CRC_ERR_POS))
#define SDH_F_DAT_END_BIT_ERR                   SDH_F_DAT_END_BIT_ERR
#define SDH_F_DAT_END_BIT_ERR_POS               (6U)
#define SDH_F_DAT_END_BIT_ERR_LEN               (1U)
#define SDH_F_DAT_END_BIT_ERR_MSK               (((1U << SDH_F_DAT_END_BIT_ERR_LEN) - 1) << SDH_F_DAT_END_BIT_ERR_POS)
#define SDH_F_DAT_END_BIT_ERR_UMSK              (~(((1U << SDH_F_DAT_END_BIT_ERR_LEN) - 1) << SDH_F_DAT_END_BIT_ERR_POS))
#define SDH_F_CURRENT_ERR                       SDH_F_CURRENT_ERR
#define SDH_F_CURRENT_ERR_POS                   (7U)
#define SDH_F_CURRENT_ERR_LEN                   (1U)
#define SDH_F_CURRENT_ERR_MSK                   (((1U << SDH_F_CURRENT_ERR_LEN) - 1) << SDH_F_CURRENT_ERR_POS)
#define SDH_F_CURRENT_ERR_UMSK                  (~(((1U << SDH_F_CURRENT_ERR_LEN) - 1) << SDH_F_CURRENT_ERR_POS))
#define SDH_F_ACMD12_ERR                        SDH_F_ACMD12_ERR
#define SDH_F_ACMD12_ERR_POS                    (8U)
#define SDH_F_ACMD12_ERR_LEN                    (1U)
#define SDH_F_ACMD12_ERR_MSK                    (((1U << SDH_F_ACMD12_ERR_LEN) - 1) << SDH_F_ACMD12_ERR_POS)
#define SDH_F_ACMD12_ERR_UMSK                   (~(((1U << SDH_F_ACMD12_ERR_LEN) - 1) << SDH_F_ACMD12_ERR_POS))
#define SDH_F_ADMA_ERR                          SDH_F_ADMA_ERR
#define SDH_F_ADMA_ERR_POS                      (9U)
#define SDH_F_ADMA_ERR_LEN                      (1U)
#define SDH_F_ADMA_ERR_MSK                      (((1U << SDH_F_ADMA_ERR_LEN) - 1) << SDH_F_ADMA_ERR_POS)
#define SDH_F_ADMA_ERR_UMSK                     (~(((1U << SDH_F_ADMA_ERR_LEN) - 1) << SDH_F_ADMA_ERR_POS))
#define SDH_F_SPI_ERR                           SDH_F_SPI_ERR
#define SDH_F_SPI_ERR_POS                       (12U)
#define SDH_F_SPI_ERR_LEN                       (1U)
#define SDH_F_SPI_ERR_MSK                       (((1U << SDH_F_SPI_ERR_LEN) - 1) << SDH_F_SPI_ERR_POS)
#define SDH_F_SPI_ERR_UMSK                      (~(((1U << SDH_F_SPI_ERR_LEN) - 1) << SDH_F_SPI_ERR_POS))
#define SDH_F_AXI_RESP_ERR                      SDH_F_AXI_RESP_ERR
#define SDH_F_AXI_RESP_ERR_POS                  (13U)
#define SDH_F_AXI_RESP_ERR_LEN                  (1U)
#define SDH_F_AXI_RESP_ERR_MSK                  (((1U << SDH_F_AXI_RESP_ERR_LEN) - 1) << SDH_F_AXI_RESP_ERR_POS)
#define SDH_F_AXI_RESP_ERR_UMSK                 (~(((1U << SDH_F_AXI_RESP_ERR_LEN) - 1) << SDH_F_AXI_RESP_ERR_POS))
#define SDH_F_CPL_TIMEOUT_ERR                   SDH_F_CPL_TIMEOUT_ERR
#define SDH_F_CPL_TIMEOUT_ERR_POS               (14U)
#define SDH_F_CPL_TIMEOUT_ERR_LEN               (1U)
#define SDH_F_CPL_TIMEOUT_ERR_MSK               (((1U << SDH_F_CPL_TIMEOUT_ERR_LEN) - 1) << SDH_F_CPL_TIMEOUT_ERR_POS)
#define SDH_F_CPL_TIMEOUT_ERR_UMSK              (~(((1U << SDH_F_CPL_TIMEOUT_ERR_LEN) - 1) << SDH_F_CPL_TIMEOUT_ERR_POS))
#define SDH_F_CRC_STATUS_ERR                    SDH_F_CRC_STATUS_ERR
#define SDH_F_CRC_STATUS_ERR_POS                (15U)
#define SDH_F_CRC_STATUS_ERR_LEN                (1U)
#define SDH_F_CRC_STATUS_ERR_MSK                (((1U << SDH_F_CRC_STATUS_ERR_LEN) - 1) << SDH_F_CRC_STATUS_ERR_POS)
#define SDH_F_CRC_STATUS_ERR_UMSK               (~(((1U << SDH_F_CRC_STATUS_ERR_LEN) - 1) << SDH_F_CRC_STATUS_ERR_POS))

/* 0x54 : ADMA Error Status Register */
#define SDH_ADMA_STATE                          SDH_ADMA_STATE
#define SDH_ADMA_STATE_POS                      (0U)
#define SDH_ADMA_STATE_LEN                      (2U)
#define SDH_ADMA_STATE_MSK                      (((1U << SDH_ADMA_STATE_LEN) - 1) << SDH_ADMA_STATE_POS)
#define SDH_ADMA_STATE_UMSK                     (~(((1U << SDH_ADMA_STATE_LEN) - 1) << SDH_ADMA_STATE_POS))
#define SDH_ADMA_LEN_ERR                        SDH_ADMA_LEN_ERR
#define SDH_ADMA_LEN_ERR_POS                    (2U)
#define SDH_ADMA_LEN_ERR_LEN                    (1U)
#define SDH_ADMA_LEN_ERR_MSK                    (((1U << SDH_ADMA_LEN_ERR_LEN) - 1) << SDH_ADMA_LEN_ERR_POS)
#define SDH_ADMA_LEN_ERR_UMSK                   (~(((1U << SDH_ADMA_LEN_ERR_LEN) - 1) << SDH_ADMA_LEN_ERR_POS))

/* 0x58 : ADMA System Address Register 1 */
#define SDH_ADMA_SYS_ADDR                       SDH_ADMA_SYS_ADDR
#define SDH_ADMA_SYS_ADDR_POS                   (0U)
#define SDH_ADMA_SYS_ADDR_LEN                   (16U)
#define SDH_ADMA_SYS_ADDR_MSK                   (((1U << SDH_ADMA_SYS_ADDR_LEN) - 1) << SDH_ADMA_SYS_ADDR_POS)
#define SDH_ADMA_SYS_ADDR_UMSK                  (~(((1U << SDH_ADMA_SYS_ADDR_LEN) - 1) << SDH_ADMA_SYS_ADDR_POS))

/* 0x5A : ADMA System Address Register 2 */
#define SDH_ADMA_SYS_ADDR                       SDH_ADMA_SYS_ADDR
#define SDH_ADMA_SYS_ADDR_POS                   (0U)
#define SDH_ADMA_SYS_ADDR_LEN                   (16U)
#define SDH_ADMA_SYS_ADDR_MSK                   (((1U << SDH_ADMA_SYS_ADDR_LEN) - 1) << SDH_ADMA_SYS_ADDR_POS)
#define SDH_ADMA_SYS_ADDR_UMSK                  (~(((1U << SDH_ADMA_SYS_ADDR_LEN) - 1) << SDH_ADMA_SYS_ADDR_POS))

/* 0x5C : ADMA System Address Register 3 */
#define SDH_ADMA_SYS_ADDR                       SDH_ADMA_SYS_ADDR
#define SDH_ADMA_SYS_ADDR_POS                   (0U)
#define SDH_ADMA_SYS_ADDR_LEN                   (16U)
#define SDH_ADMA_SYS_ADDR_MSK                   (((1U << SDH_ADMA_SYS_ADDR_LEN) - 1) << SDH_ADMA_SYS_ADDR_POS)
#define SDH_ADMA_SYS_ADDR_UMSK                  (~(((1U << SDH_ADMA_SYS_ADDR_LEN) - 1) << SDH_ADMA_SYS_ADDR_POS))

/* 0x5E : ADMA System Address Register 4 */
#define SDH_ADMA_SYS_ADDR                       SDH_ADMA_SYS_ADDR
#define SDH_ADMA_SYS_ADDR_POS                   (0U)
#define SDH_ADMA_SYS_ADDR_LEN                   (16U)
#define SDH_ADMA_SYS_ADDR_MSK                   (((1U << SDH_ADMA_SYS_ADDR_LEN) - 1) << SDH_ADMA_SYS_ADDR_POS)
#define SDH_ADMA_SYS_ADDR_UMSK                  (~(((1U << SDH_ADMA_SYS_ADDR_LEN) - 1) << SDH_ADMA_SYS_ADDR_POS))

/* 0x60 : Preset Value Register for Initialization */
#define SDH_SDCLK_FREQ_SEL_VAL                  SDH_SDCLK_FREQ_SEL_VAL
#define SDH_SDCLK_FREQ_SEL_VAL_POS              (0U)
#define SDH_SDCLK_FREQ_SEL_VAL_LEN              (10U)
#define SDH_SDCLK_FREQ_SEL_VAL_MSK              (((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS)
#define SDH_SDCLK_FREQ_SEL_VAL_UMSK             (~(((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS))
#define SDH_CLKGEN_SEL_VAL                      SDH_CLKGEN_SEL_VAL
#define SDH_CLKGEN_SEL_VAL_POS                  (10U)
#define SDH_CLKGEN_SEL_VAL_LEN                  (1U)
#define SDH_CLKGEN_SEL_VAL_MSK                  (((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS)
#define SDH_CLKGEN_SEL_VAL_UMSK                 (~(((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS))
#define SDH_DRV_STRENGTH_VAL                    SDH_DRV_STRENGTH_VAL
#define SDH_DRV_STRENGTH_VAL_POS                (14U)
#define SDH_DRV_STRENGTH_VAL_LEN                (2U)
#define SDH_DRV_STRENGTH_VAL_MSK                (((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS)
#define SDH_DRV_STRENGTH_VAL_UMSK               (~(((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS))

/* 0x62 : Preset Value Register for Default Speed */
#define SDH_SDCLK_FREQ_SEL_VAL                  SDH_SDCLK_FREQ_SEL_VAL
#define SDH_SDCLK_FREQ_SEL_VAL_POS              (0U)
#define SDH_SDCLK_FREQ_SEL_VAL_LEN              (10U)
#define SDH_SDCLK_FREQ_SEL_VAL_MSK              (((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS)
#define SDH_SDCLK_FREQ_SEL_VAL_UMSK             (~(((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS))
#define SDH_CLKGEN_SEL_VAL                      SDH_CLKGEN_SEL_VAL
#define SDH_CLKGEN_SEL_VAL_POS                  (10U)
#define SDH_CLKGEN_SEL_VAL_LEN                  (1U)
#define SDH_CLKGEN_SEL_VAL_MSK                  (((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS)
#define SDH_CLKGEN_SEL_VAL_UMSK                 (~(((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS))
#define SDH_DRV_STRENGTH_VAL                    SDH_DRV_STRENGTH_VAL
#define SDH_DRV_STRENGTH_VAL_POS                (14U)
#define SDH_DRV_STRENGTH_VAL_LEN                (2U)
#define SDH_DRV_STRENGTH_VAL_MSK                (((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS)
#define SDH_DRV_STRENGTH_VAL_UMSK               (~(((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS))

/* 0x64 : Preset Value Register for High Speed */
#define SDH_SDCLK_FREQ_SEL_VAL                  SDH_SDCLK_FREQ_SEL_VAL
#define SDH_SDCLK_FREQ_SEL_VAL_POS              (0U)
#define SDH_SDCLK_FREQ_SEL_VAL_LEN              (10U)
#define SDH_SDCLK_FREQ_SEL_VAL_MSK              (((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS)
#define SDH_SDCLK_FREQ_SEL_VAL_UMSK             (~(((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS))
#define SDH_CLKGEN_SEL_VAL                      SDH_CLKGEN_SEL_VAL
#define SDH_CLKGEN_SEL_VAL_POS                  (10U)
#define SDH_CLKGEN_SEL_VAL_LEN                  (1U)
#define SDH_CLKGEN_SEL_VAL_MSK                  (((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS)
#define SDH_CLKGEN_SEL_VAL_UMSK                 (~(((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS))
#define SDH_DRV_STRENGTH_VAL                    SDH_DRV_STRENGTH_VAL
#define SDH_DRV_STRENGTH_VAL_POS                (14U)
#define SDH_DRV_STRENGTH_VAL_LEN                (2U)
#define SDH_DRV_STRENGTH_VAL_MSK                (((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS)
#define SDH_DRV_STRENGTH_VAL_UMSK               (~(((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS))

/* 0x66 : Preset Value Register for SDR12 */
#define SDH_SDCLK_FREQ_SEL_VAL                  SDH_SDCLK_FREQ_SEL_VAL
#define SDH_SDCLK_FREQ_SEL_VAL_POS              (0U)
#define SDH_SDCLK_FREQ_SEL_VAL_LEN              (10U)
#define SDH_SDCLK_FREQ_SEL_VAL_MSK              (((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS)
#define SDH_SDCLK_FREQ_SEL_VAL_UMSK             (~(((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS))
#define SDH_CLKGEN_SEL_VAL                      SDH_CLKGEN_SEL_VAL
#define SDH_CLKGEN_SEL_VAL_POS                  (10U)
#define SDH_CLKGEN_SEL_VAL_LEN                  (1U)
#define SDH_CLKGEN_SEL_VAL_MSK                  (((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS)
#define SDH_CLKGEN_SEL_VAL_UMSK                 (~(((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS))
#define SDH_DRV_STRENGTH_VAL                    SDH_DRV_STRENGTH_VAL
#define SDH_DRV_STRENGTH_VAL_POS                (14U)
#define SDH_DRV_STRENGTH_VAL_LEN                (2U)
#define SDH_DRV_STRENGTH_VAL_MSK                (((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS)
#define SDH_DRV_STRENGTH_VAL_UMSK               (~(((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS))

/* 0x68 : Preset Value Register for SDR25 */
#define SDH_SDCLK_FREQ_SEL_VAL                  SDH_SDCLK_FREQ_SEL_VAL
#define SDH_SDCLK_FREQ_SEL_VAL_POS              (0U)
#define SDH_SDCLK_FREQ_SEL_VAL_LEN              (10U)
#define SDH_SDCLK_FREQ_SEL_VAL_MSK              (((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS)
#define SDH_SDCLK_FREQ_SEL_VAL_UMSK             (~(((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS))
#define SDH_CLKGEN_SEL_VAL                      SDH_CLKGEN_SEL_VAL
#define SDH_CLKGEN_SEL_VAL_POS                  (10U)
#define SDH_CLKGEN_SEL_VAL_LEN                  (1U)
#define SDH_CLKGEN_SEL_VAL_MSK                  (((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS)
#define SDH_CLKGEN_SEL_VAL_UMSK                 (~(((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS))
#define SDH_DRV_STRENGTH_VAL                    SDH_DRV_STRENGTH_VAL
#define SDH_DRV_STRENGTH_VAL_POS                (14U)
#define SDH_DRV_STRENGTH_VAL_LEN                (2U)
#define SDH_DRV_STRENGTH_VAL_MSK                (((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS)
#define SDH_DRV_STRENGTH_VAL_UMSK               (~(((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS))

/* 0x6a : Preset Value Register for SDR50 */
#define SDH_SDCLK_FREQ_SEL_VAL                  SDH_SDCLK_FREQ_SEL_VAL
#define SDH_SDCLK_FREQ_SEL_VAL_POS              (0U)
#define SDH_SDCLK_FREQ_SEL_VAL_LEN              (10U)
#define SDH_SDCLK_FREQ_SEL_VAL_MSK              (((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS)
#define SDH_SDCLK_FREQ_SEL_VAL_UMSK             (~(((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS))
#define SDH_CLKGEN_SEL_VAL                      SDH_CLKGEN_SEL_VAL
#define SDH_CLKGEN_SEL_VAL_POS                  (10U)
#define SDH_CLKGEN_SEL_VAL_LEN                  (1U)
#define SDH_CLKGEN_SEL_VAL_MSK                  (((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS)
#define SDH_CLKGEN_SEL_VAL_UMSK                 (~(((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS))
#define SDH_DRV_STRENGTH_VAL                    SDH_DRV_STRENGTH_VAL
#define SDH_DRV_STRENGTH_VAL_POS                (14U)
#define SDH_DRV_STRENGTH_VAL_LEN                (2U)
#define SDH_DRV_STRENGTH_VAL_MSK                (((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS)
#define SDH_DRV_STRENGTH_VAL_UMSK               (~(((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS))

/* 0x6c : Preset Value Register for SDR104 */
#define SDH_SDCLK_FREQ_SEL_VAL                  SDH_SDCLK_FREQ_SEL_VAL
#define SDH_SDCLK_FREQ_SEL_VAL_POS              (0U)
#define SDH_SDCLK_FREQ_SEL_VAL_LEN              (10U)
#define SDH_SDCLK_FREQ_SEL_VAL_MSK              (((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS)
#define SDH_SDCLK_FREQ_SEL_VAL_UMSK             (~(((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS))
#define SDH_CLKGEN_SEL_VAL                      SDH_CLKGEN_SEL_VAL
#define SDH_CLKGEN_SEL_VAL_POS                  (10U)
#define SDH_CLKGEN_SEL_VAL_LEN                  (1U)
#define SDH_CLKGEN_SEL_VAL_MSK                  (((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS)
#define SDH_CLKGEN_SEL_VAL_UMSK                 (~(((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS))
#define SDH_DRV_STRENGTH_VAL                    SDH_DRV_STRENGTH_VAL
#define SDH_DRV_STRENGTH_VAL_POS                (14U)
#define SDH_DRV_STRENGTH_VAL_LEN                (2U)
#define SDH_DRV_STRENGTH_VAL_MSK                (((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS)
#define SDH_DRV_STRENGTH_VAL_UMSK               (~(((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS))

/* 0x6e : Preset Value Register for DDR50 */
#define SDH_SDCLK_FREQ_SEL_VAL                  SDH_SDCLK_FREQ_SEL_VAL
#define SDH_SDCLK_FREQ_SEL_VAL_POS              (0U)
#define SDH_SDCLK_FREQ_SEL_VAL_LEN              (10U)
#define SDH_SDCLK_FREQ_SEL_VAL_MSK              (((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS)
#define SDH_SDCLK_FREQ_SEL_VAL_UMSK             (~(((1U << SDH_SDCLK_FREQ_SEL_VAL_LEN) - 1) << SDH_SDCLK_FREQ_SEL_VAL_POS))
#define SDH_CLKGEN_SEL_VAL                      SDH_CLKGEN_SEL_VAL
#define SDH_CLKGEN_SEL_VAL_POS                  (10U)
#define SDH_CLKGEN_SEL_VAL_LEN                  (1U)
#define SDH_CLKGEN_SEL_VAL_MSK                  (((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS)
#define SDH_CLKGEN_SEL_VAL_UMSK                 (~(((1U << SDH_CLKGEN_SEL_VAL_LEN) - 1) << SDH_CLKGEN_SEL_VAL_POS))
#define SDH_DRV_STRENGTH_VAL                    SDH_DRV_STRENGTH_VAL
#define SDH_DRV_STRENGTH_VAL_POS                (14U)
#define SDH_DRV_STRENGTH_VAL_LEN                (2U)
#define SDH_DRV_STRENGTH_VAL_MSK                (((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS)
#define SDH_DRV_STRENGTH_VAL_UMSK               (~(((1U << SDH_DRV_STRENGTH_VAL_LEN) - 1) << SDH_DRV_STRENGTH_VAL_POS))

/* 0xe0 : Shared Bus Control Register */
#define SDH_NUM_CLK_PINS                        SDH_NUM_CLK_PINS
#define SDH_NUM_CLK_PINS_POS                    (0U)
#define SDH_NUM_CLK_PINS_LEN                    (3U)
#define SDH_NUM_CLK_PINS_MSK                    (((1U << SDH_NUM_CLK_PINS_LEN) - 1) << SDH_NUM_CLK_PINS_POS)
#define SDH_NUM_CLK_PINS_UMSK                   (~(((1U << SDH_NUM_CLK_PINS_LEN) - 1) << SDH_NUM_CLK_PINS_POS))
#define SDH_NUM_INT_PINS                        SDH_NUM_INT_PINS
#define SDH_NUM_INT_PINS_POS                    (4U)
#define SDH_NUM_INT_PINS_LEN                    (2U)
#define SDH_NUM_INT_PINS_MSK                    (((1U << SDH_NUM_INT_PINS_LEN) - 1) << SDH_NUM_INT_PINS_POS)
#define SDH_NUM_INT_PINS_UMSK                   (~(((1U << SDH_NUM_INT_PINS_LEN) - 1) << SDH_NUM_INT_PINS_POS))
#define SDH_BUS_WIDTH_PRESET                    SDH_BUS_WIDTH_PRESET
#define SDH_BUS_WIDTH_PRESET_POS                (8U)
#define SDH_BUS_WIDTH_PRESET_LEN                (7U)
#define SDH_BUS_WIDTH_PRESET_MSK                (((1U << SDH_BUS_WIDTH_PRESET_LEN) - 1) << SDH_BUS_WIDTH_PRESET_POS)
#define SDH_BUS_WIDTH_PRESET_UMSK               (~(((1U << SDH_BUS_WIDTH_PRESET_LEN) - 1) << SDH_BUS_WIDTH_PRESET_POS))
#define SDH_CLK_PIN_SEL                         SDH_CLK_PIN_SEL
#define SDH_CLK_PIN_SEL_POS                     (16U)
#define SDH_CLK_PIN_SEL_LEN                     (3U)
#define SDH_CLK_PIN_SEL_MSK                     (((1U << SDH_CLK_PIN_SEL_LEN) - 1) << SDH_CLK_PIN_SEL_POS)
#define SDH_CLK_PIN_SEL_UMSK                    (~(((1U << SDH_CLK_PIN_SEL_LEN) - 1) << SDH_CLK_PIN_SEL_POS))
#define SDH_INT_PIN_SEL                         SDH_INT_PIN_SEL
#define SDH_INT_PIN_SEL_POS                     (20U)
#define SDH_INT_PIN_SEL_LEN                     (3U)
#define SDH_INT_PIN_SEL_MSK                     (((1U << SDH_INT_PIN_SEL_LEN) - 1) << SDH_INT_PIN_SEL_POS)
#define SDH_INT_PIN_SEL_UMSK                    (~(((1U << SDH_INT_PIN_SEL_LEN) - 1) << SDH_INT_PIN_SEL_POS))
#define SDH_BEND_PWR_CTRL                       SDH_BEND_PWR_CTRL
#define SDH_BEND_PWR_CTRL_POS                   (24U)
#define SDH_BEND_PWR_CTRL_LEN                   (7U)
#define SDH_BEND_PWR_CTRL_MSK                   (((1U << SDH_BEND_PWR_CTRL_LEN) - 1) << SDH_BEND_PWR_CTRL_POS)
#define SDH_BEND_PWR_CTRL_UMSK                  (~(((1U << SDH_BEND_PWR_CTRL_LEN) - 1) << SDH_BEND_PWR_CTRL_POS))

/* 0xFC : Slot Interrupt Status Register */
#define SDH_SLOT_INT0                           SDH_SLOT_INT0
#define SDH_SLOT_INT0_POS                       (0U)
#define SDH_SLOT_INT0_LEN                       (1U)
#define SDH_SLOT_INT0_MSK                       (((1U << SDH_SLOT_INT0_LEN) - 1) << SDH_SLOT_INT0_POS)
#define SDH_SLOT_INT0_UMSK                      (~(((1U << SDH_SLOT_INT0_LEN) - 1) << SDH_SLOT_INT0_POS))
#define SDH_SLOT_INT1                           SDH_SLOT_INT1
#define SDH_SLOT_INT1_POS                       (1U)
#define SDH_SLOT_INT1_LEN                       (1U)
#define SDH_SLOT_INT1_MSK                       (((1U << SDH_SLOT_INT1_LEN) - 1) << SDH_SLOT_INT1_POS)
#define SDH_SLOT_INT1_UMSK                      (~(((1U << SDH_SLOT_INT1_LEN) - 1) << SDH_SLOT_INT1_POS))

/* 0xFE : Host Control Version Register */
#define SDH_SD_VER                              SDH_SD_VER
#define SDH_SD_VER_POS                          (0U)
#define SDH_SD_VER_LEN                          (8U)
#define SDH_SD_VER_MSK                          (((1U << SDH_SD_VER_LEN) - 1) << SDH_SD_VER_POS)
#define SDH_SD_VER_UMSK                         (~(((1U << SDH_SD_VER_LEN) - 1) << SDH_SD_VER_POS))
#define SDH_VENDOR_VER                          SDH_VENDOR_VER
#define SDH_VENDOR_VER_POS                      (8U)
#define SDH_VENDOR_VER_LEN                      (8U)
#define SDH_VENDOR_VER_MSK                      (((1U << SDH_VENDOR_VER_LEN) - 1) << SDH_VENDOR_VER_POS)
#define SDH_VENDOR_VER_UMSK                     (~(((1U << SDH_VENDOR_VER_LEN) - 1) << SDH_VENDOR_VER_POS))

#ifdef SDH_STD_V3

/* 0x100 : SD Extra Parameters Register */
#define SDH_BOOT_ACK                            SDH_BOOT_ACK
#define SDH_BOOT_ACK_POS                        (3U)
#define SDH_BOOT_ACK_LEN                        (1U)
#define SDH_BOOT_ACK_MSK                        (((1U << SDH_BOOT_ACK_LEN) - 1) << SDH_BOOT_ACK_POS)
#define SDH_BOOT_ACK_UMSK                       (~(((1U << SDH_BOOT_ACK_LEN) - 1) << SDH_BOOT_ACK_POS))
#define SDH_SQU_EMPTY_CHK                       SDH_SQU_EMPTY_CHK
#define SDH_SQU_EMPTY_CHK_POS                   (4U)
#define SDH_SQU_EMPTY_CHK_LEN                   (1U)
#define SDH_SQU_EMPTY_CHK_MSK                   (((1U << SDH_SQU_EMPTY_CHK_LEN) - 1) << SDH_SQU_EMPTY_CHK_POS)
#define SDH_SQU_EMPTY_CHK_UMSK                  (~(((1U << SDH_SQU_EMPTY_CHK_LEN) - 1) << SDH_SQU_EMPTY_CHK_POS))
#define SDH_SQU_FULL_CHK                        SDH_SQU_FULL_CHK
#define SDH_SQU_FULL_CHK_POS                    (5U)
#define SDH_SQU_FULL_CHK_LEN                    (1U)
#define SDH_SQU_FULL_CHK_MSK                    (((1U << SDH_SQU_FULL_CHK_LEN) - 1) << SDH_SQU_FULL_CHK_POS)
#define SDH_SQU_FULL_CHK_UMSK                   (~(((1U << SDH_SQU_FULL_CHK_LEN) - 1) << SDH_SQU_FULL_CHK_POS))
#define SDH_GEN_PAD_CLK_ON                      SDH_GEN_PAD_CLK_ON
#define SDH_GEN_PAD_CLK_ON_POS                  (6U)
#define SDH_GEN_PAD_CLK_ON_LEN                  (1U)
#define SDH_GEN_PAD_CLK_ON_MSK                  (((1U << SDH_GEN_PAD_CLK_ON_LEN) - 1) << SDH_GEN_PAD_CLK_ON_POS)
#define SDH_GEN_PAD_CLK_ON_UMSK                 (~(((1U << SDH_GEN_PAD_CLK_ON_LEN) - 1) << SDH_GEN_PAD_CLK_ON_POS))
#define SDH_GEN_PAD_CLK_CNT                     SDH_GEN_PAD_CLK_CNT
#define SDH_GEN_PAD_CLK_CNT_POS                 (24U)
#define SDH_GEN_PAD_CLK_CNT_LEN                 (8U)
#define SDH_GEN_PAD_CLK_CNT_MSK                 (((1U << SDH_GEN_PAD_CLK_CNT_LEN) - 1) << SDH_GEN_PAD_CLK_CNT_POS)
#define SDH_GEN_PAD_CLK_CNT_UMSK                (~(((1U << SDH_GEN_PAD_CLK_CNT_LEN) - 1) << SDH_GEN_PAD_CLK_CNT_POS))

/* 0x104 : FIFO Parameters Register */
#define SDH_RTC                                 SDH_RTC
#define SDH_RTC_POS                             (0U)
#define SDH_RTC_LEN                             (2U)
#define SDH_RTC_MSK                             (((1U << SDH_RTC_LEN) - 1) << SDH_RTC_POS)
#define SDH_RTC_UMSK                            (~(((1U << SDH_RTC_LEN) - 1) << SDH_RTC_POS))
#define SDH_WTC                                 SDH_WTC
#define SDH_WTC_POS                             (2U)
#define SDH_WTC_LEN                             (2U)
#define SDH_WTC_MSK                             (((1U << SDH_WTC_LEN) - 1) << SDH_WTC_POS)
#define SDH_WTC_UMSK                            (~(((1U << SDH_WTC_LEN) - 1) << SDH_WTC_POS))
#define SDH_FIFO_CLK                            SDH_FIFO_CLK
#define SDH_FIFO_CLK_POS                        (4U)
#define SDH_FIFO_CLK_LEN                        (1U)
#define SDH_FIFO_CLK_MSK                        (((1U << SDH_FIFO_CLK_LEN) - 1) << SDH_FIFO_CLK_POS)
#define SDH_FIFO_CLK_UMSK                       (~(((1U << SDH_FIFO_CLK_LEN) - 1) << SDH_FIFO_CLK_POS))
#define SDH_FIFO_CS                             SDH_FIFO_CS
#define SDH_FIFO_CS_POS                         (5U)
#define SDH_FIFO_CS_LEN                         (1U)
#define SDH_FIFO_CS_MSK                         (((1U << SDH_FIFO_CS_LEN) - 1) << SDH_FIFO_CS_POS)
#define SDH_FIFO_CS_UMSK                        (~(((1U << SDH_FIFO_CS_LEN) - 1) << SDH_FIFO_CS_POS))
#define SDH_PDWN                                SDH_PDWN
#define SDH_PDWN_POS                            (6U)
#define SDH_PDWN_LEN                            (1U)
#define SDH_PDWN_MSK                            (((1U << SDH_PDWN_LEN) - 1) << SDH_PDWN_POS)
#define SDH_PDWN_UMSK                           (~(((1U << SDH_PDWN_LEN) - 1) << SDH_PDWN_POS))
#define SDH_USE_DAT3                            SDH_USE_DAT3
#define SDH_USE_DAT3_POS                        (7U)
#define SDH_USE_DAT3_LEN                        (1U)
#define SDH_USE_DAT3_MSK                        (((1U << SDH_USE_DAT3_LEN) - 1) << SDH_USE_DAT3_POS)
#define SDH_USE_DAT3_UMSK                       (~(((1U << SDH_USE_DAT3_LEN) - 1) << SDH_USE_DAT3_POS))
#define SDH_CLK_GATE_CTL                        SDH_CLK_GATE_CTL
#define SDH_CLK_GATE_CTL_POS                    (8U)
#define SDH_CLK_GATE_CTL_LEN                    (1U)
#define SDH_CLK_GATE_CTL_MSK                    (((1U << SDH_CLK_GATE_CTL_LEN) - 1) << SDH_CLK_GATE_CTL_POS)
#define SDH_CLK_GATE_CTL_UMSK                   (~(((1U << SDH_CLK_GATE_CTL_LEN) - 1) << SDH_CLK_GATE_CTL_POS))
#define SDH_CLK_GATE_ON                         SDH_CLK_GATE_ON
#define SDH_CLK_GATE_ON_POS                     (9U)
#define SDH_CLK_GATE_ON_LEN                     (1U)
#define SDH_CLK_GATE_ON_MSK                     (((1U << SDH_CLK_GATE_ON_LEN) - 1) << SDH_CLK_GATE_ON_POS)
#define SDH_CLK_GATE_ON_UMSK                    (~(((1U << SDH_CLK_GATE_ON_LEN) - 1) << SDH_CLK_GATE_ON_POS))
#define SDH_OVRRD_CLK_OEN                       SDH_OVRRD_CLK_OEN
#define SDH_OVRRD_CLK_OEN_POS                   (11U)
#define SDH_OVRRD_CLK_OEN_LEN                   (1U)
#define SDH_OVRRD_CLK_OEN_MSK                   (((1U << SDH_OVRRD_CLK_OEN_LEN) - 1) << SDH_OVRRD_CLK_OEN_POS)
#define SDH_OVRRD_CLK_OEN_UMSK                  (~(((1U << SDH_OVRRD_CLK_OEN_LEN) - 1) << SDH_OVRRD_CLK_OEN_POS))
#define SDH_FORCE_CLK_ON                        SDH_FORCE_CLK_ON
#define SDH_FORCE_CLK_ON_POS                    (12U)
#define SDH_FORCE_CLK_ON_LEN                    (1U)
#define SDH_FORCE_CLK_ON_MSK                    (((1U << SDH_FORCE_CLK_ON_LEN) - 1) << SDH_FORCE_CLK_ON_POS)
#define SDH_FORCE_CLK_ON_UMSK                   (~(((1U << SDH_FORCE_CLK_ON_LEN) - 1) << SDH_FORCE_CLK_ON_POS))
#define SDH_PDFVSSM                             SDH_PDFVSSM
#define SDH_PDFVSSM_POS                         (13U)
#define SDH_PDFVSSM_LEN                         (1U)
#define SDH_PDFVSSM_MSK                         (((1U << SDH_PDFVSSM_LEN) - 1) << SDH_PDFVSSM_POS)
#define SDH_PDFVSSM_UMSK                        (~(((1U << SDH_PDFVSSM_LEN) - 1) << SDH_PDFVSSM_POS))
#define SDH_PDLVMC                              SDH_PDLVMC
#define SDH_PDLVMC_POS                          (14U)
#define SDH_PDLVMC_LEN                          (1U)
#define SDH_PDLVMC_MSK                          (((1U << SDH_PDLVMC_LEN) - 1) << SDH_PDLVMC_POS)
#define SDH_PDLVMC_UMSK                         (~(((1U << SDH_PDLVMC_LEN) - 1) << SDH_PDLVMC_POS))
#define SDH_PRE_GATE_CLK_CNT                    SDH_PRE_GATE_CLK_CNT
#define SDH_PRE_GATE_CLK_CNT_POS                (16U)
#define SDH_PRE_GATE_CLK_CNT_LEN                (4U)
#define SDH_PRE_GATE_CLK_CNT_MSK                (((1U << SDH_PRE_GATE_CLK_CNT_LEN) - 1) << SDH_PRE_GATE_CLK_CNT_POS)
#define SDH_PRE_GATE_CLK_CNT_UMSK               (~(((1U << SDH_PRE_GATE_CLK_CNT_LEN) - 1) << SDH_PRE_GATE_CLK_CNT_POS))

/* 0x108 : SPI Mode Register */
#define SDH_SPI_EN                              SDH_SPI_EN
#define SDH_SPI_EN_POS                          (0U)
#define SDH_SPI_EN_LEN                          (1U)
#define SDH_SPI_EN_MSK                          (((1U << SDH_SPI_EN_LEN) - 1) << SDH_SPI_EN_POS)
#define SDH_SPI_EN_UMSK                         (~(((1U << SDH_SPI_EN_LEN) - 1) << SDH_SPI_EN_POS))
#define SDH_SPI_ERR_TOKEN                       SDH_SPI_ERR_TOKEN
#define SDH_SPI_ERR_TOKEN_POS                   (8U)
#define SDH_SPI_ERR_TOKEN_LEN                   (5U)
#define SDH_SPI_ERR_TOKEN_MSK                   (((1U << SDH_SPI_ERR_TOKEN_LEN) - 1) << SDH_SPI_ERR_TOKEN_POS)
#define SDH_SPI_ERR_TOKEN_UMSK                  (~(((1U << SDH_SPI_ERR_TOKEN_LEN) - 1) << SDH_SPI_ERR_TOKEN_POS))

/* 0x10a : Clock and Burst Size Setup Register */
#define SDH_BRST_SIZE                           SDH_BRST_SIZE
#define SDH_BRST_SIZE_POS                       (0U)
#define SDH_BRST_SIZE_LEN                       (2U)
#define SDH_BRST_SIZE_MSK                       (((1U << SDH_BRST_SIZE_LEN) - 1) << SDH_BRST_SIZE_POS)
#define SDH_BRST_SIZE_UMSK                      (~(((1U << SDH_BRST_SIZE_LEN) - 1) << SDH_BRST_SIZE_POS))
#define SDH_DMA_SIZE                            SDH_DMA_SIZE
#define SDH_DMA_SIZE_POS                        (2U)
#define SDH_DMA_SIZE_LEN                        (2U)
#define SDH_DMA_SIZE_MSK                        (((1U << SDH_DMA_SIZE_LEN) - 1) << SDH_DMA_SIZE_POS)
#define SDH_DMA_SIZE_UMSK                       (~(((1U << SDH_DMA_SIZE_LEN) - 1) << SDH_DMA_SIZE_POS))
#define SDH_PRIORITY                            SDH_PRIORITY
#define SDH_PRIORITY_POS                        (4U)
#define SDH_PRIORITY_LEN                        (1U)
#define SDH_PRIORITY_MSK                        (((1U << SDH_PRIORITY_LEN) - 1) << SDH_PRIORITY_POS)
#define SDH_PRIORITY_UMSK                       (~(((1U << SDH_PRIORITY_LEN) - 1) << SDH_PRIORITY_POS))
#define SDH_AXI_NON_POST_WR                     SDH_AXI_NON_POST_WR
#define SDH_AXI_NON_POST_WR_POS                 (5U)
#define SDH_AXI_NON_POST_WR_LEN                 (1U)
#define SDH_AXI_NON_POST_WR_MSK                 (((1U << SDH_AXI_NON_POST_WR_LEN) - 1) << SDH_AXI_NON_POST_WR_POS)
#define SDH_AXI_NON_POST_WR_UMSK                (~(((1U << SDH_AXI_NON_POST_WR_LEN) - 1) << SDH_AXI_NON_POST_WR_POS))
#define SDH_RD_ENDIAN                           SDH_RD_ENDIAN
#define SDH_RD_ENDIAN_POS                       (6U)
#define SDH_RD_ENDIAN_LEN                       (1U)
#define SDH_RD_ENDIAN_MSK                       (((1U << SDH_RD_ENDIAN_LEN) - 1) << SDH_RD_ENDIAN_POS)
#define SDH_RD_ENDIAN_UMSK                      (~(((1U << SDH_RD_ENDIAN_LEN) - 1) << SDH_RD_ENDIAN_POS))
#define SDH_WR_ENDIAN                           SDH_WR_ENDIAN
#define SDH_WR_ENDIAN_POS                       (7U)
#define SDH_WR_ENDIAN_LEN                       (1U)
#define SDH_WR_ENDIAN_MSK                       (((1U << SDH_WR_ENDIAN_LEN) - 1) << SDH_WR_ENDIAN_POS)
#define SDH_WR_ENDIAN_UMSK                      (~(((1U << SDH_WR_ENDIAN_LEN) - 1) << SDH_WR_ENDIAN_POS))
#define SDH_RD_OSTDG                            SDH_RD_OSTDG
#define SDH_RD_OSTDG_POS                        (14U)
#define SDH_RD_OSTDG_LEN                        (1U)
#define SDH_RD_OSTDG_MSK                        (((1U << SDH_RD_OSTDG_LEN) - 1) << SDH_RD_OSTDG_POS)
#define SDH_RD_OSTDG_UMSK                       (~(((1U << SDH_RD_OSTDG_LEN) - 1) << SDH_RD_OSTDG_POS))
#define SDH_WR_OSTDG                            SDH_WR_OSTDG
#define SDH_WR_OSTDG_POS                        (15U)
#define SDH_WR_OSTDG_LEN                        (1U)
#define SDH_WR_OSTDG_MSK                        (((1U << SDH_WR_OSTDG_LEN) - 1) << SDH_WR_OSTDG_POS)
#define SDH_WR_OSTDG_UMSK                       (~(((1U << SDH_WR_OSTDG_LEN) - 1) << SDH_WR_OSTDG_POS))

/* 0x10c : CE-ATA Register 1 */
#define SDH_CPL_TIMEOUT                         SDH_CPL_TIMEOUT
#define SDH_CPL_TIMEOUT_POS                     (0U)
#define SDH_CPL_TIMEOUT_LEN                     (14U)
#define SDH_CPL_TIMEOUT_MSK                     (((1U << SDH_CPL_TIMEOUT_LEN) - 1) << SDH_CPL_TIMEOUT_POS)
#define SDH_CPL_TIMEOUT_UMSK                    (~(((1U << SDH_CPL_TIMEOUT_LEN) - 1) << SDH_CPL_TIMEOUT_POS))

/* 0x10e : CE-ATA Register 2 */
#define SDH_MISC_INT_INT_EN                     SDH_MISC_INT_INT_EN
#define SDH_MISC_INT_INT_EN_POS                 (0U)
#define SDH_MISC_INT_INT_EN_LEN                 (1U)
#define SDH_MISC_INT_INT_EN_MSK                 (((1U << SDH_MISC_INT_INT_EN_LEN) - 1) << SDH_MISC_INT_INT_EN_POS)
#define SDH_MISC_INT_INT_EN_UMSK                (~(((1U << SDH_MISC_INT_INT_EN_LEN) - 1) << SDH_MISC_INT_INT_EN_POS))
#define SDH_MISC_INT_EN                         SDH_MISC_INT_EN
#define SDH_MISC_INT_EN_POS                     (1U)
#define SDH_MISC_INT_EN_LEN                     (1U)
#define SDH_MISC_INT_EN_MSK                     (((1U << SDH_MISC_INT_EN_LEN) - 1) << SDH_MISC_INT_EN_POS)
#define SDH_MISC_INT_EN_UMSK                    (~(((1U << SDH_MISC_INT_EN_LEN) - 1) << SDH_MISC_INT_EN_POS))
#define SDH_MISC_INT                            SDH_MISC_INT
#define SDH_MISC_INT_POS                        (2U)
#define SDH_MISC_INT_LEN                        (1U)
#define SDH_MISC_INT_MSK                        (((1U << SDH_MISC_INT_LEN) - 1) << SDH_MISC_INT_POS)
#define SDH_MISC_INT_UMSK                       (~(((1U << SDH_MISC_INT_LEN) - 1) << SDH_MISC_INT_POS))
#define SDH_CPL_COMPLETE_INT_EN                 SDH_CPL_COMPLETE_INT_EN
#define SDH_CPL_COMPLETE_INT_EN_POS             (4U)
#define SDH_CPL_COMPLETE_INT_EN_LEN             (1U)
#define SDH_CPL_COMPLETE_INT_EN_MSK             (((1U << SDH_CPL_COMPLETE_INT_EN_LEN) - 1) << SDH_CPL_COMPLETE_INT_EN_POS)
#define SDH_CPL_COMPLETE_INT_EN_UMSK            (~(((1U << SDH_CPL_COMPLETE_INT_EN_LEN) - 1) << SDH_CPL_COMPLETE_INT_EN_POS))
#define SDH_CPL_COMPLETE_EN                     SDH_CPL_COMPLETE_EN
#define SDH_CPL_COMPLETE_EN_POS                 (5U)
#define SDH_CPL_COMPLETE_EN_LEN                 (1U)
#define SDH_CPL_COMPLETE_EN_MSK                 (((1U << SDH_CPL_COMPLETE_EN_LEN) - 1) << SDH_CPL_COMPLETE_EN_POS)
#define SDH_CPL_COMPLETE_EN_UMSK                (~(((1U << SDH_CPL_COMPLETE_EN_LEN) - 1) << SDH_CPL_COMPLETE_EN_POS))
#define SDH_CPL_COMPLETE                        SDH_CPL_COMPLETE
#define SDH_CPL_COMPLETE_POS                    (6U)
#define SDH_CPL_COMPLETE_LEN                    (1U)
#define SDH_CPL_COMPLETE_MSK                    (((1U << SDH_CPL_COMPLETE_LEN) - 1) << SDH_CPL_COMPLETE_POS)
#define SDH_CPL_COMPLETE_UMSK                   (~(((1U << SDH_CPL_COMPLETE_LEN) - 1) << SDH_CPL_COMPLETE_POS))
#define SDH_MMC_RESETN                          SDH_MMC_RESETN
#define SDH_MMC_RESETN_POS                      (11U)
#define SDH_MMC_RESETN_LEN                      (1U)
#define SDH_MMC_RESETN_MSK                      (((1U << SDH_MMC_RESETN_LEN) - 1) << SDH_MMC_RESETN_POS)
#define SDH_MMC_RESETN_UMSK                     (~(((1U << SDH_MMC_RESETN_LEN) - 1) << SDH_MMC_RESETN_POS))
#define SDH_MMC_CARD                            SDH_MMC_CARD
#define SDH_MMC_CARD_POS                        (12U)
#define SDH_MMC_CARD_LEN                        (1U)
#define SDH_MMC_CARD_MSK                        (((1U << SDH_MMC_CARD_LEN) - 1) << SDH_MMC_CARD_POS)
#define SDH_MMC_CARD_UMSK                       (~(((1U << SDH_MMC_CARD_LEN) - 1) << SDH_MMC_CARD_POS))
#define SDH_CEATA_CARD                          SDH_CEATA_CARD
#define SDH_CEATA_CARD_POS                      (13U)
#define SDH_CEATA_CARD_LEN                      (1U)
#define SDH_CEATA_CARD_MSK                      (((1U << SDH_CEATA_CARD_LEN) - 1) << SDH_CEATA_CARD_POS)
#define SDH_CEATA_CARD_UMSK                     (~(((1U << SDH_CEATA_CARD_LEN) - 1) << SDH_CEATA_CARD_POS))
#define SDH_SND_CPL                             SDH_SND_CPL
#define SDH_SND_CPL_POS                         (14U)
#define SDH_SND_CPL_LEN                         (1U)
#define SDH_SND_CPL_MSK                         (((1U << SDH_SND_CPL_LEN) - 1) << SDH_SND_CPL_POS)
#define SDH_SND_CPL_UMSK                        (~(((1U << SDH_SND_CPL_LEN) - 1) << SDH_SND_CPL_POS))
#define SDH_CHK_CPL                             SDH_CHK_CPL
#define SDH_CHK_CPL_POS                         (15U)
#define SDH_CHK_CPL_LEN                         (1U)
#define SDH_CHK_CPL_MSK                         (((1U << SDH_CHK_CPL_LEN) - 1) << SDH_CHK_CPL_POS)
#define SDH_CHK_CPL_UMSK                        (~(((1U << SDH_CHK_CPL_LEN) - 1) << SDH_CHK_CPL_POS))

/* 0x110 : PAD I/O Setup Register */
#define SDH_ASYNC_IO_EN                         SDH_ASYNC_IO_EN
#define SDH_ASYNC_IO_EN_POS                     (0U)
#define SDH_ASYNC_IO_EN_LEN                     (1U)
#define SDH_ASYNC_IO_EN_MSK                     (((1U << SDH_ASYNC_IO_EN_LEN) - 1) << SDH_ASYNC_IO_EN_POS)
#define SDH_ASYNC_IO_EN_UMSK                    (~(((1U << SDH_ASYNC_IO_EN_LEN) - 1) << SDH_ASYNC_IO_EN_POS))
#define SDH_INAND_SEL                           SDH_INAND_SEL
#define SDH_INAND_SEL_POS                       (1U)
#define SDH_INAND_SEL_LEN                       (1U)
#define SDH_INAND_SEL_MSK                       (((1U << SDH_INAND_SEL_LEN) - 1) << SDH_INAND_SEL_POS)
#define SDH_INAND_SEL_UMSK                      (~(((1U << SDH_INAND_SEL_LEN) - 1) << SDH_INAND_SEL_POS))
#define SDH_ECO_REG                             SDH_ECO_REG
#define SDH_ECO_REG_POS                         (16U)
#define SDH_ECO_REG_LEN                         (8U)
#define SDH_ECO_REG_MSK                         (((1U << SDH_ECO_REG_LEN) - 1) << SDH_ECO_REG_POS)
#define SDH_ECO_REG_UMSK                        (~(((1U << SDH_ECO_REG_LEN) - 1) << SDH_ECO_REG_POS))

/* 0x114 : RX Configuration Register */
#define SDH_SDCLK_SEL0                          SDH_SDCLK_SEL0
#define SDH_SDCLK_SEL0_POS                      (0U)
#define SDH_SDCLK_SEL0_LEN                      (2U)
#define SDH_SDCLK_SEL0_MSK                      (((1U << SDH_SDCLK_SEL0_LEN) - 1) << SDH_SDCLK_SEL0_POS)
#define SDH_SDCLK_SEL0_UMSK                     (~(((1U << SDH_SDCLK_SEL0_LEN) - 1) << SDH_SDCLK_SEL0_POS))
#define SDH_SDCLK_SEL1                          SDH_SDCLK_SEL1
#define SDH_SDCLK_SEL1_POS                      (2U)
#define SDH_SDCLK_SEL1_LEN                      (2U)
#define SDH_SDCLK_SEL1_MSK                      (((1U << SDH_SDCLK_SEL1_LEN) - 1) << SDH_SDCLK_SEL1_POS)
#define SDH_SDCLK_SEL1_UMSK                     (~(((1U << SDH_SDCLK_SEL1_LEN) - 1) << SDH_SDCLK_SEL1_POS))
#define SDH_SDCLK_DELAY                         SDH_SDCLK_DELAY
#define SDH_SDCLK_DELAY_POS                     (8U)
#define SDH_SDCLK_DELAY_LEN                     (10U)
#define SDH_SDCLK_DELAY_MSK                     (((1U << SDH_SDCLK_DELAY_LEN) - 1) << SDH_SDCLK_DELAY_POS)
#define SDH_SDCLK_DELAY_UMSK                    (~(((1U << SDH_SDCLK_DELAY_LEN) - 1) << SDH_SDCLK_DELAY_POS))
#define SDH_TUNING_DLY_INC                      SDH_TUNING_DLY_INC
#define SDH_TUNING_DLY_INC_POS                  (18U)
#define SDH_TUNING_DLY_INC_LEN                  (10U)
#define SDH_TUNING_DLY_INC_MSK                  (((1U << SDH_TUNING_DLY_INC_LEN) - 1) << SDH_TUNING_DLY_INC_POS)
#define SDH_TUNING_DLY_INC_UMSK                 (~(((1U << SDH_TUNING_DLY_INC_LEN) - 1) << SDH_TUNING_DLY_INC_POS))

/* 0x118 : TX Configuration Register */
#define SDH_TX_HOLD_DELAY0                      SDH_TX_HOLD_DELAY0
#define SDH_TX_HOLD_DELAY0_POS                  (0U)
#define SDH_TX_HOLD_DELAY0_LEN                  (10U)
#define SDH_TX_HOLD_DELAY0_MSK                  (((1U << SDH_TX_HOLD_DELAY0_LEN) - 1) << SDH_TX_HOLD_DELAY0_POS)
#define SDH_TX_HOLD_DELAY0_UMSK                 (~(((1U << SDH_TX_HOLD_DELAY0_LEN) - 1) << SDH_TX_HOLD_DELAY0_POS))
#define SDH_TX_HOLD_DELAY1                      SDH_TX_HOLD_DELAY1
#define SDH_TX_HOLD_DELAY1_POS                  (16U)
#define SDH_TX_HOLD_DELAY1_LEN                  (10U)
#define SDH_TX_HOLD_DELAY1_MSK                  (((1U << SDH_TX_HOLD_DELAY1_LEN) - 1) << SDH_TX_HOLD_DELAY1_POS)
#define SDH_TX_HOLD_DELAY1_UMSK                 (~(((1U << SDH_TX_HOLD_DELAY1_LEN) - 1) << SDH_TX_HOLD_DELAY1_POS))
#define SDH_TX_INT_CLK_SEL                      SDH_TX_INT_CLK_SEL
#define SDH_TX_INT_CLK_SEL_POS                  (30U)
#define SDH_TX_INT_CLK_SEL_LEN                  (1U)
#define SDH_TX_INT_CLK_SEL_MSK                  (((1U << SDH_TX_INT_CLK_SEL_LEN) - 1) << SDH_TX_INT_CLK_SEL_POS)
#define SDH_TX_INT_CLK_SEL_UMSK                 (~(((1U << SDH_TX_INT_CLK_SEL_LEN) - 1) << SDH_TX_INT_CLK_SEL_POS))
#define SDH_TX_MUX_SEL                          SDH_TX_MUX_SEL
#define SDH_TX_MUX_SEL_POS                      (31U)
#define SDH_TX_MUX_SEL_LEN                      (1U)
#define SDH_TX_MUX_SEL_MSK                      (((1U << SDH_TX_MUX_SEL_LEN) - 1) << SDH_TX_MUX_SEL_POS)
#define SDH_TX_MUX_SEL_UMSK                     (~(((1U << SDH_TX_MUX_SEL_LEN) - 1) << SDH_TX_MUX_SEL_POS))

/* 0x11c : TUNING CONFIG Register */
#define SDH_TUNING_TT_CNT                       SDH_TUNING_TT_CNT
#define SDH_TUNING_TT_CNT_POS                   (0U)
#define SDH_TUNING_TT_CNT_LEN                   (8U)
#define SDH_TUNING_TT_CNT_MSK                   (((1U << SDH_TUNING_TT_CNT_LEN) - 1) << SDH_TUNING_TT_CNT_POS)
#define SDH_TUNING_TT_CNT_UMSK                  (~(((1U << SDH_TUNING_TT_CNT_LEN) - 1) << SDH_TUNING_TT_CNT_POS))
#define SDH_TUNING_WD_CNT                       SDH_TUNING_WD_CNT
#define SDH_TUNING_WD_CNT_POS                   (8U)
#define SDH_TUNING_WD_CNT_LEN                   (6U)
#define SDH_TUNING_WD_CNT_MSK                   (((1U << SDH_TUNING_WD_CNT_LEN) - 1) << SDH_TUNING_WD_CNT_POS)
#define SDH_TUNING_WD_CNT_UMSK                  (~(((1U << SDH_TUNING_WD_CNT_LEN) - 1) << SDH_TUNING_WD_CNT_POS))
#define SDH_TUNING_CLK_DLY                      SDH_TUNING_CLK_DLY
#define SDH_TUNING_CLK_DLY_POS                  (14U)
#define SDH_TUNING_CLK_DLY_LEN                  (10U)
#define SDH_TUNING_CLK_DLY_MSK                  (((1U << SDH_TUNING_CLK_DLY_LEN) - 1) << SDH_TUNING_CLK_DLY_POS)
#define SDH_TUNING_CLK_DLY_UMSK                 (~(((1U << SDH_TUNING_CLK_DLY_LEN) - 1) << SDH_TUNING_CLK_DLY_POS))
#define SDH_TUNING_SUCCESS_CNT                  SDH_TUNING_SUCCESS_CNT
#define SDH_TUNING_SUCCESS_CNT_POS              (24U)
#define SDH_TUNING_SUCCESS_CNT_LEN              (6U)
#define SDH_TUNING_SUCCESS_CNT_MSK              (((1U << SDH_TUNING_SUCCESS_CNT_LEN) - 1) << SDH_TUNING_SUCCESS_CNT_POS)
#define SDH_TUNING_SUCCESS_CNT_UMSK             (~(((1U << SDH_TUNING_SUCCESS_CNT_LEN) - 1) << SDH_TUNING_SUCCESS_CNT_POS))

#endif

#endif /* __SDH_REG_H__ */
