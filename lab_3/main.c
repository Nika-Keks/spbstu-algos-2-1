#pragma warning(disable : 4996)
#include <stdio.h>
#include "struct.h"
#include <locale.h>


int main()
{
	setlocale(LC_ALL, ".1251");
	FILE* file = fopen("data.txt", "r");
	All_Operations(file);

	return 0;

}