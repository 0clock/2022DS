#include "sendmsg.h"
#define DATA_SEND_UART USART_8



uint8 msgs[18] = {0};


/*int main(void)
{
    DisableGlobalIRQ();
    board_init();//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    uart_init (DATA_SEND_UART, 115200, UART8_TX_D16, UART8_RX_D17);           //�����豸��ʼ��
    //����ʹ�õ�������������ģ��Ĵ���
    //���ж������
    EnableGlobalIRQ(0);
    while (1)
    {
        //���ձ������򣬴���ʱ�䣬���꣬�������λ����������

        //������Ŀ����Ϣ
        send_msg(DATA_SEND_UART, 123, 456, 1, 2, CATEGORY_NULL);
        //�������ڰ�����Ϣ
        send_msg(DATA_SEND_UART, 123, 456, 9, 1, CARRY);
        systick_delay_ms(2000);
        //���Ͷ��������Ϣ
        send_msg(DATA_SEND_UART, 123, 456, 1, 2, DOG);
        send_msg(DATA_SEND_UART, 123, 456, 1, 2, HORSE);
        send_msg(DATA_SEND_UART, 234, 567, 3, 4, CAT);
        send_msg(DATA_SEND_UART, 123, 456, 5, 6, CATTLE);
        send_msg(DATA_SEND_UART, 234, 567, 7, 8, PIG);
        systick_delay_ms(2000);
        //����ˮ�������Ϣ
        send_msg(DATA_SEND_UART, 123, 456, 9, 1, ORANGE);
        send_msg(DATA_SEND_UART, 123, 456, 1, 2, APPLE);
        send_msg(DATA_SEND_UART, 234, 567, 3, 4, DURIAN);
        send_msg(DATA_SEND_UART, 123, 456, 5, 6, GRAPE);
        send_msg(DATA_SEND_UART, 234, 567, 7, 8, BANANA);
        systick_delay_ms(2000);
        //���ͽ�ͨ���������Ϣ
        send_msg(DATA_SEND_UART, 123, 456, 9, 1, TRAINS);
        send_msg(DATA_SEND_UART, 123, 456, 1, 2, STEAMSHIP);
        send_msg(DATA_SEND_UART, 234, 567, 3, 4, PLANE);
        send_msg(DATA_SEND_UART, 123, 456, 5, 6, CAR);
        send_msg(DATA_SEND_UART, 234, 567, 7, 8, COACH);
        systick_delay_ms(2000);
    }
}*/

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����Ӿ�������ת��ģ�� ���ͺ���
//  @param      uartn               ����ö��
//  @param      second              ����ʱ�����룩
//  @param      msecond             ����ʱ�������룩
//  @param      pos_x               X����
//  @param      pos_y               Y����
//  @param      cg                  ���
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void send_msg(UARTN_enum uartn, uint16 second, uint16 msecond, uint8 pos_x, uint8 pos_y, category_enum cg)
{
    //ʱ����Ϣ
    msgs[0] = second/100 + '0';
    msgs[1] = second%100/10 + '0';
    msgs[2] = second%10 + '0';
    msgs[3] = '.';
    msgs[4] = msecond/100 + '0';
    msgs[5] = msecond%100/10 + '0';
    msgs[6] = msecond%10 + '0';

    //����X��Ϣ
    msgs[7] = ' ';
    msgs[8] = pos_x/10 + '0';
    msgs[9] = pos_x%10 + '0';

    //����Y��Ϣ
    msgs[10] = ' ';
    msgs[11] = pos_y/10 + '0';
    msgs[12] = pos_y%10 + '0';

    //��� ������Ϣ
    msgs[13] = ' ';
    msgs[14] = (uint8)cg/6 + '0';

    //��� С����Ϣ
    msgs[15] = ' ';
    msgs[16] = (uint8)cg%6 + '0';

    msgs[17] = '\n';
    uart_putbuff(uartn, msgs, 18);
}


