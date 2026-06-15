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
        pos = mypot.read_u16() >> 12; // 5구간으로 분할
        printf("val= %d\n", pos);
        led_on = pos << 4; // led들의 비트 패턴
        leds = led_on; // 비트패턴에 따라 LED 켬
        ThisThread::sleep_for(POT_DELAY);
    }
}