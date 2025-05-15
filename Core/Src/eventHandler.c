#include "eventHandler.h"
#include "DS3231.h"
#include "RC522.h"
#include "dataStruct.h"
#include "ff.h"
#include "label/lv_label.h"
#include "lv_event.h"
#include "lv_obj.h"
#include "lv_obj_event.h"
#include "lv_types.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "textarea/lv_textarea.h"
#include "gui_guider.h"
#include <stdlib.h>
#include "function.h"

static int hour = -1;
static int minute = -1;

void userInfoPanel_ImportFromSDcard_event_handler(lv_event_t *e) // 从SD卡导入
{
    // TODO: 从SD卡导入（不做）
}

void newUserInfoPanel_ConfirmButton_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED)
        return;

    // 获取输入内容
    const char *name = lv_textarea_get_text(guider_ui.MainMenuScreen_ta_1);
    const char *id_str = lv_textarea_get_text(guider_ui.MainMenuScreen_ta_2);

    // 验证输入不为空
    if (name == NULL || id_str == NULL || name[0] == '\0' || id_str[0] == '\0')
    {
        lv_label_set_text(guider_ui.MainMenuScreen_label_8, "输入为空!请重试");
        lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    // 验证ID是否为有效数字
    char *endptr;
    uint64_t id_num = strtoull(id_str, &endptr, 10);

    // 检查转换是否完全成功
    if (*endptr != '\0' || id_str == endptr)
    {
        lv_label_set_text(guider_ui.MainMenuScreen_label_8, "ID必须为数字!");
        lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    // 准备用户信息
    UserInfo info = {id_num};

    // 安全复制名称
    size_t name_len = strlen(name);
    if (name_len >= sizeof(info.Name))
    {
        lv_label_set_text(guider_ui.MainMenuScreen_label_8, "姓名过长!");
        lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
        return;
    }
    strncpy(info.Name, name, sizeof(info.Name) - 1);
    info.Name[sizeof(info.Name) - 1] = '\0'; // 确保终止

    // 写入用户信息
    if (writeUserInfo(&info) && updateUserInfoList(&info))
    {
        // TODO: 将信息写入NFC卡内
        lv_obj_add_flag(guider_ui.MainMenuScreen_newUserInfo, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(guider_ui.MainMenuScreen_label_8, "添加成功！\n请将卡靠近读卡器");
        lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
        lv_refr_now(NULL); // 立即执行刷新
        uint8_t data[16];
        memcpy(data, &id_num, sizeof(id_num));
        uint16_t crc = calculateCRC16(data, sizeof(id_num));
        data[9] = crc >> 8;
        data[10] = crc & 0xFF;
        uint8_t status;
        status = RC522WriteCard(data);
        while (true)
        {
            if (status == PCD_OK)
            {
                lv_label_set_text(guider_ui.MainMenuScreen_label_8, "写入成功！");
                lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
                break;
            }
            else if (status == PCD_ERR)
            {
                lv_label_set_text(guider_ui.MainMenuScreen_label_8, "写入失败！请重试");
                lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
            }
            else if (status == PCD_NOTAGERR)
            {
                lv_label_set_text(guider_ui.MainMenuScreen_label_8, "请将卡靠近读卡器");
                lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
            }
            status = RC522WriteCard(data);
            HAL_Delay(100);
        }
        // 清空输入框
        lv_textarea_set_text(guider_ui.MainMenuScreen_ta_1, "");
        lv_textarea_set_text(guider_ui.MainMenuScreen_ta_2, "");
        initUserInfoTable(&guider_ui);
    }
    else
    {
        lv_label_set_text(guider_ui.MainMenuScreen_label_8, "添加失败!请重试");
        lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
    }
}

void changeTimePanel_ConfirmButton_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (unlikely(hour == -1))
        {
            hour = atoi(lv_label_get_text(guider_ui.MainMenuScreen_hourChangeLabel));
        }
        if (unlikely(minute == -1))
        {
            minute = atoi(lv_label_get_text(guider_ui.MainMenuScreen_minuteChangeLabel));
        }

        DS3231_SetMinute(minute);
        DS3231_SetHour(hour);
        DS3231_SetSecond(0); // 设置秒为0
        lv_obj_add_flag(guider_ui.MainMenuScreen_changeTime, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_Clock, "%02d:%02d", hour, minute);
    }
    default:
        break;
    }
}

