#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "SkewHeap.h"


int GetMinimun(SkewHeap h, ElementType* pval)
{
	return h->data;
}
void DestoryHeap(SkewHeap h)
{
	if (h == NULL)
		return;
	if (h->left != NULL)
		DestoryHeap(h->left);
	if (h->right != NULL)
		DestoryHeap(h->right);
	free(h);
}

//交换两个节点
static void SwapNode(SkewNode* node1, SkewNode* node2)
{
	SkewNode tmp = *node1;
	*node1 = *node2;
	*node2 = tmp;	
}

SkewHeap MergeHeap(SkewHeap h1, SkewHeap h2)
{
	if (h1 == NULL)
		return h2;
	if (h2 == NULL)
		return h1;
	if (h1->data > h2->data)
		SwapNode(h1, h2);
	SkewNode* tmp = MergeHeap(h1->right, h2);		//合并h1的右子树与h2并交换
	h1->right = h1->left;
	h1->left = tmp;

	return h1;
}
SkewHeap InsertHeap(SkewHeap h, ElementType x)
{
	SkewNode* NewNode;
	if ((NewNode = (SkewNode*)malloc(sizeof(SkewNode))) == NULL)
		return NULL;
	NewNode->data = x;
	NewNode->left = NewNode->right = NULL;

	return MergeHeap(h, NewNode);
}
SkewHeap DeleteHeap(SkewHeap h)
{
	SkewHeap r = h->right;
	SkewHeap l = h->left;
	free(h);

	return MergeHeap(l, r);
}

//打印
static void PrintHeap1(SkewHeap h, ElementType data, int dir)
{
	if (h != NULL)
	{
		if (dir == 0)
			printf("%2d is root\n", h->data);
		else
			printf("%2d is %2d's %6s child\n", h->data, data, dir == -1 ? "left" : "right");
		PrintHeap1(h->left, h->data, -1);
		PrintHeap1(h->right, h->data, 1);
	}
}

void PrintHeap(SkewHeap h)
{
	if (h != NULL)
		PrintHeap1(h, h->data, 0);
}

static bool InHeap(SkewHeap h, SkewNode* node)
{
	if (h == NULL)
		return false;
	if (h->data == node->data)
		return true;
	return InHeap(h->left, node) || InHeap(h->right, node);
}