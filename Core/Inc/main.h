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
#include "stm32h5xx_hal.h"

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
#define B1_BLUE_USER_BUTTON_Pin GPIO_PIN_13
#define B1_BLUE_USER_BUTTON_GPIO_Port GPIOC
#define B1_BLUE_USER_BUTTON_EXTI_IRQn EXTI13_IRQn
#define RESET_BUTTON_Pin GPIO_PIN_3
#define RESET_BUTTON_GPIO_Port GPIOC
#define RESET_BUTTON_EXTI_IRQn EXTI3_IRQn
#define USER_RED_LED_Pin GPIO_PIN_0
#define USER_RED_LED_GPIO_Port GPIOA
#define USER_YELLOW_LED_Pin GPIO_PIN_1
#define USER_YELLOW_LED_GPIO_Port GPIOA
#define USER_GREEN_LED_Pin GPIO_PIN_2
#define USER_GREEN_LED_GPIO_Port GPIOA
#define T_VCP_RX_Pin GPIO_PIN_3
#define T_VCP_RX_GPIO_Port GPIOA
#define T_VCP_TX_Pin GPIO_PIN_4
#define T_VCP_TX_GPIO_Port GPIOA
#define USER_LED_Pin GPIO_PIN_5
#define USER_LED_GPIO_Port GPIOA
#define SET_BUTTON_Pin GPIO_PIN_4
#define SET_BUTTON_GPIO_Port GPIOC
#define SET_BUTTON_EXTI_IRQn EXTI4_IRQn
#define MID_BUTTON_Pin GPIO_PIN_5
#define MID_BUTTON_GPIO_Port GPIOC
#define MID_BUTTON_EXTI_IRQn EXTI5_IRQn
#define USER_BLUE_LED_Pin GPIO_PIN_0
#define USER_BLUE_LED_GPIO_Port GPIOB
#define RIGHT_BUTTON_Pin GPIO_PIN_1
#define RIGHT_BUTTON_GPIO_Port GPIOB
#define RIGHT_BUTTON_EXTI_IRQn EXTI1_IRQn
#define LEFT_BUTTON_Pin GPIO_PIN_2
#define LEFT_BUTTON_GPIO_Port GPIOB
#define LEFT_BUTTON_EXTI_IRQn EXTI2_IRQn
#define ARD_D1_TX_Pin GPIO_PIN_14
#define ARD_D1_TX_GPIO_Port GPIOB
#define ARD_D0_RX_Pin GPIO_PIN_15
#define ARD_D0_RX_GPIO_Port GPIOB
#define DOWN_BUTTON_Pin GPIO_PIN_7
#define DOWN_BUTTON_GPIO_Port GPIOC
#define DOWN_BUTTON_EXTI_IRQn EXTI7_IRQn
#define USB_FS_VBUS_Pin GPIO_PIN_9
#define USB_FS_VBUS_GPIO_Port GPIOA
#define USB_FS_DN_Pin GPIO_PIN_11
#define USB_FS_DN_GPIO_Port GPIOA
#define USB_FS_DP_Pin GPIO_PIN_12
#define USB_FS_DP_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define T_JTDI_Pin GPIO_PIN_15
#define T_JTDI_GPIO_Port GPIOA
#define USB_FS_PWR_EN_Pin GPIO_PIN_10
#define USB_FS_PWR_EN_GPIO_Port GPIOC
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB
#define UP_BUTTON_Pin GPIO_PIN_6
#define UP_BUTTON_GPIO_Port GPIOB
#define UP_BUTTON_EXTI_IRQn EXTI6_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
