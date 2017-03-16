/*
二叉树：每个节点至多有两棵子树，且二叉树的子树有左右之分，次序不能颠倒。
因此：二叉树中不存在度数大于2的节点
二叉树的性质：（1）二叉树的第i层最多有2^(i-1)个节点；
（2）深度为k的二叉树至多有2^k-1个节点（k>=1)。
*/


#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

//定义二叉树的节点结构
//有一个关键字，以及指向左右节点的指针
typedef struct __TreeNode
{
	ElemType key;
	struct __TreeNode *left;
	struct __TreeNode *right;
}BinaryTreeNode, *BinaryTree;


//辅助的结构体：带有一个标志位，判断是不是第一次出现在栈顶
typedef struct __TreeNodeFlag
{
	BinaryTreeNode* node;
	bool isFirst;
}BTNodeF;

//一些操作:初始化，创建一颗树，用数组创建一颗树，先序遍历，中序遍历，后续遍历

void InitTree(BinaryTree *root);
void CreateTree(BinaryTree* root);
void CreateTreeUseArray(BinaryTree* root, ElemType* arr, int len, int index = 0);
void PreorderTraverse(BinaryTree root);
void InorderTraverse(BinaryTree root);
void PostorderTraverse(BinaryTree root);

//求二叉树节点的个数
int GetNodeNum(BinaryTree pRoot);

//求二叉树的深度
//二叉树的深度是指根节点到叶子节点的最长的距离
//二叉树为空，深度为0；二叉树不为空，深度为max(deep(left), deep(right))+1
int GetDepth(BinaryTree pRoot);

//二叉树的分层遍历:从上到下，从左往右
//使用队列：先将根节点压入栈中，当队列不为空则：
//弹出一个节点并访问，如果左子节点不为空或者右子节点不为空，将其压入栈中
void LevelTraverse(BinaryTree pRoot);

//求二叉树第k层的节点个数
//求第K层结点的个数也可以用递归来实现：
//若二叉树为空或者K小于0，返回0
//若K等于0，第0层就是树根，根只有一个，返回1
//若K大于0，返回左子树中第K - 1层结点个数 加上 右子树中第K - 1层结点的个数
//因为，第K层结点，相对于根的左子树 和 右子树 而言，就是第K - 1层结点
int GetNodeNumKthLevel(BinaryTree pRoot, int k);


//求二叉树叶子节点个数
//（1）如果二叉树为空，返回0
//（2）如果二叉树不为空且左右子树为空，返回1
//（3）如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子节点个数加上右子树中叶子节点个数
int GetLeafNum(BinaryTree pRoot);

//先序遍历：非递归
//先输出结点值，再入栈，然后遍历左子树。退栈时，遍历栈顶结点的右子树
void PreorderTraverseIter(BinaryTree pRoot);

//中序遍历的非递归实现
void InorderTraverseIter(BinaryTree pRoot);

//非递归的后序遍历
//对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，
//直到搜索到没有左孩子的结点，此时该结点出现在栈顶，
//但是此时不能将其出栈并访问，因此其右孩子还为被访问。
//所以接下来按照相同的规则对其右子树进行相同的处理，
//当访问完其右孩子时，该结点又出现在栈顶，此时可以将其出栈并访问。
//这样就保证了正确的访问顺序。可以看出，在这个过程中，
//每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。
//因此需要多设置一个变量标识该结点是否是第一次出现在栈顶。
void PostorderTraverseIter(BinaryTree pRoot);

//第二种思路：要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。
//如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，
//但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
//若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，
//左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
void PostorderTraverseIter2(BinaryTree pRoot);

//判断两棵二叉树是否结构相同
//结构相同意味着对应的左子树和对应的右子树都结构相同。
//递归解法：
//（1）如果两棵二叉树都为空，返回真
//（2）如果两棵二叉树一棵为空，另一棵不为空，返回假
//（3）如果两棵二叉树都不为空，如果对应的左子树和右子树都同构返回真，其他返回假
bool StructureCmp(BinaryTree pRoot1, BinaryTree pRoot2);

//判断是不是平衡二叉树
//为空，返回真；不为空，左子树和右子树都是AVL树并且左子树和右子树高度相差不大于1，返回真，其他返回假
bool IsAVL(BinaryTree pRoot, int &height);

//求二叉树的镜像
//（1）如果二叉树为空，返回空
//（2）如果二叉树不为空，求左子树和右子树的镜像，然后交换左子树和右子树
BinaryTreeNode* Mirror(BinaryTreeNode* pRoot);

//求二叉树中两个节点的最低公共祖先节点
//递归解法：
//（1）如果两个节点分别在根节点的左子树和右子树，则返回根节点
//（2）如果两个节点都在左子树，则递归处理左子树；如果两个节点都在右子树，则递归处理右子树
//辅助函数：判断是不是在二叉树上
BinaryTreeNode* GetLastCommenParent(BinaryTreeNode* pRoot, BinaryTreeNode* pNode1, BinaryTreeNode* pNode2);

#endif

