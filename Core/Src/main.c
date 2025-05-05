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
#include "adc.h"
#include "at24cxx.h"
#include "dataStruct.h"
#include "dma.h"

#include "fatfs.h"
#include "i2c.h"
#include "sdio.h"
#include "spi.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "function.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "touch.h"
#include "delay.h"
#include "lcd.h"
#include "gui_guider.h"
#include "events_init.h"
#include "eventHandler.h"
#include <stdint.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    // 阻塞方式打印 -> 串口1
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// #define WRITEMODE
// #define READMODE
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
lv_ui guider_ui;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
    MX_DMA_Init();
    MX_ADC1_Init();
    MX_I2C2_Init();
    MX_I2C3_Init();
    MX_SDIO_SD_Init();
    MX_SPI1_Init();
    MX_SPI2_Init();
    MX_USART1_UART_Init();
    MX_USART3_UART_Init();
    MX_FATFS_Init();
    /* USER CODE BEGIN 2 */
    // char message[64];
    // srand(HAL_GetTick());
    // HAL_ADC_Start(&hadc1);
    // HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    // totalInit();
#ifdef WRITEMODE
    if (at24_isConnected())
    {
        uint16_t tmp = 5;
        UserInfo users[] = {{23125011044, "张三"},
                            {23125011045, "李四"},
                            {23125011046, "王五"},
                            {23125011047, "赵六"},
                            {23125011048, "钱七"}};
        CheckInfo checks[] = {{23125011044, 202505050443, 202505050543},
                              {23125011045, 202505050444, 202505050544},
                              {23125011046, 202505050445, 202505050545},
                              {23125011047, 202505050446, 202505050546},
                              {23125011048, 202505050447, 202505050547}};
        at24_write(USER_INFO_LEN_ADDR, (uint8_t *)&tmp, 2, 1000);
        at24_write(CHECK_INFO_LEN_ADDR, (uint8_t *)&tmp, 2, 1000);
        at24_write(USER_INFO_ADDR, (uint8_t *)users, sizeof(users), 1000);
        at24_write(CHECK_INFO_ADDR, (uint8_t *)checks, sizeof(checks), 1000);
        HAL_UART_Transmit(&huart1, (uint8_t *)"Write OK\n", 10, 1000);
        HAL_Delay(HAL_MAX_DELAY);
    }
#endif
#ifdef READMODE
    if (at24_isConnected())
    {
        uint8_t message[64];
        uint16_t userNumber = 0, checkNumber = 0;
        at24_read(USER_INFO_LEN_ADDR, (uint8_t *)&userNumber, 2, 1000);
        at24_read(CHECK_INFO_LEN_ADDR, (uint8_t *)&checkNumber, 2, 1000);
        UserInfo *users = (UserInfo *)malloc(sizeof(UserInfo) * userNumber);
        CheckInfo *checks = (CheckInfo *)malloc(sizeof(CheckInfo) * checkNumber);
        at24_read(USER_INFO_ADDR, (uint8_t *)users, sizeof(UserInfo) * userNumber, 1000);
        at24_read(CHECK_INFO_ADDR, (uint8_t *)checks, sizeof(CheckInfo) * checkNumber, 1000);
        snprintf((char *)message, sizeof(message), "User Number: %d\n", userNumber);
        HAL_UART_Transmit(&huart1, message, strlen((char *)message), 1000);
        HAL_Delay(500);
        snprintf((char *)message, sizeof(message), "Check Number: %d\n", checkNumber);
        HAL_UART_Transmit(&huart1, message, strlen((char *)message), 1000);
        HAL_Delay(500);
        for (int i = 0; i < userNumber; i++)
        {
            // printf("User %d: %d %s\n", i, users[i].id, users[i].name);
            snprintf((char *)message, sizeof(message), "User %d: %llu %s\n", i, users[i].ID, users[i].Name);
            HAL_UART_Transmit(&huart1, message, strlen((char *)message), 1000);
            HAL_Delay(500);
        }
        for (int i = 0; i < checkNumber; i++)
        {
            // printf("Check %d: %d %d %d\n", i, checks[i].id, checks[i].checkIn, checks[i].checkOut);
            snprintf((char *)message, sizeof(message), "Check %d: %llu %llu %llu\n", i, checks[i].ID, checks[i].startTime, checks[i].endTime);
            HAL_UART_Transmit(&huart1, message, strlen((char *)message), 1000);
            HAL_Delay(500);
        }
        HAL_Delay(HAL_MAX_DELAY);
    }
#endif

#ifndef WRITEMODE
#ifndef READMODE
    ds3231Init();
    delay_init(100);
    at24Init();
    LCD_Init();
    LCD_direction(3);
    TP_Init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    myEventInit(&guider_ui);
    myLVGL_UIInit();
    //  lv_demo_benchmark();
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        // loop();
        lv_task_handler();
        HAL_Delay(1);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
#endif
#endif
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

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 6;
    RCC_OscInitStruct.PLL.PLLN = 100;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    RCC_OscInitStruct.PLL.PLLR = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
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
