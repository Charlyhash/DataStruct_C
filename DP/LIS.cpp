/*
求最长非降子序列的长度
问题描述：设L=<a1,a2,…,an>是n个不同的实数的序列，
L的递增子序列是这样一个子序列Lin=<aK1,ak2,…,akm>，
其中k1<k2<…<km且aK1<ak2<…<akm。求最大的m值。
求解思路：DP(状态和状态转移方程)
d(i)表示最后一个元素为ai的最长递增子序列。找到ai前面小于它的元素aj，
那么，d(i)=d(j)+1.
*/

#include <iostream>
using namespace std;

int lis(int *A, int n)
{
	int *d = new int[n];
	int len = 1;
	for (int i = 0; i < n; ++i)
	{
		d[i] = 1;
		for (int j = 0; j < i; ++j)
		{
			if (A[j] <= A[i] && d[j] + 1 > d[i])
				d[i] = d[j] + 1;
		}
		if (d[i] > len)
		{
			len = d[i];
		}
	}
	delete[] d;
	return len;
}

int main()
{
	int A[] = {5, 3, 4, 8, 6, 7};
	cout << lis(A, 6) << endl;

	return 0;
}