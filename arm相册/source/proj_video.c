/*
	用于视频播放的代码
 */

#include <stdio.h>
#include "main.h"
#include "lcd.h"
//#include "show_bmp.h"
//
#define FIFO_PATH "/tmp/fifo"

int my_video(LCD_DEV_P lcd_dev)
{
	//先判断管道是否存在
	int ret = access(FIFO_PATH,F_OK);	
	if(ret != -1)
	{
		perror("fifo exist");
	}

	else
	{
		//创建管道
		ret = mkfifo(FIFO_PATH,O_CREAT | 0666);
		if(ret == -1)
		{
			perror("mkfifo failed");
			return -1;
		}
		else
			printf("mkfifo success\n");
	}

	//打开管道文件
	int fifo_fd = open(FIFO_PATH, O_RDWR);
	if(fifo_fd == -1)
	{
		perror("open failed");
		return -1;
	}

	//后台播放一个视频
system("mplayer 11.avi -quiet -slave -input file=/tmp/fifo &");

	//循环获取坐标，判断点击的位置，再发送对应的文字
	int x,y,p;
	char buf[20];
	bzero(buf,20);

	//刷一张用于点击的图片
	show_bmp(lcd_dev,0,0,800,480,"./1.bmp",1);

	while(1)
	{
		bzero(buf,20);

		get_xy(&x,&y,&p,lcd_dev);

		if(x>0&&x<400 && y>0 &&y<200)
		{
			//点击了
			//往管道写入快进的代码
			
			strcpy(buf,"seek +10\n\0");
			ret = write(fifo_fd,buf,strlen(buf));		
		}

		//点击了快退
		else if(x>400&&x<800 && y>0 &&y<200)
		{
			//点击了声音加
			//往管道写入加大10声音的代码
			
			strcpy(buf,"seek -10\n\0");
			ret = write(fifo_fd,buf,strlen(buf));	
		 }

/*		else if(x>0&&x<400 && y>200 &&y<400)
		{
			//点击了声音加
			//往管道写入加大10声音的代码
			
			strcpy(buf,"volume +10\n\0");
			ret = write(fifo_fd,buf,strlen(buf));
			if(ret == -1)
			{
				perror("write failed");
				break;
			}		
		}

		//降低声音
		else if(x>200&&x<400 && y>400 &&y<800)
		{
			//点击了声音加
			//往管道写入加大10声音的代码
			
			strcpy(buf,"volume -10\n\0");
			ret = write(fifo_fd,buf,strlen(buf));
			if(ret == -1)
			{
				perror("write failed");
				break;
			}		
		}

		//点击了静音
		else if(x>400&&x<480 && y>600 &&y<800)
		{
			//点击了声音加
			//往管道写入加大10声音的代码
		
			strcpy(buf,"mute\n\0");
			ret = write(fifo_fd,buf,strlen(buf));
			if(ret == -1)
			{
				perror("write failed");
				break;
			}		
		}*/

		//点击了退出
		else if(x>0&&x<200 && y>300 &&y<480)
		{
			//点击了声音加
			//往管道写入加大10声音的代码
			
			strcpy(buf,"quit\n\0");
			ret = write(fifo_fd,buf,strlen(buf));
	
			system("killall -9 mplayer");
			close(fifo_fd);
			break;
		}


	}

		close(fifo_fd);
}