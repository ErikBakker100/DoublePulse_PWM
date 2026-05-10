#include "include/interrupts_BCM2711.h"

#include "../../include/interrupts.h"
#include "../../include/uart.h"
#include "../../include/mailbox.h"
#include "../../cpu/include/cpu.h"
#include "../../include/timers.h"
#include "../../include/gpio.h"
#include "../../include/interrupts.h"
#include "../timers/include/timers_BCM2711.h"
#include "../uart/include/uart_BCM2711.h"
#include "../mailbox/include/mailbox_BCM2711.h"
#include "../../../../general/include/serial.h"
#include "../../../../general/include/config.h" // for BLINK_TIMER
#include "../../../../multi_core/include/core1.h"

static volatile interrupt_slot_t interrupt_table[256];

// ------------------------------------------------------------------------------
// GIC-400 helpers
// ------------------------------------------------------------------------------
void bcm2711_gic400_irq_enable(uint32_t interrupt_id, uint8_t cpu_mask) {
    // Stel target CPU in (1 = Core 0, 2 = Core 1, 4 = Core 2, 8 = Core 3)
    INT_GICD_2711->ISENABLER[interrupt_id / 32] |= 1u << (interrupt_id % 32); // Enable the interrupt in the GIC Distributor
    INT_GICD_2711->ITARGETSR[interrupt_id] = cpu_mask; // Stel target CPU in (1 = Core 0, 2 = Core 1, 4 = Core 2, 8 = Core 3)
    INT_GICD_2711->IPRIORITYR[interrupt_id] = 0x80; // Stel prioriteit in (0-255, lagere waarde = hogere prioriteit)
    INT_GICD_2711->IGROUPR[interrupt_id / 32] |= (1u << (interrupt_id % 32));
}

void bcm2711_gic400_fiq_enable(uint32_t interrupt_id, uint8_t cpu_mask) {
    // Stel target CPU in (1 = Core 0, 2 = Core 1, 4 = Core 2, 8 = Core 3)
    INT_GICD_2711->ISENABLER[interrupt_id / 32] |= 1u << (interrupt_id % 32); // Enable the interrupt in the GIC Distributor
    INT_GICD_2711->ITARGETSR[interrupt_id] = cpu_mask; // Stel target CPU in (1 = Core 0, 2 = Core 1, 4 = Core 2, 8 = Core 3)
    INT_GICD_2711->IPRIORITYR[interrupt_id] = 0x80; // Stel prioriteit in (0-255, lagere waarde = hogere prioriteit)
    INT_GICD_2711->IGROUPR[interrupt_id / 32] &= ~(1u << (interrupt_id % 32));
}

// Koppel een driver-functie aan een specifiek ID.
void bcm2711_gic400_register_handler(uint32_t interrupt_id, interrupt_handler_t handler, void *data) {
    if (interrupt_id < 256) {
    interrupt_table[interrupt_id].handler = handler;
    interrupt_table[interrupt_id].data = data;
    }
}

// ------------------------------------------------------------------------------
// IRQ handlers for core0
// ------------------------------------------------------------------------------
void bcm2711_interrupts_init_core0(void) {
    interrupts->irq_disable();              // Disable IRQs
    interrupts->fiq_disable();              // Disable FIQs
    INT_GICD_2711->CTLR = 0;                // Schakel de Distributor uit tijdens config
    INT_GICC_2711->CTLR = 1;                // Schakel de CPU Interface in
    INT_GICC_2711->PMR = 0xFF;              // Priority Mask: laat alle interrupts met prioriteit 0-255 door
    INT_GICC_2711->BPR = 0x3;               // 0x3 of 0x7 negeren subprioriteiten.
    static uint8_t timer_data = 1;
    bcm2711_gic400_register_handler(GIC_IRQ_TIMER1, bcm2711_timer_callback, &timer_data);
    bcm2711_gic400_irq_enable(GIC_IRQ_TIMER1, CORE0); // Enable timer interrupt voor Core 0
    static uint8_t uart_data = 0;
    bcm2711_gic400_register_handler(GIC_IRQ_MINI_UART, bcm2711_uart_callback, &uart_data);
    bcm2711_gic400_irq_enable(GIC_IRQ_MINI_UART, CORE0); // Enable mini UART interrupt voor Core 0
    INT_GICD_2711->CTLR = 3;                // Schakel de Distributor in voor Group 0 (secure) en Group 1 (non secure) interrupts
    interrupts->irq_enable();               // Enable IRQs
}

void bcm2711_irq_handler_core0(void) {
    uint32_t iar = INT_GICC_2711->IAR;      // Acknowledge de interrupt en krijg het ID
    uint32_t irq_id = iar & 0x3FF; 
    // Roep de geregistreerde handler aan
    if (irq_id < 256 && interrupt_table[irq_id].handler) {
        interrupt_table[irq_id].handler(interrupt_table[irq_id].data);
    }
    INT_GICC_2711->EOIR = iar;              // End of Interrupt schrijven om de interrupt te de-acknowledgen
}

