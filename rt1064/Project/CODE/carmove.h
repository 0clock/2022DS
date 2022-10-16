//
// Created by Jay on 2022/7/11.
//

#ifndef MY_SMARTCAR_RTT_CARMOVE_H
#define MY_SMARTCAR_RTT_CARMOVE_H
#include "headfile.h"

extern int nextpoint;
extern int smotor_duty;
void car_noheadmove(void);
void car_omnimove(void);
void car_return(void);
void reset_mileage(void);
void back_garage(void);
void cefang();
void carmove_mileage(float x,float y);
void car_xunxian();
void t_locate_right();
void go_angel(int target_angel,int target_speed,int16 duty);

#endif //MY_SMARTCAR_RTT_CARMOVE_H
