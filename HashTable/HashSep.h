#ifndef _HASHSEP_H_
//分离链表法的实现，参考《数据结构与算法分析-c语言描述》

typedef int ElementType;
typedef unsigned int Index;

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef Position List;

//链表的结点
struct ListNode
{
	ElementType data;
	Position next;
};

//散列的结构
struct HashTbl
{
	int TableSize;
	List* TheLists;
};

Index Hash(const int key, int TableSize);
HashTable InitHashTable(int TableSize);
void DestroyTable(HashTable h);
Position Find(ElementType key, HashTable h);
void Insert(ElementType key, HashTable h);
ElementType Retriever(Position p);

#endif
