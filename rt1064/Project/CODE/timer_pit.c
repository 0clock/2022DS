#include "encoder.h"
#include "motor.h"
#include "timer_pit.h"
#include "elec.h"
#include "MahonyAHRS.h"
#include "attitude_solution.h"
#include "location.h"
#include "imgproc.h"
#include "flash_param.h"
#include "carmove.h"
#include "openart_mini.h"

uint32 getAngel_times=0;
double getAngel_k=0;
double getAngelN=0;
float getAngel_Err=0.00003f;
void Find_Edge_1(void);

extern image_t img_raw;
extern image_t img_thres;
extern image_t img_line;

extern int angelTarget;
uint16 msecond=0,time_second=0;

void timer1_pit_entry(void *parameter)
{
    static uint32 time;
    msecond++;

    time++;
    if( 0==(time_second%1000)){
        time_second++;
    }
    getAngel_times++;

    //�ɼ����������� 
    //Mahony_computeAngles();
    ICM_getEulerianAngles();
    if(0 == (time%1000)) {
//        getAngel_Err+=getAngel_Err;
        //eulerAngle.yaw=getAngel_Err*getAngel_times;
        getAngel_k=eulerAngle.yaw/(getAngel_times*1.0);
    }

    if(0 == (time%100)&&openartMode==get_picture) {
        uart_putstr(USART_4,"2\n");
    }
    eulerAngle.yaw=eulerAngle.yaw+getAngel_Err*getAngel_times;
    Car.Angel=eulerAngle.yaw;
    //��ȡ��������ֵ
    encoder_get();


    Car.Speed_Z=-angel_pid(  eulerAngle.yaw,angelTarget);//omnimoveģʽ��Ŀ�귽��һֱΪ0
    //���Ƶ��ת��
    motor_control(true);
}


void timer_pit_init(void)
{
    rt_timer_t timer;
    
    //����һ����ʱ�� ��������
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);

    //������ʱ��
    if(RT_NULL != timer)
    {
        rt_timer_start(timer);
    }
}