#include "mbed.h"
#define LED_MASK 0x000000f0
// LED0=PA_4, LED1=PA_5, LED2=PA_6, LED3=PA_7
#define BLINK_DELAY 500ms
PortOut leds(PortA, LED_MASK);
int main() {
    while (1) {
        leds = 0;
        ThisThread::sleep_for(BLINK_DELAY);
        for(int i = 1; i < 16; i++)
        {
            leds = i * 16;
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}