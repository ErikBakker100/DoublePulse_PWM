#pragma once
#include <stdbool.h>
#include "../../general/include/config.h"
#include "../../general/include/stdlib.h"
#include "../soc/include/soc.h"
#include "../include/mailbox_vc.h"
#include <stddef.h>

/*
Revision	Model	        PCB Revision	Memory	        CPU Core            Partnumber  SoC         CORE_FREQ   ARM_FREQ    Network                                     Cores   Notes
code                                                                            MIDR reg                GHz         GHz    
900021      A+	            1.1	            512 MB	        ARM1176JZF-S        0xB76       BCM2835     0.7         0.70        none                                        1       (Mfg by Sony)
900032	    B+	            1.2	            512 MB	        ARM1176JZF-S        0xB76       BCM2835     0.7         0.70        10/100 Eth                                  1       (Mfg by Sony)
a01040	    2B	            1.0	            1 GB	        Cortex A7 (Armv7)   0xC07       BCM2836     0.25        0.90        10/100 Eth                                  4       (Mfg by Sony)
a01041	    2B	            1.1	            1 GB	        Cortex A7 (Armv7)   0xC07       BCM2836     0.25        0.90        10/100 Eth                                  4       (Mfg by Sony)
a21041	    2B	            1.1	            1 GB	        Cortex A7 (Armv7)   0xC07       BCM2836     0.25        0.90        10/100 Eth                                  4       (Mfg by Embest)
a02042      2B              1.2             1 GB            Cortex A53 (Armv8)  0xC07       BCM2837                 1.20        10/100 Eth                                  4       (Mfg by Sony)
a22042	    2B              1.2	            1 GB	        Cortex A53 (Armv8)  0xC07       BCM2837                 1.20        10/100 Eth                                  4       (Mfg by Embest)
900061	    CM1             1.0	            512 MB	        ARM1176JZF-S        0xB76       BCM2835                 0.70        Depends on carrier board                    1       (Mfg by Sony)
a02082	    3B      	    1.2	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837                             10/100 Eth, , BT 4.1                        4       (Mfg by Sony) https://developer.arm.com/documentation/ddi0500/latest/
a22081	    3B	            1.1	            1 GB	        Cortex A7 (Armv7)   0xC07       BCM2836     0.25        1.20        10/100 Eth, 802.11n WiFi, BT 4.1            4       (Mfg by Embest)
a22082	    3B	            1.2	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837     0.25        1.20        10/100 Eth, 802.11n WiFi, BT 4.1            4       (Mfg by Embest)
a22083	    3B	            1.3	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837B0               1.20        10/100 Eth, 802.11n WiFi, BT 4.1            4       (Mfg by Embest)
a52082	    3B	            1.2	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837     0.25        1.20        10/100 Eth, 802.11n WiFi, BT 4.1            4       (Mfg by Stadium)
a32082	    3B	            1.2	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837     0.25        1.20        10/100 Eth, 802.11n WiFi, BT 4.1            4       (Mfg by Sony Japan)
900092	    Zero	        1.2	            512 MB	        ARM1176JZF-S        0xB76       BCM2835     0.25        0.70        none                                        1       (Mfg by Sony)
920092	    Zero	        1.2	            512 MB	        ARM1176JZF-S        0xB76       BCM2835     0.25        0.70        none                                        1       (Mfg by Embest)
900093      Zero            1.3             512 MB	        ARM1176JZF-S        0xB76       BCM2835     0.25        0.70        none                                        1       (Mfg by Sony)
920093      Zero            1.3             512 MB	        ARM1176JZF-S        0xB76       BCM2835     0.25        0.70        none                                        1       (Mfg by Embest)
902120	    Zero 2 W	    1.0	            512 MB	        Cortex A53          0xD03       RP3A0       0.25        1.00        802.11n WiFi; BT                            2       (Mfg by Sony), System-in-Package (SiP) consisting of a Broadcom BCM2710A1 — silicon die packaged inside the Broadcom BCM2837
9000c1      Zero W          1.1             512 MB	        ARM1176JZF-S        0xB76       BCM2835     0.25        0.70        802.11n WiFi, BT                            1       (Mfg by Sony)
a020a0	    CM3      	    1.0	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837                 1.20        Depends on carrier board                    4       (Mfg by Sony)
a220a0	    CM3      	    1.0	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837                 1.20        Depends on carrier board                    4       (Mfg by Embest)
a02100      CM3+            1.0             1 GB            Cortex A53 (Armv8)  0xD03       BCM2837                 1.20        Depends on carrier board                    4       (Mfg by Sony)
a020d3	    3B+	            1.3	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837     0.25        1.40        10/100/1000 Eth, dual 802.11n WiFi BT 4.2   4       (Mfg by Sony)
a020d4	    3B+	            1.4	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837     0.25        1.40        10/100/1000 Eth, dual 802.11n WiFi BT 4.2   4       (Mfg by Sony)
9020e0	    3A+	            1.0	            512 MB	        Cortex A53 (Armv8)  0xD03       BCM2837B0   0.25        1.40        802.11ac WiFi (no Ethernet)                 4       (Mfg by Sony)
9020e1	    3A+	            1.1	            512 MB	        Cortex A53 (Armv8)  0xD03       BCM2837B0   0.25        1.40        802.11ac WiFi (no Ethernet)                 4       (Mfg by Sony)
a02100	    CM3+            1.0	            1 GB	        Cortex A53 (Armv8)  0xD03       BCM2837B0               1.20        Depends on carrier board                    4       (Mfg by Sony)
a03140      CM4             1.0             1 GB            Cortex-A72 (Armv8-A)0xD08       BCM2711                 1.50        Depends on carrier board                    4       (Mfg by Sony)
b03140      CM4             1.0             2 GB            Cortex-A72 (Armv8-A)0xD08       BCM2711                 1.50        Depends on carrier board                    4       (Mfg by Sony)
c03140      CM4             1.0             4 GB            Cortex-A72 (Armv8-A)0xD08       BCM2711                 1.50        Depends on carrier board                    4       (Mfg by Sony)
d03140      CM4             1.0             8 GB            Cortex-A72 (Armv8-A)0xD08       BCM2711                 1.50        Depends on carrier board                    4       (Mfg by Sony)
a03111	    4B      	    1.1	            1 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
b03111	    4B      	    1.1	            2 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
b03112	    4B      	    1.2	            2 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
b03114	    4B      	    1.4	            2 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
b03115	    4B      	    1.5	            2 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
c03111	    4B      	    1.1	            4 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
c03112	    4B      	    1.2	            4 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
c03114	    4B      	    1.4	            4 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
c03115	    4B      	    1.5	            4 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
d03114	    4B      	    1.4	            8 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
d03115	    4B      	    1.5	            8 GB	        Cortex-A72 (Armv8-A)0xD08       BCM2711     0.50        1.50        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
c03130      400             1.0             4 GB            Cortex-A72 (Armv8-A)0xD08       BCM2711                 1.80        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
b04170      5               1.0             2 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712     1.00        2.00        Enh. 10/100/1000 Eth, dual 802.11n WiFi BT5 4       (Mfg by Sony)
c04170      5               1.0             4 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712     1.00        2.00        (Mfg by Sony)
d04170      5               1.0             8 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712     1.00        2.00        (Mfg by Sony)
b04171      5               1.1             2 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712     1.00        2.00        (Mfg by Sony)
c04171      5               1.1             4 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712     1.00        2.00        (Mfg by Sony)
d04171      5               1.1             8 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712     1.00        2.00        (Mfg by Sony)
e04171      5               1.1             16 GB           Cortex-A76 (Armv8-A)0xD0B       BCM2712     1.00        2.00        (Mfg by Sony)
b04180      CM5             1.0             2 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        Depends on carrier board                    4       (Mfg by Sony)
c04180      CM5             1.0             4 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        Depends on carrier board                    4       (Mfg by Sony)
d04180      CM5             1.0             8 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        Depends on carrier board                    4       (Mfg by Sony)
e04180      CM5             1.0             16 GB           Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        Depends on carrier board                    4       (Mfg by Sony)
d04190      500             1.0             8 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
e04190      500             1.0             16 GB           Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        10/100/1000 Eth, dual 802.11ac WiFi BT 5    4       (Mfg by Sony)
b041a0      CM5 Lite        1.0             2 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        Depends on carrier board                    4       (Mfg by Sony)
c041a0      CM5 Lite        1.0             4 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        Depends on carrier board                    4       (Mfg by Sony)
d041a0      CM5 Lite        1.0             8 GB            Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        Depends on carrier board                    4       (Mfg by Sony)
e041a0      CM5 Lite        1.0             16 GB           Cortex-A76 (Armv8-A)0xD0B       BCM2712                 2.00        Depends on carrier board                    4       (Mfg by Sony)
*/



