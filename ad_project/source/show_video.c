#include "main.h"


//////////////////////////////////////////////////////////
///	
///	1、把需要播放的视屏命令逐一放到一个二维数组VIDEO_ARR里面
///	2、可用二维数组也可用指针数组
///
/////////////////////////////////////////////////////////

char VIDEO_ARR[4][128] = {VIDEO1,VIDEO2,VIDEO3,VIDEO4};

//当前目录下的视屏个数
int VIDEO_MAX = 4;
//用于判断当前的视屏是第几个
int flag ;


////////////////////////////////////////////////////////////////
///	
///	1、主函数创建线程后调用的线程函数
///		
///		作用：播放一个视屏
///
///////////////////////////////////////////////////////////////
void *func1(void *arg)
{
	pthread_detach(pthread_self());
	system(VIDEO_ARR[0]);
}


////////////////////////////////////////////////////////////////
///	
///	1、通过给视屏播放器发送信号杀死当前播放的视屏
///	2、然后播放存放在函数头上面的定义的数组里的视屏
///	3、当到达数组最后一位则跳到数组第一位
///
///////////////////////////////////////////////////////////////
//========================控制视频================================
int video_control(int *CURRENT_NUM)
{
	//选择需要操作的选项
	while(1)
	{
		system("clear");
		
		printf("=================================\n");
		printf("	exit:0\n");
		printf("	next:1\n");
		printf("	pause/continue:2\n");
		printf("=================================\n");
		
		printf("please select option:");
		int num;
		scanf("%d",&num);
	
		switch(num)
		{
			case 0:
				return 0;
				break;

			case 1:
				//杀死当前播放的视屏
				system("killall -9 mplayer");
	
				//当达到最大视频个数
				if(*CURRENT_NUM>=VIDEO_MAX)
				{
					*CURRENT_NUM=0;
				}
				
				//播放下一个视屏
				system(VIDEO_ARR[*CURRENT_NUM]);

				break;

			case 2:
				if(!flag)
				{
					//发送信号暂停视屏
					system("killall -19 mplayer");
					flag ++;
	
				}

				else
				{
					//暂停后继续播放
					system("killall -18 mplayer");
					flag = 0;

				}
				break;
		}
			
		(*CURRENT_NUM)++;

	}

}
//===============================================================