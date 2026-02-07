#include "uart_main_rx.h"
#include "usart.h"
#include <string.h>

uint8_t main_rxbuf[11];
int16_t Real_Speed_From_Sub[4] = {0};

void UART_Main_RxInit(void)
{
    HAL_UART_Receive_DMA(&huart3, main_rxbuf, 11);
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
}

void UART_Main_RxPrase(void)
{
    uint8_t main_rxbuf_temp[11];

    for(int i = 0; i < 11; i++)
    {
        if(main_rxbuf[i] == 0xAA && main_rxbuf[i+1] == 0x55)
        {
            memcpy(main_rxbuf_temp, main_rxbuf, 11);
            for(int k = 0; k < i; k++){
                int temp = main_rxbuf_temp[0];
                for (int j = 1; j < 11; j++){
                    main_rxbuf_temp[j-1] = main_rxbuf_temp[j];
                }
                main_rxbuf_temp[10] = temp;
            }

            uint8_t sum = main_rxbuf_temp[2] + main_rxbuf_temp[3] + main_rxbuf_temp[4] + main_rxbuf_temp[5] + main_rxbuf_temp[6] + main_rxbuf_temp[7] + main_rxbuf_temp[8] + main_rxbuf_temp[9];
            if(sum == main_rxbuf_temp[10])
            {
                Real_Speed_From_Sub[0] = (int16_t)((main_rxbuf_temp[3] << 8) | main_rxbuf_temp[2]);
                Real_Speed_From_Sub[1] = (int16_t)((main_rxbuf_temp[5] << 8) | main_rxbuf_temp[4]);
                Real_Speed_From_Sub[2] = (int16_t)((main_rxbuf_temp[7] << 8) | main_rxbuf_temp[6]);
                Real_Speed_From_Sub[3] = (int16_t)((main_rxbuf_temp[9] << 8) | main_rxbuf_temp[8]);
            }
        }
    }
}


// void Buff_Process(){
//     int buff[5] = {1,2,3,4,5};
//     int temp = buff[0];
//     for(int i = 1; i < 5; i++){
//         buff[i-1] = buff[i];
//     }
//     buff[4] = temp; 
// }