//
// Created by Jay on 2022/10/15.
//
#include "task.h"
#include "carmove.h"
#include "motor.h"
#include "openart_mini.h"

uint8_t t_times=0;

void find_t_times(){
    static bool temp=0;

    if(findT!=temp&&findT){
        t_times++;
    }
    temp=findT;
    rt_thread_delay(50);
}

void task_entry(){
    bool temp=false;
    car_go(5,5);
    while(1){
        car_xunxian();
        if(t_times>=4){
            break;
        }
    }
    back_garage();

    car_xunxian();
}
void task_init(void)
{
    rt_thread_t tid;


    //������ʾ�߳� ���ȼ�����Ϊ31
    tid = rt_thread_create("display", task_entry, RT_NULL, 1024, 31, 16);

    //������ʾ�߳�
    if(RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}