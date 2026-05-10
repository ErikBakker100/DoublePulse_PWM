#include "../include/BCM2835.h"
#include "include/timers_BCM2835.h"
#include "../../include/timers.h"

bool bcm2835_timer_set(uint8_t timer, uint32_t time) {
    return timer_set(SYS_TMR_2835, timer, time);
}

bool bcm2835_timer_expired(uint8_t timer) {
    return timer_expired(SYS_TMR_2835, timer);
}

void bcm2835_timer_clear(uint8_t timer) {
    timer_clear(SYS_TMR_2835, timer);
}

const timers_ops_t bcm2835_timers_ops = {
    .set        = bcm2835_timer_set,
    .expired    = bcm2835_timer_expired,
    .clear      = bcm2835_timer_clear,
};

void bcm2835_timer_init(void)
{
    timer = &bcm2835_timers_ops;
}
