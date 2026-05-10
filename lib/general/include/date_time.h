#pragma once
#include <stdint.h>

typedef struct {
    uint16_t year;    // Bijv. 2025
    uint8_t  month;   // 1 - 12
    uint8_t  day;     // 1 - 31
    uint8_t  hour;    // 0 - 23
    uint8_t  minute;  // 0 - 59
    uint8_t  second;  // 0 - 59
    uint16_t ms;      // 0 - 999
} date_time_t;
extern date_time_t date_time;

void format_firmware_date_time(uint32_t timestamp, date_time_t *dt);