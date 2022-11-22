#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Header.h"
#pragma warning(disable:4996)

int main(void) {
	int n;
	int max;
	scanf("%d", &n);
	int i; 
	int item = 0; 
	TreeNodePtr rootPtr = NULL; 
	srand(time(NULL));
	puts("The numbers being placed in the tree are:");
	for (i = 0; i < n; ++i) {
		item = rand() % Inf;
		printf("%3d", item);
		InsertNode(&rootPtr, item);
	}
	

	puts("\n\nThe preOrder traversal is:");
	Preorder(rootPtr);
	leafSum(rootPtr);
	puts("");
	puts("\n\nThe number of list is:");
	Preorder2(rootPtr);
	puts("");
	int mas[Inf][Inf] = { 0 };
	ancestorMatrixRec(rootPtr, mas);
	ancestorMatrix(rootPtr, mas);

	return 0;
}

