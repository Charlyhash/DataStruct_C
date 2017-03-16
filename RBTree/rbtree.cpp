#include "rbtree.h"

//一些辅助函数
//左旋
static void LeftRotate(RBTree* rbTree, RBTreeNode* x)
{
	RBTreeNode* y;
	y = x->right;
	x->right = y->left;
	if (y->left != NULL)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	//如果x为根节点
	if (x->parent == NULL)
	{
		*rbTree = y;		//此时的根节点变为了y
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}
//右旋
static void RightRotate(RBTree* rbTree, RBTreeNode* x)
{
	RBTreeNode* y;
	y = x->left;
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		*rbTree = y;
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

static RBTreeNode* MakeNode(ElemType x)
{
	RBTreeNode* p = (RBTreeNode*)malloc(sizeof(RBTreeNode));
	if (p == NULL)
		return NULL;
	p->key = x;
	p->color = RED;
	p->left = p->right = NULL;
	p->parent = NULL;

	return p;
}

//一次插入操作，只可能破坏性质(2)和(4)
//如果插入节点的父节点是黑色，不会破坏任何性质
//如果插入的是根结点，此情况只会违反性质2，因此直接把此结点涂为黑色；
//如果插入节点的父节点是红色(z->parent->parent一定为黑色，因为原来是红黑树)，会破坏性质4有一下几种情况
//1.z的叔叔节点y是红色：这种情况下把p[z]和y都涂黑，当前节点设为p[p[z]]继续向上调整
//2.z的叔叔节点y是黑色，z是右孩子：当前节点的父节点做为新的当前节点，以新当前节点为支点左旋，变为情况3
//3.z的叔叔节点y是黑色，z是左孩子：父节点变为黑色，祖父节点变为红色，在祖父节点为支点右旋
 static void InsertFixup(RBTree *rbTree, RBTreeNode* x)
{
	RBTreeNode *p, *gparent, *uncle;

	while (((p = x->parent) != NULL) && (p->color == RED))
	{
		gparent = p->parent;			//祖父节点
		if (p == gparent->left)		//当父节点为左孩子时
		{
			uncle = gparent->right;	//叔叔节点为右孩子
			//1.z的叔叔节点y是红色
			if (uncle != NULL && uncle->color == RED)
			{
				gparent->color = RED;		//(1)把祖父节点涂红
				p->color = BLACK;			//(2)把父节点和叔叔节点涂黑
				uncle->color = BLACK;
				x = gparent;				//把当前节点设为祖父节点
			}
			else  //叔叔节点是黑色
			{
				//2.z的叔叔节点y是黑色，z是右孩子
				if (x == p->right)
				{
					x = p;					//当前节点的父节点为新的当前节点
					LeftRotate(rbTree, x);	//对当前节点左旋
					p = x->parent;			//旋转后，p仍为z节点的父结点
				}
				//3.z的叔叔节点y是黑色，z是左孩子
				p->color = BLACK;				//把父节点设为黑色
				gparent->color = RED;			//祖父节点设为红色										
				RightRotate(rbTree, gparent);	//对祖父节点右旋	
			}
		}
		else //父节点为祖父节点的右孩子
		{
			uncle = gparent->left;
			if (uncle && uncle->color == RED)
			{
				uncle->color = BLACK;
				p->color = BLACK;
				gparent->color = RED;
				x = gparent;
			}
			else
			{
				if (p->left == x)
				{
					x = p;
					RightRotate(rbTree, x);
					p = x->parent;
				}
				p->color = BLACK;
				gparent->color = RED;
				LeftRotate(rbTree, gparent);
			}
		}
	}

	(*rbTree)->color = BLACK;
}

 /*
 *删除的调整。删除一个黑色节点会导致一下几种情况
 *(1) 如果删除的节点是根节点，而y的一个红色孩子成为了新的根，则违反了性质2 
 *(2) 如果y的父结点和其孩子结点都是红色的，则违反了性质4 
 *(3) 删除y将导致先前包含y的任何路径上的黑结点树少一个，破坏了性质5。
 * 解决方案是：被删除的结点黑色属性下移到其孩子结点x上。此时性质5都得以保持，于是存在2种情况：
 * （1）x原来为红色，此时孩子结点属性是红黑，此时破坏了性质（1），（4），如果x还是树根则，破坏了性质（2）
 *       处理方式为：将x重新着色为黑色（此操作同时去除其多余的黑色属性），处理完毕，红黑树性质得以保持
 * （2）x原来为黑色，此时x的属性为双重黑色，破坏了性质（1），若x为树根，则可以只是简单的消除x多余的黑色属性
 *       否则需要做必要的旋转和颜色修改
 */

 static void DeleteFixup(RBTree *rbTree, RBTreeNode* parent, RBTreeNode* x)
 {
	 RBTreeNode* brother;

	 while ((x == NULL || x->color == BLACK) && x != *rbTree)
	 {
		 if (parent->left == x)
		 {
			 brother = parent->right;
			 //情况1：如果兄弟结点为红色,则parent颜色比为黑色，此时调整颜色，并左旋，使得brother和  
			 //parent位置调换，此操作不破坏别的性质，并将情况1变化为情况2，3，4 
			 if (brother->color == RED)
			 {
				 brother->color = BLACK;			//兄弟节点设为黑色
				 parent->color = RED;			//父节点设为红色
				 LeftRotate(rbTree, parent);	//对父节点左旋
				 brother = parent->right;		//重新设置兄弟节点
			 }
			 //情况2： brother有两个黑色结点（NULL也为黑色结点）:将x和brother抹除一重黑色  
			 //具体操作为，brother的颜色变为红，x结点上移到其父结点  
			 if ((brother->left == NULL || brother->left->color == BLACK) &&
				 (brother->right == NULL || brother->right->color == BLACK))
			 {
				 brother->color = RED;
				 x = parent;
				 parent = parent->parent;
			 }
			 else
			 {
				 //情况3： brother左孩子为红色结点，右孩子为黑色结点  
				 if ((brother->right == NULL) || (brother->right->color == BLACK))
				 {
					 brother->left->color = BLACK;		//
					 brother->color = RED;				//兄弟节点设为红色
					 LeftRotate(rbTree, brother);
					 brother = parent->left;
					 //转为情况4
				 }
				 //情况4：brother的右孩子为红色节点
				 //交换brother和parent的颜色和位置，使得x的2重黑色属性中的一重转移到其parent上  
				 //此时到brother的右孩子的黑结点数少一，于是将右结点的颜色置黑，红黑树性质得以保持  
				 brother->color = parent->color;
				 parent->color = BLACK;
				 brother->right->color = BLACK;
				 LeftRotate(rbTree, parent);			 

				 x = *rbTree;		//x设为根节点，循环结束
			 }
		 }
		 else
		 {
			 brother = parent->left;
			 //情况1
			 if (brother->color == RED)
			 {
				 brother->color = BLACK;
				 parent->color = RED;
				 RightRotate(rbTree, parent);
				 brother = parent->left;
			 }
			 //情况2
			 if ((brother->left == NULL || brother->left->color == BLACK) &&
				 (brother->right == NULL || brother->right->color == BLACK))
			 {
				 brother->color = RED;
				 x = parent;
				 parent = parent->parent;
			 }
			 else
			 {
				 //情况3
				 if (brother->left == NULL || brother->left->color == BLACK)
				 {
					 brother->right->color = BLACK;
					 brother->color = RED;
					 LeftRotate(rbTree, brother);
					 brother = parent->left;
				 }
				 //情况4
				 brother->color = parent->color;
				 parent->color = BLACK;
				 brother->left->color = BLACK;
				 RightRotate(rbTree, parent);

				 x = *rbTree;
			 }
		 }
	 }

	 if (x != NULL)
		 x->color = BLACK;
 }

 //创建
 void InitTree(RBTree* p)
 {
	 p = NULL;
 }

//查找
 RBTreeNode* RBSearch(RBTree *rbTree, ElemType key)
 {
	 if (*rbTree == NULL)
		 return NULL;
	 RBTreeNode* pNode = *rbTree;
	 while (pNode != NULL)
	 {
		 if (pNode->key == key)
			 return pNode;
		 else if (pNode->key < key)
			 pNode = pNode->right;
		 else
			 pNode = pNode->left;
	 }

	 return pNode;
 }
//返回最大节点
 RBTreeNode* RBFindMax(RBTree rbTree)
 {
	 if (rbTree == NULL)
		 return NULL;
	 while (rbTree->right != NULL)
	 {
		 rbTree = rbTree->right;
	 }

	 return rbTree;
 }
//返回最小节点
 RBTreeNode* RBFindMin(RBTree rbTree)
 {
	 if (rbTree == NULL)
		 return NULL;
	 while (rbTree->left != NULL)
	 {
		 rbTree = rbTree->left;
	 }

	 return rbTree;
 }
//返回后继节点
 //如果x有右子树，那么后继节点为右子树中最左边的节点；
 //如果没有右子树，那么后继节点为
 RBTreeNode* RBSuccessor(RBTree *rbTree, ElemType data)
 {
	 RBTreeNode* x = RBSearch(rbTree, data);
	 if (x == NULL)
		 return NULL;
	 if (x->right != NULL)
		 return RBFindMin(x->right);
	 RBTreeNode* y = x->parent;
	 while (y != NULL && x == y->right)	//一直向上搜索，直到x为y的左孩子
	 {
		 x = y;
		 y = y->parent;
	 }

	 return y;
 }

//插入
//新插入的节点，颜色为红色;插入之后，可能破坏红黑树的性质，需要调整
bool RBInsert(RBTree *rbTree, ElemType data)
{
	RBTreeNode* node, *p, *cur;
	node = MakeNode(data);
	if (node == NULL)
		return false;
	cur = *rbTree;
	p = NULL;
	while (cur != NULL)
	{
		p = cur;
		if (data < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	if (p == NULL)
		*rbTree = node;
	else
	{
		if (data < p->key)
			p->left = node;
		else
			p->right = node;
	}
	node->parent = p;
	InsertFixup(rbTree, node);

	return true;

}
//删除
bool RBDelete(RBTree *rbTree, ElemType data)
{
	RBTreeNode *target, *realDel, *child;
	target = RBSearch(rbTree, data);
	if (target != NULL)			//target为目标节点
	{
		//当被删除的节点只有一个孩子或者没有孩子的时候，可以直接删除
		if (target->left == NULL || target->right == NULL)		
			realDel = target;
		else
			realDel = RBSuccessor(rbTree, data);	//否则，删除其后继，后继的值替代目标节点的值

		if (realDel->left != NULL)					//最后的realDel不可能有两个孩子
			child = realDel->left;
		else
			child = realDel->right;
		if (child != NULL)
			child->parent = realDel->parent;			//调整childe的parent,为空就不用管
		if (realDel->parent == NULL)					//以下是调整其父节点：删除的是根节点
			*rbTree = child;
		else										//删除的不为父节点
		{
			if (realDel->parent->left == realDel)
				realDel->parent->left = child;
			else
				realDel->parent->right = child;
		}
		if (target != realDel)						//后继的值替代目标节点的值
			target->key = realDel->key;
		if (realDel->color == BLACK)					//删除的是红色节点不用调整
			DeleteFixup(rbTree, realDel->parent, child);			//child为删除节点的孩子，parent为删除节点的父节点
		free(realDel);
		return true;
	}
	else
		return false;
}

//销毁
void Destroy(RBTree pRoot)
{
	if (pRoot == NULL)
		return;
	if (pRoot->left != NULL)
		Destroy(pRoot->left);
	if (pRoot->right != NULL)
		Destroy(pRoot->right);

	free(pRoot);
}

//打印
static void PrintRBTreeAux(RBTree pRoot, ElemType key, int dir)
{
	if (pRoot != NULL)
	{
		if (dir == 0)		//根节点
			printf("%2d(B) is root \n", pRoot->key);
		else
			printf("%2d(%s) is %2d's %6s child\n", 
				pRoot->key, pRoot->color == BLACK ? "B" : "R", key, dir == 1 ? "right" : "left");
		PrintRBTreeAux(pRoot->left, pRoot->key, -1);
		PrintRBTreeAux(pRoot->right, pRoot->key, 1);
	}
}

void PrintRBTree(RBTree pRoot)
{
	if (pRoot != NULL)
		PrintRBTreeAux(pRoot, pRoot->key, 0);
}