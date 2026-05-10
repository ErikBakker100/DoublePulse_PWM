#include "include/core1.h"
#include "../general/include/stdlib.h"
#include "../general/include/config.h"
#include "../boards/soc/include/gpio.h"
#include "../boards/soc/include/interrupts.h"
#include "../boards/soc/cpu/include/cpu.h"
#include "../boards/soc/include/pwm.h"

void mailbox0(uint32_t data) {
    dmb();
    pwm->run();
    dmb();
}
