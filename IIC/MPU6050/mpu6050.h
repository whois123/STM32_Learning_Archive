#ifndef __MPU6050_H
#define __MPU6050_H

#include "stm32f1xx_hal.h"

#define MPU6050_ADDR         (0x68 << 1)
#define MPU6050_GYRO_CONFIG  0x1B    // 陀螺仪
#define MPU6050_ACCEL_CONFIG 0x1C    // 加速度计
#define MPU6050_ACCEL_XOUT_H 0x3B

typedef struct {
    float ax, ay, az;
    float gx, gy, gz;
    float gx_bias, gy_bias, gz_bias; 
} MPU6050_Data_t;

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);
void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *Data);
void MPU6050_Calibrate(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *Data);

#endif