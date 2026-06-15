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
        else
        {
            leds = 0;
        }
        printf("Light level = %f\n", light);
        ThisThread::sleep_for(SAMPLING_DELAY);
    }
}