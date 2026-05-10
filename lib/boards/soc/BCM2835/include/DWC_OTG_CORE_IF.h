#pragma once
#include <stdint.h>
// see https://www.cl.cam.ac.uk/~atm26/ephemeral/rpi/dwc_otg/doc/html/dwc__otg__regs_8h-source.html

typedef struct {
    volatile uint32_t GOTGCTL;              // 0x00 Control and Status Register
    volatile uint32_t GOTGINT;              // 0x04 Interrupt Register
    volatile uint32_t GAHBCCFG;             // 0x08 AHB Configuration Register
#define DWC_GLBINTRMASK             0x0001
#define DWC_DMAENABLE               0x0020
#define DWC_NPTXEMPTYLVL_EMPTY      0x0080
#define DWC_NPTXEMPTYLVL_HALFEMPTY  0x0000
#define DWC_PTXEMPTYLVL_EMPTY       0x0100
#define DWC_PTXEMPTYLVL_HALFEMPTY   0x0000
    volatile uint32_t GUSBCFG;              // 0x0C USB Configuration Register
    volatile uint32_t GRSTCTL;              // 0x10 Reset Register
    volatile uint32_t GINTSTS;              // 0x14 Interrupt Register
    volatile uint32_t GINTMSK;              // 0x18 Interrupt Mask Register
    volatile uint32_t GRXSTSR;              // 0x1C Receive Status Queue Read Register (Read Only)
    volatile uint32_t GRXSTSP;              // 0x20 Receive Status Queue Read & POP Register (Read Only)
    volatile uint32_t GRXFSIZ;              // 0x24 Receive FIFO Size Register
    volatile uint32_t GNPTXFSIZ;            // 0x28 Non Periodic Transmit FIFO Size Register
    volatile uint32_t GNPTXSTS;             // 0x2C Non Periodic Transmit FIFO/Queue Status Register (Read Only)
    volatile uint32_t GI2CCTL;              // 0x30 I2C Access Register
    volatile uint32_t GPVNDCTL;             // 0x34 PHY Vendor Control Register
    volatile uint32_t GGPIO;                // 0x38 General Purpose Input/Output Register
    volatile uint32_t GUID;                 // 0x3C User ID Register
    volatile uint32_t GSNPSID;              // 0x40 Synopsys ID Register (Read Only)
    volatile uint32_t GHWCFG1;              // 0x44 User HW Config1 Register (Read Only)
    volatile uint32_t GHWCFG2;              // 0x48 User HW Config2 Register (Read Only)
#define DWC_SLAVE_ONLY_ARCH             0
#define DWC_EXT_DMA_ARCH                1
#define DWC_INT_DMA_ARCH                2
#define DWC_MODE_HNP_SRP_CAPABLE        0
#define DWC_MODE_SRP_ONLY_CAPABLE       1
#define DWC_MODE_NO_HNP_SRP_CAPABLE     2
#define DWC_MODE_SRP_CAPABLE_DEVICE     3
#define DWC_MODE_NO_SRP_CAPABLE_DEVICE  4
#define DWC_MODE_SRP_CAPABLE_HOST       5
#define DWC_MODE_NO_SRP_CAPABLE_HOST    6
    volatile uint32_t GHWCFG3;              // 0x4C User HW Config3 Register (Read Only)
    volatile uint32_t GHWCFG4;              // 0x50 User HW Config4 Register (Read Only)
    volatile uint32_t GLPMCFG;              // 0x54 
    volatile uint32_t reserved[10];         // 0x58-0x7C
} dwc_otg_core_global_regs_t_p1;

typedef struct {
    volatile uint32_t HPTXFSIZ;             // 0x100 Host Periodic Transmit FIFO Size Register
    volatile uint32_t DPTXFSIZ_DIEPTXF[15]; // 0x104 + (FIFO_Number-1)*04h, 1 <= FIFO Number <= 15 (1<=n<=15). Device Periodic Transmit FIFO::n Register if dedicated fifos are disabled, otherwise Device Transmit FIFO::n Register
} dwc_otg_core_global_regs_t_p2; 



/**
 * Synopsys USB 2.0 (DWC2) Register Bitfield Definitions
 */

