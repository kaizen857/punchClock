#include "eventHandler.h"
#include "DS3231.h"
#include "dataStruct.h"
#include "label/lv_label.h"
#include "lv_event.h"
#include "lv_obj.h"
#include "lv_obj_event.h"
#include "lv_types.h"
#include "textarea/lv_textarea.h"
#include "gui_guider.h"
#include <stdlib.h>
#include "function.h"

static int hour = -1;
static int minute = -1;

// 分支优化
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

void userInfoPanel_ImportFromSDcard_event_handler(lv_event_t *e) // 从SD卡导入
{
    // TODO: 从SD卡导入
}

void newUserInfoPanel_ConfirmButton_event_handler(lv_event_t *e)
{
    // TODO:确认添加新用户
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        const char *name = lv_textarea_get_text(guider_ui.MainMenuScreen_ta_1);
        const char *id = lv_textarea_get_text(guider_ui.MainMenuScreen_ta_2);
        uint64_t id_num = strtoull(id, NULL, 10);
        UserInfo info = {id_num};
        strncpy(info.Name, name, sizeof(info.Name) - 1);
        if (writeUserInfo(&info) == 0)
        {
            // 添加成功
            lv_obj_add_flag(guider_ui.MainMenuScreen_newUserInfo, LV_OBJ_FLAG_HIDDEN);
            break;
        }
        else
        {
            // TODO:添加失败
            lv_label_set_text(guider_ui.MainMenuScreen_label_8, "添加失败!请重试");
            lv_obj_clear_flag(guider_ui.MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);
        }
    }
    default:
        break;
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

        // TODO:确认修改时间
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
        int hour, minute;
        sscanf(time, "%02d:%02d", &hour, &minute);
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_hourChangeLabel, "%02d", hour);
        lv_label_set_text_fmt(guider_ui.MainMenuScreen_minuteChangeLabel, "%02d", minute);
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
    // lv_obj_add_event_cb(ui->MainMenuScreen_ConfirmButton, newUserInfoPanel_ConfirmButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_hourUpButton, changeTimePanel_HourUpButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_hourDownButton, changeTimePanel_HourDownButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_minuteUpButton, changeTimePanel_MinUpButton_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_minuteDownButton, changeTimePanel_MinDownButton_event_handler, LV_EVENT_ALL, ui);

    lv_obj_add_event_cb(ui->MainMenuScreen_Clock, MainMenuScreen_Clock_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MainMenuScreen_ConfirmButton, changeTimePanel_ConfirmButton_event_handler, LV_EVENT_ALL, ui);
}

void myLVGL_UIInit(void)
{
    // 时间初始化
    uint8_t firesHour = DS3231_GetHour();
    uint8_t FiresMinute = DS3231_GetMinute();
    lv_label_set_text_fmt(guider_ui.MainMenuScreen_Clock, "%02d:%02d", firesHour, FiresMinute);

    lv_timer_create(MainMenuScreen_digital_clock_1_timer, 60000, NULL);

    // 日期初始化
    uint16_t year = DS3231_GetYear();
    uint8_t month = DS3231_GetMonth();
    uint8_t day = DS3231_GetDate();
    lv_label_set_text_fmt(guider_ui.MainMenuScreen_calendar, "%04d/%02d/%02d", year, month, day);
}