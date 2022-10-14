#include "encoder.h"
#include "filter.h"
#include "location.h"
#include "flash_param.h"

//---------------------结构体---------------------//
struct RC_Para Encoder1_Para = {0,0,0.25};
struct RC_Para Encoder2_Para = {0,0,0.25};
struct RC_Para Encoder3_Para = {0,0,0.25};
struct RC_Para Encoder4_Para = {0,0,0.25};

RC_Filter_pt RC_Encoder1 = &Encoder1_Para;
RC_Filter_pt RC_Encoder2 = &Encoder2_Para;

int32 encoder1=0,encoder2=0;//编码器的值
int32 RC_encoder1,RC_encoder2;//滤波之后encoder的值
uint16 speed_l, speed_r;



void encoder_init(void)
{
    //一个QTIMER可以 创建两个正交解码
    //qtimer_quad_init(QTIMER_3,QTIMER3_TIMER2_B18,QTIMER3_TIMER3_B19);
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);
    //初始化 QTIMER_1 A相使用QTIMER1_TIMER0_C0 B相使用QTIMER1_TIMER1_C1
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER2_C2,QTIMER1_TIMER3_C24);
    //初始化 QTIMER_1 A相使用QTIMER2_TIMER0_C3 B相使用QTIMER2_TIMER3_C25
    //qtimer_quad_init(QTIMER_2,QTIMER2_TIMER0_C3,QTIMER2_TIMER3_C25);
}

void omni_mileage(){
}

void encoder_get(void)
{
    encoder1 = -qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0 ); //这里需要注意第二个参数务必填写A相引脚
    encoder2 = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER2_C2); //这里需要注意第二个参数务必填写A相引脚
    //计算位移(单位：m)
    //Car.mileage=(Encoder/1024)*(45/104)*2*PI*0.03;
    omni_mileage();
    RC_encoder1 = (int16_t)RCFilter(encoder1,RC_Encoder1);
    RC_encoder2 = (int16_t)RCFilter(encoder2,RC_Encoder2);

    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0 );
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_C2 );
}
