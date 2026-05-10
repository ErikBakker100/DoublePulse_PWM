#ifndef MACROS_S
#define MACROS_S

#include "../lib/general/include/sysregs.h"

#if defined(ARCH_ARM32)
.macro	    core_entry_x	core
.globl core_entry_\core
.extern core_main_\core
.extern __stack_svc_top_core\core
.extern __stack_irq_top_core\core
.extern __stack_fiq_top_core\core

core_entry_\core:
    cpsid if                     // disable IRQ and FIQ
#if defined(ARCH_ARMV6)
    // set vector table
    ldr     r5, =vector_table_core\core
    mcr     p15, 0, r5, c12, c0, 0
    mov     r0, #0
    mcr     p15, 0, r0, c7, c5, 4     // Flush Prefetch Buffer
#else
    ldr     r5, =vector_table_core\core
    mcr     p15, 0, r5, c12, c0, 0
    isb    
    // Check if we are in Hyp mode
    mrs     r1, cpsr
    and     r1, r1, #0x1F
    cmp     r1, #0x1A           // If in hypervisor mode switch to SVC mode
    bne     svc_entry_core\core
    ldr     r3, =svc_entry_core\core
    msr     ELR_hyp, r3
    mrs     r4, cpsr
    bic     r4, r4, #0x1F
    orr     r4, r4, #0x13        // SPSR_hyp = SVC mode (mode bits only)
    orr     r4, r4, #0xC0        // SPSR_hyp: disable FIQ and IRQ (bits 7 and 6)
    msr     SPSR_hyp, r4
    eret
#endif
svc_entry_core\core:
    // setup SVC stack
    ldr     sp, =__stack_svc_top_core\core
    // setup IRQ stack
    mov     r5, #0xD2           // IRQ mode, disable FIQ and IRQ        
    msr     cpsr_c, r5
    ldr     sp, =__stack_irq_top_core\core
    // setup FIQ stack
    mov     r5, #0xD1           // FIQ mode, disable FIQ and IRQ        
    msr     cpsr_c, r5
    ldr     sp, =__stack_fiq_top_core\core
    // back to SVC
    mov     r5, #0xD3           // SVC mode, disable FIQ and IRQ
    msr     cpsr_c, r5
    ldr     sp, =__stack_svc_top_core\core
    bl      core_main_\core
    b       hang
.endm

// -----------------------------------------------------
// IRQ entry macro
// -----------------------------------------------------
.macro	    irq_entry_x	core
.globl irq_entry_\core
.extern irq_handler_core\core
irq_entry_\core:
    sub lr, lr, #4
    stmfd sp!, {r0-r12, lr}
    bl irq_handler_core\core
    ldmfd sp!, {r0-r12, pc}^
.endm

// -----------------------------------------------------
// FIQ entry macro
// -----------------------------------------------------
.macro	    fiq_entry_x	core
.globl fiq_entry_\core
.extern fiq_handler_core\core
fiq_entry_\core:
    sub lr, lr, #4
    stmfd sp!, {r0-r12, lr}
    bl fiq_handler_core\core
    ldmfd sp!, {r0-r12, pc}^
.endm

.macro	    vector_core_x	core
.section .vectors_core\core, "ax"
.align 5

vector_table_core\core:
    b   core_entry_\core        // reset
    b   hang                    // undefined
    b   hang                    // swi
    b   hang                    // prefetch
    b   hang                    // data
    b   hang                    // unused
    b   irq_entry_\core         // irq
    b   fiq_entry_\core         // fiq
.endm

#endif // arm32

// -----------------------------------------------------
// 64bit macro's
// -----------------------------------------------------
#if defined(ARCH_ARM64)
// -----------------------------------------------------
// Core entry macro
// -----------------------------------------------------
.macro	    core_entry_x	core
.globl core_entry_\core
.extern core_main_\core
.extern __stack_el1_top_core\core

core_entry_\core:
    // Determine current exception level
    mrs     x1, CurrentEL           // Put the current exception level in x1.
    lsr     x1, x1, #2              // CurrentEL >> 2 gives EL number (0..3)
    // Als we al in EL1 zijn, ga dan direct naar el1_entry_core0
    cmp     x1, #1                  // Compare current EL with 1
    beq     el1_entry_core\core     // If we are in EL1 nothing more to do, jump to el1_entry_core0

    // We are in EL2: set exception vector base for EL2 and prepare stack pointers and exception vector base for EL1,

    // Prepare SPSR_EL2 to return to EL1, using EL1h and with interrupts masked.
    // Chosen SPSR value encodes: AArch64, EL1h, DAIF = all masked (A/I/F/D). M[3:0] = 0b0101 = 0x5  → EL1h mode
    // Put CPU in a known state
	ldr	    x4, =SCTLR_VALUE_MMU_DISABLED
	msr	    sctlr_el1, x4		
    isb
    mov     x6, (1 << 31)           // Hypervisor configuration: aarch64 mode for EL1.
    msr     hcr_el2, x6             // Written to the HCR_EL2 system register.
    
    mov     x6, #0x3c5              // 0x3C5 = 0b 11 1100 0101 -> DAIF = all masked (A/I/F/D), M[3:0] = 0b0101 = 0x5  → EL1h mode
    msr     spsr_el2, x6            // SPSR (Saved Program Status Register) Bewaard het proces wanneer een EL2 exception optreed. 
                                    // bits [9,8,7,6] → D, A, I, F bits (Debug, SError, IRQ, FIQ) interrupt masks. 1 = masked, 0 = unmasked.
                                    // bit [4] → AArch64 execution state (0 = AArch64, 1 = AArch32)
                                    // bits [3:0] → mode field 0b00101 = 0x5 → EL1h mode (EL1 using SP_EL1)
                                    // Dus bij terugkeer naar EL1 zijn alle interrupts gemaskeerd.
                                    // Zie ARM DDI 0487A.a, hoofdstuk B3.5.1 "Saved Program Status Register (SPSR_EL2)".
                                    // Wanneer een ERET wordt uitvoert vanuit EL2: SPSR_EL2 → bepaalt in welke mode EL1 start (EL1h/EL1t, DAIF, flags)
    // Set ELR_EL2 to the address we'll return to in EL1
    ldr     x6, =el1_entry_core\core
    msr     elr_el2, x6
    // Now return to EL1 (execution continues at el1_entry_core0 in EL1)
    eret

