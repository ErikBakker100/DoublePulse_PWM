#pragma once
#include <stdint.h>

typedef struct {
    void (*run)();
    /* For PWM only certain GPIO's can be used:
        GPIO 12 uses ALT0 and PWM channel 0,
        GPIO 13 uses ALT0 and PWM channel 1,
        GPIO 18 uses ALT5 and PWM channel 0,
        GPIO 19 uses ALT5 and PWM channel 1,
    */
} pwm_ops_t;
extern const pwm_ops_t *pwm;
