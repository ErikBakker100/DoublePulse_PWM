#pragma once
#include <stdint.h>
#include "DWC_OTG_CORE_IF.h"
#include "../../include/soc.h"
//
// System Timer, base address at mmio_base + 0x003000
//
typedef struct {
    volatile uint32_t CS;                   // 0x00 System Timer Control/Status
    volatile uint32_t CLO;                  // 0x04 System Timer Counter Lower 32 bits
    volatile uint32_t CHI;                  // 0x08 System Timer Counter Higher 32 bits
    volatile uint32_t C[4];                 // 0x0C-0x18 System Timer Compare 0-3
} bcm2835_sys_timer_regs_t;
extern volatile bcm2835_sys_timer_regs_t *SYS_TMR_2835;

//
// DMA Direct Memory Access, base address at mmio_base + 0x007000 - 0x007F00
//
/*  15 DMA Controller Registers
    
    Each DMA channel of a particular type has an identical register map, only the base address of each channel is different.
    There is a global enable register at the top of the Address map that can disable each DMA for powersaving.
    Only three registers in each channel’s register set are directly writeable (CS, CONBLK_AD and DEBUG). The other registers
    (TI, SOURCE_AD, DEST_AD, TXFR_LEN, STRIDE & NEXTCONBK) are automatically loaded from a Control Block data
    structure held in external memory. */

/*  Control Blocks (CB) are 8 words (256 bits) in length and must start at a 256-bit aligned address. The format of the
    different CB data structures in memory, are shown below.
    Each 32-bit word of the Control Block is automatically loaded into the corresponding 32-bit DMA Control Block register at
    the start of a DMA transfer. The descriptions of these registers also define the corresponding bit locations in the CB data
    structure in memory.*/

typedef struct {
    volatile uint32_t TI;                   // 0x00 Transfer Information
#define TI_INTEN       (1 << 0)             // Interrupt Enable, 1 = Generate an interrupt when the transfer described by the current 
                                            // Control Block completes. 0 = Do not generate an interrupt. 
#define TI_TDMODE      (1 << 1)             // 1 = interpret the TXFR_LEN register as YLENGTH number of transfers each of XLENGTH, 
                                            // and add the strides to the address after each transfer. 0 = Linear mode interpret
                                            // the TXFR register as a single transfer of total length in bytes {YLENGTH ,XLENGTH}.
#define TI_WAIT_RESP   (1 << 3)             // When set this makes the DMA wait until it receives the AXI write response for each write.
                                            // This ensures that multiple writes cannot get stacked in the AXI bus pipeline. 
                                            // 1= Wait for the write response to be received before proceeding. 0 = Don t wait; continue as soon as the write data is sent.
#define TI_DEST_INC    (1 << 4)             // Destination Address Increment. 1 = Destination address increments after each write. The address 
                                            // will increment by 4, if DEST_WIDTH=0 else by 32. 0 = Destination address does not change.
#define TI_DEST_WIDTH  (1 << 5)             // Destination Transfer Width. 1 = Use 128-bit. 0 = Use 32-bit destination write width.
#define TI_DEST_DREQ   (1 << 6)             // Control Destination Writes with DREQ. 1 = The DREQ selected by PERMAP will gate the 
                                            // destination writes. 0 = DREQ has no effect.
#define TI_DEST_IGNORE (1 << 7)             // Ignore Writes, 1 = Do not perform destination writes. 0 = Write data to destination.
#define TI_SRC_INC     (1 << 8)             // Source Address Increment. 1 = Source address increments after each read. The address
                                            // will increment by 4, if S_WIDTH=0 else by 32. 0 = Source address does not change. 
#define TI_SRC_WIDTH   (1 << 9)             // Source Transfer Width. 1 = Use 128-bit source read width. 0 = Use 32-bit source read width.
#define TI_SRC_DREQ    (1 << 10)            // Control Source Reads with DREQ. 1 = The DREQ selected by PER_MAP will gate the
                                            // source reads. 0 = DREQ has no effect.
#define TI_SRC_IGNORE  (1 << 11)            // Ignore Reads. 1 = Do not perform source reads. In addition, destination writes will 
                                            // zero all the write strobes. This is used for fast cache fill operations. 0 = Perform source reads.
#define TI_BURST_LENGTH (0xF << 12)         // Burst Transfer Length. Indicates the burst length of the DMA transfers. The DMA will attempt
                                            // to transfer data as bursts of this number of words. A value of zero will produce a single 
                                            // transfer. Bursts are only produced for specific conditions, see main text.
#define TI_PERMAP(x) (((x) & 0x1F) << 16)   // Peripheral Mapping. Indicates the peripheral number (1-31) whose ready signal shall be used 
                                            // to control the rate of the transfers, and whose panic signals will be output on the DMA AXI bus.
                                            // Set to 0 for a continuous un-paced transfer.
                                            // 1 = DSI, 2 = PCM TX, 3 = PCM RX, 4 = SMI, 5 = PWM, 6 = SPI TX, 7 = SPI RX, 12 = UART TX.
#define TI_WAITS      (0x1F << 21)          // Add Wait Cycles. This slows down the DMA throughput by setting the number of dummy cycles 
                                            // burnt after each DMA read or write operation is completed. A value of 0 means that no wait cycles are to be added.
#define TI_NO_WIDE_BURSTS (1 << 16)         // Don't do wide writes as a 2 beat burst. This prevents the DMA from issuing wide writes as 2
                                            // beat AXI bursts. This is an inefficient access mode, so the default (0) is to use the bursts.
    volatile uint32_t SOURCE_AD;            // 0x04 Source Address
    volatile uint32_t DEST_AD;              // 0x08 Destination Address
    volatile uint32_t TXFR_LEN;             // 0x0C Transfer length, in bytes
#define TXFR_YLENGTH(x) (((x) & 0xFFFF) << 16) // Y length for 2D mode transfers. This is the number of rows to be transferred in 2D mode. Ignored in linear mode.
#define TXFR_XLENGTH(x) ((x) & 0xFFFF)      // X length for 2D mode transfers. This is the number of bytes to be transferred in each row in 2D mode, 
    volatile uint32_t STRIDE;               // 0x10 2D Mode Stride, 0 for simple 1D transfers (= lite dma)
    volatile uint32_t NEXTCONBK;            // 0x14 Next Control Block Address
    volatile uint32_t DEBUG;                // 0x18 Debug. This register is only writeable by the ARM, and is used to control and monitor the state of the DMA channel.
    uint32_t reserved[1];                   // 0x1C Reserved – set to zero
} __attribute__((aligned(32))) bcm2835_dma_ctrl_blck_t;

