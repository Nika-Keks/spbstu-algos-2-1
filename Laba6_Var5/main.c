#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Header.h"
#pragma warning(disable:4996)

int main() {
	tree* Tree = NULL;
	//let's add some interface
	printf("Choose action:\nAdd to Tree - 1\nDelete from Tree - 2\nPrint the Tree - 3\nExit - any other number\n");
	int ans = 1;
	while (ans == 1 || ans == 2 || ans == 3) {
		scanf("%d", &ans);
		if (ans == 1) Add(&Tree);
		if (ans == 2) Delete(&Tree);
		if (ans == 3) {
			printf("Tree is: ");
			if (Tree == NULL) printf("*empty*");
			else Print(Tree);
			printf("\n");
		}
	}
	return 0;
}