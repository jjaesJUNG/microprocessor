#include "mbed.h"
Timer timer; 
PwmOut buzzer(PB_0);
DigitalIn echo(PB_6);
DigitalOut trigger(PC_7);
int main(void){
    float distance = 0.0;
    buzzer.write(0.0f);

    while(1){
        trigger = 1; 
        wait_us(10); 
        trigger = 0; 

        // 2. 에코 펄스가 High(1)가 될 때까지 대기 (무한루프 방지용 카운터 추가)
        int timeout_counter = 0;
        while(echo == 0) {
            wait_us(1);
            if(++timeout_counter > 20000) break; // 너무 오래 걸리면 탈출
        }; 
        
        // 3. 타이머 시작 및 High 유지 시간 측정
        timer.reset();
        timer.start(); 
        
        timeout_counter = 0;
        while(echo == 1) {
            wait_us(1);
            if(++timeout_counter > 20000) break; // 너무 오래 걸리면 탈출
        }; 
        
        timer.stop();
        auto round_trip_time = timer.elapsed_time().count();
        distance = round_trip_time*0.0173; // 거리계산
        if(distance < 5){
            buzzer.period_us(1000); // 1ms period, 1000Hz
            buzzer.write(0.5f); // 50% duty cycle
            ThisThread::sleep_for(1000ms);

            buzzer.period_us(2000); // 2ms period, 500Hz
            buzzer.write(0.5f); // 50% duty cycle
            ThisThread::sleep_for(1000ms);

            buzzer.write(0.0f);
        }
        else{
            buzzer.write(0.0f);
        }
        printf("distance: %f\n", distance);
    }
}