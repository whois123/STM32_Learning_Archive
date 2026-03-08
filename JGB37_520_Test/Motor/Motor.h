#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f1xx_hal.h"

typedef struct
{
    TIM_HandleTypeDef *htim_pwm;
    uint32_t pwm_channel;

    TIM_HandleTypeDef *htim_encoder;

    /* 改名，避免宏污染 */
    GPIO_TypeDef *gpio_in1_port;
    uint16_t      gpio_in1_pin;

    GPIO_TypeDef *gpio_in2_port;
    uint16_t      gpio_in2_pin;

    float gear_ratio;
    float encoder_ppr;

    int32_t last_count;
    int32_t total_count;

    float speed_rpm;
    float angle_deg;

} Motor_t;

void Motor_Init(Motor_t *motor);
void Motor_Set(Motor_t *motor, int16_t pwm);
void Motor_Update(Motor_t *motor, float dt);
float Motor_GetSpeed(Motor_t *motor);
float Motor_GetAngle(Motor_t *motor);

#endif