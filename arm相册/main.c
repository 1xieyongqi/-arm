/*
	智能家居系统
 */

#include "main.h"
#include "lcd.h"



int main(int argc,char **argv)
{
	fc_flag=1;//用于判断点击到哪里




	//定义一个结构体存储lcd的文件描述符和内存映射
	//为结构体申请堆空间内存
	LCD_DEV_P lcd_dev = calloc(1,sizeof(LCD_DEV));
	
	//初始化lcd
	lcd_init(lcd_dev);
	touch_init(lcd_dev);
	//开机显示开机动画

	//把lcd涂成黑色
//	clear_lcd(lcd_dev);
	sleep(2);

	//测试视频播放
	my_video(lcd_dev);



	//===================开机界面============================
	show_bmp(lcd_dev,0,0,800,480,"./picture/start/1.bmp",5);
	//睡眠1000微秒
	sleep(1);
	show_bmp(lcd_dev,0,0,800,480,"./picture/start/2.bmp",1);
	sleep(1);
	//======================================================
	usleep(1000);
	//然后展示输入密码界面
	show_bmp(lcd_dev,0,0,800,100,"picture/input/0.bmp",1);

	show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

	//进入循环判断
	int x,y,p;
	while(1)
	{
		//循环记录点击的位置
		get_xy(&x,&y,&p,lcd_dev);
		switch(fc_flag)
		{
			case 0:
				//展示一张主界面图片
				
				judeg_xy(x,y,lcd_dev);//主界面的判断与函数判断
				break;

			case 1:
				//初始为开机界面
				//进入开机登录界面
				passworld(lcd_dev);
				break;

			case 2:
				
				//跳转相册的函数
				my_pictrue(lcd_dev);//跳转后把fc_flag置为0
				break;

			case 3:
				//播放音乐界面
//system("play ots.mp3");
				show_bmp(lcd_dev,0,0,800,480,"./picture/development.bmp",2);
				sleep(1);
				show_bmp(lcd_dev,0,0,800,480,"./picture/main.bmp",1);
				fc_flag =0 ;
				break;

			case 4:
				//点击了视屏
				//展示一张图片提示未开发
				show_bmp(lcd_dev,0,0,800,480,"./picture/development.bmp",2);
				sleep(1);
				show_bmp(lcd_dev,0,0,800,480,"./picture/main.bmp",1);
				fc_flag = 0;
				break;

			case 5:
				//点击了坏点测试,跳转函数
				show_bmp(lcd_dev,0,0,800,480,"./picture/development.bmp",2);
				sleep(1);
				show_bmp(lcd_dev,0,0,800,480,"./picture/main.bmp",1);
				fc_flag = 0;
				break;

			case 6:
				//点击了正在开发中
				//展示一张图片提示未开发
				show_bmp(lcd_dev,0,0,800,480,"./picture/development.bmp",2);
				sleep(1);
				show_bmp(lcd_dev,0,0,800,480,"./picture/main.bmp",1);
				fc_flag = 0;
				break;

			case 7:
				//展示一张图片提示未开发
				show_bmp(lcd_dev,0,0,800,480,"./picture/development.bmp",2);
				sleep(1);
				show_bmp(lcd_dev,0,0,800,480,"./picture/main.bmp",1);
				fc_flag = 0;
				break;
		}
	}

	//解除初始化
	lcd_uninit(lcd_dev);

	//触摸屏接触初始化
	touch_uninit(lcd_dev);
	//把lcd涂成黑色
	clear_lcd(lcd_dev);

	//把刚刚申请的堆空间内存释放掉，防止系统可用内存越来越少
	free(lcd_dev);

	return 0;
}