#include "function.h"
#include "at24cxx.h"
#include "dataStruct.h"
#include "gui_guider.h"
#include "label/lv_label.h"
#include "lcd.h"
#include "RC522/RC522.h"
#include "Status.h"
#include "lv_types.h"
#include "lv_utils.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_it.h"
#include "table/lv_table.h"
#include "usart.h"
#include "lvgl.h"
#include "main.h"
#include <stdint.h>
#include <string.h>
#include "hashmap.h"
#include "stdlib.h"

uint16_t totalUserNum = 0;
uint16_t totalCheckNum = 0;
UserInfo *userList = NULL;
CheckInfo *checkList = NULL;
#define DEBUG

Time nowTime = {0};

int myCompare(const void *a, const void *b, void *udata)
{
    const CheckInfoHashNode *itemA = a;
    const CheckInfoHashNode *itemB = b;
    return itemA->cardID - itemB->cardID;
}
uint64_t myHash(const void *Item, uint64_t seed0, uint64_t seed1)
{
    const CheckInfoHashNode *itemA = Item;
    return hashmap_sip(&itemA->cardID, sizeof(uint64_t), seed0, seed1);
}

struct hashmap *checkingMap = NULL;

// 计算星期
int16_t
calculate_weekday(int16_t year, int16_t month, int16_t day)
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
    }
    else // 正常启动
    {
        nowTime.year = year;
        nowTime.month = month;
        nowTime.day = day;
        nowTime.hour = hour;
        nowTime.minute = minute;
        nowTime.second = second;
    }
}

int compareUserInfo(const void *a, const void *b)
{
    const UserInfo *itemA = a;
    const UserInfo *itemB = b;
    return itemA->ID - itemB->ID;
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
        // 对记录排序
        qsort(userList, totalUserNum, sizeof(UserInfo), compareUserInfo);

        // 打卡记录条数
        at24_read(CHECK_INFO_LEN_ADDR, (uint8_t *)&totalCheckNum, 2, HAL_MAX_DELAY);
        if (totalCheckNum > 3000)
        {
            totalCheckNum = 0;
        }
    }
    else
    {
    }
    return;
}

void getTime(Time *time)
{
    if (time == NULL)
    {
        return;
    }
    (*time).year = DS3231_GetYear();
    (*time).month = DS3231_GetMonth();
    (*time).day = DS3231_GetDate();
    (*time).hour = DS3231_GetHour();
    (*time).minute = DS3231_GetMinute();
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

// 总初始化函数
void totalInit(void)
{
    delay_init(100);
    LCD_Init();         // 初始化LCD
    if (TP_Init() == 1) // 初始化触摸屏
    {
    }
    LCD_direction(1); // 设置LCD方向
    LCD_Clear(BLACK);
    POINT_COLOR = WHITE;
    BACK_COLOR = BLACK;
    ds3231Init(); // 初始化DS3231
    at24Init();   // 初始化AT24C512
    // 初始化sdio

    // 初始化ld2410b
}
/**
 * @brief       向EEPROM中写入用户信息
 *
 * @param userInfo 用户信息
 * @return true    写入成功
 * @return false   写入失败
 */
bool writeUserInfo(UserInfo *userInfo)
{
    // 向EEPROM中写入用户信息

    // 计算写入地址
    uint32_t addr = USER_INFO_ADDR + (uint32_t)totalUserNum * sizeof(UserInfo);
    if (addr + sizeof(UserInfo) > EEPROM_MAX_ADDRESS)
    {
        return false;
    }
    // 写入用户数据
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
#ifdef DEBUG
    printf("写入用户信息成功\n");
    printf("总人数:%d", totalUserNum);
#endif
    return true;
}

bool writeCheckInfo(CheckInfo *checkInfo)
{
    if (checkInfo == NULL)
    {
        return false;
    }
    // 计算写入地址
    uint32_t addr = CHECK_INFO_ADDR + (uint32_t)totalCheckNum * sizeof(CheckInfo);
    if (addr + sizeof(CheckInfo) > EEPROM_MAX_ADDRESS)
    {
        return false;
    }
    else
    {
        if (!at24_write(addr, (uint8_t *)checkInfo, sizeof(CheckInfo), 1000))
        {
            return false;
        }
        uint16_t newTotal = totalCheckNum + 1;
        if (!at24_write(CHECK_INFO_LEN_ADDR, (uint8_t *)&newTotal, sizeof(newTotal), 1000))
        {
            CheckInfo empty = {0};
            at24_write(addr, (uint8_t *)&empty, sizeof(CheckInfo), 1000);
            return false;
        }
        totalCheckNum = newTotal;
        return true;
    }
}
/**
 * @brief      初始化UI上的用户信息表格
 *
 * @param ui       UI界面
 */
void initUserInfoTable(lv_ui *ui)
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
/**
 * @brief      更新UI上的用户信息表格
 *
 * @param ui     UI界面
 */
void updateUserInfoTable(lv_ui *ui)
{
    lv_table_set_row_count(ui->MainMenuScreen_UserInfoTable, totalUserNum + 1);
    char buffer[21];
    snprintf(buffer, sizeof(buffer), "%" PRIu64, userList[totalUserNum - 1].ID);
    lv_table_set_cell_value(ui->MainMenuScreen_UserInfoTable, totalUserNum, 0, userList[totalUserNum - 1].Name);
    lv_table_set_cell_value(ui->MainMenuScreen_UserInfoTable, totalUserNum, 1, buffer);
}
/**
 * @brief    添加用户信息到运存中缓存的用户信息列表
 *
 * @param user      新增的用户信息
 * @return true     添加用户信息成功
 * @return false    添加用户信息成功
 */
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
        memmove(newUserList, userList, sizeof(UserInfo) * (totalUserNum - 1));
    }
    memcpy(&newUserList[totalUserNum - 1], user, sizeof(UserInfo));
    if (userList != NULL)
    {
        free(userList);
    }
    userList = newUserList;
    qsort(userList, totalUserNum, sizeof(UserInfo), compareUserInfo);
    return true;
    // memcpy(newUserList, userList, sizeof(UserInfo) * (totalUserNum - 1));
}
/**
 * @brief     从EEPROM中读取打卡记录到UI中打卡记录的列表
 *
 * @param ui         UI界面
 * @return true      读取打卡记录成功
 * @return false     读取打卡记录失败
 */
