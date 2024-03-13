

class Uart {
private:
    template <typename T> void sendDigit(T n);
public:
    Uart(long baudrate);
    void send(char c);
    void send(const char __flash *str);
    void send(signed char n);
    void send(unsigned char n);
    void send(signed short n);
    void send(unsigned short n);
    void send(signed int n);
    void send(unsigned int n);
    void send(signed long n);
    void send(unsigned long n);

};