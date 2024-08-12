#pragma once
#include <stdio.h>
#include "common/time.h"

#define SPAM_BAUDRATE 38400

void spamInit(void);
void spamUpdate(timeUs_t currentTimeUs);
void changeAuxValue(float rcData[]);