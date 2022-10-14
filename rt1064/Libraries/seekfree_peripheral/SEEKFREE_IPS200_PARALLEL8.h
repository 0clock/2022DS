/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		IPS 2.0��Һ��
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.26
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-09-17
 * @note		
					���߶��壺
					------------------------------------ 
						ģ��ܽ�            ��Ƭ���ܽ�
						D0                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D0_PIN �궨��
						D1                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D1_PIN �궨��
						D2                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D2_PIN �궨��
						D3                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D3_PIN �궨��
						D4                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D4_PIN �궨��
						D5                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D5_PIN �궨��
						D6                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D6_PIN �궨��
						D7                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D7_PIN �궨��
                                                                                            
						BL                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_BL_PIN �궨��
						CS                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_CS_PIN �궨��
						RD                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_RD_PIN �궨��
						WR                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_WR_PIN �궨��
						RS                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_RS_PIN �궨��
						RST                 �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_RST_PIN �궨��

						��Դ����
						VCC 3.3V��Դ
						GND ��Դ��
						���ֱ���240*320
					------------------------------------ 

 ********************************************************************************************************************/

#ifndef _SEEKFREE_IPS200PARALLEL8_H
#define _SEEKFREE_IPS200PARALLEL8_H

#include "common.h"
#include "SEEKFREE_FONT.h"

     
//-------������ɫ��SEEKFREE_FONT.h�ļ��ж���----------
//#define RED          	    0xF800	//��ɫ
//#define BLUE         	    0x001F  //��ɫ
//#define YELLOW       	    0xFFE0	//��ɫ
//#define GREEN        	    0x07E0	//��ɫ
//#define WHITE        	    0xFFFF	//��ɫ
//#define BLACK        	    0x0000	//��ɫ 
//#define GRAY  			0X8430 	//��ɫ
//#define BROWN 			0XBC40 	//��ɫ
//#define PURPLE    		0XF81F	//��ɫ
//#define PINK    		    0XFE19	//��ɫ


#define IPS200_BGCOLOR      WHITE	//������ɫ
#define IPS200_PENCOLOR     RED		//������ɫ


//����ֻ��ѡ��B C D�������˿��е����ţ�����ʹ�ÿ���GPIO�������ʾ�ٶ�
#define IPS200_RD_PIN  		B0
#define IPS200_WR_PIN  		B1
#define IPS200_RS_PIN  		B2
#define IPS200_RST_PIN 		C19
#define IPS200_CS_PIN  		B3
#define IPS200_BL_PIN  		C18






//������Ļ�����������ӵĶ˿�����
#define IPS200_PORT_NUM    2    //�����ò���1�����뵥Ƭ����һ���˿�����  2���뵥Ƭ���������˿�����


//-------------------------���ݶ˿ڶ���ͬһ��PORT��--------------------
#if(1==IPS200_PORT_NUM)

//����ֻ��ѡ��B C D�������˿��е����ţ�����ʹ�ÿ���GPIO�������ʾ�ٶ�
//�����IPS200_PORT_NUM�궨��ѡ�ź��ʵ�����
//IPS200_PORT_NUMΪ1ʱ��8���������ű������� ����C0-C7,C6-C13�ȵȡ�
//�л����ź�ע���޸�IPS200_DATA_PORT�궨��
#define IPS200_D0_PIN 		C8
#define IPS200_D1_PIN 		C9
#define IPS200_D2_PIN 		C10
#define IPS200_D3_PIN 		C11
#define IPS200_D4_PIN 		C12
#define IPS200_D5_PIN 		C13
#define IPS200_D6_PIN 		C14
#define IPS200_D7_PIN 		C15

//�������ݶ˿�����PORT���л����ź���ظ�����������PORT���и���
//Ĭ����������ʹ�õ���C�˿ڣ��������Ĭ������Ϊ2
#define IPS200_DATA_PORT    2       //1��B�˿�  2��C�˿�  3��D�˿�
                            
#if  ( 1 == IPS200_DATA_PORT )
    #define IPS200_DATAPORT PORTB_FAST_DR	    //�궨�����GPIO������Ĵ���
#elif( 2 == IPS200_DATA_PORT )
    #define IPS200_DATAPORT PORTC_FAST_DR	    //�궨�����GPIO������Ĵ���
#elif( 3 == IPS200_DATA_PORT )
    #define IPS200_DATAPORT PORTD_FAST_DR	    //�궨�����GPIO������Ĵ���
#endif

#define DATA_START_NUM		(IPS200_D0_PIN&0x1f)  //�궨���������ŵ���ʼ���


//-------------------------���ݶ˿ڶ���������PORT��--------------------
//����D0-D3��һ���˿��ϣ�D4-D7������һ���˿���
#elif(2==IPS200_PORT_NUM)

