#include "main.h"
#include "tim.h"
#include "servo.h"

void Servo_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1555);
}

void Servo_SetAngle(uint8_t angle)
{
    uint16_t pulse = SERVO_MIN_PULSE + (angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE) / 180);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pulse);
}

void Servo_Control_Update(RC_Type *rc)
{
    static uint8_t servo_angle = 0;      // 当前角度
    static uint16_t last_key = 0;        // 上一次按键状态
    static uint8_t toggle_state = 0;     // 当前开合状态（0=关，1=开）

    if (rc == NULL) return;

    if (rc->key_code != last_key)
    {
        if (rc->key_code == 8) 
        {
            toggle_state = !toggle_state; 
            servo_angle = toggle_state ? 45 : 5;
            Servo_SetAngle(servo_angle);
        }
        else if (rc->key_code == 4)
        {
            toggle_state = !toggle_state; 
            servo_angle = toggle_state ? 95 : 5;
            Servo_SetAngle(servo_angle);
        }

        last_key = rc->key_code; 
    }

}
