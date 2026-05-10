#include "include/pwm_BCM2712.h"
#include "../../include/pwm.h"
#include <stddef.h>

const pwm_ops_t bcm2712_pwm_ops = {
    .run = NULL
};

void bcm2712_pwm_init(void) {
    pwm = &bcm2712_pwm_ops;
}
