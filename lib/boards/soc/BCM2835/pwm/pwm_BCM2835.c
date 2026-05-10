#include "include/pwm_BCM2835.h"
#include "../../include/pwm.h"
#include <stddef.h>

const pwm_ops_t bcm2835_pwm_ops = {
    .run = NULL,
};

void bcm2835_pwm_init(void) {
    pwm = &bcm2835_pwm_ops;
}
