/*
��N��Ԫ�صļ��ϵ��ݼ���
����ڼ���A={1,2,3},��A���ݼ�Ϊ
p(A)={{1,2,3},{1,2},{1,3},{1},{2,3},{2},{3},��}
�ݼ���ÿ��Ԫ����һ�����ϣ������ǿռ����򺬼���A�е�һ��Ԫ�أ�
��A�е�����Ԫ�أ����ߵ��ڼ���A��
��֮������A�е�ÿһ��Ԫ�أ���ֻ������״̬��
�����ݼ���Ԫ�ؼ����������ݼ�Ԫ�ؼ��������ݼ�P��A����Ԫ�صĹ���
�ɿ��������ζԼ���A��Ԫ�ؽ��С�ȡ�����ᡱ�Ĺ��̣����ҿ�����һ��״̬��
����ʾ�����ݼ�Ԫ�صĹ��̼�Ϊ����������״̬���Ĺ��̡�
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
