////////////////////////////////////////////////////////////////
///	
///	广告机主函数：用于创建线程及控制广告机
///
///////////////////////////////////////////////////////////////
#include "main.h"

char date[128] = "date 090306202020.10";

int main(int argc,char **argv)
{
	system(date);

	//用于打印文字广告的
	char world_buf[128]= "i am boy";

	//=================创建三个线程=====================
	pthread_t pid[4];

	pthread_create(&pid[0],NULL,func1,NULL);//播放视屏
	pthread_create(&pid[1],NULL,func2,NULL);//展示时间
	pthread_create(&pid[2],NULL,func3,world_buf);//展示文字
	pthread_create(&pid[3],NULL,func4,NULL);//播放指定图片
	pthread_create(&pid[3],NULL,jud_x,NULL);//滑动
	//================================================



////////////////////////////////////////////////////////////////
///	
///	广告机终端控制部分
///
///////////////////////////////////////////////////////////////
	//用于播放视频的第几个
	int CURRENT_NUM=1;
	int num;
	while(1)
	{
		system("clear");
		printf("=================================\n");
		printf("	exit 		: 0\n");
		printf("	video control 	: 1\n");
		printf("	world control 	: 2\n");
		printf("	picture control : 3\n");
		printf("=================================\n");
		printf("\n");
		
		printf("pleaes enter a num:");
		scanf("%d",&num);

		//用于循环控制视屏图片和广告文字
		switch(num)
		{
			case 0:
				//按下0退出整个程序
				system("killall mplayer");
				exit(0);

				break;
			
			case 1:
				//视屏播放控制函数
				video_control(&CURRENT_NUM);
				
				break;
			
			case 2:
				//广告文字控制函数
				world_control(world_buf);
			
				break;

			case 3:
				//图片控制函数
				pic_control();
			
				break;
		}

	}

}