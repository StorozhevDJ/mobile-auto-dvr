
#include <inavr.h>

#include "../driver/atmega8/gpio/Gpio.h"
#include "../driver/atmega8/Common.h"

#include "Debug.h"

#include "DvrControl.h"

#ifdef DEBUG
const char __flash POWER_ON[] = "Power On";
const char __flash POWER_OFF[] = "Power Off";
const char __flash REC_START[] = "Rec Start";
const char __flash REC_FINISH[] = "Rec Finish";
const char __flash POWER_BUTTON_PRESS[] = "Power Button press";
const char __flash POWER_BUTTON_UNPRESS[] = "Power Button unpress";
const char __flash REC_BUTTON_PRESS[] = "Rec Button press";
const char __flash REC_BUTTON_UNPRESS[] = "Rec Button unpress";
#endif


DvrControl::DvrControl(Gpio &gpio, CommonDriver &commonDriver) {
  this->gpio = gpio;
  this->commonDriver = commonDriver;
}

void DvrControl::powerOn() {
    LOG(POWER_ON);
    if(!gpio.isBlueLed()) {
        LOG(POWER_BUTTON_PRESS);
        gpio.powerButtonPress();
        __delay_cycles(MCU_CLOCK*2);
        LOG(POWER_BUTTON_UNPRESS);
        gpio.powerButtonUnpress();
        __delay_cycles(MCU_CLOCK*2);
    }
}

void DvrControl::powerOff() {
    LOG(POWER_OFF);
    LOG(POWER_BUTTON_PRESS);
    gpio.powerButtonPress();
    __delay_cycles(MCU_CLOCK/3);
    LOG(POWER_BUTTON_UNPRESS);
    gpio.powerButtonUnpress();
    __delay_cycles(MCU_CLOCK*2);
}

void DvrControl::recordStart() {
    LOG(REC_START);
    if(gpio.isBlueLed() && !gpio.isRedLed()) {
        LOG(REC_BUTTON_PRESS);
        gpio.recButtonPress();
        __delay_cycles(MCU_CLOCK/3);
        LOG(REC_BUTTON_UNPRESS);
        gpio.recButtonUnpress();
    }
}

void DvrControl::recordFinish() {
    LOG(REC_FINISH);
    if(gpio.isBlueLed()) {
        LOG(REC_BUTTON_PRESS);
        gpio.recButtonPress();
        __delay_cycles(MCU_CLOCK/3);
        LOG(REC_BUTTON_UNPRESS);
        gpio.recButtonUnpress();
        __delay_cycles(MCU_CLOCK/3);
    }
}
    
void DvrControl::begin() {
    // The DVR switch Power on
    powerOn();
    // Start the DVR record
    recordStart();
    // Continue record while timeout is not 0, 
    // if the PIR sensor activate then the timeout will be updated
    while(commonDriver.isRecordTime()) {
        // if blue LED is off then the DVR is off because battery low level, card is full etc
        // Power off and finish program cycle, without of timeout ending
        if(!gpio.isBlueLed()) {
            powerOff();
            break;
        }
    }
    //recordFinish();
    powerOff();
}