#ifndef __TURRET_MOVE_H__
#define __TURRET_MOVE_H__ 

#include "tim.h"
#include "gpio.h"
#include "Motor_Move.h"

extern uint8_t current_yaw_angle;

#define SERVO_MIN_PULSE  500
#define SERVO_MAX_PULSE  2500

#define MOTOR_PITCH_PWM_MAX 2000

void Motor_Pitch_Init(void);
void Servo_Init(void);
void Turret_Init(void);
void Servo_SetAngle(uint8_t angle);
void Turret_Yaw(uint8_t direction_flag);
void Turret_Yaw_Control(int16_t dir);
void Turret_Pitch_Left(void);
void Turret_Pitch_Right(void);
void Turret_Pitch_Control(int16_t dir);

#endif
