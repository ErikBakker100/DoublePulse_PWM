#include "include/interrupts_BCM2835.h"
#include "../../include/interrupts.h"
#include "../../include/uart.h"
#include "../../include/mailbox.h"
#include "../../cpu/include/cpu.h"
#include "../../include/timers.h"
#include "../../include/gpio.h"
#include "../../../../general/include/serial.h"
#include "../../../../general/include/config.h" // for BLINK_TIMER
#include "../../../../multi_core/include/core1.h"
#include "../../../../general/include/stdlib.h"

// ------------------------------------------------------------------------------
// IRQ handlers for core0
// ------------------------------------------------------------------------------

void bcm2835_interrupts_init_core0(void) {
    // Disable interrupts
    interrupts->irq_disable();
    interrupts->fiq_disable();
    IC_2835->FIQ_CONTROL = 0; // Disable FIQs
    IC_2835->DISABLE_IRQS_BASIC = 0xFFFFFFFF; // Disable all basic IRQs
    IC_2835->DISABLE_IRQS[0] = 0xFFFFFFFF;  // Disable all IRQs in bank 0
    IC_2835->DISABLE_IRQS[1] = 0xFFFFFFFF;  // Disable all IRQs in bank 1
    // Mask all interrupts
    IC_2835->ENABLE_IRQS_BASIC = 0;
    IC_2835->ENABLE_IRQS[0] = 0;
    IC_2835->ENABLE_IRQS[1] = 0;
    // Enable UART and SYSTEM Timer interrupts
    IC_2835->ENABLE_IRQS[0] = (1 << 29);    // Enable Mini UART bit 29
    IC_2835->ENABLE_IRQS[0] = (1 << 1);     // Enable SYSTEM Timer C1 interrupt (bit 1 overall, bit 1 in ENABLE_IRQS[0])
    // ensure writes reach device before we enable interrupts
    dsb();
    isb();
    // Enable interrupts
    interrupts->irq_enable();
//    interrupts->fiq_enable();
}

void bcm2835_irq_handler_core0(void) {
    if (AUX_2835->IRQ & 1) {                // Mini UART interrupt
        uart->rxc();
    }
    if (SYS_TMR_2835->CS & (1 << 1)) {      // System Timer C1 interrupt
        SYS_TMR_2835->CS = (1 << 1);        // Clear the interrupt
        timer->clear(1);                    // Clear timer 1 expiration flag
        gpio->toggle(STATUS_PIN);           // Toggle GPIO 21 for heart beat indication
        timer->set(1, BLINK_TIMER);         // Re-set timer 1 for 1 second
    }
}

void bcm2835_fiq_handler_core0(void) {
}

const interrupts_ops_t bcm2835_interrupts_ops = {
    .init_core0         = bcm2835_interrupts_init_core0,
    .irq_handler_core0  = bcm2835_irq_handler_core0,
    .fiq_handler_core0  = bcm2835_fiq_handler_core0,
    .irq_handler_core1  = 0,
    .fiq_handler_core1  = 0,    
    .init_core1         = 0,
    .irq_disable        = irq_disable,
    .fiq_disable        = fiq_disable,
    .irq_enable         = irq_enable,
    .fiq_enable         = fiq_enable
};

void bcm2835_interrupts_init(void)
{
    interrupts = &bcm2835_interrupts_ops;
}
