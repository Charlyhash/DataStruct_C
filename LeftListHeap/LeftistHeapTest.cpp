#include "LeftistHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )
//�����ã��ο�http://www.cnblogs.com/skywang12345/p/3638327.html
static void PrintHeap(LeftistHeap h, ElementType data, int dir = 0)
{
	if (h != NULL)
	{
		if (dir == 0)
			printf("%2d(%d) is root\n",h->data, h->npl);
		else
			printf("%2d(%d) is %2d's %6s child\n", h->data, h->npl, data, dir == 1 ? "right" : "left");
		PrintHeap(h->left, h->data, -1);
		PrintHeap(h->right, h->data, 1);
	}
}

int main()
{
	int i;
	int a[] = { 10,40,24,30,36,20,12,16 };
	int b[] = { 17,13,11,15,19,21,23 };
	int alen = LENGTH(a);
	int blen = LENGTH(b);
	LeftistHeap ha, hb;

	ha = hb = NULL;

	printf("��ӵ�ha:\n");
	for (i = 0; i < alen; ++i)
	{
		printf("%d ", a[i]);
		ha = InsertHeap(ha, a[i]);
	}
	printf("ha����ϸ��Ϣ��\n");
	PrintHeap(ha, ha->data, 0);

	printf("\n��ӵ�hb:\n");
	for (i = 0; i < blen; ++i)
	{
		printf("%d ", b[i]);
		hb = InsertHeap(hb, b[i]);
	}
	printf("\nhb����ϸ��Ϣ\n");
	PrintHeap(hb, hb->data, 0);

	ha = MergeHeap(ha, hb);
	printf("\n�ϲ������ϸ��Ϣ��\n");
	PrintHeap(ha, ha->data, 0);

	ha = DeleteHeap(ha);
	printf("\nɾ����СԪ�غ�\n");
	PrintHeap(ha, ha->data, 0);
	printf("\n���������\n");
	PreOrderHeap(ha);
	printf("\n���������\n");
	InOrederHeap(ha);
	printf("\n�������\n");
	PostOrderHeap(ha);
	printf("\n��СԪ�أ�\n");
	int val;
	if (GetMinimun(ha, &val) == 0)
		printf("%d\n", val);
	DestoryHeap(ha);

}