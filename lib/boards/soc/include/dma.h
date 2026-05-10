#pragma once
#include <stdint.h>
#include "../BCM2835/include/BCM2835.h"
typedef struct {
    // handlers for dma functions
    void (*run)(void);                      // Start DMA transfer
} dma_ops_t;
extern const dma_ops_t *dma;


