#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define MAILBOX_VC_OFFSET       0xB880
#define MAILBOX_TIMEOUT         100000      // used to avoid infinite loops in mailbox communication, in case something goes wrong. Value is arbitrary, but should be large enough to not cause false positives.
#define VC_PAGE_SIZE            0x1000      // 4KB page size for memory allocation
#define VC_PAGE_ROUNDUP(size)   (((size) + VC_PAGE_SIZE - 1) & ~(VC_PAGE_SIZE - 1))

/* --- Videocore Mailbox Property Interface Tags --- */
// https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
/* VideoCore Informatie */
#define GET_FIRMWARE_REVISION   0x00000001  // Request: Length: 0, Response: 4 bytes, Value: u32: firmware revision
#define GET_BOARD_MODEL         0x00010001  // Request: Length: 0, Response: 4 bytes, Value: u32: board model
#define GET_BOARD_REVISION      0x00010002  // Request: Length: 0, Response: 4 bytes, Value: u32: board revision
#define GET_MAC_ADDRESS         0x00010003  // Request: Length: 0, Response: 6 bytes, Value: u8[6]: MAC address in network byte order
#define GET_BOARD_SERIAL        0x00010004  // Request: Length: 0, Response: 8 bytes, Value: u64: board serial
#define GET_ARM_MEMORY          0x00010005  // Request: Length: 0, Response: 8 bytes, Value: u32: base address in bytes, u32: size in bytes, Get the ARM memory size
#define GET_GPU_MEMORY          0x00010006  // Request: Length: 0, Response: 8 bytes, Value: u32: base address in bytes, u32: size in bytes, Get the GPU memory size
#define GET_CLOCKS              0x00010007  // Request: Length: 0, Response: variable (multiple of 8), Value: u32: parent clock id (0 for a root clock), u32: clock id, repeated for each clock, 
                                            // Get the clock tree as a list of parent-child relationships. This can be used to reconstruct the clock tree and understand 
                                            // how the different clocks are related to each other.
/* Power Management */
#define GET_POWER_STATE         0x00020001  // Request: Length: 4, Value: u32: device id, Response: 8 bytes, Value: u32: device id, u32: bitmask of power states (bit 0: 0=off, 1=on, bit 1: 0= device exists, 1=does not exist)
#define SET_POWER_STATE         0x00028001  // Request: Length: 8, Value: u32: device id, u32: power state (bit0: 0=off, 1=on, Bit1: 0=device exists, 1=does not exist)), 
                                            // Response: 8 bytes, Value: u32: device id, u32: state (bit0: 0=off, 1=on, Bit1: 0=device exists, 1=does not exist)
#define GET_TIMING              0x00020002  // Request: Length: 4, Value: u32: device id, Response: 8 bytes, Value: u32: device id, u32: enable wait time in microseconds
/* Clocks & Frequenties */
#define GET_CLOCK_STATE         0x00030001  // Request: Length: 4, Value: u32: clock id, Response: 8 bytes, Value: u32: clock id, u32: bitmask of clock states (bit 0: 0=off, 1=on, bit 1: 0=clock exists, 1=clock does not exist)
#define SET_CLOCK_STATE         0x00038001  // Request: Length: 8, Value: u32: clock id, u32: clock state (bit0: 0=off, 1=on, Bit1: 0=do not wait, 1=wait), 
                                            // Response: 8 bytes, Value: u32: clock id, u32: state (bit0: 0=off, 1=on, Bit1: 0=clock exists, 1=clock does not exist)