typedef struct {
    volatile uint32_t TI;                   // 0x00 Transfer Information
    volatile uint32_t SOURCE_AD;            // 0x04 Source Address
    volatile uint32_t SOURCE_I;             // 0x08 Source Information
    volatile uint32_t DEST_AD;              // 0x0C Transfer length
    volatile uint32_t DEST_I;               // 0x10 Destination Information
    volatile uint32_t TXFR_LEN;             // 0x14 Transfer length
    volatile uint32_t NEXTCONBK;            // 0x18 Next Control Block Address
    uint32_t reserved0;                     // 0x1C Reserved – set to zero
} __attribute__((aligned(32))) bcm2835_dma_4_ctrl_blck_t;

typedef struct {
    volatile uint32_t CS;                   // 0x000 Control and Status
#define CS_ACTIVE       (1 << 0)            // Activate the DMA. This bit enables the DMA. The DMA will start if this bit is set and the CB_ADDR is
                                            // non zero. The DMA transfer can be paused and resumed by clearing, then setting it again. This bit is
                                            // automatically cleared at the end of the complete DMA transfer, ie. after a NEXTCONBK = 0x0000_0000 has been loaded.
#define CS_END          (1 << 1)            // DMA End Flag. Set when the transfer described by the current control block is complete. Write 1 to clear.
#define CS_INT          (1 << 2)            // Interrupt Status. This is set when the transfer for the CB ends and INTEN is set to 1. Once set it
                                            // must be manually cleared down, even if the next CB has INTEN = 0. Write 1 to clear.
#define CS_DREQ         (1 << 3)            // DREQ State. Indicates the state of the selected DREQ (Data Request) signal, ie. the DREQ selected 
                                            // by the PERMAP field of the transfer info. 1 = Requesting data. This will only be valid once the DMA 
                                            // has started and the PERMAP field has been loaded from the CB. It will remain valid, indicating the
                                            // selected DREQ signal, until a new CB is loaded. If PERMAP is set to zero (unpaced transfer) then 
                                            // this bit will read back as 1. 0 = No data request.
#define CS_PAUSED       (1<< 4)             // DMA Paused State. Indicates if the DMA is currently paused and not transferring data. This will occur
                                            // if: the active bit has been cleared, if the DMA is currently executing wait cycles or if the debug_pause
                                            // signal has been set by the debug block, or the number of outstanding writes has exceeded the max count.
                                            // 1 = DMA channel is paused. 0 = DMA channel is running.
#define CS_DREQ_STOPS_DMA (1 << 5)          // DMA Paused by DREQ State. Indicates if the DMA is currently paused and not transferring data due to the
                                            // DREQ being inactive. 1 = DMA channel is paused. 0 = DMA channel is running.
#define CS_WAITING_FOR_OUTSTANDING_WRITES (1 << 6) // DMA is Waiting for the Last Write to be Received Indicates if the DMA is currently waiting 
                                            // for any outstanding writes to be received, and is not transferring data. 1 = DMA channel is waiting.
#define CS_ERROR        ( 1 << 8)           // DMA Error. Indicates if the DMA has detected an error. The error flags are available in the debug register,
                                            // and have to be cleared by writing to that register. 1 = channel has an error. 0 = channel is ok.
#define CS_PRIORITY     (0xF << 16)         // AXI Priority Level. Sets the priority of normal AXI bus transactions. This value is used when the 
                                            // panic bit of the selected peripheral channel is zero. Zero is the lowest priority.
#define CS_PANIC_PRIORITY (0xF << 20)       // AXI Panic Priority Level. Sets the priority of panicking AXI bus transactions. This value is used when the 
                                            // panic bit of the selected peripheral channel is 1. Zero is the lowest priority.
#define CS_WAIT_FOR_OUTSTANDING_WRITES (1 << 28) // Wait for outstanding writes. When set to 1, the DMA will keep a tally of the AXI writes going out and 
                                            // the write responses coming in. At the very end of the current DMA transfer it will wait until the last
                                            // outstanding write response has been received before indicating the transfer is complete. Whilst waiting it 
                                            // will load the next CB address (but will not fetch the CB), clear the active flag (if the next CB address = zero),
                                            // and it will defer setting the END flag or the INT flag until the last outstanding write response 
                                            // has been received. In this mode, the DMA will pause if it has more than 13 outstanding writes at any one time.
#define CS_DISDEBUG     (1 << 29)           // Disable debug pause signal. When set to 1, the DMA will not stop when the debug pause signal is asserted.
#define CS_ABORT        (1 << 30)           // Abort DMA. Writing a 1 to this bit will abort the current DMA CB. The DMA will load the next CB and 
                                            // attempt to continue. The bit cannot be read, and will self clear.
#define CS_RESET        (1 << 31)           // DMA Channel Reset. Writing a 1 to this bit will reset the DMA. The bit cannot be read, and will self clear. 
    volatile uint32_t CONBLK_AD;            // 0x004 Control Block Address
    volatile uint32_t TI;                   // 0x008 CB Word 0 Transfer Information, automatically loaded from a Control Block data structure
    volatile uint32_t SOURCE_AD;            // 0x00C CB Word 1 Source Address, automatically loaded from a Control Block data structure
    volatile uint32_t DEST_AD;              // 0x010 CB Word 2 Destination Address, automatically loaded from a Control Block data structure
    volatile uint32_t TXFR_LEN;             // 0x014 CB Word 3 Transfer length, automatically loaded from a Control Block data structure
// DMA Transfer Length. This specifies the amount of data to be transferred in bytes. In normal (non 2D) mode this specifies the amount of bytes to be transferred. 
// In 2D mode it is interpreted as an X and a Y length, and the DMA will perform Y transfers, each of length X bytes and add the strides onto the addresses after 
// each X leg of the transfer. The length register is updated by the DMA engine as the transfer progresses, so it will indicate the data left to transfer. 
#define TX_XLENGTH      (0xFFFF << 0)       // Transfer Length in bytes.
#define TX_YLENGTH      (0x7FFF << 16)      // When in 2D mode, This is the Y transfer length, indicating how many xlength transfers are performed. 
                                            // When in normal linear mode this becomes the top bits of the XLENGTH
    volatile uint32_t STRIDE;               // 0x018 CB Word 4 2D Mode Stride, automatically loaded from a Control Block data structure
    volatile uint32_t NEXTCONBK;            // 0x01C CB Word 5 Next Control Block Address, automatically loaded from a Control Block data structure
    volatile uint32_t DEBUG;                // 0x020 Debug
#define DEBUG_READ_LAST_NOT_SET_ERROR (1 << 0) // This bit is set if the DMA detects an AXI read error. It will be set until cleared by the ARM.
#define DEBUG_FIFO_ERROR (1 << 1)           // This bit is set if the DMA detects a FIFO error. It will be set until cleared by the ARM.
#define DEBUG_READ_ERROR (1 << 2)           // This bit is set if the DMA detects a read error. It will be set until cleared by the ARM.
#define DEBUG_CLEAR_ERRORS (DEBUG_READ_LAST_NOT_SET_ERROR | DEBUG_FIFO_ERROR | DEBUG_READ_ERROR) // Writing a 1 to any of the error bits will clear that bit.
                                            // This is the only way to clear the error bits.
} bcm2835_dma_ctrl_regs_t;
extern volatile bcm2835_dma_ctrl_regs_t *DMA00_2835;
extern volatile bcm2835_dma_ctrl_regs_t *DMA01_2835;
extern volatile bcm2835_dma_ctrl_regs_t *DMA02_2835;
extern volatile bcm2835_dma_ctrl_regs_t *DMA03_2835;
extern volatile bcm2835_dma_ctrl_regs_t *DMA04_2835;
extern volatile bcm2835_dma_ctrl_regs_t *DMA05_2835;
extern volatile bcm2835_dma_ctrl_regs_t *DMA06_2835;

