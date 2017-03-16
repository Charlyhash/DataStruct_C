/*

哈夫曼树：一般来说，用n（n>0）个带权值的叶子来构造二叉树，限定二叉树中除了这n个叶子外只能出现度为2的结点。
那么符合这样条件的二叉树往往可构造出许多颗，其中带权路径长度最小的二叉树就称为哈夫曼树或最优二叉树。

哈夫曼树的构造：根据哈弗曼树的定义，一棵二叉树要使其带权路径值最小，必须使权值越大的叶子结点越靠近根结点，而权值越小的叶子结点
越远离根结点。

哈夫曼树的构造过程：
1.  对一个给定的n个权值{w1,w2,...,wn},构造n棵只有根节点的二叉树，权值为Wi
2. 构建的森林中，选取权值最小的树作为左右子树，构建一个新的二叉树。新的二叉树的节点为左右子树权值之和
3. 在森林中删除这两棵树，同时加入新构建的二叉树。
4. 重复以上两部，直到构建成一棵树。这棵树就是哈夫曼树。

哈夫曼树的特点：

1. 对于同一组权值，哈夫曼数不是唯一的
2. 哈夫曼树左右可以互换
3. 带权值的节点都是叶子节点
4. n个叶子节点的哈夫曼树有(2n-1)个节点
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//vs2015
#pragma warning(disable:4996)

typedef struct Node {
	int weight;		//权值
	int parent;		//父节点的序号，0是根节点
	int lchild;		//左右子树，0为叶子节点
	int rchild;
}HTNode, *HuffmanTree;

typedef char** HUffmanCode;		//每一个节点的哈夫曼编码


//从HT数组中找到前k个元素，选出weight最小且parent为-1的元素并返回该元素的序号
int minIndex(HuffmanTree HT, int k)
{
	int i = 0;
	int ret;
	int retWeight;

	while (HT[i].parent != -1)
		++i;
	ret = i;
	retWeight = HT[i].weight;

	for (; i<k; ++i)
	{
		if (HT[i].parent == -1 && HT[i].weight < retWeight)
		{
			ret = i;
			retWeight = HT[i].weight;
		}
	}

	//已选的parent置为1,以免下次会再次选到。
	HT[ret].parent = 1;//这是没有关系的，因为每当选到了之后，会调整其parent。
	//printf("%d \n", ret);
	return ret;
}

//辅助函数:选出最小的两个节点，返回的是节点在的位置
//因为这里是用数组模拟节点的关系
void SelectMin(HuffmanTree HT, int k, int &min1, int &min2)
{
	min1 = minIndex(HT, k);
	min2 = minIndex(HT, k);
}


//使用weigh数组构建一个huffman树
HuffmanTree CreateTree(int* weight, int n)
{
	int total = 2 * n - 1;
	HuffmanTree HT = (HuffmanTree)malloc(total * sizeof(HTNode));
	if (!HT)
	{
		printf("HuffmanTree malloc faild!\n");
		exit(-1);
	}
	int i;

	//HT[0...n-1]存放的是需要编码的n个叶子节点
	//初始情况下父节点和左右子节点都为-1
	for (i = 0; i < n; ++i)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].weight = *weight;
		weight++;
	}

	//HT[n ... 2n-2]存放的是中间构造的二叉树的节点
	for (; i<total; ++i)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].weight = -1;
	}

	int min1, min2;
	for (i = n; i < total; ++i)
	{
		SelectMin(HT, i, min1, min2);
		HT[min1].parent = i;
		HT[min2].parent = i;
		HT[i].lchild = min1;
		HT[i].rchild = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
	}

	return HT;
}


//从叶子节点逆向求解哈夫曼编码
void HufmanCoding(HuffmanTree HT, HUffmanCode &HC, int n)
{
	HC = (HUffmanCode)malloc(n * sizeof(char*));
	if (!HC)
	{
		printf("HuffmanCoding Error!\n");
		exit(-1);
	}

	char* code = (char *)malloc(sizeof(char)*n);//临时存放code
	code[n - 1] = '\0';//结束符
	int i;
	for (i = 0; i<n; ++i)
	{
		int cur = i;
		int father = HT[i].parent;
		int start = n - 1;
		while (father != -1)//没有到顶点
		{
			if (HT[father].lchild == cur)
				code[--start] = '0';
			else
				code[--start] = '1';

			cur = father;
			father = HT[father].parent;
		}
		printf("len : %d", n - start);
		HC[i] = (char*)malloc((n - start) * sizeof(char));//为字符i的编码分配足够的存储空间
		if (!HC[i])
		{
			printf("HC[%d] malloc error!\n", i);
			exit(-1);
		}

		strcpy(HC[i], code + start);
	}

	free(code);

}

void TEST_HUFMAN()
{
	freopen("input.txt", "r", stdin);
	int n;   //需要编码的字符的个数

	scanf("%d", &n);

	int i;
	int *wet = (int *)malloc(n * sizeof(int));  //存放每个字符的权值
	for (i = 0; i<n; i++)
	{
		scanf("%d", wet + i);
	}

	HUffmanCode HC;  //保存赫夫曼编码
	HuffmanTree HT = CreateTree(wet, n);  //生成赫夫曼树
	HufmanCoding(HT, HC, n);        //求每个字符的赫夫曼编码

	printf("哈夫曼编码如下：\n");
	for (i = 0; i<n; i++)
	{
		puts(HC[i]);
	}
	free(wet);
}

//int main()
//{
//	TEST_HUFMAN();
//
//	return 0;
//}

