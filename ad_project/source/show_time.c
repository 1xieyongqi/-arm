////////////////////////////////////////////////////////////////
///	
///	在开发板上打印时间函数：
///			1、先初始化字库，通过time获取当前时间（1970至今）再通过localtime转换成需要的时间
///			2、把时分秒和年月日使用sprintf函数合成后打印
///			3、判断今天是一个星期中的第几天然后打印
///
///////////////////////////////////////////////////////////////

#include "main.h"


char day[7][50] = {"Monday","Tuesday","wednesday","Thursday","Friday","saturday","Sunday"};


//控制时间的
void *func2(void *arg)
{
	//线程分离
	pthread_detach(pthread_self());

	Init_Font();
	
	//用于存放时间的变量
	char buf[50];
	struct tm *tm;

	while(1)
	{

		bzero(&tm,sizeof(struct tm));

		time_t my_time = time(NULL);
		tm = localtime(&my_time);
		
		//当时间是下午六点以后和早上六点以前则把背景调为白色，否则是暗色	
		if(tm->tm_hour>18 && tm->tm_hour<6)
		{					
			Clean_Area(640, 0, 160, 160, 0xffffff);
		}
		else
			Clean_Area(640, 0, 160, 160, 0x0);

		//把时分秒合成放到buf中
		sprintf(buf,"%d:%d:%d",tm->tm_hour,tm->tm_min,tm->tm_sec);

		//把时间画到开发板上
		Display_characterX(640, 130, buf, 0x00ffff, 2);

		//把星期几画到开发板上
		Display_characterX(640, 70, day[tm->tm_wday], 0x00ffff, 3);

		//把年月日合成一个字符串，并输出到开发板上
		sprintf(buf,"%d/%d/%d",(tm->tm_year+1900),tm->tm_mon,tm->tm_mday);
		Display_characterX(640, 10, buf, 0x00ffff, 2);

		//每隔一秒更新一次时间
		sleep(1);			
	}

	UnInit_Font();
}