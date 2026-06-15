#include "mbed.h"
#define LED_MASK 0x000000f0
DigitalOut trigger(PC_7);
DigitalIn echo(PB_6);
Timer timer;
PortOut leds(PortA, LED_MASK);
int main()
{
    float distance = 0.0;
    while(1) {
        trigger = 1; // HC-SR04에 트리거 펄스 전송개시
        timer.reset(); // timer 초기화
        wait_us(10); // 10us 대기 (트리거 지속 기긴)
        trigger = 0; // 트리거 펄스 종료
        while(echo==0) {}; // 에코펄스가 High가 될 때까지 대기
        timer.start(); // 타이머 시작
        while(echo==1) {}; // 에코펄스가 Low가 될 때까지 대기
        timer.stop(); // 타이머 종료
        // 시간측정
        auto round_trip_time = timer.elapsed_time().count();
        distance = round_trip_time*0.0173; // 거리계산
        if(distance <= 5){
            leds = 0xF0;
            ThisThread::sleep_for(150ms);
            leds = 0;
        }
        printf("Distance = %f cm \n\r", distance);
        ThisThread::sleep_for(1500ms);
    }
}