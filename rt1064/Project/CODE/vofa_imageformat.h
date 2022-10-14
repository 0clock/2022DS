enum ImgFormat {
    Format_Invalid,
    Format_Mono,
    Format_MonoLSB,
    Format_Indexed8,
    Format_RGB32,
    Format_ARGB32,
    Format_ARGB32_Premultiplied,
    Format_RGB16,
    Format_ARGB8565_Premultiplied,
    Format_RGB666,
    Format_ARGB6666_Premultiplied,
    Format_RGB555,
    Format_ARGB8555_Premultiplied,
    Format_RGB888,
    Format_RGB444,
    Format_ARGB4444_Premultiplied,
    Format_RGBX8888,
    Format_RGBA8888,
    Format_RGBA8888_Premultiplied,
    Format_BGR30,
    Format_A2BGR30_Premultiplied,
    Format_RGB30,
    Format_A2RGB30_Premultiplied,
    Format_Alpha8,
    Format_Grayscale8,
    
    // ���¸�ʽ����ʱ��IMG_WIDTH��IMG_HEIGHT����Ҫǿ��ָ��������Ϊ-1����
    Format_BMP,
    Format_GIF,
    Format_JPG,
    Format_PNG,
    Format_PBM,
    Format_PGM,
    Format_PPM,
    Format_XBM,
    Format_XPM,
    Format_SVG,
};

//������ʧ��û�б�Ҫ�ýṹ�������ݣ�����̫����
//#define CHANNEL_CNT 10
//typedef struct VOFA_FRAME0{								//��һ�����ݰ�
//		float channel_data[CHANNEL_CNT];			//��ͬͨ��������
//		unsigned char tail[4];								//�������֡β:{0x00, 0x00, 0x80, 0x7f}
//}vofa_JF_CH_frame;												//justfloat��floatͨ��ģʽ��Ӧ������֡����

//typedef struct VOFA_FRAME1{
//		uint32_t preframe[7];											//ͼƬ��ǰ��֡
//		char* image;													//��byte���ķ�ʽ����ͼ��
//}vofa_JF_IMAGE_frame;											//justfloat��floatͨ��ģʽ��Ӧ������֡����

//typedef struct VOFA_FRAME2{
//		float channel_data[CHANNEL_CNT];			//��ͬͨ��������-------?
//		unsigned char tail[4];								//�������֡β:{0x00, 0x00, 0x80, 0x7f}
//}vofa_FW_CH_frame;												//firewater��floatͨ��ģʽ��Ӧ������֡����

//typedef struct VOFA_FRAME3{
//		float channel_data[CHANNEL_CNT];			//��ͬͨ��������-------?
//		unsigned char tail[4];								//�������֡β:{0x00, 0x00, 0x80, 0x7f}
//}vofa_FW_IMAGE_frame;											//firewater��floatͨ��ģʽ��Ӧ������֡����
// 