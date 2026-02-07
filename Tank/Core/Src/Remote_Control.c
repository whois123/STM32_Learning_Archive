#include "Remote_Control.h"

uint8_t usart2_rx_buf[RX_BUF_LEN];
uint8_t usart2_rx_len = 0;
uint8_t usart2_rx_byte;
uint32_t last_rx_tick = 0;

Joystick_t joystick;
void Parse_Joystick_Packet(char *buf)
{
    int lx, ly, rx, ry;

    if (strncmp(buf, "[joystick", 9) != 0)
        return;

    if (sscanf(buf, "[joystick,%d,%d,%d,%d]",
               &lx, &ly, &rx, &ry) == 4)
    {
        joystick.left_x  = lx;
        joystick.left_y  = ly;
        joystick.right_x = rx;
        joystick.right_y = ry;
        
    }
}

void Tank_Move_Control(void)
{
    int16_t forward = joystick.left_y;  // 前后
    int16_t turn    = joystick.left_x;  // 左右

    /* ----------------- 1. 死区处理 ----------------- */
    if (abs(forward) < 5) forward = 0;
    if (abs(turn) < 5)    turn = 0;

    /* ----------------- 2. 转向随前进速度衰减 ----------------- */
    float k = 1.0f - (float)abs(forward) / 100.0f;
    if (k < 0.3f) k = 0.3f; // 保留最低转向能力
    float turn_eff = turn * k;

    /* ----------------- 3. 混控 ----------------- */
    float left  = forward + turn_eff;
    float right = forward - turn_eff;

    /* ----------------- 4. 比例压缩（防打滑/限幅） ----------------- */
    float max_val = fmaxf(fabsf(left), fabsf(right));
    if (max_val > 100.0f)
    {
        left  = left  * 100.0f / max_val;
        right = right * 100.0f / max_val;
    }

    /* ----------------- 5. 输出给电机 ----------------- */
    Motor_Left_SetSpeed((int16_t)left);
    Motor_Right_SetSpeed((int16_t)right);
}

void Turret_Control(void)
{
    Turret_Yaw_Control(joystick.right_y);
    Turret_Pitch_Control(joystick.right_x);
}

void Lost_Control_Check(void)
{
    if (HAL_GetTick() - last_rx_tick > 100) // 100ms
    {
        Motor_Left_SetSpeed(0);
        Motor_Right_SetSpeed(0);
    }
}
