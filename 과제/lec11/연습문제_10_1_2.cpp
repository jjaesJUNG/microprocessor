#include "mbed.h"
InterruptIn button(BUTTON1);
int i = 10;
volatile bool run = true;
void toggle() {
    run = !run;
}
int main(){
    button.mode(PullUp);
    button.rise(&toggle);
    while(i > 0)
    {
        if(run){
            printf("%d\n", i);
            i--;
        }
        ThisThread::sleep_for(1000ms);
    }
    printf("BOOM!\n");
    return 0;
}