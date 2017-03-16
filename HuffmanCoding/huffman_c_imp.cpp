/*

����������һ����˵����n��n>0������Ȩֵ��Ҷ����������������޶��������г�����n��Ҷ����ֻ�ܳ��ֶ�Ϊ2�Ľ�㡣
��ô�������������Ķ����������ɹ�������ţ����д�Ȩ·��������С�Ķ������ͳ�Ϊ�������������Ŷ�������

���������Ĺ��죺���ݹ��������Ķ��壬һ�ö�����Ҫʹ���Ȩ·��ֵ��С������ʹȨֵԽ���Ҷ�ӽ��Խ��������㣬��ȨֵԽС��Ҷ�ӽ��
ԽԶ�����㡣

���������Ĺ�����̣�
1.  ��һ��������n��Ȩֵ{w1,w2,...,wn},����n��ֻ�и��ڵ�Ķ�������ȨֵΪWi
2. ������ɭ���У�ѡȡȨֵ��С������Ϊ��������������һ���µĶ��������µĶ������Ľڵ�Ϊ��������Ȩֵ֮��
3. ��ɭ����ɾ������������ͬʱ�����¹����Ķ�������
4. �ظ�����������ֱ��������һ��������������ǹ���������

�����������ص㣺

1. ����ͬһ��Ȩֵ��������������Ψһ��
2. �����������ҿ��Ի���
3. ��Ȩֵ�Ľڵ㶼��Ҷ�ӽڵ�
4. n��Ҷ�ӽڵ�Ĺ���������(2n-1)���ڵ�
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//vs2015
#pragma warning(disable:4996)

typedef struct Node {
	int weight;		//Ȩֵ
	int parent;		//���ڵ����ţ�0�Ǹ��ڵ�
	int lchild;		//����������0ΪҶ�ӽڵ�
	int rchild;
}HTNode, *HuffmanTree;

typedef char** HUffmanCode;		//ÿһ���ڵ�Ĺ���������


//��HT�������ҵ�ǰk��Ԫ�أ�ѡ��weight��С��parentΪ-1��Ԫ�ز����ظ�Ԫ�ص����
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

	//��ѡ��parent��Ϊ1,�����´λ��ٴ�ѡ����
	HT[ret].parent = 1;//����û�й�ϵ�ģ���Ϊÿ��ѡ����֮�󣬻������parent��
	//printf("%d \n", ret);
	return ret;
}

//��������:ѡ����С�������ڵ㣬���ص��ǽڵ��ڵ�λ��
//��Ϊ������������ģ��ڵ�Ĺ�ϵ
void SelectMin(HuffmanTree HT, int k, int &min1, int &min2)
{
	min1 = minIndex(HT, k);
	min2 = minIndex(HT, k);
}


//ʹ��weigh���鹹��һ��huffman��
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

	//HT[0...n-1]��ŵ�����Ҫ�����n��Ҷ�ӽڵ�
	//��ʼ����¸��ڵ�������ӽڵ㶼Ϊ-1
	for (i = 0; i < n; ++i)
	{
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].weight = *weight;
		weight++;
	}

	//HT[n ... 2n-2]��ŵ����м乹��Ķ������Ľڵ�
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


//��Ҷ�ӽڵ�����������������
void HufmanCoding(HuffmanTree HT, HUffmanCode &HC, int n)
{
	HC = (HUffmanCode)malloc(n * sizeof(char*));
	if (!HC)
	{
		printf("HuffmanCoding Error!\n");
		exit(-1);
	}

	char* code = (char *)malloc(sizeof(char)*n);//��ʱ���code
	code[n - 1] = '\0';//������
	int i;
	for (i = 0; i<n; ++i)
	{
		int cur = i;
		int father = HT[i].parent;
		int start = n - 1;
		while (father != -1)//û�е�����
		{
			if (HT[father].lchild == cur)
				code[--start] = '0';
			else
				code[--start] = '1';

			cur = father;
			father = HT[father].parent;
		}
		printf("len : %d", n - start);
		HC[i] = (char*)malloc((n - start) * sizeof(char));//Ϊ�ַ�i�ı�������㹻�Ĵ洢�ռ�
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
	int n;   //��Ҫ������ַ��ĸ���

	scanf("%d", &n);

	int i;
	int *wet = (int *)malloc(n * sizeof(int));  //���ÿ���ַ���Ȩֵ
	for (i = 0; i<n; i++)
	{
		scanf("%d", wet + i);
	}

	HUffmanCode HC;  //����շ�������
	HuffmanTree HT = CreateTree(wet, n);  //���ɺշ�����
	HufmanCoding(HT, HC, n);        //��ÿ���ַ��ĺշ�������

	printf("�������������£�\n");
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

