#include "include/pwm_BCM2837.h"
#include "../dma/include/dma_BCM2837.h"
#include "../../include/pwm.h"
#include "../../include/gpio.h"
#include "../../../../general/include/stdlib.h"
#include "../../../../general/include/config.h"

#include <stdbool.h>
#include <stddef.h>

void bcm2837_pwm_set_pulses(volatile uint8_t* pulse_length, uint8_t channel) {
}

void bcm2837_pwm_run() {
    PWM0_2837->CTL = 0;                     // Disable the channel before we start setting it up.   
    PWM0_2837->CTL = PWM_CTL_CLRF;          // Clear the FIFO to reset the state of the channel.
    dmb();                                  // Data memory barrier to ensure that the write to the control register is completed.
    // set up the clock for the PWM signal.
    CM_2837->PWM.CTL = (CM_PASSWD | CM_CTL_KILL) & ~CM_CTL_ENAB; // Set kill bit to stop the clock generator
    while (BIT_IS_SET(CM_2837->PWM.CTL, CM_CTL_BUSY)); // wait till cycle is completed

    CM_2837->PWM.DIV = (CM_DIV_DIVI(16)) | CM_PASSWD; // Set the clock divider
    CM_2837->PWM.CTL = 0 | CM_CTL_SRC(CM_CLK_SRC_PLLD_PER) | CM_CTL_ENAB | CM_PASSWD;
    while (!BIT_IS_SET(CM_2837->PWM.CTL, CM_CTL_BUSY)); // Wait until the PWM clock is running.

    // set up the PWM channel for the specified pin.
    PWM0_2837->DMAC = 0 | PWM_DMAC_ENAB | PWM_DMAC_PANIC_LVL(7) | PWM_DMAC_DREQ_LVL(7); // Enable DMA for the channel, and set the panic and DREQ thresholds.
    PWM0_2837->STA = 0x1FFFF; // Clear the status register to reset all flags for the channel, since we don't know what state it is in from previous runs.
        
    uint32_t ctl = 0;                       // Control variable to hold the control register value for the PWM channel.
    uint32_t trigger_period = Intervals[0] + Intervals[1] + Intervals[2] + Intervals[3];
    uint32_t trigger_width = TRIGGER_PULSE_BITS;
    if (trigger_width >= trigger_period) {
        trigger_width = 1;
    }

    if (*pwm->channel) {
        PWM0_2837->RNG1 = 32;               // Set the range register to 32, since we are using a 32-bit bitstream for the PWM signal. This means that each 
                                            // bit in the bitstream will represent one cycle of the PWM signal, and the total length of the PWM signal will be 32 cycles.
        ctl |= PWM_CTL_MODE1;               // Set the mode bit to 1 to use serializer mode, which will allow us to write a stream of bits to the FIFO and have it 
                                            // output as a PWM signal.
        ctl |= PWM_CTL_USEF1;               // Set the use FIFO bit to 1 to enable the use of the FIFO for the channel.
//    ctl |= PWM_CTL_RPTL1;                 // Set the repeat last data bit to 1 to have the channel repeat the last data in the FIFO when it runs out of data.  
        PWM0_2837->RNG0 = trigger_period;
        PWM0_2837->DAT0 = 0x1;
        ctl |= PWM_CTL_MSEN0;
    }
    else { 
        PWM0_2837->RNG0 = 32;
        ctl |= PWM_CTL_MODE0;               // Set the mode bit to 1 to use serializer mode, which will allow us to write a stream of bits to the FIFO and have it output as a PWM signal.
        ctl |= PWM_CTL_USEF0;               // Set the use FIFO bit to 1 to enable the use of the FIFO for the channel.
//    ctl |= PWM_CTL_RPTL0;                 // Set the repeat last data bit to 1 to have the channel repeat the last data in the FIFO when it runs out of data.  
        PWM0_2837->RNG1 = trigger_period;
        PWM0_2837->DAT1 = trigger_width;
        ctl |= PWM_CTL_MSEN1;
    }
    PWM0_2837->CTL = ctl;                   // Configure FIFO/serializer mode before starting DMA.
    dmb();                                  // Ensure all data is visible before starting the DMA channel.
    bcm2837_dma_run();                      // Start DMA now PWM is ready so PWM DREQ paces FIFO writes.
    dmb();
    PWM0_2837->CTL = ctl | PWM_CTL_EN_CH0 | PWM_CTL_EN_CH1; // Enable pulse and trigger outputs together.
}

const pwm_ops_t bcm2837_pwm_ops = {
    .run = bcm2837_pwm_run,
};

void bcm2837_pwm_init(void) {
    pwm = &bcm2837_pwm_ops;
}
