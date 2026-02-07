#ifndef __MOTOR_SHOOT_H
#define __MOTOR_SHOOT_H

#include "main.h"
#include "tim.h"
#include "remote_control.h"

#define speed_max ((int)(0.2f * 20000))
#define speed_min ((int)(0.1f * 20000))

void Motor_Shoot_Control_Init(void);
void Motor_Shoot_Set_Speed(uint16_t speed_level);
void Motor_Shoot_Control_Update(RC_Type *rc);

#endif
