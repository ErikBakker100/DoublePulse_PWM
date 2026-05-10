#pragma once
#include <stdint.h>
#include "../../include/BCM2837.h"

void bcm2837_dma_init(void);                // Set dma function pointers
void bcm2837_dma_run(void);
