#include "../include/BCM2837.h"
#include "include/mailbox_BCM2837.h"
#include "../../include/mailbox.h"
#include "../../../../general/include/stdlib.h"

static inline uint8_t validate_mailbox(uint8_t mailbox, uint8_t core) {
    if (mailbox > 3) mailbox = 3;
    if (core > 3) core = 3;
    return (core * 4) + mailbox;
}

uint32_t bcm2837_mailbox_read(uint8_t mailbox, uint8_t core) {
    uint8_t nr = validate_mailbox(mailbox, core);
    dmb();
    uint32_t val = MAILBOX_2837->MBOX_CLR[nr];
    MAILBOX_2837->MBOX_CLR[nr] = 0xFFFFFFFF;              // Clear all bits
    dmb();
    return val;
}

void bcm2837_mailbox_write(uint8_t mailbox, uint8_t core, uint32_t val) {
    uint8_t nr = validate_mailbox(mailbox, core);
    MAILBOX_2837->MBOX_CLR[nr] = 0xFFFFFFFF;              // Clear mailbox, writing a '1' clears that bit.
    dmb();
    MAILBOX_2837->MBOX_SET[nr] = val;
    dmb();
}

const mailboxes_ops_t bcm2837_mailbox = {
    .read   = bcm2837_mailbox_read,
    .write  = bcm2837_mailbox_write
};

void bcm2837_mailbox_init(void) {
    mailbox = &bcm2837_mailbox;
}
