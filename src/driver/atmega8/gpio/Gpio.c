
#include "Gpio.h"


Gpio::Gpio() {
    // Set pull up on all pins
    DDRB = 0x00;
    PORTB = 0xFF;
    DDRC = 0x00;
    PORTC = 0xDF;
    DDRD = 0x00;
    PORTD = 0xFF;
    //PIR sensor signal pin
    PIR_DATA_PIN = 1;   //Pull up
    PIR_DATA_DDR = 0;   //Input
    //DVR Control pins
    DVR_PWR_PORT = 0;   //Power button pin is off
    DDRB_Bit3 = 1;      //Dir is out
    DVR_REC_PORT = 0;   //Rec button pin is off
    DDRB_Bit2 = 0;      //Dir is out
    PORTB_Bit4 = 0;     //Record led pin is input without pull up
    PORTB_Bit5 = 0;     //Power led pin is input without pull up
}


void Gpio::powerButtonPress() {
    DVR_PWR_PORT = 1;
}

void Gpio::powerButtonUnpress() {
    DVR_PWR_PORT = 0;
}

void Gpio::recButtonPress() {
    DDRB_Bit2 = 1;
}

void Gpio::recButtonUnpress() {
    DDRB_Bit2 = 0;
}

bool Gpio::isBlueLed() {
    return DVR_PWR_LED_PIN == 1;
}

bool Gpio::isRedLed() {
    return DVR_REC_LED_PIN == 1;
}

bool Gpio::isSensor() {
return PIR_DATA_PIN;
}