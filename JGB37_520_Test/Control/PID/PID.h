#ifndef __PID_H
#define __PID_H

#include "stm32f1xx_hal.h"
#include <math.h>

typedef float fp32;

/* PIDģʽ */
#define PID_POSITION 0
#define PID_DELTA    1

typedef struct PidTypeDef
{
    float Dead_Zone;
    uint8_t mode;

    float Kp;
    float Ki;
    float Kd;

    float max_out;
    float max_iout;

    float set;
    float fdb;

    float out;
    float Pout;
    float Iout;
    float Dout;

    float Dbuf[3];
    float error[3];

    int angle_max;
    int angle_min;

    float I_Separation;
    float gama;

    float lastdout;
    float lastout;

    void (*f_param_init)(
        struct PidTypeDef* pid,
        uint8_t mode,
        const float PID[3],
        float max_out,
        float max_iout,
        float I_Separation,
        float Dead_Zone,
        float gama,
        int angle_max,
        int angle_min);

    fp32 (*f_cal_pid)(
        struct PidTypeDef* pid,
        const fp32 ref,
        const fp32 set);

    void (*f_reset_pid)(struct PidTypeDef* pid, fp32 PID[3]);
    void (*f_clear_pid)(struct PidTypeDef* pid);

} PidTypeDef;

void pid_init(PidTypeDef *pid);

#endif