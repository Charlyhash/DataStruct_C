#ifndef __SKIPLIST_H
#define __SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SKIPLIST_MAXLEVEL 16		//最大层数

typedef int keyType;
typedef int valueType;

//节点的数据结构
typedef struct node
{
	keyType key;			//key值
	valueType value;		//value值
	struct node *next[1];	//后继指针数组，柔性数组，可以实现结构体的变长
}Node;

//跳表的数据结构
typedef struct skip_list
{
	int level;		//最大层数
	Node* head;		//指向头结点
}skip_list;

/*
创建节点
*/
Node* create_node(int level, keyType key, valueType val);
//创建skiplist
skip_list* create_sl();

//产生随机的层数
int randomLevel();

//插入节点
int insert(skip_list* sl, keyType key, valueType val);

//删除节点
int erase(skip_list* sl, keyType key);

//查找
valueType* search(skip_list* sl, keyType key);

//打印
void print_sl(skip_list *sl);

//释放
void free_sl(skip_list* sl);

#endif
