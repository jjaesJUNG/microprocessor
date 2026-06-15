#include "mbed.h"
PwmOut myled(LED1);
AnalogIn mypot(PA_0);
int main(){
    while(1) {
        myled = mypot;
        ThisThread::sleep_for(200ms);
    }
}