typedef union gotgctl_data {
    uint32_t d32;
    struct {
        unsigned sesreqscs:1;
        unsigned sesreq:1;
        unsigned reserved2_7:6;
        unsigned hstnegscs:1;
        unsigned hnpreq:1;
        unsigned hstsethnpen:1;
        unsigned devhnpen:1;
        unsigned reserved12_15:4;
        unsigned conidsts:1;
        unsigned reserved17:1;
        unsigned asesvld:1;
        unsigned bsesvld:1;
        unsigned currmod:1;
        unsigned reserved21_31:11;
    } b;
} gotgctl_data_t;

// GOTGINT: OTG Interrupt Register
typedef union gotgint_data {
    uint32_t d32;
    struct {
        unsigned reserved0_1          : 2;
        unsigned sesenddet            : 1;
        unsigned reserved3_7          : 5;
        unsigned sesreqsucstschng     : 1;
        unsigned hstnegsucstschng     : 1;
        unsigned reserver10_16        : 7;
        unsigned hstnegdet            : 1;
        unsigned adevtoutchng         : 1;
        unsigned debdone              : 1;
        unsigned reserved31_20        : 12;
    } b;
} gotgint_data_t;

// GAHBCFG: Core AHB Configuration Register
#define DWC_GAHBCFG_GLBINT_ENABLE           1
#define DWC_GAHBCFG_INT_DMA_BURST_SINGLE    0
#define DWC_GAHBCFG_INT_DMA_BURST_INCR      1
#define DWC_GAHBCFG_INT_DMA_BURST_INCR4     3
#define DWC_GAHBCFG_INT_DMA_BURST_INCR8     5
#define DWC_GAHBCFG_INT_DMA_BURST_INCR16    7
#define DWC_GAHBCFG_DMAENABLE               1
#define DWC_GAHBCFG_TXFEMPTYLVL_EMPTY       1
#define DWC_GAHBCFG_TXFEMPTYLVL_HALFEMPTY   0

typedef union gahbcfg_data {
    uint32_t d32;
    struct {
        unsigned glblintrmsk            : 1;
        unsigned hburstlen              : 4;
        unsigned dmaenable              : 1;
        unsigned reserved               : 1;
        unsigned nptxfemplvl_txfemplvl  : 1;
        unsigned ptxfemplvl             : 1;
        unsigned reserved9_31           : 23;
    } b;
} gahbcfg_data_t;

// GUSBCFG: Core USB Configuration Register
typedef union gusbcfg_data {
    uint32_t d32;
    struct {
        unsigned toutcal                : 3;
        unsigned phyif                  : 1;
        unsigned ulpi_utmi_sel          : 1;
        unsigned fsintf                 : 1;
        unsigned physel                 : 1;
        unsigned ddrsel                 : 1;
        unsigned srpcap                 : 1;
        unsigned hnpcap                 : 1;
        unsigned usbtrdtim              : 4;
        unsigned nptxfrwnden            : 1;
        unsigned phylpwrclksel          : 1;
        unsigned otgutmifssel           : 1;
        unsigned ulpi_fsls              : 1;
        unsigned ulpi_auto_res          : 1;
        unsigned ulpi_clk_sus_m         : 1;
        unsigned ulpi_ext_vbus_drv      : 1;
        unsigned ulpi_int_vbus_indicator: 1;
        unsigned term_sel_dl_pulse      : 1;
        unsigned reserved23_25          : 3;
        unsigned ic_usb_cap             : 1;
        unsigned ic_traffic_pull_remove : 1;
        unsigned tx_end_delay           : 1;
        unsigned reserved29_31          : 3;
    } b;
} gusbcfg_data_t;

// GLPMCFG: Core LPM Configuration Register
typedef union glpmcfg_data {
    uint32_t d32;
    struct {
        unsigned lpm_cap_en             : 1;
        unsigned appl_resp              : 1;
        unsigned hird                   : 4;
        unsigned rem_wkup_en            : 1;
        unsigned en_utmi_sleep          : 1;
        unsigned hird_thres             : 5;
        unsigned lpm_resp               : 2;
        unsigned prt_sleep_sts          : 1;
        unsigned sleep_state_resumeok   : 1;
        unsigned lpm_chan_index         : 4;
        unsigned retry_count            : 3;
        unsigned send_lpm               : 1;
        unsigned retry_count_sts        : 3;
        unsigned reserved28_29          : 2;
        unsigned hsic_connect           : 1;
        unsigned inv_sel_hsic           : 1;
    } b;
} glpmcfg_data_t;

