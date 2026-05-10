#pragma once
#include "../../include/BCM2711.h"

#define GIC_IRQ_TIMER1     97
#define GIC_IRQ_TIMER3     99
#define GIC_IRQ_USB        124
#define GIC_IRQ_MINI_UART  125
#define GIC_IRQ_I2C1       151
#define GIC_IRQ_UART0      153
#define GIC_IRQ_SGI0       0
#define GIC_IRQ_SGI1       1
#define GIC_IRQ_SGI2       2
#define GIC_IRQ_SGI3       3

typedef void (*interrupt_handler_t)(void *data);
typedef struct {
    interrupt_handler_t handler;
    void *data;
} interrupt_slot_t;

void bcm2711_interrupts_init(void);
