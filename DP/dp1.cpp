/*
��̬�滮��һ��--�����붯̬�滮
1�����ӣ���һ��¥����10��̨�ף��涨ÿһ��ֻ�ܿ�һ����������Ҫ���ϵ�10��̨���м��ֲ�ͬ���߷�?
������F(n)=F(n-1)+F(n-2)
*/


#include <iostream>
#include <vector>
#include <string>

using namespace std;

//�ݹ���
int solution1(int n)
{
	if (n == 1 || n == 2)
		return n;
	if (n > 2)
		return solution1(n - 1) + solution1(n - 2);

	return -1;
}

//һ�ָĽ�
vector<int> dp(11, 0);
int solution2(int n)
{
	if (n == 1 || n == 2)
		return n;
	if (dp[n] != 0)
		return dp[n];
	dp[n] = solution2(n - 1) + solution2(n - 2);

	return dp[n];
}

//ȥ���ݹ�
int solution3(int n)
{
	vector<int> dp(n + 1, 0);
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; ++i)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
		cout << dp[i] << " ";
	}
	cout << endl;
	return dp[n];
}


int main()
{
	//cout << solution1(10) << endl;
	//cout << solution2(10) << endl;
	cout << solution3(10) << endl;

	return 0;
}