////////////////////////////////////////////////////////////////
///	
///	从开发板获取坐标并判断是左滑还是右滑：
///		1、在图片区域左滑则展示上一张图片
///		   右滑则展示下一张图片
///		
///		2、在图片区域左滑则展示上一个视频
///		   右滑则展示下一张视频
///
///////////////////////////////////////////////////////////////
#include "main.h"
#include "list.h"
#include <linux/input.h> 

//需要读取图片的路径名
#define path_name "./picture"

//把视频的操作放入数组中
char video[4][128] = {VIDEO1,VIDEO2,VIDEO3,VIDEO4};

//定义一个标签判断目前是第几个视频
int flag=1;

void *jud_x(void *argc)
{
	//定义一个结构体用于存放第一次获取到的x和y坐标值
	struct X_Y before;
	bzero(&before,sizeof(struct X_Y));

	//新建链表，不要头节点
	LIST_P head = init_list();

	//开始读取目录下的图片
	dir_option(head,path_name);

	LIST_P pro = head;

	int x, y, p;
	while(1)
	{
		//获取坐标
		get_xy(&x,&y,&p,&before);

		//判断是否在图片区域
		if(x>600&&y>160)
		{
			//判断左滑还是右滑
			if(x - before.x1>0)
			{
				pro=pro->next;
				show_bmp(pro->data);
			}
			else if(x - before.x1<0)
			{
				pro=pro->prev;
				show_bmp(pro->data);
			}
		}

		//判断是否在视频区域
		else if(x<600 && y<400)
		{
			//判断是左滑还是右滑
			if(x - before.x1>0)
			{
				flag++;
				if(flag >= 4)
				{
					flag = 0;
				}
				system("killall mplayer");
				system(video[flag]);

			}
			else if(x - before.x1<0)
			{
				flag--;
				if(flag == 0)
				{
					flag = 4;
				}
				system("killall mplayer");
				system(video[flag]);
			}
		}
	}
	
	
	
	
	
	
	return 0;
}



////////////////////////////////////////////////////////////////
///	
///	获取坐标函数
///		1、打开触摸板，判断是否按下
///		
///		2、按下后获取第一次坐标，然后判断压力值判断是否已经松手，松手后则退出本函数
///
///////////////////////////////////////////////////////////////
int get_xy(int* x,int *y,int *p,struct X_Y *before)
{
	// 1》打开触摸屏文件
	int ts_fd = open("/dev/input/event0", O_RDONLY);
	if(ts_fd == -1)
	{
		perror("open /dev/input/event0 failed!");
		return -1;
	}
	
	struct input_event ts_buf;
	bzero(&ts_buf, sizeof(ts_buf));
	
	int falg=0;//用于记录第一次按下的值

	while(1)
	{
		// 2》读取触摸屏文件数据-->阻塞等待手指触摸屏幕，如果没有点击屏幕是会一直等待（在驱动里面设置）
		read(ts_fd, &ts_buf, sizeof(ts_buf));
		
		// 3》把触摸屏文件数据转化具体坐标和压力值
		//判断是否为绝对位移坐标事件
		if(ts_buf.type == EV_ABS)
		{
			//进一步判断是否为x轴事件
			if(ts_buf.code == ABS_X)
			{
				
				//保存具体的x轴坐标
				*x = ts_buf.value;
			
				//只保存第一次获取到的x值到结构体
				if(falg == 0)
				{
					before->x1 = *x; 
					falg++;
				}
			}
			//进一步判断是否为y轴事件
			else if(ts_buf.code == ABS_Y)
			{
				
				//保存具体的y轴坐标
				*y = ts_buf.value;

			}
		
		}
		//判断按键事件
		else if(ts_buf.type == EV_KEY)
		{
			//进一步判断是否为压力值事件
			if(ts_buf.code == BTN_TOUCH)
			{
				//保存具体的压力值
				*p = ts_buf.value;
				if(*p==0)
				{
					break;
				}
				
			}

		}
	}



	// 4》关闭文件
	close(ts_fd);

}