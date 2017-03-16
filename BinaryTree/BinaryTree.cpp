#include "BinaryTree.h"
#include <queue>
#include <stack>
#include <algorithm>
using namespace  std;

//二叉树初始化：让根节点为空
void InitTree(BinaryTree *root)
{
	*root = NULL;		//C不能传入引用，因此传入指针
}

//创建一棵树，直接输入。
//递归的创建，先创建一个节点，再递归创建左右子树
void CreateTree(BinaryTree* root)
{
	ElemType data;
	printf("请输入要创建的节点值（0表示为NULL）：");
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
		printf("创建%d的左子树.\n", data);
		CreateTree(&((*root)->left));
		printf("创建%d的右子树.\n", data);
		CreateTree(&((*root)->right));
	}

}

//用一个数组中的元素来创建二叉树
//root为根节点，arr为数组，len为数组的长度，index为当前创建的节点在数组中的位置
//根据二叉树的性质，i位置的左子树为2*i+1右子树为2*i+2。因此我们递归调用该函数
void CreateTreeUseArray(BinaryTree* root, ElemType* arr, int len, int index)
{
	if (index >= len)
		return;
	(*root) = (BinaryTree)malloc(sizeof(BinaryTreeNode));	//分配空间
	(*root)->key = arr[index];
	(*root)->right = NULL;
	(*root)->left = NULL;
	CreateTreeUseArray(&((*root)->right), arr, len, 2 * index + 2);
	CreateTreeUseArray(&((*root)->left), arr, len, 2 * index + 1);
}

//先序遍历：先访问根节点，在访问左右子树
void PreorderTraverse(BinaryTree root)
{
	if (root == NULL)
		return;
	printf("%d ", root->key);
	PreorderTraverse(root->left);
	PreorderTraverse(root->right);
}

//中续遍历：先访问左子树，再访问根节点，最后访问右子树
void InorderTraverse(BinaryTree root)
{
	if (root == NULL)
		return;
	PreorderTraverse(root->left);
	printf("%d ", root->key);
	PreorderTraverse(root->right);
}

//后续遍历：先访问左子树，再访问右子树，最后访问根节点
void PostorderTraverse(BinaryTree root)
{
	if (root == NULL)
		return;
	PreorderTraverse(root->left);
	PreorderTraverse(root->right);
	printf("%d ", root->key);
}

//先序遍历：非递归
//先输出结点值，再入栈，然后遍历左子树。退栈时，遍历栈顶结点的右子树
void PreorderTraverseIter(BinaryTree pRoot)
{
	stack<BinaryTreeNode *> s;
	BinaryTreeNode *p = pRoot;
	//用p指向当前要访问的根节点，s为一个栈存放要访问的元素
	//p不为空，就先访问，然后入栈，接着访问左子树
	//p为空，说明后面没有元素了，栈顶元素为p的父节点
	//将该节点弹出，并访问该节点的右子树。
	while (p != NULL || !s.empty())		//p不为空或者栈不为空
	{ 
		while (p != NULL)				//p不为空
		{
			printf("%d ", p->key);		//输出根节点
			s.push(p);					//入栈
			p = p->left;					//继续访问左子树
		}
		if (!s.empty())					//p为空，但是栈中还有元素
		{
			p = s.top();				//让p为栈顶元素，开始访问这个元素的右子树
			s.pop();
			p = p->right;
		}
	}
}

//中序遍历的非递归实现
void InorderTraverseIter(BinaryTree pRoot)
{
	stack<BinaryTreeNode*> s;
	BinaryTreeNode* p = pRoot;
	while (p != NULL || !s.empty())
	{
		while (p != NULL)
		{
			s.push(p);		//先入栈
			p = p->left;		//访问左子树
		}
		if (!s.empty())
		{
			p = s.top();				//取根节点
			printf("%d ", p->key);		//这里输出
			s.pop();					//弹出
			p = p->right;				//开始访问右边的节点
		}
	}
}

//非递归的后序遍历
//对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，
//直到搜索到没有左孩子的结点，此时该结点出现在栈顶，
//但是此时不能将其出栈并访问，因此其右孩子还为被访问。
//所以接下来按照相同的规则对其右子树进行相同的处理，
//当访问完其右孩子时，该结点又出现在栈顶，此时可以将其出栈并访问。
//这样就保证了正确的访问顺序。可以看出，在这个过程中，
//每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。
//因此需要多设置一个变量标识该结点是否是第一次出现在栈顶。
void PostorderTraverseIter(BinaryTree pRoot)
{
	stack<BTNodeF*> s;
	BinaryTreeNode *p = pRoot;
	BTNodeF *tmp;
	while (p != NULL && !s.empty())
	{
		while (p != NULL)		//一直沿着左子树走下去
		{
			BTNodeF *btf = (BTNodeF*)malloc(sizeof(BTNodeF));		//该节点记录访问到的节点和其是不是第一次访问
			btf->node = p;
			btf->isFirst = true;
			s.push(btf);
			p = p->left;
		}
		if (!s.empty())
		{
			tmp = s.top();
			s.pop();
			if (tmp->isFirst == true)		//第一次访问
			{
				tmp->isFirst = false;
				s.push(tmp);
				p = tmp->node->right;		//开始访问右子树
			}
			else  //第二次出现在栈顶
			{
				printf("%d ", tmp->node->key);
				p = NULL;					
			}
		}
	}

}

