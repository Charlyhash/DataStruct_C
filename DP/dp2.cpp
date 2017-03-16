/*

所以一个问题是该用递推、贪心、搜索还是动态规划，完全是由这个问题本身阶段间状态的转移方式决定的！
每个阶段只有一个状态->递推；
每个阶段的最优状态都是由上一个阶段的最优状态得到的->贪心；
每个阶段的最优状态是由之前所有阶段的状态的组合得到的->搜索；
每个阶段的最优状态可以从之前某个阶段的某个或某些状态直接得到而不管之前这个状态是如何得到的->动态规划。

01背包问题
有n个重量和价值分别为vector<int> weight, vector<int> value的物品；背包最大负重为W，求能用背包装下的物品的最大价值？
输入：n =4
weight=2, 1, 3, 2
value =3, 2, 4, 2
W=5
输出=7
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> weight{2, 1, 3, 2};
vector<int> value{3,2,4,2};

//递归与分治
//从i...n个物品中，选择重量不大于j的物品的最大价值
int solution1(int i, int j)
{
	int res;
	if (i == weight.size())
		res = 0;
	else if (j < weight[i])
		res = solution1(i + 1,  j);
	else
		res = max(solution1(i + 1, j), solution1(i + 1,j - weight[i]) + value[i]);

	return res;
}


int main()
{
	cout << solution1(0,5) << endl;

}