#include "headfile.h"
#include "encoder.h"
#include "display.h"
#include "location.h"
#include "button.h"
#include "attitude_solution.h"
#include "MahonyAHRS.h"
#include "imgproc.h"
#include "flash_param.h"
#include "carmove.h"
#include "openart_mini.h"
#include "smotor.h"

enum Gui_Page Page_Number=InfoPage;
bool Gui_Page_Active=true;

extern image_t img_raw;
extern image_t img_thres;
extern image_t img_line;
extern float ahrs_kp;
extern int tempTest;
extern double getAngel_k;

extern float pictureP,pictureI,pictureD;


void gui_info(){
    ips200_showstr(0,1,"Encoder:");
    ips200_showint16(5,2,RC_encoder1);
    ips200_showint16(5,3,RC_encoder2);
    ips200_showstr(160,2,"Speed");

    ips200_showstr(0,6,"Angel:");
    ips200_showfloat(5,7,Car.Angel,3,4);

    ips200_showstr(0,9,"Line:");
    ips200_showint8(5,10,road_location);

    ips200_showstr(0,12,"Smotor:");
    ips200_showint16(5,13,smotor_duty);
}



void GUI_TargetPoint(){
    //ips200_drawRectangle(55, 11, 265, 161,GREEN);
    ips200_showstr(200,0,"err:");
    ips200_showint8(200,1,edge_rotation[0]);
    ips200_showint8(200,2,edge_rotation[1]);
    for(int i=0;i<locate_sz;i++){
        //ips200_drawCircle(55+originMap[i][0]*6,161-originMap[i][1]*6,1,WHITE);
//        if(i<=8) {
//            ips200_showint8(50, i, originMap[i][0]);
//            ips200_showint8(90, i , originMap[i][1]);
//        }else{
//            ips200_showint8(180,i-9,originMap[i][0]);
//            ips200_showint8(220,i-9,originMap[i][1]);
//        }
        //ips200_showint8(55+originMap[i][0]*6,(161-originMap[i][1]*6)/16-1,originMap[i][0]);
        //ips200_drawline(55+originMap[i][0]*6,161-originMap[i][1]*6,240+originMap[i+1][0]*6,80-originMap[i+1][1]*6,WHITE);
    }
    //ips200_drawpoint(Car.x,Car.y,RED);
}

void config_page(){
    uint8_t line=1;
    switch (config_action) {
        case MileageX:
            ips200_showstr(10,line,"#");
            break;
        case MileageY:
            ips200_showstr(10,line+1,"#");
            break;
        case AngelP:
            ips200_showstr(10,line+2,"#");
            break;
        case AngelI:
            ips200_showstr(10,line+3,"#");
            break;
        case AngelD:
            ips200_showstr(10,line+4,"#");
            break;
        case MotorP:
            ips200_showstr(10,line+5,"#");
            break;
        case MotorI:
            ips200_showstr(10,line+6,"#");
            break;
        case MotorD:
            ips200_showstr(10,line+7,"#");
            break;
        default:break;
    }
    ips200_showstr(30,line,"MileKX:");
    ips200_showfloat(100,line,MileageKx,1,5);
    ips200_showfloat(200,line,Car.MileageX,3,2);
    ips200_showstr(30,line+1,"MileKY:");
    ips200_showfloat(100,line+1,MileageKy,1,5);
    ips200_showfloat(200,line+1,Car.MileageY,3,2);
    ips200_showstr(30,line+2,"AngelP:");
    ips200_showfloat(100,line+2,Angel_KP,2,3);
    ips200_showstr(30,line+3,"AngelI:");
    ips200_showfloat(100,line+3,Angel_KI,2,3);
    ips200_showstr(30,line+4,"AngelD:");
    ips200_showfloat(100,line+4,Angel_KD,2,3);
    ips200_showstr(30,line+5,"MotorP:");
    ips200_showfloat(100,line+5,Position_KP,3,2);
    ips200_showstr(30,line+6,"MotorI:");
    ips200_showfloat(100,line+6,Position_KI,3,2);
    ips200_showstr(30,line+7,"MotorD:");
    ips200_showfloat(100,line+7,Position_KD,3,2);
}
void display_page(){
    if(Gui_Page_Active){
        ips200_clear(BLACK);
        Gui_Page_Active=false;
    }
    switch(Page_Number){
        case InfoPage:
            ips200_showstr(0,0,"Info:");
            gui_info();
            break;
        case ConfigPage:
            ips200_showstr(0,0,"Config:");
            config_page();
            // 调试模式下定时写入flash参数
            break;
        case TargetPointPage:
            ips200_showstr(0,0,"Route");
            GUI_TargetPoint();
            break;
        case CameraPage:
            ips200_showstr(0,0,"openart:");
            if(havePicture&&openartMode==get_picture) {
                ips200_showstr(10, 1, "picture:");
                ips200_showint16(10, 2, picture_location[0]);
                ips200_showint16(80, 2, picture_location[1]);
            }
            //ips200_displayimage032_zoom1(mt9v03x_csi_image[0], MT9V03X_CSI_W  , MT9V03X_CSI_H, 66, 26, MT9V03X_CSI_W, MT9V03X_CSI_H);
            //ips200_showfloat(80,0,thres,3,2);
            //mt9v03x_csi_finish_flag = 0;	//清除采集完成标志位
            //ImageHandel();
            //ips200_displayimage032_zoom1(img_thres.data, MT9V03X_CSI_W, MT9V03X_CSI_H, 66, 26, MT9V03X_CSI_W, MT9V03X_CSI_H);
            //ips200_displayimage032_zoom(img_thres.data, MT9V03X_CSI_W, MT9V03X_CSI_H, 240, 135);	//显示摄像头图像
            //ips200_displayimage032_zoom(img_raw.data, MT9V03X_CSI_W, MT9V03X_CSI_H, 240, 135);	//显示摄像头图像
//            ips200_drawline(66+Xt,26+Yl,66+Xt,26+Yl,BLUE);
//            ips200_drawline(66+Xt,26+Yr,66+Xb,26+Yr,BLUE);
//            ips200_drawline(66+Xb,26+Yr,66+Xb,26+Yl,BLUE);
//            ips200_drawline(66+Xb,26+Yl,66+Xt,26+Yl,BLUE);
            break;
        case AboutPage:
            ips200_showstr(0,0,"About:");

            break;
    }
}


void display_entry(void *parameter)
{


    while(1){
        display_page();
        //ips200_showstr(10,0,"camera");
        //ips200_displayimage032_zoom1(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 66, 26, MT9V03X_CSI_W, MT9V03X_CSI_H);
    }


}




void display_init(void)
{
    rt_thread_t tid;
    
    //初始化屏幕
    ips200_init();
    ips200_clear(BLACK);

    //创建显示线程 优先级设置为31
    tid = rt_thread_create("display", display_entry, RT_NULL, 1024, 31, 16);
    
    //启动显示线程
    if(RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}