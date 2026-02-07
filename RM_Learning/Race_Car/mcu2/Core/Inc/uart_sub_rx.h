#ifndef __UART_SUB_RX_H
#define __UART_SUB_RX_H

#include "main.h"

extern uint8_t sub_rxbuf[7];
extern int8_t Motor_Direction_From_Main[4];

void UART_Sub_RxParse(); 

#endif
