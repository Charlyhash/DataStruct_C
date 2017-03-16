#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "BinomialQueue.h"

#define swap(a,b) (a^=b,b^=a,a^=b)

//���������
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

//��ȡ��С���ڵ㣨*y�� prev_yΪ��С���ڵ��ǰһ���ڵ�
static void MinimumBinHeap(BinHeap heap, BinNode **prev_y, BinNode **y)
{
	BinNode *x, *prev_x;

	if (heap == NULL)
		return;

	prev_x = heap;
	x = heap->next;
	*prev_y = NULL;
	*y = heap;

	//������С�ڵ�
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

//������С�ڵ�
BinNode* GetMinNode(BinHeap heap)
{
	BinNode* prev_y, *y;
	MinimumBinHeap(heap, &prev_y, &y);

	return y;
}


//��h1,h2�ĸ���ϲ�Ϊһ����������������������
static BinHeap MergeBinHeap(BinHeap h1, BinHeap h2)
{
	BinHeap heap = NULL;		//�µĸ��ڵ�
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

//��child�ϲ���heap��
static void LinkBinHeap(BinHeap child, BinHeap heap)
{
	//child->parent->sibling = heap;
	child->parent = heap;
	child->next = heap->leftChild;
	heap->leftChild = child;
	heap->degree++;
}

//�ϲ�
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
			if (prev_x == NULL)	//�ϲ���һ���ڵ�ʱ
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

//�����ڵ�
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

//����
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

//���뵽�������
BinHeap InsertBinHeap(BinHeap heap, ElementType data)
{
	BinNode* node;

	if (SearchBinNode(heap, data) != NULL)
	{
		printf("Insert Fail�� the data (%d) is existed!\n", data);
		return heap;
	}

	node = MakeNode(data);
	if (node == NULL)
		return heap;
	return UnionBinHeap(heap, node);
}

//��תheap
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

//�Ƴ���С�ڵ㲢����heap
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
	//��ת��С�ڵ�����������õ���С��child,
	//����ʹ����С�ڵ����ڶ������ĺ����������������Ϊһ�������Ķ�����
	BinHeap childHeap = Reverse(y->leftChild);
	heap = UnionBinHeap(heap, childHeap);

	free(y);

	return heap;
}

//��С�ؼ��ֵ�ֵ,node��ֵ��С��data
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

//���ӹؼ����ֵ
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
			//�����ǰ�ڵ�С�����ӵĽڵ㣬�����������Ӻ����ӵ��ֵܽڵ���Ѱ����С�ڵ�
			//Ȼ�󽻻���С�ڵ��ֵ�͵�ǰ�ڵ��ֵ
			least = child;
			while (child->next != NULL)
			{
				if (least->data > child->data)
					least = child->next;
				child = child->next;
			}
			//������С�ڵ�͵�ǰ�ڵ��ֵ
			swap(least->data, cur->data);

			//����֮���ԭ��С�ڵ���е�����ʹ��������С�ѵ����ʣ����ڵ㡶=�ӽڵ�
			cur = least;
			child = cur->leftChild;
		}
		else
		{
			child = child->next;
		}
	}
}

//����heap�Ľڵ�node��ֵΪdata
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

//ɾ���ڵ�ؼ���Ϊdata��ֵ
BinHeap Delete(BinHeap heap, ElementType data)
{
	BinNode *node;
	BinNode *parent, *prev, *pos;
	if (heap == NULL)
		return heap;

	if ((node = SearchBinNode(heap, data)) == NULL)
		return heap;

	//����ɾ���Ľڵ���������Ƶ������ڵĶ������ĸ��ڵ�
	parent = node->parent;
	while (parent != NULL)
	{
		swap(node->data, parent->data);
		node = parent;
		parent = node->parent;
	}
	//�ҵ�node��ǰһ���ڵ�
	prev = NULL;
	pos = heap;
	while (pos != node)
	{
		prev = pos;
		pos = pos->next;
	}
	//�Ƴ�node
	if (prev != NULL)
		prev->next = node->next;
	else
		heap = node->next;		//ɾ������ͷ���
	heap = UnionBinHeap(heap, Reverse(node->leftChild));

	free(node);

	return heap;
}

//��ӡ�����
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

		// �ֵܽڵ�
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
	printf("== �����( ");
	while (p != NULL)
	{
		printf("B%d ", p->degree);
		p = p->next;
	}
	printf(")����ϸ��Ϣ��\n");

	int i = 0;
	while (heap != NULL)
	{
		i++;
		printf("%d. ������B%d: \n", i, heap->degree);
		printf("\t%2d(%d) is root\n", heap->data, heap->degree);

		PrintHeap(heap->leftChild, heap, 1);
		heap = heap->next;
	}

	printf("\n");
}



