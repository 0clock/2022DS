#ifndef _encoder_h
#define _encoder_h

#include "headfile.h"

extern uint16 speed_l, speed_r;
extern int32 encoder1,encoder2;//��������ֵ
extern int32 RC_encoder1,RC_encoder2;//�˲�֮��encoder��ֵ

void encoder_init(void);
void encoder_get(void);
#endif