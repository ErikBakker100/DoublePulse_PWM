#include <stdbool.h>
#include "include/bitbuffer.h"
#include "include/config.h"
#include "include/stdlib.h"

// To calculate size and fill a buffer in uncached memory with the pattern based on the Intervals array
// The pulse_length array is a 4 byte array. The buffer is 32bits wide, retunrs the amount of words that we have filled in the buffer, so we know how many words to send in the DMA transfer.
// Note DMA sends 

uint32_t make_bit_buffer(volatile uint32_t* buffer, const uint16_t* pulse_length) {
    // Accept 16-bit interval values. If needed, adjust pulseInterval (index 3)
    // so total pattern length aligns to 32-bit boundaries.
    uint32_t pattern_len = (uint32_t)pulse_length[0] + (uint32_t)pulse_length[1] + (uint32_t)pulse_length[2] + (uint32_t)pulse_length[3];
    // If pattern_len is not divisible by 32, round up by extending pulseInterval (index 3).
    uint32_t rem = pattern_len % 32;
    if (rem != 0) {
        uint32_t add = 32 - rem;
        // modify the global Intervals to reflect the adjusted interval
        // (pulse_length points to Intervals in config.c)
        ((volatile uint16_t*)pulse_length)[3] = (uint16_t)((uint32_t)pulse_length[3] + add);
        pattern_len += add;
    }
    if (pattern_len == 0) return 0; // Veiligheid: voorkom deling door 0

    uint32_t word_len = 32;
    uint32_t a = pattern_len, b = word_len;

    // GGD berekenen
    while (b != 0) {
        uint32_t temp = b;
        b = a % b;
        a = temp;
    }
    uint32_t ggd = a;

    uint32_t total_bits = (pattern_len / ggd) * word_len;
    uint32_t num_elements = total_bits / 32;
    uint32_t num_repeats = total_bits / pattern_len;
    if (num_elements > BITSTREAM_WORDS) return 0;

    // Reset buffer
    for(uint32_t i = 0; i < num_elements; i++) buffer[i] = 0;

    uint32_t current_bit = 0;
    for (uint32_t r = 0; r < num_repeats; r++) {
        for (uint8_t i = 0; i < 4; i++) {
            uint32_t length = (uint32_t)pulse_length[i];
            bool is_high = (i % 2 == 0);

            if (is_high) {
                for (uint32_t b_idx = 0; b_idx < length; b_idx++) {
                    uint32_t word_idx = current_bit / 32;
                    uint32_t bit_pos = current_bit % 32;

                    // MSB-first mapping voor PWM/DMA
                    buffer[word_idx] |= (1U << (31 - bit_pos));
                    current_bit++;
                }
            } else {
                current_bit += length;
            }
        }
    }
    clean_cache(buffer, num_elements * sizeof(uint32_t)); // Clean the cache to ensure that the data in the bitstream is written to memory before the DMA transfer starts
    return num_elements; // Return het aantal uint32_t's dat we hebben gevuld
}

/*
2. DMA Control Block (CB) Setup
Dit is waar de magie gebeurt. Je vertelt de DMA dat hij na het 15e woord direct weer bij het 1e woord moet beginnen.

dma_cb_t control_block;

void setup_dma_loop() {
    control_block.info = (1 << 6) | (1 << 3) | (5 << 16); // DEST_DREQ, WAIT_RESP, PERMAP 5 (PWM)
    control_block.src = (uint32_t)dma_buffer_bus_addr;    // Bus adres van je buffer
    control_block.dest = 0x7e20c018;                     // PWM FIFO Bus adres
    control_block.length = BUFFER_WORDS * 4;             // 15 * 4 bytes
    control_block.next_cb = (uint32_t)cb_bus_addr;       // Wijs naar ZICHZELF voor loop
    
    // Schrijf CB adres naar DMA kanaal register...
}

Hardware continuïteit: De PWM-module vraagt via DREQ om nieuwe data zodra er plek is in de FIFO. De DMA vult dit direct aan.
Geen Bit-Padding: Omdat de totale buffer-lengte een veelvoud is van 32, hoeft de hardware nooit "loze" bits toe te voegen. Bit 480 wordt direct gevolgd door bit 1 van de volgende cyclus.
Klok-onafhankelijk: Omdat dit in hardware gebeurt, maken interrupts of CPU-belasting niet meer uit voor de timing van je pulsen.
Waarschuwing: Op de Zero 2W moet je het dma_buffer geheugen toewijzen via de Mailbox Property Interface "Uncached Memory" te krijgen. Als je gewone malloc gebruikt, 
ziet de DMA alleen oude data in het RAM en niet wat de CPU in de cache heeft geschreven.
Moet ik je helpen met de specifieke code om 'Uncached Memory' aan te vragen op de Pi?
*/
