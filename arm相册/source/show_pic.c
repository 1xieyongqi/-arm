	
/*
	相册内容展示
 */
#include "main.h"

int show_pic(LCD_DEV_P lcd_dev)
{
	
	//定义x，y变量以获取坐标值，p为压力值，址里可有可无
	int x=0,y=0,p=0;
	

	while(1)
	{
		
		get_xy(&x,&y,&p, lcd_dev);

		//如果点击了上一张
		if(650<x && x<800 && y>0&& y<65)
		{
			//展示上一张图片
			show_bmp(lcd_dev,0,0,800,380,"main.bmp",2);

		}

		//如果点击了下一张
		else if(650<x && x<800 && y>65&& y<130)
		{
			//展示下一张图片
			show_bmp(lcd_dev,0,0,800,380,"main.bmp",2);

		}

		//如果点击了缩小
		else if(650<x && x<800 && y>130&& y<195)
		{
			//展示一张缩小图片
			show_bmp(lcd_dev,0,0,800,380,"main.bmp",2);

		}

		//如果点击了放大
		else if(650<x && x<800 && y>195&& y<270)
		{
			//展示一张放大图片
			show_bmp(lcd_dev,0,0,800,380,"main.bmp",2);

		}

		//如果点击了幻灯片
		else if(650<x && x<800 && y>270&& y<345)
		{
			//幻灯片展示,（调用函数）
			show_bmp(lcd_dev,0,0,800,380,"main.bmp",2);

		}

		//如果点击了缩略图
		else if(650<x && x<800 && y>270&& y<415)
		{
			//有序展示所有缩小图片,（调用函数）
			show_bmp(lcd_dev,0,0,800,380,"main.bmp",2);

		}

		//如果点击了返回
		else if(650<x && x<800 && y>415&& y<480)
		{
			//结束这个函数返回上一级函数
			break;

		}

	}	
}
