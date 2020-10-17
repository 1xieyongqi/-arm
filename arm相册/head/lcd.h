#ifndef _LCD_H_
#define _LCD_H_

//系统输入输出用到的头文件
#include <stdio.h>
//==========文件操作所需的头文件============
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//========================================
//字符串操作所需的头文件
#include <string.h>
#include <strings.h>
//用于映射的头文件
#include <sys/mman.h>

#include <stdbool.h>
#include <unistd.h>//关闭文件用到的函数


//定义一个结构体储存lcd的文件描述符和映射的内存地址
typedef struct lcd_init
{
	int lcd_fd;//lcd文件描述符
	unsigned int *addr;//映射内存首地址
	int ts_fd;//触摸屏文件描述符

}LCD_DEV,*LCD_DEV_P;


//初始化lcd
int lcd_init(LCD_DEV *lcd_dev);

//解除初始化
bool lcd_uninit(LCD_DEV *lcd_dev);

//清屏：整个屏幕涂黑
void clear_lcd(LCD_DEV *lcd_dev);

//触摸屏初始化
int touch_init(LCD_DEV *lcd_dev);

//触摸屏解除初始化
bool touch_uninit(LCD_DEV *lcd_dev);


#endif