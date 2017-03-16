#include "BinaryTree.h"

//directionΪ 0����ʾ�ýڵ��Ǹ��ڵ�;
//directionΪ - 1����ʾ�ýڵ������ĸ���������;
//directionΪ 1����ʾ�ýڵ������ĸ������Һ��ӡ�
void PrintTree(BinaryTree tree, ElemType key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree�Ǹ��ڵ�
			printf("%2d is root\n", tree->key);
		else                // tree�Ƿ�֧�ڵ�
			printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");

		PrintTree(tree->left, tree->key, -1);
		PrintTree(tree->right, tree->key, 1);
	}
}

int main()
{
	BinaryTree root;
	InitTree(&root);
	//CreateTree(&root);
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	CreateTreeUseArray(&root, arr, 10);

	PrintTree(root, root->key, 0);

	//PreorderTraverse(root);
	//printf("\n");
	//InorderTraverse(root);
	//printf("\n");
	//PostorderTraverse(root);
	//printf("\n");

	//printf("�ڵ����Ϊ��%d\n", GetNodeNum(root));
	//printf("�������Ϊ��%d\n", GetDepth(root));
	//LevelTraverse(root);

	printf("��2��Ľڵ����Ϊ��%d\n", GetNodeNumKthLevel(root, 2));
	printf("Ҷ�ӽڵ����Ϊ��%d\n", GetLeafNum(root));
	
	return 0;
}

