#include "vofa.h"	//vofa��λ���ӿ�
#include "encoder.h"

//Vofaר�û�����
float vofa_ch_data[ch_sz]    = {1.2,2.4,3.6,4.8};  //������ͨ������		
uint8_t vofa_image[image_sz]  = {0};	 						 //������ͼ������
uint8_t custom_buf[custom_sz]  = {0};    				   //��λ������״̬���ݻ�����
uint8_t cmd_rxbuf[cmd_sz] = {0};  					 		   //��λ�������������


//����ʶ��������λ��
void send_result(){

}
void vofa_Send(){
    //VOFA_pt->sendzip(VOFA_pt,VOFA_PROTOCOL_JUSTFLOAT,VOFA_CH_FRAME);
    //VOFA_pt->sendzip(VOFA_pt,VOFA_PROTOCOL_JUSTFLOAT,VOFA_CH_FRAME);
     //myprintf("%f,%f,%f\n",Angel_x,Angel_y,Angel_z);
    myprintf("%d,%d,%d,%d,%d\n",RC_encoder1,RC_encoder2,speed_tar);
//    vofa_ch_data[0]=RC_encoder1;
//    vofa_ch_data[1]=RC_encoder2;
//    vofa_ch_data[2]=RC_encoder3;
//    vofa_ch_data[3]=RC_encoder4;
//    vofa_ch_data[4]=icm_data.gyro_x;
}

/**********************************************************************
 *	@fcn	��ʼ��VOFAЭ������ͷ�VOFA����ռ�õ���Դ
 *	@para vofa_pt:vofa����
 *	 			ch_data_pt:ͨ�������ݻ�����
 **********************************************************************/ 	
//��ʼ�� 
VOFA* vofa_create(void)
{
		//����VOFA����
		VOFA* vofa_pt = (VOFA*)malloc(sizeof(VOFA));
		//����ͨ��������������ͬ��Ķ���
		return vofa_pt;
}

VOFA_STATE vofa_init(VOFA* vofa_pt,
											void* 	 ch_data_pt	  	,uint32_t ch_size,\
											uint8_t* image_pt  	  	,uint32_t image_size,\
											uint8_t* custom_buf_pt  ,uint32_t custom_size,\
											uint8_t* cmd_rxbuf_pt   ,uint32_t cmd_size,\
											uint8_t  VOFA_UART 		  ,uint8_t  BLE_UART,uint8_t SCOPE_UART)
{
		//vofa���ݻ�����
			//1.��ͨ���ݻ��������(��Ҫ���ڰ���λ�������ݷ��͵���λ��)
		vofa_pt->ch_data_pt = ch_data_pt;
		vofa_pt->ch_size 	  = ch_size;
			//2.ͼ�����ݻ��������
		vofa_pt->image_pt   = image_pt;		
		vofa_pt->image_size = image_size;
			//3.�Զ��������ݻ��������
		vofa_pt->custom_buf_pt  = custom_buf_pt;		
		vofa_pt->custom_buf_size = custom_size;
			//4.����ָ�������ݻ��������(��Ҫ���ڽ�����λ���Ŀ���ָ��)
		vofa_pt->cmd_rxbuf  = cmd_rxbuf_pt;
		vofa_pt->cmd_size		= cmd_size;
		
		//����ʵ�ֶ˿�		
			//1.vofa��λ���Ķ˿�
		vofa_pt->VOFA_UART  = VOFA_UART;
			//2.�����������Ķ˿�
		vofa_pt->BLE_UART   = BLE_UART;
			//3.����ʾ�����Ķ˿�
		vofa_pt->SCOPE_UART = SCOPE_UART;
		
		//Э��涨����������
			//1.JF��FWͨ�õ�ͼ������ǰ��֡(�û��ɵ���image_property_set��vofa_preframe�����ǰ5��Ԫ�أ���ЩԪ����������������ͼƬ����Ϣ)
		vofa_pt->vofa_preframe[5] = 0x7F800000;
		vofa_pt->vofa_preframe[6] = 0x7F800000;   
			//2.JFͨ�������ݵĹ̶�֡β
		vofa_pt->vofa_JF_tail[0] = 0x00;
		vofa_pt->vofa_JF_tail[1] = 0x00;
		vofa_pt->vofa_JF_tail[2] = 0x80;
		vofa_pt->vofa_JF_tail[3] = 0x7F;
		
		//vofa��������ķ���	
		vofa_pt->vofa_release  = vofa_release;
		vofa_pt->sendzip = vofa_sendzip;
		vofa_pt->unzip 	 = vofa_unzip;
		vofa_pt->image_property_set = image_property_set;
		vofa_pt->image_property_get = image_property_get;
		return VOFA_OK;
}

