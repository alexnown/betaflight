#pragma once

#include "pg/pg.h"
#include "drivers/io_types.h"

typedef struct spamConfig_s {
    uint16_t value;
    uint16_t value2;
} spamConfig_t;

PG_DECLARE(spamConfig_t, spamConfig);