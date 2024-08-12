#include <stdio.h>
#include "spam.h"
#include "io/serial.h"

static serialPort_t *spamPort;
uint16_t _counterRx;
uint16_t _counterTx;
uint16_t _counterTx2;

static void spamDataReceive(uint16_t c, void *data)
{
    UNUSED(c);
    UNUSED(data);
    _counterRx++;
    if(_counterRx > 2000) {
        _counterRx = 1000;
    }
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
    _counterRx=_counterTx=_counterTx2 = 1042;
    spamPort = openSerialPort(SERIAL_PORT_USART3, FUNCTION_RX_SERIAL, spamDataReceive, NULL, SPAM_BAUDRATE, MODE_RXTX, 0);
    if (!spamPort) {
        return;
    }
    
}

void changeAuxValue(float [] rcData) {
    int length = sizeof(rcData) / sizeof(rcData[0]);
    if(length >=8) {
        rcData[5] = 1333;
        rcData[6] = _counterRx;
        rcData[7] = _counterTx;
        rcData[8] = _counterTx2;
    }
}

void spamUpdate(timeUs_t currentTimeUs) {
    UNUSED(currentTimeUs);
    _counterTx++;
    if(_counterTx > 2000) {
        _counterTx = 1000;
    }
if (!spamPort) {
        return;
    }
    _counterTx2++;
if(_counterTx2 > 2000) {
        _counterTx2 = 1000;
    }
    serialWrite(spamPort, 5);
    serialWriteBuf(spamPort, (uint8_t *)"Hallo\r\n", 7);
}