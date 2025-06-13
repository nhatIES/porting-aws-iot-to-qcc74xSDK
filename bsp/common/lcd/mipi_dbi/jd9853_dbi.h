#ifndef _JD9853_DBI_H_
#define _JD9853_DBI_H_

#include "../lcd_conf.h"

#if defined LCD_DBI_JD9853

/* Do not modify the following */

#if (JD9853_DBI_PIXEL_FORMAT == 1)
#define JD9853_DBI_COLOR_DEPTH 16
typedef uint16_t jd9853_dbi_color_t;
#elif (JD9853_DBI_PIXEL_FORMAT == 2)
#define JD9853_DBI_COLOR_DEPTH 32
typedef uint32_t jd9853_dbi_color_t;
#endif

typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} jd9853_dbi_init_cmd_t;

int jd9853_dbi_init();
void jd9853_dbi_async_callback_enable(bool enable);
void jd9853_dbi_async_callback_register(void (*callback)(void));
int jd9853_dbi_set_dir(uint8_t dir, uint8_t mir_flag);
void jd9853_dbi_set_draw_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void jd9853_dbi_draw_point(uint16_t x, uint16_t y, jd9853_dbi_color_t color);
void jd9853_dbi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, jd9853_dbi_color_t color);
void jd9853_dbi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, jd9853_dbi_color_t *picture);
void jd9853_dbi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, jd9853_dbi_color_t *picture);
int jd9853_dbi_draw_is_busy(void);

#endif
#endif
