#pragma once
#include <stdint.h>

void start_core(uint8_t core_nr); // Set entry point for core1
void mailbox0(uint32_t);
