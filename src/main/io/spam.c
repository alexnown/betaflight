#include "spam.h"
#include "io/serial.h"
#include "fc/rc_modes.h"

static serialPort_t *spamPort;

static void spamDataReceive(uint16_t c, void *data)
{
    UNUSED(data);
    spamConfigMutable()->value = c;
}

uint16_t getSpamOSDState(void) {
    return spamConfig()->value;
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
    return false;//ch>=6 && ch<=8;
}
float getDebugAuxValue(int ch) {
    switch (ch)
    {
    default:
        return 999;
    }
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