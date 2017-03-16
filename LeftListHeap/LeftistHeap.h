#ifndef _LEFTISTHEAP_H_
#define _LEFTISTHEAP_H_

typedef int ElementType;

typedef struct _LeftistNode
{
	ElementType data;
	struct _LeftistNode* left;
	struct _LeftistNode* right;
	int npl;
}LeftistNode, *LeftistHeap;

void PreOrderHeap(LeftistHeap h);			//先序遍历
void InOrederHeap(LeftistHeap h);			//中序遍历
void PostOrderHeap(LeftistHeap h);			//后序遍历
int GetMinimun(LeftistHeap h, ElementType* pval);				//得到最小值
void DestoryHeap(LeftistHeap h);			//销毁

LeftistHeap MergeHeap(LeftistHeap h1, LeftistHeap h2);		//合并
LeftistHeap InsertHeap(LeftistHeap h, ElementType x);		//插入
LeftistHeap DeleteHeap(LeftistHeap h);						//删除最小值
#endif