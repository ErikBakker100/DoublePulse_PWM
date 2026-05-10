#pragma once
#include <stdint.h>

void core_main_1(void); // Function to be executed by core1 after start
void start_core(uint8_t core_nr); // Set entry point for core1
extern void core_entry_1(void); // Entry point defined in startxx.s
void doublepulse_generator(uint32_t, uint32_t, uint32_t, uint32_t); // Function to generate the double pulse pattern
void mailbox0(uint32_t);
