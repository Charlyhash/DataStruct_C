//�ڽӱ�����ͼ�ı�ʾ
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define isLetter(a) (((a >= 'a') && (a <= 'z')) || ((a >= 'A') && (a <= 'Z')))
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))
#define scanf scanf_s
#define MAX 20

//����ָ����������������
typedef struct _ENode
{
	int ivex;		//λ��
	struct _ENode* next_edeg;	//��һ����
}ENode, *PENode;

//�����ʾ
typedef struct _VNode
{
	char data;		//������Ϣ
	ENode* first_edge; //ָ��ĵ�һ����
}VNode;

//�ڽӱ�
typedef struct _LGraph
{
	int vexnum;
	int edgenum;
	VNode vexs[MAX];
}LGraph, *PLGraph;

static int get_position(LGraph G, char ch)
{
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vexs[i].data == ch)
			return i;

	return -1;
}

//���ӵ������β��
static void link_last(ENode* list, ENode* node)
{

	ENode* p = list;
	while (p->next_edeg != NULL)
		p = p->next_edeg;
	p->next_edeg = node;

}

LGraph* create_example_graph()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'G' },
		{ 'B', 'A' },
		{ 'B', 'D' },
		{ 'C', 'F' },
		{ 'C', 'G' },
		{ 'D', 'E' },
		{ 'D', 'F' } };
	int vexsLen = LENGTH(vexs);
	int edgesNum = LENGTH(edges);

	//��ʼ���ڽӱ�
	LGraph *pG = (LGraph*)malloc(sizeof(LGraph));
	if (pG == NULL)
		return NULL;
	memset(pG, 0, sizeof(LGraph));
	pG->vexnum = vexsLen;
	pG->edgenum = edgesNum;

	int i, p1, p2;
	char c1, c2;
	ENode *node1;
	//�����ʼ��
	for (i = 0; i < pG->vexnum; ++i)
	{
		pG->vexs[i].data = vexs[i];
		pG->vexs[i].first_edge = NULL;
	}
	//�ߵĳ�ʼ��
	for (i = 0; i < pG->vexnum; ++i)
	{
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = get_position(*pG, c1);
		p2 = get_position(*pG, c2);

		node1 = (ENode*)malloc(sizeof(ENode));
		memset(node1, 0, sizeof(ENode));
		//����ͼҪ��������
		node1->ivex = p2;
		if (pG->vexs[p1].first_edge == NULL)
			pG->vexs[p1].first_edge = node1;
		else
			link_last(pG->vexs[p1].first_edge, node1);
	}

	return pG;
}

//��ӡ
void print_lgraph(LGraph G)
{
	ENode* node;

	printf("List Graph:\n");
	for (int i = 0; i < G.vexnum; ++i)
	{
		printf("%d(%c)-->", i, G.vexs[i].data);
		node = G.vexs[i].first_edge;
		while (node != NULL)
		{
			printf("%d(%c)-->", node->ivex, G.vexs[node->ivex].data);
			node = node->next_edeg;
		}
		printf("\n");
	}
}

/*
��������
����������Ҫά��һ�����Ϊ0�Ķ��㼯�ϣ������Ƕ��У�ջ��������ÿ�δӸü�����ȡ��һ�����㣬�����õ����List��
������ѭ�������ɸö������������бߣ���ͼ���Ƴ������ߣ�ͬʱ��ȡ�ñߵ�����һ�����㣬
����ö��������ڼ�ȥ������֮��Ϊ0����ôҲ���������ŵ����Ϊ0�ļ����С�
Ȼ������Ӽ�����ȡ��һ������
*/

void topological_sort(LGraph G)
{
	int i, j;
	int index = 0;
	int head = 0;
	int rear = 0;
	int *queue;		//��������
	int *ins;		//�������
	char* tops;		//��¼���
	int num = G.vexnum;
	ENode* node;

	ins = (int *)malloc(num *sizeof(int));
	if (ins == NULL)
	{
		return;
	}
	tops = (char*)malloc(num*sizeof(char));
	if (tops == NULL)
	{
		free(ins);
		return;
	}
	queue = (int *)malloc(num*sizeof(int));
	if (queue == NULL)
	{
		free(ins);
		free(tops);
		return;
	}

	memset(ins, 0, num *sizeof(int));
	memset(tops, 0, num*sizeof(char));
	memset(queue, 0, num*sizeof(int));

	//ÿ������������
	for (i = 0; i < num; ++i)
	{
		node = G.vexs[i].first_edge;
		while (node != NULL)
		{
			ins[node->ivex]++;		//�ýڵ���������һ
			node = node->next_edeg;
		}
	}

	//�����Ϊ0�Ķ��������
	for (i = 0; i < num; ++i)
	{
		if (ins[i] == 0)
			queue[rear++] = i;
	}

	while (head != rear)
	{
		j = queue[head++];
		tops[index++] = G.vexs[j].data;		//����tops��
		node = G.vexs[j].first_edge;

		//�ڽӵ� ��ȼ�1
		while (node != NULL)
		{

			ins[node->ivex]--;
			if (ins[node->ivex] == 0)
				queue[rear++] = node->ivex;

			node = node->next_edeg;
		}
	}
	//�л�
	if (index != G.vexnum)
	{
		printf("Graph has a cycle!\n");
		free(queue);
		free(ins);
		free(tops);
		return;
	}

	printf("++++++topo sort+++++\n");
	for (i = 0; i < num; ++i)
		printf("%c ", tops[i]);
	printf("\n");

	free(queue);
	free(tops);
	free(ins);
}

int main()
{
	LGraph* pG;
	pG = create_example_graph();
	//pG = create_graph();

	print_lgraph(*pG);
	topological_sort(*pG);


	return 0;
}