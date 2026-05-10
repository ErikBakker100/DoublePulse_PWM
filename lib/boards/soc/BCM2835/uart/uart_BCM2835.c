#include "../include/BCM2835.h"
#include "include/uart_BCM2835.h"
#include "../../include/uart.h"

void bcm2835_mu_set(uint32_t baudrate) {
    mu_set(MU_2835, AUX_2835, baudrate);
}

bool bcm2835_mu_rxc(void) {
    return mu_rxc(MU_2835);
}

void bcm2835_mu_txc(const uint8_t c) {
    mu_txc(MU_2835, c); 
}

void bcm2835_mu_flush_rx(void) {
    mu_flush_rx(MU_2835);
}

uart_ops_t bcm2835_uart_ops = {
    .set = &bcm2835_mu_set,
    .txc = &bcm2835_mu_txc,
    .flush_rx = &bcm2835_mu_flush_rx,
    .rxc = &bcm2835_mu_rxc
};

void bcm2835_uart_init(void)
{
    uart = &bcm2835_uart_ops;
}