//第二种思路：要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。
//如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，
//但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
//若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，
//左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
void PostorderTraverseIter2(BinaryTree pRoot)
{
	stack<BinaryTreeNode*> s;
	BinaryTreeNode* cur;		//当前访问的节点
	BinaryTreeNode* pre = NULL;	//前一次访问的节点
	s.push(pRoot);
	while (!s.empty())
	{
		cur = s.top();
		if ((cur->left == NULL && cur->right == NULL) || (pre != NULL && (pre == cur->left || pre == cur->right)))
		{//当前节点左右子树都为空或者其左右孩子都被访问过了
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

//访问节点
ElemType Retrieve(BinaryTreeNode *pNode)
{
	if (pNode != NULL)
		return pNode->key;
	else
		return -1;
}

//求二叉树节点的个数
int GetNodeNum(BinaryTree pRoot)
{
	if (pRoot == NULL)
		return 0;
	return GetNodeNum(pRoot->right) + GetNodeNum(pRoot->left) + 1;
}

//求二叉树的深度
//二叉树的深度是指根节点到叶子节点的最长的距离
//二叉树为空，深度为0；二叉树不为空，深度为max(deep(left), deep(right))+1
int GetDepth(BinaryTree pRoot)
{
	if (pRoot == NULL)
		return 0;
	int leftDepth = GetDepth(pRoot->left);
	int rightDepth = GetDepth(pRoot->right);

	return leftDepth > rightDepth ? (leftDepth + 1) : (rightDepth + 1);
}

//二叉树的分层遍历:从上到下，从左往右
//使用队列：先将根节点压入栈中，当队列不为空则：
//弹出一个节点并访问，如果左子节点不为空或者右子节点不为空，将其压入栈中
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

//求二叉树第k层的节点个数
//求第K层结点的个数也可以用递归来实现：
//若二叉树为空或者K小于0，返回0
//若K等于0，第0层就是树根，根只有一个，返回1
//若K大于0，返回左子树中第K - 1层结点个数 加上 右子树中第K - 1层结点的个数
//因为，第K层结点，相对于根的左子树 和 右子树 而言，就是第K - 1层结点
int GetNodeNumKthLevel(BinaryTree pRoot, int k)
{
	if (k < -1 || pRoot == NULL)
		return 0;
	if (k == 0)
		return 1;
	else
		return GetNodeNumKthLevel(pRoot->left, k - 1) + GetNodeNumKthLevel(pRoot->right, k - 1);
}

//求二叉树叶子节点个数
//（1）如果二叉树为空，返回0
//（2）如果二叉树不为空且左右子树为空，返回1
//（3）如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子节点个数加上右子树中叶子节点个数
int GetLeafNum(BinaryTree pRoot)
{
	if (pRoot == NULL)
		return 0;
	if (pRoot->left == NULL && pRoot->right == NULL)
		return 1;
	return (GetLeafNum(pRoot->right) + GetLeafNum(pRoot->left));
}

//判断两棵二叉树是否结构相同
//结构相同意味着对应的左子树和对应的右子树都结构相同。
//递归解法：
//（1）如果两棵二叉树都为空，返回真
//（2）如果两棵二叉树一棵为空，另一棵不为空，返回假
//（3）如果两棵二叉树都不为空，如果对应的左子树和右子树都同构返回真，其他返回假
bool StructureCmp(BinaryTree pRoot1, BinaryTree pRoot2)
{
	if (pRoot1 == NULL && pRoot2 == NULL)
		return true;
	else if (pRoot1 == NULL || pRoot2 == NULL)
		return false;
	return (StructureCmp(pRoot1->left, pRoot2->left) && StructureCmp(pRoot1->right, pRoot2->right));
}

//判断是不是平衡二叉树
//为空，返回真；不为空，左子树和右子树都是AVL树并且左子树和右子树高度相差不大于1，返回真，其他返回假
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

//求二叉树的镜像
//（1）如果二叉树为空，返回空
//（2）如果二叉树不为空，求左子树和右子树的镜像，然后交换左子树和右子树
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

//求二叉树中两个节点的最低公共祖先节点
//递归解法：
//（1）如果两个节点分别在根节点的左子树和右子树，则返回根节点
//（2）如果两个节点都在左子树，则递归处理左子树；如果两个节点都在右子树，则递归处理右子树
//辅助函数：判断是不是在二叉树上
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

