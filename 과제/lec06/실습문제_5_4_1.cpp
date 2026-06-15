#include "mbed.h"
DigitalOut green(PA_4);
DigitalOut red(PA_5);
//temperature sensor -> TMP36GT
DigitalIn alarm(D7);
int main() {
    green = 1;
    red = 0;
    while(1) {
        if(alarm){
            green = 0;
            for(int i = 0; i < 5; i++)
            {
                red = !red;
                ThisThread::sleep_for(500ms);
            }
            red = 0;
        }
        green = 1;
    }
}