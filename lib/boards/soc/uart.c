#include "include/uart.h"
#include "../include/boards.h"
#include "../../general/include/config.h"
#include "include/gpio.h"
#include "../../general/include/serial.h"
#include "include/mailbox.h"

uart_ops_t *uart = NULL;

void mu_set(volatile bcm2835_mu_regs_t *mu_regs, volatile bcm2835_aux_regs_t *aux_regs, uint32_t baudrate) {
    aux_regs->ENABLES |= 1;          // Enable Mini UART (bit 0)
    mu_regs->MU_CNTL = 0;            // Disable TX/RX
    mu_regs->MU_LCR = 3;             // 8-bit mode, DLAB=0 (FIFO's used)
    mu_regs->MU_MCR = 0;             // RTS disabled
    while(mu_regs->MU_LSR & 1) { (void)mu_regs->MU_IO; } // Clear the RX FIFO by reading from it until it's empty
    mu_regs->MU_BAUD = (((board.clock_rates_measured[CORE_id]) + (4 * baudrate)) / (8 * baudrate)) - 1;
    // Set GPIO 14 and 15 to ALT5 (Mini UART)
    gpio->init_pin(14, GPIO_ALT5, PULL_NONE);
    gpio->init_pin(15, GPIO_ALT5, PULL_NONE);
    mu_regs->MU_IER  = ((1 << 0) | (1 << 2) | (1 << 3));     // mini UART RX interrupt enable, BCM2835 errata stelt dat bit 3:2 moeten worden ingesteld voor RX interrupt
    mu_regs->MU_IIR = 0xC6;          // Bit 6 en 7 op 1 (FIFO enable/clear) + bit 1 en 2 (FIFO reset)
    mu_regs->MU_CNTL = 3;            // Enable TX and RX
    (void)mu_regs->MU_IO;            // Dummy read to ensure the UART is ready
}

// Receive char's
bool mu_rxc(volatile bcm2835_mu_regs_t *regs) {
    bool received = false;
    while (regs->MU_LSR & 1) {             // Check if data is ready (bit 0 of Line Status Register)
        uint8_t c = regs->MU_IO & 0xFF;     // Read the received character (mask to 8 bits)
        rx_put(c);
        received = true;
    }
    return received;
}

// Transmit char 
void mu_txc(volatile bcm2835_mu_regs_t *regs, const uint8_t c) {
    do{asm volatile("nop");} while (!(regs->MU_LSR & 0x20)); // Wacht tot de TX FIFO ruimte heeft
   regs->MU_IO = c;              // write the character to the buffer
}

// Clear RX buffer mini-UART
void mu_flush_rx(volatile bcm2835_mu_regs_t *regs)
{
    while (regs->MU_LSR & 0x01) {
        (void)(regs->MU_IO & 0xFF);
    }
}