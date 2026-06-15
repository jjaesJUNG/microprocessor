#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include <cstring> // strlen 함수 사용을 위해 추가

// 1. I2C 핀 및 디스플레이 해상도 설정
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C 및 OLED 객체 생성
I2C i2c(I2C_SDA, I2C_SCL);
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, SCREEN_HEIGHT, SCREEN_WIDTH);

// DS3231 RTC I2C 8비트 주소 (0x68 << 1)
const int DS3231_ADDR = 0xD0;

// 2. BCD(이진화 십진법) 코드를 10진수로 변환하는 함수
int bcdToDec(char bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// 🛠️ 3. 인수 부족 에러가 나던 write 함수 호출 부분을 수정했습니다.
void oled_print_str(Adafruit_SSD1306_I2c &display, const char* str) {
    if (str == NULL) return;
    
    // 문자열 전체의 길이를 구합니다.
    size_t len = strlen(str); 
    
    // 라이브러리의 요구 조건에 맞춰 (데이터 주소, 길이) 형태로 인수를 넘겨줍니다.
    display.write((const uint8_t*)str, len);
}

int main() {
    oled.begin();
    oled.clearDisplay();
    
    char cmd[1];
    char data[7];
    char temp_data[2];
    char buf[32]; 
    
    while(1) {
        // --- DS3231 RTC에서 시간 데이터 읽기 ---
        cmd[0] = 0x00; 
        if(i2c.write(DS3231_ADDR, cmd, 1, true) != 0) {
            // I2C 쓰기 실패 시 에러 표시 (선이 빠졌거나 주소가 틀림)
            oled.clearDisplay();
            oled.setTextCursor(0, 0);
            oled_print_str(oled, "RTC Write Error");
            oled.display();
            thread_sleep_for(1000);
            continue;
        }
        i2c.read(DS3231_ADDR, data, 7); 
        
        // --- DS3231 RTC에서 온도 데이터 읽기 ---
        cmd[0] = 0x11; 
        i2c.write(DS3231_ADDR, cmd, 1, true);
        i2c.read(DS3231_ADDR, temp_data, 2); 
        
        // --- 데이터 변환 ---
        int second = bcdToDec(data[0] & 0x7F);
        int minute = bcdToDec(data[1]);
        int hour   = bcdToDec(data[2] & 0x3F); 
        int day    = bcdToDec(data[4]);
        int month  = bcdToDec(data[5] & 0x1F);
        int year   = bcdToDec(data[6]);
        
        float temperature = temp_data[0] + ((temp_data[1] >> 6) * 0.25f);
        
        // 소수점 포맷 우회를 위한 정수형 쪼개기 🌟
        int temp_high = (int)temperature;
        int temp_low  = (int)((temperature - temp_high) * 100);
        
        // --- OLED 화면 출력 처리 ---
        oled.clearDisplay();
        
        // 1. 날짜 출력
        oled.setTextSize(1);
        oled.setTextCursor(0, 0);
        snprintf(buf, sizeof(buf), "20%02d/%02d/%02d", year, month, day);
        oled_print_str(oled, buf); 
        
        // 2. 시간 출력
        oled.setTextSize(2);
        oled.setTextCursor(10, 22);
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hour, minute, second);
        oled_print_str(oled, buf);
        
        // 3. 온도 출력 (%f 대신 %d 사용으로 포맷 깨짐 방지) 🌟
        oled.setTextSize(1);
        oled.setTextCursor(0, 54);
        snprintf(buf, sizeof(buf), "Temp: %d.%02d C", temp_high, temp_low);
        oled_print_str(oled, buf);
        
        oled.display();
        thread_sleep_for(1000);
    }
}