#pragma once
#include <stdint.h>
#include "../../boards/include/boards.h"

// BASE_ADDR depends on architecture, set accordingly. Used for core_boot address table.
// The auxiliary cores are initially asleep.
// They can be woken up (independently) by following the following steps.
// 1) Writing an address to jump to at:
// 2) Issuing an "sev" instruction to force the core out of low-power mode.
// For 32-bit ARM (AArch32), the boot address for each core is located at an offset from the local peripheral base address. The offsets are as follows:
// Core	32-bit Adres (AArch32) for the BCM2836/2837/2710, Raspi 2, 3, Zero 2W	
//  0	0x4000008C
//  1	0x4000009C
//  2	0x400000AC
//  3	0x400000BC
// Core	32-bit Adres (AArch32) for the BCM2711, Raspi 4B
//  0   0x8C
//  1   0x9C
//  2   0xAC
//  3   0xBC

// For 64-bit ARM (AArch64), the boot address for each core is located at an offset from the local peripheral base address. The offsets are as follows:
// Core	64-bit Adres (AArch64) for the BCM2836/2837/2710, Raspi 2, 3, Zero 2W	
//  0	0x400000D8
//  1	0x400000E0
//  2	0x400000E8
//  3	0x400000F0
// Core	64-bit Adres (AArch64) for the BCM2711, Raspi 4B
//  0   0xFF8000D8
//  1   0xFF8000E0
//  2   0xFF8000E8
//  3   0xFF8000F0

#if defined(__aarch64__) || defined(__AARCH64__)
typedef volatile uint64_t core_reg_t;
#define CORE_BOOT_OFFSET 0xD8
#define CORE_ID_OFFSET(i) ((i) * 8)
#else
typedef volatile uint32_t core_reg_t;
#define CORE_BOOT_OFFSET 0x8C
#define CORE_ID_OFFSET(i) ((i) * 16)
#endif

// Pointer to core_boot register array to write the boot address for each core
volatile core_reg_t *core_boot(uintptr_t arm_local_base, int core_id);
