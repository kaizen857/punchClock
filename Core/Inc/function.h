#ifndef __AFUNCTION_H__
#define __AFUNCTION_H__

#include "Status.h"
#include <stdint.h>
#include "dataStruct.h"
#include "gui_guider.h"
#include "i2c.h"
#include "lcd.h"
#include "touch.h"
#include "RC522.h"
#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "DS3231.h"
#include <stdbool.h>
#include "at24cxx.h"
#include "main.h"
#include "adc.h"

#define DEBUG

// 时间格式
typedef struct Time
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} Time;

typedef struct CheckInfoHashNode
{
    uint64_t cardID;
    uint64_t startTime;
} CheckInfoHashNode;

extern Time nowTime;

int16_t calculate_weekday(int16_t year, int16_t month, int16_t day); // 计算星期几
void ds3231Init(void);                                               // DS3231上电检查

void RC522Scan(void);                       // RC522读卡
uint8_t RC522WriteCard(uint8_t *Card_Data); // RC522写卡

void at24Init(void); // AT24初始化

void LD2410BInit(void); // LD2410B初始化

void setTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute); // 设置ds3231时间
void getTime(Time *time); // 获取ds3231时间

// 导出数据到SD卡
uint8_t exportData(void);

uint16_t calculateCRC16(const uint8_t *data, int length); // CRC校验

void totalInit(void); // 系统初始化

bool writeUserInfo(UserInfo *userInfo);    // 写入用户信息
bool writeCheckInfo(CheckInfo *checkInfo); // 写入打卡信息

void initUserInfoTable(lv_ui *ui);   // 初始化用户信息表
void updateUserInfoTable(lv_ui *ui); // 更新用户信息表

bool updateUserInfoList(UserInfo *user); // 更新内存中的用户信息列表

bool initCheckInfoTable(lv_ui *ui);                    // 初始化打卡信息表
bool updateCheckInfoTable(lv_ui *ui, CheckInfo *info); // 更新打卡信息表

bool hasChecking(uint64_t cardID);                   // 查找打卡信息
void newCheck(uint64_t cardID, uint64_t startTime);  // 新的打卡
bool finishCheck(uint64_t cardID, uint64_t endTime); // 完成打卡

#endif