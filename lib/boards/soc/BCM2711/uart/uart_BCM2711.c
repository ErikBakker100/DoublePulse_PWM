#include "../include/BCM2711.h"
#include "include/uart_BCM2711.h"
#include "../../include/uart.h"

void bcm2711_uart_callback(void *data){
    // Handle UART interrupt (e.g., read received data)
    uart->rxc();
}

void bcm2711_mu_set(uint32_t baudrate) {
    mu_set(MU_2711, AUX_2711, baudrate);
}

// Receive char's
bool bcm2711_mu_rxc(void) {
    return mu_rxc(MU_2711);
}

// Transmit char 
void bcm2711_mu_txc(const uint8_t c) {
    mu_txc(MU_2711, c); 
}

// Clear RX buffer mini-UART
void bcm2711_mu_flush_rx(void) {
    mu_flush_rx(MU_2711);
}

uart_ops_t bcm2711_uart_ops = {
    .set = &bcm2711_mu_set,
    .txc = &bcm2711_mu_txc,
    .flush_rx = &bcm2711_mu_flush_rx,
    .rxc = &bcm2711_mu_rxc
};

void bcm2711_uart_init(void)
{
    uart = &bcm2711_uart_ops;
}