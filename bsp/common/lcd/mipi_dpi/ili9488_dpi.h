#ifndef _ILI9488_DPI_H_
#define _ILI9488_DPI_H_

#include "../lcd_conf.h"

/* Do not modify the following information */

#if defined LCD_DPI_ILI9488

#if (ILI9488_DPI_PIXEL_FORMAT == 1)
#define ILI9488_DPI_COLOR_DEPTH 16
typedef uint16_t ili9488_dpi_color_t;
#elif (ILI9488_DPI_PIXEL_FORMAT == 2)
#define ILI9488_DPI_COLOR_DEPTH 32
typedef uint32_t ili9488_dpi_color_t;
#else
#error "ILI9488 pixel format select error"
#endif

/* Ili9488 needs to be initialized using the DBI(typeC) or SPI interface */
typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} ili9488_dpi_init_cmd_t;

int ili9488_dpi_init(ili9488_dpi_color_t *screen_buffer);
int ili9488_dpi_screen_switch(ili9488_dpi_color_t *screen_buffer);
ili9488_dpi_color_t *ili9488_dpi_get_screen_using(void);
int ili9488_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void));

#endif
#endif
