//
// Created by Jay on 2022/7/11.
//

#ifndef MY_SMARTCAR_RTT_CARMOVE_H
#define MY_SMARTCAR_RTT_CARMOVE_H
#include "headfile.h"

extern int nextpoint;
void car_noheadmove(void);
void car_omnimove(void);
void car_return(void);
void reset_mileage(void);
void carmove_mileage(float x,float y);

#endif //MY_SMARTCAR_RTT_CARMOVE_H
