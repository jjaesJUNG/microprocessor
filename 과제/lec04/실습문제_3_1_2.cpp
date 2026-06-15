#include "mbed.h"
#define LED_MASK 0x000000f0
// LED0=PA_4, LED1=PA_5, LED2=PA_6, LED3=PA_7
#define BLINK_DELAY 500ms
#define LOW 0
#define HIGH 1
PortOut leds(PortA, LED_MASK);
DigitalIn button0(PC_0, PullDown);
DigitalIn button1(PC_1, PullDown);
int main() {
    int before0 = LOW, before1 = LOW;
    int now0, now1;
    int count = 0;
    leds = 0; //leds.write(0x00000000)
    while (1) {
        now0 = button0;
        now1 = button1;
        if((before0 == LOW) && (now0 == HIGH)){
            count = count + 1;
            leds = count << 4; // 비트들을 LED위치로 이동
        }
        if((before1 == LOW) && (now1 == HIGH)){
            count = count - 1;
            leds = count << 4;
        }
        before0 = now0;
        before1 = now1;
        ThisThread::sleep_for(20ms); //debounce
    }
}