typedef struct {
    volatile uint32_t CS;                   // 0x000 Control and Status
    volatile uint32_t CONBLK_AD;            // 0x004 Control Block Address
    volatile uint32_t TI;                   // 0x008 CB Word 0 Transfer Information, automatically loaded from a Control Block data structure
    volatile uint32_t SOURCE_AD;            // 0x00C CB Word 1 Source Address, automatically loaded from a Control Block data structure
    volatile uint32_t DEST_AD;              // 0x010 CB Word 2 Destination Address, automatically loaded from a Control Block data structure
    volatile uint32_t TXFR_LEN;             // 0x014 CB Word 3 Transfer length, automatically loaded from a Control Block data structure
    uint32_t reserved0;                     // 0x10 Reserved – set to zero
    volatile uint32_t NEXTCONBK;            // 0x01C CB Word 5 Next Control Block Address, automatically loaded from a Control Block data structure
    volatile uint32_t DEBUG;                // 0x020 Debug
} bcm2835_dma_lite_ctrl_regs_t;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA07_2835;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA08_2835;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA09_2835;
extern volatile bcm2835_dma_lite_ctrl_regs_t *DMA10_2835;

typedef struct {
    volatile uint32_t CS;                   // 0x000 Control and Status
    volatile uint32_t CONBLK_AD;            // 0x004 Control Block Address
    uint32_t reserved0;                     // 0x008 Reserved – set to zero
    volatile uint32_t DEBUG;                // 0x00C Debug
    volatile uint32_t TI;                   // 0x010 CB Word 0 Transfer Information, automatically loaded from a Control Block data structure
    volatile uint32_t SOURCE_AD;            // 0x014 CB Word 1 Source Address [31:0], automatically loaded from a Control Block data structure
    volatile uint32_t SOURCE_ADI;           // 0x018 CB Word 2 Source Address [40:32] and Info, automatically loaded from a Control Block data structure
    volatile uint32_t DEST_AD;              // 0x01C CB Word 3 Destination Address[31:0], automatically loaded from a Control Block data structure
    volatile uint32_t DEST_ADI;             // 0x020 CB Word 4 Destination Address[40:32] and Info, automatically loaded from a Control Block data structure
    volatile uint32_t TXFR_LEN;             // 0x024 CB Word 5 Transfer length, automatically loaded from a Control Block data structure
    volatile uint32_t NEXTCONBK;            // 0x028 CB Word 6 Next Control Block Address, automatically loaded from a Control Block data structure
    volatile uint32_t DEBUG2;               // 0x02C Debug
} bcm2835_dma_4_ctrl_regs_t;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA11_2835;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA12_2835;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA13_2835;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA14_2835;
extern volatile bcm2835_dma_4_ctrl_regs_t *DMA15_2835;
//
// DMA irq status register, base address at mmio_base + 0x007FE0
//
typedef struct {
    volatile uint32_t INT_STATUS;           // 0xFE0 Interrupt status of each DMA channel
} bcm2835_dma_irq_stat_reg_t;
extern volatile bcm2835_dma_irq_stat_reg_t *DMAIRQ_2835;

