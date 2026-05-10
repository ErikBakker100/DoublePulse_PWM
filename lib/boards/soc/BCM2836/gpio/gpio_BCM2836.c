#include "../include/BCM2836.h"
#include "include/gpio_BCM2836.h"
#include "../../include/gpio.h"
#include "../../../../general/include/stdlib.h" // For DELAY function

void bcm2836_gpio_init_pin(uint8_t pin, gpio_mode_t mode, gpio_pud_t pud) {
    bcm283x_gpio_init_pin(GPIO_2836, pin, mode, pud);
}

void bcm2836_gpio_set(uint8_t pin) {
    bcm283x_gpio_set(GPIO_2836, pin);
    }

void bcm2836_gpio_clear(uint8_t pin) {
    bcm283x_gpio_clear(GPIO_2836, pin);
}   

void bcm2836_gpio_toggle(uint8_t pin) {
    bcm283x_gpio_toggle(GPIO_2836, pin);
}

uint32_t bcm2836_gpio_read(uint8_t pin) {
    return bcm283x_gpio_read(GPIO_2836, pin);
}

const gpio_ops_t bcm2836_gpio_ops = {
    .init_pin   = bcm2836_gpio_init_pin,
    .set        = bcm2836_gpio_set,
    .clear      = bcm2836_gpio_clear,
    .toggle     = bcm2836_gpio_toggle,
    .read       = bcm2836_gpio_read
};

void bcm2836_gpio_init(void)
{
    gpio = &bcm2836_gpio_ops;
}

