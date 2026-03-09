#include "imu_filter.h"
#include <math.h>

// 四元数 q0, q1, q2, q3
static float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;

// 积分误差补偿变量 
static float exInt = 0.0f, eyInt = 0.0f, ezInt = 0.0f;

// PI 参数 
#define Kp 2.0f    
#define Ki 0.005f  
#define halfT 0.0025f // 周期的一半

void IMU_Update(float ax, float ay, float az, float gx, float gy, float gz, float dt) {
    float norm;
    float vx, vy, vz;
    float ex, ey, ez;

    // 角度转弧度
    float wx = gx * 0.01745329f;
    float wy = gy * 0.01745329f;
    float wz = gz * 0.01745329f;

    // 如果加速度计无效则仅进行陀螺仪积分
    if(ax*ax + ay*ay + az*az == 0.0f) {
        return; 
    }

    // 归一化 
    norm = sqrtf(ax*ax + ay*ay + az*az);
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;

    // 推算理论上的重力分量
    vx = 2.0f * (q1 * q3 - q0 * q2);
    vy = 2.0f * (q0 * q1 + q2 * q3);
    vz = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;

    // 计算误差
    ex = (ay * vz - az * vy);
    ey = (az * vx - ax * vz);
    ez = (ax * vy - ay * vx);

    // PI 控制
    exInt += ex * Ki;
    eyInt += ey * Ki;
    ezInt += ez * Ki;

    wx = wx + Kp * ex + exInt;
    wy = wy + Kp * ey + eyInt;
    wz = wz + Kp * ez + ezInt;

    // 整合进四元数微分方程更新 (一阶龙格库塔 RK1)
    float dq0 = (-q1 * wx - q2 * wy - q3 * wz) * halfT;
    float dq1 = ( q0 * wx + q2 * wz - q3 * wy) * halfT;
    float dq2 = ( q0 * wy - q1 * wz + q3 * wx) * halfT;
    float dq3 = ( q0 * wz + q1 * wy - q2 * wx) * halfT;

    q0 += dq0;
    q1 += dq1;
    q2 += dq2;
    q3 += dq3;

    // 归一化
    norm = sqrtf(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    if (norm > 0) { 
        q0 /= norm; q1 /= norm; q2 /= norm; q3 /= norm; 
    }
}

// 获取欧拉角
//根据q_0^2 + q_1^2 + q_2^2 + q_3^2 = 1 对计算化简，减轻算力消耗
void IMU_GetEuler(Attitude_t *att) {
    att->roll  = atan2f(2.0f * (q0 * q1 + q2 * q3), 1.0f - 2.0f * (q1 * q1 + q2 * q2)) * 57.29578f;
    att->pitch = atan2f(2.0f * (q0 * q2 - q3 * q1), sqrtf(1.0f - (2.0f * (q0 * q2 - q3 * q1)) * (2.0f * (q0 * q2 - q3 * q1)))) * 57.29578f;
    att->yaw   = atan2f(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3)) * 57.29578f;
}