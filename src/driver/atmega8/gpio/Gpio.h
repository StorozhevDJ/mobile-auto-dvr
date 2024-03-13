#ifndef __ATMEGA8_GPIO
#define __ATMEGA8_GPIO


//PIR sensor signal pin
#define PIR_DATA_PIN	PIND_Bit2
#define PIR_DATA_DDR	DDRD_Bit2
//DVR Control pins
#define DVR_REC_PORT	PORTB_Bit2
#define DVR_REC_LED_PIN	PINB_Bit4
#define DVR_PWR_PORT	PORTB_Bit3
#define DVR_PWR_LED_PIN	PINB_Bit5

#endif

class Gpio {
private:
  
public:
  Gpio();
  void powerButtonPress();
  void powerButtonUnpress();
  void recButtonPress();
  void recButtonUnpress();
  bool isBlueLed();
  bool isRedLed();
  bool isSensor();
};

