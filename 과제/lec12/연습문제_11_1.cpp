#include "mbed.h"
DigitalOut led1(LED1);
DigitalOut led2(PA_4);
DigitalOut led3(PA_7);
InterruptIn button(BUTTON1);
Thread thread, thread2;
void led2_blink();
void toggle();
void led3_blink();
int main() {
    button.rise(toggle);
    thread.start(led2_blink);
    thread2.start(led3_blink);
    ThisThread::sleep_for(10s);
    thread2.terminate();
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
void led3_blink(){
    while (1) {
        led3 = !led3;
        ThisThread::sleep_for(500ms);
    }
}
