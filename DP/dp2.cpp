/*

����һ�������Ǹ��õ��ơ�̰�ġ��������Ƕ�̬�滮����ȫ����������Ȿ��׶μ�״̬��ת�Ʒ�ʽ�����ģ�
ÿ���׶�ֻ��һ��״̬->���ƣ�
ÿ���׶ε�����״̬��������һ���׶ε�����״̬�õ���->̰�ģ�
ÿ���׶ε�����״̬����֮ǰ���н׶ε�״̬����ϵõ���->������
ÿ���׶ε�����״̬���Դ�֮ǰĳ���׶ε�ĳ����ĳЩ״ֱ̬�ӵõ�������֮ǰ���״̬����εõ���->��̬�滮��

01��������
��n�������ͼ�ֵ�ֱ�Ϊvector<int> weight, vector<int> value����Ʒ�����������ΪW�������ñ���װ�µ���Ʒ������ֵ��
���룺n =4
weight=2, 1, 3, 2
value =3, 2, 4, 2
W=5
���=7
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> weight{2, 1, 3, 2};
vector<int> value{3,2,4,2};

//�ݹ������
//��i...n����Ʒ�У�ѡ������������j����Ʒ������ֵ
int solution1(int i, int j)
{
	int res;
	if (i == weight.size())
		res = 0;
	else if (j < weight[i])
		res = solution1(i + 1,  j);
	else
		res = max(solution1(i + 1, j), solution1(i + 1,j - weight[i]) + value[i]);

	return res;
}


int main()
{
	cout << solution1(0,5) << endl;

}