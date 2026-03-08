/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Motor.h"
#include "PID.h"
#include <math.h>
#include "Feedforward.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
Feedforward_t SpeedFF;
/* ===================== PID对象 ===================== */
PidTypeDef pid_pos;
PidTypeDef pid_speed;

/* ===================== 电机对象 ===================== */
Motor_t motor;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* 固定采样周期 */
#define CONTROL_DT 0.001f   // 1kHz
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float pwm = 0.0f;

float raw_speed = 0.0f;
float flitered_speed = 0.0f;
float flitered_speed_alpha = 0.3f;

/* ===================== PID参数 ===================== */
float pid_pos_param[3]   = {3.0f, 0.0f, 5.0f};   // 位置环
float pid_speed_param[3] = {10.0f, 1.0f, 0.0f};   // 速度环

/* ===================== 控制变量 ===================== */
float target_pos   = 0.0f;   // 目标角度 (deg)
float target_speed = 0.0f;   // 目标转速 (rpm)

float angle = 0.0f; // 当前角度 (deg) 
float speed = 0.0f; // 当前转速 (rpm)

/* ===================== 正弦波测试专用变量 ===================== */
float run_time = 0.0f;           // 运行时间累计 (s)
float test_sine_freq = 2.0f;     // 测试频率: 2Hz
float test_sine_amp = 300.0f;    // 测试幅值: 300 RPM
float debug_u_ff = 0.0f;         // 记录前馈输出电压分量
float debug_u_fb = 0.0f;         // 记录反馈(PID)输出电压分量
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void SetTargetAngle(float delta_deg)
{
    target_pos = angle + delta_deg;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    // static uint8_t pos_div = 0;
    static uint8_t speed_div = 0;

    if (htim == &htim6)
    {
        /* ===== 更新电机状态 ===== */
        Motor_Update(&motor, CONTROL_DT);

        raw_speed = Motor_GetSpeed(&motor);
        // 一阶低通滤波
        flitered_speed = (1.0f - flitered_speed_alpha) * flitered_speed
                          + flitered_speed_alpha * raw_speed;
    
        speed = flitered_speed;

        angle = Motor_GetAngle(&motor);

        /* ===================================================== */
        /* ================= 位置环 200Hz ======================= */
        /* ===================================================== */
        // if (++pos_div >= 5)
        // {
        //     pos_div = 0;

        //     target_speed = pid_pos.f_cal_pid(
        //         &pid_pos,
        //         angle,
        //         target_pos
        //     );
        // }

        /* ================= 外环关闭 ================= */
        /* 直接给固定速度用于调速度环 */
        target_speed = 200.0f; 

        /* ===================================================== */
        /* ================= 速度环 1000Hz ======================== */
        /* ===================================================== */
        if(++speed_div >= 1)
        {
            speed_div = 0;


            float u_ff = FF_Calculate(&SpeedFF, target_speed, 0.0f);
        
            /* 计算PID补偿量 */
            float u_fb = pid_speed.f_cal_pid(
              &pid_speed,
              speed,
              target_speed
              );
            
            /* 输出汇总 (前馈前馈 + 反馈) */
            float final_output = u_ff + u_fb;

            pwm = final_output;
            
            // pwm = pid_speed.f_cal_pid(
            //   &pid_speed,
            //   speed,
            //   target_speed
          // );

          Motor_Set(&motor, (int16_t)pwm);
          
        }
        
        /*======开环控制======*/
        // Motor_Set(&motor, 1000); 
        
    }
}

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//     // static uint8_t pos_div = 0;
//     static uint8_t speed_div = 0;

//     if (htim == &htim6)
//     {
//         /* ===== 更新电机状态 ===== */
//         Motor_Update(&motor, CONTROL_DT);

//         raw_speed = Motor_GetSpeed(&motor);
//         flitered_speed = (1.0f - flitered_speed_alpha) * flitered_speed
//                           + flitered_speed_alpha * raw_speed;
//         speed = flitered_speed;
//         angle = Motor_GetAngle(&motor);

//         /* ================= 旁路位置环 ======================= */
//         /*
//         if (++pos_div >= 5) {
//             pos_div = 0;
//             target_speed = pid_pos.f_cal_pid(&pid_pos, angle, target_pos);
//         }
//         */

//         /* ================= 正弦波目标速度生成 (1000Hz) ================= */
//         run_time += CONTROL_DT; // 累加时间 (dt = 0.001s)
        
//         // ω_ref = A * sin(2 * π * f * t)
//         target_speed = test_sine_amp * sinf(1.0f * 3.14159265f * test_sine_freq * run_time);

//         /* ================= 速度环 1000Hz ======================== */
//         if(++speed_div >= 1)
//         {
//             speed_div = 0;

//             /* 1. 前馈计算 (传入目标速度，内部自动差分得加速度) */
//             debug_u_ff = FF_Calculate(&SpeedFF, target_speed, 0.0f);
        
//             /* 2. PID补偿量计算 */
//             debug_u_fb = pid_speed.f_cal_pid(&pid_speed, speed, target_speed);
            
//             /* 3. 输出汇总并下发 */
//             pwm = debug_u_ff + debug_u_fb;
//             // pwm = debug_u_fb;
//             Motor_Set(&motor, (int16_t)pwm);
//         }
//     }
// }

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  target_pos = Motor_GetAngle(&motor); 

  /* ===================== 电机参数绑定 ===================== */
  motor.htim_pwm     = &htim1;
  motor.pwm_channel  = TIM_CHANNEL_1;
  motor.htim_encoder = &htim2;

  motor.encoder_ppr  = 44.0f;      // 电机编码器PPR
  motor.gear_ratio   = 19.0f;      // 减速比

  motor.gpio_in1_port = IN1_GPIO_Port;
  motor.gpio_in1_pin  = IN1_Pin;
  
  motor.gpio_in2_port = IN2_GPIO_Port;
  motor.gpio_in2_pin  = IN2_Pin;

  Motor_Init(&motor);

  /* ===================== PID初始化 ===================== */
  pid_init(&pid_pos);
  pid_init(&pid_speed);

  /* 位置环 */
  pid_pos.f_param_init(
      &pid_pos,
      PID_POSITION,
      pid_pos_param,
      200.0f,
      100.0f,
      1000.0f,
      0.0f,
      0.7f,
      0, 0
  );

  /* 速度环 */
  pid_speed.f_param_init(
      &pid_speed,
      PID_POSITION,
      pid_speed_param,
      600.0f,       // 输出限幅
      500.0f,       // 积分限幅
      100.0f,       // I分离
      1.0f,         // 死区
      0.7f,         // 微分滤波gama
      0, 0
  );

  FF_Init(&SpeedFF, 0.6849f, 0.1849f, 0.001f, 1000.0f);

  /* 启动控制定时器 */
  HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // static uint8_t move_flag = 0;

    // if(move_flag == 0)
    // {
    //     HAL_Delay(100);
    //     SetTargetAngle(180.0f);   // 转180°
    //     move_flag = 1;
    // }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
