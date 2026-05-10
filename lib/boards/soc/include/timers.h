#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "../BCM2835/include/BCM2835.h"
typedef struct {
    bool (*set)(uint8_t timer, uint32_t time); // Set timer to expire after 'time'. The free running counter is driven by the timer. Returns true on success
                                            // clock and stopped whenever the processor is stopped in debug mode.
    bool (*expired)(uint8_t timer);         // Check if timer has expired, returns true if expired
    void (*clear)(uint8_t timer);           // After timer expiration, clear the flag. clear timer channel comparator matches.
                                            // The system timer match bits are routed to the interrupt controller where they can generate an interrupt.
                                            // If using with interrrupts, the interrupts should be routed seperately
} timers_ops_t;
extern const timers_ops_t *timer;

bool timer_set(volatile bcm2835_sys_timer_regs_t *regs, uint8_t timer, uint32_t time);
bool timer_expired(volatile bcm2835_sys_timer_regs_t *regs, uint8_t timer);
void timer_clear(volatile bcm2835_sys_timer_regs_t *regs, uint8_t timer);