//
// DMA Enable register, base address at mmio_base + 0x007FF0
//
typedef struct {
    volatile uint32_t ENABLE;               // 0xFF0 Global enable bits for each DMA channel
#define DMA_CHANNEL_0 (1U << 0)
#define DMA_CHANNEL_1 (1U << 1)
#define DMA_CHANNEL_2 (1U << 2)
#define DMA_CHANNEL_3 (1U << 3)
#define DMA_CHANNEL_4 (1U << 4)
#define DMA_CHANNEL_5 (1U << 5)
#define DMA_CHANNEL_6 (1U << 6)
#define DMA_CHANNEL_7 (1U << 7)
#define DMA_CHANNEL_8 (1U << 8)
#define DMA_CHANNEL_9 (1U << 9)
#define DMA_CHANNEL_10 (1U << 10)
#define DMA_CHANNEL_11 (1U << 11)
#define DMA_CHANNEL_12 (1U << 12)
#define DMA_CHANNEL_13 (1U << 13)
#define DMA_CHANNEL_14 (1U << 14)
} bcm2835_dma_enable_reg_t;
extern volatile bcm2835_dma_enable_reg_t *DMAEN_2835;

//
// Interrupt controller, base address at mmio_base + 0x00B200
//
typedef struct {
    volatile uint32_t IRQ_BASIC_PENDING;    // 0x00
    volatile uint32_t IRQ_PENDING[2];       // 0x04 - 0x08
    volatile uint32_t FIQ_CONTROL;          // 0x0C
    volatile uint32_t ENABLE_IRQS[2];       // 0x10 - 0x14
    volatile uint32_t ENABLE_IRQS_BASIC;    // 0x18    
    volatile uint32_t DISABLE_IRQS[2];      // 0x1C - 0x20
    volatile uint32_t DISABLE_IRQS_BASIC;   // 0x24   
#define IRQ_ARM_TIMER           (1 << 0);   // Used in the ENABLE_IRQS_BASIC register
#define IRQ_ARM_MAILBOX         (1 << 1);   // Used in the ENABLE_IRQS_BASIC register
#define IRQ_ARM_DOORBELL_0      (1 << 2);   // Used in the ENABLE_IRQS_BASIC register
#define IRQ_ARM_DOORBELL_1      (1 << 3);   // Used in the ENABLE_IRQS_BASIC register
#define IRQ_ARM_GPU0_HALTED     (1 << 4);   // Used in the ENABLE_IRQS_BASIC register
#define IRQ_ARM_GPU1_HALTED     (1 << 5);   // Used in the ENABLE_IRQS_BASIC register
#define IRQ_ARM_ILLEGAL_TYPE0   (1 << 6);   // Used in the ENABLE_IRQS_BASIC register
#define IRQ_ARM_ILLEGAL_TYPE1   (1 << 7);   // Used in the ENABLE_IRQS_BASIC register
} bcm2835_ic_regs_t;
extern volatile bcm2835_ic_regs_t *IC_2835;

