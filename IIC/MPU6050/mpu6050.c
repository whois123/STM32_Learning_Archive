#include "mpu6050.h"

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t data;
    HAL_Delay(100);
    data = 0x00; HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x6B, 1, &data, 1, 100); // 唤醒
    data = 0x07; HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x19, 1, &data, 1, 100); // 1kHz
    data = 0x06; HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x1A, 1, &data, 1, 100); // DLPF
    data = 0x00; HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_GYRO_CONFIG, 1, &data, 1, 100); // ±250°/s
    data = 0x00; HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 1, &data, 1, 100); // ±2g
    return HAL_OK;
}

//零偏校准
void MPU6050_Calibrate(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *Data) {
    float sum_gx = 0, sum_gy = 0, sum_gz = 0;
    const int samples = 500;
    
    // 归零初始偏置
    Data->gx_bias = 0; Data->gy_bias = 0; Data->gz_bias = 0;
    
    for(int i = 0; i < samples; i++) {
        MPU6050_Read_All(hi2c, Data);
        sum_gx += Data->gx;
        sum_gy += Data->gy;
        sum_gz += Data->gz;
        HAL_Delay(2);
    }
    Data->gx_bias = sum_gx / samples;
    Data->gy_bias = sum_gy / samples;
    Data->gz_bias = sum_gz / samples;
}

void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *Data) {
    uint8_t mpu_buf[14];
    if(HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, 1, mpu_buf, 14, 10) != HAL_OK) return;

    Data->ax = (int16_t)(mpu_buf[0] << 8 | mpu_buf[1]) / 16384.0f;
    Data->ay = (int16_t)(mpu_buf[2] << 8 | mpu_buf[3]) / 16384.0f;
    Data->az = (int16_t)(mpu_buf[4] << 8 | mpu_buf[5]) / 16384.0f;
    
    Data->gx = ((int16_t)(mpu_buf[8] << 8 | mpu_buf[9]) / 131.0f) - Data->gx_bias;
    Data->gy = ((int16_t)(mpu_buf[10] << 8 | mpu_buf[11]) / 131.0f) - Data->gy_bias;
    Data->gz = ((int16_t)(mpu_buf[12] << 8 | mpu_buf[13]) / 131.0f) - Data->gz_bias;
}