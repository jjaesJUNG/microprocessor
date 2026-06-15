#include "mbed.h"

// I2C 핀 설정 (보드에 맞게 핀 이름을 변경하세요)
I2C i2c(I2C_SDA, I2C_SCL); 

// DS3231의 8비트 Write/Read 주소
const int DS3231_ADDR_WRITE = 0xD0;
const int DS3231_ADDR_READ  = 0xD1;

// 온도 레지스터 시작 주소
const char TEMP_REG_ADDR = 0x11;

int main() {
    // I2C 주파수 설정 (100kHz 표준 모드)
    i2c.frequency(100000);
    
    printf("DS3231 Temperature Sensor Test\r\n");
    printf("--------------------------------\r\n");

    while(1) {
        char data[2] = {0, 0};

        // 1. 읽을 레지스터 주소(0x11)를 DS3231에 먼저 씁니다.
        // 주소 전송 후 Stop 비트를 생성하지 않기 위해 3번째 인자에 true(Repeated Start)를 줍니다.
        if (i2c.write(DS3231_ADDR_WRITE, &TEMP_REG_ADDR, 1, true) != 0) {
            printf("I2C Write Error!\r\n");
            thread_sleep_for(1000);
            continue;
        }

        // 2. MSB(0x11)와 LSB(0x12) 총 2바이트를 읽어옵니다.
        if (i2c.read(DS3231_ADDR_READ, data, 2) != 0) {
            printf("I2C Read Error!\r\n");
            thread_sleep_for(1000);
            continue;
        }

        // 3. 온도 데이터 변환
        // data[0] = 정수부 (음수 표현을 위해 signed char로 캐스팅)
        int8_t temp_msb = (int8_t)data[0]; 
        // data[1] = 소수부 (상위 2비트만 사용하며, 0.25를 곱해줍니다)
        float temp_lsb = (data[1] >> 6) * 0.25f; 

        float temperature = temp_msb + temp_lsb;

        // 4. 결과 출력
        printf("Current Temperature: %.2f C\r\n", temperature);

        // 2초마다 측정
        thread_sleep_for(2000);
    }
}