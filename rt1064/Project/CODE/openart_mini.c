#include "openart_mini.h"
#include "location.h"
#include "buzzer.h"



int32 picture_location[2]={0};

uint8               openart_rx_buffer;
lpuart_transfer_t   openart_receivexfer;
lpuart_handle_t     openart_g_lpuartHandle;

uint8               openart1_rx_buffer;
lpuart_transfer_t   openart1_receivexfer;
lpuart_handle_t     openart1_g_lpuartHandle;

uint8 openartBuffer=0;

enum picture_type picture_type;
enum picture_big_type pictureBigType=animal;
enum openart_mode openartMode=get_map;
enum receve_model receve_Model=road_loaction;
bool havePicture;
bool isDetection=false;
uint8 nowpointmp=0;
uint8 edge_rotation[2]={0};
int road_location=0;
uint8 t_location=0;

bool findT=false;




void openart_uart1_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    static int rx_num = 0;
    static bool isgetmap=false,finshgetmap=false;
    if(kStatus_LPUART_RxIdle == status) {
        if(openart_rx_buffer==0xFF) {
            rx_num = 0;
            receve_Model=road_loaction;
            rx_num++;
        }else if(openart_rx_buffer==0xDD){
            rx_num = 0;
            receve_Model=isfindT;
           findT=true;
           rx_num++;
        }else if(openart_rx_buffer==0xEE){
            rx_num = 0;
            t_location=0;
            findT=false;
        }

        if(receve_Model==road_loaction&&rx_num>1){
            road_location=openart_rx_buffer;
            if(road_location<0){
                road_location=-road_loaction;
            }
        }else if(receve_Model==findT&&rx_num>1){
            t_location=openart_rx_buffer;
        }
        rx_num+=1;
    }

    handle->rxDataSize = openart_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = openart_receivexfer.data;          //还原缓冲区地址
}

void openart1_uart1_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    static int rx_num = 0;
    if(kStatus_LPUART_RxIdle == status)
    {
        if(openart1_rx_buffer==0xFF){
            rx_num=0;
            isDetection=true;
        }else {
            if (isDetection) {
                picture_type =openart1_rx_buffer;
                switch (picture_type) {
                    case apple:
                    case banana:
                    case durian:
                    case grape:
                    case orange:
                        pictureBigType=fruit;
                        break;
                    case cat:
                    case cow:
                    case dog:
                    case horse:
                    case pig:
                        pictureBigType=animal;
                        break;
                    case bus:
                    case car:
                    case plane:
                    case ship:
                    case trains:
                        pictureBigType=vehicle;
                        break;
                    default:break;
                }
            }else{
                picture_type=0;
                pictureBigType=animal;
            }
        }
    }
    handle->rxDataSize = openart1_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = openart1_receivexfer.data;          //还原缓冲区地址
}


void openart_mini(void)
{
    uart_init(USART_8, 115200, UART8_TX_D16, UART8_RX_D17);


    //配置串口接收的缓冲区及缓冲区长度
    openart_receivexfer.dataSize = 1;
    openart_receivexfer.data = &openart_rx_buffer;




    //设置中断函数及其参数
    uart_set_handle(USART_8, &openart_g_lpuartHandle, openart_uart1_callback, NULL, 0, openart_receivexfer.data, 1);
    //uart_set_handle(USART_1, &csi_g_lpuartHandle, uart1_call_back, NULL, 0, buff, 1);
    NVIC_SetPriority(LPUART8_IRQn, 0);         //设置串口中断优先级 范围0-15 越小优先级越高
    uart_rx_irq(USART_8, 1);
    /*
     *
     uart_init(USART_4, 115200, UART4_TX_C16, UART4_RX_C17);

    //配置串口接收的缓冲区及缓冲区长度
    openart_receivexfer.dataSize = 1;
    openart_receivexfer.data = &openart_rx_buffer;

    //设置中断函数及其参数
    uart_set_handle(USART_4, &openart_g_lpuartHandle, openart_uart1_callback, NULL, 0, openart_receivexfer.data, 1);

    NVIC_SetPriority(LPUART4_IRQn, 14);         //设置串口中断优先级 范围0-15 越小优先级越高
    uart_rx_irq(USART_4, 1);
     * */

}