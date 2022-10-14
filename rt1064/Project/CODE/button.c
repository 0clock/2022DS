#include "buzzer.h"
#include "button.h"
#include "display.h"
#include "motor.h"
#include "flash_param.h"
#include "ahrs.h"
#include "location.h"
#include "zf_uart.h"
#include "attitude_solution.h"



#define KEY_1   C31	// ���������ϰ�����Ӧ����
#define KEY_2   C27	// ���������ϰ�����Ӧ����
#define KEY_3   C26	// ���������ϰ�����Ӧ����
#define KEY_4   C4	// ���������ϰ�����Ӧ����

enum Config_Action config_action;
extern float pictureP,pictureI,pictureD;

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//�����ź���
rt_sem_t key1_sem;
rt_sem_t key2_sem;
rt_sem_t key3_sem;
rt_sem_t key4_sem;



void button_entry(void *parameter)
{
    //���水��״̬
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
    
    //��ȡ��ǰ����״̬
    key1_status = gpio_get(KEY_1);
    key2_status = gpio_get(KEY_2);
    key3_status = gpio_get(KEY_3);
    key4_status = gpio_get(KEY_4);
    
    //��⵽��������֮�󲢷ſ� �ͷ�һ���ź���
    if(key1_status && !key1_last_status)    
    {
        if(Page_Number==InfoPage){
            speed_tar+=10;//С������
        }
        if(Page_Number==ConfigPage){
            switch (config_action) {
                case MileageX : MileageKx+=0.0002f;break;
                case MileageY : MileageKy+=0.0002f;break;
                case AngelP : Angel_KP+=0.1f;break;
                case AngelI: Angel_KI+=0.1f;break;
                case AngelD:Angel_KD+=0.1f;break;
                case MotorP:Position_KP+=1;break;
                case MotorI:Position_KI+=1;break;
                case MotorD:Position_KD+=1;break;
                default:break;
            }
            flash_param_write();

        }
        if(Page_Number==CameraPage){
            pictureP+=0.001;
            uart_putstr(USART_1, "KEY1");
        }
        rt_sem_release(key1_sem);
        rt_mb_send(buzzer_mailbox, 23);
    }
    if(key2_status && !key2_last_status)    
    {
        if(Page_Number==InfoPage){
            speed_tar=0;//С��ɲ��
        }
        if(Page_Number==ConfigPage){
            switch (config_action) {
                case MileageX : MileageKx-=0.0002f;break;
                case MileageY : MileageKy-=0.0002f;break;
                case AngelP : Angel_KP-=0.1f;break;
                case AngelI: Angel_KI-=0.1f;break;
                case AngelD:Angel_KD-=0.1f;break;
                case MotorP:Position_KP-=1;break;
                case MotorI:Position_KI-=1;break;
                case MotorD:Position_KD-=1;break;
                default:break;
            }
            flash_param_write();
        }
        if(Page_Number==CameraPage){
            pictureP-=0.001;
        }
        rt_sem_release(key2_sem);
        rt_mb_send(buzzer_mailbox, 23);
    }
    if(key3_status && !key3_last_status)    
    {
        if(Page_Number==ConfigPage){
            config_action++;
            if(config_action>7)
                config_action=0;
            Gui_Page_Active=true;
        }
        if(Page_Number==InfoPage){
            speed_tar-=10;
        }
        if(Page_Number==CameraPage){
            pictureD+=0.001;
        }
        rt_sem_release(key3_sem);
        rt_mb_send(buzzer_mailbox, 23);
    }
    if(key4_status && !key4_last_status)    
    {
        if(Page_Number==CameraPage){
                pictureD-=0.001;
            }
        Page_Number++;

        Gui_Page_Active=true;
        if(Page_Number>4)
            Page_Number=0;
        rt_sem_release(key4_sem);
        rt_mb_send(buzzer_mailbox, 23);
    }
}

void button_init(void)
{
    rt_timer_t timer1;
    
    gpio_init(KEY_1, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);			// ��ʼ��ΪGPIO�������� Ĭ�������ߵ�ƽ
	gpio_init(KEY_2, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);
	gpio_init(KEY_3, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);
	gpio_init(KEY_4, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);


    
    key1_sem = rt_sem_create("key1", 0, RT_IPC_FLAG_FIFO);		//�����������ź��������������¾��ͷ��ź���������Ҫʹ�ð����ĵط���ȡ�ź�������
    key2_sem = rt_sem_create("key2", 0, RT_IPC_FLAG_FIFO);  
    key3_sem = rt_sem_create("key3", 0, RT_IPC_FLAG_FIFO);  
    key4_sem = rt_sem_create("key4", 0, RT_IPC_FLAG_FIFO);
    
    timer1 = rt_timer_create("button", button_entry, RT_NULL, 20, RT_TIMER_FLAG_PERIODIC);

    if(RT_NULL != timer1) 
    {
        rt_timer_start(timer1);
    }
}