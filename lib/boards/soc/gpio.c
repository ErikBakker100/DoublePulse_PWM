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

// set the right alt function for the pin, and enable the right channel for that pin. Only 4 pins are supported for PWM, so if the pin is not supported, return -1 to indicate failure
void bcm283x_gpio_init_pwm_pin(uint8_t pin) {
    int8_t ch = -1;
    gpio_mode_t alt;
    trigger_pin = 255;                       // dummy value to prevent compiler warning, will be overwritten in the switch statement.
                                            // We can not use this variable to determine the alt function, because for some pins the 
                                            // alt function is different, even if they are on the same channel. So we need to set the 
                                            // alt function in the switch statement based on the pin number, and not based on the channel number.
    switch (pin) {
        case 12:
            alt = GPIO_ALT0;
            ch = 0;
            trigger_pin = 13;
            break;
        case 18:
            alt = GPIO_ALT5;
            ch = 0;
            trigger_pin = 19;
            break;
        case 13:
            alt = GPIO_ALT0;
            ch = 1;
            trigger_pin = 12;
            break;
        case 19:
            alt = GPIO_ALT5;
            ch = 1;
            trigger_pin = 18;
            break;
        default:                            // We can not continue with PWM, pin not supported
            ch = -1;                        // Set channel to an invalid value
            trigger_pin = 255;                       // Set tp to an invalid value
            break;
    }
    *pwm->channel = ch;
    if (ch != -1) {
        gpio->init_pin(pin, alt, PULL_DOWN);
        gpio->init_pin(trigger_pin, alt, PULL_DOWN); // We also need to set the corresponding trigger pin to the same alt function,
                                            // otherwise we can not use the trigger pin for the scope trigger output.
    }
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
