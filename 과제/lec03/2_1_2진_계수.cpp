#include "mbed.h"
#define BLINK_DELAY 500ms
DigitalOut led0(PA_4);
DigitalOut led1(PA_5);
DigitalOut led2(PA_6);
DigitalOut led3(PA_7);
int main()
{
    while (1) {
        DigitalOut* leds[4] = {&led0,&led1,&led2,&led3};
        *leds[0] = 0; *leds[1] = 0; *leds[2] = 0; *leds[3] = 0;
        ThisThread::sleep_for(BLINK_DELAY);
        for(int i = 1; i < 16; i++){
            int nums = i;
            int arr[4] = {0};
            for(int j = 0; j < 4; j++){
                arr[j] = nums % 2;
                nums /= 2;
            }
            *leds[0] = arr[0];*leds[1] = arr[1];*leds[2] = arr[2];*leds[3] = arr[3];
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}