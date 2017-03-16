#include "BTree.h"
#include <iostream>


int main()
{
	const int len = 10;
	int data[len] = {'G', 'M', 'P', 'X', 'A', 'C', 'D', 'E', 'J', 'K'};
	BTree tree = NULL;

	//¥¥Ω®
	BTreeCreate(&tree, data, len);
	printf("create tree:\n");
	BTreePrint(tree);
	printf("\n");

	//≤È’“£∫
	for (int i = 0; i < len; ++i)
	{
		int pos = -1;
		BTNode* node = BTreeSearch(tree, data[i], &pos);
		if (node)
		{
			printf("find the node.data:%c, nodeNum:%d, index:%d\n", data[i], node->keyNum, pos);
		}
		else
			printf("not find the key %c", data[i]);
	}

	//find 'B'
	int pos = -1;
	BTNode* node = BTreeSearch(tree, 'B', &pos);
	if (node)
	{
		printf("find the key 'B'\n");
	}
	else
		printf("not find the key 'B'\n");


	//remove
	for (int i = 0; i < len - 1; ++i)
	{
		BTreeRemove(&tree, data[i]);
		BTreePrint(tree);
		printf("\n");
	}

	//destory tree
	BTreeDestory(&tree);
}