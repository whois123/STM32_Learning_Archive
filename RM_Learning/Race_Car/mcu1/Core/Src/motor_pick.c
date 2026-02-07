#include "main.h"
#include "tim.h"
#include "motor_pick.h"

void Motor_Pick_Control_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); // Start PWM_CH2 for motor pick
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0); // Initialize with 0 speed

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // Start PWM_CH1 for motor low
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0); // Initialize with 0 speed
}

void Motor_Pick_High_Set_Speed(uint16_t speed)
{
    switch(speed){
        case 1:
            speed = speed_save; // Save speed
            break;
        case 2:
            speed = motor_high_speed_max; // Max speed
            break;
        case 3:
            speed = motor_high_speed_min; // Min speed
            break;
        case 0:
            speed = 0; // Stop
            break;
        default:
            speed = 0; // Stop
            break;
    }

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed);
}

void Motor_Pick_Low_Set_Speed(uint16_t speed)
{
    switch(speed){
        case 1:
            speed = speed_save; // Save speed
            break;
        case 2:
            speed = motor_low_speed_max; // Max speed
            break;
        case 3:
            speed = motor_low_speed_min; // Min speed
            break;
        case 0:
            speed = 0; // Stop
            break;
        default:
            speed = 0; // Stop
            break;
    }

    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, speed);
}




void Motor_Pick_Control_Update(RC_Type *rc)
{
    if(rc == NULL) return;


    if(rc->switch_right == 1){ 
        Motor_Pick_High_Set_Speed(2); // Max speed
        Motor_Pick_Low_Set_Speed(2); 
    }
    else if(rc->switch_right == 2){
        Motor_Pick_High_Set_Speed(3); // Min speed
        Motor_Pick_Low_Set_Speed(3); 
    }
    else if(rc->switch_right == 3){
        Motor_Pick_High_Set_Speed(0); // Stop
        Motor_Pick_Low_Set_Speed(0); // Stop
    }
    else if (rc->key_code == 1){
        Motor_Pick_High_Set_Speed(1); // Save speed
        Motor_Pick_Low_Set_Speed(1); // Save speed
    }
}
