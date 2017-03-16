/*
��������������B0ֻ��һ���ڵ㣬������Bk�����Ŷ�����Bk-1���ɣ�����һ������һ�ŵ���������
�����������ʣ�(1)�߶�Ϊk������2^k���ڵ�;(2)���i�Ľڵ���ΪC(i,k);

������У������������һЩ��������ɵ�ɭ�֡�
������е����ʣ�(1)ÿһ�õĸ߶�Ϊk�Ķ��������ֻ��һ��;(2)ÿ�ö������и��ڵ�<=�ӽڵ�
*/


#ifndef _BINOMIALQUEUE_H_
#define _BINOMIALQUEUE_H_

typedef int ElementType;
typedef struct _BinNode
{
	ElementType data;				//������
	int degree;						//�ڵ�Ķ���
	struct _BinNode* parent;		//���ڵ�
	struct _BinNode* leftChild;		//����
	struct _BinNode* next;			//��һ����
	
}BinNode, *BinHeap;

//���������
BinHeap MakeBinHeap();
//������С�ڵ�
BinNode* GetMinNode(BinHeap heap);
//�ϲ�
BinHeap UnionBinHeap(BinHeap h1, BinHeap h2);
//����
BinNode* SearchBinNode(BinHeap heap, ElementType data);
//���뵽�������
BinHeap InsertBinHeap(BinHeap heap, ElementType data);
//�Ƴ���С�ڵ㲢����heap
BinHeap ExtractMin(BinHeap heap);
void UpadateBinHeap(BinHeap heap, ElementType oldData, ElementType newData);
//ɾ���ڵ�ؼ���Ϊdata��ֵ
BinHeap Delete(BinHeap heap, ElementType data);
void PrintBinHeap(BinHeap heap);

#endif