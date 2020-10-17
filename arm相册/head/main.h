/*
	主函数头文件
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
//点击或按键事件所需要的结构体在这个函数里面
#include <linux/input.h>

#include <unistd.h>
#include "lcd.h"

//#define LCD_PATH "/dev/fb0"
//#define TOUCH_PATH "/dev/input/event0"
#define LCD_PATH "/dev/fb0"
#define TOUCH_PATH "/dev/input/event0"

//获取坐标函数
int get_xy(int *x,int *y,int *p,LCD_DEV_P lcd_dev);

//密码登陆界面
int passworld(LCD_DEV_P lcd_dev);

//展示图片函数
void show_bmp(LCD_DEV_P lcd_dev,int x,int y,int bmp_w,int bmp_h,char *bmp_name,int num);

int show_pic(LCD_DEV_P lcd_dev);

int my_pictrue(LCD_DEV_P lcd_dev);

//int fuc_options(LCD_DEV_P lcd_dev);

//主界面用于判断点击位置
int judeg_xy(int x,int y,LCD_DEV_P lcd_dev);

int my_video(LCD_DEV_P lcd_dev);//用于视频播放

int fc_flag;//用于判断点击到哪里




#endif