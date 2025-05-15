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
#include "RC522.h"
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
// #define SDTEST
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
#ifdef SDTEST
void FatFsTest(void)
{
    static FATFS myFatFs;                                           // FatFs 文件系统对象; 这个结构体占用598字节，有点大，需用static修饰(存放在全局数据区), 避免stack溢出
    static FIL myFile;                                              // 文件对象; 这个结构体占用570字节，有点大，需用static修饰(存放在全局数据区), 避免stack溢出
    static FRESULT f_res;                                           // 文件操作结果
    static unsigned int num;                                        // 文件实际成功读写的字节数
    static uint8_t aReadData[1024] = {0};                           // 读取缓冲区; 这个数组占用1024字节，需用static修饰(存放在全局数据区), 避免stack溢出
    static uint8_t aWriteBuf[] = "测试; This is FatFs Test ! \r\n"; // 要写入的数据

    // 重要的延时：避免烧录期间的复位导致文件读写、格式化等错误
    HAL_Delay(1000); // 重要：稍作延时再开始读写测试; 避免有些仿真器烧录期间的多次复位，短暂运行了程序，导致下列读写数据不完整。

    // 1、挂载测试：在SD卡挂载文件系统
    printf("\r\n\r\n");
    printf("1、挂载 FatFs 测试 ****** \r\n");
    f_res = f_mount(&myFatFs, "0:", 1); // 在SD卡上挂载文件系统; 参数：文件系统对象、驱动器路径、读写模式(0只读、1读写)
    if (f_res == FR_NO_FILESYSTEM)      // 检查是否已有文件系统，如果没有，就格式化创建创建文件系统
    {
        printf("SD卡没有文件系统，开始格式化…...\r\n");
        static uint8_t aMountBuffer[4096];                              // 格式化时所需的临时缓存; 块大小512的倍数; 值越大格式化越快, 如果内存不够，可改为512或者1024; 当需要在函数内定义这种大缓存时，要用static修饰，令缓存存放在全局数据区内，不然，可能会导致stack溢出。
        f_res = f_mkfs("0:", 0, 0, aMountBuffer, sizeof(aMountBuffer)); // 格式化SD卡; 参数：驱动器、文件系统(0-自动\1-FAT12\2-FAT16\3-FAT32\4-exFat)、簇大小(0为自动选择)、格式化临时缓冲区、缓冲区大小; 格式化前必须先f_mount(x,x,1)挂载，即必须用读写方式挂载; 如果SD卡已格式化，f_mkfs()的第2个参数，不能用0自动，必须指定某个文件系统。
        if (f_res == FR_OK)                                             // 格式化 成功
        {
            printf("SD卡格式化：成功 \r\n");
            f_res = f_mount(NULL, "0:", 1);     // 格式化后，先取消挂载
            f_res = f_mount(&myFatFs, "0:", 1); // 重新挂载
            if (f_res == FR_OK)
                printf("FatFs 挂载成功 \r\n"); // 挂载成功
            else
                return; // 挂载失败，退出函数
        }
        else
        {
            printf("SD卡格式化：失败 \r\n"); // 格式化 失败
            return;
        }
    }
    else if (f_res != FR_OK) // 挂载异常
    {
        printf("FatFs 挂载异常: %d; 检查MX_SDIO_SD_Init()是否已修改1B\r", f_res);
        return;
    }
    else // 挂载成功
    {
        if (myFatFs.fs_type == 0x03) // FAT32; 1-FAT12、2-FAT16、3-FAT32、4-exFat
            printf("SD卡已有文件系统：FAT32\n");
        if (myFatFs.fs_type == 0x04) // exFAT; 1-FAT12、2-FAT16、3-FAT32、4-exFat
            printf("SD卡已有文件系统：exFAT\n");
        printf("FatFs 挂载成功 \r\n"); // 挂载成功
    }

    // 2、写入测试：打开或创建文件，并写入数据
    printf("\r\n");
    printf("2、写入测试：打开或创建文件，并写入数据 ****** \r\n");
    f_res = f_open(&myFile, "0:text2.txt", FA_CREATE_ALWAYS | FA_WRITE); // 打开文件; 参数：要操作的文件对象、路径和文件名称、打开模式;
    if (f_res == FR_OK)
    {
        printf("打开文件 成功 \r\n");
        printf("写入测试：");
        f_res = f_write(&myFile, aWriteBuf, sizeof(aWriteBuf), &num); // 向文件内写入数据; 参数：文件对象、数据缓存、申请写入的字节数、实际写入的字节数
        if (f_res == FR_OK)
        {
            printf("写入成功  \r\n");
            printf("已写入字节数：%d \r\n", num);       // printf 写入的字节数
            printf("已写入的数据：%s \r\n", aWriteBuf); // printf 写入的数据; 注意，这里以字符串方式显示，如果数据是非ASCII可显示范围，则无法显示
        }
        else
        {
            printf("写入失败 \r\n");            // 写入失败
            printf("错误编号： %d\r\n", f_res); // printf 错误编号
        }
        f_close(&myFile); // 不再读写，关闭文件
    }
    else
    {
        printf("打开文件 失败: %d\r\n", f_res);
    }

    // 3、读取测试：打开已有文件，读取其数据
    printf("3、读取测试：打开刚才的文件，读取其数据 ****** \r\n");
    f_res = f_open(&myFile, "0:text2.txt", FA_OPEN_EXISTING | FA_READ); // 打开文件; 参数：文件对象、路径和名称、操作模式; FA_OPEN_EXISTING：只打开已存在的文件; FA_READ: 以只读的方式打开文件
    if (f_res == FR_OK)
    {
        printf("打开文件 成功 \r\n");
        f_res = f_read(&myFile, aReadData, sizeof(aReadData), &num); // 从文件中读取数据; 参数：文件对象、数据缓冲区、请求读取的最大字节数、实际读取的字节数
        if (f_res == FR_OK)
        {
            printf("读取数据 成功 \r\n");
            printf("已读取字节数：%d \r\n", num);      // printf 实际读取的字节数
            printf("读取到的数据：%s\r\n", aReadData); // printf 实际数据; 注意，这里以字符串方式显示，如果数据是非ASCII可显示范围，则无法显示
        }
        else
        {
            printf("读取 失败  \r\n");          // printf 读取失败
            printf("错误编号：%d \r\n", f_res); // printf 错误编号
        }
    }
    else
    {
        printf("打开文件 失败 \r\n");      // printf 打开文件 失败
        printf("错误编号：%d\r\n", f_res); // printf 错误编号
    }

    f_close(&myFile);       // 不再读写，关闭文件
    f_mount(NULL, "0:", 1); // 不再使用文件系统，取消挂载文件系统
}

