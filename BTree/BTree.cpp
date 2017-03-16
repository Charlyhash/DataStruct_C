#include "BTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

void DiskWrite(BTNode* node)
{
	printf("write node data to the disk.\n");
}

void DiskRead(BTNode** node)
{
	printf("read node data from the disk.\n");
}

//create a b-tree use data array,the lenght of data array is len
void BTreeCreate(BTree* tree, const int* data, int len)
{
	assert(tree);
	printf("create b-tree using the key: \n");
	for (int i = 0; i < len; ++i)
	{
		printf("%c ", data[i]);
		BTreeInsert(tree, data[i]);

		BTreePrint(*tree);
		printf("\n");

	}
	printf("\n");
	
	printf("the b-tree is : \n ");
	BTreePrint(*tree);
}

//destory a b-tree
void BTreeDestory(BTree* tree)
{
	BTNode* node = *tree;
	if (node)
	{
		for (int i = 0; i <= node->keyNum; ++i)
			BTreeDestory(&node->child[i]);

		free(node);
	}

	*tree = NULL;
}

//split b-tree node if it's a full node
void BTreeSplitChild(BTNode* parent, int index, BTNode* node)
{
	assert(parent && node);

	BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
	if (!newNode)
	{
		printf("B-tree split error! Out of memory!\n");
		return;
	}

	//new node to store the second part of node node
	newNode->isLeaf = node->isLeaf;
	newNode->keyNum = BTreeT - 1;
	
	//copy the second part of node
	for (int i = 0; i < newNode->keyNum; ++i)
	{
		newNode->key[i] = node->key[BTreeT + i];
		node->key[BTreeT + i] = 0;
	}
	//node is not a leaf , copy the child
	if (!node->isLeaf)
	{
		for (int i = 0; i < BTreeT; ++i)
		{
			newNode->child[i] = node->child[BTreeT + i];
			node->child[BTreeT + i] = NULL;
		}
	}
	//the key number has changed
	node->keyNum = BTreeT - 1;

	//adjust the parent node
	for (int i = parent->keyNum; i > index; --i)
		parent->child[i + 1] = parent->child[i];
	parent->child[index + 1] = newNode;

	for (int i = parent->keyNum - 1; i >= index; --i)
		parent->key[i + 1] = parent->key[i];

	parent->key[index] = node->key[BTreeT - 1];
	++parent->keyNum;

	node->key[BTreeT - 1] = 0;
	node->child[BTreeT] = NULL;

	//write to the disk
	DiskWrite(parent);
	DiskWrite(newNode);
	DiskWrite(node);
}

//insert to b-tree if the root is not full
void BTreeInsertNotFull(BTNode* node, int key)
{
	assert(node);

	//insert to the leaf
	if (node->isLeaf)
	{
		int i = node->keyNum - 1;
		while (i >= 0 && key < node->key[i])
		{
			node->key[i + 1] = node->key[i];
			--i;
		}
		node->key[i + 1] = key;
		++node->keyNum;
		
		DiskWrite(node);
	}
	else //not a leaf
	{
		//find which child node to insert
		int i = node->keyNum - 1;
		while (i >= 0 && key < node->key[i])
		{
			--i;
		}
		++i;

		DiskRead(&node->child[i]);
		if (node->child[i]->keyNum == BTreeN)
		{
			BTreeSplitChild(node, i, node->child[i]);
			//which child node to insert, i or i+1
			if (key > node->key[i])
				++i;
		}

		BTreeInsertNotFull(node->child[i], key);
	}
}

//insert a key to a b-tree
void BTreeInsert(BTree* tree, int key)
{
	BTNode* node;
	BTNode* root = *tree;

	//empty tree
	if (root == NULL)
	{
		root = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!root)
		{
			printf("ERROR: out of memory!\n");
			return;
		}
		root->isLeaf = true;
		root->keyNum = 1;
		root->key[0] = key;

		*tree = root;

		return;
	}

	//the node is full, split and insert
	if (root->keyNum == BTreeN)
	{
		node = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!node)
		{
			printf("ERROR: out of memory!\n");
			return;
		}
		*tree = node;
		node->isLeaf = false;
		node->keyNum = 0;
		node->child[0] = root;

		BTreeSplitChild(node, 0, root);

		BTreeInsertNotFull(node, key);
	}
	else //the tree node is not full, insert anyway.
		BTreeInsertNotFull(root, key);
}

