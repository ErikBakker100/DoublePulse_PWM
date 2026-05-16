#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "../../include/boards.h"

typedef struct {
    uint32_t (*read)(uint8_t mailbox);
    void (*write)(uint8_t mailbox, uint32_t val);
} mailboxes_ops_t;
extern const mailboxes_ops_t *mailbox;
