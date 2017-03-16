/*
������������ʵ��(Binary Search Tree)
������������һ�ֶ������������ṩ����ʱ���Ԫ�ز�������ʡ�
�ص㣺
1. ���������ǿգ����������ϵ����н��Ĺؼ���ֵ��С�ڸ����Ĺؼ���ֵ��
2. ���������ǿգ����������ϵ����н��Ĺؼ���ֵ�����ڸ����Ĺؼ���ֵ��
3. ������������Ҳ�ֱ���һ�ö�����������
4. û�м�ֵ��ȵĽڵ�
���������Щ�����ĵĶ�����Ϊ����������
*/

#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_

#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_DEPRECATE 1
typedef int ElemType;

//�ڵ㶨��
typedef struct __TreeNode
{
	ElemType key;
	struct __TreeNode *left;
	struct __TreeNode *right;
}BSTNode, *BSTree;

//һЩ��������ʼ��,���ң�������С�����ڵ㣬���룬ɾ�����õ�Ԫ�ص�ֵ����������������ͺ���������ɾ��
void InitTree(BSTree* p);
BSTree MakeEmpty(BSTree p);
BSTNode* Find(ElemType x, BSTree p);
BSTNode* FindMin(BSTree p);
BSTNode* FindMax(BSTree p);
BSTree Insert(ElemType x, BSTree p);
BSTree Delete(ElemType x, BSTree p);
ElemType Retrieve(BSTNode* pos);
void CreateBST(BSTree* pRoot, ElemType arr[], int n);
void PreorderTraverse(BSTree root);
void InorderTraverse(BSTree root);
void PostorderTraverse(BSTree root);
void Delete(BSTree pRoot);

//һЩ��������


#endif // _BINARY_SEARCH_TREE_
