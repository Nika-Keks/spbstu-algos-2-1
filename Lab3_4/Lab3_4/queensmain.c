#include <stdio.h>
#include "queens.h"

#pragma warning(disable:4996)

int main() {
	printf("Goryunov Maxim 5030102/10002 Lab 4 Variant 13\n");
	int n;
	printf("Print Board size: \n");
	scanf("%i", &n);
	int** board = boardCreate(n);
	int* queens = queensCreate(n);
	placeQueens(board, queens, 1, n);
	return 0;
}