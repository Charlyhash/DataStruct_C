/*
������������һ����װ��Ҫװ��һ��������Ϊc���ִ������м�װ��i������ΪWi��
����װ������Ҫ��ȷ����װ������������Ƶ�����£��������ܶ�ļ�װ��װ���ִ���
�����̣�Ҫ��װ�Ķ࣬��ô����װ����С�ġ��ȶԼ�װ�����������Ȼ��װ���ִ���
*/

#include <stdio.h>
#include <stdlib.h>


//qsot��
int cmp(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

/*
box : ����������
w : �ܹ����ص�����
n : ��װ�������
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