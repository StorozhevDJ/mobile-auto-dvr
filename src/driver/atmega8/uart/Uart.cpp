

#include "../Common.h"

#include "Uart.h"

#include "ioavr.h"


Uart::Uart(long baudrate) {
    // rounding toward nearest integer, instead of downwards
    // divide by 8 (instead of 16) in 2x mode
    UBRRL = ((MCU_CLOCK + (baudrate*4))/(baudrate*8)-1);// set baud rate
    UCSRA = (1<<U2X);                           // enable 2x mode
    UCSRB = (1<<TXEN);                          // enable transmitter
    UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format
    DDRD_Bit1 = 1;
}



void Uart::send(char c) {
    // Wait for empty transmit buffer
    while(!(UCSRA&(1<<UDRE))){};
    UDR = c;
    // Wait Transmit Complete
    while(!(UCSRA&(1<<TXC))){};
}

void Uart::send(const char __flash *str) {
    for (; *str; str++) {
        send(*str);
    }
}

void Uart::send(signed char n) {
    if(n < 0) {
        send('-');
    }
    sendDigit<char>(n);
}

void Uart::send(unsigned char n) {
    sendDigit<char>(n);
}

void Uart::send(signed short n) {
    if(n < 0) {
        send('-');
    }
    sendDigit<short>(n);
}

void Uart::send(unsigned short n) {
    sendDigit<short>(n);
}

void Uart::send(signed int n) {
    if(n < 0) {
        send('-');
    }
    sendDigit<int>(n);
}

void Uart::send(unsigned int n) {
    sendDigit<int>(n);
}

void Uart::send(signed long n) {
    if(n < 0) {
        send('-');
    }
    sendDigit<long>(n);
}

void Uart::send(unsigned long n) {
    sendDigit<long>(n);
}

template <typename T> void Uart::sendDigit(T n) {
    char buf[10];
    char ptr=0;
    while(n) {
        buf[ptr++] = n%10 | 0x30;
        n/=10;
    }
    while(ptr--) {
        send(buf[ptr]);
    }
    
}