/*
	判断主界面点击的位置
 */
#include "main.h"

int judeg_xy(int x,int y,LCD_DEV_P lcd_dev)
{
	

	//如果点击了相册
		if(50<x && x<200 && y>120&& y<235)
		{
			//跳转相册的函数
			//展示一张右边用于点击的代码
			show_bmp(lcd_dev,0,0,800,480,"./picture/pic/picture.bmp",1);
			//show_bmp(lcd_dev,0,0,650,480,"./picture/show/2.bmp",1);
			show_bmp(lcd_dev,0,0,650,480,"./picture/show/5.bmp",1);
			fc_flag = 2;


		}

		//如果点击了音乐
		else if(280<x && x<430 && y>120&& y<235)
		{
			//播放一首歌吧
			fc_flag = 3;

		}

		//如果点击了视屏
		else if(530<x && x<680 && y>120&& y<235)
		{
			//展示一张图片提示未开发
			fc_flag = 4;

		}

		//如果点击了抖音
		else if(50<x && x<200 && y>300&& y<420)
		{
			//展示一张图片提示未开发
			fc_flag = 5;

		}

		//如果点击了正在开发中
		else if(50<x && x<200 && y>295&& y<415)
		{
			//展示一张图片提示正在开发中
			fc_flag = 6;

		}

printf("%d\n",fc_flag);
}