//
// ARM Timer, base address at mmio_base + 0x00B400
//
typedef struct {
    volatile uint32_t LOAD;                 // 0x00 Load Register
    volatile uint32_t VALUE;                // 0x04 Value Register
    volatile uint32_t CONTROL;              // 0x08 Control Register
    volatile uint32_t IRQ_CLEAR;            // 0x0C IRQ Clear/Acknowledge Register
    volatile uint32_t RAW_IRQ;              // 0x10 Raw IRQ Register
    volatile uint32_t MASKED_IRQ;           // 0x14 Masked IRQ Register
    volatile uint32_t RELOAD;               // 0x18 Reload Register
    volatile uint32_t PRE_DIVIDER;          // 0x1C Pre-divider Register
    volatile uint32_t FREE_RUNNING_CNT;     // 0x20 Free running counter
} bcm2835_arm_timer_regs_t;
extern volatile bcm2835_arm_timer_regs_t *ARM_TMR_2835;

//
// 3 x Clock Manager General Purpose Clocks Control, base address at mmio_base + 0x101070 + 1 PWM Clock Manager Control at mmio_base + 0x1010A0
//
typedef struct {
    volatile uint32_t CTL;                  // 0x00 General Purpose Clock Control
#define CM_CTL_BUSY	( 1 << 7 )              // Clock Manager Control bit: 1 = clock is running
#define CM_CTL_KILL	( 1 << 5 )              // Clock Manager Control bit, 1 = stop and reset the clock generator. This is intended for test/debug only.
#define CM_CTL_ENAB	( 1 << 4 )              // Clock Manager Control bit, 1 = enable clock generator
#define CM_CTL_MASH_MASK ( 0x3 << 9 )       // Clock Manager Control bits, MASH control for fractional clock divisor, 0 = no MASH, 1 = MASH level 1, 2 = MASH level 2, 3 = MASH level 3
#define CM_CTL_SRC_MASK ( 0xF << 0 )        // Clock Manager Control bits, clock source, 0 = GND, 1 = oscillator, 2 = testdebug0, 3 = testdebug1, 4 = PLLA per, 5 = PLLC per, 6 = PLLD per, 7 = HDMI auxiliary, 8-15 = reserved
#define CM_PASSWD	(0x5A << 24)            // Clock Manager password “5a”
#define CM_CTL_SRC(x) ((x) & 0xF)           // set sourcem, make sure only first 4 bits are being used.
    volatile uint32_t DIV;                  // 0x04 General Purpose Clock Divisor 
#define CM_DIV_DIVI(x) (((x) & 0xFFF) << 12) // Clock Manager Divisor Integer part shift
#define CM_DIV_DIVI_SHIFT   12            // Clock Manager Divisor Integer part shift
#define CM_DIV_DIVF_SHIFT   0               // Clock Manager Divisor Fractional
#define CM_DIV_DIVI_MASK    (0xFFF << CM_DIV_DIVI_SHIFT) // Clock Manager Divisor Integer part mask
#define CM_DIV_DIVF_MASK    0xFFF           // Clock Manager Divisor Fractional part mask
} bcm2835_cm_regs_t;
typedef enum {
    CM_CLK_SRC_GND         = 0,
    CM_CLK_SRC_OSCI        = 1,
    CM_CLK_SRC_TESTDEBUG0  = 2,
    CM_CLK_SRC_TESTDEBUG1  = 3,
    CM_CLK_SRC_PLLA_PER    = 4,
    CM_CLK_SRC_PLLC_PER    = 5,
    CM_CLK_SRC_PLLD_PER    = 6,
    CM_CLK_SRC_HDMI_AUX    = 7
} bcm2835_cm_clk_src_t;
typedef struct {
    bcm2835_cm_regs_t GP[3];                // 0x00 - 0x14
    uint32_t reserved[6];                   // 0x18 - 0x2C
    bcm2835_cm_regs_t PWM;                  // 0x30 - 0x37 (Fysieke offset: 0xA0)
} bcm2835_cm_cc_regs_t;
extern volatile bcm2835_cm_cc_regs_t *CM_2835;

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
    uint32_t reserved10;                    // 0x90
    volatile uint32_t PUD;                  // 0x94 Pull-up/down + Clocks
    volatile uint32_t PUDCLK[2];            // 0x98, 0x9C
    uint32_t reserved11[4];                 // 0xA0-0xAC
    volatile uint32_t TEST;                 // 0xB0 Test
} bcm2835_gpio_regs_t;
extern volatile bcm2835_gpio_regs_t *GPIO_2835;