#define GET_CLOCK_RATE          0x00030002
#define SET_CLOCK_RATE          0x00038002
#define GET_MAX_CLOCK_RATE      0x00030004
#define GET_MIN_CLOCK_RATE      0x00030007
#define GET_TURBO               0x00030009
#define SET_TURBO               0x00038009
#define GET_CLOCK_RATE_MEASURED 0x00030047
/* Voltages (Gevaarlijk maar nuttig voor overclocking) */
#define GET_VOLTAGE             0x00030003
#define SET_VOLTAGE             0x00038003
#define GET_MAX_VOLTAGE         0x00030005
#define GET_MIN_VOLTAGE         0x00030008
/* Sensoren */
#define GET_SOC_TEMPERATURE     0x00030006
#define GET_MAX_TEMPERATURE     0x0003000A
/* VPU Geheugenbeheer (DMA & Buffers) */
#define ALLOCATE_MEMORY         0x0003000C  // Request: Length: 12, Value: u32: size, u32: alignment, u32: flags, Response: 4 bytes, Value: u32: handle (handle != 0 is success), Allocates contiguous memory on the GPU. size and alignment are in bytes. flags contain:
#define MEM_FLAG_DISCARDABLE    (1 << 0)    // can be resized to 0 at any time. Use for cached data
#define MEM_FLAG_NORMAL         (0 << 2)    // normal allocating alias. Allocated memory will not be directly accessible by the ARM, and will need to be mapped using lock_memory to get an ARM virtual address that can be used to access the memory.
#define MEM_FLAG_DIRECT         (1 << 2)    // allocate memory that is directly mappable to ARM address space. This is the most common flag to use, since it allows the ARM to access the memory
                                            // without needing to lock it first. The returned handle can be used with lock_memory to get the ARM virtual address, but the physical address can be 
                                            // calculated  from the handle without needing to lock it first, using the formula: physical_address = (handle & 0x3FFFFFFF) + 0xC0000000.
#define MEM_FLAG_COHERENT       (2 << 2)    // Non-allocating in L2 but coherent. Allocate memory that is directly mappable to ARM address space and is also coherent,
                                            // meaning that the GPU and ARM will see the same data in the memory without needing to flush or invalidate caches.
                                            // This is useful for sharing data between the GPU and ARM without needing to worry about cache coherency issues,
                                            // but it may be slower than normal memory for the GPU to access, so it should only be used when necessary.
#define MEM_FLAG_L1_NONALLOCATING (MEM_FLAG_DIRECT | MEM_FLAG_COHERENT) // Allocating in L2
#define MEM_FLAG_ZERO           (1 << 4)    // initialize the allocated memory to all zeros
#define MEM_FLAG_NO_INIT        (1 << 5)    // do not initialize the allocated memory, it may contain sensitive data, so only use this flag if you are going to overwrite all the data in the 
                                            // allocated memory before using it.
#define MEM_FLAG_HINT_PERMALOCK (1 << 6)    // hint that the memory will be locked for a long time, so the system should try to avoid moving it around in memory, 
                                            // which can help improve performance when using lock_memory on the allocated memory.
#define LOCK_MEMORY             0x0003000D  // Request: Length: 4, Value: u32: handle, Response: 4 bytes, Value: u32: bus address, Lock buffer in place, and return a bus address.
                                            // Must be done before memory can be accessed. bus address != 0 is success.
#define UNLOCK_MEMORY           0x0003000E  // Request: Length: 4, Value: u32: handle, Response: 4 bytes, Value: u32: status, Unlock buffer. It retains contents, but may move. 
                                            // Needs to be locked before next use. status=0 is success.
#define RELEASE_MEMORY          0x0003000F  // Request: Length: 4, Value: u32: handle, Response: 4 bytes, Value: u32: status, Release memory block. status=0 is success.
#define EXECUTE_CODE            0x00030010
#define GET_DISPMANX_HANDLE     0x00030014
#define GET_EDID_BLOCK          0x00030020 // Voor monitor info
/* Display / Framebuffer */
#define ALLOCATE_FRAMEBUFFER    0x00040001  // Vraag het Bus Address van de framebuffer op
#define RELEASE_FRAMEBUFFER     0x00048001
#define GET_PHYS_WH             0x00040003
#define SET_PHYS_WH             0x00048003  // Zet fysieke breedte/hoogte
#define GET_VIRT_WH             0x00040004
#define SET_VIRT_WH             0x00048004  // Zet virtuele breedte/hoogte
#define GET_DEPTH               0x00040005
#define SET_DEPTH               0x00048005  // Zet kleurdiepte (bijv. 32-bit)
#define GET_PIXEL_ORDER         0x00040006
#define SET_PIXEL_ORDER         0x00048006
#define GET_ALPHA_MODE          0x00040007
#define SET_ALPHA_MODE          0x00048007
#define FB_GET_PITCH            0x00040008
#define FB_SET_PITCH            0x00048008
#define GET_VIRT_OFFSET         0x00040009
#define SET_VIRT_OFFSET         0x00048009 // Handig voor double buffering / scrolling
#define GET_OVERSCAN            0x0004000A
#define SET_OVERSCAN            0x0004800A
#define GET_PALETTE             0x0004000B
#define SET_PALETTE             0x0004800B

