/*
	实现点击相册后的函数
 */

#include "main.h"
#include "list.h"
#include "lcd.h"

#define path_name "./picture/show"
int reduce_pic(LIST_P head,LCD_DEV_P lcd_dev);
int slide_flag;

int my_pictrue(LCD_DEV_P lcd_dev)
{
	//新建链表，不要头节点
	LIST_P head = init_list();

	//开始读取目录下的图片
	dir_option(head,path_name);

	show_list(head);
printf("%d\n",__LINE__ );
	//判断点击的位置进行操作
	int x=0,y=0,p=0;
	int flag;
	LIST_P pro = head;
	while(1)
	{
		get_xy(&x,&y,&p,lcd_dev);

		//点击了上一张的话
		if(650<x && x<800 && y>0&& y<65)
		{
			//展示上一张图片
			pro = pro->prev;
			show_bmp(lcd_dev,0,0,650,480,pro->data,1);

		}

		//如果点击了下一张
		else if(650<x && x<800 && y>65&& y<130)
		{
			//展示下一张图片

			pro = pro->next;

			printf("the next：%s\n",pro->data);
			show_bmp(lcd_dev,0,0,650,480,pro->data,1);
			
		}

		//点击了缩小的话
		else if(650<x && x<800 && y>130&& y<195)
		{
			//先刷黑一下
			clear_lcd(lcd_dev);

			show_bmp(lcd_dev,0,0,800,480,"./picture/pic/picture.bmp",1);

			//展示一张缩小图片
			show_bmp(lcd_dev,0,0,650,480,pro->data,6);
			
		}

		//点击了放大的话
		else if(650<x && x<800 && y>195&& y<275)
		{
			//展示一张放大图片
			show_bmp(lcd_dev,0,0,650,480,pro->data,7);
			
		}

		//点击了幻灯片的话
		else if(650<x && x<800 && y>275&& y<350)
		{
			//幻灯片展示目录下的所有图片
			LIST_P p = NULL;
			int i=0;//用于for循环
			
			//展示链表中的所以图片
			for(p=head;p->next!=head;p=p->next)
			{
				printf("%d\n",i);
				show_bmp(lcd_dev,0,0,650,480,p->data,i%5);
				sleep(1);
				i++;
			}
			
		}

		//点击了缩略图的话
		else if(650<x && x<800 && y>350&& y<415)
		{
			//按循序展示所有图片缩小的图片
			int i=0,j=0;
			LIST_P p=head;
			/*
			for(p=head->next;p!=head;p=p->next)
			{
					if(i+150>650)
					{
						i=0;
						j+=200;
					}
					show_bmp(lcd_dev,j,i,650,480,p->data,6);
					i+=200;
					
					
				}
			*/
			//先刷黑一下
			clear_lcd(lcd_dev);

			//i为y轴坐标，j为x轴坐标，每次加上一张图片的长和宽
			for(i=0;i<480&&i+200<480;i+=200)
			{
				for(j=0;j<650&&j+150<800;j+=200)
				{
					p=p->next;
					if(p==head)
						break;
					printf("i:%d;\tj:%d\n",i,j);
					show_bmp(lcd_dev,i,j,650,480,p->data,6);
					
				}
			}
			
			//点击缩略图后，跳转到相应图片
			//调用本函数，如果点击返回就回到缩略图界面
			reduce_pic(head,lcd_dev);			
		}

		//点击了返回的话的话
		else if(650<x && x<800 && y>415&& y<480)
		{

			//结束这个函数，返回上一个函数
			fc_flag = 0;//把fc_flag置为0，然后返回主函数后继续从主界面继续开始

			show_bmp(lcd_dev,0,0,800,480,"./picture/main.bmp",1);

			free_list(head);
			return 0;
		}

	
//printf("%d\n",__LINE__ );

	}

	
}

//用于判断点击的是那个缩略图
int reduce_pic(LIST_P head,LCD_DEV_P lcd_dev)
{
	if(head == NULL)
	{
		printf("the list is null\n");
		return -1;
	}

	int x,y,p1;
	int i;
	get_xy(&x,&y,&p1,lcd_dev);
	LIST_P p = head->next;

	if(x>0&&x<200&&y>0&&y<200)
	{
		//先展示一下右边点击的图片
		show_bmp(lcd_dev,0,0,800,480,"./picture/pic/picture.bmp",1);
		//点击的是第一张
		show_bmp(lcd_dev,0,0,650,480,p->data,1);

		return 0;
	}

	else if(x>200&&x<400&&y>0&&y<200)
	{
		
		//点击的是第二张
		for(i=0;i<1;i++)
		{
			p=p->next;
		}
		//先展示一下右边点击的图片
		show_bmp(lcd_dev,0,0,800,480,"./picture/pic/picture.bmp",1);
		show_bmp(lcd_dev,0,0,650,480,p->data,1);

		return 0;
	}

	else if(x>400&&x<600&&y>0&&y<200)
	{
		
		//点击的是第三张
		for(i=0;i<2;i++)
		{
			p=p->next;
		}
		//先展示一下右边点击的图片
		show_bmp(lcd_dev,0,0,800,480,"./picture/pic/picture.bmp",1);
		show_bmp(lcd_dev,0,0,650,480,p->data,1);

		return 0;
	}

	else if(x>600&&x<800&&y>0&&y<200)
	{
		//先展示一下右边点击的图片
		show_bmp(lcd_dev,0,0,800,480,"./picture/pic/picture.bmp",1);
		
		//点击的是第四张
		for(i=0;i<3;i++)
		{
			p=p->next;
		}
		show_bmp(lcd_dev,0,0,650,480,p->data,1);
		return 0;
	}

	else if(x>0&&x<200&&y>200&&y<400)
	{
		//先展示一下右边点击的图片
		show_bmp(lcd_dev,0,0,800,480,"./picture/pic/picture.bmp",1);
		
		//点击的是第五张
		for(i=0;i<4;i++)
		{
			p=p->next;
		}
		show_bmp(lcd_dev,0,0,650,480,p->data,1);
		return 0;
	}

	else if(x>200&&x<400&&y>200&&y<400)
	{
		//先展示一下右边点击的图片
		show_bmp(lcd_dev,0,0,800,480,"./picture/pic/picture.bmp",1);
		//点击的是第六张
		for(i=0;i<5;i++)
		{
			p=p->next;
		}
		show_bmp(lcd_dev,0,0,650,480,p->data,1);
		
		return 0;
	}


	return 0;
}