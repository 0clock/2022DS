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


    //创建显示线程 优先级设置为31
    tid = rt_thread_create("display", task_entry, RT_NULL, 1024, 31, 16);

    //启动显示线程
    if(RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}