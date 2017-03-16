/*
二叉搜索树的实现(Binary Search Tree)
二叉搜索树是一种二叉树，可以提供对数时间的元素插入与访问。
特点：
1. 若左子树非空，则左子树上的所有结点的关键字值均小于根结点的关键字值。
2. 若右子树非空，则右子树上的所有结点的关键字值均大于根结点的关键字值。
3. 左、右子树本身也分别是一棵二叉搜索树。
4. 没有键值相等的节点
因此满足这些特征的的二叉树为二叉搜索树
*/

#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_

#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_DEPRECATE 1
typedef int ElemType;

//节点定义
typedef struct __TreeNode
{
	ElemType key;
	struct __TreeNode *left;
	struct __TreeNode *right;
}BSTNode, *BSTree;

//一些操作：初始化,查找，查找最小和最大节点，插入，删除，得到元素的值，创建，先序中序和后续遍历，删除
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

//一些其他操作


#endif // _BINARY_SEARCH_TREE_
