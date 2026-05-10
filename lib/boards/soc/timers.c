#include "include/timers.h"
#include "../../general/include/stdlib.h"

const timers_ops_t *timer = NULL;

bool timer_set(volatile bcm2835_sys_timer_regs_t *regs, uint8_t timer, uint32_t time) {
        // Implementation for setting the timer on BCM2835
    if (timer > 3) return false; // BCM2835 has 4 timers: 0-3
    regs->C[timer] = regs->CLO + time;
    return true;
}

bool timer_expired(volatile bcm2835_sys_timer_regs_t *regs, uint8_t timer) {
     // Implementation for checking if the timer has expired
    if (timer > 3) return false; // BCM2835 has 4 timers: 0-3
        return (regs->CS & (1 << timer));
}

void timer_clear(volatile bcm2835_sys_timer_regs_t *regs, uint8_t timer) {
    // Implementation for clearing the timer after being expired
    if (timer > 3) return; // BCM2835 has 4 timers: 0-3
    regs->CS = (1 << timer); // Clear the expiration flag
}