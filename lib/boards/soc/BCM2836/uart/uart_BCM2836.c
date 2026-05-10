#include "../include/BCM2836.h"
#include "include/uart_BCM2836.h"
#include "../../include/uart.h"

void bcm2836_mu_set(uint32_t baudrate) {
    mu_set(MU_2836, AUX_2836, baudrate);
}

// Receive char's
bool bcm2836_mu_rxc(void) {
    return mu_rxc(MU_2836);
}

// Transmit char 
void bcm2836_mu_txc(const uint8_t c) {
    mu_txc(MU_2836, c); 
}

// Clear RX buffer mini-UART
void bcm2836_mu_flush_rx(void) {
    mu_flush_rx(MU_2836);
}

uart_ops_t bcm2836_uart_ops = {
    .set = &bcm2836_mu_set,
    .txc = &bcm2836_mu_txc,
    .flush_rx = &bcm2836_mu_flush_rx,
    .rxc = &bcm2836_mu_rxc
};

void bcm2836_uart_init(void)
{
    uart = &bcm2836_uart_ops;
}