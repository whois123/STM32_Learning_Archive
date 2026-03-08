#ifndef __FEEDFORWARD_H
#define __FEEDFORWARD_H

#include "stm32f1xx_hal.h"

/* 前馈控制器结构体 */
typedef struct
{
    float Kv;           // 速度前馈系数
    float Ka;           // 加速度前馈系数
    
    float last_ref;     // 上一次的目标速度 (用于差分计算加速度)
    float dt;           // 控制周期 (单位: s)
    
    float out_v;        // 速度前馈输出分量
    float out_a;        // 加速度前馈输出分量
    float out_total;    // 总前馈输出
    
    float max_out;      // 输出限幅
} Feedforward_t;

void FF_Init(Feedforward_t *ff, float Kv, float Ka, float dt, float max_out);
float FF_Calculate(Feedforward_t *ff, float ref_speed, float ref_accel_feed);
void FF_Clear(Feedforward_t *ff);

#endif /* __FEEDFORWARD_H */