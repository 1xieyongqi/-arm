/*
	密码登陆界面
		//把bmp图片放到链表中,(后期实现)
*/

#include "main.h"
char *bmp_name[14] = {"picture/input/0.bmp","picture/input/1.bmp","picture/input/2.bmp","picture/input/3.bmp",
				"picture/input/4.bmp","./picture/input/5.bmp","./picture/input/6.bmp","./picture/input/7.bmp",
				"./picture/input/8.bmp","./picture/input/9.bmp","./picture/input/10.bmp","./picture/input/11.bmp",
				"./picture/input/12.bmp","./picture/input/13.bmp"};

char pass[20] = {"1234"};//定义一个初始化密码

//密码输入界面
int passworld(LCD_DEV_P lcd_dev)
{
	//strcpy(pass,"1234");//定义一个初始化密码
printf("%d\n",__LINE__ );		
	printf("%s\n",pass);
	//定义一个数组存放输入的密码
	char input[20];
	//清空一下数组
	bzero(input,20);
printf("%d\n",__LINE__ );
	//跳转函数，获取点击，判断密码正确与否
	int x=0,y=0,p=0;
	
	//用于挪动密码存放的位置
	int i=0;

	//判断点击位置
	while(1)
	{
		//	void show_bmp(LCD_DEV_P lcd_dev,int x,int y,int bmp_w,int bmp_h,char *bmp_name,int num);
printf("%d\n",__LINE__ );
		get_xy(&x,&y,&p,lcd_dev);
	
		//如果在1的位置就
		if(35<x && x<250 && y>120&& y<195)
		{
			//每次i++
			//i++;
printf("%d\n",__LINE__ );				
			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/1.bmp",1);

			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);
			//把输入密码放入数组
			input[i] = '1';
			//执行完后加1
			i++;
printf("%d\n", i);
		}

		//如果在2的位置就
		else if(250<x && x<505 && y>120&& y<195)
		{
			//每次i++
			//i++;

			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/2.bmp",1);
//			usleep(200);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			//把输入密码放入数组
			input[i] = '2';
			//执行完后加1
			i++;
		}

		//如果在3的位置就
		else if(505<x && x<740 && y>120&& y<195)
		{
			//每次i++
			//i++;
printf("%d\n",__LINE__ );	
			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/3.bmp",1);

			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);
//			usleep(200);
			//把输入密码放入数组
			input[i] = '3';
			//执行完后加1
			i++;
		}

		//如果在4的位置就
		else if(35<x && x<250 && y>195&& y<280)
		{
			//每次i++
			//i++;
printf("%d\n",__LINE__ );
			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);

			show_bmp(lcd_dev,100,0,800,380,"./picture/click/4.bmp",1);

//			usleep(200);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			//把输入密码放入数组
			input[i] = '4';
			//执行完后加1
			i++;
		}

		//如果在5的位置就
		else if(250<x && x<505 && y>195&& y<280)
		{
			//每次i++
			//i++;

			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/5.bmp",1);
//			usleep(200);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			//把输入密码放入数组
			input[i] = '5';
			//执行完后加1
			i++;
		}

		//如果在6的位置就
		else if(505<x && x<740 && y>195&& y<280)
		{
			//每次i++
			//i++;

			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/6.bmp",1);
//			usleep(200);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			//把输入密码放入数组
			input[i] = '6';
			//执行完后加1
			i++;
		}

		//如果在7的位置就
		else if(35<x && x<250 && y>280&& y<365)
		{
			//每次i++
			//i++;

			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/7.bmp",1);
//			usleep(200);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			//把输入密码放入数组
			input[i] = '7';
			//执行完后加1
			i++;
		}

		//如果在8的位置就
		else if(250<x && x<505 && y>280&& y<365)
		{
			//每次i++
			//i++;
	
			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/8.bmp",1);
//			usleep(200);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			//把输入密码放入数组
			input[i] = '8';
			//执行完后加1
			i++;
		}

		//如果在9的位置就
		else if(505<x && x<740 && y>280&& y<365)
		{
			//每次i++
			//i++;
	
			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/9.bmp",1);
//			usleep(200);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			//把输入密码放入数组
			input[i] = '9';
			//执行完后加1
			i++;
		}

		//如果在0的位置就
		else if(250<x && x<505 && y>365&& y<460)
		{
			//每次i++
			//i++;

			//展示按下去的效果
			show_bmp(lcd_dev,0,0,800,100,bmp_name[i+1],1);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/0.bmp",1);
//			usleep(200);
			show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			//把输入密码放入数组
			input[i] = '0';
			//执行完后加1
			i++;
		}

		//如果在确认键的位置就
		else if(505<x && x<740 && y>365&& y<460)
		{

			show_bmp(lcd_dev,100,0,800,380,"./picture/click/ok.bmp",1);
			usleep(200);
				
			printf("%s\n",input );
			//比较两个密码是否一样
			if(0==strcmp(input,pass))
			{
				//结束函数跳转到主界面
				fc_flag = 0;//置为0，让结束此次循环后回到主函数执行主界面的函数
				show_bmp(lcd_dev,0,0,800,480,"./picture/main.bmp",1);
				
				break;
			}

			else
			{
				//展示密码错误界面
				show_bmp(lcd_dev,0,0,800,480,"./picture/error.bmp",2);
				sleep(1);
				//把i重新置为0，然后重新输入密码
				i=0;
				bzero(input,strlen(input));
				//然后展示输入密码界面
				show_bmp(lcd_dev,0,0,800,100,bmp_name[i],1);
				show_bmp(lcd_dev,100,0,800,380,"./picture/click/null.bmp",1);

			}

		}

		//执行完后加1
		//i++;

		if(i>12)
		{
			printf("the passworld is to long!\n");

			show_bmp(lcd_dev,0,0,800,380,"./picture/error.bmp",2);
			usleep(1000);

			i=0;
		}

	}
	return 0;
}