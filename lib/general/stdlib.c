#include "include/stdlib.h"

uint32_t strlen(const char *s) {
    uint32_t len = 0;
    while (*s++) len++;
    return len;
}

int32_t strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    } 
    return *(const unsigned char *)s1 - *(const unsigned char *)s2; 
}

char *strncpy(char *dest, const char *src, uint32_t n) {
    uint32_t i;
    for (i = 0; i < n && src[i]; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

uint32_t strtoul(const char *nptr, char **endptr, int base) {
    uint32_t result = 0;
    while (*nptr >= '0' && *nptr <= '9') {
        result = result * base + (*nptr - '0');
        nptr++;
    }
    if (endptr) *endptr = (char *)nptr;
    return result;
}

void u32_to_str(uint32_t value, char *buf) {
    char tmp[10];
    int i = 0;
    // Speciale case: 0
    if (value == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    // Cijfer voor cijfer in omgekeerde volgorde
    while (value > 0 && i <10) {
        tmp[i++] = '0' + (value % 10);
        value /= 10;
    }
    // Draai de volgorde om in buf[]
    int j = 0;
    while (i > 0) {
        buf[j++] = tmp[--i];
    }
    buf[j] = '\0';  // nulterminator
}

void *memset(void *dst, int v, uint32_t n)
{
    unsigned char *p = dst;
    while (n--) *p++ = (unsigned char)v;
    return dst;
}

void delay(unsigned long count) {
    while (count--) {
        asm volatile("nop");
    }
}

/* Data Memory Barrier, dmb zorgt er voor dat de volgorde van geheugenacties behouden blijft. De processor mag instructies die na de dmb komen alvast uitvoeren, behalve als die instructies het geheugen aanraken. */
void dmb(void) {
    #if defined(__arm__) && (__ARM_ARCH <= 6)
        // ARMv6 (Pi 1 / Zero)
        __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 5" : : "r" (0) : "memory");
    #else
        // ARMv7 en ARMv8 (Pi 2, 3, 4, 5 in zowel 32-bit als 64-bit)
        __asm__ __volatile__ ("dmb sy" : : : "memory");
    #endif
}

/* Data Synchronization Barrier - Wacht tot alle geheugenacties echt klaar zijn. Het legt de hele executie van de processor stil totdat alle voorgaande geheugenacties volledig zijn afgerond. */
void dsb(void)
{
#if defined(__aarch64__)
    /* ARMv8-A AArch64 */
    __asm__ volatile ("dsb sy" ::: "memory");

#elif defined(__ARM_ARCH_8A__)
    /* ARMv8-A AArch32 (Cortex-A53 in 32-bit mode) */
    __asm__ volatile ("dsb sy" ::: "memory");

#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__)
    /* ARMv7-A / ARMv7-R */
    __asm__ volatile ("dsb sy" ::: "memory");

#elif defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    /* Cortex-M (geen shareability domains) */
    __asm__ volatile ("dsb" ::: "memory");

#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || \
      defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || \
      defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6KZ__)
    /* ARMv6 barrier via CP15 */
    __asm__ volatile ( "mcr p15, 0, r0, c7, c10, 4\n" ::: "memory");
#else
#error "dsb: unsupported architecture"
#endif
}

/* Instruction Synchronization Barrier
 Een isb is nodig in situaties waarbij de context van de processor verandert. Als je dit niet doet, voert de CPU instructies uit op basis van de "oude" regels.
*/
void isb(void)
{
#if defined(__aarch64__)
    /* ARMv8-A AArch64 */
    __asm__ volatile ("isb" ::: "memory");

#elif defined(__ARM_ARCH_8A__)
    /* ARMv8-A AArch32 (Cortex-A53 in 32-bit mode) */
    __asm__ volatile ("isb" ::: "memory");

#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__)
    /* ARMv7-A / ARMv7-R */
    __asm__ volatile ("isb" ::: "memory");

#elif defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    /* Cortex-M */
    __asm__ volatile ("isb" ::: "memory");

#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || \
      defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || \
      defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6KZ__)
    /* ARMv6 ISB via CP15 */
    __asm__ volatile ( "mcr p15, 0, r0, c7, c5, 4\n" ::: "memory");

#else
#error "isb: unsupported architecture"
#endif
}

/*
Send Event
De "Wekker". De sev instructie stuurt een signaal naar alle cores in het systeem. Elke core die op dat moment in een wfe-slaapstand staat, wordt direct wakker en gaat weer verder met zijn werk.
Wanneer gebruik je dit?
Multicore communicatie: Core 0 is bezig een mailbox-bericht te verwerken, terwijl Core 1 slaapt (wfe). Zodra Core 0 klaar is en de data in het RAM heeft gezet, roept hij sev() aan om Core 1 te wekken zodat deze het resultaat kan verwerken.*/
void sev(void)
{
    __asm__ volatile ("sev");
}

/*
Wait for event 
De "Slaapstand". Wanneer een CPU-core een wfe instructie tegenkomt, stopt hij onmiddellijk met het uitvoeren van code en gaat hij in een energiezuinige stand. Hij blijft daar "slapen" totdat er een specifiek signaal (een "event") binnenkomt.
Wanneer gebruik je dit?
Spinlocks: Als je wacht tot een andere core een variabele vrijgeeft. In plaats van constant de waarde te checken (wat veel stroom kost en de geheugenbus belast), gebruik je wfe.
Idle loop: In je main loop, als er even niets te doen is, kun je de CPU laten slapen tot de volgende interrupt.
*/
void wfe(void)
{
    __asm__ volatile ("wfe");
}

#if defined(__aarch64__)
#define CACHE_LINE_SIZE 64
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_8A__)
#define CACHE_LINE_SIZE 64
#else
#define CACHE_LINE_SIZE 32
#endif

/* Cache Clean - Duw data van Cache naar RAM */
void clean_cache(const volatile void *addr, uint32_t size) {
    uintptr_t start = (uintptr_t)addr;
    uintptr_t end = start + size;
    // ARM11 cache lines zijn 32 bytes
    for (uintptr_t a = start & ~(CACHE_LINE_SIZE - 1); a < end; a += CACHE_LINE_SIZE) {
#if defined(__aarch64__)
        /* ARMv8 64-bit */
        __asm__ volatile ("dc cvac, %0" :: "r"(a) : "memory");
#else
        /* ARMv6 / ARMv7 / ARMv8 AArch32 */
        __asm__ volatile ("mcr p15, 0, %0, c7, c10, 1" : : "r"(a) : "memory");
#endif
    }
    dsb(); // Wacht tot het flashen klaar is
}

void invalidate_cache(const volatile void *addr, uint32_t size) {
    uintptr_t start = (uintptr_t)addr;
    uintptr_t end = start + size;
    for (uintptr_t a = start & ~(CACHE_LINE_SIZE - 1); a < end; a += CACHE_LINE_SIZE) {
#if defined(__aarch64__)
        /* ARMv8 64-bit */
        __asm__ volatile ("dc ivac, %0" :: "r"(a) : "memory");
#else
        /* ARMv6 / ARMv7 / ARMv8 AArch32 */
        __asm__ volatile ("mcr p15, 0, %0, c7, c6, 1" : : "r"(a) : "memory");
#endif
    }
    dsb();
}
