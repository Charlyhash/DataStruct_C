//邻接表有向图的表示
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define isLetter(a) (((a >= 'a') && (a <= 'z')) || ((a >= 'A') && (a <= 'Z')))
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))
#define scanf scanf_s
#define MAX 20

//顶点指向的其他顶点的链表
typedef struct _ENode
{
	int ivex;		//位置
	struct _ENode* next_edeg;	//下一条弧
}ENode, *PENode;

//顶点表示
typedef struct _VNode
{
	char data;		//顶点信息
	ENode* first_edge; //指向的第一条弧
}VNode;

//邻接表
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

//连接到链表的尾部
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

	//初始化邻接表
	LGraph *pG = (LGraph*)malloc(sizeof(LGraph));
	if (pG == NULL)
		return NULL;
	memset(pG, 0, sizeof(LGraph));
	pG->vexnum = vexsLen;
	pG->edgenum = edgesNum;

	int i, p1, p2;
	char c1, c2;
	ENode *node1;
	//顶点初始化
	for (i = 0; i < pG->vexnum; ++i)
	{
		pG->vexs[i].data = vexs[i];
		pG->vexs[i].first_edge = NULL;
	}
	//边的初始化
	for (i = 0; i < pG->vexnum; ++i)
	{
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = get_position(*pG, c1);
		p2 = get_position(*pG, c2);

		node1 = (ENode*)malloc(sizeof(ENode));
		memset(node1, 0, sizeof(ENode));
		//无向图要连接两次
		node1->ivex = p2;
		if (pG->vexs[p1].first_edge == NULL)
			pG->vexs[p1].first_edge = node1;
		else
			link_last(pG->vexs[p1].first_edge, node1);
	}

	return pG;
}

//打印
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
拓扑排序
拓扑排序需要维护一个入度为0的顶点集合（可以是队列，栈，链表），每次从该集合中取出一个顶点，并将该点放入List中
紧接着循环遍历由该顶点引出的所有边，从图中移除这条边，同时获取该边的另外一个顶点，
如果该顶点的入度在减去本条边之后为0，那么也将这个顶点放到入度为0的集合中。
然后继续从集合中取出一个顶点
*/

void topological_sort(LGraph G)
{
	int i, j;
	int index = 0;
	int head = 0;
	int rear = 0;
	int *queue;		//辅助队列
	int *ins;		//入度数组
	char* tops;		//记录结果
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

	//每个顶点的入度数
	for (i = 0; i < num; ++i)
	{
		node = G.vexs[i].first_edge;
		while (node != NULL)
		{
			ins[node->ivex]++;		//该节点的入度数加一
			node = node->next_edeg;
		}
	}

	//将入度为0的顶点入队列
	for (i = 0; i < num; ++i)
	{
		if (ins[i] == 0)
			queue[rear++] = i;
	}

	while (head != rear)
	{
		j = queue[head++];
		tops[index++] = G.vexs[j].data;		//加入tops中
		node = G.vexs[j].first_edge;

		//邻接点 入度减1
		while (node != NULL)
		{

			ins[node->ivex]--;
			if (ins[node->ivex] == 0)
				queue[rear++] = node->ivex;

			node = node->next_edeg;
		}
	}
	//有环
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