bool initCheckInfoTable(lv_ui *ui)
{
    if (totalCheckNum == 0)
    {
        return true;
    }
    lv_table_set_row_count(ui->MainMenuScreen_table_2, totalCheckNum + 1);
    CheckInfo info;
    uint16_t addr = CHECK_INFO_ADDR;
    char buffer[30];
    for (int i = 0; i < totalCheckNum; i++)
    {
        if (at24_read(addr, (uint8_t *)&info, sizeof(info), 1000))
        {
            // snprintf(buffer, sizeof(buffer), "%" PRIu64, info.ID);
            // lv_table_set_cell_value(ui->MainMenuScreen_table_2, i + 1, 0, buffer);
            UserInfo *user = bsearch(&(UserInfo){.ID = info.ID}, userList, totalUserNum, sizeof(UserInfo), compareUserInfo);
            lv_table_set_cell_value(ui->MainMenuScreen_table_2, i + 1, 0, user->Name);
            uint8_t month = (uint8_t)(info.startTime >> 40);
            uint8_t day = (uint8_t)(info.startTime >> 32);
            uint8_t hour = (uint8_t)(info.startTime >> 24);
            uint8_t minute = (uint8_t)(info.startTime >> 16);
            snprintf(buffer, sizeof(buffer), "%02d月%02d日%02d:%02d", month, day, hour, minute);
            lv_table_set_cell_value(ui->MainMenuScreen_table_2, i + 1, 1, buffer);
            month = (uint8_t)(info.endTime >> 40);
            day = (uint8_t)(info.endTime >> 32);
            hour = (uint8_t)(info.endTime >> 24);
            minute = (uint8_t)(info.endTime >> 16);
            snprintf(buffer, sizeof(buffer), "%02d月%02d日%02d:%02d", month, day, hour, minute);
            lv_table_set_cell_value(ui->MainMenuScreen_table_2, i + 1, 2, buffer);
            addr += sizeof(info);
        }
        else
        {
            return false;
        }
    }
    return true;
}
/**
 * @brief        更新UI中的打卡记录表
 *
 * @param ui     UI界面
 * @param info   打卡记录
 * @return true  更新成功
 * @return false 更新失败
 */
