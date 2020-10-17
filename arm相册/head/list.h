#ifndef _LIST_H_
#define _LIST_H_


#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//设计双向链表节点
typedef struct node
{
	//为什么用数组会报错//要用strcpy
	//char *data
	char data[128];//用于存储bmp文件名
	struct node * prev;
	struct node * next;
}LIST,*LIST_P;

LIST_P init_list();
bool dir_option(LIST_P head,char *path_name);
LIST_P creat_node(char *name);
bool insert_list(LIST_P head,LIST_P new);
void show_list(LIST_P head);
void free_list(LIST_P head);


#endif