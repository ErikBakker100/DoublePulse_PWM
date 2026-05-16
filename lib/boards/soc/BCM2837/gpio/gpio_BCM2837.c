#include "../include/BCM2837.h"
#include "include/gpio_BCM2837.h"
#include "../../include/gpio.h"

void bcm2837_gpio_init_pin(uint8_t pin, gpio_mode_t mode, gpio_pud_t pud) {
    bcm283x_gpio_init_pin(GPIO_2837, pin, mode, pud);
}

void bcm2837_gpio_set(uint8_t pin) {
    bcm283x_gpio_set(GPIO_2837, pin);
}

void bcm2837_gpio_clear(uint8_t pin) {
    bcm283x_gpio_clear(GPIO_2837, pin);
}   

void bcm2837_gpio_toggle(uint8_t pin) {
    bcm283x_gpio_toggle(GPIO_2837, pin);
}

uint32_t bcm2837_gpio_read(uint8_t pin) {
    return bcm283x_gpio_read(GPIO_2837, pin);
}

const gpio_ops_t bcm2837_gpio_ops = {
    .init_pin   = bcm2837_gpio_init_pin,
    .set        = bcm2837_gpio_set,
    .clear      = bcm2837_gpio_clear,
    .toggle     = bcm2837_gpio_toggle,
    .read       = bcm2837_gpio_read
};

void bcm2837_gpio_init(void)
{
    gpio = &bcm2837_gpio_ops;
}
