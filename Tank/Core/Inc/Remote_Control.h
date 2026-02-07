#ifndef _REMOTE_CONTROL_H_
#define _REMOTE_CONTROL_H_

#include "main.h"
#include "Motor_Move.h"
#include "Turret_Move.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int8_t left_x;
    int8_t left_y;
    int8_t right_x;
    int8_t right_y;
} Joystick_t;

extern Joystick_t joystick;

extern uint8_t usart2_rx_buf[];
extern uint8_t usart2_rx_len;
extern uint8_t usart2_rx_byte;
extern uint32_t last_rx_tick;

#define RX_BUF_LEN 64

void Parse_Joystick_Packet(char *buf);
void Tank_Move_Control(void);
void Turret_Control(void);
void Lost_Control_Check(void);

#endif
