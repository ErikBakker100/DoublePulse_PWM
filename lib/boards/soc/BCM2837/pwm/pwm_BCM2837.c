#include "include/pwm_BCM2837.h"
#include "../../include/dma.h"
#include "../../include/pwm.h"
#include "../../include/gpio.h"
#include "../../../../general/include/stdlib.h"
#include "../../../../general/include/config.h"

#include <stdbool.h>
#include <stddef.h>

void bcm2837_pwm_set_pulses(volatile uint8_t* pulse_length) {
}

void bcm2837_pwm_run() {
    PWM0_2837->CTL = 0;                                     // Disable the channels before we start setting it up.
    PWM0_2837->CTL = PWM_CTL_CLRF | PWM_CTL_USEF0;          // Clear the FIFO to reset the state of the channel and enable FIFO mode for channel 0.
    dmb();                                  // Data memory barrier to ensure that the write to the control register is completed.
    // set up the clock for the PWM signal.
    CM_2837->PWM.CTL = (CM_PASSWD | CM_CTL_KILL) & ~CM_CTL_ENAB; // Set kill bit to stop the clock generator
    while (BIT_IS_SET(CM_2837->PWM.CTL, CM_CTL_BUSY)); // wait till cycle is completed

    CM_2837->PWM.DIV = (CM_DIV_DIVI(16)) | CM_PASSWD; // Set the clock divider
    CM_2837->PWM.CTL = 0 | CM_CTL_SRC(CM_CLK_SRC_PLLD_PER) | CM_CTL_ENAB | CM_PASSWD;
    while (!BIT_IS_SET(CM_2837->PWM.CTL, CM_CTL_BUSY)); // Wait until the PWM clock is running.

    // set up the PWM channel.
    PWM0_2837->DMAC = 0 | PWM_DMAC_ENAB | PWM_DMAC_PANIC_LVL(7) | PWM_DMAC_DREQ_LVL(7); // Enable DMA for the channel, and set the panic and DREQ thresholds.
    PWM0_2837->STA = 0x1FFFF;               // Clear the status register to reset all flags, since we don't know what state it is in from previous runs.
        
    uint32_t ctl = 0;                       // Control variable to hold the control register value for the PWM channel.
    ctl |= PWM_CTL_MODE0;                   // Channel 0 serializer mode, so DMA/FIFO output can drive GPIO18.
    ctl |= PWM_CTL_USEF0;                   // Enable FIFO for channel 0.
//    ctl |= PWM_CTL_SBIT0;                   // Use MSB-first serial output for channel 0 to match bitbuffer layout.
    ctl |= PWM_CTL_MSEN1;                   // Channel 1 mark-space mode for the short trigger pulse on GPIO19.
    PWM0_2837->CTL = ctl;                   // Configure FIFO/serializer mode before starting DMA.

    PWM0_2837->RNG0 = 32;                   // 32-bit serializer words for channel 0.
    PWM0_2837->DAT0 = 0;                    // Not used for channel 0 serializer mode.

    dmb();                                  // Ensure all data is visible before starting the DMA channel.
    dma->run();                             // Start DMA now PWM is ready so PWM DREQ paces FIFO writes.
    dmb();
    // Now that DMA/make_bit_buffer may have adjusted Intervals[3], compute trigger period and set channel1 registers
    uint32_t trigger_period = (uint32_t)Intervals[0] + (uint32_t)Intervals[1] + (uint32_t)Intervals[2] + (uint32_t)Intervals[3];
    uint32_t trigger_width = 1; // minimal short pulse; keep small to mark the rising edge
    if (trigger_width >= trigger_period) trigger_width = 1;
    PWM0_2837->RNG1 = trigger_period;
    PWM0_2837->DAT1 = trigger_width;

    PWM0_2837->CTL = ctl | PWM_CTL_EN_CH0 | PWM_CTL_EN_CH1; // Enable pulse and trigger outputs together.
}

const pwm_ops_t bcm2837_pwm_ops = {
    .run = bcm2837_pwm_run,
};

void bcm2837_pwm_init(void) {
    pwm = &bcm2837_pwm_ops;
}
