/*
	lcd 初始化和解除初始化以及清屏
 */

#include "lcd.h"
#include "main.h"

//lcd初始化
int lcd_init(LCD_DEV *lcd_dev)
{
	//打开lcd屏幕
	lcd_dev->lcd_fd = open(LCD_PATH,O_RDWR);
	//判断打开lcd是否成功
	if(lcd_dev->lcd_fd==-1)
	{
		perror("open lcd failed");
		return -1;
	}

	//lcd内存映射
	lcd_dev->addr = mmap(NULL,800*480*4,PROT_WRITE | PROT_READ,MAP_SHARED,lcd_dev->lcd_fd,0);
	if(lcd_dev->addr == NULL)
	{
		//判断设备内存是否映射成功
		perror("map memory failed");
		return -1;
	}

	return 0;
}



//lcd解除初始化
bool lcd_uninit(LCD_DEV *lcd_dev)
{

	int fd = close(lcd_dev->lcd_fd);//关闭lcd文件
	//判断是否关闭成功
	if(fd==-1)
	{
		perror("close lcd_fd failed");
		return false;
	}
	int map_fd = munmap(lcd_dev->addr,800*480);//解除lcd的内存映射
	//判断是否解除映射成功
	if(map_fd==-1)
	{
		perror("munmap lcd failed");
		return false;
	}

	return true;
}


//用于清屏
void clear_lcd(LCD_DEV *lcd_dev)
{
	//把整个屏幕刷成黑色
	int i,j;
	for(i=0;i<480;i++)//一列480个像素点
	{
		for(j=0;j<800;j++)//一行800个像素点
		{
			*(lcd_dev->addr+i*800+j) = 0x0;//0x0代表黑色 
		}
	}

	return ;
}

//触摸屏初始化
//打开触摸屏
int touch_init(LCD_DEV *lcd_dev)
{
	//打开触摸屏
	lcd_dev->ts_fd = open(TOUCH_PATH,O_RDONLY);
	//判断是否打开成功
	if(lcd_dev->ts_fd==-1)
	{
		perror("open lcd_touch failed");
		return -1;
	}

	//把触摸屏的文件描述符赋值到lcd结构体里面
	//lcd_dev->ts_fd = fd;

	return 0;
}
	
//解除触摸屏初始化
bool touch_uninit(LCD_DEV *lcd_dev)
{
	//关闭触摸屏的文件
	int fd=close(lcd_dev->ts_fd);
	//判断是否返回成功
	if(fd==-1)
	{
		perror("close touch_fd failed");
		return false;
	}

	return true;
}