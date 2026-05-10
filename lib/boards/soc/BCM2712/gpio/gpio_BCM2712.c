#include "include/gpio_BCM2712.h"
#include "../../include/gpio.h"

void bcm2712_init_pin(uint8_t pin, gpio_mode_t mode, gpio_pud_t pud) { /* ... */ }
void bcm2712_set(uint8_t pin) { /* ... */ }
void bcm2712_clear(uint8_t pin) { /* ... */ }
uint32_t bcm2712_read(uint8_t pin) { /* ... */ return 0;}

const gpio_ops_t bcm2712_gpio_ops = {
    .init_pin = bcm2712_init_pin,
    .set      = bcm2712_set,
    .clear    = bcm2712_clear,
    .read     = bcm2712_read,
};

void BCM2712_GPIO_Init(void)
{
    gpio = &bcm2712_gpio_ops;
}