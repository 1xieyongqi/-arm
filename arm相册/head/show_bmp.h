/*
	显示图片头文件
 */

#ifndef _SHOW_H_
#define _SHOW_H_

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/input.h>

void show_bmp(int x,int y,int bmp_w,int bmp_h,char *bmp_name,int num);
int lcd_init();

#endif