#include "rbtree.h"

//һЩ��������
//����
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
	//���xΪ���ڵ�
	if (x->parent == NULL)
	{
		*rbTree = y;		//��ʱ�ĸ��ڵ��Ϊ��y
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
//����
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

//һ�β��������ֻ�����ƻ�����(2)��(4)
//�������ڵ�ĸ��ڵ��Ǻ�ɫ�������ƻ��κ�����
//���������Ǹ���㣬�����ֻ��Υ������2�����ֱ�ӰѴ˽��ͿΪ��ɫ��
//�������ڵ�ĸ��ڵ��Ǻ�ɫ(z->parent->parentһ��Ϊ��ɫ����Ϊԭ���Ǻ����)�����ƻ�����4��һ�¼������
//1.z������ڵ�y�Ǻ�ɫ����������°�p[z]��y��Ϳ�ڣ���ǰ�ڵ���Ϊp[p[z]]�������ϵ���
//2.z������ڵ�y�Ǻ�ɫ��z���Һ��ӣ���ǰ�ڵ�ĸ��ڵ���Ϊ�µĵ�ǰ�ڵ㣬���µ�ǰ�ڵ�Ϊ֧����������Ϊ���3
//3.z������ڵ�y�Ǻ�ɫ��z�����ӣ����ڵ��Ϊ��ɫ���游�ڵ��Ϊ��ɫ�����游�ڵ�Ϊ֧������
 static void InsertFixup(RBTree *rbTree, RBTreeNode* x)
{
	RBTreeNode *p, *gparent, *uncle;

	while (((p = x->parent) != NULL) && (p->color == RED))
	{
		gparent = p->parent;			//�游�ڵ�
		if (p == gparent->left)		//�����ڵ�Ϊ����ʱ
		{
			uncle = gparent->right;	//����ڵ�Ϊ�Һ���
			//1.z������ڵ�y�Ǻ�ɫ
			if (uncle != NULL && uncle->color == RED)
			{
				gparent->color = RED;		//(1)���游�ڵ�Ϳ��
				p->color = BLACK;			//(2)�Ѹ��ڵ������ڵ�Ϳ��
				uncle->color = BLACK;
				x = gparent;				//�ѵ�ǰ�ڵ���Ϊ�游�ڵ�
			}
			else  //����ڵ��Ǻ�ɫ
			{
				//2.z������ڵ�y�Ǻ�ɫ��z���Һ���
				if (x == p->right)
				{
					x = p;					//��ǰ�ڵ�ĸ��ڵ�Ϊ�µĵ�ǰ�ڵ�
					LeftRotate(rbTree, x);	//�Ե�ǰ�ڵ�����
					p = x->parent;			//��ת��p��Ϊz�ڵ�ĸ����
				}
				//3.z������ڵ�y�Ǻ�ɫ��z������
				p->color = BLACK;				//�Ѹ��ڵ���Ϊ��ɫ
				gparent->color = RED;			//�游�ڵ���Ϊ��ɫ										
				RightRotate(rbTree, gparent);	//���游�ڵ�����	
			}
		}
		else //���ڵ�Ϊ�游�ڵ���Һ���
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
 *ɾ���ĵ�����ɾ��һ����ɫ�ڵ�ᵼ��һ�¼������
 *(1) ���ɾ���Ľڵ��Ǹ��ڵ㣬��y��һ����ɫ���ӳ�Ϊ���µĸ�����Υ��������2 
 *(2) ���y�ĸ������亢�ӽ�㶼�Ǻ�ɫ�ģ���Υ��������4 
 *(3) ɾ��y��������ǰ����y���κ�·���ϵĺڽ������һ�����ƻ�������5��
 * ��������ǣ���ɾ���Ľ���ɫ�������Ƶ��亢�ӽ��x�ϡ���ʱ����5�����Ա��֣����Ǵ���2�������
 * ��1��xԭ��Ϊ��ɫ����ʱ���ӽ�������Ǻ�ڣ���ʱ�ƻ������ʣ�1������4�������x�����������ƻ������ʣ�2��
 *       ����ʽΪ����x������ɫΪ��ɫ���˲���ͬʱȥ�������ĺ�ɫ���ԣ���������ϣ���������ʵ��Ա���
 * ��2��xԭ��Ϊ��ɫ����ʱx������Ϊ˫�غ�ɫ���ƻ������ʣ�1������xΪ�����������ֻ�Ǽ򵥵�����x����ĺ�ɫ����
 *       ������Ҫ����Ҫ����ת����ɫ�޸�
 */

 static void DeleteFixup(RBTree *rbTree, RBTreeNode* parent, RBTreeNode* x)
 {
	 RBTreeNode* brother;

	 while ((x == NULL || x->color == BLACK) && x != *rbTree)
	 {
		 if (parent->left == x)
		 {
			 brother = parent->right;
			 //���1������ֵܽ��Ϊ��ɫ,��parent��ɫ��Ϊ��ɫ����ʱ������ɫ����������ʹ��brother��  
			 //parentλ�õ������˲������ƻ�������ʣ��������1�仯Ϊ���2��3��4 
			 if (brother->color == RED)
			 {
				 brother->color = BLACK;			//�ֵܽڵ���Ϊ��ɫ
				 parent->color = RED;			//���ڵ���Ϊ��ɫ
				 LeftRotate(rbTree, parent);	//�Ը��ڵ�����
				 brother = parent->right;		//���������ֵܽڵ�
			 }
			 //���2�� brother��������ɫ��㣨NULLҲΪ��ɫ��㣩:��x��brotherĨ��һ�غ�ɫ  
			 //�������Ϊ��brother����ɫ��Ϊ�죬x������Ƶ��丸���  
			 if ((brother->left == NULL || brother->left->color == BLACK) &&
				 (brother->right == NULL || brother->right->color == BLACK))
			 {
				 brother->color = RED;
				 x = parent;
				 parent = parent->parent;
			 }
			 else
			 {
				 //���3�� brother����Ϊ��ɫ��㣬�Һ���Ϊ��ɫ���  
				 if ((brother->right == NULL) || (brother->right->color == BLACK))
				 {
					 brother->left->color = BLACK;		//
					 brother->color = RED;				//�ֵܽڵ���Ϊ��ɫ
					 LeftRotate(rbTree, brother);
					 brother = parent->left;
					 //תΪ���4
				 }
				 //���4��brother���Һ���Ϊ��ɫ�ڵ�
				 //����brother��parent����ɫ��λ�ã�ʹ��x��2�غ�ɫ�����е�һ��ת�Ƶ���parent��  
				 //��ʱ��brother���Һ��ӵĺڽ������һ�����ǽ��ҽ�����ɫ�úڣ���������ʵ��Ա���  
				 brother->color = parent->color;
				 parent->color = BLACK;
				 brother->right->color = BLACK;
				 LeftRotate(rbTree, parent);			 

				 x = *rbTree;		//x��Ϊ���ڵ㣬ѭ������
			 }
		 }
		 else
		 {
			 brother = parent->left;
			 //���1
			 if (brother->color == RED)
			 {
				 brother->color = BLACK;
				 parent->color = RED;
				 RightRotate(rbTree, parent);
				 brother = parent->left;
			 }
			 //���2
			 if ((brother->left == NULL || brother->left->color == BLACK) &&
				 (brother->right == NULL || brother->right->color == BLACK))
			 {
				 brother->color = RED;
				 x = parent;
				 parent = parent->parent;
			 }
			 else
			 {
				 //���3
				 if (brother->left == NULL || brother->left->color == BLACK)
				 {
					 brother->right->color = BLACK;
					 brother->color = RED;
					 LeftRotate(rbTree, brother);
					 brother = parent->left;
				 }
				 //���4
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

 //����
 void InitTree(RBTree* p)
 {
	 p = NULL;
 }

//����
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
//�������ڵ�
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
//������С�ڵ�
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
//���غ�̽ڵ�
 //���x������������ô��̽ڵ�Ϊ������������ߵĽڵ㣻
 //���û������������ô��̽ڵ�Ϊ
 RBTreeNode* RBSuccessor(RBTree *rbTree, ElemType data)
 {
	 RBTreeNode* x = RBSearch(rbTree, data);
	 if (x == NULL)
		 return NULL;
	 if (x->right != NULL)
		 return RBFindMin(x->right);
	 RBTreeNode* y = x->parent;
	 while (y != NULL && x == y->right)	//һֱ����������ֱ��xΪy������
	 {
		 x = y;
		 y = y->parent;
	 }

	 return y;
 }

//����
//�²���Ľڵ㣬��ɫΪ��ɫ;����֮�󣬿����ƻ�����������ʣ���Ҫ����
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
//ɾ��
bool RBDelete(RBTree *rbTree, ElemType data)
{
	RBTreeNode *target, *realDel, *child;
	target = RBSearch(rbTree, data);
	if (target != NULL)			//targetΪĿ��ڵ�
	{
		//����ɾ���Ľڵ�ֻ��һ�����ӻ���û�к��ӵ�ʱ�򣬿���ֱ��ɾ��
		if (target->left == NULL || target->right == NULL)		
			realDel = target;
		else
			realDel = RBSuccessor(rbTree, data);	//����ɾ�����̣���̵�ֵ���Ŀ��ڵ��ֵ

		if (realDel->left != NULL)					//����realDel����������������
			child = realDel->left;
		else
			child = realDel->right;
		if (child != NULL)
			child->parent = realDel->parent;			//����childe��parent,Ϊ�վͲ��ù�
		if (realDel->parent == NULL)					//�����ǵ����丸�ڵ㣺ɾ�����Ǹ��ڵ�
			*rbTree = child;
		else										//ɾ���Ĳ�Ϊ���ڵ�
		{
			if (realDel->parent->left == realDel)
				realDel->parent->left = child;
			else
				realDel->parent->right = child;
		}
		if (target != realDel)						//��̵�ֵ���Ŀ��ڵ��ֵ
			target->key = realDel->key;
		if (realDel->color == BLACK)					//ɾ�����Ǻ�ɫ�ڵ㲻�õ���
			DeleteFixup(rbTree, realDel->parent, child);			//childΪɾ���ڵ�ĺ��ӣ�parentΪɾ���ڵ�ĸ��ڵ�
		free(realDel);
		return true;
	}
	else
		return false;
}

//����
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

//��ӡ
static void PrintRBTreeAux(RBTree pRoot, ElemType key, int dir)
{
	if (pRoot != NULL)
	{
		if (dir == 0)		//���ڵ�
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