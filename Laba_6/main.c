#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void main(void)
{
	short flag = 1;
	tree* test = create_tree("test.txt");
	print(test,&flag);
	free_n(test);
}