#define GET_COMMAND_LINE        0x00050001 // Length: 0, Response: variable, Value: u8....: ASCII command line string

#define GET_DMA_CHANNELS        0x00060001 // Length: 0, Response: 4 bytes, Value: u32: mask of available channels, Mask: Bits 0-15: DMA channels 0-15 (0=do not use, 1=usable)

// Clock IDs, used to index clock rate arrays in board_t
typedef enum {
INVALID_id = 0,                             // 0x0 
EMMC_id    = 1,                             // 0x1 
UART_id,                                    // 0x2
ARM_id,                                     // 0x3
CORE_id,                                    // 0x4
V3D_id,                                     // 0x5
H264_id,                                    // 0x6
ISP_id,                                     // 0x7
SDRAM_id,                                   // 0x8
PIXEL_id,                                   // 0x9
PWM_id,                                     // 0xa
HEVC_id,                                    // 0xb
EMMC2_id,                                   // 0xc
M2MC_id,                                    // 0xd
PIXEL_BVB_id,                               // 0xe
CLOCK_SIZE                                  // 0xf
} clock_id_t;

// Device IDs used in Power Management
typedef enum {
    SD_CARD = 0,                            // 0x0
    UART0,                                  // 0x1
    UART1,                                  // 0x2
    USB_HCD,                                // 0x3
    I2C0,                                   // 0x4
    I2C1,                                   // 0x5
    I2C2,                                   // 0x6
    SPI,                                    // 0x7
    CCP2TX                                  // 0x8
    // Unknown (RPi4) 0x9 and 0xa, possibly related to Bluetooth and WiFi, but not confirmed.
} device_id_t;

//
// Videocore Mailbox, base address at mmio_base + 0x00B880
// The primary means of communication between the ARM and the VideoCore firmware running on the GPU
//
typedef struct {
    volatile uint32_t READ;                 // 0x00 (Mailbox 0: GPU -> ARM)
    uint32_t reserved[3];                   // 0x04, 0x08, 0x0C
    volatile uint32_t PEEK;                 // 0x10
    volatile uint32_t SENDER;               // 0x14
    volatile uint32_t STATUS;               // 0x18
    volatile uint32_t CONFIG;               // 0x1C
    volatile uint32_t WRITE;                // 0x20 (Mailbox 1: ARM -> GPU)
#define MAIL_PROC_REQ   0x00000000          // process request
#define MAIL_TAG_END    0x00000000          // end of tags, used to indicate the end of a message buffer when sending messages to the GPU
#define MAIL_FULL       (1 << 31)           // This bit is set in the status register if there is no space to write into the mailbox
#define MAIL_EMPTY      (1 << 30)           // This bit is set in the status register if there is nothing to read from the mailbox
#define MAIL_RESP_OK    (1 << 31)           // request successful
#define MAIL_RESP_ERR   0x80000001          // error parsing request buffer (partial response)
} mailbox_vc_regs_t;
extern volatile mailbox_vc_regs_t *MAILBOX_VC;

// Mailbox command/response structure
typedef uint32_t vc_alloc_flags_t;

typedef struct {
    uint32_t len,   // Overall length (bytes)
        req,        // Zero for request, 1<<31 for response
        tag,        // Command number
        blen,       // Buffer length (bytes)
        dlen;       // Data length (bytes)
        uint32_t uints[32-5];   // Data (108 bytes maximum)
} vc_message __attribute__ ((aligned (16)));

bool mailbox_process(volatile vc_message *msg);
bool mailbox_property(uint32_t tag, uint32_t *data, uint8_t data_len);

uint32_t alloc_vc_mem(uint32_t size, vc_alloc_flags_t flags);
void *lock_vc_mem(uint32_t handle);
uint32_t unlock_vc_mem(uint32_t handle);
uint32_t free_vc_mem(uint32_t handle);

uint32_t get_firmware_revision();
uint32_t get_board_revision();
void get_mac_address(uint8_t* mac);
uint64_t get_board_serial();
void get_arm_memory(uint32_t *base, uint32_t *size);
void get_gpu_memory(uint32_t *base, uint32_t *size);
uint32_t get_clock_rate(clock_id_t id);
void get_clock_rates(uint32_t *id);
void get_clock_rates_measured(uint32_t *id);
void get_max_clock_rates(uint32_t *id);
void get_min_clock_rates(uint32_t *id);
uint32_t get_soc_temperature();
