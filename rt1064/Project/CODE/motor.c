#include "motor.h"
#include "encoder.h"
#include "flash_param.h"

#define DIR_1 D1
#define DIR_2 D0
#define PWM_LIMIT 25000
#define PWM_1 PWM2_MODULE3_CHB_D3
#define PWM_2 PWM2_MODULE3_CHA_D2

int32 duty1=0,duty2=0;//���PWMֵ


float pictureP=7,pictureI=0,pictureD=-1;


float ypictureP=0.07,ypictureI=0,ypictureD=0;

//���ַ�����λ�Ʋ���

//���Ŀ���ٶ�
int speed_tar_1 = 0;
int speed_tar_2 = 0;

double speed_tar = 0;//Ŀ���ٶ�


void motor_init(void)
{
    gpio_init(DIR_1, GPO, 0, GPIO_PIN_CONFIG); 		//��Ƭ���˿�D0 ��ʼ��DIR_1			GPIO
    pwm_init(PWM_1, 17000, 0);      					//��Ƭ���˿�D2 ��ʼ��PWM_1����10K ռ�ձ�0
    gpio_init(DIR_2, GPO, 0, GPIO_PIN_CONFIG);       //��Ƭ���˿�D1 ��ʼ��DIR_2          GPIO
    pwm_init(PWM_2, 17000, 0);                          //��Ƭ���˿�D3 ��ʼ��PWM_2����10K ռ�ձ�0											// PWM ͨ��4 ��ʼ��Ƶ��10KHz ռ�ձȳ�ʼΪ0
}

void car_go(int left,int right){
    speed_tar_1=left;
    speed_tar_2=right;
}


void car_stop(){
    speed_tar_1 = 0;
    speed_tar_2 = 0;
}

/**
 * @name: position_pid
 * @msg: λ��ʽpid
 * @param {int Encoder,int Target}
 * @return {int pwm}
 */
int position_pid1(int Encoder,int Target){
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=(float)(Target - Encoder);//��ǰ���
    Integral_bias+=Bias;//���Ļ���
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);//��ǰ���-�ϴ����
    Last_Bias=Bias;
    return (int)Pwm;
}

int position_pid2(int Encoder,int Target){
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=(float)(Target - Encoder);
    Integral_bias+=Bias;
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);
    Last_Bias=Bias;
    return (int)Pwm;
}

int position_pid3(int Encoder,int Target){
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=(float)(Target - Encoder);
    Integral_bias+=Bias;
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);
    Last_Bias=Bias;
    return (int)Pwm;
}


int position_pid4(int Encoder,int Target){
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=(float)(Target - Encoder);
    Integral_bias+=Bias;
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);
    Last_Bias=Bias;
    return (int)Pwm;
}

int angel_pid(int NowAngel,int TargetAngel){
    if (NowAngel<=0){
        if(NowAngel-TargetAngel<=-180){
            NowAngel+=180;
            TargetAngel-=180;
        }
    }else if(NowAngel>0){
        if(NowAngel-TargetAngel>=180){
            NowAngel-=180;
            TargetAngel+=180;
        }
    }
    static float Bias,Speed_Z,Integral_bias,Last_Bias;
    Bias=(float)(TargetAngel - NowAngel);
    Integral_bias+=Bias;
    Speed_Z=Angel_KP*Bias+Angel_KI*Integral_bias+Angel_KD*(Bias-Last_Bias);
    Last_Bias=Bias;
    if(Speed_Z>=10)
        Speed_Z=10;
    if(Speed_Z<=-10)
        Speed_Z=-10;
    return (int)Speed_Z;
}

int picture_xerror_pid(int16 now_x,int16 target_x){
    static float Bias,Speed_X,Integral_bias,Last_Bias;
    Bias=(float)(target_x - now_x);
    Integral_bias+=Bias;
    Speed_X=-pictureP*Bias+pictureI*Integral_bias+pictureD*(Bias-Last_Bias);
    Last_Bias=Bias;
    if(Speed_X>=400)
        Speed_X=400;
    if(Speed_X<=-400)
        Speed_X=-400;
    return (int)Speed_X;
}

int picture_yerror_pid(int16 now_y,int16 target_y){
    static float Bias,Speed_Y,Integral_bias,Last_Bias;
    Bias=(float)(target_y - now_y);
    Integral_bias+=Bias;
    Speed_Y=ypictureP*Bias+ypictureI*Integral_bias+ypictureD*(Bias-Last_Bias);
    Last_Bias=Bias;
    if(Speed_Y>=5)
        Speed_Y=5;
    if(Speed_Y<=-5)
        Speed_Y=-5;
    return (int)Speed_Y;
}

/**
 * @name: limit_pwm
 * @msg: pwm�޷�
 * @param {int pwm}
 * @return {int pwm}
 */

int limit_pwm(int pwm){
    if (pwm>=0)
    {
        if (pwm>=PWM_LIMIT)
        {
            pwm = PWM_LIMIT;
        }

    }
    else if (pwm<=0)
    {
        if (pwm<-PWM_LIMIT)
        {
            pwm = -PWM_LIMIT;
        }
    }
    return pwm;
}


/**
 * @name: PID_Calculate
 * @msg: ���ø������ӵ�pid�������ó�������PWMֵ
 * @param {void}
 * @return {void}
 */

void pid_calculate(void){
    duty1 = position_pid1(RC_encoder1,speed_tar_1);
    duty2 = position_pid2(RC_encoder2,speed_tar_2);

    duty1 = limit_pwm(duty1);
    duty2 = limit_pwm(duty2);
}


void motor_control(bool run)
{
    if(run) {
        pid_calculate();
    }else{
        duty1 = 0;
        duty2 = 0;
    }

    if(duty1>=0){
        gpio_set(DIR_1,0);
        pwm_duty(PWM_1,duty1);
    } else {
        gpio_set(DIR_1,1);
        pwm_duty(PWM_1,-duty1);
    }
    if(duty2>=0){
        gpio_set(DIR_2,1);
        pwm_duty(PWM_2,duty2);
    } else {
        gpio_set(DIR_2,0);
        pwm_duty(PWM_2,-duty2);
    }

}

