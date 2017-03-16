#ifndef _SKEWHEEP_H_
#define _SKEWHEEP_H_

typedef int ElementType;
typedef struct SkewHeapNode
{
	ElementType data;
	struct SkewHeapNode* left;
	struct SkewHeapNode* right;
}SkewNode, *SkewHeap;

int GetMinimun(SkewHeap h, ElementType* pval);		//获取最小的元素
void DestoryHeap(SkewHeap h);						//销毁

SkewHeap MergeHeap(SkewHeap h1, SkewHeap h2);		//合并
SkewHeap InsertHeap(SkewHeap h, ElementType x);		//插入
SkewHeap DeleteHeap(SkewHeap h);					//删除最小值
void PrintHeap(SkewHeap h);							//打印
#endif