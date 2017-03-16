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

PriorityQueue Init(int maxElements);	//��ʼ��
void Destroy(PriorityQueue);			//����
void MakeEmpty(PriorityQueue h);		//ʹheapΪ��
void Insert(ElementType x, PriorityQueue h);	//����
ElementType DeleteMin(PriorityQueue h);		//ɾ����СԪ��
ElementType FindMin(PriorityQueue h);		//������СԪ��
int IsEmpty(PriorityQueue h);				//�ж��Ƿ�Ϊ��
int IsFull(PriorityQueue h);				//�ж��Ƿ��Ѿ�����


#endif


