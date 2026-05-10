#include "include/soc.h"
#include "../../general/include/stdlib.h"
#include <stddef.h>

#include "BCM2835/include/BCM2835.h"
#include "BCM2836/include/BCM2836.h"
#include "BCM2837/include/BCM2837.h"
#include "BCM2711/include/BCM2711.h"
#include "BCM2712/include/BCM2712.h"

const soc_t soc_list[] = {
    {BCM2835, "Broadcom BCM2835"},
    {BCM2836, "Broadcom BCM2836"},
    {BCM2837, "Broadcom BCM2837"},
    {BCM2711, "Broadcom BCM2711"},
    {BCM2712, "Broadcom BCM2712"},
    {UNKNOWN, "Unknown SoC"}
};

const uintptr_t memory_table[][3] = {
    //physicalbase, local_periph_base, bus_base
    { 0x20000000UL, 0x00000000UL, 0x7E000000}, // BCM2835
    { 0x3F000000UL, 0x40000000UL, 0x7E000000}, // BCM2836
    { 0x3F000000UL, 0x40000000UL, 0x7E000000}, // BCM2837
    { 0xFE000000UL, 0xFF800000UL, 0x7E000000}, // BCM2711
    { 0xFE000000UL, 0xFF800000UL, 0x7E000000}, // BCM2712, TODO: BCM2712 requires new mapping (RP1 southbridge)
    { 0x00000000UL, 0x00000000UL, 0x7E000000}  // UNKNOWN
};
const uint8_t memory_table_len = ARRAY_SIZE(memory_table);

void soc_init(soc_t *soc){
        soc_list_t id = soc->id;
        soc->data.phys_base = memory_table[id][0];
        soc->data.local_periph_base = memory_table[id][1];
        soc->data.bus_base = memory_table[id][2];
        soc->name = soc_list[id].name;
    switch (id) {
        case BCM2835:
            BCM2835_init(soc);
            break;
        case BCM2836:
            BCM2836_init(soc);
            break;
        case BCM2837:
            BCM2837_init(soc);
            break;
        case BCM2711:
            BCM2711_init(soc);
            break;
        case BCM2712:
            BCM2712_init(soc);
            break;
        case UNKNOWN:                       // board not found, error
            break;
    }
}
