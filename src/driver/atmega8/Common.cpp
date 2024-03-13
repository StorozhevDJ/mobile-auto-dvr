
#include <inavr.h>

#include "../../service/Debug.h"

#include "Common.h"


#ifdef DEBUG
const char __flash PIR_ON[] = "PIR On, update timeout to ";
const char __flash SLEEP[] = "Go to sleep...";
const char __flash TIMEOUT[] = "Timeout ";
#endif


unsigned int timer_tick;

/**
* If the PIR sensor is deactivated, the timer decreases.
*/
#pragma vector=TIMER1_COMPA_vect
__interrupt void Timer (void) {
    LOG(TIMEOUT);
    if (!PIR_ACTIVE) {
        if (timer_tick) {
            timer_tick--;
            LOG(TIMEOUT, timer_tick);
            }
    }
}


/**
* If MCU in power down mode, then INT0 interrupt activate MCU to Run mode and 
* timer counter set to new value. 
* Then if interrupt mode change from Low level to Rising edge (for new PIR activated) 
* then the counter value is update.
*/
#pragma vector=INT0_vect
__interrupt void Int0 (void) {
    // waking up...
    // disable external interrupt, for long low pulse
    MCUCR|=(1<<ISC01);		//The falling edge of INT0 generates an interrupt request
    MCUCR &=~(1<<ISC00);        //for time increment if PIR activate
    timer_tick = REC_TIMEOUT;
    LOG(PIR_ON, timer_tick);
}


void CommonDriver::init() {
    ACSR |= (1<<ACD);		//Analog Comparator Disable, for lower power

    GICR |= (1<<INT0);		//Set interrupt to INT0 pin
    MCUCR &= ~((1 << ISC01) | (1 << ISC00));// level interrupt INT0 (only low level for wake up)
    DDRD_Bit2 = 0;	        // INT0: input...
    PORTD_Bit2 = 1;	        // ...with pullup.
    PORTC_Bit5 = 0;

    TIMSK |= (1<<OCIE1A);	//Set Tim1 Output Compare A Match Interrupt Enable
    TCCR1B = (1<<CS10)|(1<<CS12); //ClkI/O/1024
    TCCR1B|= (1<<WGM12);	//CTC mode with TOP = OCR1A
    // MCU_CLOCK is 1 000 000
    // MCU_CLOCK/1024 = 976
    OCR1A = 976;		//(MCU_CLOCK/1024)/976(OCR1A) ~ 1 seconds
    
    __enable_interrupt();
}


void CommonDriver::systemSleep() {
    while(PIR_ACTIVE){};                //Waiting if PIR is activated
    GICR |= (1<<INT0);			//Set interrupt to INT0 (for wake up)
    MCUCR &= ~((1 << ISC01) | (1 << ISC00));//Set interrupt mode to Low level
    //Set PowerDown mode and sleep mode enable
    MCUCR &= ~((1<<SM2)|(1<<SM0));
    MCUCR |= (1<<SM1)|(1<<SE);		
    LOG(SLEEP);
    __sleep();				//Go to sleep mode
}


bool CommonDriver::isRecordTime() {
    return timer_tick > 0;
}