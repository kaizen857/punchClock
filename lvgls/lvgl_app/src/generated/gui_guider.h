/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"

    typedef struct
    {
        lv_obj_t *MainMenuScreen;
        bool MainMenuScreen_del;
        lv_obj_t *MainMenuScreen_MainMenu;
        lv_obj_t *MainMenuScreen_label_1;
        lv_obj_t *MainMenuScreen_userInfoButton;
        lv_obj_t *MainMenuScreen_userInfoButton_label;
        lv_obj_t *MainMenuScreen_btn_3;
        lv_obj_t *MainMenuScreen_btn_3_label;
        lv_obj_t *MainMenuScreen_btn_4;
        lv_obj_t *MainMenuScreen_btn_4_label;
        lv_obj_t *MainMenuScreen_btn_5;
        lv_obj_t *MainMenuScreen_btn_5_label;
        lv_obj_t *MainMenuScreen_userInfoPanel;
        lv_obj_t *MainMenuScreen_tileview_1;
        lv_obj_t *MainMenuScreen_tileview_1_tile;
        lv_obj_t *MainMenuScreen_UserInfoTable;
        lv_obj_t *MainMenuScreen_newUserInfoButton;
        lv_obj_t *MainMenuScreen_newUserInfoButton_label;
        // lv_obj_t *writeUserInfoIntoCard;
        // lv_obj_t *writeUserInfoIntoCard_label;
        lv_obj_t *MainMenuScreen_btn_6;
        lv_obj_t *MainMenuScreen_btn_6_label;
        lv_obj_t *MainMenuScreen_CheckInfoPanel;
        lv_obj_t *MainMenuScreen_tileview_2;
        lv_obj_t *MainMenuScreen_tileview_2_tile;
        lv_obj_t *MainMenuScreen_table_2;
        lv_obj_t *MainMenuScreen_btn_10;
        lv_obj_t *MainMenuScreen_btn_10_label;
        lv_obj_t *MainMenuScreen_btn_9;
        lv_obj_t *MainMenuScreen_btn_9_label;
        lv_obj_t *MainMenuScreen_About;
        lv_obj_t *MainMenuScreen_aboutReturnButton;
        lv_obj_t *MainMenuScreen_aboutReturnButton_label;
        lv_obj_t *MainMenuScreen_designerInfoLabel;
        lv_obj_t *MainMenuScreen_newUserInfo;
        lv_obj_t *MainMenuScreen_label_7;
        lv_obj_t *MainMenuScreen_ta_1;
        lv_obj_t *MainMenuScreen_ta_2;
        lv_obj_t *MainMenuScreen_label_6;
        lv_obj_t *MainMenuScreen_btn_11;
        lv_obj_t *MainMenuScreen_btn_11_label;
        lv_obj_t *MainMenuScreen_btn_12;
        lv_obj_t *MainMenuScreen_btn_12_label;
        lv_obj_t *MainMenuScreen_changeTime;
        lv_obj_t *MainMenuScreen_minuteChangeLabel;
        lv_obj_t *MainMenuScreen_hourChangeLabel;
        lv_obj_t *MainMenuScreen_label_5;
        lv_obj_t *MainMenuScreen_hourUpButton;
        lv_obj_t *MainMenuScreen_hourUpButton_label;
        lv_obj_t *MainMenuScreen_minuteUpButton;
        lv_obj_t *MainMenuScreen_minuteUpButton_label;
        lv_obj_t *MainMenuScreen_hourDownButton;
        lv_obj_t *MainMenuScreen_hourDownButton_label;
        lv_obj_t *MainMenuScreen_minuteDownButton;
        lv_obj_t *MainMenuScreen_minuteDownButton_label;
        lv_obj_t *MainMenuScreen_btn_14;
        lv_obj_t *MainMenuScreen_btn_14_label;
        lv_obj_t *MainMenuScreen_ConfirmButton;
        lv_obj_t *MainMenuScreen_ConfirmButton_label;
        lv_obj_t *MainMenuScreen_eventPopUp;
        lv_obj_t *MainMenuScreen_btn_13;
        lv_obj_t *MainMenuScreen_btn_13_label;
        lv_obj_t *MainMenuScreen_label_8;
        lv_obj_t *MainMenuScreen_label_11;
        lv_obj_t *MainMenuScreen_calendar;
        lv_obj_t *MainMenuScreen_Battery;
        lv_obj_t *MainMenuScreen_Clock;
        lv_obj_t *g_kb_top_layer;
    } lv_ui;

    typedef void (*ui_setup_scr_t)(lv_ui *ui);

    void ui_init_style(lv_style_t *style);

    void ui_load_scr_animation(lv_ui *ui, lv_obj_t **new_scr, bool new_scr_del, bool *old_scr_del, ui_setup_scr_t setup_scr,
                               lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

    void ui_animation(void *var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                      uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                      lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

    void init_scr_del_flag(lv_ui *ui);

    void setup_bottom_layer(void);

    void setup_ui(lv_ui *ui);

    void video_play(lv_ui *ui);

    void init_keyboard(lv_ui *ui);

    extern lv_ui guider_ui;

    void setup_scr_MainMenuScreen(lv_ui *ui);
    LV_IMAGE_DECLARE(_up_triangle_RGB565A8_38x31);
    LV_IMAGE_DECLARE(_down_triangle_RGB565A8_38x31);

    LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_25)
    LV_FONT_DECLARE(lv_font_montserratMedium_16)
    LV_FONT_DECLARE(lv_font_youyuan_16)
    LV_FONT_DECLARE(lv_font_montserratMedium_12)
    LV_FONT_DECLARE(lv_font_youyuan_12)
    LV_FONT_DECLARE(lv_font_youyuan_14)
    LV_FONT_DECLARE(lv_font_youyuan_25)

#ifdef __cplusplus
}
#endif
#endif