// 获取SD卡信息
// 注意: 本函数需要在f_mount()执行后再调用，因为CubeMX生成的FatFs代码, 会在f_mount()函数内对SD卡进行初始化
void SDCardInfo(void)
{
    HAL_SD_CardInfoTypeDef pCardInfo = {0};     // SD卡信息结构体
    uint8_t status = HAL_SD_GetCardState(&hsd); // SD卡状态标志值
    if (status == HAL_SD_CARD_TRANSFER)
    {
        HAL_SD_GetCardInfo(&hsd, &pCardInfo); // 获取 SD 卡的信息
        printf("\r\n");
        printf("*** 获取SD卡信息 *** \r\n");
        printf("卡类型：%d \r\n", pCardInfo.CardType);                                                           // 类型返回：0-SDSC、1-SDHC/SDXC、3-SECURED
        printf("卡版本：%d \r\n", pCardInfo.CardVersion);                                                        // 版本返回：0-CARD_V1、1-CARD_V2
        printf("块数量：%d \r\n", pCardInfo.BlockNbr);                                                           // 可用的块数量
        printf("块大小：%d \r\n", pCardInfo.BlockSize);                                                          // 每个块的大小; 单位：字节
        printf("卡容量：%lluG \r\n", ((uint64_t)pCardInfo.BlockSize * pCardInfo.BlockNbr) / 1024 / 1024 / 1024); // 计算卡的容量; 单位：GB
    }
}
#endif
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
#ifdef SDTEST
    SDCard_ShowInfo();
    HAL_Delay(500);
    FatFsTest();
    SDCardInfo();
    HAL_Delay(HAL_MAX_DELAY);
#endif
#ifdef WRITEMODE
    if (at24_isConnected())
    {
        at24_eraseChip();
        uint16_t tmp = 5;
        UserInfo users[] = {{23125011044, "张三"},
                            {23125011045, "李四"},
                            {23125011046, "王五"},
                            {23125011047, "赵六"},
                            {23125011048, "钱七"}};
        CheckInfo checks[] = {{23125011044, 569992346941980672, 569992346958757888},
                              {23125011045, 569992346942046208, 569992346958823424},
                              {23125011046, 569992346942111744, 569992346958888960},
                              {23125011047, 569992346942177280, 569992346958954496},
                              {23125011048, 569992346942242816, 569992346959020032}};

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
#ifndef SDTEST
    delay_init(100);
    LCD_Init();
    LCD_direction(3);
    ds3231Init();
    at24Init();
    TP_Init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    myEventInit(&guider_ui);
    myLVGL_UIInit();
    PCD_Init();
    //  lv_demo_benchmark();
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        // loop();
        lv_task_handler();
        RC522Scan();
        HAL_Delay(1);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
#endif
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
