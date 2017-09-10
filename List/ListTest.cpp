#include "List.h"

void TEST_CREATE()
{
	vector<int> data{ 1,2,3,4,5 };
	List* l = createList(data);
	vector<int> v;
	traverseList(l, v);
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

void TEST_INSERT()
{
	vector<int> data{ 1,2,3,4,5 };
	List* l = createList(data);
	for (int i = 6; i < 10; ++i)
		l = insertList(l, i);
	vector<int> v;
	traverseList(l, v);
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

void TEST_DELETE()
{
	vector<int> data{ 1,2,3,4,5 };
	List* l = createList(data);
	vector<int> v{ 1,3,5,2,4 };
	for (auto val : v)
	{
		l = deleteList(l, val);
		vector<int> rst;
		traverseList(l, rst);
		for (auto i : rst)
			cout << i << " ";
		cout << endl;
	}
}

int main()
{
	//TEST_CREATE();
	//TEST_INSERT();
	TEST_DELETE();
}