/*�߶���*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#pragma warning(disable:4996)

#define MAXN 1000
#define MAX_INT 0x7fffffff

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int NextPow(int n)
{
	--n;
	n = n >> 1 | n;
	n = n >> 2 | n;
	n = n >> 4 | n;
	n = n >> 8 | n;
	n = n >> 16 | n;

	return ++n;
}

struct IntervalTreeNode
{
	int val;
	int addMask; //�ӳٱ��ʹ��
}intervalTree[MAXN]; //����һ�����Ϊ1000���߶�����intervalTree[0]Ϊ���ڵ�

/*
ʹ��arr[]��ʼ���߶�����rootΪ���ڵ��λ�á�istartΪ������ʼλ�ã�iendΪ�������λ��
*/
void IntervalTreeBuilt(int root, int arr[], int istart, int iend)
{
	intervalTree[root].addMask = 0;
	if (istart == iend) //Ҷ�ӽڵ㣬��ʱarr[istart]���Ǹýڵ��ֵ
		intervalTree[root].val = arr[istart];
	else
	{
		//���򣬵ݹ�
		int mid = (istart + iend) >> 1;
		IntervalTreeBuilt(root * 2 + 1, arr, istart, mid);// ����������
		IntervalTreeBuilt(root * 2 + 2, arr, mid + 1, iend);//����������
		//��ǰ�ڵ��ֵ
		intervalTree[root].val = min(intervalTree[root * 2 + 1].val, intervalTree[root * 2 + 2].val);
	}
}


//�������������´��ݱ�־��rootΪ��ǰ�Ľڵ�
//pushdown���������ý���ֻ�ǰ�addMask�����ӽڵ㣬Ȼ��ѵ�ǰ�ڵ��addMask����Ϊ0
void PushDown(int root)
{
  
	if (intervalTree[root].addMask != 0)
	{
		intervalTree[root].addMask = 0;
		//�����ӽڵ��addMask��val(��Ϊ���е��ӽڵ㶼Ҫ����addMask,�����������
		//��СֵҲҪ����addMask)
		intervalTree[root * 2 + 1].addMask += intervalTree[root].addMask;
		intervalTree[root * 2 + 2].addMask += intervalTree[root].addMask;
		intervalTree[root * 2 + 1].val += intervalTree[root].addMask;
		intervalTree[root * 2 + 2].val += intervalTree[root].addMask;
	}
}

//��ѯ������rootΪ���ڵ㣬��ǰ����[nstart, nend],��ѯ����[qstart, qend].
//��ѯ�������Сֵ
int intervalTreeQuery(int root, int nstart, int nend, int qstart, int qend)
{
	//û�н���
	if (qstart > nend || qend < nstart)
		return MAX_INT;
	//��ǰ��������ڲ�ѯ����:���ص�ǰ�ڵ��ֵ
	if (qstart <= nstart && qend >= nend)
		return intervalTree[root].val;
	//�ֱ������������ѯ
	PushDown(root);//���´���
	int mid = (nstart + nend) >> 1;
	return min(intervalTreeQuery(root * 2 + 1, nstart, mid, qstart, qend),
		intervalTreeQuery(root * 2 + 2, mid + 1, nend, qstart, qend));
}

//������£���addMask�ӵ�root������ĵ����䲢���´���
//[nstart, nend]λ��ǰ�ڵ�����ʾ������
//[ustart, uend]Ϊ�����µ�����
//addValΪ����ֵ
void intervalTreeUpdate(int root, int nstart, int nend, int ustart, int uend, int addVal)
{
	//û�н���
	if (ustart > nend || uend < nstart)
		return;
	//��ǰ�ڵ�����������ڸ���������
	if (ustart <= nstart && uend >= nend)
	{
		intervalTree[root].addMask += addVal;
		intervalTree[root].val += addVal;
		return;
	}
	//������������
	PushDown(root);
	int mid = (nstart + nend) >> 1;
	intervalTreeUpdate(root * 2 + 1, nstart, mid, ustart, uend, addVal);
	intervalTreeUpdate(root * 2 + 2, mid+1, nend, ustart, uend, addVal);
	//���µ�ǰ�ڵ��val
	intervalTree[root].val = min(intervalTree[root * 2 + 1].val, intervalTree[root * 2 + 2].val);
}

void Print(int len)
{
	for (int i = 0; i < NextPow(len)-1; ++i)
		printf("(%d) ", intervalTree[i].val);
	printf("\n");
}

void test_interval_tree()
{
	int arr[6] = {2,5,1,4,3,9};
	//����built����
	IntervalTreeBuilt(0, arr, 0, 5);
	Print(12);
	//����query����
	printf("[1,3]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 1, 3));
	printf("[0,2]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 0, 4));
	printf("[3,5]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 3, 5));

	//����updata
	intervalTreeUpdate(0, 0, 5, 1, 3, 2);
	Print(12);
	//����query����
	printf("[1,3]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 1, 3));
	printf("[0,2]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 0, 4));
	printf("[3,5]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 3, 5));


	intervalTreeUpdate(0, 0, 5, 0, 2, 1);
	Print(12);
	//����query����
	printf("[1,3]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 1, 3));
	printf("[0,2]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 0, 4));
	printf("[3,5]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 3, 5));


	intervalTreeUpdate(0, 0, 5, 3, 5, 2);
	Print(12);
	//����query����
	printf("[1,3]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 1, 3));
	printf("[0,2]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 0, 4));
	printf("[3,5]����Сֵ��%d\n", intervalTreeQuery(0, 0, 5, 3, 5));

}



int main()
{
	test_interval_tree();
	//printf("%d %d %d", NextPow(15), NextPow(16), NextPow(17));
	printf("down!\n");

	return 0;
}