#include"uart_main_rx.h"
#include "motor_mecanum.h"

double Speed_PID_P = 0.5;//P
double Speed_PID_I = 0.5;//I
 
// double Speed_Proportion = 2.0;//空转速度与负载速度比值

double PID_Pwm_Buff[4] = {0};


int16_t Speed_PID(int index, double TargetSpeed,int Motor_Direction)
{
    static float Bias[4]={0}, Last_Bias[4]={0}, Pwm[4]={0};

    // 将 encoder 结果转换为真实速度
    float RealSpeed = Real_Speed_From_Sub[index] * Motor_Direction; // 10ms → *100 = pulses/sec

    // 偏差
    Bias[index] = TargetSpeed - RealSpeed;

    // 增量式 PID：Δu = Kp*(e - e_last) + Ki*e + Kd*(e - 2e_last1 + e_last2)
    float delta = Speed_PID_P * (Bias[index] - Last_Bias[index])
                 + Speed_PID_I * Bias[index];

    // 累加控制量
    Pwm[index] += delta;

    // PWM 限幅
    if(Pwm[index] > CCR_MAX) Pwm[index] = CCR_MAX;
    if(Pwm[index] < -CCR_MAX) Pwm[index] = -CCR_MAX;

    // 记录偏差
    Last_Bias[index] = Bias[index];

    return (int16_t)Pwm[index];
}
