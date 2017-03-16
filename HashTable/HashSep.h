#ifndef _HASHSEP_H_
//����������ʵ�֣��ο������ݽṹ���㷨����-c����������

typedef int ElementType;
typedef unsigned int Index;

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef Position List;

//����Ľ��
struct ListNode
{
	ElementType data;
	Position next;
};

//ɢ�еĽṹ
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
