#include "mbed.h"
#include <math.h>
#define LED_MASK 0x000000f0
// LED0=PA_4, LED1=PA_5, LED2=PA_6, LED3=PA_7
#define POT_DELAY 200ms
AnalogIn mypot(PA_0, 3.3);
PortOut leds(PortA, LED_MASK);
int main() {
    int led_on, pos=0;
    while(1){
        printf("read() = %f, read_voltage() = %f\n", mypot.read() * 3.3, mypot.read_voltage());
        ThisThread::sleep_for(POT_DELAY);
    }
}