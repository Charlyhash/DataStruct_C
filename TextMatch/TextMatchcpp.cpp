/*
�ַ���ƥ���㷨.
���ı�text�в���ģʽpattern�������Ϊ�ַ���ƥ�����⣬ͨ�������text�ǳ���
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
�����ַ���ƥ���㷨��
�㷨˼�룺ÿ�ζ����ַ���pattern�ĵ�һλ��ʼƥ�䣬ֱ��ƥ��ʧ�ܣ�Ȼ�����text����һ��λ��
ʱ�临�Ӷ�O((N)M+1)M)
*/

int BruteForceSearch(string txt, string patt) 
{
	if (patt == "")
		return 0;
	if (txt == "")
		return -1;

	int m = txt.size();
	int n = patt.size();
	if (m < n)
		return -1;

	for (int i = 0; i <= m - n; ++i)
	{
		int j;
		for (j = 0; j < n; ++j)
		{
			if (txt[i + j] != patt[j])
				break;
		}
		if (j == n)
			return i;
	}

	return -1;
}

void TEST_BruteForceSearch()
{
	string text = "aaabbccd";
	string pattern = "abbc";

	cout << BruteForceSearch(text, pattern) << endl;
}

/*
Rabin-Karp�㷨
���㷨�����Ӵ���hashֵ, ������text��ÿ������ΪM���Ӵ���hashֵ���������
hashֵ��ȣ���Ҫ�����������㷨���ж�һ�Ρ�
�ڼ���hashֵʱ����ǰ���Ӵ���hashֵ�����ϼ�����һ���Ӵ���hashֵ�����hash�㷨���ٶ�
d��ʾ�����ַ�����qΪһ��������
p=(d*p+patt[i])%q
t=(d*p+txt[i])%q
*/

int RabinKarpSearch(string txt, string patt, int q)
{

	if (patt == "")
		return 0;
	if (txt == "")
		return -1;

	int m = txt.size();  //length of txt
	int n = patt.size(); //length of patt
	if (m < n)
		return -1;
	const int d = 256; //256���ַ�
	int p = 0; //hash value for patt
	int t = 0; //hash value for txt
	int h = 1; // h = pow(d, M-1)%q
	for (int i = 0; i < n-1; ++i)
		h = (h * d) % q;

	for (int i = 0; i < n; ++i)
	{
		p = (d*p + patt[i]) % q;
		t = (d*t + txt[i]) % q;
	}

	for (int i = 0; i <= m-n; ++i)
	{
		int j;
		if (p == t)
		{
			for (j = 0; j < n; ++j)
				if (txt[i + j] != patt[j])
					break;
			if (j == n)
				return i;
		}

		//calculate hash value for next text
		if (i < m - n)
		{
			t = (d*(t - txt[i] * h) + txt[i + n]) % q;
			if (t < 0)
				t += q;
		}
	}

	return -1;
}

void TEST_RabinKarpSearch()
{
	string txt = "a";//"abde9f df ee d23 e99 a9";
	string patt = "a";//"e99";
	const int q = 101;
	cout << RabinKarpSearch(txt, patt, q) << endl;
}

/*
kmp�㷨��
����˼���ǣ�ƥ��ʧ�ܺ��ƶ�j-next[j]λ��next[]���壺��ǰ�ַ���֮ǰ���ַ����г���
��ͬ��ǰ׺�ͺ�׺����ΪGetNext������
*/
static void GetNext(string patt, vector<int>& next)
{
	next.resize(patt.size());
	next[0] = -1;
	int k = -1; //kΪǰ׺�ַ��ĵ�ǰλ��
	int j = 0; //jΪ��׺�ַ��ĵ�ǰλ��

	while (j < patt.size()-1)
	{
		if (k == -1 || patt[j] == patt[k])
		{
			++j;
			++k;
			next[j] = k;
		}
		else
			k = next[k];
	}
}
int KMPSearch(string txt, string patt, vector<int>& next)
{
	int txtLen = txt.size();
	int pattLen = patt.size();
	int i = 0; //i��txt��ǰ��λ��
	int j = 0; //j��patt��ǰ��λ��
	while (i < txtLen && j < pattLen)
	{
		if (j == -1 || txt[i] == patt[j])
		{
			++i;
			++j;
		}
		else
			j = next[j]; //����next[j]λ����ƥ��
	} 

	if (j == patt.size())
		return i - j;
	return -1;
}

