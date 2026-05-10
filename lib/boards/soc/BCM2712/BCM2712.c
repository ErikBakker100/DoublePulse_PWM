#include "include/BCM2712.h"
#include "gpio/include/gpio_BCM2712.h"
#include "pwm/include/pwm_BCM2712.h"

volatile bcm2712_int_gic_600_gicr_regs_t *INT_GICR[4];

void BCM2712_init(soc_t *mmio) {

    bcm2712_pwm_init();
}