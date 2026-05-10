#include "include/BCM2711.h"
#include "gpio/include/gpio_BCM2711.h"
#include "uart/include/uart_BCM2711.h"
#include "interrupts/include/interrupts_BCM2711.h"
#include "mailbox/include/mailbox_BCM2711.h"
#include "timers/include/timers_BCM2711.h"
#include "pwm/include/pwm_BCM2711.h"

volatile bcm2835_sys_timer_regs_t *SYS_TMR_2711;
volatile bcm2835_dma_ctrl_regs_t *DMA00_2711;
volatile bcm2835_dma_ctrl_regs_t *DMA01_2711;
volatile bcm2835_dma_ctrl_regs_t *DMA02_2711;
volatile bcm2835_dma_ctrl_regs_t *DMA03_2711;
volatile bcm2835_dma_ctrl_regs_t *DMA04_2711;
volatile bcm2835_dma_ctrl_regs_t *DMA05_2711;
volatile bcm2835_dma_ctrl_regs_t *DMA06_2711;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA07_2711;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA08_2711;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA09_2711;
volatile bcm2835_dma_lite_ctrl_regs_t *DMA10_2711;
volatile bcm2835_dma_4_ctrl_regs_t *DMA11_2711;
volatile bcm2835_dma_4_ctrl_regs_t *DMA12_2711;
volatile bcm2835_dma_4_ctrl_regs_t *DMA13_2711;
volatile bcm2835_dma_4_ctrl_regs_t *DMA14_2711;
volatile bcm2835_dma_4_ctrl_regs_t *DMA15_2711;
volatile bcm2835_dma_irq_stat_reg_t *DMAIRQ_2711;
volatile bcm2835_dma_enable_reg_t *DMAEN_2711;
volatile bcm2711_armc_regs_t *ARMC_2711;
volatile bcm2835_arm_timer_regs_t *ARM_TMR_2711;
volatile bcm2835_cm_cc_regs_t *CM_2711;
volatile bcm2711_gpio_regs_t *GPIO_2711;
volatile bcm2835_uart_regs_t *UART0_2711;
volatile bcm2835_uart_regs_t *UART2_2711;
volatile bcm2835_uart_regs_t *UART3_2711;
volatile bcm2835_uart_regs_t *UART4_2711;
volatile bcm2835_uart_regs_t *UART5_2711;
volatile bcm2835_pcm_regs_t *PCM_2711;
volatile bcm2835_spi_regs_t *SPI0_2711;
volatile bcm2835_spi_regs_t *SPI3_2711;
volatile bcm2835_spi_regs_t *SPI4_2711;
volatile bcm2835_spi_regs_t *SPI5_2711;
volatile bcm2835_spi_regs_t *SPI6_2711;
volatile bcm2835_i2c_regs_t *I2C0_2711;
volatile bcm2835_i2c_regs_t *I2C3_2711;
volatile bcm2835_i2c_regs_t *I2C4_2711;
volatile bcm2835_i2c_regs_t *I2C5_2711;
volatile bcm2835_i2c_regs_t *I2C6_2711;
volatile bcm2835_pwm_regs_t *PWM0_2711;
volatile bcm2835_pwm_regs_t *PWM1_2711;
volatile bcm2835_aux_regs_t *AUX_2711;
volatile bcm2835_mu_regs_t *MU_2711;
volatile bcm2711_aux_spi_regs_t *SPI1_2711;
volatile bcm2711_aux_spi_regs_t *SPI2_2711;
volatile bcm2836_al_mailboxes_regs_t *MAILBOX_2711;
volatile bcm2711_irqs_arm_local_regs_t *INT_ARM_LOCAL_2711;
volatile bcm2711_int_gic_400_gicd_regs_t *INT_GICD_2711;
volatile bcm2711_int_gic_400_gicc_regs_t *INT_GICC_2711;
volatile bcm2711_int_gic_400_gich_regs_t *INT_GICH_2711;
volatile bcm2711_int_gic_400_gicc_regs_t *INT_GICV_2711;