//����ʼ��
VOFA_STATE vofa_release(VOFA* vofa_pt)
{
		if(!vofa_pt)	free(vofa_pt);
		else	return VOFA_ERR;
		return VOFA_OK;
}



/**********************************************************************
 *	@fcn	���ݷ��ͺ���(˽�к���)
 *	@para vofa_pt:vofa����
 * 				vofa_frame:�����������֡
 **********************************************************************/ 		
//��������֡ͷ��֡β���������֣�
static VOFA_STATE vofa_transmit_leader(VOFA* vofa_pt,uint8_t vofa_frame_leader)
{		
		if(vofa_pt == NULL)	return VOFA_ERR;
	
		if(vofa_frame_leader == JF_TAIL)
		{		
				//����λ������JFͨ�������ݵ�֡β��4byte
				uart_putbuff(vofa_pt->VOFA_UART,vofa_pt->vofa_JF_tail,4);									
				return VOFA_OK;
		}
		
		else if(vofa_frame_leader == JF_PREFRAME)
		{			
				//����λ������JFͼ��ǰ��֡��28byte
				uart_putbuff(vofa_pt->VOFA_UART,(uint8_t*)(vofa_pt->vofa_preframe),28);		
				return VOFA_OK;
		}
		
		return VOFA_ERR;
}


//�����û�����
static VOFA_STATE vofa_transmit(VOFA* vofa_pt,uint8_t vofa_frame_category)
{
		if(vofa_pt == NULL)	return VOFA_ERR;
	
		if(vofa_frame_category == VOFA_CH_FRAME)
		{	
				uart_putbuff(vofa_pt->VOFA_UART,(uint8_t*)(vofa_pt->ch_data_pt),vofa_pt->ch_size);
				return VOFA_OK;
		}

		else if(vofa_frame_category == VOFA_IMAGE_FRAME)
		{
				uart_putbuff(vofa_pt->VOFA_UART,(uint8_t*)(vofa_pt->image_pt),vofa_pt->vofa_preframe[2]);
				return VOFA_OK;
		}
		
//		else if(vofa_frame_category == VOFA_RAMDOM_FRAME)	
//		{
//				uart_putbuff(vofa_pt->VOFA_UART,(uint8_t*)(vofa_pt->image_pt),vofa_pt->vofa_preframe[2]);
//				return VOFA_OK;
//		}
		
		return VOFA_ERR;
}



/**********************************************************************
 *	@fcn	���ݴ�����û�ָ�������Ͳ�����
 *	@para vofa_pt:VOFA����;
 *				vofa_protocal:���ݴ���Э��
 *				vofa_frame_category:���������ݵ�����
 *				rawdataΪԭʼ����
 **********************************************************************/ 	
