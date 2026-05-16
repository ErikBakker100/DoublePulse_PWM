#include "include/interrupts_BCM2837.h"
#include "../../include/interrupts.h"
#include "../../include/uart.h"
#include "../../include/mailbox.h"
#include "../../cpu/include/cpu.h"
#include "../../include/timers.h"
#include "../../include/gpio.h"
#include "../../../../general/include/serial.h"
#include "../../../../general/include/config.h" // for BLINK_TIMER
#include "../../../../cores/include/core0.h"

// ------------------------------------------------------------------------------
// IRQ handlers for core0
// ------------------------------------------------------------------------------

void bcm2837_interrupts_init_core0(void) {
    // Disable interrupts
    interrupts->irq_disable();
    interrupts->fiq_disable();
    IC_2837->FIQ_CONTROL = 0; // Disable FIQs
    IC_2837->DISABLE_IRQS_BASIC = 0xFFFFFFFF; // Disable all basic IRQs
    IC_2837->DISABLE_IRQS[0] = 0xFFFFFFFF;  // Disable all IRQs in bank 0
    IC_2837->DISABLE_IRQS[1] = 0xFFFFFFFF;  // Disable all IRQs in bank 1
    // Mask all interrupts
    IC_2837->ENABLE_IRQS_BASIC = 0;
    IC_2837->ENABLE_IRQS[0] = 0;
    IC_2837->ENABLE_IRQS[1] = 0;
    // Enable UART and SYSTEM Timer interrupts
    IC_2837->ENABLE_IRQS[0] |= (1 << 29);   // Enable Mini UART (bit 61 overall, bit 29 in ENABLE_IRQS[1])
    IC_2837->ENABLE_IRQS[0] |= (1 << 1);    // Enable SYSTEM Timer C1 interrupt (bit 1 overall, bit 1 in ENABLE_IRQS[0])
    // PWM en DMA interrupts.
    IC_2837->ENABLE_IRQS[0] |= (1 << 21);   // Enable DMA interrupt (bit 21 overall, bit 21 in ENABLE_IRQS[0])
    IC_2837->ENABLE_IRQS[1] |= (1 << 13);   // Enable PWM interrupt (bit 45 overall, bit 13 in ENABLE_IRQS[1])
    CORE_MB_CTRL_2837->MAILBOX_CNTRL[0] = (MBOX0_IRQ); // IRQ voor mailbox 0 van core0 enabelen.
    // ensure writes reach device before we enable interrupts
    dsb();
    isb();
    // Enable interrupts
    interrupts->irq_enable();
//    interrupts->fiq_enable();
 }

void bcm2837_irq_handler_core0(void) {
    if (AUX_2837->IRQ & 1) {  // Mini UART interrupt
        uart->rxc();
    }
    if (SYS_TMR_2837->CS & (1 << 1)) {      // System Timer C1 interrupt
        SYS_TMR_2837->CS = (1 << 1);        // Clear the interrupt
        timer->clear(1);                    // Clear timer 1 expiration flag
        gpio->toggle(STATUS_PIN);           // Toggle GPIO 21 for heart beat indication
        timer->set(1, BLINK_TIMER);         // Re-set timer
    }
    if (IC_2837->IRQ_PENDING[1] & (1 << 13)) { // PWM interrupt
        // Clear the PWM interrupt by writing to the appropriate register in the PWM controller
        mu_puts("> PWM interrupt occurred ");
        mu_put_bits32(PWM0_2837->STA);
        mu_puts("\r\n");
        PWM0_2837->STA = 0xFFF; // Clear the PWM interrupt status for channel 0
    }
    if (IC_2837->IRQ_PENDING[0] & (1 << 21)) { // DMA 5 interrupt
        DMA05_2837->CS |= CS_INT;           // Set to clear interrupt status
        if (DMA05_2837->DEBUG & DEBUG_FIFO_ERROR) {
            mu_puts("> DMA 5 FIFO error detected\r\n");
        }
        if (DMA05_2837->DEBUG & DEBUG_READ_ERROR) {
            mu_puts("> DMA 5 read error detected\r\n");
        }
        DMA05_2837->DEBUG = DEBUG_CLEAR_ERRORS; // Clear any error flags in the debug register
        DMAEN_2837->ENABLE |= DMA_CHANNEL_5;// Re-enable DMA channel 5 for the next transfer
    }
    if (ISR_2837->IRQ_SOURCE[0] & INT_SRC_MBOX0) {
        mailbox0(mailbox->read(0));// Read mailbox 0 for core0
    }
}

void bcm2837_fiq_handler_core0(void) {
}

const interrupts_ops_t bcm2837_interrupts_ops = {
    .init_core0         = bcm2837_interrupts_init_core0,
    .irq_handler_core0  = bcm2837_irq_handler_core0,
    .fiq_handler_core0  = bcm2837_fiq_handler_core0,
    .irq_disable        = irq_disable,
    .fiq_disable        = fiq_disable,
    .irq_enable         = irq_enable,
    .fiq_enable         = fiq_enable
};

void bcm2837_interrupts_init(void)
{
    interrupts = &bcm2837_interrupts_ops;
}
