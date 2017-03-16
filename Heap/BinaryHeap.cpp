#include "BinaryHeap.h"
#include <stdlib.h>
#include <malloc.h>

PriorityQueue Init(int maxElements)
{
	PriorityQueue h;
	if (maxElements < MinPQSize)
	{
		printf("Priority queue size is too small!\n");
		return NULL;
	}

	h = PriorityQueue(malloc(sizeof(struct HeapStruct)));
	if (h == NULL)
	{
		printf("Out of space!\n");
		return NULL;
	}

	h->data = (ElementType*)(malloc(sizeof(ElementType)*(maxElements + 1)));
	if (h->data == NULL)
	{
		printf("Out of space!\n");
		return NULL;
	}
	h->capacity = maxElements;
	h->size = 0;
	h->data[0] = MinData;
}

void Destroy(PriorityQueue h)
{
	if (h->data != NULL)
		free(h->data);
	if (h != NULL)
		free(h);
}
void MakeEmpty(PriorityQueue h)
{
	h->size = 0;
}
void Insert(ElementType x, PriorityQueue h)
{
	if (IsFull(h))
	{
		printf("Error! Priority queue is full!\n");
		return;
	}
	int i;
	for (i = ++h->size; h->data[i / 2] > x; i /= 2)
		h->data[i] = h->data[i / 2];					//precolate up
	h->data[i] = x;
}
ElementType DeleteMin(PriorityQueue h)
{
	int i, child;
	ElementType minElement, lastElement;
	if (IsEmpty(h))
	{
		printf("Priority queue is empty!\n");
		return h->data[0];
	}
	minElement = h->data[1];
	lastElement = h->data[h->size--];
	for (i = 1; i * 2 <= h->size; i = child)	//如果i*2 <= h->size,说明没有到最后一层
	{
		child = i * 2;	//左儿子
		if (child != h->size && h->data[child + 1] < h->data[child])	//如果child = h->size说明已经到最末尾的元素，i没有右孩子
			++child;

		if (lastElement > h->data[child])
			h->data[i] = h->data[child];
		else
			break;
	}
	h->data[i] = lastElement;
	return minElement;
}
ElementType FindMin(PriorityQueue h);		//查找最小元素
int IsEmpty(PriorityQueue h)
{
	return h->size == 0;
}
int IsFull(PriorityQueue h)
{
	return h->capacity == h->size;
}