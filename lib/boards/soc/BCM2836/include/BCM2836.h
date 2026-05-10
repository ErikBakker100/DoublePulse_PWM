#pragma once
#include <stdint.h>
#include "../../BCM2835/include/BCM2835.h"
#include "../../include/soc.h"

//
// System Timer, base address at mmio_base + 0x003000
//
// For registers see BCM2835.h
extern volatile bcm2835_sys_timer_regs_t *SYS_TMR_2836;

//
// DMA Direct Memory Access, base address at mmio_base + 0x007000 - 0x007F00
//
// For registers see BCM2835.h
extern volatile bcm2835_dma_ctrl_regs_t *DMA00_2836;
extern volatile bcm2835_dma_ctrl_regs_t *DMA01_2836;
extern volatile bcm2835_dma_ctrl_regs_t *DMA02_2836;
extern volatile bcm2835_dma_ctrl_regs_t *DMA03_2836;
extern volatile bcm2835_dma_ctrl_regs_t *DMA04_2836;
extern volatile bcm2835_dma_ctrl_regs_t *DMA05_2836;
extern volatile bcm2835_dma_ctrl_regs_t *DMA06_2836;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA07_2836;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA08_2836;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA09_2836;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA10_2836;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA11_2836;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA12_2836;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA13_2836;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA14_2836;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA15_2836;

//
// DMA irq status register, base address at mmio_base + 0x007FE0
//
// For registers see BCM2835.h
extern volatile bcm2835_dma_irq_stat_reg_t *DMAIRQ_2836;

//
// DMA Enable register, base address at mmio_base + 0x007FF0
//
// For registers see BCM2835.h
extern volatile bcm2835_dma_enable_reg_t *DMAEN_2836;

//
// Interrupt controller, base address at mmio_base + 0x00B200
//
// For registers see BCM2835.h
extern volatile bcm2835_ic_regs_t *IC_2836;

//
// ARM Timer, base address at mmio_base + 0x00B400
//
// For registers see BCM2835.h
extern volatile bcm2835_arm_timer_regs_t *ARM_TMR_2836;

//
// 3 x Clock Manager General Purpose Clocks Control, base address at mmio_base + 0x101070 + 1 PWM Clock Manager Control at mmio_base + 0x1010A0
//
// For registers see BCM2835.h
extern volatile bcm2835_cm_cc_regs_t *CM_2836;

//
// General Purpose I/O (GPIO), base address at mmio_base + 0x200000
//
// For registers see BCM2835.h
extern volatile bcm2835_gpio_regs_t *GPIO_2836;

//
// PL011 UART0, base address at mmio_base + 0x201000
//
// For registers see BCM2835.h
extern volatile bcm2835_uart_regs_t *UART0_2836;

//
// SDHOST Controller (SD Card), base address at mmio_base + 0x202000
//
// For registers see BCM2835.h
extern volatile bcm2835_sdhost_regs_t *SDHOST_2836;

//
// PCM audio interface, base address at mmio_base + 0x203000
//
// For registers see BCM2835.h
extern volatile bcm2835_pcm_regs_t *PCM_2836;

//
// SPI Serial Peripheral Interface, base address at mmio_base + 0x204000
//
// For registers see BCM2835.h
extern volatile bcm2835_spi_regs_t *SPI0_2836;

//
// I2C0, base address at mmio_base + 0x205000
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_regs_t *I2C0_2836;

//
// Pulse Width Modulator, base address at mmio_base + 0x20C000
//
// For registers see BCM2835.h
extern volatile bcm2835_pwm_regs_t *PWM0_2836;

//
// I2C/SPI SLAVE, base address at mmio_base + 0x214000
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_spi_slave_regs_t *I2C_SPI_SLAVE_2836;

//
// AUX registers, base address at mmio_base + 0x215000
//
// For registers see BCM2835.h
extern volatile bcm2835_aux_regs_t *AUX_2836;

//
// Mini UART, base address at mmio_base + 0x215040
//
// For registers see BCM2835.h
extern volatile bcm2835_mu_regs_t *MU_2836;

//
// SPI1, Universal SPI Master, base address (BA) at mmio_base + 0x215000 + 0x80
// SPI2, base address at mmio_base + 0x215000 + 0xC0
//
// For registers see BCM2835.h
extern volatile bcm2835_aux_spi_regs_t *SPI1_2836; // SPI 1 base address pointer
extern volatile bcm2835_aux_spi_regs_t *SPI2_2836; // SPI 2 base address pointer

//
// External Mass Media Controller (SD Card), base address at mmio_base + 0x300000
//
// For registers see BCM2835.h
extern volatile bcm2835_emmc_regs_t *EMMC_2836;          // EMMC base address pointer

//
// I2C1, base address at mmio_base + 0x804000
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_regs_t *I2C1_2836;

//
// USB Controller, base address at mmio_base + 0x980000
//
// For registers see BCM2835.h
extern volatile bcm2835_usb_regs_t *USB_2836;

//
// Core Timer, base address at mmio_base + 0x40000000
//
typedef struct {
    volatile uint32_t ARM_CONTROL;          // 0x00
    uint32_t reserved1[1];
    volatile uint32_t PRESCALER;            // 0x08 Core timer prescaler 
    uint32_t reserved2[4];                  // 0x0C-0x18
    volatile uint32_t TIMER_LS;             // 0x1C Core timer access LS 32 bits
    volatile uint32_t TIMER_MS;             // 0x20 Core timer access MS 32 bits
    volatile uint32_t INT_ROUTING;          // 0x24 Local Interrupt 0 [1-7] routing
} bcm2836_core_tmr_regs_t;
extern volatile bcm2836_core_tmr_regs_t *CORE_TMR_2836;