void BCM2711_init(const soc_t *mmio) {
    SYS_TMR_2711 = (volatile bcm2835_sys_timer_regs_t *)(mmio->data.phys_base + 0x003000);
    DMA00_2711 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7000);
    DMA01_2711 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7100);
    DMA02_2711 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7200);
    DMA03_2711 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7300);
    DMA04_2711 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7400);
    DMA05_2711 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7500);
    DMA06_2711 = (volatile bcm2835_dma_ctrl_regs_t *)(mmio->data.phys_base + 0x7600);
    DMA07_2711 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7700);
    DMA08_2711 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7800);
    DMA09_2711 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7900);
    DMA10_2711 = (volatile bcm2835_dma_lite_ctrl_regs_t *)(mmio->data.phys_base + 0x7A00);
    DMA11_2711 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7B00);
    DMA12_2711 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7C00);
    DMA13_2711 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7D00);
    DMA14_2711 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7E00);
    DMA15_2711 = (volatile bcm2835_dma_4_ctrl_regs_t *)(mmio->data.phys_base + 0x7F00);
    DMAIRQ_2711 = (volatile bcm2835_dma_irq_stat_reg_t *)(mmio->data.phys_base + 0x7FE0);
    DMAEN_2711 = (volatile bcm2835_dma_enable_reg_t *)(mmio->data.phys_base + 0x7FF0);
    ARMC_2711 = (volatile bcm2711_armc_regs_t *)(mmio->data.phys_base + 0xB200);
    ARM_TMR_2711 = (volatile bcm2835_arm_timer_regs_t *)(mmio->data.phys_base + 0xB400);
    CM_2711 = (volatile bcm2835_cm_cc_regs_t*)(mmio->data.phys_base + 0x101070);
    GPIO_2711 = (volatile bcm2711_gpio_regs_t *)(mmio->data.phys_base + 0x200000);
    UART0_2711 = (volatile bcm2835_uart_regs_t *)(mmio->data.phys_base + 0x201000);
    UART2_2711 = (volatile bcm2835_uart_regs_t *)(mmio->data.phys_base + 0x201400);
    UART3_2711 = (volatile bcm2835_uart_regs_t *)(mmio->data.phys_base + 0x201600);
    UART4_2711 = (volatile bcm2835_uart_regs_t *)(mmio->data.phys_base + 0x201800);
    UART5_2711 = (volatile bcm2835_uart_regs_t *)(mmio->data.phys_base + 0x201A00);
    PCM_2711 = (volatile bcm2835_pcm_regs_t *)(mmio->data.phys_base + 0x203000);
    SPI0_2711 = (volatile bcm2835_spi_regs_t *)(mmio->data.phys_base + 0x204000);
    SPI3_2711 = (volatile bcm2835_spi_regs_t *)(mmio->data.phys_base + 0x204600);
    SPI4_2711 = (volatile bcm2835_spi_regs_t *)(mmio->data.phys_base + 0x204800);
    SPI5_2711 = (volatile bcm2835_spi_regs_t *)(mmio->data.phys_base + 0x204A00);
    SPI6_2711 = (volatile bcm2835_spi_regs_t *)(mmio->data.phys_base + 0x204C00);
    I2C0_2711 = (volatile bcm2835_i2c_regs_t *)(mmio->data.phys_base + 0x205000);
    I2C3_2711 = (volatile bcm2835_i2c_regs_t *)(mmio->data.phys_base + 0x205600);
    I2C4_2711 = (volatile bcm2835_i2c_regs_t *)(mmio->data.phys_base + 0x205800);
    I2C5_2711 = (volatile bcm2835_i2c_regs_t *)(mmio->data.phys_base + 0x211A9C);
    I2C6_2711 = (volatile bcm2835_i2c_regs_t *)(mmio->data.phys_base + 0x205C00);
    PWM0_2711 = (volatile bcm2835_pwm_regs_t *)(mmio->data.phys_base + 0x20C000);
    PWM1_2711 = (volatile bcm2835_pwm_regs_t *)(mmio->data.phys_base + 0x20C800);
    AUX_2711 = (volatile bcm2835_aux_regs_t *)(mmio->data.phys_base + 0x215000);
    MU_2711 = (volatile bcm2835_mu_regs_t *)(mmio->data.phys_base + 0x215040);
    SPI1_2711 = (volatile bcm2711_aux_spi_regs_t *)(mmio->data.phys_base + 0x215080);
    SPI2_2711 = (volatile bcm2711_aux_spi_regs_t *)(mmio->data.phys_base + 0x2150C0);
    // GIC-400 Interrupt controller, base = in low Peripheral mode (32 bit) 0xFF840000, in high Peripheral mode (64 bit) 0x4C0040
    INT_ARM_LOCAL_2711 = (volatile bcm2711_irqs_arm_local_regs_t *)(mmio->data.local_periph_base);
    INT_GICD_2711 = (volatile bcm2711_int_gic_400_gicd_regs_t *)(mmio->data.local_periph_base + 0x41000);
    INT_GICC_2711 = (volatile bcm2711_int_gic_400_gicc_regs_t *)(mmio->data.local_periph_base + 0x42000);
    INT_GICH_2711 = (volatile bcm2711_int_gic_400_gich_regs_t *)(mmio->data.local_periph_base + 0x44000);
    INT_GICV_2711 = (volatile bcm2711_int_gic_400_gicc_regs_t *)(mmio->data.local_periph_base + 0x45000);

    bcm2711_gpio_Init();
    bcm2711_interrupts_init();
    bcm2711_mailbox_init();
    bcm2711_timer_init();
    bcm2711_uart_init();
    bcm2711_pwm_init();
}
