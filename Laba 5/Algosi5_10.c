#include "header.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable:4996)



int main()
{
	NodePtr tree = Creation();

	puts("classification of animals");
	puts("to end the proccess of adding enter 0");
	char item[100];
	char quality[100];
	puts("Enter the animal");
	scanf("%s", item);
	puts("Enter quality");
	scanf("%s", quality);
	while (item[0] != '0')
	{
		Insert(item, quality, &tree);
		puts("Enter the animal");
		scanf("%s", item);
		if (item[0] == '0') return 0;
		puts("Enter quality");
		scanf("%s", quality);
	}
	return 0;
}
