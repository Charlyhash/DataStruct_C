#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main()
{
	const int len = 7;
	int index;
	int arr[len] = { 2, 3, 1, 7, 5, 4, 6 };
	printf("Before sort:\n");
	for (index = 0; index < len; ++index)
	{
		printf("%d ", arr[index]);
	}
	printf("\n");

	qsort(arr, len, sizeof(arr[0]), cmp);

	printf("After sort:\n");
	for (index = 0; index < len; ++index)
	{
		printf("%d ", arr[index]);
	}
	printf("\n");

	return 0;
}
/*
Êä³ö£º
Before sort:
2 3 1 7 5 4 6
After sort:
1 2 3 4 5 6 7
*/