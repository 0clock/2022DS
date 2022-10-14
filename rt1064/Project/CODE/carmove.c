//
// Created by Jay on 2022/7/11.
//
#include "carmove.h"
#include "location.h"
#include "motor.h"
#include "buzzer.h"
#include "attitude_solution.h"
#include "smotor.h"
#include "openart_mini.h"
#include "sendmsg.h"

extern const float PI;
extern uint16 msecond,time_second;
int nextpoint=0;
int smotor_duty=0;
bool isgetpicture;

int angelTarget;
/*
***************************************************************
*	�� �� ��: Charge_Locate
* ����˵��: �����жϵõ���ǰ������,���н�ģʽ��ѭ�����У�
*	��    ��: ��
*	�� �� ֵ: ��������
***************************************************************
*/

void charge_locate(void)
{
    //Car.x=Car.x1;
    //Car.y=Car.y1;
//    //��ȡ��ǰ����
//    if (Car.Position_Pointer == 0){ //λ�����1
//        Car.x=0;
//        Car.y=0;
//    }else if(Car.Position_Pointer < locate_sz){
//        Car.x=Car_Location_Route[Car.Position_Pointer-1][0];
//        Car.y=Car_Location_Route[Car.Position_Pointer-1][1];
//    } else if (Car.Position_Pointer==locate_sz){
//        Car.x=Car_Location_Route[locate_sz-1][0];
//        Car.y=Car_Location_Route[locate_sz-1][1];
//    }

/*    Car.x+=Car.MileageX/20;
    Car.y+=Car.MileageY/20;*/
    //�����������Է��������
}

/*
***************************************************************
*	�� �� ��: Get_Target
* ����˵��: ����ṹ����һ������Ԫ�ص�����,ÿ���н�ģʽ֮ǰʹ��
*	��    ��: ����
*	�� �� ֵ: ��
***************************************************************
*/

void get_target() {
    //�����µ�Ŀ�������
    /*
    nextpoint=locate_route();
    Car.x1=originMap[nextpoint][0];
    Car.y1=originMap[nextpoint][1];
    */

    if(Car.Position_Pointer<locate_sz){//locate_sz => true_sz��
        get_route();
    }
//    if(Car.Position_Pointer<locate_sz){
//        Car.x1=Car_Location_Route[Car.Position_Pointer][0];
//        Car.y1=Car_Location_Route[Car.Position_Pointer][1];
//    }else if(Car.Position_Pointer==locate_sz){
//        Car.x1=0;
//        Car.y1=0;
//    }

}

/*
***************************************************************
*	�� �� ��: Get_Road
* ����˵��: ����·�����ǶȺ����
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************
*/

void get_detection(){
    int n=0,dection;
    while(1){
        uart_putstr(USART_1,"1\n");
        if(isDetection){
            dection=picture_type;
            uart_putstr(USART_1,"1\n");
            rt_thread_delay(100);
            if (dection==picture_type) {
                break;
            }
        }else{
            n++;
            Car.Speed_X = picture_xerror_pid(picture_location[0], 78);
            Car.Speed_Y = picture_yerror_pid(picture_location[1], 80);
            //carmove_mileage(1,1);
            if(n>=500){
               break;
            }
        }
        rt_thread_delay(2);
    }
    isDetection=false;
}

void get_location(void){
    charge_locate();
    get_target();
    //������ʽ����ǶȺ;���
    Car.Angel_Target=atan2((Car.x1-Car.x),(Car.y1-Car.y))*180/PI;
    Car.DistanceX=20*(Car.x1-Car.x);
    Car.DistanceY=20*(Car.y1-Car.y);
    //Car.DistanceY=sqrt(Car.DistanceX*Car.DistanceX+Car.DistanceY*Car.DistanceY);
}

void omni_banyun(){
    //��ͷ��ǰ��ͼƬ���˵�ָ��λ��
    reset_mileage();
    switch (pictureBigType) {
        case animal:
            angelTarget=90;
            rt_thread_delay(800);
            Car.DistanceY=20*(Car.x-1);
            Car.x=1;
            break;
        case vehicle:
            angelTarget=0;
            rt_thread_delay(800);
            Car.DistanceY=20*(21-Car.y);
            Car.y=22;
            break;
        case fruit:
            angelTarget=-90;
            rt_thread_delay(800);
            Car.DistanceY=20*(26-Car.x);
            Car.x=26;
            break;
        default:break;
    }
    //Car.DistanceY=sqrt(Car.DistanceX*Car.DistanceX+Car.DistanceY*Car.DistanceY);
    carmove_mileage(Car.DistanceX,Car.DistanceY);
    car_stop();
    reset_mileage();
    //����Ҫ�ı�Car.x,Car.y
}

