#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "spam.h"

PG_REGISTER_WITH_RESET_TEMPLATE(spamConfig_t, spamConfig, PG_SPAM_CONFIG, 0);