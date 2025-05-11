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
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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
#define BATTERY_Pin GPIO_PIN_1
#define BATTERY_GPIO_Port GPIOC
#define BLK_Pin GPIO_PIN_0
#define BLK_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOA
#define LCD_RESET_Pin GPIO_PIN_2
#define LCD_RESET_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_3
#define LCD_CS_GPIO_Port GPIOA
#define CD_CS2_Pin GPIO_PIN_4
#define CD_CS2_GPIO_Port GPIOA
#define RC522_RST_Pin GPIO_PIN_5
#define RC522_RST_GPIO_Port GPIOC
#define RC522_IRQ_Pin GPIO_PIN_0
#define RC522_IRQ_GPIO_Port GPIOB
#define RC522_CS_Pin GPIO_PIN_1
#define RC522_CS_GPIO_Port GPIOB
#define SD_CD_Pin GPIO_PIN_7
#define SD_CD_GPIO_Port GPIOC
#define LD2410_OUT_Pin GPIO_PIN_12
#define LD2410_OUT_GPIO_Port GPIOC
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_7
#define I2C1_SDA_GPIO_Port GPIOB
#define CTP_RST_Pin GPIO_PIN_8
#define CTP_RST_GPIO_Port GPIOB
#define CTP_INT_Pin GPIO_PIN_9
#define CTP_INT_GPIO_Port GPIOB
#define CTP_INT_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */
// 分支优化
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
    /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
