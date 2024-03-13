
#include "../driver/atmega8/uart/Uart.h"

static Uart uart = Uart(9600);

void debugLog(const char __flash *str) {
    uart.send(str);
    uart.send('\r');
}


void debugLog(const char __flash *str, unsigned int n) {
    uart.send(str);
    uart.send(n);
    uart.send('\r');
}