void changeTimePanel_HourUpButton_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // 增加小时
        if (unlikely(hour == -1))
        {
            hour = atoi(lv_label_get_text(guider_ui.MainMenuScreen_hourChangeLabel));
        }
        hour = (hour + 1) % 24;
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_hourChangeLabel, "%02d", hour);
        break;
    }
    default:
        break;
    }
}

void changeTimePanel_HourDownButton_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // 减少小时
        if (unlikely(hour == -1)) //[[unlikely]]
        {
            hour = atoi(lv_label_get_text(guider_ui.MainMenuScreen_hourChangeLabel));
        }
        hour = (hour - 1) < 0 ? 23 : (hour - 1);
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_hourChangeLabel, "%02d", hour);
        break;
    }
    default:
        break;
    }
}

void changeTimePanel_MinUpButton_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // 增加分钟
        if (unlikely(minute == -1))
        {
            minute = atoi(lv_label_get_text(guider_ui.MainMenuScreen_minuteChangeLabel));
        }
        minute = (minute + 1) % 60;
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_minuteChangeLabel, "%02d", minute);
        break;
    }
    default:
        break;
    }
}

void changeTimePanel_MinDownButton_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // 减少分钟
        if (unlikely(minute == -1))
        {
            minute = atoi(lv_label_get_text(guider_ui.MainMenuScreen_minuteChangeLabel));
        }
        minute = (minute - 1) < 0 ? 59 : (minute - 1);
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_minuteChangeLabel, "%02d", minute);
        break;
    }
    default:
        break;
    }
}

