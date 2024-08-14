#include "spam.h"
#include "pg/spam.h"
#include "io/serial.h"
#include "fc/rc_modes.h"

static serialPort_t *spamPort;
uint16_t _receivedData;
uint16_t _receivedData2;
typedef struct spamFractialsData_s {
    unsigned int chan0 : 2;
    unsigned int chan1 : 2;
    unsigned int chan2 : 2;
    unsigned int chan3 : 2;
} __attribute__((__packed__)) spamFractialsData_t;

#define SPAM_DATA_LENGTH sizeof(spamFractialsData_t)

struct spamFrame_s {
    uint8_t syncByte;
    spamFractialsData_t data;
} __attribute__ ((__packed__));

typedef union spamFrame_u {
    uint8_t bytes[2];
    struct spamFrame_s frame;
} spamFrame_t;

typedef struct spamFrameData_s {
    spamFrame_t frame;
    //wtf
    timeUs_t startAtUs;
    uint8_t position;
    bool done;
} spamFrameData_t;


static void spamDataReceive(uint16_t c, void *data)
{
    _receivedData = c;
    spamFrameData_t *frameData = data;
    _receivedData2 = frameData->frame.frame.syncByte;
}

uint16_t getSpamOSDState(void) {
    return _receivedData;
}

void spamInit(void) {
    
    const serialPortConfig_t *spamPortConfig = findSerialPortConfig(FUNCTION_ACTIVATION_DEVICE);
    serialPortIdentifier_e uartIdentifier = spamPortConfig ? spamPortConfig->identifier : SERIAL_PORT_UART5;
    /*
    if ((spamPortConfig->identifier >= SERIAL_PORT_USART1) && (spamPortConfig->identifier <= SERIAL_PORT_USART_MAX)){
        options |= SERIAL_CHECK_TX;
    } 
    debugSerialPort = openSerialPort(DPRINTF_SERIAL_PORT, FUNCTION_NONE, NULL, NULL, 115200, MODE_RXTX, 0);
    if (debugSerialPort) {
        setPrintfSerialPort(debugSerialPort);
    }
    dprintf(("smartAudioInit: OK\r\n")); */
    spamPort = openSerialPort(uartIdentifier, FUNCTION_ACTIVATION_DEVICE, spamDataReceive, NULL, SPAM_BAUDRATE, MODE_RXTX, 0);
}

bool changeDebugAuxValue(int ch) {
    UNUSED(ch);
    return ch>=6 && ch<=7;
}
float getDebugAuxValue(int ch) {
    //UNUSED(ch);
    switch(ch) {
        case 6:
        return 1000+_receivedData;
        case 7:
        return 1000+_receivedData2;
    }
    return 999;
}

void spamUpdate(timeUs_t currentTimeUs) {
    UNUSED(currentTimeUs);
    
    if (!spamPort) {
        return;
    }
    uint8_t data = 1 | IS_RC_MODE_ACTIVE(BOXUSER1) << 1 
    | IS_RC_MODE_ACTIVE(BOXUSER2)<<2
    | IS_RC_MODE_ACTIVE(BOXUSER3)<<3
    | IS_RC_MODE_ACTIVE(BOXUSER4)<<4;
    serialWrite(spamPort, data);
    //serialWriteBuf(spamPort, (uint8_t *)"Hallo\r\n", 7);
    
}