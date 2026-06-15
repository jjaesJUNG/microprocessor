#include "mbed.h"
#define LED_MASK 0x000000f0
// LED0=PA_4, LED1=PA_5, LED2=PA_6, LED3=PA_7
#define BLINK_DELAY 500ms
#define LOW 0
#define HIGH 1
PortOut leds(PortA, LED_MASK);
DigitalIn button(PC_0, PullDown);
int main() {
    int before = LOW;
    int now;
    int count = 0;
    leds = 0; //leds.write(0x00000000)
    while (1) {
        now = button;
        if((before == LOW) && (now == HIGH)){
            count = count + 1;
            leds = count << 4; // 비트들을 LED위치로 이동
        }
        before = now;
        ThisThread::sleep_for(20ms); //debounce
    }
}