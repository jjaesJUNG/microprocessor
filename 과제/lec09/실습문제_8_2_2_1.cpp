#include "mbed.h"

// PB_0 핀을 부저 출력으로 설정
PwmOut buzzer(PB_0);

int main(void) {
    // 부저의 출력 비율을 50%로 고정 (소리가 가장 선명하게 나는 비율)
    buzzer.write(0.5f);

    while(1) {
        // 1. 음이 점점 높아지는 구간 (400Hz -> 1200Hz)
        // 주기를 us(마이크로초) 단위로 줄여나가면 주파수(Hz)가 올라갑니다.
        // 400Hz(2500us)에서 시작해 1200Hz(833us)까지 가도록 설정
        for(int period = 2500; period >= 833; period -= 10) {
            buzzer.period_us(period);
            wait_us(4000); // 이 값이 작을수록 사이렌이 더 빠르게 윙- 올라갑니다 (4ms)
        }

        // 2. 음이 점점 낮아지는 구간 (1200Hz -> 400Hz)
        // 주기를 다시 늘려나갑니다.
        for(int period = 833; period <= 2500; period += 10) {
            buzzer.period_us(period);
            wait_us(4000); // 이 값이 작을수록 사이렌이 더 빠르게 윙- 내려옵니다
        }
        
        // 3. 한 사이클이 끝나고 아주 잠깐 쉬어주기 (선택 사항)
        ThisThread::sleep_for(50ms);
    }
}