#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include <stdio.h>

I2C i2c_bus(I2C_SDA, I2C_SCL);
Adafruit_SSD1306_I2c oled( i2c_bus,NC,0x78,64,128);

#define OLED_I2C_ADDRESS  0x3C 

int main() {
    i2c_bus.frequency(400000);
    oled.clearDisplay();

    // 1. sprintf로 문자열 포맷팅
    char buffer[32]; 
    sprintf(buffer, "Address: 0x%02X", OLED_I2C_ADDRESS);

    // 2. 디스플레이 기본 설정
    oled.setTextSize(1);
    oled.setTextCursor(0, 20); 
    
    // 3. [확인 완료] writeChar를 이용해 한 글자씩 출력
    int i = 0;
    while (buffer[i] != '\0') {
        oled.writeChar(buffer[i]); // 알려주신 정확한 함수명 적용!
        i++;
    }
    
    // 화면에 반영
    oled.display();

    while(1) {
        thread_sleep_for(1000); 
    }
}