void bcm2711_fiq_handler_core0(void) {
    bcm2711_irq_handler_core0();
}

// ----------------------------------------------------------------------------------
// IRQ handlers for core1
// ----------------------------------------------------------------------------------

void bcm2711_interrupts_init_core1(void) {
    interrupts->irq_disable();              // Disable IRQs
    interrupts->fiq_disable();              // Disable FIQs
    INT_GICC_2711->CTLR = 1;                // Schakel de CPU Interface in
    INT_GICC_2711->PMR = 0xFF;              // Priority Mask: laat alle interrupts met prioriteit 0-255 door
    INT_GICC_2711->BPR = 0x3;               // 0x3 of 0x7 negeren subprioriteiten.
    static uint8_t data;                           
    bcm2711_gic400_register_handler(GIC_IRQ_SGI0, bcm2711_mailbox_irq_handler, &data);
    bcm2711_gic400_irq_enable(GIC_IRQ_SGI0, CORE1);
    dmb();
    interrupts->irq_enable();               // Enable IRQs
}

void bcm2711_irq_handler_core1(void) {
    uint32_t iar = INT_GICC_2711->IAR;      // Acknowledge de interrupt en krijg het ID
    uint32_t irq_id = iar & 0x3FF; 
    // Roep de geregistreerde handler aan
    if (irq_id >= GIC_IRQ_SGI0 && irq_id <= GIC_IRQ_SGI3) {
        mailbox0(mailbox->read(irq_id, 1)); // BCM2711 uses SGI's 0-3 to signal to update delay values
    }
    INT_GICC_2711->EOIR = iar;              // End of Interrupt schrijven om de interrupt te de-acknowledgen
}

void bcm2711_fiq_handler_core1(void) {
    bcm2711_irq_handler_core1();
}

// ----------------------------------------------------------------------------------
// General IRQ routines
// ----------------------------------------------------------------------------------

void bcm2711_irq_disable(void) {
#ifdef __aarch64__
    asm volatile("msr daifset, #2" ::: "memory");
#else
    asm volatile("cpsid i" ::: "memory");
#endif
}

void bcm2711_fiq_disable(void) {
#ifdef __aarch64__
    asm volatile("msr daifset, #1" ::: "memory");
#else
    asm volatile("cpsid f" ::: "memory");
#endif
}

void bcm2711_irq_enable(void) {
#ifdef __aarch64__
    asm volatile("msr daifclr, #2" ::: "memory");
#else
    asm volatile("cpsie i" ::: "memory");
#endif
}

void bcm2711_fiq_enable(void) {
#ifdef __aarch64__
    asm volatile("msr daifclr, #1" ::: "memory");
#else
    asm volatile("cpsie f" ::: "memory");
#endif
}

void bcm2711_gic400_init_distributor_disable (void) {
    INT_GICD_2711->CTLR = 0; // Disable GIC Distributor
}

void bcm2711_gic400_init_distributor_enable (void) {
    INT_GICD_2711->CTLR = 1; // Enable GIC Distributor
}

const interrupts_ops_t bcm2711_interrupts_ops = {
    .init_core0     = bcm2711_interrupts_init_core0,
    .irq_handler_core0  = bcm2711_irq_handler_core0,
    .fiq_handler_core0  = bcm2711_fiq_handler_core0,
    .init_core1     = bcm2711_interrupts_init_core1,
    .irq_handler_core1  = bcm2711_irq_handler_core1,
    .fiq_handler_core1  = bcm2711_fiq_handler_core1,
    .irq_disable        = bcm2711_irq_disable,
    .fiq_disable        = bcm2711_fiq_disable,
    .irq_enable         = bcm2711_irq_enable,
    .fiq_enable         = bcm2711_fiq_enable
};

void bcm2711_interrupts_init(void)
{
    interrupts = &bcm2711_interrupts_ops;
}

/*
void gic_init(void) {
    INT_GICD->CTLR = 0;
    // Enable UART IRQ (57)
    INT_GICD->ISENABLER[57 / 32] = 1 << (57 % 32);
    INT_GICD->IPRIORITYR[57] = 0x80;
    INT_GICD->ITARGETSR[57] = 1; // CPU0

    INT_GICD->CTLR = 1;

    INT_GICC->PMR = 0xFF;
    INT_GICC->CTLR = 1;
}

uint32_t irq = INT_GICC->IAR & 0x3FF;

switch (irq) {
    case 57:  // UART (PL011)
        uart_irq_handler();
        break;
}

GICC->EOIR = irq;
*/