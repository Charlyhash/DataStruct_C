//邻接矩阵有向图的表示

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define  scanf scanf_s

#define  MAX 100
#define isLetter(a) (((a >= 'a') && (a <= 'z')) || ((a >= 'A') && (a <= 'Z')))
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

typedef struct _graph
{
	char vexs[MAX];		//顶点数组
	int vexnum;			//顶点数
	int edgenum;		//边数
	int matrix[MAX][MAX];	//邻接矩阵
}Graph, *PGraph;

//获取ch在matix的位置
static int get_position(Graph g, char ch)
{
	int i;
	for (i = 0; i < g.vexnum; ++i)
		if (g.vexs[i] == ch)
			return i;
	return -1;
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

Graph* create_graph()
{
	char c1, c2;
	int v, e;
	int i, p1, p2;
	Graph* pG;

	printf("input vertex number: ");
	scanf("%d", &v);
	printf("input edge number: ");
	scanf("%d", &e);
	if (v < 1 || e < 1 || (e >(v*(v - 1))/2))
	{
		printf("input error: vertex number or edge number\n");
		return NULL;
	}
	if ((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));

	pG->vexnum = v;
	pG->edgenum = e;
	//初始化顶点
	for (i = 0; i < pG->vexnum; ++i)
	{
		printf("vertex(%d): ", i);
		pG->vexs[i] = read_char();
	}
	//初始化边
	for (i = 0; i < pG->edgenum; ++i)
	{
		printf("edge(%d): ", i);
		c1 = read_char();
		c2 = read_char();

		p1 = get_position(*pG, c1);
		p2 = get_position(*pG, c2);
		if (p1 == -1 || p2 == -1)
		{
			printf("input error: invalied edge!\n");
			free(pG);
			return NULL;
		}

		pG->matrix[p1][p2] = 1;
	}

	return pG;
}

//用自己提供的矩阵创建图
Graph* create_example_graph()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'B' },
		{ 'B', 'C' },
		{ 'B', 'E' },
		{ 'B', 'F' },
		{ 'C', 'E' },
		{ 'D', 'C' },
		{ 'E', 'B' },
		{ 'E', 'D' },
		{ 'F', 'G' } };
	int vexsLen = LENGTH(vexs);
	int edgesNum = LENGTH(edges);

	Graph *pG = (Graph*)malloc(sizeof(Graph));
	if (pG == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));
	pG->vexnum = vexsLen;
	pG->edgenum = edgesNum;
	for (int i = 0; i < pG->vexnum; ++i)
	{
		pG->vexs[i] = vexs[i];
	}

	int p1, p2;
	for (int i = 0; i < edgesNum; ++i)
	{
		p1 = get_position(*pG, edges[i][0]);
		p2 = get_position(*pG, edges[i][1]);
		pG->matrix[p1][p2] = 1;
	}

	return pG;

}

//返回第一个邻接顶点的索引
static int first_vertex(Graph G, int v)
{
	int i;
	if (v < 0 || v > (G.vexnum - 1))
		return -1;
	for (i = 0; i < G.vexnum; ++i)
		if (G.matrix[v][i] == 1)
			return i;

	return -1;
}

//返回顶点v相对于顶点w的下一个邻接顶点的索引
static int next_vertex(Graph G, int v, int w)
{
	int i;
	if (v < 0 || v > (G.vexnum - 1) || w < 0 || w > (G.vexnum - 1))
		return -1;

	for (i = w+1; i < G.vexnum; ++i)
	{
		if (G.matrix[v][i] == 1)
			return i;
	}

	return -1;
}

//深度优先
static void DFS(Graph G, int i, int* visited)
{
	int w;
	visited[i] = 1;
	printf("%c->", G.vexs[i]);
	for (w = first_vertex(G, i); w >= 0; w = next_vertex(G, i, w))
		if (!visited[i])
			DFS(G, w, visited);
}

//深度优先遍历
void DFSTraverse(Graph G)
{
	int i;
	int visited[MAX];
	for (i = 0; i < G.vexnum; ++i)
		visited[i] = 0;
	printf("DFS:\n");
	for (i = 0; i < G.vexnum; ++i)
	{
		if (!visited[i])
			DFS(G, i, visited);
	}
	printf("\n");
}

//BFS
void BFS(Graph G)
{
	int head = 0;
	int rear = 0;
	int queue[MAX];
	int visited[MAX];
	int i, j, k;

	for (i = 0; i < G.vexnum; ++i)
		visited[i] = 0;

	printf("BFS:\n");
	for (i = 0; i < G.vexnum; ++i)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			printf("%c->", G.vexs[i]);
			queue[rear++] = i;		//访问了要如队列
		}
		while (head != rear)		//邻接点没有访问完
		{
			j = queue[head++];		//出队列，开始访问邻接点
			for (k = first_vertex(G, j); k >= 0; k = next_vertex(G, j, k))
			{
				if (!visited[k])
				{
					visited[k] = 1;
					printf("%c->", G.vexs[k]);
					queue[rear++] = k;		//访问之后就入队列
				}
			}
		}
	}

	printf("\n");
}


//打印
void print_graph(Graph G)
{
	int i, j;
	printf("Matrix Graph:\n");
	for (i = 0; i < G.vexnum; ++i)
	{
		for (j = 0; j < G.vexnum; ++j)
			printf("%d ", G.matrix[i][j]);
		printf("\n");
	}
}

int main()
{
	Graph* pG;
	//pG = create_graph();
	pG = create_example_graph();
	print_graph(*pG);
	DFSTraverse(*pG);
	BFS(*pG);

	return 0;
}

//输出
//input vertex number : 7
//input edge number : 7
//vertex(0) : A
//vertex(1) : B
//vertex(2) : C
//vertex(3) : D
//vertex(4) : E
//vertex(5) : F
//vertex(6) : G
//edge(0) : A C
//edge(1) : A D
//edge(2) : A F
//edge(3) : B C
//edge(4) : C D
//edge(5) : E G
//edge(6) : F G
//Matrix Graph :
//0 0 1 1 0 1 0
//0 0 1 0 0 0 0
//0 0 0 1 0 0 0
//0 0 0 0 0 0 0
//0 0 0 0 0 0 1
//0 0 0 0 0 0 1
//0 0 0 0 0 0 0
