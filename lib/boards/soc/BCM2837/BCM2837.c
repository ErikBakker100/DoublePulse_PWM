#include "include/BCM2837.h"
#include "gpio/include/gpio_BCM2837.h"
#include "uart/include/uart_BCM2837.h"
#include "interrupts/include/interrupts_BCM2837.h"
#include "mailbox/include/mailbox_BCM2837.h"
#include "timers/include/timers_BCM2837.h"
#include "pwm/include/pwm_BCM2837.h"
#include "dma/include/dma_BCM2837.h"

volatile bcm2835_sys_timer_regs_t *SYS_TMR_2837;
volatile bcm2835_dma_ctrl_regs_t *DMA00_2837;
volatile bcm2835_dma_ctrl_regs_t *DMA01_2837;
volatile bcm2835_dma_ctrl_regs_t *DMA02_2837;
volatile bcm2835_dma_ctrl_regs_t *DMA03_2837;
volatile bcm2835_dma_ctrl_regs_t *DMA04_2837;
volatile bcm2835_dma_ctrl_regs_t *DMA05_2837;
volatile bcm2835_dma_ctrl_regs_t *DMA06_2837;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA07_2837;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA08_2837;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA09_2837;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA10_2837;
volatile bcm2835_dma_4_ctrl_regs_t *DMA11_2837;
volatile bcm2835_dma_4_ctrl_regs_t *DMA12_2837;
volatile bcm2835_dma_4_ctrl_regs_t *DMA13_2837;
volatile bcm2835_dma_4_ctrl_regs_t *DMA14_2837;
volatile bcm2835_dma_4_ctrl_regs_t *DMA15_2837;
volatile bcm2835_dma_irq_stat_reg_t *DMAIRQ_2837;
volatile bcm2835_dma_enable_reg_t *DMAEN_2837;
volatile bcm2835_ic_regs_t *IC_2837;
volatile bcm2835_arm_timer_regs_t *ARM_TMR_2837;
volatile bcm2835_cm_cc_regs_t *CM_2837;
volatile bcm2835_gpio_regs_t *GPIO_2837;
volatile bcm2835_uart_regs_t *UART0_2837;                 // PL011 UART
volatile bcm2835_sdhost_regs_t *SDHOST_2837;
volatile bcm2835_pcm_regs_t *PCM_2837;
volatile bcm2835_spi_regs_t *SPI0_2837;
volatile bcm2835_i2c_regs_t *I2C0_2837;
volatile bcm2835_pwm_regs_t *PWM0_2837;
volatile bcm2835_i2c_spi_slave_regs_t *I2C_SPI_SLAVE_2837;
volatile bcm2835_aux_regs_t *AUX_2837;
volatile bcm2835_mu_regs_t *MU_2837;
volatile bcm2835_aux_spi_regs_t *SPI1_2837;
volatile bcm2835_aux_spi_regs_t *SPI2_2837;
volatile bcm2835_emmc_regs_t *EMMC_2837;
volatile bcm2835_i2c_regs_t *I2C1_2837;
volatile bcm2835_usb_regs_t *USB_2837;
volatile bcm2836_core_tmr_regs_t *CORE_TMR_2837;
volatile bcm2836_lic_routing_regs_t *LIC_ROUT_2837;
volatile bcm2836_axi_regs_t *AXI_2837;
volatile bcm2836_local_tmr_regs_t *LOC_TMR_2837;
volatile bcm2836_core_tmr_ctrl_regs_t *CORE_TMR_CTRL_2837;
volatile bcm2836_core_mailbox_ctrl_regs_t *CORE_MB_CTRL_2837;
volatile bcm2836_isr_regs_t *ISR_2837;
volatile bcm2836_al_mailboxes_regs_t *MAILBOX_2837;    // ARM Local Mailboxes

