#include <iostream>
#include <string>

using namespace std;

//大数加法
string sum(string s1, string s2)
{
	if (s1.length() < s2.length())
	{
		string tmp = s1;
		s1 = s2;
		s2 = tmp;
	}

	for (int i = s1.length() - 1, j = s2.length() - 1; i >= 0; i--, j--)
	{
		s1[i] = char(s1[i] + (j >= 0 ? s2[j] - '0' : 0));
		if (s1[i] - '0' >= 10)
		{
			s1[i] = char((s1[i] - '0') % 10 + '0');
			if (i)
				s1[i - 1]++;
			else
				s1 = '1' + s1;
		}
	}

	return s1;

}

//reference : http://bangbingsyb.blogspot.com/2014/11/leetcode-multiply-strings.html
string Multiply(string s1, string s2)
{
	if (s1.empty() || s2.empty())
		return "";

	int len1 = s1.length();
	int len2 = s2.length();
	string ret(len1+len2, '0');

	for (int j = 0; j < len2; ++j)
	{
		int carry = 0;
		int val = s2[j] - '0';
		for (int i = 0; i < len1; ++i)
		{
			carry += (s1[i] - '0')*val + ret[i + j] - '0';	//i位 * j位
			ret[i + j] = carry % 10 + '0';					//i+j 位
			carry /= 10;	//进位
		}
		if (carry != 0)
			ret[len1 + j] = carry + '0';		//最后的进位不为0，需要将carry转为字符
	}
	
	reverse(ret.begin(), ret.end());
	int count = 0;
	while (count < ret.size() - 1 && ret[count] == '0')
		count++;
	ret.erase(0, count);

	reverse(ret.begin(), ret.end());

	return ret;
}



int main()
{
	string s;
	cin >> s;

	string s1;
	while (cin >> s1)
	{
		if ((s1 == "0"))
			break;
		//s = sum(s, s1);
		s = Multiply(s, s1);
	}
	cout << s << endl;

	return 0;
}