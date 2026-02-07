#include "main.h"

#ifndef __MOTOR_MECANUM_H
#define __MOTOR_MECANUM_H

#define CCR_MAX (int)(600 * 0.7 )

extern int8_t Motor_Direction[4];  // 1 正转, -1 反转， 0 停止

void Motor_Mecanum_Init(void);

void Motor_Mecanum_LA_Speed(int16_t Compare);
void Motor_Mecanum_LA_Coast(void);
void Motor_Mecanum_LA_Brake(void);

void Motor_Mecanum_LB_Speed(int16_t Compare);
void Motor_Mecanum_LB_Coast(void);
void Motor_Mecanum_LB_Brake(void);

void Motor_Mecanum_RA_Speed(int16_t Compare);
void Motor_Mecanum_RA_Coast(void);
void Motor_Mecanum_RA_Brake(void);

void Motor_Mecanum_RB_Speed(int16_t Compare);
void Motor_Mecanum_RB_Coast(void);
void Motor_Mecanum_RB_Brake(void);

#endif
