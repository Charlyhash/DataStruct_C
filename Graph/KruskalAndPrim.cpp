/*
kruakal�㷨����С������
�㷨ԭ��ѡ��n-1��Ȩֵ��С�ıߣ��Ҳ����ɻ�·
�ȹ���һ��ֻ����n�������ɭ�֣�Ȼ�����������С�ߣ�ֱ������һ������
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define INF (~(0x1 << 31))
#define MAXN 30
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

//ͼ�ıߵĽṹ��
typedef struct _ENode
{
	int vexpos;		//�ñ߶����λ��
	int weight;		//Ȩֵ
	struct _ENode* next;	//ָ����һ����
}ENode;

//ͼ�Ķ���Ľṹ��
typedef struct _VNode
{
	char data;		//������
	ENode* first_edge;	//��һ����

}VNode;

//ͼ����Ϣ
typedef struct _LGraph
{
	VNode vexarr[MAXN];	//ͼ��������
	int vexnum;			//������
	int edgnum;			//����
}LGraph;

//�ߵĽṹ��
typedef struct _EData
{
	char start;		//�ߵ����
	char end;		//�ߵ��յ�
	char weight;	//�ߵ�Ȩ��
}EData;

//��������
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

//��ȡ��Ԫ����ͼ�е�λ��
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
	G->vexnum = LENGTH(gVexs);		//������
	G->edgnum = LENGTH(gEdges);		//����
	//��ʼ������
	for (int i = 0; i < G->vexnum; ++i)
	{
		G->vexarr[i].data = gVexs[i];
		G->vexarr[i].first_edge = NULL;
	}
	//��ʼ����
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

//��ӡͼ�����Դ���ͼ�Ƿ�ɹ�
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

//��ȡͼ�еı�
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

//�Ա�����
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

//��ȡi���յ�
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
	int vends[MAXN] = {0};	//���ڱ���"������С������"��ÿ�������ڸ���С���е��յ㡣
							//for ex:�Ѿ���һ����AB�ˣ���ôvends[A.pos] = B.pos
	EData rets[MAXN];		//������飬�����������ı�
	EData *edges;			//ͼ��Ӧ�����б�
	
	edges = get_edges(G);
	sort_edges(edges, G.edgnum);

	for (int i = 0; i < G.edgnum; ++i)
	{
		p1 = getPos(G, edges[i].start);
		p2 = getPos(G, edges[i].end);

		m = get_end(vends, p1);
		n = get_end(vends, p2);
		//m != n˵��û���γɻ�
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
	int index = 0;		//prim��С��������
	char prims[MAXN];	//prim���
	int weight[MAXN];	//�����Ȩֵ���洢����start-point��Ȩֵ
						//���Լ�Ϊ0���������ڽ�ΪȨ�أ����ڽ�ΪINF

	prims[index++] = G.vexarr[start].data;		//��һ��ֵ

	//��ʼ�������Ȩֵ����
	//��ÿ�������Ȩֵ��ʼ��Ϊ��start�����㵽�ö����Ȩֵ
	for (int i = 0; i < G.vexnum; ++i)
		weight[i] = getWeight(G, start, i);
	for (int i = 0; i < G.vexnum; ++i)
	{
		if (start == i)
			continue;

		int j = 0;
		int k = 0;
		int min = INF;
		//�� δ������Ķ����У��ҵ�Ȩֵ��С�Ķ���
		while (j < G.vexnum)
		{
			if (weight[j] != 0 && weight[j] < min)
			{
				min = weight[j];
				k = j;
			}
			++j;
		}
		//kΪȨֵ��С�Ķ�����ţ�����k��������뵽��С��������
		prims[index++] = G.vexarr[k].data;
		//��k��Ȩֵ��Ϊ0
		weight[k] = 0;
		//Ȼ�������kΪ�����Ȩֵ
		int tmp;
		for (j = 0; j < G.vexnum; ++j)
		{
			tmp = getWeight(G, k, j);
			if (weight[j] != 0 && tmp < weight[j])
				weight[j] = tmp;
		}
	}
	//������С��������Ȩ��
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