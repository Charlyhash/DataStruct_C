/*
poj1015 ��̬�滮
reference:http://blog.csdn.net/lyy289065406/article/details/6671105
��Ŀ���⣺��n������ѡȡm������������ţ�Ҫ����ط���d���ͱ緽��p������m���˵��ܷ�֮��ľ���ֵ��С��
���������ͬ����ôѡ�����֮�����ġ���������Ҫ���m���ˣ�Ȼ������緽��ֵ�Ϳط���ֵ��
��Ŀ��������̬�滮(�ؼ���ȷ��״̬��״̬ת��)
1<=n<=200, 1<=m<=20.d, p�޷���һάdp���.��������dp[i][j]��ʾ����ʲô״̬�أ�
Ҫѡ��m����,1<=m<=20,��ômӦ����dp���档i��ʾѡ��i���˵������
����j��ѡȡ��Ҫ����״̬ת�ƣ�dp[i][j]ͬdp[i-1][x]����һ���˺��Ϊdp[i][j]
����ѡ��jΪ��ǰ��pd���ôdp[i-1][j+p-d]�Ϳ��Եõ�״̬ת�Ʒ��̡�
��ˣ�dp[i][j]��ʾ����ѡ��i���˺�pd����j������� pd����� �ĺ͡�
��dp[i-1][x]��Ϊdp[i][j]������Ϊ������ĳ����ѡ��i,��dp[i-1][x]��û�б�ѡ�ϣ�
��x+d-p = j;ѡ��dp[i-1][x]+d+p��ֵ�����Ǹ�(i)����ô����dp[i-1][x]�ټ���i,�ͱ�ɷ���dp[i][j]
������м䣬������Ҫ��һ��������ѡ����Щ�˼�¼��������path[i][j]��dp[i][j]�����ѡ���Ǹ��˵���ż�¼������
��ô�����ڶ����˵ı��Ϊpath[i-1][j-V[path[i][j]]].��������ҵ������ս�ķ����ı�ز�k����ô��path[m][k]����
����һ��һ������������б�ѡ�еĺ�ѡ�ˡ�
��ʼ������dp[0][0]=0,������Ϊ-1.

С���ɣ�����pd�Ĳ����Ϊ���������ǰ���������m*20,j�ķ�Χ�ʹ�-400-400�����0-800��


������
��������
4 2
1 2
2 3
4 1
6 2
0 0
�������
Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3
*/

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
const int MAXN = 801;
const int MAXM = 21;
int n;
int m;
int dp[MAXM][MAXN];		//dp[j][k]:ȡj����ѡ�ˣ�ʹ���ز�Ϊk�����÷����У���غ����ı�غ�
int path[MAXM][MAXN];	//��¼��ѡ���ĺ�ѡ�˵ı��

//���ݣ�ȷ��dp[j][k]�����Ƿ���ѡ�����ѡ��i
bool select(int j, int k, int i, int* v)
{
	//����ÿһ��j����û��ѡ��i,˵��ǰ���j��û��ѡ��i
	while (j > 0 && path[j][k] != i)		//path[j][k]��¼����dp[i][j]�����ѡ���Ǹ��˵����
	{
		k -= v[path[j][k]];					//path[j-1][k-v(path[j][k])]Ϊ�����ڶ����˵����
		j--;
	}

	return j == 0;
}

int main()
{
	int time = 1;
	while (cin >> n >> m && n)
	{
		//Initial
		int j, k, i;
		int *p = new int[n + 1];	//ÿ���˵Ŀط�ֵ
		int *d = new int[n + 1];	//ÿ���˵ı緽ֵ
		int *s = new int[n + 1];	//ÿ���˵ı�غ�
		int *v = new int[n + 1];	//ÿ���˵ı�ز�

		memset(dp, -1, sizeof(dp));		//��ʼ��Ϊ-1
		memset(path, 0, sizeof(path));	//·����Ϊ0

		//input
		for (i = 1; i <= n; ++i)
		{
			cin >> p[i] >> d[i];

			s[i] = p[i] + d[i];		//��غ�
			v[i] = p[i] - d[i];		//��ز�
		}
		int fix = m * 20;		//������ֵ��

		//dp
		dp[0][fix] = 0;			//������dp[0][fix]����������dp[0][0];
		for (j = 1; j <= m; ++j)
		{
			for (k = 0; k <= 2 * fix; ++k)		//����ÿһ��d-p
			{
				if (dp[j - 1][k] >= 0)			//��ʼ��Ϊ-1�����ѡ�������ô>=0��û��ѡ�������Ҫ��
				{
					for (i = 1; i <= n;++i)
					{
						if (dp[j][k + v[i]] < dp[j - 1][k] + s[i])		//����ѡ��������ı�غ�dp[j - 1][k] + s[i]	���ȵ�ǰ�ı�غʹ���滻
						{
							if (select(j - 1, k, i, v))					//���i����û��ѡ��
							{
								dp[j][k + v[i]] = dp[j - 1][k] + s[i];	//��������
								path[j][k + v[i]] = i;
							}
						}
					}
				}
			}
		}

		//output
		for (k = 0; k <= fix; ++k)
		{
			if (dp[m][fix-k] >=0 || dp[m][fix+k] >= 0)	//�м��Ϊ��С�ı�ز���м�����������
				break;
		}
		int div = dp[m][fix - k] > dp[m][fix + k] ? fix - k : fix + k;	//��С��ز�
		//��ز�div-fix(��Ϊ��������������fix),��غ�dp[m][div]
		//div-fxi = p - d
		//dp[m][div]= p + d;
		//p = (dp[m][div] + div - fix) / 2;d = (dp[m][div] - div + fix) / 2

		cout << "Jury #" << time++ << endl;
		cout << "Best jury has value ";
		cout << (dp[m][div] + div - fix) / 2 << " for prosecution and value ";
		cout << (dp[m][div] - div + fix) / 2 << " for defence:" << endl;

		int* id = new int[m];
		for (i = 0, j = m, k = div; i < m; i++)
		{
			id[i] = path[j][k];						//�ӵ�i��һ·���ҵ���һ��
			k -= v[id[i]];
			j--;
		}
		sort(id, id + m);   //���������ѡ�˱��  
		for (i = 0; i < m; i++)
			cout << ' ' << id[i];
		cout << endl ;

		/*Relax*/

		delete p;
		delete d;
		delete s;
		delete v;
		delete id;
	}
	return 0;
}