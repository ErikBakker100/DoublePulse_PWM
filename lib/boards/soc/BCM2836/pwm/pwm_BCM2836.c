#include "include/pwm_BCM2836.h"
#include "../../include/pwm.h"
#include<stddef.h>

const pwm_ops_t bcm2836_pwm_ops = {
    .run = NULL
};

void bcm2836_pwm_init(void) {
    pwm = &bcm2836_pwm_ops;
}
