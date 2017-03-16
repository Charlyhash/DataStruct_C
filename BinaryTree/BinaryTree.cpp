#include "BinaryTree.h"
#include <queue>
#include <stack>
#include <algorithm>
using namespace  std;

//��������ʼ�����ø��ڵ�Ϊ��
void InitTree(BinaryTree *root)
{
	*root = NULL;		//C���ܴ������ã���˴���ָ��
}

//����һ������ֱ�����롣
//�ݹ�Ĵ������ȴ���һ���ڵ㣬�ٵݹ鴴����������
void CreateTree(BinaryTree* root)
{
	ElemType data;
	printf("������Ҫ�����Ľڵ�ֵ��0��ʾΪNULL����");
	scanf("%d",&data);
	if (data == 0)
		*root = NULL;
	else
	{
		*root = (BinaryTree)malloc(sizeof(BinaryTreeNode));
		if (root == NULL)
		{
			printf("Out of sapce!\n");
			exit(-1);
		}
		(*root)->key = data;
		printf("����%d��������.\n", data);
		CreateTree(&((*root)->left));
		printf("����%d��������.\n", data);
		CreateTree(&((*root)->right));
	}

}

//��һ�������е�Ԫ��������������
//rootΪ���ڵ㣬arrΪ���飬lenΪ����ĳ��ȣ�indexΪ��ǰ�����Ľڵ��������е�λ��
//���ݶ����������ʣ�iλ�õ�������Ϊ2*i+1������Ϊ2*i+2��������ǵݹ���øú���
void CreateTreeUseArray(BinaryTree* root, ElemType* arr, int len, int index)
{
	if (index >= len)
		return;
	(*root) = (BinaryTree)malloc(sizeof(BinaryTreeNode));	//����ռ�
	(*root)->key = arr[index];
	(*root)->right = NULL;
	(*root)->left = NULL;
	CreateTreeUseArray(&((*root)->right), arr, len, 2 * index + 2);
	CreateTreeUseArray(&((*root)->left), arr, len, 2 * index + 1);
}

//����������ȷ��ʸ��ڵ㣬�ڷ�����������
void PreorderTraverse(BinaryTree root)
{
	if (root == NULL)
		return;
	printf("%d ", root->key);
	PreorderTraverse(root->left);
	PreorderTraverse(root->right);
}

//�����������ȷ������������ٷ��ʸ��ڵ㣬������������
void InorderTraverse(BinaryTree root)
{
	if (root == NULL)
		return;
	PreorderTraverse(root->left);
	printf("%d ", root->key);
	PreorderTraverse(root->right);
}

//�����������ȷ������������ٷ����������������ʸ��ڵ�
void PostorderTraverse(BinaryTree root)
{
	if (root == NULL)
		return;
	PreorderTraverse(root->left);
	PreorderTraverse(root->right);
	printf("%d ", root->key);
}

//����������ǵݹ�
//��������ֵ������ջ��Ȼ���������������ջʱ������ջ������������
void PreorderTraverseIter(BinaryTree pRoot)
{
	stack<BinaryTreeNode *> s;
	BinaryTreeNode *p = pRoot;
	//��pָ��ǰҪ���ʵĸ��ڵ㣬sΪһ��ջ���Ҫ���ʵ�Ԫ��
	//p��Ϊ�գ����ȷ��ʣ�Ȼ����ջ�����ŷ���������
	//pΪ�գ�˵������û��Ԫ���ˣ�ջ��Ԫ��Ϊp�ĸ��ڵ�
	//���ýڵ㵯���������ʸýڵ����������
	while (p != NULL || !s.empty())		//p��Ϊ�ջ���ջ��Ϊ��
	{ 
		while (p != NULL)				//p��Ϊ��
		{
			printf("%d ", p->key);		//������ڵ�
			s.push(p);					//��ջ
			p = p->left;					//��������������
		}
		if (!s.empty())					//pΪ�գ�����ջ�л���Ԫ��
		{
			p = s.top();				//��pΪջ��Ԫ�أ���ʼ�������Ԫ�ص�������
			s.pop();
			p = p->right;
		}
	}
}

//��������ķǵݹ�ʵ��
void InorderTraverseIter(BinaryTree pRoot)
{
	stack<BinaryTreeNode*> s;
	BinaryTreeNode* p = pRoot;
	while (p != NULL || !s.empty())
	{
		while (p != NULL)
		{
			s.push(p);		//����ջ
			p = p->left;		//����������
		}
		if (!s.empty())
		{
			p = s.top();				//ȡ���ڵ�
			printf("%d ", p->key);		//�������
			s.pop();					//����
			p = p->right;				//��ʼ�����ұߵĽڵ�
		}
	}
}

