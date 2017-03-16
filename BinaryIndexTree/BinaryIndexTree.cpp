/*
poj2299-��״����+��ɢ��

��Ŀ���⣺����һ����������������

����˼·����״����

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

//����
void update(int x) {
	while (x <= n) {
		c[x] += 1;
		x += lowbit(x);
	}
}

//���
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
	//����ÿһ������
	while (scanf("%d", &n) != EOF && n != 0) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].val);
			a[i].index = i;
		}
		/*
		��ɢ��������ԭ����������
		val:	9 1 0 5 4
		index:	1 2 3 4 5 

		sort֮��
		val:	0 1 4 5 9
		index:	3 2 5 4 1

		aa���飺
		a[i]:	1 2 3 4 5
		val:	5 2 1 4 3

		����������ÿ�β��뵽��״�����У�Ȼ�����������(����С����)��
		���������������
		(1)i=1,aa[i]=5,����5��sum[aa[i]]=1��������Ϊi-sum[5]
		(2)i=2,aa[i]=2,����2��sum[2]=1.���2����û�б�2С��������ô��Щ��Ӧ���Ѿ���2�Ȳ��룬Ҳ����1�Ѿ��Ȳ��뵽
		1��λ�ã�sum[2]=2;��������sum[2]=1,˵��������i-sum[aa[i]]����û�в��롣����������Ϊ��i-sum[aa[i]]
		(3)���������Դ�����
		*/
		sort(a + 1, a + n + 1, cmp);//����
		for (int i = 1; i <= n; ++i)//��ɢ��
			aa[a[i].index] = i;
		for (int i = 1; i <= n; ++i)//��ʼ����״����
			c[i] = 0;
		long long ret = 0;
		for (int i = 1; i <= n; ++i) {
			update(aa[i]);				//����
			ret += (i - sum(aa[i]));		//������
		}
		printf("%lld\n", ret);
	}
}