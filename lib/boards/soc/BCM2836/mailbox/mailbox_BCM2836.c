#include "../include/BCM2836.h"
#include "include/mailbox_BCM2836.h"
#include "../../include/mailbox.h"
#include "../../../../general/include/stdlib.h"

static inline uint8_t validate_mailbox(uint8_t mailbox) {
    if (mailbox > 3) mailbox = 3;
    return mailbox;
}

uint32_t bcm2836_mailbox_read(uint8_t mailbox) {
    uint8_t nr = validate_mailbox(mailbox);
    uint32_t val = MAILBOX_2836->MBOX_CLR[nr];
    MAILBOX_2836->MBOX_CLR[nr] = 0xFFFFFFFF;              // Clear all bits
    return val;
}

void bcm2836_mailbox_write(uint8_t mailbox, uint32_t val) {
    uint8_t nr = validate_mailbox(mailbox);
    MAILBOX_2836->MBOX_CLR[nr] = 0xFFFFFFFF;              // Clear mailbox, writing a '1' clears that bit.
    MAILBOX_2836->MBOX_SET[nr] = val;
}

const mailboxes_ops_t bcm2836_mailbox = {
    .read   = bcm2836_mailbox_read,
    .write  = bcm2836_mailbox_write
};

void bcm2836_mailbox_init(void) {
    mailbox = &bcm2836_mailbox;
}
