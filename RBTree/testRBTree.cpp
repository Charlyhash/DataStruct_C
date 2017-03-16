#include "rbtree.h"


int main()
{
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };
	int len = 9;
	RBTree tree = NULL;
	for (int i = 0; i < len; ++i)
	{
		if (RBInsert(&tree, a[i]) == false)
			break;
		//printf("������ϸ��Ϣ��\n");
		//PrintRBTree(tree);
	}
	printf("������ϸ��Ϣ��\n");
	PrintRBTree(tree);

	for (int i = 0; i < len; ++i)
	{
		RBDelete(&tree, a[i]);
		printf("ɾ����%d��\n",a[i]);
		if (tree)
		{
			printf("������ϸ��Ϣ��\n");
			PrintRBTree(tree);
		}
	}

	return 0;
}