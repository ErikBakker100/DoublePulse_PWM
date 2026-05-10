#pragma once
#include <stdint.h>
#include "../../include/soc.h"
#include "../../BCM2835/include/BCM2835.h"
#include "../../BCM2836/include/BCM2836.h"
#include "../../BCM2837/include/BCM2837.h"

//
// System Timer, base address at mmio_base + 0x003000
//
// For registers see BCM2835.h
extern volatile bcm2835_sys_timer_regs_t *SYS_TMR_2711;

//
// DMA Direct Memory Access (0 - 15), base address at mmio_base + 0x007000 - 0x007F00
//
// For registers see BCM2835.h

//
// DMA irq status register, base address at mmio_base + 0x007FE0
//
// For registers see BCM2835.h

//
// DMA Enable register, base address at mmio_base + 0x007FF0
//
// For registers see BCM2835.h

//
// ARMC IRQ Interrupt Registers, base address at mmio_base + 0x00B200 - 0x00B2E8
//
typedef struct {
    volatile uint32_t IRQ_PENDING[3];       // 0x00 - 0x08 ARM Core 0 IRQ Enabled Interrupt Pending bits [31:0], [63:32] en [79:64] 
    uint32_t reserved0[1];
    volatile uint32_t IRQ_SET_EN[3];        // 0x10 - 0x18 Write to Set ARM Core 0 IRQ enable bits [31:0], [63:32] en [79:64]
    uint32_t reserved1[1];
    volatile uint32_t IRQ_CLR_EN[3];        // 0x20 - 0x28 Write to Clear ARM Core 0 IRQ enable bits [31:0], [63:32] en [79:64]
    uint32_t reserved2[1];
    volatile uint32_t IRQ_STATUS[3];        // 0x30 - 0x38 Interrupt Line bits [31:0], [63:32] en [79:64]
    uint32_t reserved3[1];  
} bcm2711_ic_irq_regs_t;

//
// ARMC FIQ Interrupt Registers, base address at mmio_base + 0x00B300 - 0x00B3E8
//
typedef struct {
    volatile uint32_t FIQ_PENDING[3];       // 0x00 - 0x08 ARM Core 0 FIQ Enabled Interrupt Pending bits [31:0], [63:32] en [79:64] 
    uint32_t reserved0[1];
    volatile uint32_t FIQ_SET_EN[3];        // 0x10 - 0x18 Write to Set ARM Core 0 IRQ enable bits [31:0], [63:32] en [79:64]
    uint32_t reserved1[1];
    volatile uint32_t FIQ_CLR_EN[3];        // 0x20 - 0x28 Write to Clear ARM Core 0 IRQ enable bits [31:0], [63:32] en [79:64]
    uint32_t reserved2[1];
    volatile uint32_t FIQ_STATUS[3];        // 0x30 - 0x38 Interrupt Line bits [31:0], [63:32] en [79:64]
    uint32_t reserved3[1];
} bcm2711_ic_fiq_regs_t;

//
// Set Clear Interrupt sources, base address at mmio_base + 0x00B3F0
//
typedef struct {
    volatile uint32_t SWIRQ_SET;            // 0x00  Write to Set Software Interrupt sources
    volatile uint32_t SWIRQ_CLEAR;          // 0x04  Write to Clear Software Interrupt sources
} bcm2711_ic_sc_regs_t;

typedef struct {
    bcm2711_ic_irq_regs_t *ARMC_IRQ[4];
    bcm2711_ic_fiq_regs_t *ARMC_FIQ[4];
    bcm2711_ic_sc_regs_t *IC_SC;
} bcm2711_armc_regs_t;
extern volatile bcm2711_armc_regs_t *ARMC_2711;

//
// ARM Timer, base address at mmio_base + 0x00B400
//
// For registers see BCM2835.h
extern volatile bcm2835_arm_timer_regs_t *ARM_TMR_2711;

//
// 3 x Clock Manager General Purpose Clocks Control, base address at mmio_base + 0x101070 + 1 PWM Clock Manager Control at mmio_base + 0x1010A0
//
// For registers see BCM2835.h
extern volatile bcm2835_cm_cc_regs_t *CM_2711;