//�ǵݹ�ĺ������
//������һ���P��������ջ��Ȼ������������һֱ����������
//ֱ��������û�����ӵĽ�㣬��ʱ�ý�������ջ����
//���Ǵ�ʱ���ܽ����ջ�����ʣ�������Һ��ӻ�Ϊ�����ʡ�
//���Խ�����������ͬ�Ĺ������������������ͬ�Ĵ���
//�����������Һ���ʱ���ý���ֳ�����ջ������ʱ���Խ����ջ�����ʡ�
//�����ͱ�֤����ȷ�ķ���˳�򡣿��Կ���������������У�
//ÿ����㶼���γ�����ջ����ֻ���ڵڶ��γ�����ջ��ʱ�����ܷ�������
//�����Ҫ������һ��������ʶ�ý���Ƿ��ǵ�һ�γ�����ջ����
void PostorderTraverseIter(BinaryTree pRoot)
{
	stack<BTNodeF*> s;
	BinaryTreeNode *p = pRoot;
	BTNodeF *tmp;
	while (p != NULL && !s.empty())
	{
		while (p != NULL)		//һֱ��������������ȥ
		{
			BTNodeF *btf = (BTNodeF*)malloc(sizeof(BTNodeF));		//�ýڵ��¼���ʵ��Ľڵ�����ǲ��ǵ�һ�η���
			btf->node = p;
			btf->isFirst = true;
			s.push(btf);
			p = p->left;
		}
		if (!s.empty())
		{
			tmp = s.top();
			s.pop();
			if (tmp->isFirst == true)		//��һ�η���
			{
				tmp->isFirst = false;
				s.push(tmp);
				p = tmp->node->right;		//��ʼ����������
			}
			else  //�ڶ��γ�����ջ��
			{
				printf("%d ", tmp->node->key);
				p = NULL;					
			}
		}
	}

}

//�ڶ���˼·��Ҫ��֤����������Ӻ��Һ��ӷ���֮����ܷ��ʣ���˶�����һ���P���Ƚ�����ջ��
//���P���������Ӻ��Һ��ӣ������ֱ�ӷ�����������P�������ӻ����Һ��ӣ�
//���������Ӻ��Һ��Ӷ��ѱ����ʹ��ˣ���ͬ������ֱ�ӷ��ʸý�㡣
//�������������������P���Һ��Ӻ�����������ջ�������ͱ�֤��ÿ��ȡջ��Ԫ�ص�ʱ��
//�������Һ���ǰ�汻���ʣ����Ӻ��Һ��Ӷ��ڸ����ǰ�汻���ʡ�
void PostorderTraverseIter2(BinaryTree pRoot)
{
	stack<BinaryTreeNode*> s;
	BinaryTreeNode* cur;		//��ǰ���ʵĽڵ�
	BinaryTreeNode* pre = NULL;	//ǰһ�η��ʵĽڵ�
	s.push(pRoot);
	while (!s.empty())
	{
		cur = s.top();
		if ((cur->left == NULL && cur->right == NULL) || (pre != NULL && (pre == cur->left || pre == cur->right)))
		{//��ǰ�ڵ�����������Ϊ�ջ��������Һ��Ӷ������ʹ���
			printf("%d ", cur->key);
			s.pop();
			pre = cur;
		}
		else
		{
			if (cur->right != NULL)
				s.push(cur->right);
			if (cur->left != NULL)
				s.push(cur->left);
		}
	}

}

//���ʽڵ�
ElemType Retrieve(BinaryTreeNode *pNode)
{
	if (pNode != NULL)
		return pNode->key;
	else
		return -1;
}

//��������ڵ�ĸ���
int GetNodeNum(BinaryTree pRoot)
{
	if (pRoot == NULL)
		return 0;
	return GetNodeNum(pRoot->right) + GetNodeNum(pRoot->left) + 1;
}

//������������
//�������������ָ���ڵ㵽Ҷ�ӽڵ����ľ���
//������Ϊ�գ����Ϊ0����������Ϊ�գ����Ϊmax(deep(left), deep(right))+1
int GetDepth(BinaryTree pRoot)
{
	if (pRoot == NULL)
		return 0;
	int leftDepth = GetDepth(pRoot->left);
	int rightDepth = GetDepth(pRoot->right);

	return leftDepth > rightDepth ? (leftDepth + 1) : (rightDepth + 1);
}

//�������ķֲ����:���ϵ��£���������
//ʹ�ö��У��Ƚ����ڵ�ѹ��ջ�У������в�Ϊ����
//����һ���ڵ㲢���ʣ�������ӽڵ㲻Ϊ�ջ������ӽڵ㲻Ϊ�գ�����ѹ��ջ��
void LevelTraverse(BinaryTree pRoot)
{
	if (pRoot == NULL)
		return;
	std::queue<BinaryTreeNode*> q;
	q.push(pRoot);
	while (!q.empty())
	{
		BinaryTreeNode* pNode = q.front();
		q.pop();
		printf("%d ", Retrieve(pNode));
		if (pNode->left != NULL)
			q.push(pNode->left);
		if (pNode->right != NULL)
			q.push(pNode->right);
	}

	return;
}