// GRSTCTL: Core Reset Register
typedef union grstctl_data {
    uint32_t d32;
    struct {
        unsigned csftrst                : 1;
        unsigned hsftrst                : 1;
        unsigned hstfrm                 : 1;
        unsigned intknqflsh             : 1;
        unsigned rxfflsh                : 1;
        unsigned txfflsh                : 1;
        unsigned txfnum                 : 5;
        unsigned reserved11_29          : 19;
        unsigned dmareq                 : 1;
        unsigned ahbidle                : 1;
    } b;
} grstctl_t;

// GINTMSK: Core Interrupt Mask Register
typedef union gintmsk_data {
    uint32_t d32;
    struct {
        unsigned reserved0              : 1;
        unsigned modemismatch           : 1;
        unsigned otgintr                : 1;
        unsigned sofintr                : 1;
        unsigned rxstsqlvl              : 1;
        unsigned nptxfempty             : 1;
        unsigned ginnakeff              : 1;
        unsigned goutnakeff             : 1;
        unsigned reserved8              : 1;
        unsigned i2cintr                : 1;
        unsigned erlysuspend            : 1;
        unsigned usbsuspend             : 1;
        unsigned usbreset               : 1;
        unsigned enumdone               : 1;
        unsigned isooutdrop             : 1;
        unsigned eopframe               : 1;
        unsigned reserved16             : 1;
        unsigned epmismatch             : 1;
        unsigned inepintr               : 1;
        unsigned outepintr              : 1;
        unsigned incomplisoin           : 1;
        unsigned incomplisoout          : 1;
        unsigned reserved22_23          : 2;
        unsigned portintr               : 1;
        unsigned hcintr                 : 1;
        unsigned ptxfempty              : 1;
        unsigned lpmtranrcvd            : 1;
        unsigned conidstschng           : 1;
        unsigned disconnect             : 1;
        unsigned sessreqintr            : 1;
        unsigned wkupintr               : 1;
    } b;
} gintmsk_data_t;

// GINTSTS: Core Interrupt Status Register
#define DWC_SOF_INTR_MASK               0x0008
#define DWC_HOST_MODE                   1

typedef union gintsts_data {
    uint32_t d32;
    struct {
        unsigned curmode                : 1;
        unsigned modemismatch           : 1;
        unsigned otgintr                : 1;
        unsigned sofintr                : 1;
        unsigned rxstsqlvl              : 1;
        unsigned nptxfempty             : 1;
        unsigned ginnakeff              : 1;
        unsigned goutnakeff             : 1;
        unsigned reserved8              : 1;
        unsigned i2cintr                : 1;
        unsigned erlysuspend            : 1;
        unsigned usbsuspend             : 1;
        unsigned usbreset               : 1;
        unsigned enumdone               : 1;
        unsigned isooutdrop             : 1;
        unsigned eopframe               : 1;
        unsigned intokenrx              : 1;
        unsigned epmismatch             : 1;
        unsigned inepint                : 1;
        unsigned outepintr              : 1;
        unsigned incomplisoin           : 1;
        unsigned incomplisoout          : 1;
        unsigned reserved22_23          : 2;
        unsigned portintr               : 1;
        unsigned hcintr                 : 1;
        unsigned ptxfempty              : 1;
        unsigned lpmtranrcvd            : 1;
        unsigned conidstschng           : 1;
        unsigned disconnect             : 1;
        unsigned sessreqintr            : 1;
        unsigned wkupintr               : 1;
    } b;
} gintsts_data_t;

// GRXSTSP: Receive Status Read and Pop Register (Device Mode)
#define DWC_STS_DATA_UPDT               0x2
#define DWC_STS_XFER_COMP               0x3
#define DWC_DSTS_GOUT_NAK               0x1
#define DWC_DSTS_SETUP_COMP             0x4
#define DWC_DSTS_SETUP_UPDT             0x6

typedef union device_grxsts_data {
    uint32_t d32;
    struct {
        unsigned epnum                  : 4;
        unsigned bcnt                   : 11;
        unsigned dpid                   : 2;
        unsigned pktsts                 : 4;
        unsigned fn                     : 4;
        unsigned reserved               : 7;
    } b;
} device_grxsts_data_t;
