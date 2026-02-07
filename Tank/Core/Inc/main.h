/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Motor_L_1_Pin GPIO_PIN_4
#define Motor_L_1_GPIO_Port GPIOA
#define Motor_L_2_Pin GPIO_PIN_5
#define Motor_L_2_GPIO_Port GPIOA
#define Motor_R_1_Pin GPIO_PIN_6
#define Motor_R_1_GPIO_Port GPIOA
#define Motor_R_2_Pin GPIO_PIN_7
#define Motor_R_2_GPIO_Port GPIOA
#define STBY_1_Pin GPIO_PIN_0
#define STBY_1_GPIO_Port GPIOB
#define Motor_Pitch_1_Pin GPIO_PIN_1
#define Motor_Pitch_1_GPIO_Port GPIOB
#define STBY_2_Pin GPIO_PIN_10
#define STBY_2_GPIO_Port GPIOB
#define Motor_Pitch_2_Pin GPIO_PIN_11
#define Motor_Pitch_2_GPIO_Port GPIOB
#define Motor_L_Pin GPIO_PIN_8
#define Motor_L_GPIO_Port GPIOA
#define Motor_R_Pin GPIO_PIN_9
#define Motor_R_GPIO_Port GPIOA
#define Motor_Pitch_Pin GPIO_PIN_10
#define Motor_Pitch_GPIO_Port GPIOA
#define Servo_Pin GPIO_PIN_11
#define Servo_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
