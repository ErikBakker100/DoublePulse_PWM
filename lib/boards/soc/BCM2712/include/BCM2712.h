#pragma once
#include <stdint.h>
#include "../../include/soc.h"

/*
Block Bus       Type    Atomic  Access Address
sysinfo         APB     Y       0x40000000
syscfg          APB     Y       0x40008000
otp             APB     Y       0x4000c000
power           APB     Y       0x40010000
resets          APB     Y       0x40014000
clocks_main     APB     Y       0x40018000
clocks_video    APB     Y       0x4001c000
pll_sys         APB     Y       0x40020000
pll_audio       APB     Y       0x40024000
pll_video       APB     Y       0x40028000
uart0           APB     N       0x40030000
uart1           APB     N       0x40034000
uart2           APB     N       0x40038000
uart3           APB     N       0x4003c000
uart4           APB     N       0x40040000
uart5           APB     N       0x40044000
spi8            APB     N       0x4004c000
spi0            APB     N       0x40050000
spi1            APB     N       0x40054000
spi2            APB     N       0x40058000
spi3            APB     N       0x4005c000
spi4            APB     N       0x40060000
spi5            APB     N       0x40064000
i2c0            APB     N       0x40070000
i2c1            APB     N       0x40074000
i2c2            APB     N       0x40078000
i2c3            APB     N       0x4007c000
i2c4            APB     N       0x40080000
i2c5            APB     N       0x40084000
i2c6            APB     N       0x40088000
audio_in        APB     Y       0x40090000
audio_out       APB     Y       0x40094000
pwm0            APB     Y       0x40098000
pwm1            APB     Y       0x4009c000
i2s0            APB     N       0x400a0000
i2s1            APB     N       0x400a4000
i2s2            APB     N       0x400a8000
timer           APB     Y       0x400ac000
sdio0_cfg       APB     Y       0x400b0000
sdio1_cfg       APB     Y       0x400b4000
busfabric_monitor APB   Y       0x400c0000
busfabric_axishim APB   Y       0x400c4000
adc             APB     Y       0x400c8000
io_bank0        APB     Y       0x400d0000
io_bank1        APB     Y       0x400d4000
io_bank2        APB     Y       0x400d8000
sys_rio0        APB     Y       0x400e0000
sys_rio1        APB     Y       0x400e4000
sys_rio2        APB     Y       0x400e8000
pads_bank0      APB     Y       0x400f0000
pads_bank1      APB     Y       0x400f4000
pads_bank2      APB     Y       0x400f8000
pads_eth        APB     Y       0x400fc000
eth             APB     N       0x40100000
eth_cfg         APB     Y       0x40104000
pcie            APB     Y       0x40108000
mipi0_csidma    APB     N       0x40110000
mipi0_csihost   APB     N       0x40114000
mipi0_dsidma    APB     N       0x40118000
mipi0_dsihost   APB     N       0x4011c000
mipi0_cfg       APB     Y       0x40120000
mipi0_isp       APB     N       0x40124000
mipi1_csidma    APB     N       0x40128000
mipi1_csihost   APB     N       0x4012c000
mipi1_dsidma    APB     N       0x40130000
mipi1_dsihost   APB     N       0x40134000
mipi1_cfg       APB     Y       0x40138000
mipi1_isp       APB     N       0x4013c000
video_out_cfg   APB     Y       0x40140000
video_out_vec   APB     Y       0x40144000
video_out_dpi   APB     Y       0x40148000
xosc            APB     Y       0x40150000
watchdog        APB     Y       0x40154000
dma_tick        APB     Y       0x40158000
usbhost0_cfg    APB     Y       0x40160000
usbhost1_cfg    APB     Y       0x40164000
rosc0           APB     Y       0x40168000
rosc1           APB     Y       0x4016c000
vbusctrl        APB     Y       0x40170000
ticks           APB     Y       0x40174000
pio             APB     Y       0x40178000
sdio0           AHB     N       0x40180000
sdio1           AHB     N       0x40184000
dma             AHB     N       0x40188000
usbhost0        AXI3    N       0x40200000
usbhost1        AXI3    N       0x40300000
exac            AXI3    N       0x40400000
usbdev          AXI3    N       0x40500000
gpu             AXI3    N       0x40600000
*/

