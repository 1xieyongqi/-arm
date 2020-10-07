#ifndef _AD_HEAD_
#define _AD_HEAD_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include "font.h"
struct X_Y
{
	int x1;
	int y1;
};

void *func1(void *arg);
void *func2(void *arg);
void *func3(void *arg);
void *func4(void *arg);

int show_bmp(char *bmp_path);
void bitmap_zoom(unsigned char *srcbuffer, int w, int h, unsigned char *destbuffer, int dw, int dh);
void show_time(char *buf);


int video_control(int *CURRENT_NUM);
int world_control(char *buf);
int pic_control();


int get_xy(int* x,int *y,int *p,struct X_Y *before);
void *jud_x(void *argc);

int CURRENT_NUM;

#define VIDEO1 "mplayer -quiet -geometry 0:0 -slave -zoom -x 640 -y 400 file=/tmp/fifo 1.mp4 >&1.txt &"
#define VIDEO2 "mplayer -quiet -geometry 0:0 -slave -zoom -x 640 -y 400  11.avi >&1.txt &"
#define VIDEO3 "mplayer -quiet -geometry 0:0 -slave -zoom -x 640 -y 400  2.mp4 >&1.txt &"
#define VIDEO4 "mplayer -quiet -geometry 0:0 -slave -zoom -x 640 -y 400  3.mp4 >&1.txt &"



#endif