//
// Created by Jay on 2022/6/5.
//

#ifndef RT1064_FLASH_PARAM_H
#define RT1064_FLASH_PARAM_H


#ifndef _FLASH_PARAM_H_
#define _FLASH_PARAM_H_

// �ɵ�����д��flash

#include <stdint.h>
#include <stdbool.h>


extern float thres;                 // ��ֵ����ֵ����Ҫ��������ʼ��(����ʹ������Ӧ��ֵ����ʹ�ø���ֵ)
extern float block_size;            // ����Ӧ��ֵ��block��С
extern float clip_value;            // ����Ӧ��ֵ����ֵ�ü���
extern float begin_x;               // ��ʼ�����ͼ�����ĵ�����ƫ����
extern float begin_y;               // ��ʼ�����ͼ��ײ�������ƫ����
extern float line_blur_kernel;      // ���������˲��˵Ĵ�С
extern float pixel_per_meter;       // ����ͼ�У�ÿ�����ض�Ӧ�ĳ���
extern float sample_dist;           // ���ߵȾ�����ļ��
extern float angle_dist;            // �������ת��ʱ�����������ľ���
extern float aim_distance;          // Ԥê�㳤��
extern float far_rate;              //
extern bool adc_cross;              // �Ƿ����õ�й�ʮ��

extern float MileageKx; //λ�Ʊ���
extern float MileageKy;
extern float Angel_KP ;
extern float Angel_KI ;
extern float Angel_KD ;

//��¼PIDϵ��
extern float Position_KP;
extern float Position_KI;
extern float Position_KD;

void flash_param_init();

bool flash_param_check();

void flash_param_load();

void flash_param_write();

#endif /* _FLASH_PARAM_H_ */


#endif //RT1064_FLASH_PARAM_H
