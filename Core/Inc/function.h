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

extern Status status;

#define CARDEVENT 1
#define TOUCHEVENT 2

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

extern uint8_t photostatus;

extern Time nowTime;

int16_t calculate_weekday(int16_t year, int16_t month, int16_t day); // 计算星期几
void ds3231Init(void);                                               // DS3231上电检查

void RC522Scan(void);                    // RC522读卡
void RC522WriteCard(uint8_t *Card_Data); // RC522写卡

void at24Init(void); // AT24初始化

void LD2410BInit(void); // LD2410B初始化

void setTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute); // 设置ds3231时间

// 导出数据到SD卡
uint8_t exportData(void);

void totalInit(void); // 系统初始化

void loop(void); // 一帧

bool writeUserInfo(UserInfo *userInfo); // 写入用户信息

void updateUserInfoTable(lv_ui *ui); // 更新用户信息表

bool updateUserInfoList(UserInfo *user);

#endif