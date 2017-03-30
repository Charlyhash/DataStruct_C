#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
string s1, s2;

//比较s1,s2的绝对值的大小
bool les(string str1, string str2)
{
	int l1 = str1.size();
	int l2 = str2.size();
	if (l1 < l2)
		return true;
	if (l1 > l2)
		return false;
	for (int i = 0; i < l1; ++i)
	{
		if (str1[i] > str2[i])
			return false;
		else
			return true;
	}

	return false;
}

string add(string s1, string s2)
{
	int l1 = s1.size();
	int l2 = s2.size();
	if (l1 < l2)
		return add(s2, s1);

	int i, j, curNum, carry = 0;
	for (i = 0, j = 0; i < l1; ++i, ++j)
	{
		curNum = s1[i] - '0' + (j >= l2 ? 0:s2[j] - '0') + carry;
		carry = curNum / 10;
		s1[i] = curNum % 10 + '0';
	}
	if (carry)
		s1 = static_cast<char>(carry + '0') + s1;

	return s1;
}

//减法：s1 > s2
string sub(string s1, string s2)
{
	if (s1 == s2)
		return "0";
	int l1 = s1.size();
	int l2 = s2.size();

	int curNum, i, j, carry;
	for (i = 0, j = 0; i < l1; ++i, ++j)
	{
		curNum = s1[i] - (j >= l2 ? '0' : s2[j]);
		if (curNum < 0)
		{
			--s1[i + 1];
			s1[i] = 10 + curNum + '0';
		}
		else
			s1[i] = curNum + '0';
	}

	return s1;

}


int main()
{

	int n;
	cin >> n;
	while (n--)
	{
		string s;
		cin >> s1 >> s2;
		int len1 = s1.size();
		int len2 = s2.size();
		int flag1 = 0;
		int flag2 = 0;
		int flag3 = 0;
		if (s1[0] == '-') flag1 = 1;
		if (s2[0] == '-') flag2 = 1;
		string str1, str2;
		int i, t;
		for (t = 0, i = len1 - 1; i >= 0 && s1[i] >= '0' && s1[i] <= '9'; --i)
			str1.push_back(s1[i]);
		for (t = 0,i = len2 - 1; i >= 0 && s2[i] >= '0' && s2[i] <= '9'; --i)
			str2.push_back(s2[i]);

		if (flag1 == 0 && flag2 == 0)		//a+b
		{
			s = add(str1, str2);
		}
		else if (flag1 == 0 && flag2 == 1)
		{
			if (les(str1, str2))
			{
				s = sub(str2, str1);
				flag3 = 1;
			}
			else
				s = sub(str1, str2);
			
		}
		else if (flag1 == 1 && flag2 == 0)
		{
			if (les(str1, str2))
				s = sub(str2, str1);
			else
			{
				s = sub(str1, str2);
				flag3 = 1;
			}
		}
		else
		{
			s = add(str1, str2);
			flag3 = 1;
		}

		reverse(s.begin(), s.end());
		if (flag3 && s != "0")
			cout << "-";
		//除去s的前导0
		int pos = s.find_first_not_of('0');
		if (pos != string::npos)
			cout << s.substr(pos) << endl;
		else
			cout << s << endl;
	}
	return 0;
}