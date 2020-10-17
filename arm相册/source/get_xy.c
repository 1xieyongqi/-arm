/*
	获取x，y和压力值的值
 */

#include "main.h"

int flag;

//x，y是需要赋值的x轴，y轴坐标，p是需要赋值的压力值，
//lcd_dev存储了关于触摸屏的文件描述符
int get_xy(int *x,int *y,int *p,LCD_DEV_P lcd_dev)
{

	int x1,y1;
	//定义一个储存事件的结构体
	struct input_event ts_buf;
	
	//清空一下结构体
	//把ts_buf这个地址里面，ts_buf大小的内存清空一下
	bzero(&ts_buf,sizeof(ts_buf));
	
	//因为一次只能读取一个值，因此需要循环
	while(1)
	{
	
		//在触摸屏这个文件描述符中读取ts_buf大小的数据
		read(lcd_dev->ts_fd,&ts_buf,sizeof(ts_buf));
	
		//判断是否为触摸事件
		if(ts_buf.type == EV_ABS)
		{
			//进一步判断是否为x的坐标值
			if(ts_buf.code == ABS_X)
			{
				//把当前的值赋值给x
				*x = 800*ts_buf.value/1024;

				//打印一下当前x的值
				printf("x: %d\t",*x);
	
			}

			//判断当前的值是否为y轴的坐标值
			else if(ts_buf.code == ABS_Y)
			{
				//如果是的话就把值赋值到y
				*y = 480*ts_buf.value/600;

				//打印一下当前y的值
				printf("y: %d\n",*y);
		
			}
		}

		//判断是否为按键事件(压力值在按键事件里面)
		else if(ts_buf.type == EV_KEY)
		{
			//判断是否为压力值
			if(ts_buf.code == BTN_TOUCH)
			{
				//把当前的压力值赋值给p
				*p = ts_buf.value;

				//打印一下当前p的值
				printf("p:%d\n", *p);

				//判断x和y是否已经获取到值,并且一直压着
				if(*x>0 && *y>0 && *p==0)
				{
					break;
				}
				//判断x和y是否已经获取到值,并且一直压着
/*				if(*x>0 && *y>0 && *p==1 && flag==0)
				{
					
					printf("%d\n",__LINE__ );
					x1 = *x;
					y1 = *y;
					flag++;//把falg置1，然后下次不在进入此循环
				}
printf("%d\n",__LINE__ );
				//当x和y都有值并且松手时就把第一次按下的值减去最后的xy值，然后结束整个函数
				if(*x>0 && *y>0 && *p==0)
				{
					*x = x1-*x;
					*y = y1-*y;

					return 0;
				}*/

			}
		}

	}

	return 0;
}