typedef struct {
    const char* description;
    uint8_t  rev_scheme;                    // 0 = oud, 1 = nieuw (Bit 23)
    const char *memory_size;                // Hoeveelheid RAM (Bits 20-22)
    const char *manufacturer;               // Fabrikant (Bits 16-19)
                                            // SoC type (Bits 12-15)
    uint16_t revision_model_type;           // Model (Pi 2, 3, 3B+, etc.) (Bits 4-11)
    uint8_t  revision_num;                  // Versienummer van de PCB (Bits 0-3)
    uint32_t revision_raw_value;            // De originele hex-waarde
    int32_t baudrate;                       // set via config.h
    uint32_t firmware_date;                 // set during board_init
    uint64_t serial;                        // set during board_init
    uint8_t mac_address[6];                 // set during board_init
    uint32_t arm_memory_base;               // set during board_init
    uint32_t arm_memory_size;               // set during board_init
    uint32_t gpu_memory_base;               // set during board_init
    uint32_t gpu_memory_size;               // set during board_init
    uint32_t soc_temperature;               // set during board_init
    uint32_t clock_rates[CLOCK_SIZE];       // set during board_init
    uint32_t clock_rates_measured[CLOCK_SIZE]; // set during board_init
    uint32_t max_clock_rates[CLOCK_SIZE];   // set during board_init
    uint32_t min_clock_rates[CLOCK_SIZE];   // set during board_init
    soc_t soc;                              // set during board_init
} board_data_t;

extern board_data_t board;

bool board_init(board_data_t *board);

