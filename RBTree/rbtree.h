#ifndef _RBTREE_H_
#define _RBTREE_H_
/*
红黑树是一个满足如下条件的二叉搜索树：
1.每个结点要么是红的要么是黑的。
2.根结点是黑的。
3.每个叶结点（叶结点即指树尾端NIL指针或NULL结点）都是黑的。
4.如果一个结点是红的，那么它的两个儿子都是黑的。
5.对于任意结点而言，其到叶结点树尾端NIL指针的每条路径都包含相同数目的黑结点。

红黑树的特点： 一棵具有n个内结点（即真正的数据结点）的红黑树的黑高度bh至多为2lg(n+1) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;
//颜色的类型
typedef enum color_t
{
	RED = 0,
	BLACK = 1
}color_t;

//红黑树的结点定义
typedef struct __RBTreeNode
{
	ElemType key;				//关键字
	color_t color;				//颜色，红色或者黑色
	struct __RBTreeNode* left;	//左儿子
	struct __RBTreeNode* right;	//右儿子
	struct __RBTreeNode* parent;//父节点
}RBTreeNode, *RBTree;

//一些操作
//创建
void InitTree(RBTree* p);
//查找
RBTreeNode* RBSearch(RBTree *rbTree, ElemType key);
//返回最大节点
RBTreeNode* RBFindMax(RBTree rbTree);
//返回最小节点
RBTreeNode* RBFindMin(RBTree rbTree);
//返回后继节点
RBTreeNode* RBSuccessor(RBTree *rbTree, ElemType data);

//插入
bool RBInsert(RBTree *rbTree, ElemType data);
//删除
bool RBDelete(RBTree *rbTree, ElemType data);


//销毁
void Destroy(RBTree pRoot);

void PrintRBTree(RBTree pRoot);

#endif