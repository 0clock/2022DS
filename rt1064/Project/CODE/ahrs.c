//
// Created by Jay on 2022/4/9.
//

#include "ahrs.h"
#include "math.h"
#include "imu.h"
#include "clock_config.h"
#include "filter.h"

Q4_t Q4 = {1, 0, 0, 0};  //��Ԫ��
float ahrs_kp = 0.15f; //PI��������������������ϵ
float ahrs_ki = 0.01f;
float angle_offset = 0;
float cpmangle_z = 0;
vectorxyz integral;  //��������������
vectorxyz ahrs_angle;  //AHRS��̬�������


/*
***************************************************************
*�� �� ��: myinvSqrt(float x)
*����˵��: ���ټ���x�����Ŀ���
*��    ��: �������ֵ
*�� �� ֵ: ���
***************************************************************
*/
float myinvSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i>>1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}
/*
***************************************************************
*�� �� ��: myatan(float v)
*����˵��: ���ټ��㷴����
*��    ��: �������ֵ
*�� �� ֵ: ���
***************************************************************
*/
float myatan(float v)
{
    float v2 = v*v;
    return (v*(1.6867629106f + v2*0.4378497304f)/(1.6867633134f + v2));
}


/*
***************************************************************
*�� �� ��: AHRS_Reset()
*����˵��: AHRS��ز�������
*��    ��: ��
*�� �� ֵ: ��
***************************************************************
*/

void AHRS_Reset(void)
{
    Q4.q0 = 1;
    Q4.q1 = 0;
    Q4.q2 = 0;
    Q4.q3 = 0;
    angle_offset = 0;
    integral.x = 0;
    integral.y = 0;
    integral.z = 0;
}

/*
***************************************************************
*�� �� ��: AHRS_quat_update(vectorxyz gyro, vectorxyz acc, float interval)
*����˵��: ������Ԫ��
*��    ��: ���ٶȣ����ٶȣ�������
*�� �� ֵ: ���
***************************************************************
*/
void AHRS_quat_update(vectorxyz gyro, vectorxyz acc, float interval)
{
    float q0 = Q4.q0;
    float q1 = Q4.q1;
    float q2 = Q4.q2;
    float q3 = Q4.q3;
/***********  ģ��  ************/
    float norm = myinvSqrt(acc.x * acc.x + acc.y * acc.y + acc.z * acc.z);
/***********  �ӼƲ���Ļ�������ϵ   **********/
    float ax = acc.x * norm;
    float ay = acc.y * norm;
    float az = acc.z * norm;
/***********  ��Ԫ��������Ļ�������ϵ  ***************/
    float half_vx = q1*q3 - q0*q2;
    float half_vy = q2*q3 + q0*q1;
    float half_vz = -0.5f + q0*q0 + q3*q3;
/***********  �����Ӽƻ���������ϴ���Ԫ��������������  ************/
    float half_ex = ay*half_vz - az*half_vy;
    float half_ey = az*half_vx - ax*half_vz;
    float half_ez = ax*half_vy - ay*half_vx;
/***********  ʹ��PI������ ������������ *************/
    integral.x += half_ex * ahrs_ki * interval;
    integral.y += half_ey * ahrs_ki * interval;
    integral.z += half_ez * ahrs_ki * interval;

    float gx = (gyro.x + ahrs_kp * half_ex + integral.x) * 0.5f * interval;
    float gy = (gyro.y + ahrs_kp * half_ey + integral.y) * 0.5f * interval;
    float gz = (gyro.z + ahrs_kp * half_ez + integral.z) * 0.5f * interval;

/**********  ������Ԫ��  ********/
    Q4.q0 += (-q1 * gx - q2 * gy - q3 * gz);
    Q4.q1 += ( q0 * gx + q2 * gz - q3 * gy);
    Q4.q2 += ( q0 * gy - q1 * gz + q3 * gx);
    Q4.q3 += ( q0 * gz + q1 * gy - q2 * gx);


    // ��λ����Ԫ���ڿռ���תʱ�������죬������ת�Ƕȣ������㷨�������Դ�����������任
    norm = myinvSqrt(Q4.q0 * Q4.q0 + Q4.q1 * Q4.q1 + Q4.q2 * Q4.q2 + Q4.q3 * Q4.q3);

    Q4.q0 *= norm;
    Q4.q1 *= norm;
    Q4.q2 *= norm;
    Q4.q3 *= norm;      // ��ȫ�ֱ�����¼��һ�μ������Ԫ��ֵ
}

/*
***************************************************************
*�� �� ��: AHRS_quat_to_angle(void)
*����˵��: ������̬��
*��    ��:��
*�� �� ֵ: ��
***************************************************************
*/
void AHRS_quat_to_angle(void)
{
    float conv_x = 2.0f * (Q4.q0 * Q4.q2 - Q4.q1 * Q4.q3);
    float conv_y = 2.0f * (Q4.q0 * Q4.q1 + Q4.q2 * Q4.q3);
    float conv_z = Q4.q0 * Q4.q0 - Q4.q1 * Q4.q1 - Q4.q2 * Q4.q2 + Q4.q3 * Q4.q3;
/*******  ��̬����  ********/
    ahrs_angle.x = myatan(conv_y * myinvSqrt(conv_x * conv_x + conv_z * conv_z)) * 57.2958f;
    ahrs_angle.y = asin(2 * (Q4.q0 * Q4.q2 - Q4.q3 * Q4.q1)) * 57.2958f;
    ahrs_angle.z = atan2(2 * (Q4.q0 * Q4.q3 + Q4.q1 * Q4.q2), 1 - 2 * (Q4.q2 * Q4.q2 + Q4.q3 * Q4.q3)) * 57.2958f;
/*******  �Ƕ�΢��  ********/
    //�ж�yaw��ƫ�������Լ�
//    static uint16_t count = 0;
//    if(count >
//    angle_offset -= 0.0005585 * 0.05f;  //����yaw �����Լ������ٶ� ���в���  1ms����һ�� ����
//	ahrs_angle.z += angle_offset;      //����yaw �����Լ������ٶ� ���в���
}
/*
***************************************************************
*�� �� ��:ahrs_update(void)
*����˵��: ��̬����
*��    ��:��
*�� �� ֵ: ��
***************************************************************
*/
void ahrs_update(void)
{
    // ��ȡ���Դ���������
    icm_getvalues();
    static uint32 lasttime = 0;
    float dt = (rt_tick_get() - lasttime)/1000.0f;
    if (dt > 0.005)                                              //��̬�����������6ms(���޸�)
    {
        lasttime = rt_tick_get();
        return;
    }
    lasttime = rt_tick_get();

    // quat update
    //AHRS_quat_update(gyro_MovAverFilter, acc_vector, dt);   //��ͨ���������˲�
    AHRS_quat_update(gyro_vector, acc_vector, dt);


    // ������̬��
    AHRS_quat_to_angle();
    cpmangle_z = complementary_filter2(ahrs_angle.z,gyro_vector.z,dt);
}

AHRS_t AHRS =
        {
                ahrs_update,
        };
/*
***************************************************************
*�� �� ��: AHRS_get_yaw(void)
*����˵��: AHRS��̬����õ�yaw��
*��    ��:��
*�� �� ֵ: ��
***************************************************************
*/
void AHRS_get_yaw(void)
{
    AHRS.update();	//AHRS��̬����
}