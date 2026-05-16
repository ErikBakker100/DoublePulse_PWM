#pragma once
#include <stdint.h>

uint32_t make_bit_buffer(volatile uint32_t* buffer, const uint16_t* pulse_length);