//
// General Purpose I/O (GPIO), base address at mmio_base + 0x200000
//
typedef struct {
    volatile uint32_t STATUS;               // 0x0000 status
    volatile uint32_t CTRL;                 // 0x0004 control including function select and overrides
} bcm2712_gpio_sc_regs_t;

typedef struct {
    volatile uint32_t INTE;                 // 0x0000 Interrupt Enable
    volatile uint32_t INTF;                 // 0x0004Interrupt Force
    volatile uint32_t INTS;                 // 0x0008 Interrupt status after masking & forcing
} bcm2712_gpio_irq_regs_t;

typedef struct {
    bcm2712_gpio_sc_regs_t SC[28];          // 0x0000-0x00DC
    uint32_t reserved0[4];                  // 0x00F0-0x00FC
    volatile uint32_t INTR;                 // 0x0100 Raw Interrupts
    bcm2712_gpio_irq_regs_t PROC[2];        // 0x0104-0x0118
    bcm2712_gpio_irq_regs_t PCIE;           // 0x011C-0x0124
} bcm2712_gpio_regs_t;

extern volatile bcm2712_gpio_regs_t *GPIO_2712;

//
// PL011 UART0, base address at 0x40030000
//

//
// PL011 UART1, base address at 0x40034000
//

//
// PL011 UART2, base address at 0x40038000
//

//
// PL011 UART3, base address at 0x4003C000
//

//
// PL011 UART4, base address at 0x40040000
//

//
// PL011 UART5, base address at 0x40044000
//

//
// RIO Registered IO, base address at ???
//
typedef struct {
    volatile uint32_t OUT;                  // 0x controls the GPIO output drive
    volatile uint32_t OE;                   // 0x controls the GPIO output drive enable
    volatile uint32_t NOSYNC_IN;            // 0x samples the GPIO inputs directly
    volatile uint32_t SYNC_IN;              // 0x samples the GPIO inputs, each synchronised with a 2-stage synchroniser to clk_sys
} bcm2712_gpio_rio_regs_t;

//
// PWM0 Pulse Width Modulator, base address at 0x40098000
//

typedef struct {
    volatile uint32_t CTRL;                 // 0x00 control register
    volatile uint32_t RANGE;                // 0x04
    volatile uint32_t PHASE;                // 0x08
    volatile uint32_t DUTY;                 // 0x0C
} bcm2712_pwm_chan_regs_t;

typedef struct {
    volatile uint32_t GLOBAL_CTRL;          // 0x00 PWM Control
    volatile uint32_t FIFO_CTRL ;           // 0x04 FIFO thresholding and status
    volatile uint32_t COMMON_RANGE;         // 0x08
    volatile uint32_t COMMON_DUTY;          // 0x0C
    volatile uint32_t DUTY_FIFO;            // 0x10
    volatile bcm2712_pwm_chan_regs_t CHAN[4]; // 0x14-0x50
    volatile uint32_t INTR;                 // 0x54
    volatile uint32_t INTE;                 // 0x58
    volatile uint32_t INTF;                 // 0x5C
    volatile uint32_t INTS;                 // 0x60
} bcm2712_pwm_regs_t;
extern volatile bcm2712_pwm_regs_t *PWM0_2712;

//
// PWM1 Pulse Width Modulator, base address at 0x4009C000
//
extern volatile bcm2712_pwm_regs_t *PWM1_2712;

//
// I2C0 two-wire serial interface, base address at 0x40070000
//

//
// I2C1 two-wire serial interface, base address at 0x40074000
//

//
// I2C2 two-wire serial interface, base address at 0x40078000
//

//
// I2C3 two-wire serial interface, base address at 0x4007C000
//

