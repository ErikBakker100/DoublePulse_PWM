#include "include/cpu.h"
#include "../../../general/include/stdlib.h"

implementer_t implementers[] = {
    {0x00, "Reserved for software use"},
    {0x41, "ARM Ltd."},
    {0x42, "Broadcom"},
    {0x43, "Cavium"},
    {0x44, "Digital Equipment Corporation"},
    {0x46, "Fujitsu Ltd."},
    {0x49, "Infineon"},
    {0x4D, "Motorola or Freescale Semiconductor Inc."},
    {0x4E, "NVIDIA Corporation"},
    {0x50, "Applied Micro Circuits Corporation"},
    {0x51, "Qualcomm Inc."},
    {0x56, "Marvell International Ltd."},
    {0x69, "Intel Corporation"},
    {0xC0, "Ampere Computing"}
};

partnum_t partnumbers[] = {
//   partnum, name*,        arch*,          profile,    reg    
/* ---------------- Legacy & Pi 1 ------------------- */
    {0xB76, "ARM1176JZF-S", "ARMv6KZ",      ARCH_A32,   CP15}, // Pi 1, Zero, Zero W, ARM11 → core familie, v6 → architectuur, J → Jazelle (Java acceleration), Z → TrustZone, F → VFP (floating point), S → synthesizable core

/* ---------------- Cortex-C (custom / unknown)------ */
    {0xD8A, "C1-Nano",      "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD8B, "C1-Pro",       "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD8C, "C1-Ultra",     "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD90, "C1-Premium",   "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD91, "C1-Extreme",   "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD92, "C1-Max",       "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD93, "C1-Max Ultra", "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD94, "C1-Extreme Ultra", "ARMv8-A",  ARCH_A64,   MIDR},
    {0xD95, "C1-Premium Ultra", "ARMv8-A",  ARCH_A64,   MIDR},
    {0xD96, "C1-Pro Ultra", "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD97, "C1-Nano Ultra","ARMv8-A",      ARCH_A64,   MIDR},

/* ---------------- Cortex-M ----------------------- */
    {0xC20, "Cortex-M0",    "ARMv6-M",      ARCH_M,     CPUID},
    {0xC60, "Cortex-M0+",   "ARMv6-M",      ARCH_M,     CPUID},
    {0xC23, "Cortex-M3",    "ARMv7-M",      ARCH_M,     CPUID},
    {0xC24, "Cortex-M4",    "ARMv7E-M",     ARCH_M,     CPUID},
    {0xC27, "Cortex-M7",    "ARMv7E-M",     ARCH_M,     CPUID},
    {0xD20, "Cortex-M23",   "ARMv8-M.base", ARCH_M,     CPUID},
    {0xD21, "Cortex-M33",   "ARMv8-M.main", ARCH_M,     CPUID},
    {0xD31, "Cortex-M35P",  "ARMv8-M.main", ARCH_M,     CPUID},
    {0xD52, "Cortex-M52",   "ARMv8.1-M",    ARCH_M,     CPUID},
    {0xD55, "Cortex-M55",   "ARMv8.1-M",    ARCH_M,     CPUID},
    {0xD85, "Cortex-M85",   "ARMv8.1-M",    ARCH_M,     CPUID}, // ⚠ clash ⚠ shares ID with X925

/* ---------------- Cortex-R ----------------------- */
    {0xC14, "Cortex-R4",    "ARMv7-R",      ARCH_R,     CP15},
    {0xC15, "Cortex-R5",    "ARMv7-R",      ARCH_R,     CP15},
    {0xC17, "Cortex-R7",    "ARMv7-R",      ARCH_R,     CP15},
    {0xC18, "Cortex-R8",    "ARMv7-R",      ARCH_R,     CP15},
    {0xD13, "Cortex-R52+",  "ARMv8-R",      ARCH_R,     MIDR},
    {0xD14, "Cortex-R82AE", "ARMv8-R",      ARCH_R,     MIDR},
    {0xD15, "Cortex-R82",   "ARMv8-R",      ARCH_R,     MIDR},

/* ---------------- Cortex-A (32-bit) -------------- */
    {0xC02, "Cortex-A5",    "ARMv7-A",      ARCH_A32,   CP15},
    {0xC03, "Cortex-A53",   "ARMv8-A",      ARCH_A32,   CP15}, // Pi 3, Zero 2 W (RP3A0), Pi 2 V1.2 in 32bit mode
    {0xC04, "Cortex-A57",   "ARMv8-A",      ARCH_A32,   CP15},
    {0xC05, "Cortex-A72",   "ARMv8-A",      ARCH_A32,   CP15}, // Pi 4, CM4, Pi 400 32bit mode
    {0xC07, "Cortex-A7",    "ARMv7-A",      ARCH_A32,   CP15}, // Pi 2 V1.1 32bit mode
    {0xC09, "Cortex-A9",    "ARMv7-A",      ARCH_A32,   CP15},
    {0xC0D, "Cortex-A15",   "ARMv7-A",      ARCH_A32,   CP15},
    {0xC0E, "Cortex-A17",   "ARMv7-A",      ARCH_A32,   CP15},
    {0xC0F, "Cortex-A12",   "ARMv7-A",      ARCH_A32,   CP15},

/* ---------------- Cortex-A (ARMv8) --------------- */
    {0xD01, "Cortex-A32",   "ARMv8-A",      ARCH_A32,   MIDR},
    {0xD02, "Cortex-A34",   "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD03, "Cortex-A53",   "ARMv8-A",      ARCH_A64,   MIDR}, // Pi 3, Zero 2 W (RP3A0), Pi 2 V1.2 in 64bit mode
    {0xD04, "Cortex-A35",   "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD05, "Cortex-A55",   "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD06, "Cortex-A65",   "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD43, "Cortex-A65AE", "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD07, "Cortex-A57",   "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD08, "Cortex-A72",   "ARMv8-A",      ARCH_A64,   MIDR}, // Pi 4, CM4, Pi 400 64bit mode
    {0xD09, "Cortex-A73",   "ARMv8-A",      ARCH_A64,   MIDR},
    {0xD0A, "Cortex-A75",   "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD0B, "Cortex-A76",   "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD0E, "Cortex-A76AE", "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD0D, "Cortex-A77",   "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD0F, "Cortex-A77AE", "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD41, "Cortex-A78",   "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD42, "Cortex-A78AE", "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD4B, "Cortex-A78C",  "ARMv8.2-A",    ARCH_A64,   MIDR},

/* ---------------- ARMv9 -------------------------- */
    {0xD47, "Cortex-A710",  "ARMv9-A",      ARCH_A64,   MIDR},
    {0xD4D, "Cortex-A715",  "ARMv9-A",      ARCH_A64,   MIDR},
    {0xD46, "Cortex-A510",  "ARMv9-A",      ARCH_A64,   MIDR},
    {0xD80, "Cortex-A520",  "ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD88, "Cortex-A520AE","ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD81, "Cortex-A720",  "ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD89, "Cortex-A720AE","ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD87, "Cortex-A725",  "ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD8F, "Cortex-A320",  "ARMv9-A",      ARCH_A64,   MIDR},

/* ---------------- Cortex-X ----------------------- */
    {0xD44, "Cortex-X1",    "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD4C, "Cortex-X1C",   "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD48, "Cortex-X2",    "ARMv9-A",      ARCH_A64,   MIDR},
    {0xD82, "Cortex-X4",    "ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD85, "Cortex-X925",  "ARMv9.2-A",    ARCH_A64,   MIDR}, // ⚠ clash

/* ---------------- Neoverse ----------------------- */
    {0xD0C, "Neoverse-N1",  "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD49, "Neoverse-N2",  "ARMv9-A",      ARCH_A64,   MIDR},
    {0xD40, "Neoverse-V1",  "ARMv8.4-A",    ARCH_A64,   MIDR},
    {0xD4A, "Neoverse-E1",  "ARMv8.2-A",    ARCH_A64,   MIDR},
    {0xD83, "Neoverse-V3AE","ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD84, "Neoverse-V3",  "ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD8D, "Neoverse-N3AE","ARMv9.2-A",    ARCH_A64,   MIDR},
    {0xD8E, "Neoverse-N3",  "ARMv9.2-A",    ARCH_A64,   MIDR}
};

void cpu_init(cpu_t *cpu) {
    uint32_t reg;

#if defined(__ARM_ARCH_8M__) || defined(__ARM_ARCH_7M__)
    // Cortex-M
    reg = CPUID_REG;

#elif defined(__aarch64__)
    // Cortex-A 64-bit
    asm volatile ("mrs %0, midr_el1" : "=r"(reg));
#elif defined(__ARM_ARCH)
    // Cortex-A/R 32-bit
    asm volatile ("mrc p15, 0, %0, c0, c0, 0" : "=r"(reg));
#else
    reg = 0;                                // error "Unsupported architecture"
#endif
/*
[31:24]	Implementor (0x41 = ARM)
[23:20]	Variant (rev van core)
[15:4]	PartNo (core type, bv 0xC20=M0, 0xC23=M3, 0xC24=M4, …)
[3:0]	Revision (minor core revision)
*/
    // Get PartNo and find matching info from partnumbers array
    uint16_t nr = (reg >> 4) & 0xFFF;
    for (uint8_t i = 0; i < ARRAY_SIZE(partnumbers); i++) {
        if (partnumbers[i].partnum == nr) {
            cpu->data->partnum = partnumbers[i].partnum;
            cpu->data->name = partnumbers[i].name;
            cpu->data->arch = partnumbers[i].arch; // set the architecture string based on the profile
            cpu->data->profile = partnumbers[i].profile;
            cpu->data->reg = partnumbers[i].reg;
            break;
        }
    }
    uint8_t var_val = (reg >> 20) & 0xF; // Extract bits [23:20]
    uint8_t rev_val = (reg >> 0)  & 0xF; // Extract bits [3:0]
    cpu->rNpM[0] = 'r';
    cpu->rNpM[1] = (var_val < 10) ? (var_val + '0') : (var_val - 10 + 'A');
    cpu->rNpM[2] = 'p';
    cpu->rNpM[3] = (rev_val < 10) ? (rev_val + '0') : (rev_val - 10 + 'A');
    cpu->rNpM[4] = 0;
    nr = (reg >> 24) & 0xFF;
    for (uint8_t i = 0; i < ARRAY_SIZE(implementers); i++) {
        if (implementers[i].implementer == nr) {
           cpu->implementer = &implementers[i];
           break;
        }
    }
}

void clearBss(void) {
    extern uint8_t __bss_start[];
    extern uint8_t __bss_end[];

    uint8_t *p = __bss_start;
    uint8_t *end = __bss_end;

    while (p < end) {
        *p++ = 0;
    }
}
