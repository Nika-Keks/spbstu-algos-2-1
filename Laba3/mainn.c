#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba3.h"
#pragma warning(disable:4996)

int main() {
	setlocale(LC_ALL, "Rus");
	char* f = "Matrix.txt";
	int n;
	List** M = ReadText(f, &n);
	Unitity(M, 4, n);
	PrintMatrix(M[0], 2 * n);
	List_free(M, 1);
	return 0;
}