void search_picture(int tmp){
    switch (tmp) {
        case 0:Car.DistanceX=20;break;
        case 1:Car.DistanceY=-40;break;
        case 2:Car.DistanceY=20;break;
        case 3:Car.DistanceX=-20;break;
        case 4:Car.DistanceX=40;break;
        case 5:Car.DistanceX=-20;break;
    }
    carmove_mileage(Car.DistanceX,Car.DistanceY);
}

void car_recmode(){
    int n=0;
    int tmp=9;

    //����ͼƬλ�øı䳵��λ��,��������ͨ���������ʶ��λ�õģ�������̫���ˣ�Ŀǰ���뷨��ͨ��openart��ʶ��ͼƬ�ù����ڷ���λ���ٽ���λ��
    while(1){
        uart_putstr(USART_1,"1\n");
        if(havePicture) {
            Car.Speed_X = picture_xerror_pid(picture_location[0], 78);
            Car.Speed_Y = picture_yerror_pid(picture_location[1], 79);
            n=0;
        }else{
            //û��ͼƬ����������,û����ֱ���˳�
            reset_mileage();
//            search_picture(n);
            n++;
            if (n <= tmp * 20) {
                Car.Speed_Y = 5;
            }else if (n <= tmp * 60) {
                Car.Speed_Y = -5;
            }else if (n <= tmp * 80) {
                Car.Speed_Y = 5;
            }else if (n <= tmp * 120) {
                Car.Speed_X = 5;
            }else if (n <= tmp * 140) {
                Car.Speed_X = -5;
            }else if (n <= tmp * 180) {
                Car.Speed_X = 5;
            }else if(n<=tmp*300){
                reset_mileage();
                //�޷��ҵ�ֱ����һ���ɡ�����
                Car.x = Car.x1;
                Car.y = Car.y1;
                break;
            }
        }

        if(Car.Speed_X==0&&Car.Speed_Y==0&&Car.Speed_Z==0){
            reset_mileage();
            rt_thread_delay(200);
            Car.Speed_X=picture_xerror_pid(picture_location[0],78);
            Car.Speed_Y=picture_yerror_pid(picture_location[1],79);

            if(Car.Speed_X==0&&Car.Speed_Y==0&&Car.Speed_Z==0) {
                Car.x=Car.x1;
                Car.y=Car.y1;
                break;
            }
        }
        rt_thread_delay(5);
    }
    get_detection();

    grab_picture();//�ȴ�ʶ����ɺ�������ȡͼƬ
    //rt_thread_delay(2500);
    rt_mb_send(buzzer_mailbox,233);
    switch (picture_type) {
        case apple:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,APPLE);break;
        case banana:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,BANANA);break;
        case durian:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,DURIAN);break;
        case grape:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,GRAPE);break;
        case orange:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,ORANGE);break;
        case cat:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,CAT);break;
        case cow:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,CATTLE);break;
        case dog:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,DOG);break;
        case horse:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,HORSE);break;
        case pig:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,PIG);break;
        case bus:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,COACH);break;
        case car:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,CAR);break;
        case plane:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,PLANE);break;
        case ship:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,STEAMSHIP);break;
        case trains:send_msg(USART_8,0,1,(int)Car.x,(int)Car.y,TRAINS);break;
        default:break;
    }
    omni_banyun();//��ȡ��ɺ����ͼƬ��ָ��λ��
    place_picture();
    angelTarget=0;
    rt_thread_delay(800);
}

void car_return(){
    reset_mileage();
    if(Car.x>15){
        angelTarget=-2;
    }else{
        angelTarget=0;
    }

    speed_tar=20;
    rt_thread_delay(800);
    Car.DistanceY=-20*(Car.y+1);
    Car.DistanceX=-20*(Car.x-1.5f);


    carmove_mileage(Car.DistanceX,Car.DistanceY);
    Car.x=1.5f;
    Car.y=-1;
    reset_mileage();
}

