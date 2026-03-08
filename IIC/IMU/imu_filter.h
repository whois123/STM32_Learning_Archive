/* imu_filter.h */
#ifndef __IMU_FILTER_H
#define __IMU_FILTER_H

#include "main.h"

typedef struct {
    float roll;
    float pitch;
    float yaw;
} Attitude_t;

// 姿态解算
void IMU_Update(float ax, float ay, float az, float gx, float gy, float gz, float dt);
// 获取欧拉角
void IMU_GetEuler(Attitude_t *att);

#endif