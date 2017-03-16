#include "BinarySearchTree.h"

void InitTree(BSTree *p)
{
	*p = NULL;
}

//����һ�ſյĶ���������
//�����Ϊ�գ�����������������Ϊ��
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

//����key=x�Ľڵ�
//���ڵ�Ĺؼ�����ô���������ϲ��ң�С�ڸ��ڵ�Ĺؼ��ֵ��������ϲ��ң��ݹ�ʵ�֡�
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

//������С�Ľڵ�
BSTNode* FindMin(BSTree p)
{
	if (p == NULL)
		return NULL;
	while (p->left != NULL)
		p = p->left;

	return p;
}

//�������Ľڵ�
BSTNode* FindMax(BSTree p)
{
	if (p == NULL)
		return NULL;
	while (p->right != NULL)
		p = p->right;

	return p;
}

//����ĳ��Ԫ�أ������Ԫ��һ����Ҷ�ӽڵ���
//���Ϊ�գ�ֱ�ӽ����ڵ㣬�����Ϊ��
//�����ӵ�keyС��Ӧ�ò��뵽�������ϣ����Һ��ӵ�key��Ӧ�ò��뵽��������
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

//ɾ�������ҵ�Ҫɾ����λ�ã����ΪҶ�ӽ�㣬����ֱ��ɾ����
//���ֻ��һ�����ӣ�������������ɾ����λ�ã�
//������������ӣ���ô���ҽ�����Сֵ�������ǰ��λ�õ�ֵ���������Ǳ���BST�Ľṹ��
BSTree Delete(ElemType x, BSTree p)
{
	BSTNode* tmp;
	if (p == NULL)
	{
		printf("û�����Ԫ��%d\n", x);
		return NULL;
	}
	else if (x < p->key)
		p->left = Delete(x, p->left);
	else if (x > p->key)
		p->right = Delete(x, p->right);
	else
	{
		if (p->right && p->left)				//������������Ϊ��
		{
			tmp = FindMin(p->right);
			p->key = tmp->key;						//������������С�ڵ�ֵ���ɾ����ֵ
			p->right = Delete(tmp->key, p->right);	//ɾ�����Ԫ��
		}
		else										//ֻ��һ�����ӻ���û�к���
		{
			tmp = p;								//����Ҫɾ���Ľڵ�
			p = (p->left == NULL) ? p->right : p->left;
			free(tmp);								//�ͷŽڵ�
		}
	}

	return p;
}
//�õ��ڵ��ֵ
ElemType Retrieve(BSTNode* pos)
{
	if (pos != NULL)
		return pos->key;
	else
		return -1;
}

//�����鴴�����������������ò���
void CreateBST(BSTree* pRoot, ElemType arr[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		*pRoot = Insert(arr[i], *pRoot);
	}
}

//����
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