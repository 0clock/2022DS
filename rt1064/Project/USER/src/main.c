/********************************************************************************************************************* * COPYRIGHT NOTICE * Copyright (c) 2019,逐飞科技 * All rights reserved. * 技术讨论QQ群：一群：179029047(已满)  二群：244861897 * * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途， * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。 * * @file       		main * @company	   		成都逐飞科技有限公司 * @author     		逐飞科技(QQ3184284598) * @version    		查看doc内version文件 版本说明 * @Software 		IAR 8.3 or MDK 5.28 * @Target core		NXP RT1064DVL6A * @Taobao   		https://seekfree.taobao.com/ * @date       		2019-04-30 ********************************************************************************************************************///整套推荐IO查看Projecct文件夹下的TXT文本//打开新的工程或者工程移动了位置务必执行以下操作//第一步 关闭上面所有打开的文件//第二步 project  clean  等待下方进度条走完//下载代码前请根据自己使用的下载器在工程里设置下载器为自己所使用的#include "headfile.h"#include "display.h"#include "timer_pit.h"#include "encoder.h"#include "buzzer.h"#include "button.h"#include "motor.h"#include "elec.h"#include "openart_mini.h"#include "smotor.h"#include "location.h"#include "attitude_solution.h"#include "vofa.h"#include "flash_param.h"#include "imgproc.h"#include "carmove.h"#include "MahonyAHRS.h"#include "sendmsg.h"#include "task.h"extern image_t img_raw;extern image_t img_thres;extern image_t img_line;rt_sem_t camera_sem;void Find_Edge_1(void);extern int openartBuffer;uint8 uart_test;int main(void){    rt_thread_delay(800);    ips200_init();    ips200_showstr(0,0,"mt9v03x-init...");    //mt9v03x_csi_init();    ips200_showstr(150,0,"ok");    ips200_showstr(0,1,"imu963ra-init...");    icm20602_init_spi();    gyroOffset_init();    ips200_showstr(150,1,"ok");	    ips200_showstr(0,2,"encoder-init...");    encoder_init();    ips200_showstr(150,2,"ok");    ips200_showstr(0,3,"buzzer-init...");    buzzer_init();    ips200_showstr(150,3,"ok");    ips200_showstr(0,4,"button-init...");    button_init();    ips200_showstr(150,4,"ok");    ips200_showstr(0,5,"motor-init...");    motor_init();    ips200_showstr(150,5,"ok");    ips200_showstr(0,6,"flash-init...");    flash_param_init();    //第一次烧写flash参数时需要将下面两句话反过来用，并将debug里面的    //flash_param_write();    flash_param_load();    ips200_showstr(150,6,"ok");    //elec_init();    ips200_showstr(0,7,"smotor-init...");    smotor_init();    ips200_showstr(150,7,"ok");		    ips200_showstr(0,8,"timer_pit...");    timer_pit_init();    ips200_showstr(150,8,"ok");    ips200_showstr(0,9,"uart-init...");    uart_init (USART_8, 115200,UART8_TX_D16,UART8_RX_D17); //初始化串口    // VOFA+//    VOFA* VOFA_pt = vofa_create();       //创建VOFA对象//    vofa_init(VOFA_pt//		,                   //初始化当前的vofa对象//              vofa_ch_data,ch_sz,//              vofa_image,image_sz,//              custom_buf,custom_sz,//              cmd_rxbuf,cmd_sz,//              USART_8,USART_8,USART_8);    ips200_showstr(150,9,"ok");    ips200_showstr(0,10,"openart_mini...");    openart_mini();    ips200_showstr(150,10,"ok");    EnableGlobalIRQ(0);    display_init();    rt_thread_delay(1000);    rt_mb_send(buzzer_mailbox,1000);    Gui_Page_Active=true;    task_init();    while (1){        find_t_times();        rt_thread_delay(1);//不留空的话，其他线程运行不了    }}  