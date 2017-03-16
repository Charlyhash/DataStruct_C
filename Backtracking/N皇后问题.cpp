/*
用n元组x[1:n]表示n后问题的解。x[i]表示皇后i放置在棋盘的第i行的第x[i]列
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

static int n, x[1000];
static long sum;

/*
判断第k个后能不能放在x[k]处
两个皇后不能放在统一斜线上：
若2个皇后放置的位置分别是（i,j）和（k,l）,
且 i-j = k -l 或 i+j = k+l，则说明这2个皇后处于同一斜线上。
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
	//如果t>n说明已经完成一次放置
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
			if (Place(t))					//可以放在i位置处，则继续搜索
				BackTrack1(t + 1);
		}
	}
}

void BackTrack()
{
	int k;
	x[1] = 0;		//初始化为0
	k = 1;
	while (k >= 1)	//循环
	{
		x[k] += 1;	//先放在第一个位置
		while ((x[k] <= n) && !(Place(k)))	//如果不能放
			x[k] += 1;						//放在下一个位置
		if (x[k] <= n)						//放置完成
		{
			if (k == n)						//如果已经放完了n个皇后
			{
				sum++;						//处理次数，输出
				OutPut();
			}
			else							//没有处理完，让k自加，处理下一个皇后
			{
				k++;
				x[k] = 0;
			}
		}									//x[k] > n，说明没有合适的位置了
		else
			k--;							//回溯回去，回到第k-1步
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
非递归 10 - 0.545s  12-6.392s
递归   10 - 0.560s  12-6.659s
*/
