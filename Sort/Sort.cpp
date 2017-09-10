#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <algorithm>
#define LENGTH(a) ((sizeof(a))/(sizeof(a[0])))
#define SWAP(a, b) (a^=b, b^=a, a^=b)

auto f = [](int x, int y) {x ^= y; y ^= x; x ^= y; };

//ð������1
void BubbleSort(int a[], int n)
{
	int i, j;
	int tmp;
	for (i = n - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (a[j] > a[j + 1])
			{
				f(a[j], a[j - 1]);
				//tmp = a[j];
				//a[j] = a[j + 1];
				//a[j + 1] = tmp;
			}
		}
	}
}

//ð������2
void BubbleSort2(int arr[], int n)
{
	int i, j;
	int tmp;
	bool isChanged = true;
	for (i = n - 1; (i > 0) && isChanged; --i)
	{
		isChanged = false;			//��i�������Ƿ񽻻�
		for (j = 0; j < i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				isChanged = true;
			}
		}
	}
}

//ϣ������
void ShellSort(int arr[], int len)
{
	int i, j;
	int increment, tmp;
	for (increment = len / 2; increment > 0; increment /= 2)
	{
		for (i = increment; i < len; ++i)
		{
			tmp = arr[i];
			for (j = i; j >= increment; j -= increment)		//every time, we should compare.
				if (tmp < arr[j - increment])
					arr[j] = arr[j - increment];
				else
					break;
			arr[j] = tmp;
		}
	}
}

//ֱ�Ӳ�������
//mark first element as sorted
//for each unsorted element
//'extract' the element
//for i = lastSortedIndex to 0
//if currentSortedElement > extractedElement
//move sorted element to the right by 1
//else: insert extracted element
void StraightInserationSort(int a[], int n)
{
	int i, j, temp;
	for (i = 1; i < n; ++i)
	{
		temp = a[i];
		j = i - 1;
		while ((j>=0)&&(temp<a[j]))
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
}


//������
#define LeftChild(i) (2*i+1)
void PrecDown(int a[], int i, int N)
{
	int child;
	int tmp;
	for (tmp = a[i]; LeftChild(i) < N; i = child)
	{
		child = LeftChild(i);
		if (child != N - 1 && a[child + 1] > a[child])
			child++;
		if (tmp < a[child])
			a[i] = a[child];
		else
			break;
	}
	a[i] = tmp;
}

void HeapSort(int a[], int N)
{
	int i;
	for (i = N / 2; i >= 0; i--)
		PrecDown(a, i, N);
	for (i = N - 1; i > 0; i--)
	{
		SWAP(a[0], a[i]);
		PrecDown(a, 0, i);
	}
}

//�鲢����
//lPos=start of left half, rPos=start of right half
//rihgtEnd = end of the right half
void Merge(int a[], int tmp[], int lPos, int rPos, int rightEnd)
{
	int i, leftEnd, numElem, tmpPos;
	leftEnd = rPos - 1;		//end of left half
	tmpPos = lPos;
	numElem = rightEnd - lPos + 1;
	while (lPos <= leftEnd && rPos <= rightEnd)
	{
		if (a[lPos] <= a[rPos])
			tmp[tmpPos++] = a[lPos++];
		else
			tmp[tmpPos++] = a[rPos++];
	}
	while (lPos <= leftEnd)
		tmp[tmpPos++] = a[lPos++];
	while (rPos <= rightEnd)
		tmp[tmpPos++] = a[rPos++];
	//copy tmp back;
	for (i = 0; i < numElem; i++, rightEnd--)
		a[rightEnd] = tmp[rightEnd];
}

void MSort(int a[], int tmp[], int left, int right)
{
	int center;
	if (left < right)
	{
		center = (right + left) / 2;		//�ֳ�����
		MSort(a, tmp, left, center);
		MSort(a, tmp, center + 1, right);
		Merge(a, tmp, left, center+1, right);	//�ϲ����������
	}
}

void MergeSort(int a[], int n)
{
	int *tmp;
	tmp = (int*)malloc(sizeof(int)*n);
	if (tmp == NULL)
		printf("No sapce for tmp array!\n");
	MSort(a, tmp, 0, n - 1);
	free(tmp);
}

//��������
void QuickSort(int a[], int left, int right)
{
	if (left < right)
	{
		int i = left, j = right, key = a[i];
		while (i < j)		//i < j˵��û�б�����
		{
			while (i < j && a[j] > key)	//���ұ߱������ҵ���һ��С��key��ֵ
				j--;
			if (i < j)
				a[i++] = a[j];			//���ҵ���ֵ�ŵ�i��λ����
			while (i < j && a[i] < key)	//����߱������ҵ���һ������key��ֵ
				i++;
			if (i < j)
				a[j--] = a[i];			//���ҵ���ֵ�ŵ�j��λ����
		}
		a[i] = key;						//��key�ŵ�i��λ���ϣ�һ���������
		QuickSort(a, left, i - 1);
		QuickSort(a, i + 1, right);
	}
}

//��������
void InsertionSort(int arr[], int len)
{
	int i, j;
	int tmp;
	for (i = 1; i < len; ++i)
	{
		tmp = arr[i];
		for (j = i; j > 0 && arr[j - 1] > tmp; j--)
			arr[j] = arr[j - 1];
		arr[j] = tmp;
	}
}

//Ͱ����
/*
����˵����	a----�����������
n----����ĳ���
max--����a�����ֵ�ķ�Χ
*/
void BucketSort(int a[], int n, int max)
{
	int i, j;
	int *bucket;

	if (a == NULL || n < 1 || max < 1)
		return;
	if ((bucket = (int*)malloc(max*sizeof(int))) == NULL)
		return;
	memset(bucket, 0, max*sizeof(int));

	for (i = 0; i < n; ++i)
		bucket[a[i]]++;
	for (i = 0, j = 0; i < max; ++i)
		while ((bucket[i]--) > 0)
			a[j++] = i;

	free(bucket);
}

//��������
/*
��ȡ����a�е����ֵ
����˵����	a---����
n---���鳤��
*/
int getMax(int a[], int n)
{
	int i, max;
	for (max = a[0], i = 1; i < n; ++i)
		if (a[i] > max)
			max = a[i];

	return max;
}

//Ͱ����
/*
�����鰴��ĳ��λ����������
����˵��:
a---����
n---���鳤��
exp---ָ��
exp=1��ʾ���ո�λ��exp=10��ʾ����ʮλ��...
*/


int main()
{
	//int a[] = { 8, 3, 6, 4, 2, 1, 5, 7 };
	int a[] = {8, 7, 1, 2, 3, 4, 5, 6};
	int len = LENGTH(a);
	int i;
	printf("before sort:");
	for (i = 0; i < len; ++i)
		printf("%d ", a[i]);
	printf("\n");
	//ShellSort(a, len);
	//BubbleSort(a, len);
	//BubbleSort2(a, len);
	//StraightInserationSort(a, len);
	//HeapSort(a, len);
	MergeSort(a, len);


	
	printf("after sort:");
	for (i = 0; i < len; ++i)
		printf("%d ", a[i]);
	printf("\n");
}