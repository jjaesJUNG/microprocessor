#include "mbed.h"
PwmOut led(PA_0);
AnalogIn CdS(PA_1, 3.3);
int main()
{
    led.period(0.01f); // 2 second period
    while(1){
        float light = CdS;
        led.write(1.0f - light);
        ThisThread::sleep_for(10ms);
    }
}