void TEST_KMPSearch()
{
	string txt = "abacababc";
	string patt = "abab";
	vector<int> next;
	GetNext(patt, next);
	cout << KMPSearch(txt, patt, next) << endl;
}

//BM�㷨
//����BmBc���飬��ÿ���ַ���pattern�������ֵ�λ��
//ʵ���ƶ��ľ���ΪbmBc['v']-m+1+i
void PreBmBc(string pattern, vector<int>& bmBc)
{
	bmBc.resize(256);
	int m = pattern.size();
	for (int i = 0; i < 256; ++i)
		bmBc[i] = m;
	for (int i = 0; i < m - 1; ++i)
		bmBc[pattern[i]] = m - 1 - i;
}

//�����׺����
void suffix(string pattern, vector<int>& suff)
{
	int m = pattern.size();
	suff.resize(m);
	suff[m - 1] = m;
	int j, k;
	for (int i = m - 1; i >= 0; --i)
	{
		j = i;
		while (j >= 0 && pattern[j] == pattern[m - 1 - i + j])
			--j;
		suff[i] = i - j;
	}
}

//����bmGs
void PreBmGs(string pattern, vector<int>& bmGs)
{
	vector<int> suff;
	suffix(pattern, suff);
	int m = pattern.size();
	bmGs.resize(m);
	//ȫ��Ϊm������case3
	for (int i = 0; i < m; ++i)
		bmGs[i] = m;
	//case 2
	int j = 0;
	for (int i = m - 1; i >= 0; --i)
	{
		if (suff[i] == i + 1)
		{
			for (; j < m - 1 - i; ++j)
				if (bmGs[j] == m) //j��ʧ���λ��
					bmGs[j] = m - 1 - i;
		}
	}

	//case1
	for (int i = 0; i <= m - 2; ++i)
		bmGs[m - 1 - suff[i]] = m - 1 - i;
}

int BoyerMoore(string pattern, string text)
{
	vector<int> bmBc;
	vector<int> bmGs;
	PreBmBc(pattern, bmBc);
	PreBmGs(pattern, bmGs);
	int m = pattern.size();
	int n = text.size();
	int j = 0;
	int i;
	while (j <= n - m)
	{
		for (i = m - 1; i >= 0 && pattern[i] == text[i + j]; --i);
		if (i < 0)
			return j;
		j += max(bmBc[text[i + j]] - m + 1 + i, bmGs[i]);
	}

	return -1;
}

void TEST_BoyerMoore()
{
	string pattern("bcababab");
	string text("bcabcdababcabaabcbcabababacbacabeeacda");
	cout << BoyerMoore(pattern, text) << endl;
}

int Sunday(string text, string pattern)
{
	const int CHARNUM = 256; //�ַ����ĸ���
	int n = text.size();
	int m = pattern.size();
	vector<int> shift(CHARNUM, m + 1); //��ʼ��Ϊm-1
	for (int i = 0; i < m; ++i)
		shift[pattern[i]] = m - i;
	int i = 0; //textƥ���λ��
	int j; //patternƥ���λ��
	while (i <= n - m)
	{
		j = 0;
		while (text[i + j] == pattern[j] && j < m)
			++j;
		if (j == m) //ƥ��ɹ�
			return i;
		i += shift[text[i + m]]; //�۲�i+mλ�ַ���Ҫ�ƶ���λ��
	}

	return -1;
}

void TEST_Sunday()
{
	string pattern("bcababab");
	string text("bcabcdababcabaabcbcabababacbacabeeacda");
	cout << Sunday(text, pattern) << endl;
}

int main()
{
	//TEST_BruteForceSearch();
	//TEST_RabinKarpSearch();
	//TEST_KMPSearch();
	//TEST_BoyerMoore();
	TEST_Sunday();
	return 0;
} 