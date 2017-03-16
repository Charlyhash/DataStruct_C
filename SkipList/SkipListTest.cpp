#include "skiplist.h"

int main()
{
	skip_list *sl = create_sl();
	int i = 1;
	for (; i < 100; ++i)
	{
		insert(sl, i, i);
	}
	print_sl(sl);
	for (i = 11; i < 100; ++i)
	{
		if (!erase(sl, i))
			printf("No!\n");
	}
	print_sl(sl);
	int *p = search(sl, 10);
	if (p)
		printf("value of key 10 is %d\n", *p);
	free_sl(sl);

	return 0;
}