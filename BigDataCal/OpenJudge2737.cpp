/*
OpenJudge2737 ��������
��������������һ�����������ڶ���Ϊ������������100λ
������̵���������
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

string sub(string s1, string s2)
{
	int flag = 0;
	if (s1.length() < s2.length() || ((s1.length() == s2.length()) && s1 < s2))
	{
		flag = 1;
		string tmp = s1;
		s1 = s2;
		s2 = s1;
	}

	int i, j;
	for (i = s1.length() - 1, j = s2.length() - 1; i >= 0; i--, j--)
	{
		s1[i] = char(s1[i] - (j >= 0 ? s2[j]-'0' : 0));
		if (s1[i] < '0')
		{
			--s1[i - 1];
			s1[i] += 10;
		}

	}

	for (i = 0; i < s1.length(); ++i)
	{
		if (s1[i] != '0') break;
	}
	if (i == s1.length()) i = s1.length() - 1;
	s1 = s1.substr(i);

	if (flag) s1 = "-" + s1;

	return s1;
}

string add(string s1, string s2)
{
	if (s1.length() < s2.length())
	{
		string tmp = s1;
		s1 = s2;
		s2 = tmp;
	}

	int i, j;
	for (i = s1.length() - 1, j = s2.length() - 1; i >= 0; --i,--j)
	{
		s1[i] = char(s1[i] + (j >= 0 ? s2[j] - '0' : 0));
		if (s1[i] - '0' >= 10)
		{
			s1[i] = (s1[i] - '0') % 10 + '0';
			if (i)
				s1[i - 1]++;
			else
				s1 = "1" + s1;
		}
	}

	return s1;
}

string div(string s1, string s2)
{
	string res = "0";
	if (s1.size() < s2.size() || (s1.size() == s2.size() && s1 < s2))
	{
		return "0";
	}

	int i;
	int subLen = s1.size() - s2.size();
	for (i = subLen; i >= 0; --i)
	{
		string s3(i, '0');
		string s4 = s2 + s3;
		//������������ֱ��s1��s4С
		do
		{
			string tmp = sub(s1, s4);
			if (tmp[0] == '-') break;	//������
			else
			{
				s1 = tmp;
				res = add(res, ("1" + s3));//����s3��λ����ȷ���ӵ���
			}
		} while (1);
	}

	return res;
}

//˳��ѳ˷�д��
string mul(string s1, string s2)
{
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());

	int tmp = 0;
	string s(s1.size() + s2.size(), '0');
	for (int i = 0; i < s1.size(); ++i)
	{
		for (int j = 0; j < s2.size(); ++j)
		{
			tmp = (s1[i] - '0')*(s2[j] - '0');
			//��λ
			s[i + j + 1] = s[i + j + 1] + (s[i + j] - '0' + tmp) / 10;
			//�ǽ�λ
			s[i + j] = (s[i + j] - '0' + tmp) % 10 + '0';
		}
	}

	reverse(s.begin(), s.end());
	int pos = s.find_first_not_of('0');
	if (pos == -1)
		return "0";
	else
		return s.substr(pos);
}

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	cout << div(s1, s2) << endl;

	return 0;
}