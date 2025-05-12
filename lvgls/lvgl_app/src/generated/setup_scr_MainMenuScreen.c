/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_MainMenuScreen(lv_ui *ui)
{
    // Write codes MainMenuScreen
    ui->MainMenuScreen = lv_obj_create(NULL);
    lv_obj_set_size(ui->MainMenuScreen, 480, 320);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen, LV_SCROLLBAR_MODE_OFF);

    // Write style for MainMenuScreen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_MainMenu
    ui->MainMenuScreen_MainMenu = lv_obj_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_MainMenu, 0, 0);
    lv_obj_set_size(ui->MainMenuScreen_MainMenu, 480, 320);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_MainMenu, LV_SCROLLBAR_MODE_OFF);

    // Write style for MainMenuScreen_MainMenu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_MainMenu, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_MainMenu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_MainMenu, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_MainMenu, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_MainMenu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_MainMenu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_MainMenu, lv_color_hex(0x79BEE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_MainMenu, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_MainMenu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_MainMenu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_MainMenu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_MainMenu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_MainMenu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_label_1
    ui->MainMenuScreen_label_1 = lv_label_create(ui->MainMenuScreen_MainMenu);
    lv_obj_set_pos(ui->MainMenuScreen_label_1, 84, 127);
    lv_obj_set_size(ui->MainMenuScreen_label_1, 322, 32);
    lv_label_set_text(ui->MainMenuScreen_label_1, "欢迎使用打卡系统(*´∀`)~♥\n");
    lv_label_set_long_mode(ui->MainMenuScreen_label_1, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_label_1, lv_color_hex(0x06f7ed), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_label_1, &lv_font_SourceHanSerifSC_Regular_25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_userInfoButton
    ui->MainMenuScreen_userInfoButton = lv_button_create(ui->MainMenuScreen_MainMenu);
    lv_obj_set_pos(ui->MainMenuScreen_userInfoButton, 68, 200);
    lv_obj_set_size(ui->MainMenuScreen_userInfoButton, 100, 50);
    ui->MainMenuScreen_userInfoButton_label = lv_label_create(ui->MainMenuScreen_userInfoButton);
    lv_label_set_text(ui->MainMenuScreen_userInfoButton_label, "人员信息");
    lv_label_set_long_mode(ui->MainMenuScreen_userInfoButton_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_userInfoButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_userInfoButton, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_userInfoButton_label, LV_PCT(100));

    // Write style for MainMenuScreen_userInfoButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_userInfoButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_userInfoButton, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_userInfoButton, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_userInfoButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_userInfoButton, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_userInfoButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_userInfoButton, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_userInfoButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_userInfoButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_userInfoButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_3
    ui->MainMenuScreen_btn_3 = lv_button_create(ui->MainMenuScreen_MainMenu);
    lv_obj_set_pos(ui->MainMenuScreen_btn_3, 197, 200);
    lv_obj_set_size(ui->MainMenuScreen_btn_3, 100, 50);
    ui->MainMenuScreen_btn_3_label = lv_label_create(ui->MainMenuScreen_btn_3);
    lv_label_set_text(ui->MainMenuScreen_btn_3_label, "打卡记录");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_3_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_3, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_3, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_4
    ui->MainMenuScreen_btn_4 = lv_button_create(ui->MainMenuScreen_MainMenu);
    lv_obj_set_pos(ui->MainMenuScreen_btn_4, 330, 200);
    lv_obj_set_size(ui->MainMenuScreen_btn_4, 100, 50);
    ui->MainMenuScreen_btn_4_label = lv_label_create(ui->MainMenuScreen_btn_4);
    lv_label_set_text(ui->MainMenuScreen_btn_4_label, "关于");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_4_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_4, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_4, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_4, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_5
    // ui->MainMenuScreen_btn_5 = lv_button_create(ui->MainMenuScreen_MainMenu);
    // lv_obj_set_pos(ui->MainMenuScreen_btn_5, 402, 4);
    // lv_obj_set_size(ui->MainMenuScreen_btn_5, 74, 31);
    // ui->MainMenuScreen_btn_5_label = lv_label_create(ui->MainMenuScreen_btn_5);
    // lv_label_set_text(ui->MainMenuScreen_btn_5_label, "随机图片");
    // lv_label_set_long_mode(ui->MainMenuScreen_btn_5_label, LV_LABEL_LONG_WRAP);
    // lv_obj_align(ui->MainMenuScreen_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_5, 0, LV_STATE_DEFAULT);
    // lv_obj_set_width(ui->MainMenuScreen_btn_5_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    // lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_5, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_width(ui->MainMenuScreen_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(ui->MainMenuScreen_btn_5, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(ui->MainMenuScreen_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui->MainMenuScreen_btn_5, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_align(ui->MainMenuScreen_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_userInfoPanel
    ui->MainMenuScreen_userInfoPanel = lv_obj_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_userInfoPanel, 0, 0);
    lv_obj_set_size(ui->MainMenuScreen_userInfoPanel, 480, 320);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_userInfoPanel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->MainMenuScreen_userInfoPanel, LV_OBJ_FLAG_HIDDEN);

    // Write style for MainMenuScreen_userInfoPanel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_userInfoPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_userInfoPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_userInfoPanel, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_userInfoPanel, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_userInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_userInfoPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_userInfoPanel, lv_color_hex(0x79BEE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_userInfoPanel, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_userInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_userInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_userInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_userInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_userInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_tileview_1
    ui->MainMenuScreen_tileview_1 = lv_tileview_create(ui->MainMenuScreen_userInfoPanel);
    lv_obj_set_pos(ui->MainMenuScreen_tileview_1, 1, 49);
    lv_obj_set_size(ui->MainMenuScreen_tileview_1, 472, 259);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_tileview_1, LV_SCROLLBAR_MODE_OFF);
    ui->MainMenuScreen_tileview_1_tile = lv_tileview_add_tile(ui->MainMenuScreen_tileview_1, 0, 0, LV_DIR_RIGHT);

    // Write style for MainMenuScreen_tileview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_tileview_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_tileview_1, lv_color_hex(0x79BEE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_tileview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_tileview_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_tileview_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_tileview_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_tileview_1, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_tileview_1, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_tileview_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_tileview_1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_UserInfoTable
    ui->MainMenuScreen_UserInfoTable = lv_table_create(ui->MainMenuScreen_tileview_1_tile);
    lv_obj_set_pos(ui->MainMenuScreen_UserInfoTable, 137, 3);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_UserInfoTable, LV_SCROLLBAR_MODE_OFF);
    lv_table_set_column_count(ui->MainMenuScreen_UserInfoTable, 2);
    lv_table_set_row_count(ui->MainMenuScreen_UserInfoTable, 13);
    lv_table_set_cell_value(ui->MainMenuScreen_UserInfoTable, 0, 0, "姓名");

    lv_table_set_cell_value(ui->MainMenuScreen_UserInfoTable, 0, 1, "学号");

    // Write style for MainMenuScreen_UserInfoTable, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->MainMenuScreen_UserInfoTable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_UserInfoTable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_UserInfoTable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_UserInfoTable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_UserInfoTable, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_UserInfoTable, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_UserInfoTable, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_UserInfoTable, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_UserInfoTable, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_UserInfoTable, lv_color_hex(0xd5dee6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_UserInfoTable, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_UserInfoTable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_UserInfoTable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_UserInfoTable, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_UserInfoTable, lv_color_hex(0x393c41), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_UserInfoTable, &lv_font_youyuan_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_UserInfoTable, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_UserInfoTable, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_UserInfoTable, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_UserInfoTable, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_UserInfoTable, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_UserInfoTable, lv_color_hex(0xd5dee6), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_UserInfoTable, LV_BORDER_SIDE_FULL, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_UserInfoTable, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_UserInfoTable, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_UserInfoTable, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_UserInfoTable, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_newUserInfoButton
    ui->MainMenuScreen_newUserInfoButton = lv_button_create(ui->MainMenuScreen_userInfoPanel);
    lv_obj_set_pos(ui->MainMenuScreen_newUserInfoButton, 3, 55);
    lv_obj_set_size(ui->MainMenuScreen_newUserInfoButton, 117, 41);
    ui->MainMenuScreen_newUserInfoButton_label = lv_label_create(ui->MainMenuScreen_newUserInfoButton);
    lv_label_set_text(ui->MainMenuScreen_newUserInfoButton_label, "新建人员信息");
    lv_label_set_long_mode(ui->MainMenuScreen_newUserInfoButton_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_newUserInfoButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_newUserInfoButton, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_newUserInfoButton_label, LV_PCT(100));

    // Write style for MainMenuScreen_newUserInfoButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_newUserInfoButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_newUserInfoButton, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_newUserInfoButton, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_newUserInfoButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_newUserInfoButton, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_newUserInfoButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_newUserInfoButton, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_newUserInfoButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_newUserInfoButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_newUserInfoButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // // Write codes writeUserInfoIntoCard
    // ui->writeUserInfoIntoCard = lv_button_create(ui->MainMenuScreen_userInfoPanel);
    // lv_obj_set_pos(ui->writeUserInfoIntoCard, 1, 101);
    // lv_obj_set_size(ui->writeUserInfoIntoCard, 129, 45);
    // ui->writeUserInfoIntoCard_label = lv_label_create(ui->writeUserInfoIntoCard);
    // lv_label_set_text(ui->writeUserInfoIntoCard_label, "从SD卡导入人员信息");
    // lv_label_set_long_mode(ui->writeUserInfoIntoCard_label, LV_LABEL_LONG_WRAP);
    // lv_obj_align(ui->writeUserInfoIntoCard_label, LV_ALIGN_LEFT_MID, 0, 0);
    // lv_obj_set_style_pad_all(ui->writeUserInfoIntoCard, 0, LV_STATE_DEFAULT);
    // lv_obj_set_width(ui->writeUserInfoIntoCard_label, LV_PCT(100));

    // // Write style for writeUserInfoIntoCard, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    // lv_obj_set_style_bg_opa(ui->writeUserInfoIntoCard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(ui->writeUserInfoIntoCard, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_grad_dir(ui->writeUserInfoIntoCard, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_width(ui->writeUserInfoIntoCard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(ui->writeUserInfoIntoCard, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_shadow_width(ui->writeUserInfoIntoCard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(ui->writeUserInfoIntoCard, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui->writeUserInfoIntoCard, &lv_font_youyuan_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_opa(ui->writeUserInfoIntoCard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_align(ui->writeUserInfoIntoCard, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_6
    ui->MainMenuScreen_btn_6 = lv_button_create(ui->MainMenuScreen_userInfoPanel);
    lv_obj_set_pos(ui->MainMenuScreen_btn_6, 375, 0);
    lv_obj_set_size(ui->MainMenuScreen_btn_6, 100, 50);
    ui->MainMenuScreen_btn_6_label = lv_label_create(ui->MainMenuScreen_btn_6);
    lv_label_set_text(ui->MainMenuScreen_btn_6_label, "返回");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_6_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_6, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_6, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_6, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_CheckInfoPanel
    ui->MainMenuScreen_CheckInfoPanel = lv_obj_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_CheckInfoPanel, 0, 0);
    lv_obj_set_size(ui->MainMenuScreen_CheckInfoPanel, 480, 320);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_CheckInfoPanel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->MainMenuScreen_CheckInfoPanel, LV_OBJ_FLAG_HIDDEN);

    // Write style for MainMenuScreen_CheckInfoPanel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_CheckInfoPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_CheckInfoPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_CheckInfoPanel, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_CheckInfoPanel, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_CheckInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_CheckInfoPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_CheckInfoPanel, lv_color_hex(0x79BEE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_CheckInfoPanel, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_CheckInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_CheckInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_CheckInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_CheckInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_CheckInfoPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_tileview_2
    ui->MainMenuScreen_tileview_2 = lv_tileview_create(ui->MainMenuScreen_CheckInfoPanel);
    lv_obj_set_pos(ui->MainMenuScreen_tileview_2, 3, 61);
    lv_obj_set_size(ui->MainMenuScreen_tileview_2, 468, 252);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_tileview_2, LV_SCROLLBAR_MODE_OFF);
    ui->MainMenuScreen_tileview_2_tile = lv_tileview_add_tile(ui->MainMenuScreen_tileview_2, 0, 0, LV_DIR_RIGHT);

    // Write style for MainMenuScreen_tileview_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_tileview_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_tileview_2, lv_color_hex(0x79BEE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_tileview_2, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_tileview_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_tileview_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_tileview_2, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_tileview_2, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_tileview_2, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_tileview_2, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_tileview_2, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_table_2
    ui->MainMenuScreen_table_2 = lv_table_create(ui->MainMenuScreen_tileview_2_tile);
    lv_obj_set_pos(ui->MainMenuScreen_table_2, 10, -4);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_table_2, LV_SCROLLBAR_MODE_OFF);
    lv_table_set_column_count(ui->MainMenuScreen_table_2, 3);
    lv_table_set_row_count(ui->MainMenuScreen_table_2, 1);
    lv_table_set_cell_value(ui->MainMenuScreen_table_2, 0, 0, "姓名");
    lv_table_set_cell_value(ui->MainMenuScreen_table_2, 0, 1, "开始时间");
    lv_table_set_cell_value(ui->MainMenuScreen_table_2, 0, 2, "结束时间");

    // Write style for MainMenuScreen_table_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->MainMenuScreen_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_table_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_table_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_table_2, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_table_2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_table_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_table_2, lv_color_hex(0xd5dee6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_table_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_table_2, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_table_2, lv_color_hex(0x393c41), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_table_2, &lv_font_youyuan_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_table_2, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_table_2, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_table_2, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_table_2, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_table_2, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_table_2, lv_color_hex(0xd5dee6), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_table_2, LV_BORDER_SIDE_FULL, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_table_2, 9, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_10
    ui->MainMenuScreen_btn_10 = lv_button_create(ui->MainMenuScreen_CheckInfoPanel);
    lv_obj_set_pos(ui->MainMenuScreen_btn_10, 325, 1);
    lv_obj_set_size(ui->MainMenuScreen_btn_10, 74, 39);
    ui->MainMenuScreen_btn_10_label = lv_label_create(ui->MainMenuScreen_btn_10);
    lv_label_set_text(ui->MainMenuScreen_btn_10_label, "返回");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_10_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_10_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_10, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_10_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_10, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_10, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_10, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_10, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_10, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_9
    ui->MainMenuScreen_btn_9 = lv_button_create(ui->MainMenuScreen_CheckInfoPanel);
    lv_obj_set_pos(ui->MainMenuScreen_btn_9, 401, 0);
    lv_obj_set_size(ui->MainMenuScreen_btn_9, 74, 41);
    ui->MainMenuScreen_btn_9_label = lv_label_create(ui->MainMenuScreen_btn_9);
    lv_label_set_text(ui->MainMenuScreen_btn_9_label, "导出");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_9_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_9_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_9, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_9_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_9, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_9, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_9, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_9, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_9, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_About
    ui->MainMenuScreen_About = lv_obj_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_About, 0, 0);
    lv_obj_set_size(ui->MainMenuScreen_About, 480, 320);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_About, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->MainMenuScreen_About, LV_OBJ_FLAG_HIDDEN);

    // Write style for MainMenuScreen_About, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_About, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_About, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_About, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_About, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_About, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_About, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_About, lv_color_hex(0x79BEE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_About, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_About, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_About, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_About, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_About, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_About, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_aboutReturnButton
    ui->MainMenuScreen_aboutReturnButton = lv_button_create(ui->MainMenuScreen_About);
    lv_obj_set_pos(ui->MainMenuScreen_aboutReturnButton, 375, 3);
    lv_obj_set_size(ui->MainMenuScreen_aboutReturnButton, 100, 50);
    ui->MainMenuScreen_aboutReturnButton_label = lv_label_create(ui->MainMenuScreen_aboutReturnButton);
    lv_label_set_text(ui->MainMenuScreen_aboutReturnButton_label, "返回");
    lv_label_set_long_mode(ui->MainMenuScreen_aboutReturnButton_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_aboutReturnButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_aboutReturnButton, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_aboutReturnButton_label, LV_PCT(100));

    // Write style for MainMenuScreen_aboutReturnButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_aboutReturnButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_aboutReturnButton, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_aboutReturnButton, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_aboutReturnButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_aboutReturnButton, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_aboutReturnButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_aboutReturnButton, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_aboutReturnButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_aboutReturnButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_aboutReturnButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_designerInfoLabel
    ui->MainMenuScreen_designerInfoLabel = lv_label_create(ui->MainMenuScreen_About);
    lv_obj_set_pos(ui->MainMenuScreen_designerInfoLabel, 97, 126);
    lv_obj_set_size(ui->MainMenuScreen_designerInfoLabel, 336, 108);
    lv_label_set_text(ui->MainMenuScreen_designerInfoLabel, "LVGL Version: 9.2.2\nPCB Designer: 谢伟力\nProgrammers：谢伟力、钟炯阳、郑浩文\n");
    lv_label_set_long_mode(ui->MainMenuScreen_designerInfoLabel, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_designerInfoLabel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_designerInfoLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_designerInfoLabel, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_designerInfoLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_designerInfoLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_designerInfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_newUserInfo
    ui->MainMenuScreen_newUserInfo = lv_obj_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_newUserInfo, 73, 60);
    lv_obj_set_size(ui->MainMenuScreen_newUserInfo, 366, 223);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_newUserInfo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->MainMenuScreen_newUserInfo, LV_OBJ_FLAG_HIDDEN);

    // Write style for MainMenuScreen_newUserInfo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_newUserInfo, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_newUserInfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_newUserInfo, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_newUserInfo, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_newUserInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_newUserInfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_newUserInfo, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_newUserInfo, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_newUserInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_newUserInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_newUserInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_newUserInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_newUserInfo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_label_7
    ui->MainMenuScreen_label_7 = lv_label_create(ui->MainMenuScreen_newUserInfo);
    lv_obj_set_pos(ui->MainMenuScreen_label_7, 36, 115);
    lv_obj_set_size(ui->MainMenuScreen_label_7, 100, 32);
    lv_label_set_text(ui->MainMenuScreen_label_7, "学号");
    lv_label_set_long_mode(ui->MainMenuScreen_label_7, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_label_7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_label_7, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_label_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_ta_1
    ui->MainMenuScreen_ta_1 = lv_textarea_create(ui->MainMenuScreen_newUserInfo);
    lv_obj_set_pos(ui->MainMenuScreen_ta_1, 111, 65);
    lv_obj_set_size(ui->MainMenuScreen_ta_1, 195, 40);
    lv_textarea_set_text(ui->MainMenuScreen_ta_1, "");
    lv_textarea_set_placeholder_text(ui->MainMenuScreen_ta_1, "");
    lv_textarea_set_password_bullet(ui->MainMenuScreen_ta_1, "*");
    lv_textarea_set_password_mode(ui->MainMenuScreen_ta_1, false);
    lv_textarea_set_one_line(ui->MainMenuScreen_ta_1, false);
    lv_textarea_set_accepted_chars(ui->MainMenuScreen_ta_1, "");
    lv_textarea_set_max_length(ui->MainMenuScreen_ta_1, 32);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->MainMenuScreen_ta_1, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    // Write style for MainMenuScreen_ta_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_ta_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_ta_1, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_ta_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_ta_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_ta_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_ta_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_ta_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_ta_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_ta_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_ta_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_ta_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_ta_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_ta_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_ta_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_ta_1, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_ta_1, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_ta_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_ta_1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_ta_2
    ui->MainMenuScreen_ta_2 = lv_textarea_create(ui->MainMenuScreen_newUserInfo);
    lv_obj_set_pos(ui->MainMenuScreen_ta_2, 112, 111);
    lv_obj_set_size(ui->MainMenuScreen_ta_2, 195, 40);
    lv_textarea_set_text(ui->MainMenuScreen_ta_2, "");
    lv_textarea_set_placeholder_text(ui->MainMenuScreen_ta_2, "");
    lv_textarea_set_password_bullet(ui->MainMenuScreen_ta_2, "*");
    lv_textarea_set_password_mode(ui->MainMenuScreen_ta_2, false);
    lv_textarea_set_one_line(ui->MainMenuScreen_ta_2, false);
    lv_textarea_set_accepted_chars(ui->MainMenuScreen_ta_2, "");
    lv_textarea_set_max_length(ui->MainMenuScreen_ta_2, 32);
#if LV_USE_KEYBOARD
    lv_obj_add_event_cb(ui->MainMenuScreen_ta_2, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif

    // Write style for MainMenuScreen_ta_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_ta_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_ta_2, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_ta_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_ta_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_ta_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_ta_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_ta_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_ta_2, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_ta_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_ta_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_ta_2, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_ta_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_ta_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_ta_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_ta_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_ta_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_ta_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_ta_2, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_ta_2, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_ta_2, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_ta_2, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_ta_2, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_label_6
    ui->MainMenuScreen_label_6 = lv_label_create(ui->MainMenuScreen_newUserInfo);
    lv_obj_set_pos(ui->MainMenuScreen_label_6, 35, 69);
    lv_obj_set_size(ui->MainMenuScreen_label_6, 100, 32);
    lv_label_set_text(ui->MainMenuScreen_label_6, "姓名");
    lv_label_set_long_mode(ui->MainMenuScreen_label_6, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_label_6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_label_6, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_label_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_11
    ui->MainMenuScreen_btn_11 = lv_button_create(ui->MainMenuScreen_newUserInfo);
    lv_obj_set_pos(ui->MainMenuScreen_btn_11, 275, 2);
    lv_obj_set_size(ui->MainMenuScreen_btn_11, 84, 39);
    ui->MainMenuScreen_btn_11_label = lv_label_create(ui->MainMenuScreen_btn_11);
    lv_label_set_text(ui->MainMenuScreen_btn_11_label, "关闭");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_11_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_11_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_11, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_11_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_11, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_11, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_11, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_11, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_11, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_12
    ui->MainMenuScreen_btn_12 = lv_button_create(ui->MainMenuScreen_newUserInfo);
    lv_obj_set_pos(ui->MainMenuScreen_btn_12, 1, 0);
    lv_obj_set_size(ui->MainMenuScreen_btn_12, 84, 39);
    ui->MainMenuScreen_btn_12_label = lv_label_create(ui->MainMenuScreen_btn_12);
    lv_label_set_text(ui->MainMenuScreen_btn_12_label, "确认");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_12_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_12_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_12, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_12_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_12, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_12, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_12, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_12, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_12, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_changeTime
    ui->MainMenuScreen_changeTime = lv_obj_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_changeTime, 59, 48);
    lv_obj_set_size(ui->MainMenuScreen_changeTime, 355, 229);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_changeTime, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->MainMenuScreen_changeTime, LV_OBJ_FLAG_HIDDEN);

    // Write style for MainMenuScreen_changeTime, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_changeTime, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_changeTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_changeTime, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_changeTime, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_changeTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_changeTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_changeTime, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_changeTime, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_changeTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_changeTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_changeTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_changeTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_changeTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_minuteChangeLabel
    ui->MainMenuScreen_minuteChangeLabel = lv_label_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_minuteChangeLabel, 168, 98);
    lv_obj_set_size(ui->MainMenuScreen_minuteChangeLabel, 100, 32);
    lv_label_set_text(ui->MainMenuScreen_minuteChangeLabel, "52");
    lv_label_set_long_mode(ui->MainMenuScreen_minuteChangeLabel, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_minuteChangeLabel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_minuteChangeLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_minuteChangeLabel, &lv_font_youyuan_25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_minuteChangeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_minuteChangeLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_minuteChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_hourChangeLabel
    ui->MainMenuScreen_hourChangeLabel = lv_label_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_hourChangeLabel, 92, 98);
    lv_obj_set_size(ui->MainMenuScreen_hourChangeLabel, 91, 34);
    lv_label_set_text(ui->MainMenuScreen_hourChangeLabel, "12");
    lv_label_set_long_mode(ui->MainMenuScreen_hourChangeLabel, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_hourChangeLabel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_hourChangeLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_hourChangeLabel, &lv_font_youyuan_25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_hourChangeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_hourChangeLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_hourChangeLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_label_5
    ui->MainMenuScreen_label_5 = lv_label_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_label_5, 132, 94);
    lv_obj_set_size(ui->MainMenuScreen_label_5, 100, 32);
    lv_label_set_text(ui->MainMenuScreen_label_5, "：");
    lv_label_set_long_mode(ui->MainMenuScreen_label_5, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_label_5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_label_5, &lv_font_youyuan_25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_label_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_hourUpButton
    ui->MainMenuScreen_hourUpButton = lv_imagebutton_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_hourUpButton, 118, 63);
    lv_obj_set_size(ui->MainMenuScreen_hourUpButton, 38, 31);
    lv_imagebutton_set_src(ui->MainMenuScreen_hourUpButton, LV_IMAGEBUTTON_STATE_RELEASED, &_up_triangle_RGB565A8_38x31, NULL, NULL);
    lv_imagebutton_set_src(ui->MainMenuScreen_hourUpButton, LV_IMAGEBUTTON_STATE_PRESSED, &_up_triangle_RGB565A8_38x31, NULL, NULL);
    ui->MainMenuScreen_hourUpButton_label = lv_label_create(ui->MainMenuScreen_hourUpButton);
    lv_label_set_text(ui->MainMenuScreen_hourUpButton_label, "");
    lv_label_set_long_mode(ui->MainMenuScreen_hourUpButton_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_hourUpButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_hourUpButton, 0, LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_hourUpButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_hourUpButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_hourUpButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_hourUpButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_hourUpButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_hourUpButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_hourUpButton, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_hourUpButton, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_hourUpButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->MainMenuScreen_hourUpButton, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->MainMenuScreen_hourUpButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_hourUpButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_hourUpButton, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for MainMenuScreen_hourUpButton, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_hourUpButton, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_hourUpButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->MainMenuScreen_hourUpButton, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->MainMenuScreen_hourUpButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_hourUpButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_hourUpButton, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write style for MainMenuScreen_hourUpButton, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_hourUpButton, 0, LV_PART_MAIN | LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_hourUpButton, 255, LV_PART_MAIN | LV_IMAGEBUTTON_STATE_RELEASED);

    // Write codes MainMenuScreen_minuteUpButton
    ui->MainMenuScreen_minuteUpButton = lv_imagebutton_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_minuteUpButton, 197, 63);
    lv_obj_set_size(ui->MainMenuScreen_minuteUpButton, 38, 31);
    lv_imagebutton_set_src(ui->MainMenuScreen_minuteUpButton, LV_IMAGEBUTTON_STATE_RELEASED, &_up_triangle_RGB565A8_38x31, NULL, NULL);
    lv_imagebutton_set_src(ui->MainMenuScreen_minuteUpButton, LV_IMAGEBUTTON_STATE_PRESSED, &_up_triangle_RGB565A8_38x31, NULL, NULL);
    ui->MainMenuScreen_minuteUpButton_label = lv_label_create(ui->MainMenuScreen_minuteUpButton);
    lv_label_set_text(ui->MainMenuScreen_minuteUpButton_label, "");
    lv_label_set_long_mode(ui->MainMenuScreen_minuteUpButton_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_minuteUpButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_minuteUpButton, 0, LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_minuteUpButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_minuteUpButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_minuteUpButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_minuteUpButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_minuteUpButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_minuteUpButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_minuteUpButton, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_minuteUpButton, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_minuteUpButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->MainMenuScreen_minuteUpButton, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->MainMenuScreen_minuteUpButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_minuteUpButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_minuteUpButton, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for MainMenuScreen_minuteUpButton, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_minuteUpButton, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_minuteUpButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->MainMenuScreen_minuteUpButton, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->MainMenuScreen_minuteUpButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_minuteUpButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_minuteUpButton, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write style for MainMenuScreen_minuteUpButton, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_minuteUpButton, 0, LV_PART_MAIN | LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_minuteUpButton, 255, LV_PART_MAIN | LV_IMAGEBUTTON_STATE_RELEASED);

    // Write codes MainMenuScreen_hourDownButton
    ui->MainMenuScreen_hourDownButton = lv_imagebutton_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_hourDownButton, 118, 124);
    lv_obj_set_size(ui->MainMenuScreen_hourDownButton, 38, 31);
    lv_imagebutton_set_src(ui->MainMenuScreen_hourDownButton, LV_IMAGEBUTTON_STATE_RELEASED, &_down_triangle_RGB565A8_38x31, NULL, NULL);
    lv_imagebutton_set_src(ui->MainMenuScreen_hourDownButton, LV_IMAGEBUTTON_STATE_PRESSED, &_down_triangle_RGB565A8_38x31, NULL, NULL);
    ui->MainMenuScreen_hourDownButton_label = lv_label_create(ui->MainMenuScreen_hourDownButton);
    lv_label_set_text(ui->MainMenuScreen_hourDownButton_label, "");
    lv_label_set_long_mode(ui->MainMenuScreen_hourDownButton_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_hourDownButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_hourDownButton, 0, LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_hourDownButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_hourDownButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_hourDownButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_hourDownButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_hourDownButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_hourDownButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_hourDownButton, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_hourDownButton, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_hourDownButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->MainMenuScreen_hourDownButton, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->MainMenuScreen_hourDownButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_hourDownButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_hourDownButton, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for MainMenuScreen_hourDownButton, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_hourDownButton, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_hourDownButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->MainMenuScreen_hourDownButton, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->MainMenuScreen_hourDownButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_hourDownButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_hourDownButton, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write style for MainMenuScreen_hourDownButton, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_hourDownButton, 0, LV_PART_MAIN | LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_hourDownButton, 255, LV_PART_MAIN | LV_IMAGEBUTTON_STATE_RELEASED);

    // Write codes MainMenuScreen_minuteDownButton
    ui->MainMenuScreen_minuteDownButton = lv_imagebutton_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_minuteDownButton, 197, 124);
    lv_obj_set_size(ui->MainMenuScreen_minuteDownButton, 38, 31);
    lv_imagebutton_set_src(ui->MainMenuScreen_minuteDownButton, LV_IMAGEBUTTON_STATE_RELEASED, &_down_triangle_RGB565A8_38x31, NULL, NULL);
    lv_imagebutton_set_src(ui->MainMenuScreen_minuteDownButton, LV_IMAGEBUTTON_STATE_PRESSED, &_down_triangle_RGB565A8_38x31, NULL, NULL);
    ui->MainMenuScreen_minuteDownButton_label = lv_label_create(ui->MainMenuScreen_minuteDownButton);
    lv_label_set_text(ui->MainMenuScreen_minuteDownButton_label, "");
    lv_label_set_long_mode(ui->MainMenuScreen_minuteDownButton_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_minuteDownButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_minuteDownButton, 0, LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_minuteDownButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_minuteDownButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_minuteDownButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_minuteDownButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_minuteDownButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_minuteDownButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for MainMenuScreen_minuteDownButton, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_minuteDownButton, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_minuteDownButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->MainMenuScreen_minuteDownButton, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->MainMenuScreen_minuteDownButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_minuteDownButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_minuteDownButton, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for MainMenuScreen_minuteDownButton, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_minuteDownButton, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_minuteDownButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->MainMenuScreen_minuteDownButton, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->MainMenuScreen_minuteDownButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_minuteDownButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_minuteDownButton, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write style for MainMenuScreen_minuteDownButton, Part: LV_PART_MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
    lv_obj_set_style_image_recolor_opa(ui->MainMenuScreen_minuteDownButton, 0, LV_PART_MAIN | LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_style_image_opa(ui->MainMenuScreen_minuteDownButton, 255, LV_PART_MAIN | LV_IMAGEBUTTON_STATE_RELEASED);

    // Write codes MainMenuScreen_btn_14
    ui->MainMenuScreen_btn_14 = lv_button_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_btn_14, 266, 4);
    lv_obj_set_size(ui->MainMenuScreen_btn_14, 84, 37);
    ui->MainMenuScreen_btn_14_label = lv_label_create(ui->MainMenuScreen_btn_14);
    lv_label_set_text(ui->MainMenuScreen_btn_14_label, "关闭");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_14_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_14_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_14, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_14_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_14, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_14, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_14, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_14, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_14, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_ConfirmButton
    ui->MainMenuScreen_ConfirmButton = lv_button_create(ui->MainMenuScreen_changeTime);
    lv_obj_set_pos(ui->MainMenuScreen_ConfirmButton, 3, 2);
    lv_obj_set_size(ui->MainMenuScreen_ConfirmButton, 80, 45);
    ui->MainMenuScreen_ConfirmButton_label = lv_label_create(ui->MainMenuScreen_ConfirmButton);
    lv_label_set_text(ui->MainMenuScreen_ConfirmButton_label, "确认");
    lv_label_set_long_mode(ui->MainMenuScreen_ConfirmButton_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_ConfirmButton_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_ConfirmButton, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_ConfirmButton_label, LV_PCT(100));

    // Write style for MainMenuScreen_ConfirmButton, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_ConfirmButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_ConfirmButton, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_ConfirmButton, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_ConfirmButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_ConfirmButton, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_ConfirmButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_ConfirmButton, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_ConfirmButton, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_ConfirmButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_ConfirmButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_eventPopUp
    ui->MainMenuScreen_eventPopUp = lv_obj_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_eventPopUp, 90, 60);
    lv_obj_set_size(ui->MainMenuScreen_eventPopUp, 300, 200);
    lv_obj_set_scrollbar_mode(ui->MainMenuScreen_eventPopUp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->MainMenuScreen_eventPopUp, LV_OBJ_FLAG_HIDDEN);

    // Write style for MainMenuScreen_eventPopUp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_eventPopUp, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MainMenuScreen_eventPopUp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MainMenuScreen_eventPopUp, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MainMenuScreen_eventPopUp, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_eventPopUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_eventPopUp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_eventPopUp, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_eventPopUp, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_eventPopUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_eventPopUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_eventPopUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_eventPopUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_eventPopUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_btn_13
    ui->MainMenuScreen_btn_13 = lv_button_create(ui->MainMenuScreen_eventPopUp);
    lv_obj_set_pos(ui->MainMenuScreen_btn_13, 212, 3);
    lv_obj_set_size(ui->MainMenuScreen_btn_13, 82, 39);
    ui->MainMenuScreen_btn_13_label = lv_label_create(ui->MainMenuScreen_btn_13);
    lv_label_set_text(ui->MainMenuScreen_btn_13_label, "关闭");
    lv_label_set_long_mode(ui->MainMenuScreen_btn_13_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MainMenuScreen_btn_13_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MainMenuScreen_btn_13, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MainMenuScreen_btn_13_label, LV_PCT(100));

    // Write style for MainMenuScreen_btn_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_btn_13, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_btn_13, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_btn_13, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_btn_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_btn_13, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_btn_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_btn_13, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_btn_13, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_btn_13, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_btn_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_label_8
    ui->MainMenuScreen_label_8 = lv_label_create(ui->MainMenuScreen_eventPopUp);
    lv_obj_set_pos(ui->MainMenuScreen_label_8, 53, 86);
    lv_obj_set_size(ui->MainMenuScreen_label_8, 198, 46);
    lv_label_set_text(ui->MainMenuScreen_label_8, "Label");
    lv_label_set_long_mode(ui->MainMenuScreen_label_8, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_label_8, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_label_8, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_label_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_label_11
    ui->MainMenuScreen_label_11 = lv_label_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_label_11, 130, 0);
    lv_obj_set_size(ui->MainMenuScreen_label_11, 89, 36);
    lv_label_set_text(ui->MainMenuScreen_label_11, "");
    lv_label_set_long_mode(ui->MainMenuScreen_label_11, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_label_11, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_label_11, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_label_11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_label_11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_label_11, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_label_11, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_label_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_calendar
    ui->MainMenuScreen_calendar = lv_label_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_calendar, 0, 0);
    lv_obj_set_size(ui->MainMenuScreen_calendar, 130, 36);
    lv_label_set_text(ui->MainMenuScreen_calendar, "2024/04/22");
    lv_obj_set_style_text_align(ui->MainMenuScreen_calendar, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->MainMenuScreen_calendar, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->MainMenuScreen_calendar, MainMenuScreen_calendar_event_handler, LV_EVENT_ALL, NULL);

    // Write style for MainMenuScreen_calendar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MainMenuScreen_calendar, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_calendar, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_calendar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_calendar, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_calendar, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_calendar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MainMenuScreen_calendar, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MainMenuScreen_calendar, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MainMenuScreen_calendar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_calendar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_calendar, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_calendar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_calendar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_calendar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_Battery
    // ui->MainMenuScreen_Battery = lv_label_create(ui->MainMenuScreen);
    // lv_obj_set_pos(ui->MainMenuScreen_Battery, 214, 5);
    // lv_obj_set_size(ui->MainMenuScreen_Battery, 102, 29);
    // lv_label_set_text(ui->MainMenuScreen_Battery, "当前电量：");
    // lv_label_set_long_mode(ui->MainMenuScreen_Battery, LV_LABEL_LONG_WRAP);

    // // Write style for MainMenuScreen_Battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    // lv_obj_set_style_border_width(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(ui->MainMenuScreen_Battery, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui->MainMenuScreen_Battery, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_opa(ui->MainMenuScreen_Battery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_letter_space(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_line_space(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_align(ui->MainMenuScreen_Battery, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_top(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_right(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_bottom(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_left(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_shadow_width(ui->MainMenuScreen_Battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes MainMenuScreen_Clock
    ui->MainMenuScreen_Clock = lv_label_create(ui->MainMenuScreen);
    lv_obj_set_pos(ui->MainMenuScreen_Clock, 134, 10);
    lv_obj_set_size(ui->MainMenuScreen_Clock, 80, 27);
    lv_obj_add_flag(ui->MainMenuScreen_Clock, LV_OBJ_FLAG_CLICKABLE);
    lv_label_set_text(ui->MainMenuScreen_Clock, "19:25");
    lv_label_set_long_mode(ui->MainMenuScreen_Clock, LV_LABEL_LONG_WRAP);

    // Write style for MainMenuScreen_Clock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MainMenuScreen_Clock, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MainMenuScreen_Clock, &lv_font_youyuan_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MainMenuScreen_Clock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MainMenuScreen_Clock, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MainMenuScreen_Clock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // The custom code of MainMenuScreen.

    // Update current screen layout.
    lv_obj_update_layout(ui->MainMenuScreen);

    // Init events for screen.
    events_init_MainMenuScreen(ui);
}
