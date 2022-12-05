/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define H_BRIDGE_FL_1_Pin GPIO_PIN_0
#define H_BRIDGE_FL_1_GPIO_Port GPIOA
#define H_BRIDGE_FL_2_Pin GPIO_PIN_1
#define H_BRIDGE_FL_2_GPIO_Port GPIOA
#define LINE_SENSOR_1_Pin GPIO_PIN_2
#define LINE_SENSOR_1_GPIO_Port GPIOA
#define BUTTON_2_Pin GPIO_PIN_3
#define BUTTON_2_GPIO_Port GPIOA
#define SENSOR_1_Pin GPIO_PIN_4
#define SENSOR_1_GPIO_Port GPIOA
#define SENSOR_2_Pin GPIO_PIN_5
#define SENSOR_2_GPIO_Port GPIOA
#define IR_PWM_Pin GPIO_PIN_6
#define IR_PWM_GPIO_Port GPIOA
#define SENSOR_3_Pin GPIO_PIN_0
#define SENSOR_3_GPIO_Port GPIOB
#define BUTTON_1_Pin GPIO_PIN_1
#define BUTTON_1_GPIO_Port GPIOB
#define LED_3_Pin GPIO_PIN_10
#define LED_3_GPIO_Port GPIOB
#define LED_2_Pin GPIO_PIN_11
#define LED_2_GPIO_Port GPIOB
#define LINE_SENSOR_2_Pin GPIO_PIN_12
#define LINE_SENSOR_2_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_13
#define LED_1_GPIO_Port GPIOB
#define H_BRIDGE_SLEEP_Pin GPIO_PIN_14
#define H_BRIDGE_SLEEP_GPIO_Port GPIOB
#define H_BRIDGE_IN_1_Pin GPIO_PIN_15
#define H_BRIDGE_IN_1_GPIO_Port GPIOB
#define STARTER_Pin GPIO_PIN_8
#define STARTER_GPIO_Port GPIOA
#define STARTER_EXTI_IRQn EXTI4_15_IRQn
#define H_BRIDGE_IN_4_Pin GPIO_PIN_3
#define H_BRIDGE_IN_4_GPIO_Port GPIOB
#define H_BRIDGE_IN_3_Pin GPIO_PIN_4
#define H_BRIDGE_IN_3_GPIO_Port GPIOB
#define H_BRIDGE_IN_2_Pin GPIO_PIN_5
#define H_BRIDGE_IN_2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
