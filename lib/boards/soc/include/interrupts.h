#pragma once
#include <stdint.h>

typedef struct {
    // handlers for core0
    void (*init_core0)(void);               // Initialize IRQs and FIQ's for core0
    void (*irq_handler_core0)(void);        // IRQ handler for core0
    void (*fiq_handler_core0)(void);        // FIQ handler for core0
    // handlers for core1
    void (*init_core1)(void);               // Initialize IRQs and FIQ's for core1
    void (*irq_handler_core1)(void);        // IRQ handler for core1
    void (*fiq_handler_core1)(void);        // FIQ handler for core1

    void (*irq_disable)(void);
    void (*fiq_disable)(void);
    void (*irq_enable)(void);
    void (*fiq_enable)(void);
} interrupts_ops_t;
extern const interrupts_ops_t *interrupts;

extern void irq_handler_core0(void);
extern void irq_handler_core1(void);
extern void fiq_handler_core0(void);
extern void fiq_handler_core1(void);