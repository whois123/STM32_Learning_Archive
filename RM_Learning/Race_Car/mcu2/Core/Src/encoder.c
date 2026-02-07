#include "encoder.h"
#include "usart.h"
#include "uart_sub_rx.h"   // 引入方向数据
#include "tim.h"

extern int8_t Motor_Direction_From_Main[4];
int16_t Encoder_Result[4] = {0};   // 原始脉冲
static uint16_t last_cnt[4] = {0}; // 上一次脉冲

int16_t Real_Speed[4];             // 最终带方向的速度

static inline uint16_t ReadCnt(TIM_HandleTypeDef *htim)
{
    return __HAL_TIM_GET_COUNTER(htim);
}

void Encoder_Init(void)
{
    // 启动 4 个计数器
    HAL_TIM_Base_Start(&htim1);
    HAL_TIM_Base_Start(&htim2);
    HAL_TIM_Base_Start(&htim3);
    HAL_TIM_Base_Start(&htim4);

    HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_IC_Start(&htim4, TIM_CHANNEL_1);
}

void Encoder_Update(void)
{
    uint16_t now_LA, now_LB, now_RA, now_RB;

    // Motor_LA
    now_LA = ReadCnt(&htim1);
    Encoder_Result[0] = (int16_t)(now_LA - last_cnt[0]);
    last_cnt[0] = now_LA;
    Real_Speed[0] = Encoder_Result[0] * Motor_Direction_From_Main[0];

    // Motor_LB
    now_LB = ReadCnt(&htim2);
    Encoder_Result[1] = (int16_t)(now_LB - last_cnt[1]);
    last_cnt[1] = now_LB;
    Real_Speed[1] = Encoder_Result[1] * Motor_Direction_From_Main[1];

    // Motor_RA
    now_RA = ReadCnt(&htim3);
    Encoder_Result[2] = (int16_t)(now_RA - last_cnt[2]);
    last_cnt[2] = now_RA;
    Real_Speed[2] = Encoder_Result[2] * Motor_Direction_From_Main[2];

    //Motor_RB
    now_RB = ReadCnt(&htim4);
    Encoder_Result[3] = (int16_t)(now_RB - last_cnt[3]);
    last_cnt[3] = now_RB;
    Real_Speed[3] = Encoder_Result[3] * Motor_Direction_From_Main[3];

    //Debug
    // char ack_msg[50];
    // sprintf(ack_msg, "RealSpeed Updated: %d,%d,%d,%d\r\n", 
    //         Real_Speed[0], Real_Speed[1],
    //         Real_Speed[2], Real_Speed[3]);
    // HAL_UART_Transmit(&huart1, (uint8_t*)ack_msg, strlen(ack_msg), 100);
}