//
// I2C4 two-wire serial interface, base address at 0x40080000
//

//
// I2C5 two-wire serial interface, base address at 0x40084000
//

//
// I2C6 two-wire serial interface, base address at 0x40088000
//

//
// I2S0 Synopsys Designware I2S peripheral, revision 1.11a, base address at 0x400a0000
//

//
// I2S1 Synopsys Designware I2S peripheral, revision 1.11a, base address at 0x400a4000
//

//
// I2S1 Synopsys Designware I2S peripheral, revision 1.11a, base address at 0x400a8000
//

//
// Tick generators, base address at 0x
//
typedef struct {
    volatile uint32_t CTRL;                 // 0x0000
    volatile uint32_t CYCLES;               // 0x0004
    volatile uint64_t COUNT;                // 0x0008
} bcm2712_ticks_regs_t;
extern volatile bcm2712_ticks_regs_t *TICKS_TIMER_2712;
extern volatile bcm2712_ticks_regs_t *TICKS_WATCHDOG_2712;
extern volatile bcm2712_ticks_regs_t *TICKS_PROC_2712;
extern volatile bcm2712_ticks_regs_t *TICKS_DMA0_2712;
extern volatile bcm2712_ticks_regs_t *TICKS_DMA1_2712;
extern volatile bcm2712_ticks_regs_t *TICKS_BANK0_2712;
extern volatile bcm2712_ticks_regs_t *TICKS_BANK1_2712;
extern volatile bcm2712_ticks_regs_t *TICKS_BANK2_2712;

//
// DMA Ticks tuning, base address at 0x
//
typedef struct {
    volatile uint32_t EN;                 // 0x0000
    volatile uint32_t CTRL;               // 0x0004
} bcm2712_dma_ticks_regs_t;
extern volatile bcm2712_dma_ticks_regs_t *TICKS_DMA0_FT_2712;
extern volatile bcm2712_dma_ticks_regs_t *TICKS_DMA1_FT_2712;

//
// SDIO0 Synopsys MSHC peripheral v1.70a. Support SDIO v4.2 and eMMC v5.1, compliant with the SD Host Controller specification v4.20, base address at 0x0x40180000
//

//
// SDIO1 Synopsys MSHC peripheral v1.70a. Support SDIO v4.2 and eMMC v5.1, compliant with the SD Host Controller specification v4.20, base address at 0x0x40184000
//

//
// USB0 config Synopsys IP dwc_usb3, v3.30b. USB3.0 xHCI Host Controllers conforming to the Extensible Host Controller Interface Specification v1.2, base address at 0x40160000
//

//
// USB1 config, base address at 0x40164000
//

//
// USB0, base address at 0x40200000
//

//
// USB1, base address at 0x40300000
//

//
// PCIe PCI Express link. PCIe is a symmetric serial protocol, base address at 0x40300000
//
typedef struct {
    volatile uint32_t DBI;                  // 0x000 address fields for dbi access
    volatile uint32_t CTRL;                 // 0x004 miscellaneous control bits
    volatile uint32_t MSIX_CFG[64];         // 0x008 - 0x104
    volatile uint32_t INTSTATL;             // 0x108 Raw interrupt status [31:0]
    volatile uint32_t INTSTATH;             // 0x10C Raw interrupt status [63:32]
    volatile uint32_t PHY_TEST;             // 0x110 address fields for pcie phy_test access
    volatile uint32_t PHY_PARAM_CTRL[2];    // 0x114 - 0x118 phy parameter control
    volatile uint32_t PHY_CR_ACC_CTRL;      // 0x11C phy control-register access - control
    volatile uint32_t PHY_CR_ACC_DATA;      // 0x120 phy control-register access - read/write data
    volatile uint32_t LTSSM_STATE_NEW;      // 0x124 Link Training and Status State Machine (LTSSM) state
    volatile uint32_t LTSSM_STATE_FILTER[4];// 0x12C - 0x138 LTSSM state filter
    volatile uint32_t AXI_LOOKUP[16];       // 0x13C - 0x17C AXI address lookup entries   
    volatile uint32_t VDM_CONFIG[2];        // 0x180 - 0x184 VDM configuration registers   
    volatile uint32_t VDM_PANIC;            // 0x188   
    volatile uint32_t VDM_TEST;             // 0x18C
    volatile uint32_t VDM_HEADER;           // 0x190 vendor defined message header
    volatile uint32_t PM_CTRL;              // 0x194 power management control
    volatile uint32_t PM_STATUS;            // 0x198 power management status
    volatile uint32_t MONITOR[3];           // 0x19C - 0x1A4 internal signals for debug
    volatile uint32_t INTR;                 // 0x1A8 Raw Interrupts
    volatile uint32_t INTE;                 // 0x1AC Interrupt Enable
    volatile uint32_t INTF;                 // 0x1B0 Interrupt Force
    volatile uint32_t INTS;                 // 0x1B4 Interrupt status after masking & forcin
} bcm2712_pcie_regs_t;
extern volatile bcm2712_pcie_regs_t *PCIE_2712;

