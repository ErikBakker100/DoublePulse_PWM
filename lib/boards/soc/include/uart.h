#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "../BCM2835/include/BCM2835.h"

// UART
typedef struct {
    void (*set)(uint32_t baudrate);
    void (*txc)(const uint8_t c);
    void (*flush_rx)(void);
    bool (*rxc)(void);
} uart_ops_t;
extern uart_ops_t *uart;

void mu_set(volatile bcm2835_mu_regs_t *mu_regs, volatile bcm2835_aux_regs_t *aux_regs, uint32_t baudrate);
bool mu_rxc(volatile bcm2835_mu_regs_t *regs);
void mu_txc(volatile bcm2835_mu_regs_t *regs, const uint8_t c);
void mu_flush_rx(volatile bcm2835_mu_regs_t *regs);
