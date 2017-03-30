/*
最长非降子序列问题.
问题描述：设L=<a1,a2,…,an>是n个不同的实数的序列，L的递增子序列是这样
一个子序列Lin=<aK1,ak2,…,akm>，其中k1<k2<…<km且aK1<ak2<…<akm。求最
大的m值。

求解思路：DP(状态和状态转移方程)
状态： dp[i]表示最后一个元素为ai的最长递增子序列。
状态转移方程：找到ai前面小于它的元素aj，那么dp[i] = max{dp[j] + 1, 1}。
也就是从i开始往前找，如果某个元素a[j] < a[i],那么以元素a[j]结尾的LIS再
加上a[i]也一定是LIS.因此状态转移方程为：
dp[i] = max(1,max(dp[j] + 1))
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int lengthOfLIS1(vector<int>& nums) 
	{
		if (nums.size() == 0)
			return 0;
		vector<int> dp(nums.size(), 1);
		int res = 1;
		for (int i = 0; i < nums.size(); ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (nums[j] < nums[i])
					dp[i] = max(dp[i], dp[j] + 1);
			}
			if (dp[i] > res)
				res = dp[i];
		}

		return res;
	}

	//解法2：维护一个数组v，将nums[0]加入到数组中，如果对于每一个nums[i],如果
	//nums[i]>v.back(),则将其push到数组中；否则找到第一个比这个数大的位置，将
	//该位置的数字替换为nums[i],最后返回v的长度，就是最长字符串的长度
	int lengthOfLIS(vector<int>& nums)
	{
		if (nums.size() == 0)
			return 0;
		vector<int> v;
		v.push_back(nums[0]);
		for (int i = 0; i < nums.size(); ++i)
		{
			if (nums[i] > v.back())
				v.push_back(nums[i]);
			else
				*lower_bound(v.begin(), v.end(), nums[i]) = nums[i];
		}

		return v.size();
	}
};

void test()
{
	vector<int> nums{ 10, 9, 2, 5, 3, 7, 101, 18 };
	Solution sol;
	cout << sol.lengthOfLIS(nums) << endl;
}

int main()
{
	test();

	return 0;
}

