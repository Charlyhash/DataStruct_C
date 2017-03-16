#ifndef __SKIPLIST_H
#define __SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SKIPLIST_MAXLEVEL 16		//������

typedef int keyType;
typedef int valueType;

//�ڵ�����ݽṹ
typedef struct node
{
	keyType key;			//keyֵ
	valueType value;		//valueֵ
	struct node *next[1];	//���ָ�����飬�������飬����ʵ�ֽṹ��ı䳤
}Node;

//��������ݽṹ
typedef struct skip_list
{
	int level;		//������
	Node* head;		//ָ��ͷ���
}skip_list;

/*
�����ڵ�
*/
Node* create_node(int level, keyType key, valueType val);
//����skiplist
skip_list* create_sl();

//��������Ĳ���
int randomLevel();

//����ڵ�
int insert(skip_list* sl, keyType key, valueType val);

//ɾ���ڵ�
int erase(skip_list* sl, keyType key);

//����
valueType* search(skip_list* sl, keyType key);

//��ӡ
void print_sl(skip_list *sl);

//�ͷ�
void free_sl(skip_list* sl);

#endif
