#include "main.h"
#include <unistd.h>

void show_bmp(LCD_DEV_P lcd_dev,int x,int y,int bmp_w,int bmp_h,char *bmp_name,int num)
{
	printf("bmp_w:%d\n",bmp_w );
	printf("bmp_h:%d\n",bmp_h );
	printf("bmp_name:%s\n",bmp_name);
	
	//1、打开bmp图片
	FILE *fp = fopen(bmp_name,"r");

	if(fp==NULL)
	{

		printf("open %s  failed\n",bmp_name);
		//perror("");
		return ;
	}
	
	//2、跳过54个头信息
	lseek(fp->_fileno, 54, SEEK_SET);
	
	//判断是否为4的倍数
	int ret = (4-bmp_w*3%4)%4;

	//3、读取bmp图片
	unsigned char *bmp_buf = calloc(1,bmp_w*bmp_h*3+ret*bmp_h);
	
	bzero(bmp_buf,bmp_w*bmp_h*3+ret*bmp_h);

	int i,j;

	fread(bmp_buf,bmp_w*bmp_h*3+ret*bmp_h,1,fp);//读取字节数据


	//4、关闭bmp图片
	fclose(fp);
	
	//6、把bmp数据转换成lcd合适的数据
	unsigned int *lcd_buf = malloc(bmp_w*bmp_h*4);

	for(j=0; j<bmp_h; j++)
		for(i=0; i<bmp_w; i++)
		{
			//位操作，把三个char数据放置到指定位置然后赋值给int型的数据
			lcd_buf[j*bmp_w+i] = (bmp_buf[3*i+3*j*bmp_w+ret*j+0]<<0) | (bmp_buf[3*i+3*j*bmp_w+ret*j+1]<<8) | (bmp_buf[3*i+3*j*bmp_w+ret*j+2]<<16) ;
			
		}

	//8、把bmp数据写入映射的内存中
	int l;
	int m=4;//要分多少块
	int k=bmp_w/m;
	int b=0,c=0;//用于bmp收缩
	int mul_m=0,mul_i=0;//用于扩大特效
	int mul=4;


	switch(num)
	{
		//正常显示
		case 1:
			for(i=0;i<bmp_h;i++)
			{
				for(j=0;j<bmp_w;j++)
				{
					*(lcd_dev->addr+800*i+800*x+y+j) = lcd_buf[(bmp_h-1-i)*bmp_w+j];//通过bmp_h-1-i从最后一行开始放到开发板第一行
				}

			}
			break;
		//从左到右
		case 2:
			for(j=0;j<bmp_w;j++)
			{
				for(i=0;i<bmp_h;i++)
				{
					*(lcd_dev->addr+800*i+800*x+y+j) = lcd_buf[(bmp_h-1-i)*bmp_w+j];
				}

			}
			break;
		//从右到左
		case 3:
			for(j=0;j<bmp_w;j++)
			{
				for(i=0;i<bmp_h;i++)
				{
					*(lcd_dev->addr+800*(bmp_h-1-i)+800*x+y+(bmp_w-j)) = lcd_buf[i*bmp_w+j];
				}

			}
			break;

		//从下到上
		case 4:
			for(i=0;i<bmp_h;i++)
			{
				for(j=0;j<bmp_w;j++)
				{
					*(lcd_dev->addr+800*(bmp_h-1-i)+800*x+y+j) = lcd_buf[i*bmp_w+j];//通过bmp_h-1-i从最后一行开始放到开发板第一行
				}
				usleep(1000);
			}
			break;

		//横百叶
		case 5:
			//每行写入一个字节，然后跳过k个字节继续写入一个
			for(i=0;i<bmp_w/m;i++)
			{
				for(j=0;j<bmp_h;j++)
				{
					for(l=0;l<m;l++)
						*(lcd_dev->addr+800*(bmp_h-1-j)+k*l+800*x+y+i) = lcd_buf[j*bmp_w+k*l+i];//每次就跳过k*l个字节写入
				}
				usleep(1000);
			}
			break;

			//收缩
		case 6:

			for(b=0,j=0;j<bmp_h;j+=mul,b++)
			{
				//设置一个b，c用于写入开发板的行和列
				for(i=0,c=0;i<bmp_w;i+=mul,c++)
				{
						//每次跳过一个像素写入数据，会丢失数据，有机会尝试四个像素点每个平均后赋值到一个像素点上
						*(lcd_dev->addr+800*b+800*x+y+c) = lcd_buf[(bmp_h-1-j)*bmp_w+i];
						
				}
				usleep(1000);
				
			}
	
			break;


			//扩大
		case 7:
			for(int j1=0,j=0;j<bmp_h&&j1+2<480;j++,j1+=2)
			{
				for(int i1=0,i=0;i<bmp_w&&i1+2<650;i++,i1+=2)
				{
					for(int mul_m=0;mul_m<2;mul_m++)
					{//每次重复读取
						for(int k=0;k<2;k++)
						{
							*(lcd_dev->addr+(800*(j1+mul_m))+(i1+k)) = lcd_buf[(bmp_h-1-j)*bmp_w+i];
							
						}
						
					}
				}
				
			}
			break;


	}
printf("%d\n",__LINE__ );


		free(bmp_buf);	
		free(lcd_buf);
		return ;

	
}