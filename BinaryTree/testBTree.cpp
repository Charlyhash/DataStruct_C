#include "BinaryTree.h"

//direction为 0，表示该节点是根节点;
//direction为 - 1，表示该节点是它的父结点的左孩子;
//direction为 1，表示该节点是它的父结点的右孩子。
void PrintTree(BinaryTree tree, ElemType key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree是根节点
			printf("%2d is root\n", tree->key);
		else                // tree是分支节点
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

	//printf("节点个数为：%d\n", GetNodeNum(root));
	//printf("数的深度为：%d\n", GetDepth(root));
	//LevelTraverse(root);

	printf("第2层的节点个数为：%d\n", GetNodeNumKthLevel(root, 2));
	printf("叶子节点个数为：%d\n", GetLeafNum(root));
	
	return 0;
}

