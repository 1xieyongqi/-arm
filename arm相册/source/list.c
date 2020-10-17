/*
	链表所用到的函数
 */
#include "list.h"

LIST_P init_list()
{
	//为头结点申请内存
	LIST_P head = calloc(1,sizeof(LIST));
	if(head == NULL)
	{
		perror("apply memory failed");
		return NULL;
	}

	//申请成功后初始化指针域，使其两个指针指向自己
	head->prev = head;
	head->next = head;

	return head;
}


bool dir_option(LIST_P head,char *path_name)
{	
	//打开指定目录的
	DIR *p = opendir(path_name);
	if(p==NULL)
	{
		perror("open directories failed");
		return false;
	}

	//循环读取目录文件
	while(1)
	{
		struct dirent *dir = readdir(p);
		//判断或否出错或者没有文件可以读取了
		if(dir==NULL)
		{
			//perror("read directories failed or end of the direntor");
			printf("read end of the file\n");
			break;
		}

		if(strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0)
			continue;

		//判断该文件是否为普通文件
		if(dir->d_type == DT_REG)
		{
			//判断该文件名后缀是否为.bmp
			if(dir->d_name == "*.bmp");
			{

				printf("%s\n",dir->d_name);
				//新建节点
				 char *buf=calloc(1,128);
                 sprintf(buf,"%s/%s",path_name,dir->d_name);

				

                 //新建节点
				LIST_P new = creat_node(buf);

				//把新节点插入到链表
				insert_list(head,new);

			}
		}

	
	}

	//判断目录文件是否为bmp图片文件
	

	//是bmp图片文件就申请节点把数据放入到链表中
	closedir(p);
}

//创建新节点
LIST_P creat_node(char *name)
{
	//为新节点申请内存
	LIST_P new = calloc(1,sizeof(LIST));
	if(new == NULL)
	{
		perror("creat new node failed");
		return NULL;
	}

	//把bmp的文件名放入到链表中
	//new->data = name;
	strcpy(new->data,name);

	new->prev = new;
	new->next = new;

	return new;
}

//把新节点插入到链表末尾
bool insert_list(LIST_P head,LIST_P new)
{
	//判断链表或者新节点是否为空
	if(head==NULL || new == NULL)
	{
		printf("the list or new_node is NULL\n");
		return false;
	}

	/*//判断链表是否为空
	LIST_P p = head;
	while(p->next != head )
	{
printf("%s:%d\n",__func__,__LINE__ );
		p=p->next;
	}
printf("%s:%d\n",__func__,__LINE__ );*/
/*	//画图比较好理解	
	new->next = p->next;//把新节点的下一个储存最后一个节点p的下一个地址
	new->prev = p;//新节点的上一个存储p的地址
	p->next = new;//p节点的下一个存储新节点的地址
	p->next->prev = new;//p的下一个的上一个存储新节点的地址*/

	new->next = head;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;

	show_list(head);


	return true;
}

//遍历链表中所有内容
void show_list(LIST_P head)
{
	//判断链表是否为空
	if(head == NULL)
	{
		printf("the list is null\n");
		return ;
	}

/*	LIST_P p = head->next;

	printf("the list context is :==============================\n");
	while(p!=head)
	{
		printf("%s\n",p->data);
		p=p->next;
	}
*/
printf("=======================\n");
	//定义一个变量
	/*LIST_P p = NULL;
	for(p = head;p->next!=head;p=p->next)
	{
		printf("%s\n",p->data);
	}
	printf("%s\n",p->data);*/

	LIST_P p = NULL;
	for(p = head->next;p!=head;p=p->next)
	{
		printf("%s\n",p->data);
	}
	//printf("%s\n",p->data);

	printf("\n");

	return ;
}

void free_list(LIST_P head)
{
	if(head == NULL)
	{
		printf("the list is null\n");
		return ;
	}
	
	LIST_P p=NULL;
	LIST_P p1=NULL;

	for(p=head,p1=head->next;p1!=head;p=p1,p1=p1->next)
	{
		//p->prev->next = p->next;
		//p->next->prev = p->prev;
		p->prev = NULL;
		p->next = NULL;

		free(p);
	}

	return ;
}