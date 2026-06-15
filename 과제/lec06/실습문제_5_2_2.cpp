#include "mbed.h"
#define SAMPLING_DELAY 1000ms
#define LED_MASK 0x000000f0
PortOut leds(PortA, LED_MASK);
AnalogIn CdS(PA_0, 3.3);
int main() {
    float light = 0.0;
    while(1){
        light = CdS;
        if(light < 0.1)
        {
            leds = 0xF0;
        }
        else if(light >= 0.1 && light < 0.15)
        {
            leds = 0x70;
        }
        else if(light >= 0.15 && light < 0.20)
        {
            leds = 0x30;
        }
        else if(light >= 0.2 && light < 0.25)
        {
            leds = 0x10;
        }
        else 
        {
            leds = 0;
        }
        printf("Light level = %f\n", light);
        ThisThread::sleep_for(SAMPLING_DELAY);
    }
}