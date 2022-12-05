/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
volatile uint8_t sensor_value_1;
volatile uint8_t sensor_value_2;
volatile uint8_t sensor_value_3;


uint8_t line_sensor_1_value;
uint8_t line_sensor_2_value;

uint8_t button_1_value;
uint8_t button_2_value;

uint32_t tempCode;
uint8_t bitIndex;
uint8_t cmd;
uint8_t cmdli;
uint32_t code;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void motorBreak()
{
	HAL_GPIO_WritePin(H_BRIDGE_IN_1_GPIO_Port, H_BRIDGE_IN_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_2_GPIO_Port, H_BRIDGE_IN_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_3_GPIO_Port, H_BRIDGE_IN_3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_4_GPIO_Port, H_BRIDGE_IN_4_Pin, GPIO_PIN_RESET);
}
void motorForward()
{
	HAL_GPIO_WritePin(H_BRIDGE_IN_1_GPIO_Port, H_BRIDGE_IN_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_2_GPIO_Port, H_BRIDGE_IN_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_3_GPIO_Port, H_BRIDGE_IN_3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_4_GPIO_Port, H_BRIDGE_IN_4_Pin, GPIO_PIN_RESET);
}
void motorRotationRight()
{
	HAL_GPIO_WritePin(H_BRIDGE_IN_1_GPIO_Port, H_BRIDGE_IN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_2_GPIO_Port, H_BRIDGE_IN_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_3_GPIO_Port, H_BRIDGE_IN_3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_4_GPIO_Port, H_BRIDGE_IN_4_Pin, GPIO_PIN_RESET);
}
void motorRotationLeft()
{
	HAL_GPIO_WritePin(H_BRIDGE_IN_1_GPIO_Port, H_BRIDGE_IN_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_2_GPIO_Port, H_BRIDGE_IN_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_3_GPIO_Port, H_BRIDGE_IN_3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_4_GPIO_Port, H_BRIDGE_IN_4_Pin, GPIO_PIN_SET);
}
void motorRevers()
{
	HAL_GPIO_WritePin(H_BRIDGE_IN_1_GPIO_Port, H_BRIDGE_IN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_2_GPIO_Port, H_BRIDGE_IN_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_3_GPIO_Port, H_BRIDGE_IN_3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_BRIDGE_IN_4_GPIO_Port, H_BRIDGE_IN_4_Pin, GPIO_PIN_SET);
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
  MX_ADC_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);
  __HAL_TIM_SET_COUNTER(&htim1, 0);


  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  if(code==1086290565)// sprawdza czy robor otrzymał start
	  {
		  while(1)
		  {
			  if(code==1086290055){while(1){motorBreak();}}
			  HAL_ADC_Start(&hadc);
			  HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
			  sensor_value_1 = HAL_ADC_GetValue(&hadc);

			  HAL_ADC_Start(&hadc);
			  HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
			  sensor_value_2 = HAL_ADC_GetValue(&hadc);

			  HAL_ADC_Start(&hadc);
			  HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
			  sensor_value_3 = HAL_ADC_GetValue(&hadc);

			  line_sensor_1_value = HAL_GPIO_ReadPin(LINE_SENSOR_1_GPIO_Port,LINE_SENSOR_1_Pin);
			  line_sensor_2_value = HAL_GPIO_ReadPin(LINE_SENSOR_2_GPIO_Port,LINE_SENSOR_2_Pin);


			  if(sensor_value_3==1)motorForward();
			  else if(sensor_value_1==1)motorRotationLeft();
			  else if(sensor_value_2==1)motorRotationRight();
			  else if(line_sensor_1_value==1)
			  {
				  motorRevers();
				  HAL_Delay(100);
				  motorRotationLeft();
				  HAL_Delay(100);
				  motorBreak();
			  }
			  else if(line_sensor_2_value==1)
			  {
				  motorRevers();
				  HAL_Delay(100);
				  motorRotationRight();
				  HAL_Delay(100);
				  motorBreak();
			  }
			  else motorForward();
		  }

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 15;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 420;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 9999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 19000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, H_BRIDGE_FL_1_Pin|H_BRIDGE_FL_2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_3_Pin|LED_2_Pin|LED_1_Pin|H_BRIDGE_IN_1_Pin
                          |H_BRIDGE_IN_4_Pin|H_BRIDGE_IN_3_Pin|H_BRIDGE_IN_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(H_BRIDGE_SLEEP_GPIO_Port, H_BRIDGE_SLEEP_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : H_BRIDGE_FL_1_Pin H_BRIDGE_FL_2_Pin */
  GPIO_InitStruct.Pin = H_BRIDGE_FL_1_Pin|H_BRIDGE_FL_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LINE_SENSOR_1_Pin */
  GPIO_InitStruct.Pin = LINE_SENSOR_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LINE_SENSOR_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_2_Pin */
  GPIO_InitStruct.Pin = BUTTON_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_1_Pin */
  GPIO_InitStruct.Pin = BUTTON_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_3_Pin LED_2_Pin LED_1_Pin */
  GPIO_InitStruct.Pin = LED_3_Pin|LED_2_Pin|LED_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LINE_SENSOR_2_Pin */
  GPIO_InitStruct.Pin = LINE_SENSOR_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LINE_SENSOR_2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : H_BRIDGE_SLEEP_Pin */
  GPIO_InitStruct.Pin = H_BRIDGE_SLEEP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(H_BRIDGE_SLEEP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : H_BRIDGE_IN_1_Pin H_BRIDGE_IN_4_Pin H_BRIDGE_IN_3_Pin H_BRIDGE_IN_2_Pin */
  GPIO_InitStruct.Pin = H_BRIDGE_IN_1_Pin|H_BRIDGE_IN_4_Pin|H_BRIDGE_IN_3_Pin|H_BRIDGE_IN_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : STARTER_Pin */
  GPIO_InitStruct.Pin = STARTER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(STARTER_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == STARTER_Pin)
  {
    if (__HAL_TIM_GET_COUNTER(&htim1) > 8000)
    {
      tempCode = 0;
      bitIndex = 0;
    }
    else if (__HAL_TIM_GET_COUNTER(&htim1) > 1700)
    {
      tempCode |= (1UL << (31-bitIndex));   // write 1
      bitIndex++;
    }
    else if (__HAL_TIM_GET_COUNTER(&htim1) > 1000)
    {
      tempCode &= ~(1UL << (31-bitIndex));  // write 0
      bitIndex++;
    }
    if(bitIndex == 32)
    {
      cmdli = ~tempCode; // Logical inverted last 8 bits
      cmd = tempCode >> 8; // Second last 8 bits
      if(cmdli == cmd) // Check for errors
      {
        code = tempCode; // If no bit errors
      }
      bitIndex = 0;
    }
    __HAL_TIM_SET_COUNTER(&htim1, 0);
  }
}
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