//���������k��Ľڵ����
//���K����ĸ���Ҳ�����õݹ���ʵ�֣�
//��������Ϊ�ջ���KС��0������0
//��K����0����0�������������ֻ��һ��������1
//��K����0�������������е�K - 1������� ���� �������е�K - 1����ĸ���
//��Ϊ����K���㣬����ڸ��������� �� ������ ���ԣ����ǵ�K - 1����
int GetNodeNumKthLevel(BinaryTree pRoot, int k)
{
	if (k < -1 || pRoot == NULL)
		return 0;
	if (k == 0)
		return 1;
	else
		return GetNodeNumKthLevel(pRoot->left, k - 1) + GetNodeNumKthLevel(pRoot->right, k - 1);
}

//�������Ҷ�ӽڵ����
//��1�����������Ϊ�գ�����0
//��2�������������Ϊ������������Ϊ�գ�����1
//��3�������������Ϊ�գ�������������ͬʱΪ�գ�������������Ҷ�ӽڵ����������������Ҷ�ӽڵ����
int GetLeafNum(BinaryTree pRoot)
{
	if (pRoot == NULL)
		return 0;
	if (pRoot->left == NULL && pRoot->right == NULL)
		return 1;
	return (GetLeafNum(pRoot->right) + GetLeafNum(pRoot->left));
}

//�ж����ö������Ƿ�ṹ��ͬ
//�ṹ��ͬ��ζ�Ŷ�Ӧ���������Ͷ�Ӧ�����������ṹ��ͬ��
//�ݹ�ⷨ��
//��1��������ö�������Ϊ�գ�������
//��2��������ö�����һ��Ϊ�գ���һ�ò�Ϊ�գ����ؼ�
//��3��������ö���������Ϊ�գ������Ӧ������������������ͬ�������棬�������ؼ�
bool StructureCmp(BinaryTree pRoot1, BinaryTree pRoot2)
{
	if (pRoot1 == NULL && pRoot2 == NULL)
		return true;
	else if (pRoot1 == NULL || pRoot2 == NULL)
		return false;
	return (StructureCmp(pRoot1->left, pRoot2->left) && StructureCmp(pRoot1->right, pRoot2->right));
}

//�ж��ǲ���ƽ�������
//Ϊ�գ������棻��Ϊ�գ�������������������AVL���������������������߶�������1�������棬�������ؼ�
bool IsAVL(BinaryTree pRoot, int &height)
{
	if (pRoot == NULL)
	{
		height = 0;
		return true;
	}
	int heightLeft;
	bool resultLeft = IsAVL(pRoot->left, heightLeft);
	int heightRight;
	bool resultRight = IsAVL(pRoot->right, heightRight);
	if (resultLeft && resultRight && abs(heightRight - heightLeft) <= 1)
	{
		height = max(heightLeft, heightRight) + 1;
		return true;
	}
	else
	{
		height = max(heightLeft, heightRight) + 1;
		return false;
	}

}

//��������ľ���
//��1�����������Ϊ�գ����ؿ�
//��2�������������Ϊ�գ������������������ľ���Ȼ�󽻻���������������
BinaryTreeNode* Mirror(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return NULL;
	BinaryTreeNode* pLeft = Mirror(pRoot->left);
	BinaryTreeNode* pRight = Mirror(pRoot->right);
	pRoot->left = pRight;
	pRoot->right = pLeft;

	return pRoot;
}

//��������������ڵ����͹������Ƚڵ�
//�ݹ�ⷨ��
//��1����������ڵ�ֱ��ڸ��ڵ�������������������򷵻ظ��ڵ�
//��2����������ڵ㶼������������ݹ鴦������������������ڵ㶼������������ݹ鴦��������
//�����������ж��ǲ����ڶ�������
bool FindNode(BinaryTreeNode* pRoot, BinaryTreeNode* pNode)
{
	if (pRoot == NULL || pNode == NULL)
		return false;
	if (pRoot == pNode)
		return true;
	bool found = FindNode(pRoot->left, pNode);
	if (!found)
		found = FindNode(pRoot->right, pNode);
	return found;
}

BinaryTreeNode* GetLastCommenParent(BinaryTreeNode* pRoot, BinaryTreeNode* pNode1, BinaryTreeNode* pNode2)
{
	if (FindNode(pRoot->left, pNode1))
	{
		if (FindNode(pRoot->right, pNode2))
			return pRoot;
		else
			return GetLastCommenParent(pRoot->left, pNode1, pNode2);
	}
	else
	{
		if (FindNode(pRoot->left, pNode2))
			return pRoot;
		else
			return GetLastCommenParent(pRoot->right, pNode1, pNode2);
	}
}

