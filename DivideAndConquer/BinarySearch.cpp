#include <iostream>

using namespace std;

int BinarySearch(int *a, int len, int key)
{
	int low = 0;
	int high = len - 1;
	while (low <= high)
	{
		int mid = (high - low) / 2 + low;
		if (a[mid] == key)
			return mid;
		else if (a[mid] > key)
			high = mid - 1;
		else
			low = mid + 1;
	}

	return -1;
}

int main()
{
	const int MAXN = 100;
	int a[MAXN];
	for (int i = 0; i < MAXN; ++i)
		a[i] = i * i;
	int key = 144;
	int res = BinarySearch(a, MAXN, key);

	if (res == -1)
	{
		cout << "Not Find!" << endl;
	}
	else
		cout << "Index : " << res << endl;
	

	return 0;
}