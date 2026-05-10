ENTRY(_start)

SECTIONS
{
    . = @LINKER_LOAD_ADDR@;

    /* --------------------------------------------------
     * Text
     * -------------------------------------------------- */
    .text :
    {
        *(.text._start)      /* _start altijd eerst */
        *(.text*)
    }

    /* --------------------------------------------------
     * Read-only data (strings, constants)
     * -------------------------------------------------- */
    .rodata : ALIGN(16)
    {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
        . = ALIGN(16);
    }
    /* --------------------------------------------------
     * Data
     * -------------------------------------------------- */
    . = ALIGN(16);
    .data : ALIGN(16)
    {
        __data_start = .;
        . = ALIGN(16);
        *(.data .data.* .gnu.linkonce.d.*)
        . = ALIGN(16);
        __data_end = .;
    }

    /* --------------------------------------------------
     * BSS
     * BSS segment (for uninitialised C global variables).
     * BSS stands for "block starting symbol".
     * The BSS segment must be zeroed prior to entering C code.
     * -------------------------------------------------- */
    .bss : ALIGN(16)
    {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(16);
        __bss_end = .;
    }

    /* --------------------------------------------------
     * Exception vectors
     * -------------------------------------------------- */
    .vectors_core0 : ALIGN(0x800)
    {
        KEEP(*(.vectors_core0))
    }

#ifdef DUALCORE
    .vectors_core1 : ALIGN(0x800)
    {
        KEEP(*(.vectors_core1))
    }
#endif

    /* --------------------------------------------------
     * Stacks
     * -------------------------------------------------- */
    STACK_SIZE = 0x1000;   /* 4 KB per mode */
    .stacks (NOLOAD) : ALIGN(16)
    {
        . = ALIGN(16);
        __stack_start__ = .;

        /* ---------- Core 0 ---------- */
        . = . +STACK_SIZE;
        . = ALIGN(16);
        __stack_svc_top_core0 = .;

        . = . +STACK_SIZE;
        . = ALIGN(16);
        __stack_irq_top_core0 = .;
        
        . = . +STACK_SIZE;
        . = ALIGN(16);
        __stack_fiq_top_core0 = .;

    #ifdef DUALCORE
        /* ---------- Core 1 ---------- */
        . = . +STACK_SIZE;
        . = ALIGN(16);
        __stack_svc_top_core1 = .;

        . = . +STACK_SIZE;
        . = ALIGN(16);
        __stack_irq_top_core1 = .;

        . = . +STACK_SIZE;
        . = ALIGN(16);
        __stack_fiq_top_core1 = .;
    #endif

    /* --------------------------------------------------
     * Aliases / compatibility
     * -------------------------------------------------- */
    __stack_top__          = __stack_svc_top_core0;
    __stack_el1_top_core0  = __stack_svc_top_core0;

#ifdef DUALCORE
    __stack_el1_top_core1  = __stack_svc_top_core1;
#endif

    __stack_end__ = .;
    }
}