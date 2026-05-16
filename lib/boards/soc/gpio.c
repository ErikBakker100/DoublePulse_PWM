#include "include/gpio.h"
#include "include/pwm.h"
#include "BCM2835/include/BCM2835.h"
#include "../../general/include/stdlib.h"

const gpio_ops_t *gpio = NULL;
uint8_t trigger_pin;

void bcm283x_gpio_init_pin(volatile bcm2835_gpio_regs_t *regs, uint8_t pin, gpio_mode_t mode, gpio_pud_t pud) {
    uint32_t reg_index = pin / 10;          // Every GPFSEL register handles 10 pins
    uint32_t shift = (pin % 10) * 3;        // 3 bits per pin
    // Mask the 3 bits for this pin, and put them to 'mode' (gpio_mode_t)
    uint32_t val = regs->FSEL[reg_index];
    val &= ~(7u << shift);
    val |=  ((uint32_t)mode << shift);
    regs->FSEL[reg_index] = val;
    // Set pull up/down for pin
    regs->PUD = (uint32_t)pud;
    DELAY(150);
    reg_index = pin / 32;
    uint32_t clk_bit = 1u << (pin % 32);
    regs->PUDCLK[reg_index] = clk_bit;
    DELAY(150);
    regs->PUD = 0;
    regs->PUDCLK[reg_index] = 0;
}

void bcm283x_gpio_set(volatile bcm2835_gpio_regs_t *regs, uint8_t pin) {
    uint8_t reg_index = pin / 32;          // Elk register behandelt 32 pins    
    uint32_t mask = 1u << (pin % 32);
    regs->SET[reg_index] = mask;
}

void bcm283x_gpio_clear(volatile bcm2835_gpio_regs_t *regs, uint8_t pin) {
    uint8_t reg_index = pin / 32;          // Elk register behandelt 32 pins    
    uint32_t mask = 1u << (pin % 32);
    regs->CLR[reg_index] = mask;
}   

void bcm283x_gpio_toggle(volatile bcm2835_gpio_regs_t *regs, uint8_t pin) {
    uint8_t reg_index = pin / 32;          // Elk register behandelt 32 pins    
    uint32_t mask = 1u << (pin % 32);
    if (regs->LEV[reg_index] & mask) regs->CLR[reg_index] = mask;
    else regs->SET[reg_index] = mask;
}

uint32_t bcm283x_gpio_read(volatile bcm2835_gpio_regs_t *regs, uint8_t pin) {
    uint32_t reg_index = pin / 10;          // Every GPFSEL register handles 10 pins
    uint32_t shift = (pin % 10) * 3;        // 3 bits per pin

    // Mask the 3 bits for this pin, and read 'mode'
    uint32_t val = regs->FSEL[reg_index];
    val >>= shift;
    val &= 0x7;                             // isolate 3 bits
    return val;
}
