#include "main.h"
#include "tim.h"
#include "remote_control.h"

#ifndef __MOTOR_PICK_H
#define __MOTOR_PICK_H

#define speed_save ((int)(0.8f * 20000))

#define motor_high_speed_max ((int)(0.3f * 20000))
#define motor_high_speed_min ((int)(0.2f * 20000))

#define motor_low_speed_max ((int)(0.3f * 20000))
#define motor_low_speed_min ((int)(0.1f * 20000))

void Motor_Pick_Control_Init(void);
void Motor_Pick_High_Set_Speed(uint16_t speed);
void Motor_Pick_Low_Set_Speed(uint16_t speed);
void Motor_Pick_Control_Update(RC_Type *rc);

#endif
