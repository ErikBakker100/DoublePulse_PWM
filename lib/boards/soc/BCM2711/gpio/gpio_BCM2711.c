#include "include/gpio_BCM2711.h"
#include "../../include/gpio.h"

void bcm2711_init_pin(uint8_t pin, gpio_mode_t mode, gpio_pud_t pud) { 
    uint32_t reg_index = pin / 10;          // Every GPFSEL register handles 10 pins
    uint32_t shift = (pin % 10) * 3;        // 3 bits per pin
    // Mask the 3 bits for this pin, and put them to 'mode' (gpio_mode_t)
    uint32_t val = GPIO_2711->FSEL[reg_index];
    val &= ~(7u << shift);
    val |=  ((uint32_t)mode << shift);
    GPIO_2711->FSEL[reg_index] = val;
    // Set pull up/down for pin
    uint32_t reg = pin / 16;
    shift = (pin % 16) * 2;
    val = GPIO_2711->PUP_PDN_CNTRL_REG[reg];
    val &= ~(3u << shift);
    val |= ((uint32_t)pud << shift);
    GPIO_2711->PUP_PDN_CNTRL_REG[reg] = val;
}

void bcm2711_set(uint8_t pin) {
    uint8_t reg_index = pin / 32;          // Elk register behandelt 32 pins    
    uint32_t mask = 1u << (pin % 32);
    GPIO_2711->SET[reg_index] = mask;
}

void bcm2711_clear(uint8_t pin) {
    uint8_t reg_index = pin / 32;          // Elk register behandelt 32 pins    
    uint32_t mask = 1u << (pin % 32);
    GPIO_2711->CLR[reg_index] = mask;
}

void bcm2711_toggle(uint8_t pin) {
    uint8_t reg_index = pin / 32;          // Elk register behandelt 32 pins    
    uint32_t mask = 1u << (pin % 32);
    if (GPIO_2711->LEV[reg_index] & mask) GPIO_2711->CLR[reg_index] = mask;
    else GPIO_2711->SET[reg_index] = mask;
}

uint32_t bcm2711_read(uint8_t pin) {
    uint32_t reg_index = pin / 10;          // Every GPFSEL register handles 10 pins
    uint32_t shift = (pin % 10) * 3;        // 3 bits per pin
    // Mask the 3 bits for this pin, and read 'mode'
    uint32_t val = GPIO_2711->FSEL[reg_index];
    val >>= shift;
    val &= 0x7;                             // isolate 3 bits
    return val;
}

const gpio_ops_t bcm2711_gpio_ops = {
    .init_pin = bcm2711_init_pin,
    .set      = bcm2711_set,
    .clear    = bcm2711_clear,
    .toggle   = bcm2711_toggle,
    .read     = bcm2711_read,
};

void bcm2711_gpio_Init(void)
{
    gpio = &bcm2711_gpio_ops;
}
