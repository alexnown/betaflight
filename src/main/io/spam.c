#include "spam.h"
#include "io/serial.h"

static serialPort_t *spamPort;

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
    spamPort = openSerialPort(SERIAL_PORT_UART4, FUNCTION_NONE, NULL, NULL, SPAM_BAUDRATE, MODE_RXTX, 0);
    if (!spamPort) {
        return;
    }
    
}

void spamUpdate(timeUs_t currentTimeUs) {
if (!spamPort) {
        return;
    }
    serialWriteBuf(spamPort, (uint8_t *)"Hallo\r\n", 7);
    if(currentTimeUs == 0) {
        return;
    }
}