//IPS200_PORT_NUMΪ2ʱ����������ǰ�ĸ�����ĸ����Խ��ڵ�Ƭ���Ĳ�ͬ�˿��ϣ�
//D0-D3�ĸ��������ű������� ����C0-C3,C1-C4�ȵȣ�
//D4-D7�ĸ��������ű������� ����B0-B3,B1-B4�ȵȡ�
//�������ӵ���ͬ�˿ڵ���˼������Ļ��D0-D3��C1-C4���ӣ�D4-D7��B2-B5���ӡ�
//�л����ź�ע���޸�IPS200_DATA_PORT1��IPS200_DATA_PORT2�궨��
#define IPS200_D0_PIN 		B16
#define IPS200_D1_PIN 		B17
#define IPS200_D2_PIN 		B18
#define IPS200_D3_PIN 		B19
#define IPS200_D4_PIN 		D12
#define IPS200_D5_PIN 		D13
#define IPS200_D6_PIN 		D14
#define IPS200_D7_PIN 		D15

//�������ݶ˿�����PORT���л����ź���ظ�����������PORT���и���
#define IPS200_DATA_PORT1    1       //1��B�˿�  2��C�˿�  3��D�˿�
                            
#if  ( 1 == IPS200_DATA_PORT1 )
    #define IPS200_DATAPORT1 PORTB_FAST_DR	    //�궨�����GPIO������Ĵ���
#elif( 2 == IPS200_DATA_PORT1 )
    #define IPS200_DATAPORT1 PORTC_FAST_DR	    //�궨�����GPIO������Ĵ���
#elif( 3 == IPS200_DATA_PORT1 )
    #define IPS200_DATAPORT1 PORTD_FAST_DR	    //�궨�����GPIO������Ĵ���
#endif

#define DATA_START_NUM1		(IPS200_D0_PIN&0x1f)  //�궨���������ŵ���ʼ���


#define IPS200_DATA_PORT2    3       //1��B�˿�  2��C�˿�  3��D�˿�
                            
#if  ( 1 == IPS200_DATA_PORT2 )
    #define IPS200_DATAPORT2 PORTB_FAST_DR	    //�궨�����GPIO������Ĵ���
#elif( 2 == IPS200_DATA_PORT2 )
    #define IPS200_DATAPORT2 PORTC_FAST_DR	    //�궨�����GPIO������Ĵ���
#elif( 3 == IPS200_DATA_PORT2 )
    #define IPS200_DATAPORT2 PORTD_FAST_DR	    //�궨�����GPIO������Ĵ���
#endif

#define DATA_START_NUM2		(IPS200_D4_PIN&0x1f)  //�궨���������ŵ���ʼ���


#endif 







#define IPS200_BL(x)		fast_gpio_set(IPS200_BL_PIN,x)
#define IPS200_CS(x)       	fast_gpio_set(IPS200_CS_PIN,x)
#define IPS200_RD(x)       	fast_gpio_set(IPS200_RD_PIN,x)
#define IPS200_WR(x)       	fast_gpio_set(IPS200_WR_PIN,x)
#define IPS200_RS(x)       	fast_gpio_set(IPS200_RS_PIN,x)
#define IPS200_RST(x)      	fast_gpio_set(IPS200_RST_PIN,x)


#define IPS200_W 240
#define IPS200_H 320


//������ʾ����
//0 ����ģʽ
//1 ����ģʽ  ��ת180��
//2 ����ģʽ
//3 ����ģʽ  ��ת180��
#define IPS200_DISPLAY_DIR 2

#if (0==IPS200_DISPLAY_DIR || 1==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX	IPS200_W	//Һ��X�����
#define IPS200_Y_MAX	IPS200_H   //Һ��Y�����
     
#elif (2==IPS200_DISPLAY_DIR || 3==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX	IPS200_H	//Һ��X�����
#define IPS200_Y_MAX	IPS200_W   //Һ��Y�����
     
#else
#error "IPS200_DISPLAY_DIR �������"
     
#endif


void ips200_init(void); //��ʼ��Ӳ��
void ips200_w_data(uint8 dat);
void ips200_wr_reg(uint16 com);
void ips200_wr_data(uint8 dat);
void ips200_wr_data16(uint16 dat);
void ips200_w_reg(uint8 com,uint8 dat);
void ips200_address_set(uint16 x1,uint16 y1,uint16 x2,uint16 y2);
void ips200_clear(uint16 color);
void ips200_drawpoint(uint16 x,uint16 y,uint16 color);
void ips200_showchar(uint16 x,uint16 y,const int8 dat);
void ips200_showstr(uint16 x,uint16 y,const int8 dat[]);


void ips200_showint8(uint16 x,uint16 y,int8 dat);
void ips200_showuint8(uint16 x,uint16 y,uint8 dat);
void ips200_showint16(uint16 x,uint16 y,int16 dat);
void ips200_showuint16(uint16 x,uint16 y,uint16 dat);
void ips200_showint32(uint16 x,uint16 y,int dat,uint8 num);
void ips200_showfloat(uint16 x,uint16 y,double dat,int8 num,int8 pointnum);
void ips200_showimage(uint16 x,uint16 y,uint16 w,uint16 l,const unsigned char *p);

void ips200_displayimage032(uint8 *p, uint16 width, uint16 height);
void ips200_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage032_zoom1(uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_zoom1(uint16 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_grayscale_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage7725(uint8 *p, uint16 width, uint16 height);
void ips200_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color);

#endif