//
// PL011 UART0, base address at mmio_base + 0x201000
//
typedef struct {
    volatile uint32_t DR;                   // 0x00 Data Register
    volatile uint32_t RSR_ECR;              // 0x04 Receive Status / Error Clear Register
    uint32_t reserved1[4];                  // 0x08 - 0x14
    volatile uint32_t FR;                   // 0x18 Flag Register
    uint32_t reserved2[1];                  // 0x1C
    volatile uint32_t ILPR;                 // 0x20 IrDA Low-Power Register
    volatile uint32_t IBRD;                 // 0x24 Integer Baud Rate Register
    volatile uint32_t FBRD;                 // 0x28 Fractional Baud Rate Register
    volatile uint32_t LCRH;                 // 0x2C Line Control Register
    volatile uint32_t CR;                   // 0x30 Control Register
    volatile uint32_t IFLS;                 // 0x34 Interrupt FIFO Level Select Register
    volatile uint32_t IMSC;                 // 0x38 Interrupt Mask Set/Clear Register
    volatile uint32_t RIS;                  // 0x3C Raw Interrupt Status Register
    volatile uint32_t MIS;                  // 0x40 Masked Interrupt Status Register
    volatile uint32_t ICR;                  // 0x44 Interrupt Clear Register
    volatile uint32_t DMACR;                // 0x48 DMA Control Register
    uint32_t reserved3[13];                 // 0x4C - 7C
    volatile uint32_t ITCR;                 // 0x80 Test Control Register
    volatile uint32_t ITIP;                 // 0x84 Integration Test Input Register
    volatile uint32_t ITOP;                 // 0x88 Integration Test Output Register
    volatile uint32_t TDR;                  // 0x8C Test Data Register
} bcm2835_uart_regs_t;
extern volatile bcm2835_uart_regs_t *UART0_2835;

//
// SDHOST Controller (SD Card), base address at mmio_base + 0x202000
//
typedef struct {
} bcm2835_sdhost_regs_t;
extern volatile bcm2835_sdhost_regs_t *SDHOST_2835;

//
// PCM audio interface, base address at mmio_base + 0x203000
//
typedef struct {
    volatile uint32_t CS_A;                 // 0x00 Control and Status
    volatile uint32_t FIFO_A;               // 0x04 FIFO Data
    volatile uint32_t MODE_A;               // 0x08 Mode
    volatile uint32_t RXC_A;                // 0x0C Receive Configuration
    volatile uint32_t TXC_A;                // 0x10 Transmit Configuration
    volatile uint32_t DREQ_A;               // 0x14 DMA Request Level
    volatile uint32_t INTEN_A;              // 0x18 Interrupt Enables
    volatile uint32_t INTSTC_A;             // 0x1C Interrupt Status & Clear
    volatile uint32_t GRAY;                 // 0x20 Gray Mode Control
} bcm2835_pcm_regs_t;
extern volatile bcm2835_pcm_regs_t *PCM_2835;

//
// SPI Serial Peripheral Interface, base address at mmio_base + 0x204000
//
typedef struct {
    volatile uint32_t CS;                   // 0x00 Control and Status
    volatile uint32_t FIFO;                 // 0x04 Master TX and RX FIFOs 
    volatile uint32_t CLK;                  // 0x08 Clock Divider
    volatile uint32_t DLEN;                 // 0x0C Data Length
    volatile uint32_t LTOH;                 // 0x10 Lossi TOH
    volatile uint32_t DC;                   // 0x14 DMA DREQ Controls
} bcm2835_spi_regs_t;
extern volatile bcm2835_spi_regs_t *SPI0_2835;

//
// I2C0, base address at mmio_base + 0x205000
//
typedef struct {
    volatile uint32_t CS;                   // 0x00 Control
    volatile uint32_t SR;                   // 0x04 Status
    volatile uint32_t DLEN;                 // 0x08 Data Length
    volatile uint32_t A;                    // 0x0C Slave Address
    volatile uint32_t FIFO;                 // 0x10 Data FIFO
    volatile uint32_t DIV;                  // 0x14 Clock Divider
    volatile uint32_t DEL;                  // 0x18 Data Delay
    volatile uint32_t CLKT;                 // 0x1C Clock Stretch Timeout
} bcm2835_i2c_regs_t;
extern volatile bcm2835_i2c_regs_t *I2C0_2835;

