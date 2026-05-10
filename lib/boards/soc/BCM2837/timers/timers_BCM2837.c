#include "../include/BCM2837.h"
#include "include/timers_BCM2837.h"
#include "../../include/timers.h"
#include "../../../../general/include/stdlib.h"

bool bcm2837_timer_set(uint8_t timer, uint32_t time) {
    return timer_set(SYS_TMR_2837, timer, time);
}

bool bcm2837_timer_expired(uint8_t timer) {
    return timer_expired(SYS_TMR_2837, timer);
}

void bcm2837_timer_clear(uint8_t timer) {
    timer_clear(SYS_TMR_2837, timer);
}

const timers_ops_t bcm2837_timers_ops = {
    .set        = bcm2837_timer_set,
    .expired    = bcm2837_timer_expired,
    .clear      = bcm2837_timer_clear,
};

void bcm2837_timer_init(void)
{
    timer = &bcm2837_timers_ops;
}
