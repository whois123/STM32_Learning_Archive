#include "uart_sub_tx.h"
#include "usart.h"
#include "encoder.h"

uint8_t sub_txbuf[11];

void UART_Sub_Send_RealSpeed(void)
{
    sub_txbuf[0] = 0xAA;
    sub_txbuf[1] = 0x55;

    // 将PID输出的 int16_t 转为字节流
    int16_t *speed = (int16_t*)Real_Speed;

    sub_txbuf[2] = speed[0] & 0xFF;
    sub_txbuf[3] = (speed[0] >> 8) & 0xFF;

    sub_txbuf[4] = speed[1] & 0xFF;
    sub_txbuf[5] = (speed[1] >> 8) & 0xFF;

    sub_txbuf[6] = speed[2] & 0xFF;
    sub_txbuf[7] = (speed[2] >> 8) & 0xFF;

    sub_txbuf[8] = speed[3] & 0xFF;
    sub_txbuf[9] = (speed[3] >> 8) & 0xFF;

    // 校验
    uint8_t sum = 0;
    for (int i = 2; i <= 9; i++)
        sum += sub_txbuf[i];
    sub_txbuf[10] = sum;

    HAL_UART_Transmit_DMA(&huart1, sub_txbuf, 11);
}
