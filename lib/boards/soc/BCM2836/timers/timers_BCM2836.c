#include "../include/BCM2836.h"
#include "include/timers_BCM2836.h"
#include "../../include/timers.h"

bool bcm2836_timer_set(uint8_t timer, uint32_t time) {
    return timer_set(SYS_TMR_2836, timer, time);
}

bool bcm2836_timer_expired(uint8_t timer) {
    return timer_expired(SYS_TMR_2836, timer);
}

void bcm2836_timer_clear(uint8_t timer) {
    timer_clear(SYS_TMR_2836, timer);
}

const timers_ops_t bcm2836_timers_ops = {
    .set        = bcm2836_timer_set,
    .expired    = bcm2836_timer_expired,
    .clear      = bcm2836_timer_clear,
};

void bcm2836_timer_init(void)
{
    timer = &bcm2836_timers_ops;
}
