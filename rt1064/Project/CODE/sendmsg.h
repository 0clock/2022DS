//
// Created by Jay on 2022/7/26.
//

#ifndef MY_SMARTCAR_RTT_SENDMSG_H
#define MY_SMARTCAR_RTT_SENDMSG_H

#include "headfile.h"

typedef enum
{
    CATEGORY_NULL   = 0,        //�����
    DOG             = 7,        //��
    HORSE           = 8,        //��
    CAT             = 9,        //è
    CATTLE          = 10,       //ţ
    PIG             = 11,       //��
    ORANGE          = 13,       //����
    APPLE           = 14,       //ƻ��
    DURIAN          = 15,       //����
    GRAPE           = 16,       //����
    BANANA          = 17,       //�㽶
    TRAINS          = 19,       //��
    STEAMSHIP       = 20,       //�ִ�
    PLANE           = 21,       //�ɻ�
    CAR             = 22,       //С�γ�
    COACH           = 23,       //��ͳ�
    CARRY           = 54,       //����
}category_enum;


void send_msg(UARTN_enum uartn, uint16 second, uint16 msecond, uint8 img_pos_x, uint8 img_pos_y, category_enum cg);

#endif //MY_SMARTCAR_RTT_SENDMSG_H
