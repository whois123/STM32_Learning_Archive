#ifndef __UART_MAIN_RX_H
#define __UART_MAIN_RX_H

#include "main.h"

extern uint8_t main_rxbuf[11];
extern int16_t Real_Speed_From_Sub[4];

void UART_Main_RxInit(void);
void UART_Main_RxParse(void);

#endif
