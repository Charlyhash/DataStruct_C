#ifndef __BTREE_H__
#define __BTREE_H__

//树的最小度数 BTreeT
//每个节点中关键字的最大数目：BTreeN = 2*BTreeT - 1
#define BTreeT 2
#define BTreeN (BTreeT*2-1)

struct BTNode
{
	int keyNum;							//the key numbers in a node
	int key[BTreeN];					//array store the value key[0...keynum-1]
	struct BTNode* child[BTreeT*2];		//children of the tree
	bool isLeaf;						//is leaf in the tree
};

typedef BTNode* BTree;

//create a b-tree
void BTreeCreate(BTree* tree, const int* data, int len);

//destory a b-tree
void BTreeDestory(BTree* tree);

//insert a key to a b-tree
void BTreeInsert(BTree* tree, int key);

//remove a key in a b-tree
void BTreeRemove(BTree* tree, int key);

//print tree
void BTreePrint(BTree tree, int hight = 1);

//find key int the tree
//return the node and *pos is the pos int the node
BTNode* BTreeSearch(const BTree tree, int key, int* pos);


#endif