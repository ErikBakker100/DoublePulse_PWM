#pragma once
#include <stdint.h>
#include "../../BCM2835/include/BCM2835.h"
#include "../../BCM2836/include/BCM2836.h"
#include "../../include/soc.h"

//
// System Timer, base address at mmio_base + 0x003000
//
// For registers see BCM2835.h
extern volatile bcm2835_sys_timer_regs_t *SYS_TMR_2837;

//
// DMA Direct Memory Access, base address at mmio_base + 0x007000 - 0x007F00
//
// For registers see BCM2835.h
extern volatile bcm2835_dma_ctrl_regs_t *DMA00_2837;
extern volatile bcm2835_dma_ctrl_regs_t *DMA01_2837;
extern volatile bcm2835_dma_ctrl_regs_t *DMA02_2837;
extern volatile bcm2835_dma_ctrl_regs_t *DMA03_2837;
extern volatile bcm2835_dma_ctrl_regs_t *DMA04_2837;
extern volatile bcm2835_dma_ctrl_regs_t *DMA05_2837;
extern volatile bcm2835_dma_ctrl_regs_t *DMA06_2837;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA07_2837;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA08_2837;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA09_2837;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA10_2837;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA11_2837;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA12_2837;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA13_2837;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA14_2837;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA15_2837;

//
// DMA irq status register, base address at mmio_base + 0x007FE0
//
// For registers see BCM2835.h
extern volatile bcm2835_dma_irq_stat_reg_t *DMAIRQ_2837;

//
// DMA Enable register, base address at mmio_base + 0x007FF0
//
// For registers see BCM2835.h
extern volatile bcm2835_dma_enable_reg_t *DMAEN_2837;

//
// Interrupt controller, base address at mmio_base + 0x00B200
//
// For registers see BCM2835.h
extern volatile bcm2835_ic_regs_t *IC_2837;

//
// ARM Timer, base address at mmio_base + 0x00B400
//
// For registers see BCM2835.h
extern volatile bcm2835_arm_timer_regs_t *ARM_TMR_2837;

//
// 3 x Clock Manager General Purpose Clocks Control, base address at mmio_base + 0x101070 + 1 PWM Clock Manager Control at mmio_base + 0x1010A0
//
// For registers see BCM2835.h
extern volatile bcm2835_cm_cc_regs_t *CM_2837;

//
// General Purpose I/O (GPIO), base address at mmio_base + 0x200000
//
// For registers see BCM2835.h
extern volatile bcm2835_gpio_regs_t *GPIO_2837;

//
// PL011 UART0, base address at mmio_base + 0x201000
//
// For registers see BCM2835.h
extern volatile bcm2835_uart_regs_t *UART0_2837;

//
// SDHOST Controller (SD Card), base address at mmio_base + 0x202000
//
// For registers see BCM2835.h
extern volatile bcm2835_sdhost_regs_t *SDHOST_2837;

//
// PCM audio interface, base address at mmio_base + 0x203000
//
// For registers see BCM2835.h
extern volatile bcm2835_pcm_regs_t *PCM_2837;

//
// SPI0 Serial Peripheral Interface, base address at mmio_base + 0x204000
//
// For registers see BCM2835.h
extern volatile bcm2835_spi_regs_t *SPI0_2837;

//
// I2C0, base address at mmio_base + 0x205000
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_regs_t *I2C0_2837;

//
// PWM0 Pulse Width Modulator, base address at mmio_base + 0x20C000
//
// For registers see BCM2835.h
extern volatile bcm2835_pwm_regs_t *PWM0_2837;

//
// I2C/SPI SLAVE, base address at mmio_base + 0x214000
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_spi_slave_regs_t *I2C_SPI_SLAVE_2837;

//
// AUX registers, base address at mmio_base + 0x215000
//
// For registers see BCM2835.h
extern volatile bcm2835_aux_regs_t *AUX_2837;

//
// Mini UART, base address at mmio_base + 0x215040
//
// For registers see BCM2835.h
extern volatile bcm2835_mu_regs_t *MU_2837;

//
// SPI1, Universal SPI Master, base address (BA) at mmio_base + 0x215000 + 0x80
// SPI2, base address at mmio_base + 0x215000 + 0xC0
//
// For registers see BCM2835.h
extern volatile bcm2835_aux_spi_regs_t *SPI1_2837; // SPI 1 base address pointer
extern volatile bcm2835_aux_spi_regs_t *SPI2_2837; // SPI 2 base address pointer

//
// EMMC External Mass Media Controller (SD Card), base address at mmio_base + 0x300000
//
// For registers see BCM2835.h
extern volatile bcm2835_emmc_regs_t *EMMC_2837;          // EMMC base address pointer

//
// I2C1, base address at mmio_base + 0x804000
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_regs_t *I2C1_2837;

//
// USB Controller, base address at mmio_base + 0x980000
//
// For registers see BCM2835.h
extern volatile bcm2835_usb_regs_t *USB_2837;

//
// Core Timer, base address at 0x40000000
//
// For registers see BCM2836.h
extern volatile bcm2836_core_tmr_regs_t *CORE_TMR_2837;

//
// Local Interrupt Controller, base address at 0x40000000 + 0x0C
//
// For registers see BCM2836.h
extern volatile bcm2836_lic_routing_regs_t *LIC_ROUT_2837;

//
// AXI registers, base address at 0x40000000 + 0x2C
//
// For registers see BCM2836.h
extern volatile bcm2836_axi_regs_t *AXI_2837;

//
// Local Timer, base address at 0x40000000 + 0x34
//
// For registers see BCM2836.h
extern volatile bcm2836_local_tmr_regs_t *LOC_TMR_2837;

//
// Core Timers Interrupt control registers, base address at 0x40000000 + 0x40
//
// For registers see BCM2836.h
extern volatile bcm2836_core_tmr_ctrl_regs_t *CORE_TMR_CTRL_2837;

//
// Core Mailbox Interrupt control registers, base address at 0x40000000 + 0x50
//
// For registers see BCM2836.h
extern volatile bcm2836_core_mailbox_ctrl_regs_t *CORE_MB_CTRL_2837;

//
// Interrrupt source registers, base address at 0x40000000 + 0x60
//
// For registers see BCM2836.h
extern volatile bcm2836_isr_regs_t *ISR_2837;

//
// Mailboxes, base address at 0x40000000 + 0x000080
//
// For registers see BCM2836.h
extern volatile bcm2836_al_mailboxes_regs_t *MAILBOX_2837;

// Initializes the BCM2837 address pointers
void BCM2837_init(const soc_t *);
