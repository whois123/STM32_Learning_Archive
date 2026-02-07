#include "main.h"
#include "tim.h"
#include "motor_shoot.h"

void Motor_Shoot_Control_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // Start PWM_CH1 for motor shoot
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0); // Initialize with 0 speed
}

void Motor_Shoot_Set_Speed(uint16_t speed)
{
    switch(speed){
        case 1:
            speed = speed_min; // Minum speed
            break;
        case 2:
            speed = speed_max; // Max speed
            break;
        default:
            speed = 0; // Stop 
            break;
    }

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed);
}


void Motor_Shoot_Control_Update(RC_Type *rc)
{
    if(rc == NULL) return;

    switch(rc->switch_left){
        case 1: //Up
            Motor_Shoot_Set_Speed(2); // Max
            break;
        case 2:  //Down
            Motor_Shoot_Set_Speed(1); // Min
            break;
        case 3: //Mid
            Motor_Shoot_Set_Speed(0); // Stop
    }
}

