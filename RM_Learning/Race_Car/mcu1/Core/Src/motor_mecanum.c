#include "main.h"
#include "tim.h"
#include "motor_mecanum.h"

int8_t Motor_Direction[4] = {1,1,1,1};  // 1 正转, 2 反转， 0 停止

//Initialize Motor Mecanum
void Motor_Mecanum_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0); 

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); 
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0); 

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); 
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0); 

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4); 
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0); 
}


//Motor Mecanum LA
void Motor_Mecanum_LA_Speed(int16_t Compare){
    uint16_t ccr = 0;

    if(Compare >= 0){ // Forward
        HAL_GPIO_WritePin(LA1_GPIO_Port, LA1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LA2_GPIO_Port, LA2_Pin, GPIO_PIN_RESET);
        ccr = Compare;
    }
    else{ // Backward
        HAL_GPIO_WritePin(LA1_GPIO_Port, LA1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LA2_GPIO_Port, LA2_Pin, GPIO_PIN_SET);
        ccr = -Compare;
    }
    
    if (ccr > CCR_MAX) ccr = CCR_MAX; // Limit max ccr to CCR_MAX

    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1, ccr);
}

void Motor_Mecanum_LA_Coast(void){
    HAL_GPIO_WritePin(LA1_GPIO_Port, LA1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LA2_GPIO_Port, LA2_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,CCR_MAX);
}

void Motor_Mecanum_LA_Brake(void){
    HAL_GPIO_WritePin(LA1_GPIO_Port, LA1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LA2_GPIO_Port, LA2_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1, 0);
}


//Motor Mecanum LB:
void Motor_Mecanum_LB_Speed(int16_t Compare){
    uint16_t ccr = 0;

    if(Compare >= 0){ // Forward
        HAL_GPIO_WritePin(LB1_GPIO_Port, LB1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LB2_GPIO_Port, LB2_Pin, GPIO_PIN_RESET);
        ccr = Compare;
    }
    else{ // Backward
        HAL_GPIO_WritePin(LB1_GPIO_Port, LB1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LB2_GPIO_Port, LB2_Pin, GPIO_PIN_SET);
        ccr = -Compare;
    }

    if (ccr > CCR_MAX) ccr = CCR_MAX; // Limit max ccr to CCR_MAX

    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, ccr);
}

void Motor_Mecanum_LB_Coast(void){
    HAL_GPIO_WritePin(LB1_GPIO_Port, LB1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LB2_GPIO_Port, LB2_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,CCR_MAX);
}

void Motor_Mecanum_LB_Brake(void){
    HAL_GPIO_WritePin(LB1_GPIO_Port, LB1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LB2_GPIO_Port, LB2_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
}


//Motor Mecanum RA
void Motor_Mecanum_RA_Speed(int16_t Compare){
    uint16_t ccr = 0;

    if(Compare >= 0){ // Forward
        HAL_GPIO_WritePin(RA1_GPIO_Port, RA1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RA2_GPIO_Port, RA2_Pin, GPIO_PIN_RESET);
        ccr = Compare;
    }
    else{ // Backward
        HAL_GPIO_WritePin(RA1_GPIO_Port, RA1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RA2_GPIO_Port, RA2_Pin, GPIO_PIN_SET);
        ccr = -Compare;
    }
    
    if (ccr > CCR_MAX) ccr = CCR_MAX; // Limit max ccr to CCR_MAX

    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, ccr);
}

void Motor_Mecanum_RA_Coast(void){
    HAL_GPIO_WritePin(RA1_GPIO_Port, RA1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RA2_GPIO_Port, RA2_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,CCR_MAX);
}

void Motor_Mecanum_RA_Brake(void){
    HAL_GPIO_WritePin(RA1_GPIO_Port, RA1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RA2_GPIO_Port, RA2_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, 0);
}


//Motor Mecanum RB
void Motor_Mecanum_RB_Speed(int16_t Compare){
    uint16_t ccr = 0;

    if(Compare >= 0){ // Forward
        HAL_GPIO_WritePin(RB1_GPIO_Port, RB1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(RB2_GPIO_Port, RB2_Pin, GPIO_PIN_RESET);
        ccr = Compare;
    }
    else{ // Backward
        HAL_GPIO_WritePin(RB1_GPIO_Port, RB1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(RB2_GPIO_Port, RB2_Pin, GPIO_PIN_SET);
        ccr = -Compare;
    }
    
    if (ccr > CCR_MAX) ccr = CCR_MAX; // Limit max ccr to CCR_MAX

    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, ccr);
}

void Motor_Mecanum_RB_Coast(void){
    HAL_GPIO_WritePin(RB1_GPIO_Port, RB1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RB2_GPIO_Port, RB2_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,CCR_MAX);
}

void Motor_Mecanum_RB_Brake(void){
    Motor_Direction[3] = 0;
    HAL_GPIO_WritePin(RB1_GPIO_Port, RB1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RB2_GPIO_Port, RB2_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);
}