void car_noheadmove(){
    bool isArrive=false;
    angelTarget=-Car.Angel_Target;
    
    if(abs(Car.MileageY) < abs(Car.DistanceY)){
        Car.Speed_Y=speed_tar;
        isArrive=false;
    }else{
        Car.Speed_Y=0;
        isArrive=true;
    }

    if(isArrive){
        reset_mileage();
        car_recmode();
        isArrive=false;
        Car.Position_Pointer++;
        get_location();
        angelTarget=-Car.Angel_Target;
        rt_thread_delay(200);

    }
    rt_thread_delay(1000);
}
void car_omnimove(){
    bool x_flag=false,y_flag=false;
    angelTarget=0;
    if(abs(Car.MileageX)<abs(Car.DistanceX)){
        nextpoint++;
        Car.Speed_X=(speed_tar * sin(Car.Angel_Target/180 *PI));//((float)speed_tar * sin(Car.Angel_Target/180 *PI)),((float)speed_tar * cos(Car.Angel_Target/180 *PI)),0);
        if(Car.Speed_X>-1&&Car.Speed_X<0){
            Car.Speed_X=-1;
        }
        if(Car.Speed_X>0&&Car.Speed_X<1){
            Car.Speed_X=1;
        }
        x_flag=false;
    }else{
        Car.Speed_X=0;
        x_flag=true;
    }
    if(abs(Car.MileageY)<abs(Car.DistanceY)){
        Car.Speed_Y=(speed_tar * cos(Car.Angel_Target/180 *PI));
        if(Car.Speed_Y<0&&Car.Speed_Y>-1){
            Car.Speed_Y=-1;
        }
        if(Car.Speed_Y>0&&Car.Speed_Y<1){
            Car.Speed_Y=1;
        }
        y_flag=false;
    }else{
        Car.Speed_Y=0;
        y_flag=true;
    }

    //Car.Speed_Z=-angel_pid(  Car.Angel,-Car.Angel_Target);//�ٶȻ�

    if(x_flag && y_flag){
        car_stop();
        reset_mileage();
        car_recmode();

        //rt_mb_send(buzzer_mailbox,1000);
        x_flag=false;
        y_flag=false;
        rt_thread_delay(300);
        get_location();
        Car.MileageX=0;
        Car.MileageY=0;
        Car.Position_Pointer++;
    }
}

void reset_mileage(){
    Car.Speed_X=0;
    Car.Speed_Y=0;
    Car.Speed_Z=0;

    Car.MileageX=0;
    Car.MileageY=0;
    Car.DistanceX=0;
    Car.DistanceY=0;
}


void carmove_mileage(float x,float y){
    Car.DistanceX=x;
    Car.DistanceY=y;
    while(abs(Car.MileageX)<abs(Car.DistanceX)) {
        if (x > 0) {
            Car.Speed_X = speed_tar;
        } else if (x == 0) {
            Car.Speed_X = 0;
        } else if (x < 0) {
            Car.Speed_X = -speed_tar;
        }
        rt_thread_delay(2);
    }
    Car.Speed_X=0;
    car_stop();
    rt_thread_delay(400);
    while(abs(Car.MileageY)< abs(Car.DistanceY)){
        if (y > 0) {
            Car.Speed_Y = speed_tar;
        } else if (y == 0) {
            Car.Speed_Y = 0;
        } else if (y < 0) {
            Car.Speed_Y = -speed_tar;
        }
        rt_thread_delay(2);
    }
    reset_mileage();
}

void car_xunxian(){
    smotor_duty=picture_xerror_pid(road_location,90);
    if(road_location!=0){
        smotor1_control(smotor_duty);
    }
}

void back_garage(){
    float angeltemp;
    smotor1_control(-400);
    angeltemp=Car.Angel;
    while(1){
        car_go(-3,-3);
        if(Car.Angel-angeltemp>=85){
            rt_mb_send(buzzer_mailbox, 100);
            smotor1_control(0);
            break;
        }
    }

    car_go(-3,-3);
    rt_thread_delay(500);
    rt_mb_send(buzzer_mailbox,100);
    car_stop();
    rt_thread_delay(5000);
    rt_mb_send(buzzer_mailbox, 100);
    car_stop();
    angeltemp=Car.Angel;
    car_go(3,3);
    rt_thread_delay(500);
    smotor1_control(-400);
    while (1){
        if(angeltemp-abs(Car.Angel)>=20){
            smotor1_control(0);
            break;
        }
    }
    rt_thread_delay(1000);
    car_stop();
}