void BCM2837_init(const soc_t *mmio) {
    SYS_TMR_2837 = (bcm2835_sys_timer_regs_t *)(mmio->data.phys_base + 0x3000);
    DMA00_2837 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7000);
    DMA01_2837 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7100);
    DMA02_2837 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7200);
    DMA03_2837 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7300);
    DMA04_2837 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7400);
    DMA05_2837 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7500);
    DMA06_2837 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7600);
    DMA07_2837 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7700);
    DMA08_2837 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7800);
    DMA09_2837 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7900);
    DMA10_2837 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7A00);
    DMA11_2837 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7B00);
    DMA12_2837 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7C00);
    DMA13_2837 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7D00);
    DMA14_2837 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7E00);
    DMA15_2837 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7F00);
    DMAIRQ_2837 = (volatile bcm2835_dma_irq_stat_reg_t *)(mmio->data.phys_base + 0x7FE0);
    DMAEN_2837 = (volatile bcm2835_dma_enable_reg_t *)(mmio->data.phys_base + 0x7FF0);
    IC_2837 = (volatile bcm2835_ic_regs_t *)(mmio->data.phys_base + 0xB200);
    ARM_TMR_2837 = (volatile bcm2835_arm_timer_regs_t *)(mmio->data.phys_base + 0xB400);
    CM_2837 = (volatile bcm2835_cm_cc_regs_t*)(mmio->data.phys_base + 0x101070);
    GPIO_2837 = (bcm2835_gpio_regs_t *)(mmio->data.phys_base + 0x200000);
    UART0_2837 = (volatile bcm2835_uart_regs_t *)(mmio->data.phys_base + 0x201000);
    PCM_2837 = (volatile bcm2835_pcm_regs_t *)(mmio->data.phys_base + 0x203000);
    SPI0_2837 = (volatile bcm2835_spi_regs_t *)(mmio->data.phys_base + 0x204000);
    I2C0_2837 = (volatile bcm2835_i2c_regs_t *)(mmio->data.phys_base + 0x205000);
    PWM0_2837 = (volatile bcm2835_pwm_regs_t *)(mmio->data.phys_base + 0x20C000);
    I2C_SPI_SLAVE_2837 = (volatile bcm2835_i2c_spi_slave_regs_t *)(mmio->data.phys_base + 0x214000);
    AUX_2837 = (bcm2835_aux_regs_t *)(mmio->data.phys_base + 0x215000);
    MU_2837 = (bcm2835_mu_regs_t *)(mmio->data.phys_base + 0x215000 + 0x40);
    SPI1_2837 = (volatile bcm2835_aux_spi_regs_t *)(mmio->data.phys_base + 0x215000 + 0x80);
    SPI2_2837 = (volatile bcm2835_aux_spi_regs_t *)(mmio->data.phys_base + 0x215000 + 0xC0);
    EMMC_2837 = (volatile bcm2835_emmc_regs_t *)(mmio->data.phys_base + 0x300000);
    USB_2837 = (volatile bcm2835_usb_regs_t *)(mmio->data.phys_base + 0x980000);
    CORE_TMR_2837 = (volatile bcm2836_core_tmr_regs_t *)(mmio->data.local_periph_base + 0x44);
    LIC_ROUT_2837 = (volatile bcm2836_lic_routing_regs_t *)(mmio->data.local_periph_base + 0x0C);
    AXI_2837 = (volatile bcm2836_axi_regs_t *)(mmio->data.local_periph_base + 0x2C);
    LOC_TMR_2837 = (volatile bcm2836_local_tmr_regs_t *)(mmio->data.local_periph_base + 0x34);
    CORE_TMR_CTRL_2837 = (volatile bcm2836_core_tmr_ctrl_regs_t *)(mmio->data.local_periph_base + 0x40);
    CORE_MB_CTRL_2837 = (volatile bcm2836_core_mailbox_ctrl_regs_t *)(mmio->data.local_periph_base + 0x50);
    ISR_2837 = (volatile bcm2836_isr_regs_t *)(mmio->data.local_periph_base + 0x60);
    MAILBOX_2837 = (volatile bcm2836_al_mailboxes_regs_t *)(mmio->data.local_periph_base + 0x80);

    SYS_TMR_2837->CS = 0; // Clear timer control/status register
    SYS_TMR_2837->C[0] = 0;
    SYS_TMR_2837->C[1] = 0;
    SYS_TMR_2837->C[2] = 0;
    SYS_TMR_2837->C[3] = 0; // Clear timer counter register

    bcm2837_gpio_init();
    bcm2837_interrupts_init();
    bcm2837_mailbox_init();
    bcm2837_timer_init();
    bcm2837_uart_init();
    bcm2837_pwm_init();
    bcm2837_dma_init();
}

