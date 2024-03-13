
class DvrControl {
private:
    Gpio gpio;
    CommonDriver commonDriver;
    void powerOn();
    void powerOff();
    void recordStart();
    void recordFinish();
public:
    DvrControl(Gpio &gpio, CommonDriver &commonDriver);
    void begin();
};