//
// General Purpose I/O (GPIO), base address at mmio_base + 0x200000
//
typedef struct {
    /* 0x00–0x14: Function Select Registers */
    volatile uint32_t FSEL[6];              // 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14
    uint32_t reserved0;                     // 0x18
    /* 0x1C–0x20: Pin Output Set */
    volatile uint32_t SET[2];               // 0x1C–0x20: Pin Output Set
    uint32_t reserved1;                     // 0x24
    /* 0x28–0x2C: Pin Output Clear */
    volatile uint32_t CLR[2];               // 0x28–0x2C: Pin Output Clear
    uint32_t reserved2;                     // 0x30
    /* 0x34–0x38: Pin Level */
    volatile uint32_t LEV[2];               // 0x34–0x38: Pin Level
    uint32_t reserved3;                     // 0x3C
    /* 0x40–0x44: Event Detect Status */
    volatile uint32_t EDS[2];               // 0x40–0x44: Event Detect Status
    uint32_t reserved4;                     // 0x48
    /* 0x4C–0x50: Rising Edge Detect Enable */
    volatile uint32_t REN[2];               // 0x4C–0x50: Rising Edge Detect Enable
    uint32_t reserved5;                     // 0x54
    /* 0x58–0x5C: Falling Edge Detect Enable */
    volatile uint32_t FEN[2];               // 0x58–0x5C: Falling Edge Detect Enable
    uint32_t reserved6;                     // 0x60
    /* 0x64–0x68: High Detect Enable */
    volatile uint32_t HEN[2];               // 0x64–0x68: High Detect Enable
    uint32_t reserved7;                     // 0x6C
    /* 0x70–0x74: Low Detect Enable */
    volatile uint32_t LEN[2];               // 0x70–0x74: Low Detect Enable
    uint32_t reserved8;                     // 0x78
    /* 0x7C–0x80: Async Rising Edge Detect */
    volatile uint32_t AREN[2];              // 0x7C–0x80: Async Rising Edge Detect
    uint32_t reserved9;                     // 0x84
    /* 0x88–0x8C: Async Falling Edge Detect */
    volatile uint32_t AFEN[2];              // 0x88–0x8C: Async Falling Edge Detect
    uint32_t reserved10[21];                // 0x90-0xE0
    volatile uint32_t  PUP_PDN_CNTRL_REG[4]; // 0xE4-0xF0 Pull-up/down Control
} bcm2711_gpio_regs_t;
extern volatile bcm2711_gpio_regs_t *GPIO_2711;

//
// PL011 UART0, base address at mmio_base + 0x201000
//
// For registers see BCM2835.h

//
// PL011 UART2, base address at mmio_base + 0x201400
//
// For registers see BCM2835.h
extern volatile bcm2835_uart_regs_t *UART2_2835;

//
// PL011 UART3, base address at mmio_base + 0x201600
//
// For registers see BCM2835.h
extern volatile bcm2835_uart_regs_t *UART3_2835;

//
// PL011 UART4, base address at mmio_base + 0x201800
//
// For registers see BCM2835.h
extern volatile bcm2835_uart_regs_t *UART4_2835;

//
// PL011 UART5, base address at mmio_base + 0x201A00
//
// For registers see BCM2835.h
extern volatile bcm2835_uart_regs_t *UART5_2835;

//
// PCM audio interface, base address at mmio_base + 0x203000
//
// For registers see BCM2835.h

//
// SPI0 Serial Peripheral Interface, base address at mmio_base + 0x204000
//
// For registers see BCM2835.h

//
// SPI3 Serial Peripheral Interface, base address at mmio_base + 0x204600
//
// For registers see BCM2835.h
extern volatile bcm2835_spi_regs_t *SPI3_2835;

//
// SPI4 Serial Peripheral Interface, base address at mmio_base + 0x204800
//
// For registers see BCM2835.h
extern volatile bcm2835_spi_regs_t *SPI4_2835;

//
// SPI5 Serial Peripheral Interface, base address at mmio_base + 0x204A00
//
// For registers see BCM2835.h
extern volatile bcm2835_spi_regs_t *SPI5_2835;

//
// SPI6 Serial Peripheral Interface, base address at mmio_base + 0x204C00
//
// For registers see BCM2835.h
extern volatile bcm2835_spi_regs_t *SPI6_2835;

//
// I2C0, base address at mmio_base + 0x205000
//
// For registers see BCM2835.h

//
// I2C3, base address at mmio_base + 0x205600
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_regs_t *I2C3_2835;

//
// I2C4, base address at mmio_base + 0x205800
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_regs_t *I2C4_2835;

//
// I2C5, base address at mmio_base + 0x205A00
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_regs_t *I2C5_2835;

//
// I2C6, base address at mmio_base + 0x205C00
//
// For registers see BCM2835.h
extern volatile bcm2835_i2c_regs_t *I2C6_2835;

//
// PWM0 Pulse Width Modulator, base address at mmio_base + 0x20C000
//
// For registers see BCM2835.h
extern volatile bcm2835_pwm_regs_t *PWM0_271;

