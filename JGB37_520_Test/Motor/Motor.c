#include "Motor.h"

void Motor_Init(Motor_t *motor)
{
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->pwm_channel);
    HAL_TIM_Encoder_Start(motor->htim_encoder, TIM_CHANNEL_ALL);

    motor->last_count = __HAL_TIM_GET_COUNTER(motor->htim_encoder);
    motor->total_count = 0;
}

void Motor_Set(Motor_t *motor, int16_t pwm)
{
    if(pwm > 1000) pwm = 1000;
    if(pwm < -1000) pwm = -1000;

    if(pwm >= 0)
    {
        HAL_GPIO_WritePin(motor->gpio_in1_port, motor->gpio_in1_pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor->gpio_in2_port, motor->gpio_in2_pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(motor->gpio_in1_port, motor->gpio_in1_pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->gpio_in2_port, motor->gpio_in2_pin, GPIO_PIN_SET);
        pwm = -pwm;
    }

    uint32_t arr = motor->htim_pwm->Instance->ARR;
    uint32_t compare = (uint32_t)((float)pwm / 1000.0f * arr);
    __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->pwm_channel, compare);
}

void Motor_Update(Motor_t *motor, float dt)
{
    int32_t current = __HAL_TIM_GET_COUNTER(motor->htim_encoder);
    int32_t delta = current - motor->last_count;

    /* ===== 处理16位计数器溢出 ===== */
    if (delta > 32768)
        delta -= 65536;
    else if (delta < -32768)
        delta += 65536;

    motor->last_count = current;
    motor->total_count += delta;

    /* ===== 速度计算 ===== */
    float rps = (float)delta / motor->encoder_ppr / dt;
    motor->speed_rpm = rps / motor->gear_ratio * 60.0f;

    /* ===== 角度计算 ===== */
    float rev = (float)motor->total_count /
                (motor->encoder_ppr * motor->gear_ratio);

    motor->angle_deg = rev * 360.0f;
}

float Motor_GetSpeed(Motor_t *motor)
{
    return motor->speed_rpm;
}

float Motor_GetAngle(Motor_t *motor)
{
    return motor->angle_deg;
}