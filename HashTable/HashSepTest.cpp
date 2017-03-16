#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "HashSep.h"
int main()
{
	//int k = NextPrime(92);
	HashTable h = InitHashTable(10);
	for (int i = 1; i < 11; ++i)
	{
		Insert(i*i, h);
		printf("%d:%d\n", i*i, Hash(i * i, h->TableSize));
	}

	return 0;
}
