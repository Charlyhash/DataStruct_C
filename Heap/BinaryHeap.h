#ifndef __BINARYHEAP_H__
#define __BINARYHEAP_H__

#include <stdio.h>

#define  MinPQSize 10
#define  MinData -1000
typedef int ElementType;

struct HeapStruct
{
	int capacity;
	int size;
	ElementType* data;
};

typedef struct HeapStruct *PriorityQueue;

PriorityQueue Init(int maxElements);	//初始化
void Destroy(PriorityQueue);			//销毁
void MakeEmpty(PriorityQueue h);		//使heap为空
void Insert(ElementType x, PriorityQueue h);	//插入
ElementType DeleteMin(PriorityQueue h);		//删除最小元素
ElementType FindMin(PriorityQueue h);		//查找最小元素
int IsEmpty(PriorityQueue h);				//判断是否为空
int IsFull(PriorityQueue h);				//判断是否已经满了


#endif


