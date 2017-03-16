//邻接表无向图的表示
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

//读取一个字符
static char read_char()
{
	char ch;
	do
	{
		ch = getchar();
	} while (!isLetter(ch));

	return ch;
}

LGraph* create_graph()
{
	int v, e;
	int i;
	char c1, c2;
	int p1, p2;
	ENode* node1, *node2;
	LGraph* pG;

	printf("input vertex number: ");
	scanf("%d", &v);
	printf("input edge number: ");
	scanf("%d", &e);
	if (v < 1 || e < 1 || (e >(v*(v - 1))))
	{
		printf("input error: invalid parameters.!\n");
		return NULL;
	}

	if ((pG = (LGraph*)malloc(sizeof(LGraph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(LGraph));

	pG->vexnum = v;
	pG->edgenum = e;
	for (i = 0; i < pG->vexnum; ++i)
	{
		printf("vertex(%d): ", i);
		pG->vexs[i].data = read_char();
		pG->vexs[i].first_edge = NULL;
	}

	//初始化邻接表
	for (i = 0; i < pG->vexnum; ++i)
	{
		printf("edge(%d): ", i);
		c1 = read_char();
		c2 = read_char();

		p1 = get_position(*pG, c1);
		p2 = get_position(*pG, c2);

		node1 = (ENode*)malloc(sizeof(ENode));
		if (node1 == NULL)
			return NULL;
		memset(node1, 0, sizeof(ENode));
		node1->ivex = p2;
		if (pG->vexs[p1].first_edge == NULL)
			pG->vexs[p1].first_edge = node1;
		else
			link_last(pG->vexs[p1].first_edge, node1);

		node2 = (ENode*)malloc(sizeof(ENode));
		if (node2 == NULL)
			return NULL;
		memset(node2, 0, sizeof(ENode));
		node2->ivex = p1;
		if (pG->vexs[p2].first_edge == NULL)
			pG->vexs[p2].first_edge = node2;
		else
			link_last(pG->vexs[p2].first_edge, node2);
	}

	return pG;
}


LGraph* create_example_graph()
{
	char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	char edges[][2] = {
		{ 'A', 'C' },
		{ 'A', 'D' },
		{ 'A', 'F' },
		{ 'B', 'C' },
		{ 'C', 'D' },
		{ 'E', 'G' },
		{ 'F', 'G' } };
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
	ENode *node1, *node2;
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

		node2 = (ENode*)malloc(sizeof(ENode));
		memset(node2, 0, sizeof(ENode));
		node2->ivex = p1;
		if (pG->vexs[p2].first_edge == NULL)
			pG->vexs[p2].first_edge = node2;
		else
			link_last(pG->vexs[p2].first_edge, node2);
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
深度优先递归实现
*/
static void DFS(LGraph G, int i, int *visited)
{
	int w;
	ENode *node;
	visited[i] = 1;
	printf("%c->", G.vexs[i].data);
	node = G.vexs[i].first_edge;
	while (node != NULL)
	{
		if (!visited[node->ivex])
			DFS(G, node->ivex, visited);
		node = node->next_edeg;
	}
}

//DFS
void DFSTraverse(LGraph G)
{
	int i;
	int visited[MAX];

	for (i = 0; i < G.vexnum; ++i)
	{
		visited[i] = 0;
	}

	printf("DFS:\n");
	for (i = 0; i < G.vexnum; ++i)
	{
		if (!visited[i])
			DFS(G, i, visited);
	}
	printf("\n");
}

//广度优先BFS
void BFS(LGraph G)
{
	int head = 0;
	int rear = 0;
	int queue[MAX];
	int visited[MAX];
	int i, j, k;
	ENode* node;

	for (i = 0; i < G.vexnum; ++i)
		visited[i] = 0;

	printf("BFS:\n");
	for (i = 0; i < G.vexnum; ++i)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			printf("%c->", G.vexs[i].data);
			queue[rear++] = i;		//访问完了入队列
		}
		while (head!= rear)
		{
			j = queue[head++];
			node = G.vexs[j].first_edge;
			while (node != NULL)
			{
				k = node->ivex;
				if (!visited[k])
				{
					visited[k] = 1;
					printf("%c->", G.vexs[i].data);
					queue[rear++] = k;
				}
				node = node->next_edeg;
			}
		}
	}

	printf("\n");
}

int main()
{
	LGraph* pG;
	pG = create_example_graph();
	//pG = create_graph();

	print_lgraph(*pG);
	DFSTraverse(*pG);

	return 0;
}