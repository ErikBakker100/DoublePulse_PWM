#pragma once
#include <stdint.h>
#include "../cpu/include/cpu.h"

typedef enum {
    BCM2835,                                // 0x0
    BCM2836,                                // 0x1
    BCM2837,                                // 0x2
    BCM2711,                                // 0x3
    BCM2712,                                // 0x4
    UNKNOWN
} soc_list_t;

typedef struct {
    uintptr_t phys_base;
    uintptr_t local_periph_base;
    uintptr_t bus_base;
} soc_data_t;
extern const uintptr_t memory_table[][3];
extern const uint8_t memory_table_len;

typedef struct {
    soc_list_t id;
    const char* name;
    soc_data_t data;
    cpu_t cpu;
} soc_t;

extern soc_t soc;

void soc_init(soc_t *soc);