//merge two child.
//two child keyNum = BTreeT - 1
//把node中索引为index+1的孩子合并到index,并将tree中缩影为index的key下降到该节点中，调整key和指针
void BTreeMergeChild(BTree* tree, BTNode* node, int index)
{
	assert(tree && node && index >= 0 && index < node->keyNum);

	int key = node->key[index];
	BTNode* preChild = node->child[index];
	BTNode* nextChild = node->child[index + 1];
	assert(preChild && preChild->keyNum == BTreeT - 1 && nextChild && nextChild->keyNum == BTreeT - 1);

	//preChild，node中index位置的key，nextchild合并
	//原来preChild中有key=BTreeT-1, child=BTree
	//注意序号是从0开始的
	preChild->key[BTreeT-1] = key; // add parent key[index] to the child，第BTreeT个关键字
	preChild->child[BTreeT] = nextChild->child[0]; // add child to the child，第BTree+1个节点
	//merge nextChild to preChild
	for (int i = 0; i < nextChild->keyNum; ++i)
	{
		preChild->key[BTreeT + i] = nextChild->key[i];
		preChild->child[BTreeT + 1 + i] = nextChild->child[i+1];
	}
	preChild->keyNum = 2 * BTreeT - 1;

	//调整node:在node中移除key并调整子节点
	for (int i = index; i < node->keyNum -1; ++i)
	{
		node->key[i] = node->key[i + 1];
		node->child[i + 1] = node->child[i + 2];
	}
	node->key[node->keyNum - 1] = 0;
	node->child[node->keyNum] = NULL;
	--node->keyNum;
	
	//如果合并之后，根节点变为空的情况：注意只有根节点可能是1个节点，才会出现借了一个节点后就
	//变为空的情况，其他的是不会出现这种情况的。
	if (node->keyNum == 0)
	{
		if (*tree == node)
			*tree = preChild;
		free(node);
		node = NULL;
	}

	//释放nextChild
	free(nextChild);
}

