#include "mbed.h"
#define SCAN_INTERVAL 10ms
I2C i2c(I2C_SDA, I2C_SCL);
int main(){
    while(1) {
        printf("Scanning I2C device addresses...\n");
        for (int addr=0; addr < 128; addr++){
            if (i2c.write((addr<<1), 0, 0) == 0){
                printf(" device found at 0x%02X \n", addr);
            }
            ThisThread::sleep_for(SCAN_INTERVAL);
        }
        printf("Scanning completed.\n\n");
        ThisThread::sleep_for(2000ms);
    }
}