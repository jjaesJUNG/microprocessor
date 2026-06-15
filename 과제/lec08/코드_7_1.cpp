#include "Adafruit_SSD1306.h"
#include "mbed.h"
I2C i2c(I2C_SDA, I2C_SCL);
Adafruit_SSD1306_I2c oled(i2c,NC,0x78,64,128);
void oled_write_string(char *str);
int main(){
    i2c.frequency(400000);
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextCursor(10,10);
    oled_write_string("Hello, World!");
    oled.setTextSize(2);
    oled.setTextCursor(10,25);
    oled_write_string("SSD1306");
    oled.display();
    ThisThread::sleep_for(5000ms);
    oled.clearDisplay();
    oled.display();
    ThisThread::sleep_for(2000ms);
    oled.setTextSize(2);
    oled.setTextCursor(10,25);
    oled_write_string("10:25 AM");
    oled.display();
    while(1){}
}
void oled_write_string(char *str){
    for(int i=0; str[i]; i++){
        oled.writeChar(str[i]);
    }
}