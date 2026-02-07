#ifndef __PID_H
#define __PID_H

#include "main.h"

extern double PID_Pwm_Buff[4];
extern float Speed_Proportion;

int16_t Speed_PID(int index, double TargetSpeed,int Motor_Direction);

#endif
