#pragma warning(disable : 4996)
#include <stdio.h>
#include "struct.h"

int main()
{
	FILE* file = fopen("spisok.txt", "r");
	Sort_And_Search(file);

	return 0;
	
}