el1_entry_core\core:
    // We are now executing in EL1.    
    mrs     x2, CurrentEL           // Put the current exception level in x2.
    lsr     x2, x2, #2              // CurrentEL gives EL number (0..3)
    // Set up stack pointer for EL1
    ldr x6, =__stack_el1_top_core\core
    mov sp, x6
    // We zetten bits 20 en 21 van CPACR_EL1 op 0b11 om toegang te verlenen
    mrs     x0, cpacr_el1
    orr     x0, x0, #(3 << 20)      // FPEN bits op 0b11 (Toegang in EL1 en EL0)
    msr     cpacr_el1, x0
    isb     // Forceer dat de setting actief is voor de volgende instructie    
    // Install an exception vector.
    ldr x6, =vector_table_\core
    msr vbar_el1, x6
    isb
    bl      core_main_\core
// If main returns, park the core.
    b       hang
.endm

// -----------------------------------------------------
// IRQ entry macro
// -----------------------------------------------------
.macro	    irq_entry_x	core
.globl irq_entry_\core
.extern irq_handler_core\core
irq_entry_\core:
    kernel_entry
    bl      irq_handler_core\core
    kernel_exit
.endm

// -----------------------------------------------------
// FIQ entry macro
// -----------------------------------------------------
.macro	    fiq_entry_x	core
.globl fiq_entry_\core
.extern fiq_handler_core\core
fiq_entry_\core:
    kernel_entry
    bl      fiq_handler_core\core
    kernel_exit
.endm

// Macro to save registers and call the C IRQ or FIQhandler
.macro	kernel_entry
.align 4
    // Reserve enough bytes (31 regs * 8 = 248 bytes; + 8 padding => 256 = 16*16)
    sub     sp, sp, #(16*16)          // ruimte voor x0–x30, aligned op 16 bytes
    stp     x0,  x1,  [sp, #16*0]
    stp     x2,  x3,  [sp, #16*1]
    stp     x4,  x5,  [sp, #16*2]
    stp     x6,  x7,  [sp, #16*3]
    stp     x8,  x9,  [sp, #16*4]
    stp     x10, x11, [sp, #16*5]
    stp     x12, x13, [sp, #16*6]
    stp     x14, x15, [sp, #16*7]
	stp	    x16, x17, [sp, #16*8]
	stp	    x18, x19, [sp, #16*9]
	stp	    x20, x21, [sp, #16*10]
	stp	    x22, x23, [sp, #16*11]
	stp	    x24, x25, [sp, #16*12]
	stp	    x26, x27, [sp, #16*13]
	stp	    x28, x29, [sp, #16*14]
    stp     x30, xzr, [sp, #16*15]   // bewaar x30 (link register)
	.endm

// Macro to restore registers and return from irq or fiq handler
.macro	kernel_exit
.align 4
    ldp     x0,  x1,  [sp, #16*0]
    ldp     x2,  x3,  [sp, #16*1]
    ldp     x4,  x5,  [sp, #16*2]
    ldp     x6,  x7,  [sp, #16*3]
    ldp     x8,  x9,  [sp, #16*4]
    ldp     x10, x11, [sp, #16*5]
    ldp     x12, x13, [sp, #16*6]
    ldp     x14, x15, [sp, #16*7]
	ldp	    x16, x17, [sp, #16*8]
	ldp	    x18, x19, [sp, #16*9]
	ldp	    x20, x21, [sp, #16*10]
	ldp	    x22, x23, [sp, #16*11]
	ldp	    x24, x25, [sp, #16*12]
	ldp	    x26, x27, [sp, #16*13]
	ldp	    x28, x29, [sp, #16*14]
    ldp     x30, xzr, [sp, #16*15]   // laad x30 (link register)
    add     sp, sp, #(16*16)
    eret
    .endm

// ---------------------------------------------------------
// Vector table macro
// ---------------------------------------------------------
	.macro	ventry	label
	.align	7
	b	\label
	.endm

.macro vector_table_x core
    .section .vectors_core\core, "ax"
    .align 11                       // 2048 bytes zoals ARM vereist
vector_table_\core:
// --- EL1t ---
    ventry hang
    ventry hang
    ventry hang
    ventry hang
// --- EL1h (THIS IS WHAT WE USE) ---
    ventry core_entry_\core
    ventry irq_entry_\core
    ventry fiq_entry_\core
    ventry hang
// --- From EL0 ---
    ventry hang
    ventry hang
    ventry hang
    ventry hang
// --- unused entries ---
    ventry hang
    ventry hang
    ventry hang
    ventry hang
.endm

#endif // arm64
// -----------------------------------------------------
// Hang routine
// -----------------------------------------------------
.section .text
hang:
    wfe                             // Wait For Event: zet de core in een laag-energie wacht-toestand totdat een interrupt of event optreedt.
    b hang

#endif // MACROS_S
