#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "BinomialQueue.h"

#define swap(a,b) (a^=b,b^=a,a^=b)

//创建二项堆
BinHeap MakeBinHeap()
{
	BinHeap heap = NULL;
	heap = (BinHeap)malloc(sizeof(BinNode));
	if (heap == NULL)
	{
		printf("Out of sapce!\n");
		exit(1);
	}
	memset(heap, 0, sizeof(BinNode));

	return heap;
}

//获取最小根节点（*y） prev_y为最小根节点的前一个节点
static void MinimumBinHeap(BinHeap heap, BinNode **prev_y, BinNode **y)
{
	BinNode *x, *prev_x;

	if (heap == NULL)
		return;

	prev_x = heap;
	x = heap->next;
	*prev_y = NULL;
	*y = heap;

	//查找最小节点
	while (x != NULL)
	{
		if (x->data < (*y)->data)
		{
			*y = x;
			*prev_y = prev_x;
		}
		prev_x = x;
		x = x->next;
	}
}

//查找最小节点
BinNode* GetMinNode(BinHeap heap)
{
	BinNode* prev_y, *y;
	MinimumBinHeap(heap, &prev_y, &y);

	return y;
}


//将h1,h2的根表合并为一个按度数单调递增的链表
static BinHeap MergeBinHeap(BinHeap h1, BinHeap h2)
{
	BinHeap heap = NULL;		//新的根节点
	BinHeap* pos = &heap;

	while (h1 != NULL && h2 != NULL)
	{
		if (h1->degree < h2->degree)
		{
			*pos = h1;
			h1 = h1->next;
		}
		else
		{
			*pos = h2;
			h2 = h2->next;
		}
		pos = &(*pos)->next;
	}
	if (h1 == NULL)
		*pos = h2;
	else
		*pos = h1;

	return heap;
}

//将child合并到heap中
static void LinkBinHeap(BinHeap child, BinHeap heap)
{
	//child->parent->sibling = heap;
	child->parent = heap;
	child->next = heap->leftChild;
	heap->leftChild = child;
	heap->degree++;
}

//合并
BinHeap UnionBinHeap(BinHeap h1, BinHeap h2)
{
	BinNode* heap;
	BinNode *prev_x, *x, *next_x;
	heap = MergeBinHeap(h1, h2);
	if (heap == NULL)
		return NULL;

	prev_x = NULL;
	x = heap;
	next_x = x->next;

	while (next_x != NULL)
	{
		//case1 x->degree != next_x->dregee
		//case2 x->degree = next_x->dregee = next_x->sibling->degree
		if ((x->degree != next_x->degree) || ((next_x->next != NULL && next_x->degree == next_x->next->degree)))
		{
			prev_x = x;
			x = next_x;
		}
		//case3 x->degree = next_x->dregee != next_x->sibling->degree && x->data <= next_x->data
		else if (x->data <= next_x->data)
		{
			x->next = next_x->next;
			LinkBinHeap(next_x, x);
		}
		//case4 x->degree = next_x->dregee != next_x->sibling->degree && x->data > next_x->data
		else
		{
			if (prev_x == NULL)	//合并第一个节点时
				heap = next_x;
			else
				prev_x->next = next_x;
			LinkBinHeap(x, next_x);
			x = next_x;
		}
		next_x = x->next;

	}
	return heap;
}

//创建节点
static BinNode* MakeNode(ElementType data)
{
	BinNode* node;
	node = (BinNode*)malloc(sizeof(BinNode));
	if (node == NULL)
	{
		printf("malloc Binomial Node failed!\n");
		return NULL;
	}
	node->data = data;
	node->degree = 0;
	node->parent = node->next = node->leftChild = NULL;

	return node;
}

//查找
BinNode* SearchBinNode(BinHeap heap, ElementType data)
{
	BinNode *child;
	BinNode *parent = heap;
	while (parent != NULL)
	{
		if (parent->data == data)
			return parent;
		else
		{
			if ((child = SearchBinNode(parent->leftChild, data)) != NULL)
				return child;
			parent = parent->next;
		}
	}

	return NULL;
}

//插入到二项队列
BinHeap InsertBinHeap(BinHeap heap, ElementType data)
{
	BinNode* node;

	if (SearchBinNode(heap, data) != NULL)
	{
		printf("Insert Fail： the data (%d) is existed!\n", data);
		return heap;
	}

	node = MakeNode(data);
	if (node == NULL)
		return heap;
	return UnionBinHeap(heap, node);
}

//反转heap
static BinHeap Reverse(BinHeap heap)
{
	BinNode* next;
	BinNode* tail = NULL;
	if (heap == NULL)
	{
		return heap;
	}
	heap->parent = NULL;
	while (heap->next != NULL)
	{
		next = heap->next;
		heap->next = tail;
		tail = heap;
		heap = next;
		heap->parent = NULL;
	}
	heap->next = tail;

	return heap;
}

