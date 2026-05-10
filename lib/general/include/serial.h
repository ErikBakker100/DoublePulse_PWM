#pragma once
#pragma once

#include <stdint.h>
#include <stdbool.h>

#define RX_BUF_SIZE 256                     // Size of the RX buffer for UART reception

/* RX ringbuffer */
typedef struct {
    volatile uint32_t head;
    volatile uint32_t tail;
    uint8_t buffer[RX_BUF_SIZE];
} rx_buf_t;

void mu_putc(const uint8_t c);
void mu_puts(const char *s);
void mu_put_uint(const uint32_t n);
//uint16_t read_json(uint8_t * const buf, uint16_t maxlen, uint32_t timeout);
void mu_put_hex8(const uint8_t value, bool leading);    // Leading true will use leading '0x', false is without
void mu_put_hex16(const uint16_t value, bool leading);
void mu_put_hex32(const uint32_t value, bool leading);
void mu_put_hex64(const uint64_t value, bool leading);
void mu_put_bits8(const uint8_t value);
void mu_put_bits16(const uint16_t value);
void mu_put_bits32(const uint32_t value);
void mu_put_bits64(const uint64_t value);
void rx_put(const uint8_t c);
bool rx_available(void);
uint8_t rx_get(void);