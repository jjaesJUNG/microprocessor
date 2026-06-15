#include "mbed.h"
#define SAMPLING_DELAY 1000ms
#define LED_MASK 0x000000f0
PortOut leds(PortA, LED_MASK);
//temperature sensor -> TMP36GT
AnalogIn TMP36(PA_0);
int main() {
    float temp = 0.0;
    while(1){
        temp=(TMP36.read()*3.3 - 0.5)*100;
        printf("Temperature= %f\n", temp);
        if(temp > 20){
            leds = 0xF0;
            ThisThread::sleep_for(150ms);
            leds = 0;
        }
        else{
            leds = 0;
        }
        ThisThread::sleep_for(SAMPLING_DELAY);
    }
}