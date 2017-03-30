/*
��ǽ�����������.
������������L=<a1,a2,��,an>��n����ͬ��ʵ�������У�L�ĵ���������������
һ��������Lin=<aK1,ak2,��,akm>������k1<k2<��<km��aK1<ak2<��<akm������
���mֵ��

���˼·��DP(״̬��״̬ת�Ʒ���)
״̬�� dp[i]��ʾ���һ��Ԫ��Ϊai������������С�
״̬ת�Ʒ��̣��ҵ�aiǰ��С������Ԫ��aj����ôdp[i] = max{dp[j] + 1, 1}��
Ҳ���Ǵ�i��ʼ��ǰ�ң����ĳ��Ԫ��a[j] < a[i],��ô��Ԫ��a[j]��β��LIS��
����a[i]Ҳһ����LIS.���״̬ת�Ʒ���Ϊ��
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

	//�ⷨ2��ά��һ������v����nums[0]���뵽�����У��������ÿһ��nums[i],���
	//nums[i]>v.back(),����push�������У������ҵ���һ������������λ�ã���
	//��λ�õ������滻Ϊnums[i],��󷵻�v�ĳ��ȣ�������ַ����ĳ���
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

