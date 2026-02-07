#include "main.h"
#include "tim.h"
#include "remote_control.h"

#ifndef SERVO_H
#define SERVO_H

#define SERVO_MIN_PULSE  500
#define SERVO_MAX_PULSE  2500

void Servo_Init(void);
void Servo_SetAngle(uint8_t angle);
void Servo_Control_Update(RC_Type *rc);

#endif
