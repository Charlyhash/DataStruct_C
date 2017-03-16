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

void PreOrderHeap(LeftistHeap h);			//�������
void InOrederHeap(LeftistHeap h);			//�������
void PostOrderHeap(LeftistHeap h);			//�������
int GetMinimun(LeftistHeap h, ElementType* pval);				//�õ���Сֵ
void DestoryHeap(LeftistHeap h);			//����

LeftistHeap MergeHeap(LeftistHeap h1, LeftistHeap h2);		//�ϲ�
LeftistHeap InsertHeap(LeftistHeap h, ElementType x);		//����
LeftistHeap DeleteHeap(LeftistHeap h);						//ɾ����Сֵ
#endif