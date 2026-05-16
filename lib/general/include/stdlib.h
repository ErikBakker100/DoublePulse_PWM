#pragma once
#include <stdint.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define NULL ((void *)0)
#define BIT_IS_SET(reg, mask) (((reg) & (mask)) != 0) // true if bit(s) is(are) set, false if not

uint32_t strlen(const char *);
int32_t strcmp(const char *, const char *);
char *strncpy(char *, const char *, uint32_t);
uint32_t strtoul(const char *, char **, int);
void u32_to_str(uint32_t value, char *buf);
void *memset(void *, int, uint32_t);
    
// Delay loop
#define DELAY(count) do { volatile uint32_t _i = (count); while (_i--) asm volatile("nop"); } while(0)

/* Data Memory Barrier */
void dmb(void);
/* Data Synchronization Barrier */
void dsb(void);
/* Instruction Synchronization Barrier */
void isb(void);
/* Cache Clean */
void clean_cache(const volatile void *, uint32_t);
void invalidate_cache(const volatile void *, uint32_t);
/* Send Event */
void sev(void);
/* Wait for Event */
void wfe(void);
