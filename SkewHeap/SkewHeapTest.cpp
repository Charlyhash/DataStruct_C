#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "SkewHeap.h"

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])));

int main()
{
	int i;
	int a[] = {10,40,24,30,36,20,12,16};
	int b[] = { 17, 13, 11, 15, 19, 21, 23 };
	int alen = LENGTH(a);
	int blen = LENGTH(b);
	SkewHeap heap1, heap2;
	heap1 = heap2 = NULL;
	printf("\n在heap1中添加元素： ");
	for (i = 0; i < alen; ++i)
	{
		printf("%d ", a[i]);
		heap1 = InsertHeap(heap1, a[i]);
	}
	printf("\nheap1的详细信息为：\n");
	PrintHeap(heap1);

	printf("\n在heap2中添加元素： ");
	for (i = 0; i <blen; ++i)
	{
		printf("%d ", b[i]);
		heap2 = InsertHeap(heap2, b[i]);
	}
	printf("\nheap2的详细信息为：\n");
	PrintHeap(heap2);

	heap1 = MergeHeap(heap1, heap2);
	printf("\nheap1的详细信息为：\n");
	PrintHeap(heap1);

	DestoryHeap(heap1);

	return 0;
}