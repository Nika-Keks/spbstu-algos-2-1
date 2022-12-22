#include <math.h>
#include <stdio.h>
#include "Header.h"
#pragma warning (disable:4996)

int main(void)
{
	int* length = (int*)malloc(sizeof(int));
	String* ptr = NULL;
	ReadWord("file.txt", length, &ptr);
	printf("First task\n");
	StringPrint(ptr, N, 1);
	int m = 2;
	printf("Second task\nEnter standard\n");
	scanf("%d", &m);
	StringPrint(ptr, m, 2);
	return 0;
}