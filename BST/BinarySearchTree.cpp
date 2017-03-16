#include "BinarySearchTree.h"

void InitTree(BSTree *p)
{
	*p = NULL;
}

//创建一颗空的二叉搜索树
//如果不为空，就让其左右子树都为空
BSTree MakeEmpty(BSTree p)
{
	if (p != NULL)
	{
		MakeEmpty(p->left);
		MakeEmpty(p->right);
		free(p);
	}

	return p;
}

//查找key=x的节点
//根节点的关键字那么在右子树上查找，小于根节点的关键字到左子树上查找，递归实现。
BSTNode* Find(ElemType x, BSTree p)
{
	if (p == NULL)
		return NULL;
	if (x == p->key)
		return p;
	if (x < p->key)
		return Find(x, p->left);
	else if (x > p->key)
		return Find(x, p->right);
	else
	{
		printf("Not Find %d!", x);
		return NULL;
	}
}

//查找最小的节点
BSTNode* FindMin(BSTree p)
{
	if (p == NULL)
		return NULL;
	while (p->left != NULL)
		p = p->left;

	return p;
}

//查找最大的节点
BSTNode* FindMax(BSTree p)
{
	if (p == NULL)
		return NULL;
	while (p->right != NULL)
		p = p->right;

	return p;
}

//插入某个元素：插入的元素一定在叶子节点上
//如果为空，直接建立节点，如果不为空
//比左孩子的key小，应该插入到左子树上，比右孩子的key大，应该插入到右子树上
BSTree Insert(ElemType x, BSTree p)
{
	if (p == NULL)
	{
		p = (BSTNode*)malloc(sizeof(BSTNode));
		p->key = x;
		p->left = p->right = NULL;
	}
	else
	{
		if (x < p->key)
			p->left = Insert(x, p->left);
		else if (x > p->key)
			p->right = Insert(x, p->right);
	}

	return p;
}

//删除：先找到要删除的位置，如果为叶子结点，可以直接删除；
//如果只有一个儿子，让这个儿子替代删除的位置；
//如果有两个儿子，那么用右结点的最小值带替代当前的位置的值，这样还是保持BST的结构。
BSTree Delete(ElemType x, BSTree p)
{
	BSTNode* tmp;
	if (p == NULL)
	{
		printf("没有这个元素%d\n", x);
		return NULL;
	}
	else if (x < p->key)
		p->left = Delete(x, p->left);
	else if (x > p->key)
		p->right = Delete(x, p->right);
	else
	{
		if (p->right && p->left)				//左右子树都不为空
		{
			tmp = FindMin(p->right);
			p->key = tmp->key;						//用右子树的最小节点值替代删除的值
			p->right = Delete(tmp->key, p->right);	//删除这个元素
		}
		else										//只有一个孩子或者没有孩子
		{
			tmp = p;								//这是要删除的节点
			p = (p->left == NULL) ? p->right : p->left;
			free(tmp);								//释放节点
		}
	}

	return p;
}
//得到节点的值
ElemType Retrieve(BSTNode* pos)
{
	if (pos != NULL)
		return pos->key;
	else
		return -1;
}

//用数组创建二叉搜索树，调用插入
void CreateBST(BSTree* pRoot, ElemType arr[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		*pRoot = Insert(arr[i], *pRoot);
	}
}

//遍历
void PreorderTraverse(BSTree root)
{
	if (root == NULL)
		return;
	printf("%d ", root->key);
	PreorderTraverse(root->left);
	PreorderTraverse(root->right);
}
void InorderTraverse(BSTree root)
{
	if (root == NULL)
		return;
	PreorderTraverse(root->left);
	printf("%d ", root->key);
	PreorderTraverse(root->right);
}
void PostorderTraverse(BSTree root)
{
	if (root == NULL)
		return;
	PreorderTraverse(root->left);
	PreorderTraverse(root->right);
	printf("%d ", root->key);
}