//
// Pulse Width Modulator, base address at mmio_base + 0x20C000
//
typedef struct {
    volatile uint32_t CTL;                  // 0x00 Control
#define PWM_CTL_EN_CH0  ( 1 << 0 )          // PWM channel 0 enable bit
#define PWM_CTL_MODE0   ( 1 << 1 )          // PWM channel 0 mode bit: 0 = PWM mode, 1 = serializer mode
#define PWM_CTL_RPTL0   ( 1 << 2 )          // PWM channel 0 repeat last data if in serializer mode
#define PWM_CTL_SBIT0   ( 1 << 3 )          // PWM channel 0 serial bit
#define PWM_CTL_POLA0   ( 1 << 4 )          // PWM channel 0 polarity bit
#define PWM_CTL_USEF0   ( 1 << 5 )          // PWM channel 0 use fifo bit
#define PWM_CTL_CLRF    ( 1 << 6 )          // PWM clear fifo bit, valid only when USEF0 is set, writing a 1 to this bit will clear the PWM FIFO used by channel 0 and 1
#define PWM_CTL_MSEN0   ( 1 << 7 )          // PWM channel 0 mark-space mode bit
#define PWM_CTL_EN_CH1  ( 1 << 8 )          // PWM channel 1 enable bit
#define PWM_CTL_MODE1   ( 1 << 9 )          // PWM channel 1 mode bit: 0 = PWM mode, 1 = serializer mode
#define PWM_CTL_RPTL1   ( 1 << 10 )         // PWM channel 1 repeat last data if in serializer mode
#define PWM_CTL_SBIT1   ( 1 << 11 )         // PWM channel 1 serial bit
#define PWM_CTL_POLA1   ( 1 << 12 )         // PWM channel 1 polarity bit
#define PWM_CTL_USEF1   ( 1 << 13 )         // PWM channel 1 use fifo bit
#define PWM_CTL_MSEN1   ( 1 << 15 )         // PWM channel 1 mark-space mode bit
    volatile uint32_t STA;                  // 0x04 Status
#define PWM_STA_FULL    ( 1 << 0 )          // PWM FIFO full bit
#define PWM_STA_EMPT    ( 1 << 1 )          // PWM FIFO empty bit
#define PWM_STA_WERR    ( 1 << 2 )          // PWM FIFO write error bit, set if you try to write to the FIFO when it is full
#define PWM_STA_RERR    ( 1 << 3 )          // PWM FIFO read error bit, set if you try to read from the FIFO when it is empty
#define PWM_STA_GAPO0   ( 1 << 4 )          // PWM channel 0 gap occurred bit, set if a gap between PWM pulses occurred on channel 0
#define PWM_STA_GAPO1   ( 1 << 5 )          // PWM channel 1 gap occurred bit, set if a gap between PWM pulses occurred on channel 1
#define PWM_STA_BERR    ( 1 << 8 )          // PWM bus error bit, set if there was a bus error while trying to write to the PWM registers
#define PWM_STA_STA0    ( 1 << 9 )          // PWM channel 0 state bit, 1 = PWM is transmitting, 0 = PWM is not transmitting
#define PWM_STA_STA1    ( 1 << 10 )         // PWM channel 1 state bit, 1 = PWM is transmitting, 0 = PWM is not transmitting
    volatile uint32_t DMAC;                 // 0x08 DMA Configuration
#define PWM_DMAC_ENAB    ( 1 << 31 )          // PWM DMA enable bit
#define PWM_DMAC_PANIC_LVL(x) (((x) & 0xF) << 8) // set PWM DMA panic threshold level
#define PWM_DMAC_DREQ_LVL(x) (((x) & 0xF) << 0) // set PWM DMA DREQ threshold level                
    uint32_t reserved1[1];                  // 0x0C
    volatile uint32_t RNG0;                 // 0x10 Channel 0 Range
    volatile uint32_t DAT0;                 // 0x14 Channel 0 Data
    volatile uint32_t FIF;                  // 0x18 FIFO input
    uint32_t reserved2[1];
    volatile uint32_t RNG1;                 // 0x20 Channel 1 Range
    volatile uint32_t DAT1;                 // 0x24 Channel 1 Data 
} bcm2835_pwm_regs_t;
extern volatile bcm2835_pwm_regs_t *PWM0_2835;

//
// I2C/SPI SLAVE, base address at mmio_base + 0x214000
//
typedef struct {
    volatile uint32_t DR;                   // 0x00 Data
    volatile uint32_t RSR;                  // 0x04 Operation status register and error clear register
    volatile uint32_t SLV;                  // 0x08 The I2C SPI Address Register holds the I2C slave address value
    volatile uint32_t CR;                   // 0x0C The Control register is used to configure the I2C or SPI operation
    volatile uint32_t FR;                   // 0x10 Flag register
    volatile uint32_t IFLS;                 // 0x14 Interrupt fifo level select register
    volatile uint32_t IMSC;                 // 0x18 Channel 2 Range
    volatile uint32_t RIS;                  // 0x1C Interupt Mask Set Clear Register
    volatile uint32_t MIS;                  // 0x20 Masked Interrupt Status Register
    volatile uint32_t ICR;                  // 0x24 Interrupt Clear Register
    volatile uint32_t DMACR;                // 0x28 DMA Control Register
    volatile uint32_t TDR;                  // 0x2C FIFO Test Data
    volatile uint32_t GPUSTAT;              // 0x30 GPU Status
    volatile uint32_t HCTRL;                // 0x34 Host Control
    volatile uint32_t DEBUG1;               // 0x38 I2C Debug Register
    volatile uint32_t DEBUG2;               // 0x3C SPI Debug Register
} bcm2835_i2c_spi_slave_regs_t;
extern volatile bcm2835_i2c_spi_slave_regs_t *I2C_SPI_SLAVE_2835;

//
// AUX registers, base address at mmio_base + 0x215000
//
typedef struct {
    volatile uint32_t IRQ;                  // 0x00 Auxiliary Interrupt status
    volatile uint32_t ENABLES;              // 0x04 Auxiliary enables
} bcm2835_aux_regs_t;
extern volatile bcm2835_aux_regs_t *AUX_2835;

