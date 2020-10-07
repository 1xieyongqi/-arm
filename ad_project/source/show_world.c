
//////////////////////////////////////////////////////////
///	
///	创建播放文字广告的线程后执行的线程函数：
///	
///	1、文字滚动效果：通过定义一个i变量从0开始每次往前挪一个一个像素点
///					当到达屏幕最末端就从屏幕开头重新往前滚动
///					
///	2、修改文字：通过创建线程函数传递需要打印的数组地址
///				当下面选择修改广告文字时修改的也是最初的数组的地址
///
/////////////////////////////////////////////////////////


#include "main.h"
//宏替换，128为存放输入的字符串的数组大小
#define WORLD_SIZE 128
#define IP_ADDR "192.168.19.118"

void *func3(void *arg)
{
	pthread_detach(pthread_self());

	//字库初始化
	Init_Font();
	int i=0;
	while(1)
	{

		if(i>800)
		{
			i=0;
		}

		//初始化一个位图空间
		Clean_Area(0, 400, 800, 80, 0x000000ff);
	
		//把传递进来的参数打印出来，每次往前挪一个像素点
		Display_characterX(i, 400,(char *)arg , 0x00ff0000, 4);

		//睡眠一会，防止刷太快视觉上有卡顿感
		usleep(30000);
		i++;
	}

	UnInit_Font();
}



////////////////////////////////////////////////////////////////
///	
///	修改文字广告的函数：
///			1、通过从输入缓冲区获取数据后赋值到在屏幕打印的数组
///			
///			2、使用fgets输入不会阻塞等待，
///			  但是使用scanf函数会导致程序继续执行下去，回到主函数打印了主函数中的选择界面
///
///////////////////////////////////////////////////////////////
int world_control(char *world_buf)
{
	
	//清屏一下，定义一个数组用于存放输入的字符串
	system("clear");
	
	char WORLD_BUF[WORLD_SIZE];
	bzero(WORLD_BUF,sizeof(WORLD_BUF));

	//创建套接字socket
	int socketfd = socket(AF_INET,SOCK_STREAM,0);
	if(socketfd < -1)
	{
		perror("socket failed");
		return -1;
	}

	//conect连接服务器
	struct sockaddr_in my_addr;

	//初始化协议和端口
	my_addr.sin_family = AF_INET;
	my_addr.sin_port   = htons(12500);
	my_addr.sin_addr.s_addr = inet_addr(IP_ADDR);//设置要绑定的ip地址


	int ret = conect(socketfd,(struct sockaddr *)&my_addr,sizeof(my_addr));
	if(ret < 0)
	{
		perror("connect failed");
		close(socketfd);
		return -1;
	}

	//读取数据recv函数
	while(1)
	{
		//bzero(world_buf,128);

		//把数据读取到world_buf
		recv(socketfd,world_buf,sizeof(world_buf),0);

		//if()

	}

	//关闭套接字文件描述符
	close(socketfd);


	//printf("please input string:");
	
	//需要用scanf函数因为fgets不会阻塞等待
	//fgets(WORLD_BUF,128,stdin);
	//scanf("%s",WORLD_BUF);

	//把输入的数据去掉回车符后放到打印文字中
	//先清空一下当前显示的东西,必须是128如果是使用sizeof(world_buf)，则只会清空四个字节一个指针的大小
	

	strncpy(world_buf,WORLD_BUF,strlen(WORLD_BUF));

	return 0;
}