#include "mbed.h"
InterruptIn button(BUTTON1);
PwmOut buzzer(PB_0);
bool pushed = false;
void toggle() {
    pushed = !pushed;
}
int main(){
    button.rise(&toggle);
    while (1){
        if(pushed){
            buzzer.period_us(1000);
            buzzer.write(0.5f);
            ThisThread::sleep_for(1000ms);
        }
        else{
            buzzer.write(0);
        }
    }
}