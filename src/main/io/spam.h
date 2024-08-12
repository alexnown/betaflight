#pragma once
#include "common/time.h"

#define SPAM_BAUDRATE 38400

void spamInit(void);
void spamUpdate(timeUs_t currentTimeUs);
bool changeDebugAuxValue(int ch);
float getDebugAuxValue(int ch);