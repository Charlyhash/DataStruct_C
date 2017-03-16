#include "SkipList.h"

/*
创建节点
*/
Node* create_node(int level, keyType key, valueType val)
{
	Node *p = (Node*)malloc(sizeof(Node) + level*sizeof(Node*));
	if (!p)
	{
		printf("Fail to Create node!\n");
		return NULL;
	}
	p->key = key;
	p->value = val;

	return p;
}

//创建skiplist
skip_list* create_sl()
{
	skip_list *sl = (skip_list*)malloc(sizeof(skip_list));
	if (sl == NULL)
	{
		printf("Fail to create skip list!\n");
		return NULL;
	}

	sl->level = 0;		//初始的层数为0
	Node *head = create_node(SKIPLIST_MAXLEVEL - 1, 0, 0);
	if (head == NULL)
	{
		printf("Fail to create skip list!\n");
		return NULL;
	}
	sl->head = head;
	for (int i = 0; i < SKIPLIST_MAXLEVEL; ++i)
	{
		head->next[i] = NULL;
	}
	srand(time(0));
	
	return sl;
}

//产生随机的层数
int randomLevel()
{
	int level = 1;
	while (rand() % 2)
	{
		level++;
		if (level > SKIPLIST_MAXLEVEL)
			break;
	}

	level = (level > SKIPLIST_MAXLEVEL) ? SKIPLIST_MAXLEVEL : level;

	return level;
}

//插入节点
int insert(skip_list* sl, keyType key, valueType val)
{
	Node *update[SKIPLIST_MAXLEVEL];		//需要更新的节点
	Node *q = NULL;							
	Node *p = sl->head;
	int i = sl->level - 1;

	//1、从最高层往下查找需要插入的位置，并更新update
	//即把降层节点指针保存在update数组
	for (; i >= 0; --i)
	{
		while ((q = p->next[i])&&(q->key < key))
		{
			p = q;
		} 
		update[i] = p;
	}
	if (q && q->key == key)		//如果已经存在了
	{
		q->value = val;
		return 1;
	}
	//2、产生随机的level
	int level = randomLevel();
	//新的层数比跳表的层数大
	if (level > sl->level)
	{
		for (i = sl->level; i < level; ++i)
		{
			update[i] = sl->head;		//这个节点要放在头结点的后面
		}
		sl->level = level;
	}

	//3、新建节点
	q = create_node(level, key, val);
	if (!q)
		return 0;
	for (i = level - 1; i >= 0; --i)
	{
		q->next[i] = update[i]->next[i];
		update[i]->next[i] = q;
	}

	return 1;
}

//删除节点
int erase(skip_list* sl, keyType key)
{
	Node *update[SKIPLIST_MAXLEVEL];
	Node *q = NULL;
	Node *p = sl->head;
	int i = sl->level - 1;

	for (; i >= 0; --i)
	{
		while ((q = p->next[i]) && (q->key < key))
		{
			p = q;
		}
		update[i] = p;
	}

	//判断
	if (!q || (q && q->key != key))
		return 0;
	//逐层删除
	for (i = sl->level - 1; i >= 0; --i)
	{
		if (update[i]->next[i] == q)		//删除节点
		{
			update[i]->next[i] = q->next[i];
			//如果删除的是最高层的节点,则level减1
			if (sl->head->next[i] == NULL)
				sl->level--;
		}
	}
	free(q);
	q = NULL;
	
	return 1;
}

//查找
valueType* search(skip_list* sl, keyType key)
{
	Node *q = NULL;
	Node *p = sl->head;
	int i = sl->level - 1;

	for (; i >= 0; --i)
	{
		while ((q = p->next[i]) && (q->key < key))
		{
			p = q;
		}
		if (q && key == q->key)
			return &(q->value);
	}

	return NULL;
}

//打印
void print_sl(skip_list *sl)
{
	Node *q;
	int i = sl->level - 1;
	for (; i >= 0; --i)
	{
		q = sl->head->next[i];
		printf("level %d:\n", i + 1);
		while (q)
		{
			printf("key:%d val:%d\t", q->key, q->value);
			q = q->next[i];
		}

		printf("\n");
	}
}

//释放
void free_sl(skip_list* sl)
{
	if (!sl)
		return;
	Node *q = sl->head;
	Node *next;
	while (q)
	{
		next = q->next[0];
		free(q);
		q = next;
	}
	free(sl);
}