//
// PWM1 Pulse Width Modulator, base address at mmio_base + 0x20C800
//
// For registers see BCM2835.h
extern volatile bcm2835_pwm_regs_t *PWM1_2835;

//
// AUX registers, base address at mmio_base + 0x215000
//
// For registers see BCM2835.h
extern volatile bcm2835_aux_regs_t *AUX_2711;

//
// Mini UART, base address at mmio_base + 0x215040
//
// For registers see BCM2835.h
extern volatile bcm2835_mu_regs_t *MU_2711;

//
// SPI1, Universal SPI Master, mmio_base + 0x215000 + 0x80
// SPI2, mmio_base + 0x215000 + 0xC0
//
typedef struct {
    volatile uint32_t CNTL_REG[2];          // 0x00-0x04
    volatile uint32_t STAT_REG;             // 0x08 Status register
    volatile uint32_t PEEK_REG;             // 0x0C 'Peek
    volatile uint32_t IO_REG[4];            // 0x10-1C
    volatile uint32_t TXHOLD_REG[4];        // 0x20-2C
} bcm2711_aux_spi_regs_t;
extern volatile bcm2711_aux_spi_regs_t *SPI1_2711;
extern volatile bcm2711_aux_spi_regs_t *SPI2_2711;

//
// Mailboxes, preripheral base address (0xff800000) + 0x000080
//
// For registers see BCM2836.h
extern volatile bcm2836_al_mailboxes_regs_t *MAILBOX_2711;

//
// GIC-400 Generic Interrupt Controller Distributor (GICD), Low Peripheral mode (32 bit) 0xFF841000, High Peripheral mode (64 bit) 0x4C0041000
// Detects and prioritizes interrupts, and forwards them to the target CPU interfaces.
//
typedef struct {
    volatile uint32_t CTLR;                 // 0x000        Distributor Control Register. If either, but not both, of the EnableGrp0 and EnableGrp1 bits is set to 1, and the highest priority pending 
                                            // interrupt is in the disabled group, the Distributor does not forward any pending interrupts to the CPU interfaces.
    volatile uint32_t TYPER;                // 0x004        Interrupt Controller Type Register. Configuration-dependent register that provides information about the GIC-400's configuration,
                                            // including the number of interrupt lines supported and the number of CPU interfaces implemented.
    volatile uint32_t IIDR;                 // 0x008        Distributor Implementer Identification Register
    uint32_t reserved0[29];                 // 0x00C-0x07C
    volatile uint32_t IGROUPR[16];          // 0x080-0x0BC  Interrupt Group Registers, only accessible by Secure access.
                                            // Control whether each interrupt is configured as Group 0 or Group 1. Using Group 0 interrupts as Secure interrupts (FIQ's and IRQ's), and Group 1 interrupts as Non-secure interrupts (IRQ's only).
                                            // The interrupt group affects whether the interrupt can be forwarded to the CPU interfaces and it also has an impact on later routing decisions in the CPU interfaces,
                                            // potentially including whether it is signaled to the processor as a FIQ or an IRQ exception request.
    uint32_t reserved1[16];                 // 0xC0-0x0FC
    volatile uint32_t ISENABLER[16];        // 0x100-0x13C  Interrupt Set-Enable Registers, 0x100 SGI's and PPI's, 0x104 SPI's. Writing a 1 to a bit in these registers enables the corresponding interrupt. Writing a 0 has no effect.
    uint32_t reserved2[16];                 // 0x140-0x17C
    volatile uint32_t ICENABLER[16];        // 0x180-0x1BC  Interrupt Clear-Enable Registers
    uint32_t reserved3[16];                 // 0x1C0-0x1FC
    volatile uint32_t ISPENDR[16];          // 0x200-0x23C  Interrupt Set-Pending Registers
    uint32_t reserved4[16];                 // 0x240-0x27C
    volatile uint32_t ICPENDR[16];          // 0x280-0x2BC  Interrupt Clear-Pending Registers
    uint32_t reserved5[16];                 // 0x2C0-0x2FC
    volatile uint32_t ISACTIVER[16];        // 0x300-0x33C  Interrupt Set-Active Registers
    uint32_t reserved6[16];                 // 0x340-0x37C
    volatile uint32_t ICACTIVER[16];        // 0x380-0x3BC  Interrupt Clear-Active Registers
    uint32_t reserved7[16];                 // 0x3C0-0x3FC
    volatile uint8_t  IPRIORITYR[1020];     // 0x400-0x7FB  Interrupt Priority Registers. The GIC-400 implements 32 priority levels in Secure state and 16 priority states in Non-secure state.
    uint32_t reserved8[1];                  // 0x7FC
#define CORE0 (1<<0)
#define CORE1 (1<<1)
#define CORE2 (1<<2)
#define CORE3 (1<<3)
#define CORE_ALL (CORE0 | CORE1 | CORE2 | CORE3)
    volatile uint8_t  ITARGETSR[1024];      // 0x800-0xBFC Interrupt Processor Targets Registers
    volatile uint32_t ICFGR[64];            // 0xC00-0xCFC Interrupt Configuration Registers
    volatile uint32_t PPISR;                // 0xD00 Private Peripheral Interrupt Status Register. Enables a processor to access the status of the PPI inputs on the Distributor. Private Peripheral Interrupt (PPI)
                                            // This is a peripheral interrupt that is specific to a single processor. Interrupt numbers ID0-ID31 are used for interrupts that are private to a CPU interface.
    volatile uint32_t SPISR[15];            // 0xD04-0xD3C Shared Peripheral Interrupt Status Registers. Enables a processor to access the status of the IRQS inputs on the Distributor.
                                            // Non-secure accesses can only read the status of Group 1 interrupts. Shared Peripheral Interrupt (SPI) This is a peripheral interrupt that the Distributor can route to any of a specified 
                                            // combination of processors.
    uint32_t reserved9[112];                // 0xD40-0xDFC
    volatile uint32_t SGIR;                 // 0xF00 Software-generated interrupt (SGI). This is an interrupt generated by software writing to a GICD_SGIR register in the GIC.
                                            // Bits 3:0 specify the interrupt ID of the SGI to be generated. Bits 25:24 target list filter, determines the processors to which the SGI is sent. Bits 23:16 specify the CPU targets for the SGI.
    uint32_t reserved10[3];                 // 0xF04-0xF0C
    volatile uint32_t CPENDSGIR[4];         // 0xF10-0xF1C  Clear-Pending Registers
    volatile uint32_t SPENDSGIR[4];         // 0xF20-0xF2C  Set-Pending Registers
    uint32_t reserved11[40];                // 0xF30-0xFCC
    volatile uint32_t PIDR4, PIDR5, PIDR6, PIDR7; // 0xFD0-0xFDC Identification registers
    volatile uint32_t PIDR0, PIDR1, PIDR2, PIDR3; // 0xFE0-0xFEC
    volatile uint32_t CIDR0, CIDR1, CIDR2, CIDR3; // 0xFF0-0xFFC
} bcm2711_int_gic_400_gicd_regs_t;
extern volatile bcm2711_int_gic_400_gicd_regs_t *INT_GICD_2711;

