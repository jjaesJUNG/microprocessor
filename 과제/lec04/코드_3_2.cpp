#include "mbed.h"
DigitalIn var1(PC_0, PullDown);
DigitalIn var2(PC_1, PullDown);
DigitalOut bool_not(PA_4);
DigitalOut bool_and(PA_5);
DigitalOut bool_or(PA_6);
DigitalOut bool_xor(PA_7);
int main() {
    unsigned int A, B;
    while (1) {
        A = var1;
        B = var2;
        bool_not = !A;
        bool_and = A && B;
        bool_or = A || B;
        bool_xor = A ^ B;
        ThisThread::sleep_for(100ms);
    }
}