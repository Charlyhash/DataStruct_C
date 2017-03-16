/*
二项树：二项树B0只有一个节点，二项树Bk由两颗二项树Bk-1构成，其中一颗是另一颗的左子树。
二项树的性质：(1)高度为k的树有2^k个节点;(2)深度i的节点数为C(i,k);

二项队列：二项队列是由一些二项树组成的森林。
二项队列的性质：(1)每一棵的高度为k的二项树最多只有一棵;(2)每棵二项树中父节点<=子节点
*/


#ifndef _BINOMIALQUEUE_H_
#define _BINOMIALQUEUE_H_

typedef int ElementType;
typedef struct _BinNode
{
	ElementType data;				//数据域
	int degree;						//节点的度数
	struct _BinNode* parent;		//父节点
	struct _BinNode* leftChild;		//左孩子
	struct _BinNode* next;			//下一颗树
	
}BinNode, *BinHeap;

//创建二项堆
BinHeap MakeBinHeap();
//查找最小节点
BinNode* GetMinNode(BinHeap heap);
//合并
BinHeap UnionBinHeap(BinHeap h1, BinHeap h2);
//查找
BinNode* SearchBinNode(BinHeap heap, ElementType data);
//插入到二项队列
BinHeap InsertBinHeap(BinHeap heap, ElementType data);
//移除最小节点并返回heap
BinHeap ExtractMin(BinHeap heap);
void UpadateBinHeap(BinHeap heap, ElementType oldData, ElementType newData);
//删除节点关键字为data的值
BinHeap Delete(BinHeap heap, ElementType data);
void PrintBinHeap(BinHeap heap);

#endif