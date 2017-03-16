#include <stdio.h>
#include "BinomialQueue.h"

#define LENGTH(a) ((sizeof(a))/ (sizeof(a[0])))

int a[] = { 12, 7, 25, 15, 28, 33, 41 };
int b[] = { 18, 35, 20, 42, 9, 31, 23, 6, 48, 11, 24, 52, 13 };

int main()
{
	int i;
	int alen = LENGTH(a);
	int blen = LENGTH(b);
	BinHeap ha, hb;
	ha = hb = NULL;

	printf("\n二项堆一次添加： ");
	for (i = 0; i < alen; ++i)
	{
		printf("%d ", a[i]);
		ha = InsertBinHeap(ha, a[i]);
	}
	printf("\n");
	printf("The binomial heap is :\n");
	PrintBinHeap(ha);

	printf("\n二项堆一次添加： ");
	for (i = 0; i < blen; ++i)
	{
		printf("%d ", b[i]);
		hb = InsertBinHeap(hb, b[i]);
	}
	printf("\n");
	printf("The binomial heap is :\n");
	PrintBinHeap(hb);

	ha = UnionBinHeap(ha, hb);
	printf("合并后ha详细信息:\n");
	PrintBinHeap(ha);

	//删除：
	ha = Delete(ha, 6);
	printf("删除后ha详细信息:\n");
	PrintBinHeap(ha);

	//更新
	UpadateBinHeap(ha, 42, 2);
	printf("更新后ha详细信息:\n");
	PrintBinHeap(ha);

	UpadateBinHeap(ha, 2, 42);
	printf("更新后ha详细信息:\n");
	PrintBinHeap(ha);

	return 0;
}