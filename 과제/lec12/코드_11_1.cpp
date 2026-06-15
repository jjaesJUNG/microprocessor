#include "mbed.h"
DigitalOut led1(LED1);
DigitalOut led2(PA_4);
InterruptIn button(BUTTON1);
Thread thread;
void led2_blink();
void toggle();
int main() {
    button.rise(toggle);
    thread.start(led2_blink);
    while (1){
    }
}
void led2_blink() {
    while (1) {
        led2 = !led2;
        ThisThread::sleep_for(200ms);
    }
}
void toggle(){
    led1 = !led1;
}