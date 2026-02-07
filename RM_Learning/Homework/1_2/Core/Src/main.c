/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
    IDLE = 0,
    SINGLE_CLICK,
    LONG_CLICK,
    DOUBLE_CLICK,
    BLINK_MODE
} ButtonState;

typedef enum {
    BLINK_SLOW = 0,
    BLINK_MEDIUM,
    BLINK_FAST,
    BLINK_COUNT
} BlinkSpeed;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEBOUNCE_DELAY 20
#define LONG_PRESS_TIME 500
#define DOUBLE_CLICK_TIME 300
#define BLINK_INTERVAL_SLOW 100   
#define BLINK_INTERVAL_MEDIUM 250   
#define BLINK_INTERVAL_FAST 500     
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
ButtonState state = IDLE;
BlinkSpeed currentBlinkSpeed = BLINK_SLOW;
uint32_t pressStartTime = 0;
uint32_t firstClickTime = 0;
uint32_t lastBlinkTime = 0;
uint8_t clickCount = 0;
uint8_t blinkEnabled = 0;
uint8_t ledState = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t isButtonPressed(void);
uint8_t isButtonReleased(void);
void handleButtonEvents(void);
void handleBlinkMode(void);
uint32_t getBlinkInterval(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t isButtonPressed(void) {
    if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET) {
        HAL_Delay(DEBOUNCE_DELAY);
        if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET) {
            return 1; 
        }
    }
    return 0; 
}

uint8_t isButtonReleased(void) {
    if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_SET) {
        HAL_Delay(DEBOUNCE_DELAY);
        if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_SET) {
            return 1;
        }
    }
    return 0; 
}

uint32_t getBlinkInterval(void) {
    switch(currentBlinkSpeed) {
        case BLINK_SLOW:
            return BLINK_INTERVAL_SLOW;
        case BLINK_MEDIUM:
            return BLINK_INTERVAL_MEDIUM;
        case BLINK_FAST:
            return BLINK_INTERVAL_FAST;
        default:
            return BLINK_INTERVAL_SLOW;
    }
}

void handleBlinkMode(void) {
    uint32_t currentTime = HAL_GetTick();
    uint32_t blinkInterval = getBlinkInterval();
    
    if (currentTime - lastBlinkTime >= blinkInterval) {
        ledState = !ledState;
        if (ledState) {
            HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET); 
        } else {
            HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);   
        }
        lastBlinkTime = currentTime;
    }
}

void handleButtonEvents(void) {
    static uint32_t doubleClickTimeout = 0;
    uint32_t currentTime = HAL_GetTick();
    
    switch(state) {
        case IDLE:
            if (isButtonPressed()) {
                pressStartTime = currentTime;
                state = SINGLE_CLICK;
            }
            break;
            
        case SINGLE_CLICK:
            if (isButtonReleased()) {
                uint32_t pressDuration = currentTime - pressStartTime;
                
                if (pressDuration >= LONG_PRESS_TIME) {
                    state = LONG_CLICK;
                    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin,GPIO_PIN_SET); 
                    blinkEnabled = 0;
                    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET); 
                } else {
                    firstClickTime = currentTime;
                    clickCount = 1;
                    doubleClickTimeout = currentTime + DOUBLE_CLICK_TIME;
                    state = DOUBLE_CLICK;
                }
            }
            break;
            
        case DOUBLE_CLICK:
            if (currentTime >= doubleClickTimeout) {
                if (!blinkEnabled) {
                    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin,GPIO_PIN_RESET);
                } else {
                    blinkEnabled = 0;
                    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
                }
                clickCount = 0;
                state = IDLE;
            }
            
            if (isButtonPressed()) {
                if (!blinkEnabled) {
                    blinkEnabled = 1;
                    currentBlinkSpeed = BLINK_SLOW; 
                    lastBlinkTime = currentTime;
                    ledState = 0;
                    state = BLINK_MODE;
                } else {
                    currentBlinkSpeed = (currentBlinkSpeed + 1) % BLINK_COUNT;
                    lastBlinkTime = currentTime;
                    state = BLINK_MODE;
                }
                clickCount = 0;
                while (isButtonReleased() == 0) {
                }
                state = IDLE;
            }
            break;
            
        case LONG_CLICK:
            if (isButtonReleased()) {
                state = IDLE;
            }
            break;
            
        case BLINK_MODE:
            if (isButtonPressed()) {
                pressStartTime = currentTime;
                state = SINGLE_CLICK;
            }
            break;
            
        default:
            state = IDLE;
            break;
    }
}
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
    /* USER CODE BEGIN 2 */
    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET); 
    state = IDLE;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        handleButtonEvents();
      
        if (blinkEnabled) {
            handleBlinkMode();
        }
        
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

#ifdef  USE_FULL_ASSERT
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
