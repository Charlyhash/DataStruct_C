/*
kruakal算法：最小生成树
算法原理：选择n-1个权值最小的边，且不构成回路
先构造一个只含有n个顶点的森林，然后依次添加最小边，直到生成一颗树。
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define INF (~(0x1 << 31))
#define MAXN 30
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

//图的边的结构体
typedef struct _ENode
{
	int vexpos;		//该边顶点的位置
	int weight;		//权值
	struct _ENode* next;	//指向下一条边
}ENode;

//图的顶点的结构体
typedef struct _VNode
{
	char data;		//数据域
	ENode* first_edge;	//第一条边

}VNode;

//图的信息
typedef struct _LGraph
{
	VNode vexarr[MAXN];	//图顶点数组
	int vexnum;			//顶点数
	int edgnum;			//边数
}LGraph;

//边的结构体
typedef struct _EData
{
	char start;		//边的起点
	char end;		//边的终点
	char weight;	//边的权重
}EData;

//测试数据
static char gVexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
static EData gEdges[] =
{
	{ 'A', 'B', 12 },
	{ 'A', 'F', 16 },
	{ 'A', 'G', 14 },
	{ 'B', 'C', 10 },
	{ 'B', 'F',  7 },
	{ 'C', 'D',  3 },
	{ 'C', 'E',  5 },
	{ 'C', 'F',  6 },
	{ 'D', 'E',  4 },
	{ 'E', 'F',  2 },
	{ 'E', 'G',  8 },
	{ 'F', 'G',  9 },
};

//获取该元素在图中的位置
int getPos(LGraph G, char c)
{
	for (int i = 0; i < G.vexnum; ++i)
	{
		if (G.vexarr[i].data == c)
			return i;
	}

	return -1;
}


LGraph* createGraphEx()
{
	char start_ch, end_ch;
	int pos1, pos2;
	int weight;
	ENode *edgeNode1, *edgeNode2;
	LGraph* G = (LGraph*)malloc(sizeof(LGraph));
	if (G == NULL)
	{
		printf("Fail to malloc graph!\n");
		return NULL;
	}
	memset(G, 0, sizeof(LGraph));
	G->vexnum = LENGTH(gVexs);		//顶点数
	G->edgnum = LENGTH(gEdges);		//边数
	//初始化顶点
	for (int i = 0; i < G->vexnum; ++i)
	{
		G->vexarr[i].data = gVexs[i];
		G->vexarr[i].first_edge = NULL;
	}
	//初始化边
	for (int i = 0; i < G->edgnum; ++i)
	{
		start_ch = gEdges[i].start;
		end_ch = gEdges[i].end;
		weight = gEdges[i].weight;
		pos1 = getPos(*G, start_ch);
		pos2 = getPos(*G, end_ch);

		edgeNode1 = (ENode*)malloc(sizeof(ENode));
		edgeNode1->vexpos = pos2;
		edgeNode1->weight = weight;
		edgeNode1->next = NULL;

		if (G->vexarr[pos1].first_edge == NULL)
		{
			G->vexarr[pos1].first_edge = edgeNode1;
		}
		else
		{
			ENode* p = G->vexarr[pos1].first_edge;
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = edgeNode1;
		}

		edgeNode2 = (ENode*)malloc(sizeof(ENode));
		edgeNode2->vexpos = pos1;
		edgeNode2->weight = weight;
		edgeNode2->next = NULL;

		if (G->vexarr[pos2].first_edge == NULL)
		{
			G->vexarr[pos2].first_edge = edgeNode2;
		}
		else
		{
			ENode* p = G->vexarr[pos2].first_edge;
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = edgeNode2;
		}
	}
	
	return G;
}

//打印图，测试创建图是否成功
void print_graph(LGraph* G)
{
	ENode* eNode;
	for (int i = 0; i < G->vexnum; ++i)
	{
		printf("%c", G->vexarr[i].data);
		eNode = G->vexarr[i].first_edge;
		while (eNode != NULL)
		{
			printf(" %c", G->vexarr[eNode->vexpos].data);
			eNode = eNode->next;
		}
		printf("\n");
	}
}

//获取图中的边
EData* get_edges(LGraph G)
{
	ENode *eNode;
	EData *edges;
	int index = 0;

	edges = (EData*)malloc(G.edgnum*sizeof(EData));
	memset(edges, 0, G.edgnum*sizeof(EData));
	for (int i = 0; i < G.vexnum; ++i)
	{
		eNode = G.vexarr[i].first_edge;
		while (eNode != NULL)
		{
			if (eNode->vexpos > i) 
			{
				edges[index].start = G.vexarr[i].data;
				edges[index].end = G.vexarr[eNode->vexpos].data;
				edges[index].weight = eNode->weight;
				index++;
			}

			eNode = eNode->next;
		}
		
	}

	return edges;
}

//对边排序
void sort_edges(EData* edges, int elen)
{
	for (int i = 0; i < elen; ++i)
	{
		for (int j = i + 1; j < elen; ++j)
		{
			if (edges[i].weight > edges[j].weight)
			{
				EData tmp = edges[i];
				edges[i] = edges[j];
				edges[j] = tmp;
			}
		}
	}
}

//获取i的终点
int get_end(int vends[], int i)
{
	while (vends[i] != 0)
	{
		i = vends[i];
	}

	return i;
}



void Kruskal(LGraph G)
{
	int p1, p2;
	int m, n;
	int index = 0;
	int vends[MAXN] = {0};	//用于保存"已有最小生成树"中每个顶点在该最小树中的终点。
							//for ex:已经有一条边AB了，那么vends[A.pos] = B.pos
	EData rets[MAXN];		//结果数组，保存生成树的边
	EData *edges;			//图对应的所有边
	
	edges = get_edges(G);
	sort_edges(edges, G.edgnum);

	for (int i = 0; i < G.edgnum; ++i)
	{
		p1 = getPos(G, edges[i].start);
		p2 = getPos(G, edges[i].end);

		m = get_end(vends, p1);
		n = get_end(vends, p2);
		//m != n说明没有形成环
		if (m != n)
		{
			vends[m] = n;
			rets[index++] = edges[i];
		}
	}
	free(edges);

	int length = 0;
	for (int i = 0; i < index; ++i)
		length += rets[i].weight;
	printf("Kruskal = %d: ", length);
	for (int i = 0; i < index; ++i)
		printf("(%c, %c) ", rets[i].start, rets[i].end);
	printf("\n");
	
}

int getWeight(LGraph G, int start, int end)
{
	ENode *node;
	if (start == end)
		return 0;
	node = G.vexarr[start].first_edge;
	while (node != NULL)
	{
		if (end == node->vexpos)
			return node->weight;
		node = node->next;
	}

	return INF;
}

void prim(LGraph G, int start)
{
	int index = 0;		//prim最小树的索引
	char prims[MAXN];	//prim结果
	int weight[MAXN];	//顶点间权值，存储的是start-point的权值
						//到自己为0，到其他邻接为权重，不邻接为INF

	prims[index++] = G.vexarr[start].data;		//第一个值

	//初始化顶点的权值数组
	//将每个顶点的权值初始化为第start个顶点到该顶点的权值
	for (int i = 0; i < G.vexnum; ++i)
		weight[i] = getWeight(G, start, i);
	for (int i = 0; i < G.vexnum; ++i)
	{
		if (start == i)
			continue;

		int j = 0;
		int k = 0;
		int min = INF;
		//从 未被加入的顶点中，找到权值最小的顶点
		while (j < G.vexnum)
		{
			if (weight[j] != 0 && weight[j] < min)
			{
				min = weight[j];
				k = j;
			}
			++j;
		}
		//k为权值最小的顶点序号，将第k个顶点加入到最小生成树中
		prims[index++] = G.vexarr[k].data;
		//将k的权值设为0
		weight[k] = 0;
		//然后更新以k为顶点的权值
		int tmp;
		for (j = 0; j < G.vexnum; ++j)
		{
			tmp = getWeight(G, k, j);
			if (weight[j] != 0 && tmp < weight[j])
				weight[j] = tmp;
		}
	}
	//计算最小生成树的权重
	int sum = 0;
	int min;
	int m, n;
	int tmp;
	for (int i = 0; i < index; ++i)
	{
		min = INF;
		n = getPos(G, prims[i]);
		if (n == start)
			continue;
		for (int j = 0; j < i; ++j)
		{
			m = getPos(G, prims[j]);
			tmp = getWeight(G, m, n);
			if (tmp < min)
				min = tmp;
		}
		sum += min;
	}

	printf("PRIM(%c) = %d:", G.vexarr[start].data, sum);
	for (int i = 0; i < index; ++i)
	{
		printf("%c ", prims[i]);
	}
	printf("\n");
}

int main()
{
	LGraph *G = createGraphEx();
	print_graph(G);
	//Kruskal(*G);
	prim(*G, 0);
	return 0;
}