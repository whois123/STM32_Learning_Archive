#include "uart_sub_rx.h"
#include "usart.h"
#include <string.h>

uint8_t sub_rxbuf[7]; 
int8_t Motor_Direction_From_Main[4] = {1,1,1,1};

void UART_Sub_RxInit(void)
{
    HAL_UART_Receive_DMA(&huart1, sub_rxbuf, 7);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
}

void UART_Sub_RxParse(){
    uint8_t sub_rxbuf_temp[7];

    for(int i = 0; i < 7; i++)
    {
        if(sub_rxbuf[i] == 0xAA && sub_rxbuf[i+1] == 0x55)
        {
            memcpy(sub_rxbuf_temp, sub_rxbuf, 7);
            for(int k = 0; k < i; k++)
            {
                int temp = sub_rxbuf_temp[0];
                for(int j = 1; j < 7; j++)
                {
                    sub_rxbuf_temp[j-1] = sub_rxbuf_temp[j];
                }
                sub_rxbuf_temp[6] = temp;
            }
        }

            int8_t sum = sub_rxbuf_temp[2] + sub_rxbuf_temp[3] + sub_rxbuf_temp[4] + sub_rxbuf_temp[5];
            if(sum == sub_rxbuf_temp[6])
            {
                Motor_Direction_From_Main[0] = sub_rxbuf_temp[2];
                Motor_Direction_From_Main[1] = sub_rxbuf_temp[3];
                Motor_Direction_From_Main[2] = sub_rxbuf_temp[4];
                Motor_Direction_From_Main[3] = sub_rxbuf_temp[5];
        }
    }
}
