//////////////////////////////////////////////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// 测试硬件：单片机STM32F429IGT6,正点原子Apollo STM32F4/F7开发板,主频180MHZ，晶振12MHZ
// QDtech-TFT液晶驱动 for STM32 IO模拟
// xiao冯@ShenZhen QDtech co.,LTD
// 公司网站:www.qdtft.com
// 淘宝网站：http://qdtech.taobao.com
// wiki技术网站：http://www.lcdwiki.com
// 我司提供技术支持，任何技术问题欢迎随时交流学习
// 固话(传真) :+86 0755-23594567
// 手机:15989313508（冯工）
// 邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
// 技术支持QQ:3002773612  3002778157
// 技术交流QQ群:324828016
// 创建日期:2018/08/09
// 版本：V1.0
// 版权所有，盗版必究。
// Copyright(C) 深圳市全动电子技术有限公司 2018-2028
// All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                STM32单片机
//      VCC          接        DC5V/3.3V      //电源
//      GND          接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI总线
//     LCD模块                STM32单片机
//    SDI(MOSI)      接          PF9          //液晶屏SPI总线数据写信号
//    SDO(MISO)      接          PF8          //液晶屏SPI总线数据读信号，如果不需要读，可以不接线
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 					      STM32单片机
//       LED         接          PD6          //液晶屏背光控制信号，如果不需要控制，接5V或3.3V
//       SCK         接          PF7          //液晶屏SPI总线时钟信号
//     LCD_RS        接          PD5          //液晶屏数据/命令控制信号
//     LCD_RST       接          PD12         //液晶屏复位控制信号
//     LCD_CS        接          PD11         //液晶屏片选控制信号
//=========================================触摸屏触接线=========================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块                STM32单片机
//     CTP_INT       接          PH11         //电容触摸屏中断信号
//     CTP_SDA       接          PI3          //电容触摸屏IIC数据信号
//     CTP_RST       接          PI8          //电容触摸屏复位信号
//     CTP_SCL       接          PH6          //电容触摸屏IIC时钟信号
**************************************************************************************************/
/* @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 **************************************************************************************************/
#ifndef __LCD_H
#define __LCD_H
#include "stdlib.h"
#include "main.h"

// LCD重要参数集
typedef struct
{
    uint16_t width;   // LCD 宽度
    uint16_t height;  // LCD 高度
    uint16_t id;      // LCD ID
    uint8_t dir;      // 横屏还是竖屏控制：0，竖屏；1，横屏。
    uint16_t wramcmd; // 开始写gram指令
    uint16_t rramcmd; // 开始读gram指令
    uint16_t setxcmd; // 设置x坐标指令
    uint16_t setycmd; // 设置y坐标指令
} _lcd_dev;

// LCD参数
extern _lcd_dev lcddev; // 管理LCD重要参数
/////////////////////////////////////用户配置区///////////////////////////////////
#define USE_HORIZONTAL 0 // 定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转

//////////////////////////////////////////////////////////////////////////////////
// 定义LCD的尺寸
#define LCD_W 320
#define LCD_H 480

// TFTLCD部分外要调用的函数
extern uint16_t POINT_COLOR; // 默认红色
extern uint16_t BACK_COLOR;  // 背景颜色.默认为白色

////////////////////////////////////////////////////////////////////
//-----------------LCD端口定义----------------

#define LED BLK_Pin // 背光控制引脚

// QDtech全系列模块采用了三极管控制背光亮灭，用户也可以接PWM调节背光亮度

#define LCD_CS LCD_CS_Pin     // 片选控制引脚
#define LCD_RS LCD_DC_Pin     // 数据/命令控制引脚
#define LCD_RST LCD_RESET_Pin // 复位控制引脚
// 如果使用官方库函数定义下列底层，速度将会下降到14帧每秒，建议采用我司推荐方法
// 以下IO定义直接操作寄存器，快速IO操作，刷屏速率可以达到28帧每秒！
/*  原始定义
#define	LCD_CS_SET  GPIO_TYPE->BSRR=1<<LCD_CS
#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS
#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST


#define	LCD_CS_CLR  GPIO_TYPE->BSRR=(1<<LCD_CS)<<16     //片选端口  	PB11
#define	LCD_RS_CLR	GPIO_TYPE->BSRR=(1<<LCD_RS)<<16     //数据/命令  PB10
#define	LCD_RST_CLR	GPIO_TYPE->BSRR=(1<<LCD_RST)<<16    //复位			  PB12
*/
#define LCD_CS_SET HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define LCD_RS_SET HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)
#define LCD_RST_SET HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET)

#define LCD_CS_CLR HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_RS_CLR HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)
#define LCD_RST_CLR HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET)

// 画笔颜色
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 // 棕色
#define BRRED 0XFC07 // 棕红色
#define GRAY 0X8430  // 灰色
// GUI颜色

#define DARKBLUE 0X01CF  // 深蓝色
#define LIGHTBLUE 0X7D7C // 浅蓝色
#define GRAYBLUE 0X5458  // 灰蓝色
// 以上三色为PANEL的颜色

#define LIGHTGREEN 0X841F // 浅绿色
#define LIGHTGRAY 0XEF5B  // 浅灰色(PANNEL)
#define LGRAY 0XC618      // 浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE 0XA651 // 浅灰蓝色(中间层颜色)
#define LBBLUE 0X2B12    // 浅棕蓝色(选择条目的反色)

void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(uint16_t Color);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x, uint16_t y);     // 画点
uint16_t LCD_ReadPoint(uint16_t x, uint16_t y); // 读点
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);

uint8_t LCD_RD_DATA(void); // 读取LCD数据
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WR_DATA(uint8_t data);
uint8_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);
uint16_t LCD_BGR2RGB(uint16_t c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(uint16_t Data);
void LCD_direction(uint8_t direction);
uint16_t LCD_Read_ID(void);

uint8_t SPI_WriteByte(uint8_t TxData);
// void SPI1_Init(void);
void SPI_SetSpeed(uint8_t SPI_BaudRatePrescaler);

#endif