//移除最小节点并返回heap
BinHeap ExtractMin(BinHeap heap)
{
	BinNode *y, *prev_y;

	if (heap == NULL)
		return heap;
	MinimumBinHeap(heap, &prev_y, &y);
	if (prev_y == NULL)
		heap = heap->next;
	else
		prev_y->next = y->next;
	//反转最小节点的左子树，得到最小堆child,
	//这样使得最小节点所在二项树的孩子们脱离出来，成为一个独立的二项树
	BinHeap childHeap = Reverse(y->leftChild);
	heap = UnionBinHeap(heap, childHeap);

	free(y);

	return heap;
}

//减小关键字的值,node的值减小到data
static void DecreaceKey(BinHeap heap, BinNode* node, ElementType data)
{
	if ((data >= node->data) || (SearchBinNode(heap, data) != NULL))
	{
		printf("decrease failed: the new data(%d) is existed or\
			 is no smaller than current key(%d)", data, node->data);
		return;
	}
	node->data = data;

	BinNode *child, *parent;
	child = node;
	parent = node->parent;
	while (parent != NULL && child->data < parent->data)
	{
		swap(parent->data, child->data);
		child = parent;
		parent = child->parent;
	}
}

//增加关键点的值
static void IncreaseKey(BinHeap heap, BinNode* node, ElementType data)
{
	if ((data <= node->data) || (SearchBinNode(heap, data)) != NULL)
	{
		printf("Iecrease failed: the new data(%d) is existed or\
			 is no greater than current key(%d)", data, node->data);
		return;
	}
	node->data = data;
	
	BinNode *cur, *child, *least;
	cur = node;
	child = cur->leftChild;
	while (child != NULL)
	{
		if (cur->data > child->data)
		{
			//如果当前节点小于左孩子的节点，则在它的左孩子和左孩子的兄弟节点中寻找最小节点
			//然后交换最小节点的值和当前节点的值
			least = child;
			while (child->next != NULL)
			{
				if (least->data > child->data)
					least = child->next;
				child = child->next;
			}
			//交换最小节点和当前节点的值
			swap(least->data, cur->data);

			//交换之后对原最小节点进行调整，使它满足最小堆的性质：父节点《=子节点
			cur = least;
			child = cur->leftChild;
		}
		else
		{
			child = child->next;
		}
	}
}

//更新heap的节点node的值为data
static void Update(BinHeap heap, BinNode *node, ElementType data)
{
	if (node == NULL)
		return;
	if (data < node->data)
		DecreaceKey(heap, node, data);
	else if (data > node->data)
		IncreaseKey(heap, node, data);
	else
	{
		return;
	}
		
}

void UpadateBinHeap(BinHeap heap, ElementType oldData, ElementType newData)
{
	BinNode* node;
	node = SearchBinNode(heap, oldData);
	if (node != NULL)
		Update(heap, node, newData);

}

//删除节点关键字为data的值
BinHeap Delete(BinHeap heap, ElementType data)
{
	BinNode *node;
	BinNode *parent, *prev, *pos;
	if (heap == NULL)
		return heap;

	if ((node = SearchBinNode(heap, data)) == NULL)
		return heap;

	//将被删除的节点的数据上移到它所在的二项树的根节点
	parent = node->parent;
	while (parent != NULL)
	{
		swap(node->data, parent->data);
		node = parent;
		parent = node->parent;
	}
	//找到node的前一个节点
	prev = NULL;
	pos = heap;
	while (pos != node)
	{
		prev = pos;
		pos = pos->next;
	}
	//移除node
	if (prev != NULL)
		prev->next = node->next;
	else
		heap = node->next;		//删除的是头结点
	heap = UnionBinHeap(heap, Reverse(node->leftChild));

	free(node);

	return heap;
}

//打印二项堆
static void PrintHeap(BinNode* node, BinNode* prev, int direction)
{
	while (node != NULL)
	{
		//printf("%2d \n", node->key);
		if (direction == 1)
			printf("\t%2d(%d) is %2d's child\n", node->data, node->degree, prev->data);
		else
			printf("\t%2d(%d) is %2d's next\n", node->data, node->degree, prev->data);

		if (node->leftChild != NULL)
			PrintHeap(node->leftChild, node, 1);

		// 兄弟节点
		prev = node;
		node = node->next;
		direction = 2;
	}
}

void PrintBinHeap(BinHeap heap)
{
	if (heap == NULL)
		return;
	BinNode *p = heap;
	printf("== 二项堆( ");
	while (p != NULL)
	{
		printf("B%d ", p->degree);
		p = p->next;
	}
	printf(")的详细信息：\n");

	int i = 0;
	while (heap != NULL)
	{
		i++;
		printf("%d. 二项树B%d: \n", i, heap->degree);
		printf("\t%2d(%d) is root\n", heap->data, heap->degree);

		PrintHeap(heap->leftChild, heap, 1);
		heap = heap->next;
	}

	printf("\n");
}



