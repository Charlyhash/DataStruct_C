#ifndef _RBTREE_H_
#define _RBTREE_H_
/*
�������һ���������������Ķ�����������
1.ÿ�����Ҫô�Ǻ��Ҫô�Ǻڵġ�
2.������Ǻڵġ�
3.ÿ��Ҷ��㣨Ҷ��㼴ָ��β��NILָ���NULL��㣩���Ǻڵġ�
4.���һ������Ǻ�ģ���ô�����������Ӷ��Ǻڵġ�
5.������������ԣ��䵽Ҷ�����β��NILָ���ÿ��·����������ͬ��Ŀ�ĺڽ�㡣

��������ص㣺 һ�þ���n���ڽ�㣨�����������ݽ�㣩�ĺ�����ĺڸ߶�bh����Ϊ2lg(n+1) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;
//��ɫ������
typedef enum color_t
{
	RED = 0,
	BLACK = 1
}color_t;

//������Ľ�㶨��
typedef struct __RBTreeNode
{
	ElemType key;				//�ؼ���
	color_t color;				//��ɫ����ɫ���ߺ�ɫ
	struct __RBTreeNode* left;	//�����
	struct __RBTreeNode* right;	//�Ҷ���
	struct __RBTreeNode* parent;//���ڵ�
}RBTreeNode, *RBTree;

//һЩ����
//����
void InitTree(RBTree* p);
//����
RBTreeNode* RBSearch(RBTree *rbTree, ElemType key);
//�������ڵ�
RBTreeNode* RBFindMax(RBTree rbTree);
//������С�ڵ�
RBTreeNode* RBFindMin(RBTree rbTree);
//���غ�̽ڵ�
RBTreeNode* RBSuccessor(RBTree *rbTree, ElemType data);

//����
bool RBInsert(RBTree *rbTree, ElemType data);
//ɾ��
bool RBDelete(RBTree *rbTree, ElemType data);


//����
void Destroy(RBTree pRoot);

void PrintRBTree(RBTree pRoot);

#endif