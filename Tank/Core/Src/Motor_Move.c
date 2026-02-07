#include "Motor_Move.h"

void Motor_Move_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
}

/*Left Motor*/
void Left_Motor_Dir_Forward(void)
{
    HAL_GPIO_WritePin(Motor_L_1_GPIO_Port, Motor_L_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Motor_L_2_GPIO_Port, Motor_L_2_Pin, GPIO_PIN_RESET);
}

void Left_Motor_Dir_Backward(void)
{
    HAL_GPIO_WritePin(Motor_L_1_GPIO_Port, Motor_L_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Motor_L_2_GPIO_Port, Motor_L_2_Pin, GPIO_PIN_SET);
}

void Left_Motor_Brake(void)
{
    HAL_GPIO_WritePin(Motor_L_1_GPIO_Port, Motor_L_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Motor_L_2_GPIO_Port, Motor_L_2_Pin, GPIO_PIN_SET);
}

/*Right Motor*/
void Right_Motor_Dir_Forward(void)
{
    HAL_GPIO_WritePin(Motor_R_1_GPIO_Port, Motor_R_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Motor_R_2_GPIO_Port, Motor_R_2_Pin, GPIO_PIN_RESET);
}

void Right_Motor_Dir_Backward(void)
{
    HAL_GPIO_WritePin(Motor_R_1_GPIO_Port, Motor_R_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Motor_R_2_GPIO_Port, Motor_R_2_Pin, GPIO_PIN_SET);
}

void Right_Motor_Brake(void)
{
    HAL_GPIO_WritePin(Motor_R_1_GPIO_Port, Motor_R_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Motor_R_2_GPIO_Port, Motor_R_2_Pin, GPIO_PIN_SET);
}

/*Motor Set Speed*/
void Motor_Left_SetSpeed(int16_t speed)
{
    /* 1. 限幅 */
    if (speed > 100)  speed = 100;
    if (speed < -100) speed = -100;

    /* 2. 判断方向 */
    if (speed > 0)
    {
        Left_Motor_Dir_Forward();   // 设置方向 IO
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,
                              speed * MOTOR_PWM_MAX / 100);
    }
    else if (speed < 0)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 调试用，指示每次接收中断
        Left_Motor_Dir_Backward();
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,
                              (-speed) * MOTOR_PWM_MAX / 100);
    }
    else
    {
        /* 3. speed == 0 */
        Left_Motor_Brake();
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    }
}

void Motor_Right_SetSpeed(int16_t speed)
{
    /* 1. 限幅 */
    if (speed > 100)  speed = 100;
    if (speed < -100) speed = -100;

    /* 2. 判断方向 */
    if (speed > 0)
    {
        Right_Motor_Dir_Forward();   // 设置方向 IO
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,
                              speed * MOTOR_PWM_MAX / 100);
    }
    else if (speed < 0)
    {
        Right_Motor_Dir_Backward();
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,
                              (-speed) * MOTOR_PWM_MAX / 100);
    }
    else
    {
        /* 3. speed == 0 */
        Right_Motor_Brake(); 
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    }
}
