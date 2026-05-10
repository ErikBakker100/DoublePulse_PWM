#include "../include/BCM2711.h"
#include "include/timers_BCM2711.h"
#include "../../include/timers.h"
#include "../../include/gpio.h"

void bcm2711_timer_callback(void *data) {
    // Doe hier je timer-acties (toggle GPIO, etc.)
    timer->clear(1);                        // Clear timer hardware flag
    gpio->toggle(STATUS_PIN);               // Toggle GPIO for heart beat indication
    timer->set(1, BLINK_TIMER);
}

bool bcm2711_timer_set(uint8_t timer, uint32_t time) {
    return timer_set(SYS_TMR_2711, timer, time);
}

bool bcm2711_timer_expired(uint8_t timer) {
    return timer_expired(SYS_TMR_2711, timer);
}

void bcm2711_timer_clear(uint8_t timer) {
    timer_clear(SYS_TMR_2711, timer);
}

const timers_ops_t bcm2711_timers_ops = {
    .set        = bcm2711_timer_set,
    .expired    = bcm2711_timer_expired,
    .clear      = bcm2711_timer_clear,
};

void bcm2711_timer_init(void)
{
    timer = &bcm2711_timers_ops;
}
