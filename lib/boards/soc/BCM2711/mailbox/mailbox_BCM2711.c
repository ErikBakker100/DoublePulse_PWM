#include "../include/BCM2711.h"
#include "include/mailbox_BCM2711.h"
#include "../../include/mailbox.h"
#include "../../../../general/include/stdlib.h"
#include "../../../../cores/include/core0.h"

uint32_t bcm2711_mailbox_read(uint8_t mailbox) {
    return 0; // Reading from the mailbox is done via interrupts, so this function can be a stub.
}

void bcm2711_mailbox_write(uint8_t mailbox, uint32_t val) {
    // GICD_SGIR: Software Generated Interrupt Register
    // TargetListFilter (bits 25:24) = 00 (gebruik TargetList)
    // CPUTargetList (bits 23:16) = 0x02 (Core 1 is de tweede bit)
    // SGIINTID (bits 3:0) = de gewenste ID (bijv. 0)
    dmb();
    INT_GICD_2711->SGIR = (1 << 16) | (mailbox & 0xF);
    dmb();
}

const mailboxes_ops_t bcm2711_mailbox = {
    .read   = bcm2711_mailbox_read,
    .write  = bcm2711_mailbox_write
};

void bcm2711_mailbox_init(void) {
    mailbox = &bcm2711_mailbox;
}

// --------------------------------------------------------------
// Mailbox wrapper functions
// --------------------------------------------------------------
void bcm2711_mailbox_irq_handler(void *data) {
    uint32_t result = mailbox->read(0); // Read mailbox 0 for core0
    mailbox0(result);
}