//remove a key in a b-tree
void BTreeRemove(BTree* tree, int key)
{
	BTNode* root = *tree;
	BTNode* node = root;
	BTNode *preChild, *nextChild, *child;

	int preKey, nextKey;

	if (!root)
	{
		printf("Fail to remove %c, not in the tree.\n", key);
		return;
	}

	int index = 0;
	while (index < node->keyNum && key > node->key[index])
		++index;

	//find the key.
	if (index < node->keyNum && node->key[index] == key)
	{
		//this node is a leaf, delete the key anyway
		if (node->isLeaf)
		{
			for (int i = index; i < node->keyNum; ++i)
			{
				node->key[i] = node->key[i + 1];
				node->child[i + 1] = node->child[i + 2];
			}
			--node->keyNum;
			if (node->keyNum == 0)
			{
				assert(node == *tree);
				free(node);
				*tree = NULL;
			}

			return;
		}
		//if the child has at least BTreeT keys
		else if (node->child[index]->keyNum >= BTreeT)
		{
			//we find the key, the use the child key replacing it and delete the child key recursively
			preChild = node->child[index];
			preKey = preChild->key[preChild->keyNum - 1];
			node->key[index] = preKey;
			BTreeRemove(&preChild, preKey);//delete the preKey recursively
		}
		else if (node->child[index + 1]->keyNum >= BTreeT)
		{
			nextChild = node->child[index + 1];
			nextKey = nextChild->key[0];
			node->key[index] = nextKey;
			BTreeRemove(&nextChild, nextKey);
		}
		//preChild and next child has only BTreeT-1 keys,then merge two child 
		//and delete the key in previous child
		else if (node->child[index]->keyNum == BTreeT - 1 && node->child[index + 1]->keyNum == BTreeT - 1)
		{
			preChild = node->child[index];
			BTreeMergeChild(tree, node, index);
			BTreeRemove(&preChild, key);
		}
	}
	//can't find the key in the node.we find in the child
	//key < node->key[index], so the key is in the child node->child[index]
	else
	{
		child = node->child[index];
		if (!child)
		{
			printf("Fail to delete %c for it's not in the tree!\n", key);
			return;
		}
		if (child->keyNum == BTreeT - 1)
		{
			//deal with the previous child and next child
			preChild = NULL;
			nextChild = NULL;

			if (index - 1 >= 0)
				preChild = node->child[index - 1];
			if (index + 1 <= node->keyNum)
				nextChild = node->child[index + 1];

			//if the child's siblings has at least BTreeT keys
			//then updown one key from sibling to the 
			if (preChild && preChild->keyNum >= BTreeT || nextChild && nextChild->keyNum >= BTreeT)
			{
				if (preChild && preChild->keyNum >= BTreeT)
				{
					for (int j = child->keyNum; j > 0; --j)
					{
						child->key[j] = child->key[j - 1];
						child->child[j + 1] = child->child[j];
					}
					child->child[1] = child->child[0];
					child->child[0] = preChild->child[preChild->keyNum];
					child->key[0] = node->key[index - 1];
					++child->keyNum;
					node->key[index - 1] = preChild->key[preChild->keyNum - 1];
					--preChild->keyNum;
				}
				else
				{ 
					child->key[child->keyNum] = node->key[index];
					child->child[child->keyNum + 1] = nextChild->child[0];
					++child->keyNum;

					node->key[index] = nextChild->key[0];

					for (int j = 0; j < nextChild->keyNum - 1; ++j)
					{
						nextChild->key[j] = nextChild->key[j + 1];
						nextChild->child[j] = nextChild->child[j + 1];
					}
					--nextChild->keyNum;
				}

			}
			//the child's siblings only has BTreeT-1 keys
			//merge child and it's sibling
			else if((!preChild || (preChild && preChild->keyNum == BTreeT-1)) && 
				(!nextChild || (nextChild && nextChild->keyNum == BTreeT - 1)))
			{
				if (preChild && preChild->keyNum == BTreeT - 1)
				{
					BTreeMergeChild(tree, node, index - 1);
					child = preChild;
				}
				else if (nextChild && nextChild->keyNum == BTreeT - 1)
				{
					BTreeMergeChild(tree, node, index);
				}
			}
		}

		BTreeRemove(&child, key);
	}
}

//print tree
void BTreePrint(BTree tree, int her)
{
	BTNode* node = tree;
	if (node)
	{
		//print level
		printf("level %d, %d nodes : ", her, node->keyNum);
		for (int i = 0; i < node->keyNum; ++i)
			printf("%c ", node->key[i]);

		printf("\n");

		//print child
		++her;
		for (int i = 0; i <= node->keyNum; ++i)
		{
			if (node->child[i])
				BTreePrint(node->child[i], her);
		}
	}
	else
		printf("The tree is empty!\n");
}

//find key int the tree
//return the node and *pos is the pos int the node
BTNode* BTreeSearch(const BTree tree, int key, int* pos)
{
	if (tree == NULL)
		return NULL;

	int i = 0;
	//search in the node tree
	while (i < tree->keyNum && key > tree->key[i])
		++i;

	//find the key
	if (i < tree->keyNum && key == tree->key[i])
	{
		if (pos)
			*pos = i;
		return tree;
	}

	//if the tree is leaf node ,then return NULL
	if (tree->isLeaf)
		return NULL;

	//key is not in the tree node, find in the child
	//tree->key[i-1] < key < key < tree->key[i]
	//find in the ith child of the tree node

	//first read from the disk
	DiskRead(&tree->child[i]);
	//the find the key
	return BTreeSearch(tree->child[i], key, pos);
}