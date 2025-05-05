#include "function.h"
#include "at24cxx.h"
#include "dataStruct.h"
#include "gui_guider.h"
#include "lcd.h"
#include "RC522/RC522.h"
#include "Status.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_it.h"
#include "usart.h"
#include "lvgl.h"
#include "main.h"
#include <stdint.h>

uint16_t totalUserNum = 0;
uint16_t totalCheckNum = 0;
UserInfo *userList = NULL;
CheckInfo *checkList = NULL;

Status status = {0};
Time nowTime = {0};
uint8_t photostatus = 0;

// 计算星期
int16_t calculate_weekday(int16_t year, int16_t month, int16_t day)
{
    // 调整月份和年份（1月和2月视为上一年的13月和14月）
    if (month < 3)
    {
        month += 12;
        year--;
    }
    int16_t q = day;
    int16_t m = month;
    int16_t K = year % 100; // 年份后两位
    int16_t J = year / 100; // 世纪部分

    // 蔡勒公式计算星期几（0=星期六, 1=星期日, ..., 6=星期五）
    int16_t h = (q + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    // 转换为0=星期日到6=星期六
    h = (h + 6) % 7;
    return h;
}

// DS3231上电检查
void ds3231Init(void)
{
    DS3231_Init(&hi2c2);
    uint16_t year = DS3231_GetYear();
    uint8_t month = DS3231_GetMonth();
    uint8_t day = DS3231_GetDate();
    uint8_t hour = DS3231_GetHour();
    uint8_t minute = DS3231_GetMinute();
    uint8_t second = DS3231_GetSecond();
    if (year == 2000 && month == 1 && day == 1 && hour == 0 && minute == 0 && second == 0)
    {
        status.mode = DS3231RESET; // 掉电重启
    }
    else // 正常启动
    {
        status.mode = OK;
        nowTime.year = year;
        nowTime.month = month;
        nowTime.day = day;
        nowTime.hour = hour;
        nowTime.minute = minute;
        nowTime.second = second;
    }
}

// RC522扫描卡
void RC522Scan(void)
{
    uint8_t Card_Type1[2];
    uint8_t Card_ID[4];
    uint8_t Card_KEY[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; //{0x11,0x11,0x11,0x11,0x11,0x11};   //密码
    uint8_t Card_Data[16];
    uint8_t status;
    if (PcdRequest(0x26, Card_Type1) == MI_OK) // 寻卡
    {
        status = PcdAnticoll(Card_ID); // 防冲撞

        if (status == MI_OK)
        {
#ifdef DEBUG
            printf("Serial Number:%02X%02X%02X%02X\r\n", Card_ID[0], Card_ID[1], Card_ID[2], Card_ID[3]); // 打印卡号
#endif
        }
        else
        {
#ifdef DEBUG
            printf("Anticoll Error\r\n");
#endif
            return;
        }

        status = PcdSelect(Card_ID); // 选卡

        if (status != MI_OK)
        {
#ifdef DEBUG
            printf("Select Card Error\r\n");
#endif
            return;
        }

        status = PcdAuthState(PICC_AUTHENT1A, 5, Card_KEY, Card_ID); // 验证密码
        if (status != MI_OK)
        {
#ifdef DEBUG
            printf("Auth Error\r\n");
#endif
            return;
        }
        status = PcdRead(6, Card_Data); // 读数据
        if (status != MI_OK)
        {
#ifdef DEBUG
            printf("Read Error\r\n");
#endif
            return;
        }
        else
        {
            // TODO:处理学号以及校验码
        }
        status = PcdHalt(); // 停止卡片
        return;
    }
    else
    {
#ifdef DEBUG
        printf("No Card\r\n");
#endif
        return;
    }
}

// RC522写卡
void RC522WriteCard(uint8_t *Card_Data)
{
    uint8_t Card_Type1[2];
    uint8_t Card_ID[4];
    uint8_t Card_KEY[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; //{0x11,0x11,0x11,0x11,0x11,0x11};   //密码
    uint8_t status;
    if (PcdRequest(0x26, Card_Type1) == MI_OK) // 寻卡
    {
        status = PcdAnticoll(Card_ID); // 防冲撞

        if (status == MI_OK)
        {
#ifdef DEBUG
            printf("Serial Number:%02X%02X%02X%02X\r\n", Card_ID[0], Card_ID[1], Card_ID[2], Card_ID[3]); // 打印卡号
#endif
        }
        else
        {
#ifdef DEBUG
            printf("Anticoll Error\r\n");
#endif
            return;
        }

        status = PcdSelect(Card_ID); // 选卡

        if (status != MI_OK)
        {
#ifdef DEBUG
            printf("Select Card Error\r\n");
#endif
            return;
        }

        status = PcdAuthState(PICC_AUTHENT1A, 5, Card_KEY, Card_ID); // 验证密码
        if (status != MI_OK)
        {
#ifdef DEBUG
            printf("Auth Error\r\n");
#endif
            return;
        }
        status = PcdWrite(6, Card_Data); // 写数据
        if (status != MI_OK)
        {
#ifdef DEBUG
            printf("Write Error\r\n");
#endif
            return;
        }
        else
        {
#ifdef DEBUG
            printf("Write Success\r\n");
#endif
        }
        status = PcdHalt(); // 停止卡片
        return;
    }
    else
    {
#ifdef DEBUG
        printf("No Card\r\n");
#endif
        return;
    }
}

// AT24初始化
void at24Init(void)
{
    if (at24_isConnected())
    {
        // 人员信息
        at24_read(USER_INFO_LEN_ADDR, (uint8_t *)&totalUserNum, 2, 1000);
        if (totalUserNum > 600) // 设计上到不了600，故这边可以用来判断数值是否有效
        {
            totalUserNum = 0;
            userList = (UserInfo *)malloc(sizeof(UserInfo) * totalUserNum + 1);
        }
        else
        {
            userList = (UserInfo *)malloc(sizeof(UserInfo) * totalUserNum);
            if (userList != NULL)
            {
                at24_read(USER_INFO_ADDR, (uint8_t *)userList, sizeof(UserInfo) * totalUserNum, HAL_MAX_DELAY);
            }
            else
            {
                // TODO:处理malloc失败
                HardFault_Handler();
            }
        }

        // 打卡记录条数
        at24_read(CHECK_INFO_LEN_ADDR, (uint8_t *)&totalCheckNum, 2, HAL_MAX_DELAY);
        if (totalCheckNum > 3000)
        {
            totalCheckNum = 0;
        }
        status.mode = OK;
    }
    else
    {
        status.mode = AT24ERROR;
    }
    return;
}

void LD2410BInit(void)
{
    // TODO:LD2410初始化
}

// 更新系统时间
void updateTime(void)
{
    nowTime.second = DS3231_GetSecond();
    nowTime.minute = DS3231_GetMinute();
    nowTime.hour = DS3231_GetHour();
    nowTime.day = DS3231_GetDate();
    nowTime.month = DS3231_GetMonth();
    nowTime.year = DS3231_GetYear();
}

// 设置DS3231时间
void setTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute)
{
    int16_t weekday = calculate_weekday(year, month, day);
    DS3231_SetFullDate(day, month, weekday, year);

    DS3231_SetFullTime(hour, minute, 0);
}

// RC522测试函数
void RC522Test()
{
    uint8_t Card_Type1[2];
    uint8_t Card_ID[4];
    uint8_t Card_KEY[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; //{0x11,0x11,0x11,0x11,0x11,0x11};   //密码
    uint8_t Card_Data[16];
    uint8_t status;
    uint8_t i;
    Card_Type1[0] = 0x04;
    Card_Type1[1] = 0x00;
    RC522_Init();
    printf("---------------------------------------\r\n");
    HAL_Delay(10);
    if (MI_OK == PcdRequest(0x26, Card_Type1)) // 寻卡函数，如果成功返回MI_OK   打印1次卡�???
    {
        uint16_t cardType = (Card_Type1[0] << 8) | Card_Type1[1]; // 读不同卡的类�???
        printf("卡类型：(0x%04X)\r\n", cardType);                 //"Card Type(0x%04X):"
        switch (cardType)
        {
        case 0x4400:
            printf("Mifare UltraLight\r\n");
            break;
        case 0x0400:
            printf("Mifare One(S50)\r\n");
            break;
        case 0x0200:
            printf("Mifare One(S70)\r\n");
            break;
        case 0x0800:
            printf("Mifare Pro(X)\r\n");
            break;
        case 0x4403:
            printf("Mifare DESFire\r\n");
            break;
        default:
            printf("Unknown Card\r\n");
            break;
        }

        status = PcdAnticoll(Card_ID); // 防冲�??? 如果成功返回MI_OK
        if (status != MI_OK)
        {
            printf("Anticoll Error\r\n");
        }
        else
        {
            printf("Serial Number:%02X%02X%02X%02X\r\n", Card_ID[0], Card_ID[1], Card_ID[2], Card_ID[3]);
        }

        status = PcdSelect(Card_ID); // 选卡 如果成功返回MI_OK
        if (status != MI_OK)
        {
            printf("Select Card Error\r\n");
        }
        else
            printf("Select Card OK\r\n");

        status = PcdAuthState(PICC_AUTHENT1A, 5, Card_KEY, Card_ID); //
        if (status != MI_OK)
        {
            printf("Auth State Error\r\n");
            return;
        }

        memset(Card_ID, 1, 4);
        memset(Card_Data, 1, 16);
        Card_Data[0] = 0xaa;
        status = PcdWrite(6, Card_Data); // 写入数据
        if (status != MI_OK)
        {
            printf("Card Write Error\r\n");
            return;
        }
        memset(Card_Data, 0, 16); // 清零
        delay_us(8);

        status = PcdRead(6, Card_Data); // 读取我们写入的数据
        if (status != MI_OK)
        {
            printf("Card Read Error\r\n");
            return;
        }
        else
        {
            for (i = 0; i < 16; i++)
            {
                printf("%02X ", Card_Data[i]);
            }
            printf("\r\n");
        }

        memset(Card_Data, 0, 16);
        PcdHalt(); // 卡片进入休眠

        status = PcdHalt(); // 卡片进入休眠状�??
        if (status != MI_OK)
        {
            printf("PcdHalt Error\r\n");
        }
        else
        {
            printf("PcdHalt OK\r\n");
        }
    }
}

// 总初始化函数
void totalInit(void)
{
    delay_init(100);
    LCD_Init();         // 初始化LCD
    if (TP_Init() == 1) // 初始化触摸屏
    {
        status.mode = TOUCHERROR;
    }
    LCD_direction(1); // 设置LCD方向
    LCD_Clear(BLACK);
    POINT_COLOR = WHITE;
    BACK_COLOR = BLACK;
    ds3231Init(); // 初始化DS3231
    at24Init();   // 初始化AT24C512
    // 初始化sdio

    // 初始化ld2410b

    status.mode = NORMALMOD;
}

bool writeUserInfo(UserInfo *userInfo)
{
    // 向EEPROM中写入用户信息

    // 计算写入地址
    uint32_t addr = USER_INFO_ADDR + (uint32_t)totalUserNum * sizeof(UserInfo);
    if (addr + sizeof(UserInfo) > EEPROM_MAX_ADDRESS)
    {
        return false;
    }
    // 入用户数据
    if (!at24_write(addr, (uint8_t *)userInfo, sizeof(UserInfo), 1000))
    {
        return false;
    }

    // 更新用户计数
    uint16_t newTotal = totalUserNum + 1;
    if (!at24_write(USER_INFO_LEN_ADDR, (uint8_t *)&newTotal, sizeof(newTotal), 1000))
    {
        // 写入失败，尝试回滚用户数据
        UserInfo empty = {0};
        at24_write(addr, (uint8_t *)&empty, sizeof(UserInfo), 1000);
        return false;
    }
    // 更新内存中的计数
    totalUserNum = newTotal;
    return true;
}

void updateUserInfoTable(lv_ui *ui)
{
    lv_table_set_column_count(ui->MainMenuScreen_UserInfoTable, 2);
    lv_table_set_row_count(ui->MainMenuScreen_UserInfoTable, totalUserNum + 1);
    lv_table_set_cell_value(ui->MainMenuScreen_UserInfoTable, 0, 0, "姓名");

    lv_table_set_cell_value(ui->MainMenuScreen_UserInfoTable, 0, 1, "学号");
    char buffer[21];
    for (int i = 0; i < totalUserNum; i++)
    {
        snprintf(buffer, sizeof(buffer), "%" PRIu64, userList[i].ID);
        lv_table_set_cell_value(ui->MainMenuScreen_UserInfoTable, i + 1, 0, userList[i].Name);
        lv_table_set_cell_value(ui->MainMenuScreen_UserInfoTable, i + 1, 1, buffer);
    }
}

bool updateUserInfoList(UserInfo *user)
{
    if (user == NULL)
    {
        return false;
    }
    UserInfo *newUserList = (UserInfo *)malloc(sizeof(UserInfo) * (totalUserNum));
    if (newUserList == NULL)
    {
        return false;
    }
    if (userList != NULL && (totalUserNum - 1) > 0)
    {
        memcpy(newUserList, userList, sizeof(UserInfo) * (totalUserNum - 1));
    }
    memcpy(&newUserList[totalUserNum - 1], user, sizeof(UserInfo));
    if (userList != NULL)
    {
        free(userList);
    }
    userList = newUserList;
    return true;
    // memcpy(newUserList, userList, sizeof(UserInfo) * (totalUserNum - 1));
}