//
// Ethernet Cadence Gigabit Ethernet MAC (GEM_GXL 1p09), base address at 
// 
typedef struct {
    volatile uint32_t CTRL;                 // 0x000 General Ethernet control register
    volatile uint32_t STATUS;               // 0x004
    volatile uint32_t TSU_TIMER_CNT[3];     // 0x008 - 0x010
    volatile uint32_t CLKGEN;               // 0x014 Clock control, can be changed on-the-fly
    volatile uint32_t CLK2FC;               // 0x018
    volatile uint32_t INTR;                 // 0x01C Raw Interrupts
    volatile uint32_t INTE;                 // 0x020 Interrupt Enable
    volatile uint32_t INTF;                 // 0x024 Interrupt Force
    volatile uint32_t INTS;                 // 0x028 Interrupt status after masking & forcin
} bcm2712_eth_regs_t;
extern volatile bcm2712_eth_regs_t *ETH_2712;

//
// MIPI0 Video Encoder (VEC), together with the built-in Video DAC, base address at 0x40110000
// 

//
// MIPI1 Video Encoder (VEC), together with the built-in Video DAC, base address at 0x40128000
// 

// DMA, base address at 0x40188000
// 

//
// GIC-600 Redistributor (GICR) IRQ controller, base address at 
// 
typedef struct {
    // RD_base (Control frame)
    volatile uint32_t CTLR;            // 0x0000
    volatile uint32_t IIDR;            // 0x0004
    volatile uint64_t TYPER;           // 0x0008
    volatile uint32_t STATUSR;         // 0x0010
    volatile uint32_t WAKER;           // 0x0014 (Belangrijk voor power management)
    uint32_t reserved0[22];            // 0x0018-0x007C
    // SGI_base (meestal op offset 0x10000 binnen de Redistributor)
    uint32_t reserved_to_sgi[16320];   // Padding naar 0x10000
    volatile uint32_t IGROUPR0;        // 0x10080
    volatile uint32_t ISENABLER0;      // 0x10100 (Beheer PPI/SGI enable)
    volatile uint32_t ICENABLER0;      // 0x10180
    volatile uint32_t ISPENDR0;        // 0x10200
    volatile uint32_t ICPENDR0;        // 0x10280
    volatile uint32_t ISACTIVER0;      // 0x10300
    volatile uint32_t ICACTIVER0;      // 0x10380
    volatile uint8_t  IPRIORITYR[32];  // 0x10400
    volatile uint32_t ICFGR0;          // 0x10C00
    volatile uint32_t ICFGR1;          // 0x10C04
    volatile uint32_t IGRPMODR0;       // 0x10D00
    volatile uint32_t NSACR;           // 0x10E00
} bcm2712_int_gic_600_gicr_regs_t;
extern volatile bcm2712_int_gic_600_gicr_regs_t *INT_GICR_2712[4];

// Initializes the BCM27612 address pointers
void BCM2712_init(soc_t *);
