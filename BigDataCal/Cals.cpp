/*
大数运算的实现
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

//加法， s1与s2均为正数 poj1503
//做竖式运算，一位一位相加
string Add(string s1, string s2)
{
	if (s1.size() < s2.size())
	{
		string tmp = s2;
		s2 = s1;
		s1 = s2;
	}

	int i = s1.size(); int j = s2.size();
	for (; i >= 0; --i, --j)
	{
		s1[i] += (j >= 0 ? s2[j] - '0' : 0);

		if (s1[i] - '0' >= 10)
		{
			s1[i] = s1[i] - 10;
			if (i != 0)
				s1[i - 1]++;
			else
				s1 = '1' + s1;
		}
	}

	return s1;
}

//乘法，s1与s2 poj
//让s1的每一位与s2相乘，然后再调用大数加法
string Multiply(string s1, string s2)
{
	vector<string> vect;
	for (int i = s1.size() - 1; i >= 0; --i)
	{
		string s = s2;
		int carry = 0; int curSum;
		for (int j = s2.size() - 1; j >= 0; --j)
		{
			curSum = static_cast<int>(s1[i] - '0') * static_cast<int>(s2[j] - '0') + carry;
			if (curSum >= 10)
				s[j] = curSum % 10 + '0';
			else
				s[j] = curSum + '0';
			carry = curSum / 10;
		}
		if (carry)
			s = static_cast<char>(carry + '0') + s;

		for (int k = s1.size() - 1 - i; k > 0; --k)
			s.push_back('0');

		vect.push_back(s);
	}
	string ret = "0";
	for (int i = 0; i < vect.size(); ++i)
		ret = Add(vect[i], ret);

	return ret;
}

string Multiply2(string s1, string s2)
{
	if (s1 == "0" || s2 == "0")
		return "0";
	size_t len1 = s1.size();
	size_t len2 = s2.size();
	string res(len1+len2+1, '0');

	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());

	for (size_t i = 0; i < len1; ++i)
	{
		for (size_t j = 0; j < len2; ++j)
		{
			int tmp = static_cast<int>(s1[i] - '0') * static_cast<int>(s2[j] - '0');
			res[i + j + 1] = res[i + j + 1] + (res[i + j] - '0' + tmp)  / 10;	//进位
			res[i + j] = (res[i + j] - '0' + tmp) % 10 + '0';					//i * j的值在i+j位置
			
		}
	}

	//翻转res
	reverse(res.begin(), res.end());
	int i;
	for (i = 0; i < res.size(); ++i)
		if (res[i] != '0')
			break;
	
	return res.substr(i);
}

void TEST_ADD()
{
	string s1, s2;
	cin >> s1;
	while (cin >> s2)
	{
		if (s2 == "0")
			break;
		s1 = Add(s1, s2);
	}

	cout << s1 << endl;
}

void TEST_MULTIPLY()
{
	string s1, s2;
	cin >> s1 >> s2;
	cout << Multiply2(s1, s2) << endl;
}

int main()
{

	TEST_MULTIPLY();

	return 0;
}