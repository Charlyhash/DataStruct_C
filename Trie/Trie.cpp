#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>

#pragma warning(disable:4996)//vs

//Trie node
typedef struct TrieNode
{
	int count;					//统计单词前缀出现的次数
	struct TrieNode* next[26];	//指向子树的指针
	bool exist;					//该节点是否存在
}TrieNode, *Trie;

//创建一个节点
TrieNode* CreateTrieNode()
{
	TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
	assert(node);
	node->count = 0;
	node->exist = false;
	memset(node->next, 0, sizeof(node->next));

	return node;
}

//插入到Trie中
void TrieInsert(Trie root, char* word)
{
	TrieNode* node = root;
	char* p = word;
	int id = 0;
	//遍历每一个char
	while (*p)
	{
		id = *p - 'a'; // find the char position in the child
		if (node->next[id] == NULL) //不存在*p这条路径
		{
			node->next[id] = CreateTrieNode();
		}
		node = node->next[id];//指针向下移动.这里必须明白：每一个节点代表的是从根节点到此节点路径上所有字符组成的单词
		node->count++;//前缀加1
		++p;
	}
	printf("insert %s ok!\n", word);
	node->exist = true;
}

//查找，和插入类似,返回以此字符为前缀的单词的个数
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
	char str[100][20];//100个单词，每个单词有20个字符
	int n = 0;
	while (~scanf("%s", str[n]))
	{
		TrieInsert(root, str[n++]);
	}

	for (int i = 0; i < 10; ++i)
	{
		TrieSearch(root, str[i]);
	}

	//无法检测的情况
	char str1[20] = "carbin";
	TrieSearch(root, str1);

	return 0;
}
/*

read.txt内容如下：
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