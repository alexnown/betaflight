#pragma once
#include "common/time.h"

#define SPAM_BAUDRATE 38400

//typedef struct spamState_s {
//    uint8_t             data; 
//} spamState_t;

void spamInit(void);
void spamUpdate(timeUs_t currentTimeUs);
bool changeDebugAuxValue(int ch);
float getDebugAuxValue(int ch);
uint16_t getSpamOSDState(void);