#include "BinarySearchTree.h"

//directionΪ 0����ʾ�ýڵ��Ǹ��ڵ�;
//directionΪ - 1����ʾ�ýڵ������ĸ���������;
//directionΪ 1����ʾ�ýڵ������ĸ������Һ��ӡ�
void PrintBST(BSTree tree, ElemType key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree�Ǹ��ڵ�
			printf("%2d is root\n", tree->key);
		else                // tree�Ƿ�֧�ڵ�
			printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");

		PrintBST(tree->left, tree->key, -1);
		PrintBST(tree->right, tree->key, 1);
	}
}

int main()
{
	BSTree p;
	InitTree(&p);
	int arr[10] = { 1,2,5,6,8,9,3,4,7,0 };
	CreateBST(&p, arr, 10);
	
	PreorderTraverse(p);
	printf("\n");
	InorderTraverse(p);
	printf("\n");
	PostorderTraverse(p);
	printf("\n");
	PrintBST(p, p->key, 0);
	printf("���ֵ��%d\n",  Retrieve(FindMax(p)));
	printf("��Сֵ��%d\n", Retrieve(FindMin(p)));
	Insert(11, p);
	Insert(12, p);
	InorderTraverse(p);
	printf("\n");
	p = Delete(11, p);
	p = Delete(12,p);
	printf("\n");
	MakeEmpty(p);

	return 0;
}