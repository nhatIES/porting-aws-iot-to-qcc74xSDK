#include "qcc74x_core.h"
#include "qcc743_memorymap.h"
#include "qcc743_irq.h"

#define DMA_CHANNEL_OFFSET 0x100

struct qcc74x_device_s qcc743_device_table[] = {
    { .name = QCC74x_NAME_ADC0,
      .reg_base = AON_BASE,
      .irq_num = QCC743_IRQ_GPADC_DMA,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_ADC,
      .user_data = NULL },
    { .name = QCC74x_NAME_DAC0,
      .reg_base = GLB_BASE,
      .irq_num = 0xff,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_DAC,
      .user_data = NULL },
    { .name = QCC74x_NAME_EF_CTRL,
      .reg_base = EF_CTRL_BASE,
      .irq_num = 0xff,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_EF_CTRL,
      .user_data = NULL },
    { .name = QCC74x_NAME_GPIO,
      .reg_base = GLB_BASE,
      .irq_num = QCC743_IRQ_GPIO_INT0,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_GPIO,
      .user_data = NULL },
    { .name = QCC74x_NAME_UART0,
      .reg_base = UART0_BASE,
      .irq_num = QCC743_IRQ_UART0,
      .idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_UART,
      .user_data = NULL },
    { .name = QCC74x_NAME_UART1,
      .reg_base = UART1_BASE,
      .irq_num = QCC743_IRQ_UART1,
      .idx = 1,
      .dev_type = QCC74x_DEVICE_TYPE_UART,
      .user_data = NULL },
    { .name = QCC74x_NAME_SPI0,
      .reg_base = SPI_BASE,
      .irq_num = QCC743_IRQ_SPI0,
      .idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_SPI,
      .user_data = NULL },
    { .name = QCC74x_NAME_PWM_V2_PWM0,
      .reg_base = PWM_BASE,
      .irq_num = QCC743_IRQ_PWM,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_PWM,
      .user_data = NULL },
    { .name = QCC74x_NAME_DMA0_CH0,
      .reg_base = DMA_BASE + 1 * DMA_CHANNEL_OFFSET,
      .irq_num = QCC743_IRQ_DMA0_ALL,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_DMA,
      .user_data = NULL },
    { .name = QCC74x_NAME_DMA0_CH1,
      .reg_base = DMA_BASE + 2 * DMA_CHANNEL_OFFSET,
      .irq_num = QCC743_IRQ_DMA0_ALL,
      .idx = 0,
      .sub_idx = 1,
      .dev_type = QCC74x_DEVICE_TYPE_DMA,
      .user_data = NULL },
    { .name = QCC74x_NAME_DMA0_CH2,
      .reg_base = DMA_BASE + 3 * DMA_CHANNEL_OFFSET,
      .irq_num = QCC743_IRQ_DMA0_ALL,
      .idx = 0,
      .sub_idx = 2,
      .dev_type = QCC74x_DEVICE_TYPE_DMA,
      .user_data = NULL },
    { .name = QCC74x_NAME_DMA0_CH3,
      .reg_base = DMA_BASE + 4 * DMA_CHANNEL_OFFSET,
      .irq_num = QCC743_IRQ_DMA0_ALL,
      .idx = 0,
      .sub_idx = 3,
      .dev_type = QCC74x_DEVICE_TYPE_DMA,
      .user_data = NULL },
    { .name = QCC74x_NAME_I2C0,
      .reg_base = I2C0_BASE,
      .irq_num = QCC743_IRQ_I2C0,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_I2C,
      .user_data = NULL },
    { .name = QCC74x_NAME_I2C1,
      .reg_base = I2C1_BASE,
      .irq_num = QCC743_IRQ_I2C1,
      .idx = 1,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_I2C,
      .user_data = NULL },
    { .name = QCC74x_NAME_I2S0,
      .reg_base = I2S_BASE,
      .irq_num = QCC743_IRQ_I2S,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_I2S,
      .user_data = NULL },
    { .name = QCC74x_NAME_TIMER0,
      .reg_base = TIMER_BASE,
      .irq_num = QCC743_IRQ_TIMER0,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_TIMER,
      .user_data = NULL },
    { .name = QCC74x_NAME_TIMER1,
      .reg_base = TIMER_BASE,
      .irq_num = QCC743_IRQ_TIMER1,
      .idx = 1,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_TIMER,
      .user_data = NULL },
    { .name = QCC74x_NAME_RTC,
      .reg_base = HBN_BASE,
      .irq_num = QCC743_IRQ_HBN_OUT0,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_RTC,
      .user_data = NULL },
    { .name = QCC74x_NAME_AES,
      .reg_base = SEC_ENG_BASE,
      .irq_num = 0xff,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_AES,
      .user_data = NULL },
    { .name = QCC74x_NAME_SHA,
      .reg_base = SEC_ENG_BASE,
      .irq_num = 0xff,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_SHA,
      .user_data = NULL },
    { .name = QCC74x_NAME_TRNG,
      .reg_base = SEC_ENG_BASE,
      .irq_num = 0xff,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_TRNG,
      .user_data = NULL },
    { .name = QCC74x_NAME_PKA,
      .reg_base = SEC_ENG_BASE,
      .irq_num = 0xff,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_PKA,
      .user_data = NULL },
    { .name = QCC74x_NAME_EMAC0,
      .reg_base = EMAC_BASE,
      .irq_num = QCC743_IRQ_EMAC,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_ETH,
      .user_data = NULL },
    { .name = QCC74x_NAME_WDT,
      .reg_base = TIMER_BASE,
      .irq_num = QCC743_IRQ_WDG,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_TIMER,
      .user_data = NULL },
    { .name = QCC74x_NAME_CKS,
      .reg_base = CKS_BASE,
      .irq_num = 0,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_CKS,
      .user_data = NULL },
    { .name = QCC74x_NAME_MJPEG,
      .reg_base = MJPEG_BASE,
      .irq_num = QCC743_IRQ_MJPEG,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_MJPEG,
      .user_data = NULL },
    { .name = QCC74x_NAME_IRRX,
      .reg_base = IR_BASE,
      .irq_num = QCC743_IRQ_IRRX,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_IR,
      .user_data = NULL },
    { .name = QCC74x_NAME_CAM0,
      .reg_base = DVP2AXI0_BASE,
      .irq_num = QCC743_IRQ_DVP2BUS_INT0,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_CAMERA,
      .user_data = NULL },
    { .name = QCC74x_NAME_CAM1,
      .reg_base = DVP2AXI1_BASE,
      .irq_num = QCC743_IRQ_DVP2BUS_INT1,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_CAMERA,
      .user_data = NULL },
    { .name = QCC74x_NAME_AUADC,
      .reg_base = AUADC_BASE,
      .irq_num = QCC743_IRQ_AUADC,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_AUDIOADC,
      .user_data = NULL },
    { .name = QCC74x_NAME_AUDAC,
      .reg_base = AUDAC_BASE,
      .irq_num = QCC743_IRQ_AUDAC,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_AUDIODAC,
      .user_data = NULL },
    { .name = QCC74x_NAME_SDIO2,
      .reg_base = SDU_BASE,
      .irq_num = QCC743_IRQ_SDIO,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_SDIO2,
      .user_data = NULL },
    { .name = QCC74x_NAME_SDH,
      .reg_base = SDH_BASE,
      .irq_num = QCC743_IRQ_SDH,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_SDH,
      .user_data = NULL },
    { .name = QCC74x_NAME_DBI,
      .reg_base = DBI_BASE,
      .irq_num = QCC743_IRQ_DBI,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_DBI,
      .user_data = NULL },
    { .name = "plfm_dma_ch0",
      .reg_base = PLFM_DMA_BASE,
      .irq_num = 0,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_PLFMDMA,
      .user_data = NULL },
    { .name = "plfm_dma_ch1",
      .reg_base = PLFM_DMA_BASE,
      .irq_num = 0,
      .idx = 1,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_PLFMDMA,
      .user_data = NULL },
    { .name = "plfm_dma_ch2",
      .reg_base = PLFM_DMA_BASE,
      .irq_num = 0,
      .idx = 2,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_PLFMDMA,
      .user_data = NULL },
    { .name = "plfm_dma_ch3",
      .reg_base = PLFM_DMA_BASE,
      .irq_num = 0,
      .idx = 3,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_PLFMDMA,
      .user_data = NULL },
    { .name = "plfm_dma_ch4",
      .reg_base = PLFM_DMA_BASE,
      .irq_num = 0,
      .idx = 4,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_PLFMDMA,
      .user_data = NULL },
    { .name = QCC74x_NAME_WO,
      .reg_base = GLB_BASE,
      .irq_num = QCC743_IRQ_GPIO_DMA,
      .idx = 0,
      .sub_idx = 0,
      .dev_type = QCC74x_DEVICE_TYPE_WO,
      .user_data = NULL },
};

struct qcc74x_device_s *qcc74x_device_get_by_name(const char *name)
{
    for (uint8_t i = 0; i < sizeof(qcc743_device_table) / sizeof(qcc743_device_table[0]); i++) {
        if (strcmp(qcc743_device_table[i].name, name) == 0) {
            return &qcc743_device_table[i];
        }
    }
    LHAL_PARAM_ASSERT(0);
    return NULL;
}

void qcc74x_device_set_userdata(struct qcc74x_device_s *device, void *user_data)
{
    device->user_data = user_data;
}