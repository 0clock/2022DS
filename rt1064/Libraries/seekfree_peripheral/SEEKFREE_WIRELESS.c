/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		��ɿƼ�����ת����ģ��
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-03-27
 * @note		
					���߶��壺
					------------------------------------ 
					    ����ת����       ��Ƭ��                        
    					RX              �鿴SEEKFREE_WIRELESS.h�ļ��е�WIRELESS_UART_TX�궨��
    					TX              �鿴SEEKFREE_WIRELESS.h�ļ��е�WIRELESS_UART_RX�궨��
    					RTS             �鿴SEEKFREE_WIRELESS.h�ļ��е�RTS_PIN�궨��
    					CMD             ���ջ�������
					------------------------------------ 
 ********************************************************************************************************************/

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "zf_systick.h"
#include "zf_gpio.h"
#include "zf_iomuxc.h"
#include "zf_uart.h"
#include "SEEKFREE_WIRELESS.h"





uint8               wireless_rx_buffer;
lpuart_transfer_t   wireless_receivexfer;
lpuart_handle_t     wireless_g_lpuartHandle;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� �����жϺ���
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       �ú�����ISR�ļ� ����8�жϳ��򱻵���
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        //�ӵ�һ���ֽں�Ƭ��������봮���жϣ�ͨ���ڴ˴���ȡwireless_rx_buffer����ȡ������
        
        
    }
    handle->rxDataSize = wireless_receivexfer.dataSize;  //��ԭ����������
    handle->rxData = wireless_receivexfer.data;          //��ԭ��������ַ
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ���ʼ��
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void seekfree_wireless_init(void)
{
    //������ʹ�õĲ�����Ϊ115200��Ϊ����ת����ģ���Ĭ�ϲ����ʣ�������������������������ģ�鲢�޸Ĵ��ڵĲ�����
    gpio_init(RTS_PIN,GPI,0,GPIO_PIN_CONFIG);//��ʼ����������
    
    uart_init (WIRELESS_UART, WIRELESS_UART_BAUD,WIRELESS_UART_TX,WIRELESS_UART_RX);	//��ʼ������    
    uart_rx_irq(WIRELESS_UART,1);
    //���ô��ڽ��յĻ�����������������
    wireless_receivexfer.dataSize = 1;
    wireless_receivexfer.data = &wireless_rx_buffer;
    
    uart_set_handle(WIRELESS_UART, &wireless_g_lpuartHandle, wireless_uart_callback, NULL, 0, wireless_receivexfer.data, 1);
    //NVIC_SetPriority((IRQn_Type)((IRQn_Type)(WIRELESS_UART) + LPUART1_IRQn),0);  //�����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
    //EnableGlobalIRQ(0);
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� ���ͺ���
//  @param      buff        ��Ҫ���͵����ݵ�ַ
//  @param      len         ���ͳ���
//  @return     uint32      ʣ��δ���͵��ֽ���   
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
uint32 seekfree_wireless_send_buff(uint8 *buff, uint32 len)
{
    while(len>30)
    {
        if(gpio_get(RTS_PIN))  
        {
            return len;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
        }
        //while(gpio_get(RTS_PIN));  //���RTSΪ�͵�ƽ���������������
        uart_putbuff(WIRELESS_UART,buff,30);

        buff += 30; //��ַƫ��
        len -= 30;//����
    }
    
    if(gpio_get(RTS_PIN))  
    {
        return len;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
    }
    //while(gpio_get(RTS_PIN));  //���RTSΪ�͵�ƽ���������������
    uart_putbuff(WIRELESS_UART,buff,len);//������������
    
    return 0;
}