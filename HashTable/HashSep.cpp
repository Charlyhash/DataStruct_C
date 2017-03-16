#include <stdio.h>
#include <stdlib.h>
#include "HashSep.h"

#define  MinTableSize (10)

//typedef Position List;

////链表的结点
//struct ListNode
//{
//	ElementType data;
//	Position next;
//};
//
////散列的结构
//struct HashTbl
//{
//	int TableSize;
//	List* TheLists;
//};

//下一个质数
static int NextPrime(int N)
{
	static unsigned aPrimeList[] = { // 素数表  
		1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
		43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 113,
		193, 241, 257, 337, 353, 401, 433, 449, 577, 593, 641,
		673, 769, 881, 929, 977, 1009, 1153, 1201, 1217, 1249,
		1297,1361, 1409, 1489, 1553, 1601, 1697, 1777, 1873,
		1889, 2017, 2081, 2113, 2129, 2161, 2273, 2417, 2593,
		2609, 2657, 2689, 2753, 2801, 2833, 2897, 3041, 3089,
		3121, 3137, 3169, 3217, 3313, 3329, 3361, 3457, 3617,
		3697, 3761, 3793, 3889, 4001, 4049, 4129, 4177, 4241,
		4273, 4289, 4337, 4481, 4513, 4561, 4657, 4673, 4721,
		4801, 4817, 4993, 5009, 5153, 5233, 5281, 5297, 5393,
		5441, 5521, 5569, 5857, 5953, 6113, 6257, 6337, 6353,
		6449, 6481, 6529, 6577, 6673, 6689, 6737, 6833, 6961,
		6977, 7057, 7121, 7297, 7393, 7457, 7489, 7537, 7649,
		7681, 7793, 7841, 7873, 7937, 8017, 8081, 8161, 8209,
		8273, 8353, 8369, 8513, 8609, 8641, 8689, 8737, 8753,
		8849, 8929, 9041, 9137, 9281, 9377, 9473, 9521, 9601,
		9649, 9697, 9857
	};
	const int nListNum = sizeof(aPrimeList) / sizeof(unsigned);//计算素数表里元素的个数  
	
	for (unsigned i = 0; i < nListNum; ++i)
		if (aPrimeList[i] > N)
			return aPrimeList[i];

	return aPrimeList[nListNum - 1];
}

//hash函数
Index Hash(const int key, int TableSize)
{
	return key % TableSize;
}

//初始化
HashTable InitHashTable(int TableSize)
{
	HashTable H;
	if (TableSize < MinTableSize)
	{
		printf("Error! Table size too small!\n");
		return NULL;
	}
	//分配空间给散列表
	H = HashTable(malloc(sizeof(struct HashTbl)));
	if (H == NULL)
		printf("Error! Out of space!\n");
	H->TableSize = NextPrime(TableSize);
	//分配空间给每一个链表
	H->TheLists = (List*)(malloc(sizeof(List)*H->TableSize));
	if (H->TheLists == NULL)
		printf("Error! Out of space!\n");
	for (int i = 0; i < H->TableSize; ++i)
	{
		H->TheLists[i] = List(malloc(sizeof(struct ListNode)));
		if (H->TheLists[i] == NULL)
			printf("Error! Out of space!\n");
		else
			H->TheLists[i]->next = NULL;
	}

	return H;
}
//销毁
void DestroyTable(HashTable h)
{
	for (int i = 0; i < h->TableSize; ++i)
	{
		Position p = h->TheLists[i];
		Position tmp;
		while (p != NULL)
		{
			tmp = p->next;
			free(p);
			p = tmp;
		}
	}
	free(h->TheLists);
	free(h);
}

//查找key
Position Find(ElementType key, HashTable h)
{
	Position p;
	List l;
	l = h->TheLists[Hash(key, h->TableSize)];
	p = l->next;
	while (p != NULL && p->data != key)
		p = p->next;

	return p;
}
//插入key
void Insert(ElementType key, HashTable h)
{
	Position p, newCell;
	List l;
	p = Find(key, h);
	if (p == NULL)
	{
		newCell = Position(malloc(sizeof(struct ListNode)));
		if (newCell == NULL)
			printf("Error! Out of space!\n");
		else
		{
			//插入到首部
			l = h->TheLists[Hash(key, h->TableSize)];
			newCell->next = l->next;
			newCell->data = key;
			l->next = newCell;
		}
	}
}

ElementType Retriever(Position p)
{
	return p->data;
}