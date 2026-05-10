#include "include/BCM2835.h"
#include "gpio/include/gpio_BCM2835.h"
#include "uart/include/uart_BCM2835.h"
#include "timers/include/timers_BCM2835.h"
#include "mailbox/include/mailbox_BCM2835.h"
#include "interrupts/include/interrupts_BCM2835.h"
#include "pwm/include/pwm_BCM2835.h"

volatile bcm2835_sys_timer_regs_t *SYS_TMR_2835;
volatile bcm2835_dma_ctrl_regs_t *DMA00_2835;
volatile bcm2835_dma_ctrl_regs_t *DMA01_2835;
volatile bcm2835_dma_ctrl_regs_t *DMA02_2835;
volatile bcm2835_dma_ctrl_regs_t *DMA03_2835;
volatile bcm2835_dma_ctrl_regs_t *DMA04_2835;
volatile bcm2835_dma_ctrl_regs_t *DMA05_2835;
volatile bcm2835_dma_ctrl_regs_t *DMA06_2835;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA07_2835;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA08_2835;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA09_2835;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA10_2835;
volatile bcm2835_dma_4_ctrl_regs_t *DMA11_2835;
volatile bcm2835_dma_4_ctrl_regs_t *DMA12_2835;
volatile bcm2835_dma_4_ctrl_regs_t *DMA13_2835;
volatile bcm2835_dma_4_ctrl_regs_t *DMA14_2835;
volatile bcm2835_dma_4_ctrl_regs_t *DMA15_2835;
volatile bcm2835_dma_irq_stat_reg_t *DMAIRQ_2835;
volatile bcm2835_dma_enable_reg_t *DMAEN_2835;
volatile bcm2835_ic_regs_t *IC_2835;
volatile bcm2835_arm_timer_regs_t *ARM_TMR_2835;
volatile bcm2835_cm_cc_regs_t *CM_2835;
volatile bcm2835_gpio_regs_t *GPIO_2835;
volatile bcm2835_uart_regs_t *UART0_2835;   // PL011 UART
volatile bcm2835_sdhost_regs_t *SDHOST_2835;
volatile bcm2835_pcm_regs_t *PCM_2835;
volatile bcm2835_spi_regs_t *SPI0_2835;
volatile bcm2835_i2c_regs_t *I2C0_2835;
volatile bcm2835_pwm_regs_t *PWM0_2835;
volatile bcm2835_i2c_spi_slave_regs_t *I2C_SPI_SLAVE_2835;
volatile bcm2835_aux_regs_t *AUX_2835;
volatile bcm2835_mu_regs_t *MU_2835;                 // Mini UART
volatile bcm2835_aux_spi_regs_t *SPI1_2835;
volatile bcm2835_aux_spi_regs_t *SPI2_2835;
volatile bcm2835_emmc_regs_t *EMMC_2835;
volatile bcm2835_i2c_regs_t *I2C1_2835;
volatile bcm2835_usb_regs_t *USB_2835;

void BCM2835_init(soc_t *mmio) {
    SYS_TMR_2835 = (bcm2835_sys_timer_regs_t *)(mmio->data.phys_base + 0x3000);
    DMA00_2835 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7000);
    DMA01_2835 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7100);
    DMA02_2835 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7200);
    DMA03_2835 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7300);
    DMA04_2835 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7400);
    DMA05_2835 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7500);
    DMA06_2835 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7600);
    DMA07_2835 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7700);
    DMA08_2835 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7800);
    DMA09_2835 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7900);
    DMA10_2835 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7A00);
    DMA11_2835 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7B00);
    DMA12_2835 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7C00);
    DMA13_2835 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7D00);
    DMA14_2835 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7E00);
    DMA15_2835 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7F00);
    DMAIRQ_2835 = (volatile bcm2835_dma_irq_stat_reg_t *)(mmio->data.phys_base + 0x7FE0);
    DMAEN_2835 = (volatile bcm2835_dma_enable_reg_t *)(mmio->data.phys_base + 0x7FF0);
    IC_2835 = (volatile bcm2835_ic_regs_t *)(mmio->data.phys_base + 0xB200);
    ARM_TMR_2835 = (volatile bcm2835_arm_timer_regs_t *)(mmio->data.phys_base + 0xB400);
    CM_2835 = (volatile bcm2835_cm_cc_regs_t*)(mmio->data.phys_base + 0x101070);
    GPIO_2835 = (bcm2835_gpio_regs_t *)(mmio->data.phys_base + 0x200000);
    UART0_2835 = (volatile bcm2835_uart_regs_t *)(mmio->data.phys_base + 0x201000);
    SDHOST_2835 = (volatile bcm2835_sdhost_regs_t *)(mmio->data.phys_base + 0x202000);
    PCM_2835 = (volatile bcm2835_pcm_regs_t *)(mmio->data.phys_base + 0x203000);
    SPI0_2835 = (volatile bcm2835_spi_regs_t *)(mmio->data.phys_base + 0x204000);
    I2C0_2835 = (volatile bcm2835_i2c_regs_t *)(mmio->data.phys_base + 0x205000);
    PWM0_2835 = (volatile bcm2835_pwm_regs_t *)(mmio->data.phys_base + 0x20C000);
    I2C_SPI_SLAVE_2835 = (volatile bcm2835_i2c_spi_slave_regs_t *)(mmio->data.phys_base + 0x214000);
    AUX_2835 = (bcm2835_aux_regs_t *)(mmio->data.phys_base + 0x215000);
    MU_2835 = (bcm2835_mu_regs_t *)(mmio->data.phys_base + 0x215000 + 0x40);
    SPI1_2835 = (volatile bcm2835_aux_spi_regs_t *)(mmio->data.phys_base + 0x215000 + 0x80);
    SPI2_2835 = (volatile bcm2835_aux_spi_regs_t *)(mmio->data.phys_base + 0x215000 + 0xC0);
    I2C1_2835 = (volatile bcm2835_i2c_regs_t *)(mmio->data.phys_base + 0x804000);
    USB_2835 = (volatile bcm2835_usb_regs_t *)(mmio->data.phys_base + 0x980000);

    SYS_TMR_2835->CS = 0; // Clear timer control/status register
    SYS_TMR_2835->C[0] = 0;
    SYS_TMR_2835->C[1] = 0;
    SYS_TMR_2835->C[2] = 0;
    SYS_TMR_2835->C[3] = 0; // Clear timer counter registers

    bcm2835_gpio_init();
    bcm2835_interrupts_init();
    bcm2835_timer_init();
    bcm2835_uart_init();
    bcm2835_pwm_init();
}
