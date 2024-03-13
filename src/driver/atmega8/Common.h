#ifndef __ATMEGA8_COMMON

#define MCU_CLOCK	1000000L
#define REC_TIMEOUT     30U

#define PIR_ACTIVE      (!PIND_Bit2)


#endif

class CommonDriver {
private:
  
public:
  void init();
  void systemSleep();
  bool isRecordTime();
};