#pragma once
#include <stdint.h>

extern void bcm2711_mailbox_init(void);

void bcm2711_mailbox_irq_handler(void *);