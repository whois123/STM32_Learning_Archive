#include "Turret_Move.h"
void Motor_Pitch_Init(void){
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
}

void Servo_Init(void){
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, SERVO_MIN_PULSE);
}

void Turret_Init(void){
    Motor_Pitch_Init();
    Servo_Init();
}

/*Yaw*/

void Servo_SetAngle(uint8_t angle)
{
    uint16_t pulse = SERVO_MIN_PULSE + (angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE) / 180);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pulse);
}


// 0: stop, 1: up, 2: down
void Turret_Yaw(uint8_t direction_flag){ 
    uint8_t current_yaw_angle;
    if (direction_flag == 1){
        current_yaw_angle = 20;
        Servo_SetAngle(current_yaw_angle);
    }
    else if (direction_flag == 2){
        current_yaw_angle = 0;
        Servo_SetAngle(current_yaw_angle);
    }
}



void Turret_Yaw_Control(int16_t dir){
    if (dir > 40){
        Turret_Yaw(1);
    }
    else if (dir < -40){
        Turret_Yaw(2);
    }
}


/*Pitch*/

void Turret_Pitch_Left(void){
    HAL_GPIO_WritePin(Motor_Pitch_1_GPIO_Port, Motor_Pitch_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Motor_Pitch_2_GPIO_Port, Motor_Pitch_2_Pin, GPIO_PIN_RESET);
}
void Turret_Pitch_Right(){
    HAL_GPIO_WritePin(Motor_Pitch_1_GPIO_Port, Motor_Pitch_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Motor_Pitch_2_GPIO_Port, Motor_Pitch_2_Pin, GPIO_PIN_SET);
}
void Turret_Pitch_Control(int16_t dir){
    
    if (dir < -40)
    {
        Turret_Pitch_Left();   
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0.8 * MOTOR_PITCH_PWM_MAX); // 设置占空比
    }
    else if (dir > 40)
    {
        Turret_Pitch_Right();  
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0.8 * MOTOR_PITCH_PWM_MAX); // 设置占空比
    }
    else
    {
        HAL_GPIO_WritePin(Motor_Pitch_1_GPIO_Port, Motor_Pitch_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Motor_Pitch_2_GPIO_Port, Motor_Pitch_2_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0); 
    }
    
}
