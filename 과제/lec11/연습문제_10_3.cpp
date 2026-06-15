#include "mbed.h"

// 인터럽트 객체 선언
InterruptIn button(BUTTON1);
Ticker led1_ticker;           // led1의 깜빡임을 담당할 Ticker 추가

DigitalOut led1(LED1);
DigitalOut led2(PA_4);

// 버튼 클릭 시 호출되는 ISR (기존 유지)
void toggle() {
    led2 = !led2;
}

// Ticker에 의해 500ms마다 호출될 ISR
void toggle_led1() {
    led1 = !led1;
}

int main() {
    // 1. 버튼 인터럽트 설정 (기존 유지)
    button.rise(&toggle);

    // 2. led1 깜빡임을 위한 Ticker 설정 (500ms 주기)
    led1_ticker.attach(&toggle_led1, 500ms);

    while (1) {
        // 이제 main 루프는 대기 상태로만 두어도 
        // led1과 led2 모두 인터럽트(하드웨어) 방식으로 완벽하게 동작합니다.
        ThisThread::sleep_for(1s);
    }
}