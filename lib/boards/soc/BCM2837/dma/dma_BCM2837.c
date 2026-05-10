#include <stddef.h>
#include "../include/BCM2837.h"
#include "include/dma_BCM2837.h"
#include "../../include/dma.h"
#include "../../../../general/include/stdlib.h"
#include "../../../../general/include/bitbuffer.h"
#include "../../../../general/include/config.h"
#include "../../../include/boards.h"
#include "../../../include/mailbox_vc.h"

// vertelt de GPU om de L1/L2 caches te omzeilen
#define VC_RAM_BUS_ALIAS 0xC0000000UL
#define VC_RAM_BUS_MASK  0x3FFFFFFFUL

//rondt een getal naar boven af naar de dichtstbijzijnde "alignment".
#define ALIGN_UP(value, align) (((value) + ((align) - 1)) & ~((align) - 1))

void bcm2837_dma_run(void) {
    static uint32_t dma_mem_h = 0;
    static uint32_t dma_mem_bus = 0;

    if (!dma_mem_h) { // if not previous done, Get some uncached memory
        dma_mem_h = alloc_vc_mem(VC_PAGE_SIZE, MEM_FLAG_L1_NONALLOCATING | MEM_FLAG_ZERO); // First we need an ID (handle) for the memory we want to allocate, we ask the GPU to allocate a page of memory.
        dma_mem_bus = (uint32_t)(uintptr_t)lock_vc_mem(dma_mem_h); // Now we need an address based on the ID
    }

    uint32_t cb_bus_addr = ALIGN_UP(dma_mem_bus, 32); // De DMA-eis
    uintptr_t cb_arm_addr = cb_bus_addr & VC_RAM_BUS_MASK; // De CPU-vertaling

    #define BITSTREAM_OFFSET 0x100 // Ruim genoeg voor 1 DMA CB (32 bytes) + padding
    uintptr_t bitstream_arm_addr = cb_arm_addr + BITSTREAM_OFFSET;
    uint32_t bitstream_bus_addr = cb_bus_addr + BITSTREAM_OFFSET;
    volatile bcm2835_dma_ctrl_blck_t *cb = (volatile bcm2835_dma_ctrl_blck_t *)cb_arm_addr;
    volatile uint32_t *dma_bitstream = (volatile uint32_t *)bitstream_arm_addr;

    memset((void *)cb, 0, sizeof(*cb));
    uint32_t length = make_bit_buffer(dma_bitstream, (const uint8_t*)Intervals); // returns the amount of 32-bit words that we have filled in the buffer.
    if (length == 0) {
        DMA05_2837->CS = CS_RESET;          // Stop de DMA als er geen data is
        return;
    }
    clean_cache((void *)dma_bitstream, length * sizeof(uint32_t));
    
    cb->TI = 0 | TI_WAIT_RESP | TI_DEST_DREQ | TI_SRC_INC | TI_PERMAP(5); // Set the control block flags for the DMA transfer, wait for the write response, 
                                            // use DREQ to pace the transfer based on the PWM FIFO status, increment the source address after each read, and set the peripheral mapping to 5 for PWM.
    cb->SOURCE_AD = bitstream_bus_addr;
    cb->DEST_AD = ((uint32_t)&PWM0_2837->FIF & 0x00FFFFFF) | board.soc.data.bus_base; // (uint32_t)(uintptr_t)0x7E20C018 het adres van de PWM FIFO register. We gebruiken een bus adres omdat de DMA-engine alleen bus adressen begrijpt.
    cb->TXFR_LEN = length * sizeof(uint32_t); // Convert number of 32-bit words to number of bytes
    cb->STRIDE = 0; // No stride for simple 1D transfers
    cb->NEXTCONBK = cb_bus_addr;
    
    clean_cache((void *)cb, sizeof(*cb));   // Clean the cache to ensure that the data in the control block is written to memory before the DMA transfer starts
    DMA05_2837->CONBLK_AD = cb_bus_addr;    // Set the control block bus address for the DMA channel.
    DMAEN_2837->ENABLE |= DMA_CHANNEL_5;
    DMA05_2837->CS = CS_RESET;
    while (DMA05_2837->CS & CS_RESET) { }   // Wacht tot reset klaar is
    DMA05_2837->CS = CS_INT | CS_END;       // Clear status vlaggen
    DMA05_2837->CONBLK_AD = cb_bus_addr;    // Set the control block bus address for the DMA channel.
    DMA05_2837->CS = CS_PRIORITY | CS_PANIC_PRIORITY | CS_WAIT_FOR_OUTSTANDING_WRITES | CS_ACTIVE;
}

const dma_ops_t bcm2837_dma_ops = {
    .run    = bcm2837_dma_run
};

void bcm2837_dma_init(void) {
    dma = &bcm2837_dma_ops;
}
