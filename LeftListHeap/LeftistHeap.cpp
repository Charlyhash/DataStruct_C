#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "LeftistHeap.h"

void PreOrderHeap(LeftistHeap h)
{
	if (h != NULL)
	{
		printf("%d ", h->data);
		PreOrderHeap(h->left);
		PreOrderHeap(h->right);
	}
}
void InOrederHeap(LeftistHeap h)
{
	if (h != NULL)
	{
		InOrederHeap(h->left);
		printf("%d ", h->data);
		InOrederHeap(h->right);
	}
}
void PostOrderHeap(LeftistHeap h)
{
	if (h != NULL)
	{
		PostOrderHeap(h->left);
		PostOrderHeap(h->right);
		printf("%d ", h->data);
	}
}
int GetMinimun(LeftistHeap h, ElementType* pval)
{
	if (h == NULL)
	{
		printf("Leftist Heap is null!\n");
		return -1;
	}
	else
	{
		*pval = h->data;
		return 0;
	}
}
void DestoryHeap(LeftistHeap h)
{
	if (h == NULL)
		return;
	if (h->left != NULL)
		DestoryHeap(h->left);
	if (h->right != NULL)
		DestoryHeap(h->right);
	free(h);
}

LeftistHeap MergeHeap(LeftistHeap h1, LeftistHeap h2)
{
	if (h1 == NULL)
		return h2;
	if (h2 == NULL)
		return h1;
	//合并后返回h1作为树根，因此需要保证h1->data < h2->data
	//如果h1->data > h2->data，需要交换
	if (h1->data > h2->data)
	{
		LeftistHeap tmp = h1;
		h1 = h2;
		h2 = tmp;
	}
	//将h1->right与h2合并
	h1->right = MergeHeap(h1->right, h2);
	//h1->left == null或者h1->left->npl < h1->right->npl需要交换左右孩子
	if (h1->left == NULL || h1->left->npl < h1->right->npl)
	{
		LeftistNode *tmp = h1->left;
		h1->left = h1->right;
		h1->right = tmp;
	}

	//设置npl
	if (h1->right == NULL || h1->left == NULL)
		h1->npl = 0;
	else
		h1->npl = h1->right->npl + 1;
		
	return h1;
}
LeftistHeap InsertHeap(LeftistHeap h, ElementType x)
{
	LeftistNode* NewCell;
	if ((NewCell = (LeftistNode*)malloc(sizeof(LeftistNode))) == NULL)
		return h;
	NewCell->data = x;
	NewCell->left = NewCell->right = NULL;
	NewCell->npl = 0;

	return MergeHeap(h, NewCell);
}
LeftistHeap DeleteHeap(LeftistHeap h)
{
	if (h == NULL)
		return NULL;
	LeftistHeap l = h->left;
	LeftistHeap r = h->right;

	free(h);

	return MergeHeap(l, r);
}