#ifndef _QCC74x_DPI_INIT_SPI_SOFT_3_H
#define _QCC74x_DPI_INIT_SPI_SOFT_3_H

#include "../lcd_conf.h"

#if (defined(LCD_DPI_INIT_INTERFACE_TYPE) && (LCD_DPI_INIT_INTERFACE_TYPE == 1))

int lcd_dpi_init_spi_soft_3_init(void);

int lcd_dpi_init_spi_soft_3_transmit_cmd_para(uint8_t cmd, uint8_t *para, size_t para_num);

#endif
#endif
