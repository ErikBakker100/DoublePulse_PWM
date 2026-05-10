#include <stddef.h>
#include "include/date_time.h"

date_time_t date_time;

void format_firmware_time(uint32_t timestamp, date_time_t *dt) {
    dt->second = timestamp % 60;
    dt->minute = (timestamp / 60) % 60;
    dt->hour   = (timestamp / 3600) % 24;
}

uint16_t is_leap(uint16_t year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void format_firmware_date(uint32_t timestamp, date_time_t *dt) {
    uint32_t days = timestamp / 86400;

    dt->year = 1970;

    // 1. Jaar bepalen
    while (1) {
        uint32_t days_in_year = is_leap(dt->year) ? 366 : 365;
        if (days < days_in_year) break;
        days -= days_in_year;
        dt->year++;
    }

    // 2. Maanden bepalen
    uint8_t month_days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (is_leap(dt->year)) {
        month_days[1] = 29;
    }

    dt->month = 0;
    while (days >= month_days[dt->month]) {
        days -= month_days[dt->month];
        dt->month++;
    }

    dt->month += 1;
    dt->day = days + 1;
}

void format_firmware_date_time(uint32_t timestamp, date_time_t *dt) {
    if (dt == NULL) return;
    format_firmware_time(timestamp, dt);
    format_firmware_date(timestamp, dt);
}