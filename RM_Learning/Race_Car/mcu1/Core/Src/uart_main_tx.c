#include "uart_main_tx.h"
#include "motor_mecanum.h"
#include "usart.h"

uint8_t main_txbuf[7];

void UART_Main_SendDirection(void)
{
    main_txbuf[0] = 0xAA;
    main_txbuf[1] = 0x55;

    main_txbuf[2] = Motor_Direction[0];
    main_txbuf[3] = Motor_Direction[1];
    main_txbuf[4] = Motor_Direction[2];
    main_txbuf[5] = Motor_Direction[3];

    main_txbuf[6] = main_txbuf[2] + main_txbuf[3] + main_txbuf[4] + main_txbuf[5];

    HAL_UART_Transmit_DMA(&huart3, main_txbuf, 7);

    // HAL_Delay(1000);

    // char ack_msg[50];
    // sprintf(ack_msg, "Direction Updated: %d,%d,%d,%d\r\n", 
    //         Motor_Direction[0], Motor_Direction[1],
    //         Motor_Direction[2], Motor_Direction[3]);
    // HAL_UART_Transmit(&huart3, (uint8_t*)ack_msg, strlen(ack_msg), 100);
}
