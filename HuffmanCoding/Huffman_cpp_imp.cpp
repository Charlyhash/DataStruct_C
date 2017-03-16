/*
* 哈夫曼树的C++实现
*/

//#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

#pragma warning(disable:4996) 

using namespace std;

//节点的定义
struct Node {
	char c;  //要编码的字符
	int fre; //字符出现的频率
	Node* left;  //左子树
	Node* right;

	Node(char _c, int f, Node* l = NULL, Node* r = NULL) :
		c(_c), fre(f), left(l), right(r) {}

	//重载<运算符
	bool operator<(const Node& node) const {
		return fre > node.fre;
	}
	

};

void initNode(priority_queue<Node> &q, int nodeNum) {
	char c;
	int fre;
	for (int i = 0; i < nodeNum; ++i) {
		cin >> c >> fre;
		Node node(c, fre);
		q.push(node);//加入优先队列
	}
}

void showNode(priority_queue<Node> &q) {
	while (!q.empty())
	{
		Node node = q.top();
		cout << node.c << "'s fre:" << node.fre << endl;
	}
}

void huffmanTree(priority_queue<Node> &q) {
	while (q.size() != 1) {
		Node* left = new Node(q.top());
		q.pop();
		Node* right = new Node(q.top());
		q.pop();
		Node node('R', left->fre + right->fre, left, right);
		q.push(node);
	}
}


void huffmanCode(Node* root, string& prefix, map<char, string>& res) {
	string pre = prefix;

	if (root->left == NULL)
		return;

	//处理左子树
	prefix += "0";
	if (root->left->left == NULL) 
		res[root->left->c] = prefix;	
	else
		huffmanCode(root->left, prefix, res);//递归


	//处理右子树
	prefix = pre;
	prefix += "1";
	if (root->right->right == NULL) 
		res[root->right->c] = prefix;
	else
		huffmanCode(root->right, prefix, res);
}

void PrintResult(map<char, string> res) {
	for (auto iter : res)
	{
		cout << iter.first << ":" << iter.second << endl;
	}
}

int main()
{
	freopen("input_1.txt", "r", stdin);
	priority_queue <Node> q;

	int nodeNum;
	cin >> nodeNum;
	initNode(q, nodeNum);
	huffmanTree(q);
	Node root = q.top();
	string prefix = "";
	map<char, string> result;
	huffmanCode(&root, prefix, result);

	PrintResult(result);

	return 0;

}

/*
input_1.txt
5
a 3
b 4
c 1
d 7
e 5

输出：
a:011
b:00
c:010
d:11
e:10
*/

