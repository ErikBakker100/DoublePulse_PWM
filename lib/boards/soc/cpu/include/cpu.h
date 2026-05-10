#pragma once
#include <stdint.h>
#include "../../../../general/include/config.h"

typedef enum {
    CPUID,                                  // Cortex-M
    MIDR,                                   // Cortex-A (EL1)
    CP15,                                   // Cortex-R / oudere A (AArch32)
} id_source_t;

typedef enum {
    ARCH_M,                                 // Cortex-M
    ARCH_A32,                               // Cortex-A AArch32
    ARCH_A64,                               // Cortex-A AArch64
    ARCH_R,                                 // Cortex-R
} profile_t;

typedef struct {
    uint8_t implementer;
    const char* name;
} implementer_t;

typedef struct {
    uint16_t        partnum;                // Bits[15:4] of MIDR/CPUID/CP15 register
    const char      *name;
    const char      *arch;
    profile_t       profile;                // Architecture profile (M / A32 / A64 / R)
    id_source_t     reg;                    // Detection register
} partnum_t;

typedef struct {
    implementer_t *implementer;             // bits [31:24]
    char rNpM[5];                           // bits [23:20] Variant (major core revision)
    partnum_t *data;
} cpu_t;

void cpu_init(cpu_t *cpu);
void clearBss(void);
