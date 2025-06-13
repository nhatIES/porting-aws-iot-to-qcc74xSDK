#include "../lcd.h"

#if (defined(LCD_DPI_INIT_INTERFACE_TYPE) && (LCD_DPI_INIT_INTERFACE_TYPE == 1))

#include "qcc74x_mtimer.h"
#include "qcc74x_gpio.h"
#include "qcc74x_dpi_init_spi_soft_3.h"

#define SPI3_CS_PIN   LCD_DPI_INIT_SPI_SOFT_3_PIN_CS
#define SPI3_CLK_PIN  LCD_DPI_INIT_SPI_SOFT_3_PIN_CLK
#define SPI3_MOSI_PIN LCD_DPI_INIT_SPI_SOFT_3_PIN_DAT

#ifndef LCD_DPI_INIT_SPI_SOFT_3_DELAY
#define SPI3_DELAY 10
#else
#define SPI3_DELAY LCD_DPI_INIT_SPI_SOFT_3_DELAY
#endif

static struct qcc74x_device_s *spi3_gpio = NULL;

static void spi_sig_io_out(uint8_t sig_pin, bool output)
{
    if (output) {
        qcc74x_gpio_set(spi3_gpio, sig_pin);
    } else {
        qcc74x_gpio_reset(spi3_gpio, sig_pin);
    }
}

static void spi_sig_delay(void)
{
    for (int i = 0; i < SPI3_DELAY; i++) {
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
    }
}

int lcd_dpi_init_spi_soft_3_init(void)
{
    spi3_gpio = qcc74x_device_get_by_name("gpio");

    qcc74x_gpio_init(spi3_gpio, SPI3_CS_PIN, GPIO_OUTPUT | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    qcc74x_gpio_init(spi3_gpio, SPI3_CLK_PIN, GPIO_OUTPUT | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);
    qcc74x_gpio_init(spi3_gpio, SPI3_MOSI_PIN, GPIO_OUTPUT | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_2);

    spi_sig_io_out(SPI3_CS_PIN, 1);
    spi_sig_io_out(SPI3_CLK_PIN, 1);
    spi_sig_io_out(SPI3_MOSI_PIN, 1);

    return 0;
}

int lcd_dpi_init_spi_soft_3_transmit_cmd_para(uint8_t cmd, uint8_t *para, size_t para_num)
{
    uint8_t byte;

    spi_sig_io_out(SPI3_CS_PIN, 0);

    for (size_t i = 0; i < (1 + para_num); i++) {
        /* cmd/data mode */
        spi_sig_io_out(SPI3_CLK_PIN, 0);
        if (i == 0) {
            byte = cmd;
            spi_sig_io_out(SPI3_MOSI_PIN, 0); /* cmd mode */
        } else {
            byte = para[i - 1];
            spi_sig_io_out(SPI3_MOSI_PIN, 1); /* data mode */
        }
        spi_sig_delay();
        spi_sig_io_out(SPI3_CLK_PIN, 1);
        spi_sig_delay();

        /* */
        for (uint8_t j = 0; j < 8; j++) {
            spi_sig_io_out(SPI3_CLK_PIN, 0);
            spi_sig_io_out(SPI3_MOSI_PIN, (bool)(byte & 0x80));
            spi_sig_delay();
            spi_sig_io_out(SPI3_CLK_PIN, 1);
            spi_sig_delay();

            byte <<= 1;
        }
    }

    spi_sig_io_out(SPI3_CS_PIN, 1);
    spi_sig_io_out(SPI3_CLK_PIN, 1);
    spi_sig_io_out(SPI3_MOSI_PIN, 1);
    return 0;
}

#endif
