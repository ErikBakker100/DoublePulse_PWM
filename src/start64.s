.globl _start
.extern clearBss
#include "macros.S"

// -----------------------------------------------------
//  Entry point voor Core0
// -----------------------------------------------------
.section .text._start, "ax"
_start:
    // Clear the BSS segment (assumes __bss_start and __bss_end word-aligned).
    bl  clearBss

// -----------------------------------------------------
// Entry for Core0 and if defined DUALCORE=on Core1
// -----------------------------------------------------
core_entry_x 0
#ifdef DUALCORE
core_entry_x 1
#endif

// -----------------------------------------------------
// IRQ handlers for Core0 and if defined DUALCORE=on Core1
// -----------------------------------------------------
irq_entry_x 0
#ifdef DUALCORE
irq_entry_x 1
#endif
// -----------------------------------------------------
//  FIQ handlers for Core0 and if defined DUALCORE=on Core1
// -----------------------------------------------------
fiq_entry_x	0
#ifdef DUALCORE
fiq_entry_x	1
#endif
// ---------------------------------------------------------
// Vector Tables (EL1) for Core0 and if defined DUALCORE=on Core1
// ---------------------------------------------------------
vector_table_x 0
#ifdef DUALCORE
vector_table_x 1
#endif
