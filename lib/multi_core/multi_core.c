#include "include/multi_core.h"

// The core boot registers are located at an offset from the local peripheral base, so we need to add the appropriate offset to get the correct address for each core. 
// The stride between cores is 0x10 (16 bytes) for 32-bit cores and 0x08 (8 bytes) for 64-bit cores, each core has a separate register for the boot address.

volatile core_reg_t *core_boot(uintptr_t arm_local_base, int core_id) {
    uintptr_t boot_addr = 0;    
    switch (board.soc.id) {
        case BCM2836:
        case BCM2837:
            #ifdef __aarch64__
            boot_addr = CORE_BOOT_OFFSET + CORE_ID_OFFSET(core_id);
            #else
            boot_addr = arm_local_base + CORE_BOOT_OFFSET + CORE_ID_OFFSET(core_id);
            #endif
            break;
        case BCM2711:
            #ifdef __aarch64__
            boot_addr = CORE_BOOT_OFFSET + CORE_ID_OFFSET(core_id);
            #else
            boot_addr = arm_local_base + CORE_BOOT_OFFSET + CORE_ID_OFFSET(core_id);
            #endif
            break;
        case BCM2835:
        case BCM2712:
        case UNKNOWN:                       // board not found, error
        default:
            boot_addr = 0;                  // Invalid SoC, return null pointer
    }
    return (volatile core_reg_t *) boot_addr;
}