//
// Local Interrupt Controller, base address at mmio_base + 0x40000000 + 0x0C
//
typedef struct {
    volatile uint32_t GPU_INT_ROUTING;      // 0x0C GPU interrupts routing
    volatile uint32_t PM_ROUTING_SET;       // 0x10 Performance Monitor Interrupts routing-set
    volatile uint32_t PM_ROUTING_CLR;       // 0x14 Performance Monitor Interrupts routing-clear
} bcm2836_lic_routing_regs_t;
extern volatile bcm2836_lic_routing_regs_t *LIC_ROUT_2836;

//
// AXI registers, base address at mmio_base + 0x40000000 + 0x2C
//
typedef struct {
    uint32_t reserved1[1];
    volatile uint32_t AXI_COUNT;            // 0x2C Axi outstanding counters
    volatile uint32_t AXI_IRQ;              // 0x30 Axi outstanding IRQ
    uint32_t reserved2[1];
} bcm2836_axi_regs_t;
extern volatile bcm2836_axi_regs_t *AXI_2836;

//
// Local Timer, base address at mmio_base + 0x40000000 + 0x34
//
typedef struct {
    volatile uint32_t TIMER_CNTRL;          // 0x34 Local timer control & status
    volatile uint32_t TIMER_WRITE;          // 0x38 Local timer write flags
#define LOCAL_TIMER_IRQ         (1 << 29)
} bcm2836_local_tmr_regs_t;
extern volatile bcm2836_local_tmr_regs_t *LOC_TMR_2836;

//
// Core Timers Interrupt control registers, base address at mmio_base + 0x40000000 + 0x40
//
typedef struct {
    volatile uint32_t TIMER_CNTRL[4];        // 0x40-4C Core0-3 timers Interrupt control
#define TIMER0_IRQ              (1 << 0)
#define TIMER1_IRQ              (1 << 1)
#define TIMER2_IRQ              (1 << 2)
#define TIMER3_IRQ              (1 << 3)
#define TIMER0_FIQ              (1 << 4)
#define TIMER1_FIQ              (1 << 5)
#define TIMER2_FIQ              (1 << 6)
#define TIMER3_FIQ              (1 << 7)
} bcm2836_core_tmr_ctrl_regs_t;
extern volatile bcm2836_core_tmr_ctrl_regs_t *CORE_TMR_CTRL_2836;

//
// Core Mailbox Interrupt control registers, base address at mmio_base + 0x40000000 + 0x50
//
typedef struct {
    volatile uint32_t MAILBOX_CNTRL[4];     // 0x50-0x5C Core0-3 Mailboxes Interrupt control
#define MBOX0_IRQ               (1 << 0)
#define MBOX1_IRQ               (1 << 1)
#define MBOX2_IRQ               (1 << 2)
#define MBOX3_IRQ               (1 << 3)
#define MBOX0_FIQ               (1 << 4)
#define MBOX1_FIQ               (1 << 5)
#define MBOX2_FIQ               (1 << 6)
#define MBOX3_FIQ               (1 << 7)
} bcm2836_core_mailbox_ctrl_regs_t;
extern volatile bcm2836_core_mailbox_ctrl_regs_t *CORE_MB_CTRL_2836;

//
// Interrrupt source registers, base address at 0x40000000 + 0x60
//
typedef struct {
    volatile uint32_t IRQ_SOURCE[4];        // 0x60 Core0-3 IRQ Source
    volatile uint32_t FIQ_SOURCE[4];        // 0x70 Core0 FIQ Source
//  Core interrupt sources
#define INT_SRC_TIMER0          (1 << 0)    // CNTPS Secure physical timer
#define INT_SRC_TIMER1          (1 << 1)    // CNTPS Non-secure physical timer
#define INT_SRC_TIMER2          (1 << 2)    // CNTHP Hypervisor timer
#define INT_SRC_TIMER3          (1 << 3)    // CNTV Virtual timer
#define INT_SRC_MBOX0           (1 << 4)
#define INT_SRC_MBOX1           (1 << 5)
#define INT_SRC_MBOX2           (1 << 6)
#define INT_SRC_MBOX3           (1 << 7)
#define INT_SRC_GPU             (1 << 8)
#define INT_SRC_PMU             (1 << 9)
#define INT_AXI                 (1 << 10)
#define INT_SRC_LOCAL_TIMER     (1 << 11) // Local timer interrupt
} bcm2836_isr_regs_t;
extern volatile bcm2836_isr_regs_t *ISR_2836;

//
// Mailboxes, peripherals base address + 0x000080
//
typedef struct {
// Mailbox write-set registers (Write only)
// A write-set register allows you to set additional bits high. Bits which were already high are not affected.
// You set a bit high by writing the value '1' to it. Everywhere you write a '0' bit the original register contents
// remains unchanged.
    volatile uint32_t MBOX_SET[16];         // 0x80-0xBC Mailbox 0 Core0 Set Register
// Mailbox write-clear registers (Read & Write)
// A write-clear register allows you to set additional bits low. Bits which were already low are not affected.
// You set a bit low by writing the value '1' to it. Everywhere you write a '0' bit the original register contents
// remains unchanged. Beware that you write a one to get a zero!
    volatile uint32_t MBOX_CLR[16];         // 0xC0-0xFC Mailbox 00 Read & Clear Bit Register
} bcm2836_al_mailboxes_regs_t;
extern volatile bcm2836_al_mailboxes_regs_t *MAILBOX_2836;

// Initializes the BCM2836 peripherals base address pointers
void BCM2836_init(const soc_t  *);
