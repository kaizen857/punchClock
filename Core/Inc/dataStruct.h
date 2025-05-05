#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

#include <stdint.h>

/*
 * EEPROM存储地址说明：
 * 0x0000~0x0001：存储总人数（不考虑页对齐）
 * 0x0002-0x3E81: 存储用户信息
 * 0x3E84-0xFFFF: 存储打卡信息
 */
#define USER_INFO_LEN_ADDR 0x0000
#define CHECK_INFO_LEN_ADDR 0x3E82
#define USER_INFO_ADDR 0x0002
#define CHECK_INFO_ADDR 0x3E84
#define EEPROM_MAX_ADDRESS 0xFFFF

/*人员信息记录
 * ID: 学生学号
 * Name: 学生姓名
 */
__attribute__((aligned(8))) typedef struct UserInfo
{
    uint64_t ID;
    char Name[20];
} UserInfo;

/*打卡信息记录
 * ID: 学生学号
 * startTime: 打卡开始时间
 * endTime: 打卡结束时间
 */
__attribute__((aligned(8))) typedef struct CheckInfo
{
    uint64_t ID;
    uint64_t startTime;
    uint64_t endTime;
} CheckInfo;

extern uint16_t totalUserNum;
extern uint16_t totalCheckNum;
extern UserInfo *userList;
extern CheckInfo *checkList;

#endif /* _DATASTRUCT_H_ */