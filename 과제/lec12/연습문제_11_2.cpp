#include "mbed.h"
DigitalOut trigger(PC_7);
DigitalIn echo(PB_6);
PwmOut buzzer(PB_0);
AnalogIn CdS(PA_0, 3.3);
DigitalOut led1(PA_4);
Thread thread;
Thread thread2;
Timer timer;
void check_distance();
void check_light();
int main(void)
{
    thread.start(check_distance);
    thread2.start(check_light);

}
void check_distance()
{
    float distance = 0;
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
        if(distance <= 10)
        {
            for(int i = 1; i <= 5; i++) {
                buzzer.period_us(1000); // 1ms period, 1000Hz
                buzzer.write(0.5f); // 50% duty cycle
                ThisThread::sleep_for(500ms);
                buzzer.period_us(2000); // 2ms period, 500Hz
                buzzer.write(0.5f); // 50% duty cycle
                ThisThread::sleep_for(500ms);
            }
        }
        ThisThread::sleep_for(1500ms);
    }
}
void check_light()
{
    float light = 0.0;
    while(1){
        light = CdS;
        if(light > 5)
        {
            led1 = 0;
        }
        else
        {
            led1 = 1;
        }
        ThisThread::sleep_for(1000ms);
    }
}