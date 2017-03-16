/*
求含N个元素的集合的幂集。
如对于集合A={1,2,3},则A的幂集为
p(A)={{1,2,3},{1,2},{1,3},{1},{2,3},{2},{3},Φ}
幂集的每个元素是一个集合，它或是空集，或含集合A中的一个元素，
或含A中的两个元素，或者等于集合A。
反之，集合A中的每一个元素，它只有两种状态：
属于幂集的元素集，或不属于幂集元素集。则求幂集P（A）的元素的过程
可看成是依次对集合A中元素进行“取”或“舍”的过程，并且可以用一棵状态树
来表示。求幂集元素的过程即为先序遍历这棵状态树的过程。
*/

#include <iostream>
#include <vector>
using namespace std;

void PrintVector(vector<int> B)
{
	if (B.size() == 0)
	{
		cout << NULL << endl;
	}
	for (auto i : B)
		cout << i << " ";
	cout << endl;
}

void PowerSet(const vector<int> A, vector<int>& B, size_t k)
{
	if (k > A.size()-1)
	{
		PrintVector(B);
		return;
	}
	else
	{
		int tmp = A[k];
		B.push_back(tmp);
		PowerSet(A, B, k + 1);
		B.pop_back();
		PowerSet(A, B, k + 1);
		return;
	}
}

int main()
{
	vector<int> A{ 1, 2, 3 };
	vector<int> B;
	PowerSet(A, B, 0);

	return 0;
}
