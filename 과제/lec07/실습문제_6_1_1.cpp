#include "mbed.h"
#include <ctime>

// I2C 핀 및 DS3231 주소 설정
I2C i2c(I2C_SDA, I2C_SCL); 
const int DS3231_ADDR = 0xD0; 

// BCD -> 10진수 변환 함수
int bcdToDec(char val) {
    return ((val / 16 * 10) + (val % 16));
}

int main() {
    printf("RTC I2C 시간 읽기 시작...\n");

    while (1) {
        char reg = 0x00; 
        char data[7];    

        // 1. RTC 칩에서 7바이트의 시간 데이터 읽기
        if (i2c.write(DS3231_ADDR, &reg, 1) == 0 && i2c.read(DS3231_ADDR, data, 7) == 0) {
            
            // 2. 읽어온 BCD 데이터를 10진수로 변환
            int sec   = bcdToDec(data[0] & 0x7F);
            int min   = bcdToDec(data[1]);
            int hour  = bcdToDec(data[2] & 0x3F); // 24시간 모드 가정
            int day   = bcdToDec(data[4]);
            int month = bcdToDec(data[5] & 0x1F);
            int year  = bcdToDec(data[6]) + 2000; 

            // 3. C 표준 tm 구조체에 데이터 매핑하기
            struct tm timeinfo;
            timeinfo.tm_sec  = sec;
            timeinfo.tm_min  = min;
            timeinfo.tm_hour = hour;
            timeinfo.tm_mday = day;
            timeinfo.tm_mon  = month - 1;      // tm 구조체는 0~11월 기준
            timeinfo.tm_year = year - 1900;    // tm 구조체는 1900년부터 지난 년도 기준
            
            // 4. 입력된 년/월/일을 바탕으로 요일(tm_wday) 자동 계산 함수 호출
            mktime(&timeinfo);

            // 5. 원하는 포맷으로 문자열 변환
            char buffer[64];
            strftime(buffer, sizeof(buffer), "현재시간: %I:%M %p %a, %b %d, %Y", &timeinfo);

            // 6. 출력 출력!
            printf("%s\n", buffer);

        } else {
            printf("I2C 통신 에러 - RTC 연결을 확인하세요.\n");
        }

        ThisThread::sleep_for(1s);
    }
}