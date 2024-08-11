#include "spam.h"
#include "io/serial.h"

static serialPort_t *spamPort;
uint8_t _counter;

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
    _counter=42;
    spamPort = openSerialPort(SERIAL_PORT_UART3, FUNCTION_RX_SERIAL, spamDataReceive, NULL, SPAM_BAUDRATE, MODE_RXTX, 0);
    if (!spamPort) {
        return;
    }
    
}

static void spamDataReceive(uint16_t c, void *data)
{
    UNUSED(c);
    UNUSED(data);
    _counter++;
}

void spamUpdate(timeUs_t currentTimeUs) {
    UNUSED(currentTimeUs);
if (!spamPort) {
        return;
    }
    serialWrite(spamPort, _counter);
    //serialWriteBuf(spamPort, (uint8_t *)"Hallo\r\n", 7);
}