/*
问题描述：有一批集装箱要装上一艘载重量为c的轮船。其中集装箱i的重量为Wi。
最优装载问题要求确定在装载体积不受限制的情况下，将尽可能多的集装箱装上轮船。
求解过程：要想装的多，那么就先装重量小的。先对集装箱的重量排序，然后装到轮船上
*/

#include <stdio.h>
#include <stdlib.h>


//qsot用
int cmp(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

/*
box : 排序后的重量
w : 能够承载的重量
n : 集装箱的总数
*/
void loading(int *box, int w, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (w - box[i] >= 0)
		{
			w -= box[i];
			printf("%d ", box[i]);
		}
	}
	printf("\n");
}

int main()
{
	int w = 100;
	int box[6] = { 80,20,25,30,10,20 };
	qsort(box, 6, sizeof(box[0]), cmp);
	loading(box, w, 6);
	
	return 0;
}