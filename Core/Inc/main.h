/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include <stdio.h>
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
#define DRV_AIN2_Pin GPIO_PIN_0
#define DRV_AIN2_GPIO_Port GPIOA
#define DRV_AIN1_Pin GPIO_PIN_1
#define DRV_AIN1_GPIO_Port GPIOA
#define DRV_BIN1_Pin GPIO_PIN_2
#define DRV_BIN1_GPIO_Port GPIOA
#define DRV_BIN2_Pin GPIO_PIN_3
#define DRV_BIN2_GPIO_Port GPIOA
#define MH_AO_Pin GPIO_PIN_4
#define MH_AO_GPIO_Port GPIOA
#define MH_DO_Pin GPIO_PIN_5
#define MH_DO_GPIO_Port GPIOA
#define MH_VCC_Pin GPIO_PIN_6
#define MH_VCC_GPIO_Port GPIOA
#define MH_GND_Pin GPIO_PIN_7
#define MH_GND_GPIO_Port GPIOA
#define TRIG_Pin GPIO_PIN_11
#define TRIG_GPIO_Port GPIOA
#define ECHO_Pin GPIO_PIN_12
#define ECHO_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
