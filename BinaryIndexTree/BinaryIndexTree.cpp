/*
poj2299-树状数组+离散化

题目大意：给定一个输出，求出逆序数

解题思路：树状数组

*/

#include <cstdio>
#include <vector>
#include <algorithm>

#pragma warning(disable:4996)

using namespace std;

const int MAXN = (500000 + 5);

struct node {
	int val;
	int index;
}a[MAXN];

int c[MAXN], aa[MAXN];
int n;

bool cmp(const node& a, const node&b) {
	return a.val < b.val;
};


int lowbit(int x) {
	return x & (-x);
}

//更新
void update(int x) {
	while (x <= n) {
		c[x] += 1;
		x += lowbit(x);
	}
}

//求和
int sum(int k) {
	int ret = 0;
	while (k > 0) {
		ret += c[k];
		k -= lowbit(k);
	}

	return ret;
}

int main() {
	freopen("poj2299.txt", "r", stdin);
	//处理每一组输入
	while (scanf("%d", &n) != EOF && n != 0) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].val);
			a[i].index = i;
		}
		/*
		离散化：比如原来是这样的
		val:	9 1 0 5 4
		index:	1 2 3 4 5 

		sort之后
		val:	0 1 4 5 9
		index:	3 2 5 4 1

		aa数组：
		a[i]:	1 2 3 4 5
		val:	5 2 1 4 3

		求逆序数：每次插入到树状数组中，然后计算逆序数(比它小的数)。
		具体过程是这样：
		(1)i=1,aa[i]=5,插入5，sum[aa[i]]=1，逆序数为i-sum[5]
		(2)i=2,aa[i]=2,插入2，sum[2]=1.如果2后面没有比2小的数，那么这些数应该已经比2先插入，也就是1已经先插入到
		1的位置，sum[2]=2;但是这里sum[2]=1,说明后面有i-sum[aa[i]]个数没有插入。故逆序数求法为：i-sum[aa[i]]
		(3)后面的情况以此类推
		*/
		sort(a + 1, a + n + 1, cmp);//排序
		for (int i = 1; i <= n; ++i)//离散化
			aa[a[i].index] = i;
		for (int i = 1; i <= n; ++i)//初始化树状数组
			c[i] = 0;
		long long ret = 0;
		for (int i = 1; i <= n; ++i) {
			update(aa[i]);				//更新
			ret += (i - sum(aa[i]));		//逆序数
		}
		printf("%lld\n", ret);
	}
}