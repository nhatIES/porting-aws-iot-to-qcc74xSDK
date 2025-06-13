#include "qcc74x_mtimer.h"
#include "qcc74x_timer.h"
#include "qcc74x_gpio.h"
#include "qcc74x_pwm_v2.h"
#include "qcc74x_clock.h"
#include "board.h"

#define PWM_CHANNEL_SELECT PWM_CH0

struct qcc74x_device_s *timer0;
struct qcc74x_device_s *gpio;

static void pwm_init()
{
    struct qcc74x_device_s *pwm0;

    pwm0 = qcc74x_device_get_by_name("pwm_v2_0");
    /* period = .XCLK / .clk_div / .period = 40MHz / 2 / 10 = 2MHz */
    struct qcc74x_pwm_v2_config_s cfg = {
        .clk_source = QCC74x_SYSTEM_XCLK,
        .clk_div = 2,
        .period = 10,
    };
    /* init pwm */
    qcc74x_pwm_v2_init(pwm0, &cfg);
    qcc74x_pwm_v2_channel_set_threshold(pwm0, PWM_CHANNEL_SELECT, 1, 5); /* duty = (5-1)/10 = 40% */
    qcc74x_pwm_v2_channel_positive_start(pwm0, PWM_CHANNEL_SELECT);
    qcc74x_pwm_v2_start(pwm0);
}

int main(void)
{
    uint32_t i;
    uint32_t cnt = 0;
    
    board_init();
    board_pwm_gpio_init();
    board_timer_gpio_init();

    printf("Timer GPIO as clock source case\n");
    pwm_init();

    struct qcc74x_timer_config_s cfg;
    cfg.counter_mode = TIMER_COUNTER_MODE_UP;
    cfg.clock_source = TIMER_CLKSRC_GPIO;
    cfg.clock_div = 0;
    cfg.trigger_comp_id = TIMER_COMP_ID_2;
    cfg.comp0_val = 0xFFFFFFFF;
    cfg.comp1_val = 0xFFFFFFFF;
    cfg.comp2_val = 0xFFFFFFFF;
    cfg.preload_val = 0;

    timer0 = qcc74x_device_get_by_name("timer0");

    /* Timer init with default configuration */
    qcc74x_timer_init(timer0, &cfg);

    /* Enable timer and get count */
    for(i = 0; i < 10; i++){
        qcc74x_timer_start(timer0);
        qcc74x_mtimer_delay_ms(2);
        cnt = qcc74x_timer_get_countervalue(timer0);
        qcc74x_timer_stop(timer0);
        printf("delay 2ms, Test %lu times, timer count value: %lu\r\n", i, cnt);
    }

    printf("case success.\r\n");
    while (1) {
        qcc74x_mtimer_delay_ms(1500);
    }
}
