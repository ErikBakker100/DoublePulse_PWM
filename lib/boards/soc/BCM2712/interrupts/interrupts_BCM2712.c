#include "include/interrupts_BCM2712.h"

/*
In GICv3 (GIC-600) gebruik je voor de CPU Interface (IAR, EOIR, PMR) geen MMIO meer via een struct. In plaats daarvan gebruik je assembly:
Acknowledge interrupt: mrs x0, S3_0_C12_C8_0 (Lezen van ICC_IAR1_EL1)
End of Interrupt: msr S3_0_C12_C8_1, x0 (Schrijven naar ICC_EOIR1_EL1)
Basisadres: 0xFE000000 (Low Peripheral mode) of 0xFF800000 (High Peripheral mode). De GIC zit meestal in het 0xFF800000 gebied.
GICR per core: Je moet weten op welke core je draait om het juiste Redistributor-blok te vinden (Core 0 is base, Core 1 is base + 0x20000, etc.).
WAKER register: Bij de GIC-600 moet je bij initialisatie bit 1 (ProcessorSleep) van het GICR_WAKER register op 0 zetten en wachten tot bit 2 (ChildrenAsleep) ook 0 is, anders ontvangt de core nooit interrupts.
*/