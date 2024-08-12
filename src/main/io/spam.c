#include "spam.h"
#include "io/serial.h"
#include "fc/rc_modes.h"

static serialPort_t *spamPort;
uint16_t _counterRx;
uint16_t _counterTx;
uint16_t _counterTx2;
uint16_t _receivedState;

static void spamDataReceive(uint16_t c, void *data)
{
    UNUSED(data);
    _receivedState = c;
}

uint8_t getOSDState(void) {
    return _receivedState;
}

void spamInit(void) {
    /*
    const serialPortConfig_t *spamPortConfig = findSerialPortConfig(FUNCTION_GPS);
    if (!spamPortConfig) {
        return;
    }
    if ((spamPortConfig->identifier >= SERIAL_PORT_USART1) && (spamPortConfig->identifier <= SERIAL_PORT_USART_MAX)){
        options |= SERIAL_CHECK_TX;
    } */
    /*
    debugSerialPort = openSerialPort(DPRINTF_SERIAL_PORT, FUNCTION_NONE, NULL, NULL, 115200, MODE_RXTX, 0);
    if (debugSerialPort) {
        setPrintfSerialPort(debugSerialPort);
    }
    dprintf(("smartAudioInit: OK\r\n")); */
    // no callback - buffer will be consumed in gpsUpdate()
    _counterRx=1040;
    _counterTx=1041;
    _counterTx2 = 1042;
    spamPort = openSerialPort(SERIAL_PORT_UART5, FUNCTION_RX_SERIAL, spamDataReceive, &_testData, SPAM_BAUDRATE, MODE_RXTX, 0);
    _counterTx2 = 1051;
    if (!spamPort) {
        return;
    }
    _counterRx=990;
}

bool changeDebugAuxValue(int ch) {
    return ch>=6 && ch<=8;
}
float getDebugAuxValue(int ch) {
    switch (ch)
    {
    case 6:
    return  _counterRx;
    case 7:
    return  _counterTx;
    case 8:
    return  _counterTx2;
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
    //_counterTx2 = 1000 + data; 
    //serialWriteBuf(spamPort, (uint8_t *)"Hallo\r\n", 7);
    
}