bool updateCheckInfoTable(lv_ui *ui, CheckInfo *info)
{
    if (totalCheckNum == 0)
    {
        return true;
    }
    uint16_t row = lv_table_get_row_count(ui->MainMenuScreen_table_2);
    uint16_t addRow = totalCheckNum - row + 1;
    if (likely(addRow > 0))
    {
        char buffer[30];
        lv_table_set_row_count(ui->MainMenuScreen_table_2, totalCheckNum + 1);

        UserInfo *user = bsearch(&(UserInfo){.ID = info->ID}, userList, totalUserNum, sizeof(UserInfo), compareUserInfo);
        lv_table_set_cell_value(ui->MainMenuScreen_table_2, totalCheckNum, 0, user->Name);

        uint8_t month = (uint8_t)(info->startTime >> 40);
        uint8_t day = (uint8_t)(info->startTime >> 32);
        uint8_t hour = (uint8_t)(info->startTime >> 24);
        uint8_t minute = (uint8_t)(info->startTime >> 16);
        snprintf(buffer, sizeof(buffer), "%02d月%02d日%02d:%02d", month, day, hour, minute);
        lv_table_set_cell_value(ui->MainMenuScreen_table_2, totalCheckNum, 1, buffer);
        month = (uint8_t)(info->endTime >> 40);
        day = (uint8_t)(info->endTime >> 32);
        hour = (uint8_t)(info->endTime >> 24);
        minute = (uint8_t)(info->endTime >> 16);
        snprintf(buffer, sizeof(buffer), "%02d月%02d日%02d:%02d", month, day, hour, minute);
        lv_table_set_cell_value(ui->MainMenuScreen_table_2, totalCheckNum, 2, buffer);
        return true;
    }
    else
    {
        return false;
    }
}

