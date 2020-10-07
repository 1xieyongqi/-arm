////////////////////////////////////////////////////////////////
///	
///	1、刷图：先把一张图片按要求大小后放到指定位置
///	2、控制图片：直接在指定位置把输入的路径下的图片刷出来，会自动覆盖
///
///////////////////////////////////////////////////////////////


#include "main.h"

#define WIDTH 800  //屏幕宽
#define HEIGHT 480  //屏幕高

#define DESTW 160  //放缩后宽
#define DESTH 240  //放缩后高

//把原图宽高位w，h转化为宽高位dw, dh
void bitmap_zoom(unsigned char *srcbuffer, int w, int h, unsigned char *destbuffer, int dw, int dh)
{
	//保证可以缩小为原来的倍数，如果不乘100；如果不是整除，在缩放后会出现一些问题不是原来的缩放倍数
	int perW = w*100.0/dw;
	int perH = h*100.0/dh;
	for(int j=0; j<dh; j++)
	{
		for(int i=0; i<dw; i++)
		{
			destbuffer[i*3+0+j*dw*3] = srcbuffer[3*i*perW/100+0+j*perH*w*3/100];
			destbuffer[i*3+1+j*dw*3] = srcbuffer[3*i*perW/100+1+j*perH*w*3/100];
			destbuffer[i*3+2+j*dw*3] = srcbuffer[3*i*perW/100+2+j*perH*w*3/100];			
		}
	}
}


//展示图片的函数
int show_bmp(char *bmp_path)
{
	//1.打开设备
	int fd  = open("/dev/fb0", O_RDWR);
	if(fd < 0)
	{
		perror("open error");
		exit(1);
	}

	//2.映射
	unsigned int *mptr = (unsigned int*)mmap(NULL, WIDTH*HEIGHT*4,PROT_READ|PROT_WRITE,
	                                         MAP_SHARED, fd, 0);
	if(mptr == (void*)-1)
	{
		perror("mmap error");
		exit(1);
	}

	//1.读取图片头， 读取图片数据
	int picfd = open(bmp_path, O_RDONLY);
	char buffer[800*480*3];
	read(picfd, buffer, 54); //读54字节头
	read(picfd, buffer, 800*480*3);//读图片数据
	close(picfd);

	
	//把800*480图缩小为DESTW*DESTH
	char destbuffer[DESTW*DESTH*3];
	bitmap_zoom(buffer, 800, 480, destbuffer, DESTW,DESTH);
	
	
	//保存绘图的位置---(200,120)
	unsigned int *p = mptr+160*WIDTH+640;
	
	//3.绘图
	for(int i=DESTH-1; i>0; i--)
	{
		for(int j=0; j<DESTW; j++)
		{
			memcpy(p+j, destbuffer+3*j+3*DESTW*i, 3);
		}
		p+=WIDTH;
	}

	//4.释放映射
	munmap(mptr, HEIGHT*WIDTH*4);

	//5.关闭设备
	close(fd);
	return 0;

}


//线程创建后执行的函数
void *func4(void *arg)
{
	pthread_detach(pthread_self());
	show_bmp("./1.bmp");

}



////////////////////////////////////////////////////////////////
///	
///	控制图片的函数：
///		1、输入图片路径，就去打印路径下的图片
///		2、输入quit则退出
///
///////////////////////////////////////////////////////////////
int pic_control()
{
	//先遍历当前目录下的所有图片，选择需要的操作

	while(1)
	{

		system("clear");
		
		printf("=================================\n");
		printf("	you can enter:\n");
		printf("	picture path: \n");
		printf("!!!!!if you want exit:please enter: \"quit\"!!!!!\n");
		printf("=================================\n");
		
		char buf[128];
		bzero(buf,sizeof(buf));

		printf("please enter :\n");
		scanf("%s",buf);


		if(!strcmp(buf,"quit"))
			break;

		show_bmp(buf);
	}
	

	return 0;
}