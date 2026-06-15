#include "mbed.h"
#define BLINK_DELAY 500ms
DigitalOut led0(PA_4);
DigitalOut led1(PA_5);
DigitalOut led2(PA_6);
DigitalOut led3(PA_7);
int main()
{
    while (1) {
        led0 = 0;led1 = 1; led2= 0; led3 = 1;
        ThisThread::sleep_for(BLINK_DELAY);
        led0 = 1;led1 = 0; led2= 1; led3 = 0;
        ThisThread::sleep_for(BLINK_DELAY);
    }
}