#pragma once

#include "common/time.h"

#define SPAM_BAUDRATE 9600

void spamInit(void);
void spamUpdate(timeUs_t currentTimeUs);