//
// GIC-400 Generic Interrupt Controller CPU Interface (GICC), Low Peripheral mode (32 bit) 0xFF842000, High Peripheral mode (64 bit) 0x4C0042000
// 1 instance for each processor in the SoC. Performs priority masking and preemption handling of physical interrupts, signals them to the 
// corresponding processor, and receives acknowledge and End of Interrupt (EOI) accesses from that processor.
//
typedef struct {
    volatile uint32_t CTLR;                 // 0x00 CPU Interface Control Register. If the Enable bit is set to 1, the CPU interface can signal interrupts 
                                            // to the processor and receive acknowledge and EOI accesses from the processor. If the Enable bit is set to 0,
                                            // the CPU interface does not signal any interrupts to the processor and it ignores any acknowledge or EOI accesses from the processor.
    volatile uint32_t PMR;                  // 0x04 Interrupt Priority Mask Register. The GIC-400 implements 32 priority levels in Secure state and 16 priority
                                            // states in Non-secure state. The PMR is used to mask interrupts based on their priority level.
    volatile uint32_t BPR;                  // 0x08 Binary Point
    volatile uint32_t IAR;                  // 0x0C Interrupt Acknowledge
    volatile uint32_t EOIR;                 // 0x10 End of Interrupt
    volatile uint32_t RPR;                  // 0x14 Running Priority
    volatile uint32_t HPPIR;                // 0x18 Highest Priority Pending
    volatile uint32_t ABPR;                 // 0x1C Aliased Binary Point
    volatile uint32_t AIAR;                 // 0x20 Aliased IAR
    volatile uint32_t AEOIR;                // 0x24 Aliased EOIR
    volatile uint32_t AHPPIR;               // 0x28 Aliased HPPIR
    uint32_t reserved0[41];                 // 0x2C-0xCC
    volatile uint32_t APR[4];               // 0xD0-0xDC Active Priorities
    volatile uint32_t NSAPR[4];             // 0xE0-0xEC Non-secure Active Priorities
    uint32_t reserved1[3];                  // 0xF0-0xFA
    volatile uint32_t IIDR;                 // 0xFC Interface Identification, Provides information about the implementer and revision of the CPU interface
    uint32_t reserved2[960];                // 0x100-0xFFC padding naar DIR
    volatile uint32_t DIR;                  // 0x1000 Deactivate Interrupt
} bcm2711_int_gic_400_gicc_regs_t;
extern volatile bcm2711_int_gic_400_gicc_regs_t *INT_GICC_2711 ;

