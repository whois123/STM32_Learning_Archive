#ifndef _MOTOR_MOVE_H_
#define _MOTOR_MOVE_H_

#include "tim.h"
#include "gpio.h"

#define MOTOR_PWM_MAX 6500

void Motor_Move_Init(void);

void Left_Motor_Dir_Forward(void);
void Left_Motor_Dir_Backward(void);
void Left_Motor_Brake(void);
void Right_Motor_Dir_Forward(void);
void Right_Motor_Dir_Backward(void);
void Right_Motor_Brake(void);

void Motor_Left_SetSpeed(int16_t speed);
void Motor_Right_SetSpeed(int16_t speed);

#endif
