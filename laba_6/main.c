#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void main(void)
{
	tree* test = create_tree("test.txt");
	print(test);
	free_n(test);
}