uint16_t calculateCRC16(const uint8_t *data, int length)
{
    uint16_t crc = 0xFFFF;
    while (length--)
    {
        crc ^= *data++;
        for (int i = 0; i < 8; i++)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ 0xA001; // 0xA001 是 CRC16 多项式
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

int comparUser(const void *a, const void *b)
{
    return ((UserInfo *)a)->ID - ((UserInfo *)b)->ID;
}

static uint8_t KEY_A[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static uint8_t KEY_B[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static uint16_t counttt = 0;
void RC522Scan(void)
{
    counttt++;
    if ((counttt % 500) == 0)
    {
        counttt = 0;
        static uint8_t readUid[5]; // 卡号
        static uint8_t CT[3];      // 卡类型
        uint8_t status = PCD_Request(0x52, CT);
        if (!status)
        {
            status = PCD_ERR;
            status = PCD_Anticoll(readUid); // 防冲撞
        }
        if (!status)
        {
            status = PCD_ERR;
            status = PCD_Select(readUid); // 选卡
        }
        if (!status)
        {
            status = PCD_ERR;
            // 验证A密钥 块地址 密码 SN
            status = PCD_AuthState(PICC_AUTHENT1A, 4, KEY_A, readUid);
            if (status == PCD_OK) // 验证A成功
            {
#ifdef DEBUG
                printf("A密钥验证成功\r\n");
#endif
            }
            else
            {
#ifdef DEBUG
                printf("A密钥验证失败\r\n");
#endif
                lv_label_set_text(guider_ui.MainMenuScreen_label_8, "卡片密钥验证失败!");
                lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
            }

            // 验证B密钥 块地址 密码 SN
            status = PCD_AuthState(PICC_AUTHENT1B, 4, KEY_B, readUid);
            if (status == PCD_OK) // 验证B成功
            {
#ifdef DEBUG
                printf("B密钥验证成功\r\n");
#endif
            }
            else
            {
#ifdef DEBUG
                printf("B密钥验证失败\r\n");
#endif
                lv_label_set_text(guider_ui.MainMenuScreen_label_8, "卡片密钥验证失败!");
                lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
            }
        }
        if (status == PCD_OK)
        {
            uint8_t DATA[16];
            status = PCD_ERR;
            status = PCD_ReadBlock(4, DATA);
            if (status == PCD_OK)
            {
                uint16_t crc = calculateCRC16(DATA, 8);
                if (crc == (DATA[9] << 8 | DATA[10]))
                {
                    // CRC校验通过
                    // TODO:处理打卡事件
                    uint64_t cardID = 0;
                    memcpy(&cardID, DATA, 8);
                    UserInfo tmp = {.ID = cardID};
                    // 查找该学号是否为有效学号（二分查找）
                    if (likely(bsearch(&tmp, userList, totalUserNum, sizeof(UserInfo), comparUser) != NULL))
                    { // 学号有效
                      // 查询是否存在该学号的打卡记录
                        if (hasChecking(cardID))
                        {
                            Time nowtime;
                            getTime(&nowtime);
                            uint64_t endTime = (uint64_t)nowtime.year << 48 | (uint64_t)nowtime.month << 40 | (uint64_t)nowtime.day << 32 | (uint64_t)nowtime.hour << 24 | (uint64_t)nowtime.minute << 16;
                            if (finishCheck(cardID, endTime))
                            {
                                lv_label_set_text(guider_ui.MainMenuScreen_label_8, "签退成功!");
                                lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
                            }
                            else
                            {
                                lv_label_set_text(guider_ui.MainMenuScreen_label_8, "签退失败!\n请重试!");
                                lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
                            }
                        }
                        else
                        {
                            Time nowtime;
                            getTime(&nowtime);
                            uint64_t startTime = (uint64_t)nowtime.year << 48 | (uint64_t)nowtime.month << 40 | (uint64_t)nowtime.day << 32 | (uint64_t)nowtime.hour << 24 | (uint64_t)nowtime.minute << 16;
                            newCheck(cardID, startTime);
                            lv_label_set_text(guider_ui.MainMenuScreen_label_8, "签到成功!");
                            lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
                        }
                    }
                    else
                    {
                        lv_label_set_text(guider_ui.MainMenuScreen_label_8, "无效卡片!");
                        lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
                    }

                    // lv_label_set_text(guider_ui.MainMenuScreen_label_8, "打卡成功!");
                    // lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
                }
                else
                {
                    // CRC校验失败
                    lv_label_set_text(guider_ui.MainMenuScreen_label_8, "卡片CRC校验失败!");
                    lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
                }
            }
        }
    }
}
/**
 * @brief 向卡片写入用户ID信息
 *
 * @param Card_Data 16字节用户ID信息
 * @return uint8_t 写入状态
 */
uint8_t RC522WriteCard(uint8_t *Card_Data)
{
    uint8_t CT[3];      // 卡类型
    uint8_t readUid[5]; // 卡号
    uint8_t status = PCD_Request(0x52, CT);
    if (!status)
    {
        status = PCD_ERR;
        status = PCD_Anticoll(readUid); // 防冲撞
    }
    if (!status)
    {
        status = PCD_ERR;
        status = PCD_Select(readUid); // 选卡
    }
    if (!status)
    {
        status = PCD_ERR;
        // 验证A密钥 块地址 密码 SN
        status = PCD_AuthState(PICC_AUTHENT1A, 4, KEY_A, readUid);
        if (status == PCD_OK) // 验证A成功
        {
            printf("A密钥验证成功\r\n");
            // HAL_Delay(1000);
        }
        else
        {
            printf("A密钥验证失败\r\n");
            // HAL_Delay(1000);
        }

        // 验证B密钥 块地址 密码 SN
        status = PCD_AuthState(PICC_AUTHENT1B, 4, KEY_B, readUid);
        if (status == PCD_OK) // 验证B成功
        {
            printf("B密钥验证成功\r\n");
        }
        else
        {
            printf("B密钥验证失败\r\n");
        }
        if (status == PCD_OK)
        {
            // TODO:写卡
            status = PCD_ERR;
            status = PCD_WriteBlock(4, Card_Data); // 写数据
            if (status == PCD_OK)
            {
#ifdef DEBUG
                printf("写数据成功\r\n");
#endif
                return PCD_OK;
            }
            else
            {
#ifdef DEBUG
                printf("写数据失败\r\n");
#endif
                return PCD_ERR;
            }
        }
    }
    return status;
}

/**
 * @brief 新增一条打卡记录
 *
 * @param cardID  学号
 * @param startTime  开始时间
 */
void newCheck(uint64_t cardID, uint64_t startTime)
{
    if (unlikely(checkingMap == NULL))
    {
        checkingMap = hashmap_new(sizeof(CheckInfoHashNode), 30, 0, 0, myHash, myCompare, NULL, NULL); // 初始化打卡记录哈希表
    }
    CheckInfoHashNode cardIDNode;
    cardIDNode.cardID = cardID;
    cardIDNode.startTime = startTime;
    hashmap_set(checkingMap, &cardIDNode);
}

bool hasChecking(uint64_t cardID)
{
    if (unlikely(checkingMap == NULL))
    {
        return false;
    }
    // 查询是否存在该学号的打卡记录
    return ((hashmap_get(checkingMap, &(CheckInfoHashNode){.cardID = cardID})) != NULL);
}

bool finishCheck(uint64_t cardID, uint64_t endTime)
{
    if (unlikely(checkingMap == NULL))
    {
        return false;
    }
    // 查询是否存在该学号的打卡记录
    CheckInfoHashNode *node = (CheckInfoHashNode *)hashmap_get(checkingMap, &(CheckInfoHashNode){.cardID = cardID});
    if (node != NULL)
    {
        CheckInfo info;
        info.ID = cardID;
        info.startTime = node->startTime;
        info.endTime = endTime;
        if (writeCheckInfo(&info))
        {
            updateCheckInfoTable(&guider_ui, &info);

            hashmap_delete(checkingMap, node);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}