//��λ�����ݴ��
VOFA_STATE vofa_sendzip(VOFA* vofa_pt,uint8_t vofa_protocol,uint8_t vofa_frame_category)
{
		
		if(vofa_pt == NULL)	return VOFA_ERR;

		//JFЭ��//
		if(vofa_protocol == VOFA_PROTOCOL_JUSTFLOAT)
		{
				if(vofa_frame_category == VOFA_CH_FRAME)				//С����ͨ��ģʽ
				{
						if(vofa_transmit(vofa_pt,VOFA_CH_FRAME))		//�����û�����(ͨ������)
						{
								vofa_transmit_leader(vofa_pt,JF_TAIL);	//����֡β
								return VOFA_OK;
						}
						else return VOFA_ERR;
				}
				
				else if(vofa_frame_category == VOFA_IMAGE_FRAME)//ͼ��ģʽ							
				{
						vofa_transmit_leader(vofa_pt,JF_PREFRAME);	//����ǰ��֡
						if(vofa_transmit(vofa_pt,VOFA_IMAGE_FRAME)) //�����û����ݣ�ͼ�����ͣ�
						{
								return VOFA_OK;
						}
				}
		}
		
		//FWЭ��//
		else if(vofa_protocol == VOFA_PROTOCOL_FIREWATER)
		{
				if(vofa_frame_category == VOFA_CH_FRAME)
				{
						uint32_t ch_size = vofa_pt->ch_size/sizeof(float);
						uint8_t i = 0;
						for(;i < ch_size;i++)
						{
								myprintf("%f",((float*)(vofa_pt->ch_data_pt))[i]);//С����ͨ��ģʽ����ǰ��֡��
								if(i < ch_size-1)
								{
										myprintf(",");
								}	
						}							
						myprintf("\n");																  //���з���FWЭ���֡β��
						return VOFA_OK;
				}
		}
		
		//RWЭ��//
//		else if(vofa_protocol == VOFA_PROTOCOL_RAWDATA)
//		{
//				vofa_transmit(vofa_pt,VOFA_RAMDOM_FRAME);
//		}
		
		//�ֻ�����������Э��(v1.0)
		//��ע����λ��Э�������byte���͵ı�����Ҳ����˵��ʹ��ǰ��Ҫ��float_to_byte֮��Ĳ���(��fast_algorithm��)
		else if(vofa_protocol == EXT_PROTOCOL_BLEDEBUGGER)
		{
				uint16_t checksum = 0; 					
				uart_putchar(vofa_pt->BLE_UART,0xA5); //����֡ͷ	
				uart_putbuff(vofa_pt->BLE_UART,custom_buf,sizeof(custom_buf));	//�����û�����				
        for (int i = 1;i < sizeof(custom_buf)-2;i++)
        { 
            checksum += custom_buf[i];
        }
				uart_putchar(vofa_pt->BLE_UART,(uint8_t)(checksum&0xff));		//����У��λ(ps.ǿ��ת����������λ)	
        uart_putchar(vofa_pt->BLE_UART,0x5A); //����֡β
				return VOFA_OK;
		}  
		
		//��������ʾ����Э��(v1.0)
		//��ע����Э�������byte���͵ı�����Ҳ����˵��ʹ��ǰ��Ҫ��float_to_byte֮��Ĳ���(��fast_algorithm��)
		else if(vofa_protocol == EXT_PROTOCOL_DATASCOPE)
		{
				uart_putchar(vofa_pt->SCOPE_UART,'$');//����֡ͷ	
				uart_putbuff(vofa_pt->SCOPE_UART,custom_buf,28);//����7��ͨ�������ݣ�Ҫ����λ�����͵���������Ϊfloat��
				return VOFA_OK;
		}	
		
		return VOFA_ERR;
}



//��λ�����ݽ��(Ŀǰ����һ������)
VOFA_STATE vofa_unzip(VOFA* vofa_pt,uint8_t vofa_protocol,uint8_t msg_catagory)//��δʵ��
{
		//��λ����ָ���б�
		//1.
		
		return VOFA_ERR;
}



/**********************************************************************
 *	@fcn	���á��鿴����ͼƬ���Ժ���
 *	@para vofa_pt:vofa����
 *				other  :ͼ����������
 *	@note ���¸�ʽ����ʱ��IMG_WIDTH��IMG_HEIGHT����Ҫǿ��ָ��������Ϊ-1���ɣ�
 *						Format_BMP,Format_GIF,Format_JPG,Format_PNG,Format_PBM,Format_PGM,
 *						Format_PPM,Format_PNG,Format_XBM,Format_XPM,Format_SVG
 **********************************************************************/ 	
VOFA_STATE image_property_set(VOFA* vofa_pt,uint32_t id,uint32_t size,uint32_t width,uint32_t height,uint32_t format)
{
		if(vofa_pt == NULL)	return VOFA_ERR;
	
		vofa_pt->vofa_preframe[0] = id;
		vofa_pt->vofa_preframe[1] = size;
		vofa_pt->vofa_preframe[2] = width;
		vofa_pt->vofa_preframe[3] = height;
		vofa_pt->vofa_preframe[4] = format;
	
		return VOFA_ERR;
}

VOFA_STATE image_property_get(VOFA* vofa_pt,uint32_t id) //�鿴ĳ��ͼƬͨ������Ϣ(Ŀǰ����ͨ��0)
{
		if(vofa_pt == NULL)	return VOFA_ERR;
		
		if(vofa_pt->vofa_preframe[0] == id)
		{
				myprintf("IMG_ID:%d",vofa_pt->vofa_preframe[0]);
				myprintf("IMG_SIZE:%d",vofa_pt->vofa_preframe[1]);
				myprintf("IMG_WIDTH:%d",vofa_pt->vofa_preframe[2]);
				myprintf("IMG_HEIGHT:%d",vofa_pt->vofa_preframe[3]);
				myprintf("IMG_FORMAT:%d",vofa_pt->vofa_preframe[4]);
				return VOFA_OK;
		}

		return VOFA_ERR;
}



























