/*
动态规划第一讲--缓存与动态规划
1、例子：有一段楼梯有10级台阶，规定每一步只能跨一级或两级，要登上第10级台阶有几种不同的走法?
分析：F(n)=F(n-1)+F(n-2)
*/


#include <iostream>
#include <vector>
#include <string>

using namespace std;

//递归解决
int solution1(int n)
{
	if (n == 1 || n == 2)
		return n;
	if (n > 2)
		return solution1(n - 1) + solution1(n - 2);

	return -1;
}

//一种改进
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

//去掉递归
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