/*
字符串匹配算法.
在文本text中查找模式pattern的问题称为字符串匹配问题，通常情况下text非常大。
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
朴素字符串匹配算法。
算法思想：每次都从字符串pattern的第一位开始匹配，直到匹配失败，然后继续text的下一个位置
时间复杂度O((N)M+1)M)
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
Rabin-Karp算法
该算法计算子串的hash值, 并计算text中每个长度为M的子串的hash值，如果两个
hash值相等，需要继续用朴素算法再判断一次。
在计算hash值时，在前面子串的hash值基础上计算下一个子串的hash值，提高hash算法的速度
d表示所有字符集，q为一个素数。
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
	const int d = 256; //256个字符
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
kmp算法：
基本思想是：匹配失败后移动j-next[j]位。next[]含义：当前字符串之前的字符串中长度
相同的前缀和后缀。求法为GetNext函数。
*/
static void GetNext(string patt, vector<int>& next)
{
	next.resize(patt.size());
	next[0] = -1;
	int k = -1; //k为前缀字符的当前位置
	int j = 0; //j为后缀字符的当前位置

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
	int i = 0; //i是txt当前的位置
	int j = 0; //j是patt当前的位置
	while (i < txtLen && j < pattLen)
	{
		if (j == -1 || txt[i] == patt[j])
		{
			++i;
			++j;
		}
		else
			j = next[j]; //跳过next[j]位继续匹配
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

//BM算法
//计算BmBc数组，即每个字符在pattern中最后出现的位置
//实际移动的距离为bmBc['v']-m+1+i
void PreBmBc(string pattern, vector<int>& bmBc)
{
	bmBc.resize(256);
	int m = pattern.size();
	for (int i = 0; i < 256; ++i)
		bmBc[i] = m;
	for (int i = 0; i < m - 1; ++i)
		bmBc[pattern[i]] = m - 1 - i;
}

//计算后缀数组
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

//计算bmGs
void PreBmGs(string pattern, vector<int>& bmGs)
{
	vector<int> suff;
	suffix(pattern, suff);
	int m = pattern.size();
	bmGs.resize(m);
	//全部为m，包含case3
	for (int i = 0; i < m; ++i)
		bmGs[i] = m;
	//case 2
	int j = 0;
	for (int i = m - 1; i >= 0; --i)
	{
		if (suff[i] == i + 1)
		{
			for (; j < m - 1 - i; ++j)
				if (bmGs[j] == m) //j是失配的位置
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
	const int CHARNUM = 256; //字符集的个数
	int n = text.size();
	int m = pattern.size();
	vector<int> shift(CHARNUM, m + 1); //初始化为m-1
	for (int i = 0; i < m; ++i)
		shift[pattern[i]] = m - i;
	int i = 0; //text匹配的位置
	int j; //pattern匹配的位置
	while (i <= n - m)
	{
		j = 0;
		while (text[i + j] == pattern[j] && j < m)
			++j;
		if (j == m) //匹配成功
			return i;
		i += shift[text[i + m]]; //观察i+m位字符需要移动的位数
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