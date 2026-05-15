#include "include/interrupts.h"
#include "../../general/include/stdlib.h"

const interrupts_ops_t *interrupts = NULL;

//
// C Wrappers for IRQ handlers called from assembly
//
void irq_handler_core0(void)
{
    if (interrupts && interrupts->irq_handler_core0) {
        interrupts->irq_handler_core0();
    }
}

void fiq_handler_core0(void)
{
    if (interrupts && interrupts->fiq_handler_core0) {
        interrupts->fiq_handler_core0();
    }
}

void irq_handler_core1(void)
{
    if (interrupts && interrupts->irq_handler_core1) {
        interrupts->irq_handler_core1();
    }
}

void fiq_handler_core1(void)
{
    if (interrupts && interrupts->fiq_handler_core1) {
        interrupts->fiq_handler_core1();
    }
}

// ----------------------------------------------------------------------------------
// General IRQ routines
// ----------------------------------------------------------------------------------

void irq_disable(void) {
#ifdef __aarch64__
    asm volatile("msr daifset, #2" ::: "memory");
#else
    asm volatile("cpsid i" ::: "memory");
#endif
}

void fiq_disable(void) {
#ifdef __aarch64__
    asm volatile("msr daifset, #1" ::: "memory");
#else
    asm volatile("cpsid f" ::: "memory");
#endif
}

void irq_enable(void) {
#ifdef __aarch64__
    asm volatile("msr daifclr, #2" ::: "memory");
#else
    asm volatile("cpsie i" ::: "memory");
#endif
}

void fiq_enable(void) {
#ifdef __aarch64__
    asm volatile("msr daifclr, #1" ::: "memory");
#else
    asm volatile("cpsie f" ::: "memory");
#endif
}
