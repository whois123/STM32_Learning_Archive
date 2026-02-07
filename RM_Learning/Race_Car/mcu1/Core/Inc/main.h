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
#define motor_pick_low_Pin GPIO_PIN_0
#define motor_pick_low_GPIO_Port GPIOA
#define STBY_L_Pin GPIO_PIN_4
#define STBY_L_GPIO_Port GPIOA
#define STBY_R_Pin GPIO_PIN_5
#define STBY_R_GPIO_Port GPIOA
#define motor_mecanum_LA_Pin GPIO_PIN_6
#define motor_mecanum_LA_GPIO_Port GPIOA
#define motor_mecanum_LB_Pin GPIO_PIN_7
#define motor_mecanum_LB_GPIO_Port GPIOA
#define motor_mecanum_RA_Pin GPIO_PIN_0
#define motor_mecanum_RA_GPIO_Port GPIOB
#define motor_mecanum_RB_Pin GPIO_PIN_1
#define motor_mecanum_RB_GPIO_Port GPIOB
#define motor_shoot_Pin GPIO_PIN_8
#define motor_shoot_GPIO_Port GPIOA
#define motor_pick_high_Pin GPIO_PIN_9
#define motor_pick_high_GPIO_Port GPIOA
#define servo_Pin GPIO_PIN_10
#define servo_GPIO_Port GPIOA
#define LA1_Pin GPIO_PIN_15
#define LA1_GPIO_Port GPIOA
#define LA2_Pin GPIO_PIN_3
#define LA2_GPIO_Port GPIOB
#define LB1_Pin GPIO_PIN_4
#define LB1_GPIO_Port GPIOB
#define LB2_Pin GPIO_PIN_5
#define LB2_GPIO_Port GPIOB
#define RA1_Pin GPIO_PIN_6
#define RA1_GPIO_Port GPIOB
#define RA2_Pin GPIO_PIN_7
#define RA2_GPIO_Port GPIOB
#define RB1_Pin GPIO_PIN_8
#define RB1_GPIO_Port GPIOB
#define RB2_Pin GPIO_PIN_9
#define RB2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