//
// Mini UART, base address at mmio_base + 0x215040
//
typedef struct {
    volatile uint32_t MU_IO;                // 0x40 I/O Data
    volatile uint32_t MU_IER;               // 0x44 Interrupt Enable
    volatile uint32_t MU_IIR;               // 0x48 Interrupt Identify/FIFO Enable
    volatile uint32_t MU_LCR;               // 0x4C Line Control
    volatile uint32_t MU_MCR;               // 0x50 Modem Control
    volatile uint32_t MU_LSR;               // 0x54 Line Status
    volatile uint32_t MU_MSR;               // 0x58 Modem Status
    volatile uint32_t MU_SCRATCH;           // 0x5C Scratch
    volatile uint32_t MU_CNTL;              // 0x60 Control
    volatile uint32_t MU_STAT;              // 0x64 Status
    volatile uint32_t MU_BAUD;              // 0x68 Baudrate
} bcm2835_mu_regs_t;
extern volatile bcm2835_mu_regs_t *MU_2835;              // Mini UART base address pointer

//
// SPI0, Universal SPI Master, base address (BA) at mmio_base + 0x215000 + 0x80
// SPI1, base address at mmio_base + 0x215000 + 0xC0
//
typedef struct {
    volatile uint32_t CNTL0;           // 0x00 SPI Control register 0
    volatile uint32_t CNTL1;           // 0x04 SPI Control register 1
    volatile uint32_t STAT;            // 0x08 SPI Status register
    uint32_t reserved0[1];
    volatile uint32_t IO;              // 0x10 SPI Data
    volatile uint32_t PEEK;            // 0x14 SPI Peek
} bcm2835_aux_spi_regs_t;
extern volatile bcm2835_aux_spi_regs_t *SPI1_2835; // SPI 1 base address pointer
extern volatile bcm2835_aux_spi_regs_t *SPI2_2835; // SPI 2 base address pointer

//
// External Mass Media Controller (SD Card), base address at mmio_base + 0x300000
//
typedef struct {
    volatile uint32_t ARG2;                 // 0x00 Argument 2
    volatile uint32_t BLKSIZECNT;           // 0x04 Block Size and Count
    volatile uint32_t ARG1;                 // 0x08 Argument 1
    volatile uint32_t CMDTM;                // 0x0C Command and Transfer Mode
    volatile uint32_t RESP0;                // 0x10 Response 0
    volatile uint32_t RESP1;                // 0x14 Response 1
    volatile uint32_t RESP2;                // 0x18 Response 2
    volatile uint32_t RESP3;                // 0x1C Response 3
    volatile uint32_t DATA;                 // 0x20 Data
    volatile uint32_t STATUS;               // 0x24 Status
    volatile uint32_t CONTROL0;             // 0x28 Control 0
    volatile uint32_t CONTROL1;             // 0x2C Control 1
    volatile uint32_t INTERRUPT;            // 0x30 Interrupt
    volatile uint32_t IRPT_MASK;            // 0x34 Interrupt Mask
    volatile uint32_t IRPT_EN;              // 0x38 Interrupt Enable
    volatile uint32_t CONTROL2;             // 0x3C Control 2
    volatile uint32_t FORCE_IRPT;           // 0x40 Force Interrupt
    volatile uint32_t BOOT_TIMEOUT;         // 0x44 Boot Timeout
    volatile uint32_t DBG_SEL;              // 0x48 Debug Select
    volatile uint32_t EXRDFIFO_CFG;         // 0x4C Extra Read FIFO Configuration
    volatile uint32_t TUNE_STEP;            // 0x50 Tune Step
    volatile uint32_t TUNE_STEPS_STD;       // 0x54 Tune Steps for Standard Speed
    volatile uint32_t TUNE_STEPS_DDR;       // 0x58 Tune Steps for DDR Mode
} bcm2835_emmc_regs_t;
extern volatile bcm2835_emmc_regs_t *EMMC_2835;          // EMMC base address pointer

//
// I2C1, base address at mmio_base + 0x804000
//
extern volatile bcm2835_i2c_regs_t *I2C1_2835;

//
// USB Controller, base address at mmio_base + 0x980000
//
typedef struct {
// For core registers see DWC_OTG_CORE_IF.h
    dwc_otg_core_global_regs_t_p1 core_p1;
    volatile uint32_t USB_MDIO_CNTL;        // 0x080 MDIO interface control
    volatile uint32_t USB_MDIO_GEN;         // 0x084 Data for MDIO interface
    volatile uint32_t USB_VBUS_DRV;         // 0x088 Vbus and other Miscellaneous controls
    uint32_t reserved[29];                  // 0x08C-0x0FC
    dwc_otg_core_global_regs_t_p2 core_p2;
}  bcm2835_usb_regs_t;
extern volatile bcm2835_usb_regs_t *USB_2835;

// Initializes the BCM2836 peripherals base address pointers
void BCM2835_init(soc_t *);
