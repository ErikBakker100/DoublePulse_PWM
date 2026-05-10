.globl _start
.extern clearBss

#if defined(RPIA) || defined(RPIB) || defined(RPIA_PLUS) || defined(RPIB_PLUS) || defined(RPIALPHA) || defined(RPICM1) || defined(RPIZ1) || defined(RPIZ1W)
    #define ARCH_ARMV6
#endif

#include "macros.S"

// -----------------------------------------------------
//  Entry point voor Core0
// -----------------------------------------------------
.section .text._start, "ax"
_start:
    // Clear the BSS segment (assumes __bss_start and __bss_end word-aligned).
    bl  clearBss
// -----------------------------------------------------
//  Entry for Core0
// -----------------------------------------------------
core_entry_x 0

// -----------------------------------------------------
//  IRQ handlers for Core0
// -----------------------------------------------------
irq_entry_x	0

// -----------------------------------------------------
//  FIQ handlers for Core0
// -----------------------------------------------------
fiq_entry_x	0

// -----------------------------------------------------
//  Vector tables for Core0
// -----------------------------------------------------
vector_core_x 0

