//
// Created by Jay on 2022/10/15.
//
#include "task.h"
#include "carmove.h"
#include "motor.h"

void task_entry(){
    car_go(5,5);
    while(1){
        car_xunxian();
    }
    //back_garage();
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