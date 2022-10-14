#include "smotor.h"

#define SMOTOR1_PIN   PWM4_MODULE2_CHA_C30       //���峵ģѰ���������
#define SMOTOR2_PIN   PWM1_MODULE0_CHA_D12       //������̨���1����
#define SMOTOR3_PIN   PWM1_MODULE0_CHB_D13       //������̨���2����
#define ELECTROMAG_PIN B25


#define SMOTOR1_CENTER  (1.5*50000/20)
#define SMOTOR2_CENTER  (1.5*50000/20)
#define SMOTOR3_CENTER  (1.5*50000/20)


void smotor_init(void)
{
    pwm_init(SMOTOR1_PIN, 50, SMOTOR1_CENTER+100);
    gpio_init(ELECTROMAG_PIN,GPO,0,GPIO_PIN_CONFIG);
    //smotor1_control(2800);
/*    pwm_init(SMOTOR2_PIN, 50, SMOTOR2_CENTER);
    pwm_init(SMOTOR3_PIN, 50, SMOTOR3_CENTER);*/
}

void smotor1_control(int16 duty)
{
    pwm_duty(SMOTOR1_PIN, (int16)SMOTOR1_CENTER + duty+100);
}

void smotor2_control(int16 duty)
{
    pwm_duty(SMOTOR2_PIN, (int16)SMOTOR1_CENTER + duty);
}

void smotor3_control(int16 duty)
{
    pwm_duty(SMOTOR3_PIN, (int16)SMOTOR1_CENTER + duty);
}

void grab_picture(){
    //������Ƶ��������
    gpio_set(ELECTROMAG_PIN,1);
    //������ԣ���Χ��Լ��-300~2800 �ȽϺ��ʣ�������ɵĶ�����������������е㲻�ȡ�
    smotor1_control(-800);
    rt_thread_delay(1000);
    smotor1_control(1600);
}

void place_picture(){
    smotor1_control(0);
    //������Ƶ�����ɿ�
    systick_delay_ms(100);
    gpio_set(ELECTROMAG_PIN,0);
    smotor1_control(1600);
}