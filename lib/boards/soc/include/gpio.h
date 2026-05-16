#pragma once
#include <stdint.h>
#include "../BCM2835/include/BCM2835.h"

// GPIO
typedef enum {
    GPIO_INPUT  = 0b000,  // 000
    GPIO_OUTPUT = 0b001,  // 001
    GPIO_ALT5   = 0b010,  // 010
    GPIO_ALT4   = 0b011,  // 011
    GPIO_ALT0   = 0b100,  // 100
    GPIO_ALT1   = 0b101,  // 101
    GPIO_ALT2   = 0b110,  // 110
    GPIO_ALT3   = 0b111,  // 111
} gpio_mode_t;

typedef enum {
    PULL_NONE = 0,
    PULL_UP = 1,
    PULL_DOWN = 2,
} gpio_pud_t;

typedef struct {
    void (*init_pin)(uint8_t pin, gpio_mode_t mode, gpio_pud_t pud);
    void (*set)(uint8_t pin);
    void (*clear)(uint8_t pin);
    void (*toggle)(uint8_t pin);
    uint32_t (*read)(uint8_t pin);
} gpio_ops_t;
extern const gpio_ops_t *gpio;

extern uint8_t trigger_pin;                 // Used to trigger a scope.

void bcm283x_gpio_init_pin(volatile bcm2835_gpio_regs_t *regs, uint8_t pin, gpio_mode_t mode, gpio_pud_t pud);
void bcm283x_gpio_set(volatile bcm2835_gpio_regs_t *regs, uint8_t pin);
void bcm283x_gpio_clear(volatile bcm2835_gpio_regs_t *regs, uint8_t pin);
void bcm283x_gpio_toggle(volatile bcm2835_gpio_regs_t *regs, uint8_t pin);
uint32_t bcm283x_gpio_read(volatile bcm2835_gpio_regs_t *regs, uint8_t pin);
