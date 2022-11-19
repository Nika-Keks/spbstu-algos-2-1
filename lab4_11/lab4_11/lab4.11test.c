#include "stdlib.h"
#include "stdio.h"
#include"Type.h"

int main()
{
	int B;//the sum to be equal to the sum of the subset
	int n;//the number of elements in the set
	char* name = "input.txt";
	int *A=ReadFile(name, &B, &n);//we fill the array A with the elements of the subset from the file
	if (A == NULL) return -1;
	if (Serch(A,n,B)==-1) return -1;//finding the right subset
	free(A);
	return 0;
}