#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>

#pragma warning(disable:4996)//vs

//Trie node
typedef struct TrieNode
{
	int count;					//ͳ�Ƶ���ǰ׺���ֵĴ���
	struct TrieNode* next[26];	//ָ��������ָ��
	bool exist;					//�ýڵ��Ƿ����
}TrieNode, *Trie;

//����һ���ڵ�
TrieNode* CreateTrieNode()
{
	TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
	assert(node);
	node->count = 0;
	node->exist = false;
	memset(node->next, 0, sizeof(node->next));

	return node;
}

//���뵽Trie��
void TrieInsert(Trie root, char* word)
{
	TrieNode* node = root;
	char* p = word;
	int id = 0;
	//����ÿһ��char
	while (*p)
	{
		id = *p - 'a'; // find the char position in the child
		if (node->next[id] == NULL) //������*p����·��
		{
			node->next[id] = CreateTrieNode();
		}
		node = node->next[id];//ָ�������ƶ�.����������ף�ÿһ���ڵ������ǴӸ��ڵ㵽�˽ڵ�·���������ַ���ɵĵ���
		node->count++;//ǰ׺��1
		++p;
	}
	printf("insert %s ok!\n", word);
	node->exist = true;
}

//���ң��Ͳ�������,�����Դ��ַ�Ϊǰ׺�ĵ��ʵĸ���
int TrieSearch(Trie root, char* word)
{
	TrieNode* node = root;
	char* p = word;
	int id;
	while (*p)
	{
		id = *p - 'a';
		node = node->next[id];
		if (node == NULL)
		{
			printf("not find the word:%s\n", word);
			return 0;			
		}
		++p;
	}
	printf("find the word:%s\n", word);
	return node->count;
}

int main()
{
	freopen("read.txt", "r", stdin);
	Trie root = CreateTrieNode();//init
	char str[100][20];//100�����ʣ�ÿ��������20���ַ�
	int n = 0;
	while (~scanf("%s", str[n]))
	{
		TrieInsert(root, str[n++]);
	}

	for (int i = 0; i < 10; ++i)
	{
		TrieSearch(root, str[i]);
	}

	//�޷��������
	char str1[20] = "carbin";
	TrieSearch(root, str1);

	return 0;
}
/*

read.txt�������£�
carbohydrate
cart
carburetor
caramel
caribou
carbonic
cartilage
carbon
carriage
carton
car
carbonate

output:
insert carbohydrate ok!
insert cart ok!
insert carburetor ok!
insert caramel ok!
insert caribou ok!
insert carbonic ok!
insert cartilage ok!
insert carbon ok!
insert carriage ok!
insert carton ok!
insert car ok!
insert carbonate ok!
find the word:carbohydrate
find the word:cart
find the word:carburetor
find the word:caramel
find the word:caribou
find the word:carbonic
find the word:cartilage
find the word:carbon
find the word:carriage
find the word:carton
not find the word:carbin
*/