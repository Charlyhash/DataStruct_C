#ifndef _SKEWHEEP_H_
#define _SKEWHEEP_H_

typedef int ElementType;
typedef struct SkewHeapNode
{
	ElementType data;
	struct SkewHeapNode* left;
	struct SkewHeapNode* right;
}SkewNode, *SkewHeap;

int GetMinimun(SkewHeap h, ElementType* pval);		//��ȡ��С��Ԫ��
void DestoryHeap(SkewHeap h);						//����

SkewHeap MergeHeap(SkewHeap h1, SkewHeap h2);		//�ϲ�
SkewHeap InsertHeap(SkewHeap h, ElementType x);		//����
SkewHeap DeleteHeap(SkewHeap h);					//ɾ����Сֵ
void PrintHeap(SkewHeap h);							//��ӡ
#endif