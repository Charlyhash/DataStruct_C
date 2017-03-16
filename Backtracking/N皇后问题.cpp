/*
��nԪ��x[1:n]��ʾn������Ľ⡣x[i]��ʾ�ʺ�i���������̵ĵ�i�еĵ�x[i]��
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

static int n, x[1000];
static long sum;

/*
�жϵ�k�����ܲ��ܷ���x[k]��
�����ʺ��ܷ���ͳһб���ϣ�
��2���ʺ���õ�λ�÷ֱ��ǣ�i,j���ͣ�k,l��,
�� i-j = k -l �� i+j = k+l����˵����2���ʺ���ͬһб���ϡ�
*/

void OutPut()
{
	for (int i = 1; i <= n; ++i)
		printf("(%d, %d) ", i, x[i]);
	printf("\n");
}

int Place(int k)
{
	for (int j = 1; j < k; ++j)
		if (abs(k - j) == abs(x[k] - x[j]) || x[j] == x[k])
			return 0;
	return 1;
}

void BackTrack1(int t)
{
	//���t>n˵���Ѿ����һ�η���
	if (t > n)
	{
		sum++;
		OutPut();
	}
	else
	{
		for (int i = 1; i <= n; ++i)
		{
			x[t] = i;
			if (Place(t))					//���Է���iλ�ô������������
				BackTrack1(t + 1);
		}
	}
}

void BackTrack()
{
	int k;
	x[1] = 0;		//��ʼ��Ϊ0
	k = 1;
	while (k >= 1)	//ѭ��
	{
		x[k] += 1;	//�ȷ��ڵ�һ��λ��
		while ((x[k] <= n) && !(Place(k)))	//������ܷ�
			x[k] += 1;						//������һ��λ��
		if (x[k] <= n)						//�������
		{
			if (k == n)						//����Ѿ�������n���ʺ�
			{
				sum++;						//������������
				OutPut();
			}
			else							//û�д����꣬��k�Լӣ�������һ���ʺ�
			{
				k++;
				x[k] = 0;
			}
		}									//x[k] > n��˵��û�к��ʵ�λ����
		else
			k--;							//���ݻ�ȥ���ص���k-1��
	}
}

int main()
{
	clock_t start, finish;
	double duration;

	int nn;
	while (scanf_s("%d", &nn) != EOF)
	{
		n = nn;
		sum = 0;
		for (int i = 0; i <= n; ++i)
			x[i] = 0;
		start = clock();
		BackTrack();
		//BackTrack1(1);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("%f seconds\n", duration);
		

		//BackTrack1(1);
		printf("%d\n", sum);
	}

	return 0;
}

/*
�ǵݹ� 10 - 0.545s  12-6.392s
�ݹ�   10 - 0.560s  12-6.659s
*/
