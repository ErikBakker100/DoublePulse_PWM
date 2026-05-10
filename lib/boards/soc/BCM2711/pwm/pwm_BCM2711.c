#include "include/pwm_BCM2711.h"
#include "../../include/pwm.h"
#include <stddef.h>

const pwm_ops_t bcm2711_pwm_ops = {
    .run = NULL
};

void bcm2711_pwm_init(void) {
    pwm = &bcm2711_pwm_ops;
}
