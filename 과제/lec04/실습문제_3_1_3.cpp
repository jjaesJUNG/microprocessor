#include "mbed.h"
#include <chrono>

using namespace std::chrono;

// PortA의 4~7번 비트(0x000000F0) 사용
PortOut leds(PortA, 0x000000F0); 

// AVDD 연결이므로 PullDown 설정 (안 누를 때 0, 누를 때 1)
DigitalIn btn_right(PC_0, PullDown); 
DigitalIn btn_left(PC_1, PullDown);  

int main() {
    // 4번째 비트(0x10)를 켜고 시작
    uint32_t led_pattern = 0x10; 
    leds = led_pattern;
    leds = 0xF0;
    while (true) {
        // [중요] 누를 때 1이 들어오므로 == 1 조건 사용
        if (btn_right.read() == 1) {
            led_pattern <<= 1;
            if (led_pattern > 0x80) { // 7번 비트를 넘어가면
                led_pattern = 0x10;   // 4번 비트로 복귀
            }
            leds = led_pattern;
            ThisThread::sleep_for(200ms); 
        }
        
        else if (btn_left.read() == 1) {
            led_pattern >>= 1;
            if (led_pattern < 0x10) { // 4번 비트보다 작아지면
                led_pattern = 0x80;   // 7번 비트로 복귀
            }
            leds = led_pattern;
            ThisThread::sleep_for(200ms);
        }

        else {
            // 아무것도 안 누르면 현재 led_pattern을 유지하며 대기
            ThisThread::sleep_for(10ms);
        }
    }
}