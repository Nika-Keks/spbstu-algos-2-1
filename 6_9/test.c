#include <stdlib.h>
#include <stdio.h>
#include "type6_9.h"
#pragma warning (disable:4996)



int main()
{
	tree* p = NULL;
	if (ReadConsol(&p) == -1) return -1;//we fill the tree with data entered in the console by the user
	int k;
	printf("Enter the sequence number of the positive element\n");
	scanf("%d", &k);
	if (k <= p->pos)//If the number of positive elements in the tree is greater than or equal to the order of the smallest desired element of the tree
	{
		tree* o = Kmin(p, k);//search for the k-th positive element of the tree
		printf(" The positive %d-th element found=%d\n", k, o->key);
		if (o->key % 2 == 0) PrintTree(p, o->key, k - 1);//If the found element is even, then we output positive elements that are smaller than the found one
	}
	else printf("There is no %d-th positive element in the tree\n", k);//The order of an element that does not exist is requested
	FreeTree(&p);//freeing up the memory allocated for the tree
	return 0;
}