//
// GIC-400 Generic Interrupt Controller Virtual Interface Control Registers(GICH), Low Peripheral mode (32 bit) 0xFF844000, High Peripheral mode (64 bit) 0x4C0044000
// 1 instance for each processor in the SoC. Allow the hypervisor to control the information presented to the virtual machines by the virtual CPU interface.
//
typedef struct {
    volatile uint32_t HCR;                  // 0x00 Hypervisor Control Register
    volatile uint32_t VTR;                  // 0x04 VGIC Type Register
    volatile uint32_t VMCR;                 // 0x08 Virtual Machine Control Register
    uint32_t reserved0;                     // 0x0C
    volatile uint32_t MISR;                 // 0x10 Maintenance Interrupt Status Register
    uint32_t reserved1[3];                  // 0x14-0x1C
    volatile uint32_t EISR0;                // 0x20 End of Interrupt Status Register 0
    volatile uint32_t EISR1;                // 0x24 End of Interrupt Status Register 1
    uint32_t reserved2[2];                  // 0x28-0x2C
    volatile uint32_t ELRSR0;               // 0x30 Empty List Register Status Register 0
    volatile uint32_t ELRSR1;               // 0x34 Empty List Register Status Register 1
    uint32_t reserved3[10];                 // 0x38-0x5C
    volatile uint32_t APR;                  // 0x60 Active Priorities Register
    uint32_t reserved4[3];                  // 0x64-0x6C
    volatile uint32_t LR[64];               // 0x70-0x16C List Registers (GIC-400 ondersteunt er meestal 4-8)
} bcm2711_int_gic_400_gich_regs_t;
extern volatile bcm2711_int_gic_400_gich_regs_t *INT_GICH_2711;

//
// GIC-400 Generic Interrupt Controller Virtual CPU Interface (GICV), Low Peripheral mode (32 bit) 0xFF846000, High Peripheral mode (64 bit) 0x4C0046000
// 1 instance for each processor in the SoC. Performs priority masking and preemption handling of virtual interrupts, signals them to virtual machines, and receives acknowledge and EOI accesses from those virtual machines.
extern volatile bcm2711_int_gic_400_gicc_regs_t *INT_GICV_2711;

//
// ARM Local Interrrupt registers, base address at (32bit) 0xff800000 (64bit) 0x4c0000000
//
typedef struct {
    volatile uint32_t ARM_CONTROL;          // 0x00
    volatile uint32_t reserved1[2];
    volatile uint32_t CORE_IRQ_CONTROL;     // 0x0C VideoCore Interrupt Control
    volatile uint32_t PMU_CONTROL_SET;      // 0x10  PMU Bit Set
    volatile uint32_t PMU_CONTROL_CLR;      // 0x14  PMU Bit Clear
    volatile uint32_t reserved2[3];
    volatile uint32_t PERI_IRQ_ROUTE0;      // 0x24 Peripheral Interrupt Routing (Bank 0)
    volatile uint32_t reserved3[2];
    volatile uint32_t AXI_QUIET_TIME ;      // 0x30 AXI Outstanding Transaction Time and IRQ Control
    volatile uint32_t L_TIMER_CNTRL;        // 0x34 Local timer control
    volatile uint32_t L_TIMER_IRQ;          // 0x38 Local Timer Reload and Interrupt
    volatile uint32_t reserved4[1];
// Timer interrupt control registers
    volatile uint32_t TIMER_CNTRL[4];       // 0x40-0x4C Core0-3 timers Interrupt control
// Mailbox interrupt control registers
    volatile uint32_t MAILBOX_CNTRL[4];     // 0x50-0x5C Core0-3 Mailboxes Interrupt control
// IRQ and FIQ source registers
    volatile uint32_t IRQ_SOURCE[4];        // 0x60-0x6C Core0-3 IRQ Source
    volatile uint32_t FIQ_SOURCE[4];        // 0x70-0x7C Core0-3 FIQ Source
} bcm2711_irqs_arm_local_regs_t;
extern volatile bcm2711_irqs_arm_local_regs_t *INT_ARM_LOCAL_2711;

// Initializes the BCM2711 peripherals base address pointers
void BCM2711_init(const soc_t *);