void MainMenuScreen_Clock_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        char *time = lv_label_get_text(guider_ui.MainMenuScreen_Clock);
        int tmphour, tmpminute;
        sscanf(time, "%02d:%02d", &tmphour, &tmpminute);
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_hourChangeLabel, "%02d", tmphour);
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_minuteChangeLabel, "%02d", tmpminute);
        hour = tmphour;
        minute = tmpminute;
        lv_obj_remove_flag(guider_ui.MainMenuScreen_changeTime, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void CheckInfoPanel_ExportButton_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // TODO:导出
        if (HAL_GPIO_ReadPin(SD_CD_GPIO_Port, SD_CD_Pin) == GPIO_PIN_SET)
        {
            lv_label_set_text(guider_ui.MainMenuScreen_label_8, "请插入SD卡");
            lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
            static FATFS myFatFs; // FatFs 文件系统对象; 这个结构体占用598字节，有点大，需用static修饰(存放在全局数据区), 避免stack溢出
            static FIL myFile;    // 文件对象; 这个结构体占用570字节，有点大，需用static修饰(存放在全局数据区), 避免stack溢出
            static FRESULT f_res; // 文件操作结果
            static uint8_t buffer[64];
            f_res = f_mount(&myFatFs, "0:", 1);
            if (f_res == FR_OK)
            {
                f_res = f_open(&myFile, "0:checkInfo.csv", FA_CREATE_ALWAYS | FA_WRITE);
                if (f_res == FR_OK)
                {
                    CheckInfo info = {0};
                    uint16_t addr = CHECK_INFO_ADDR; // 从flash中读取数据
                    for (int i = 0; i < totalCheckNum; i++)
                    {
                        if (at24_read(addr, (uint8_t *)&info, sizeof(info), 1000))
                        {
                            uint16_t startYear = (uint16_t)(info.startTime >> 48);
                            uint8_t startMonth = (uint8_t)(info.startTime >> 40);
                            uint8_t startDay = (uint8_t)(info.startTime >> 32);
                            uint8_t startHour = (uint8_t)(info.startTime >> 24);
                            uint8_t startMinute = (uint8_t)(info.startTime >> 16);
                            uint16_t endYear = (uint16_t)(info.endTime >> 48);
                            uint8_t endMonth = (uint8_t)(info.endTime >> 40);
                            uint8_t endDay = (uint8_t)(info.endTime >> 32);
                            uint8_t endHour = (uint8_t)(info.endTime >> 24);
                            uint8_t endMinute = (uint8_t)(info.endTime >> 16);
                            UserInfo *user = bsearch(&(UserInfo){.ID = info.ID}, userList, totalUserNum, sizeof(UserInfo), compareUserInfo);                                                                                 // 查找用户
                            f_printf(&myFile, "%s,%04d/%02d/%02d %02d:%02d,%04d/%02d/%02d %02d:%02d\n", user->Name, startYear, startMonth, startDay, startHour, startMinute, endYear, endMonth, endDay, endHour, endMinute); // 写入文件
                            addr += sizeof(info);
                        }
                    }
                    f_res = f_close(&myFile);
                    // if (f_res == FR_OK)
                    //{
                    f_res = f_mount(NULL, "0:", 1);
                    lv_label_set_text(guider_ui.MainMenuScreen_label_8, "导出成功");
                    lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
                    //}
                }
                else
                {
                    lv_label_set_text(guider_ui.MainMenuScreen_label_8, "文件打开失败");
                    lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
#ifdef DEBUG
                    printf("file open error code:%d\n", f_res);
#endif
                }
            }
            else
            {
                lv_label_set_text(guider_ui.MainMenuScreen_label_8, "文件系统挂载失败");
                lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
#ifdef DEBUG
                printf("file system mount error code:%d\n", f_res);
#endif
            }
        }
    }
    default:
        break;
    }
}

void MainMenuScreen_digital_clock_1_timer(lv_timer_t *timer)
{
    // 更新时间
    if (lv_obj_is_valid(guider_ui.MainMenuScreen_Clock))
    {
        uint8_t hour = DS3231_GetHour();
        uint8_t minute = DS3231_GetMinute();
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_Clock, "%02d:%02d", hour, minute);
    }
}

void myEventInit(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->MainMenuScreen_btn_12, newUserInfoPanel_ConfirmButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_hourUpButton, changeTimePanel_HourUpButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_hourDownButton, changeTimePanel_HourDownButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_minuteUpButton, changeTimePanel_MinUpButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_minuteDownButton, changeTimePanel_MinDownButton_event_handler, LV_EVENT_ALL, ui);

    lv_obj_add_event_cb(ui->MainMenuScreen_Clock, MainMenuScreen_Clock_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_ConfirmButton, changeTimePanel_ConfirmButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_btn_9, CheckInfoPanel_ExportButton_event_handler, LV_EVENT_ALL, ui);
}

void myLVGL_UIInit(void)
{
    // 时间初始化
    uint8_t firesHour = DS3231_GetHour();
    uint8_t FiresMinute = DS3231_GetMinute();
    lv_label_set_text_fmt(guider_ui.MainMenuScreen_Clock, "%02d:%02d", firesHour, FiresMinute);

    lv_timer_create(MainMenuScreen_digital_clock_1_timer, 10000, NULL);

    // 日期初始化
    uint16_t year = DS3231_GetYear();
    uint8_t month = DS3231_GetMonth();
    uint8_t day = DS3231_GetDate();
    lv_label_set_text_fmt(guider_ui.MainMenuScreen_calendar, "%04d/%02d/%02d", year, month, day);

    initUserInfoTable(&guider_ui);

    initCheckInfoTable(&guider_ui);
}