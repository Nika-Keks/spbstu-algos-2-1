#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#pragma warning(disable:4996)

int main(void) {
	Tree* tree = NULL;
	printf("add node - 1\ndelete node - 2\nprint current tree - 3\nend up program - any other num\n");
	int num = 1;
	while (num == 1 || num == 2 || num == 3) {
		if (!scanf("%i", &num)) break;
		if (num == 1) Add(&tree);
		if (num == 2) Delete(&tree);
		if (num == 3) {
			printf("result: ");
			if (tree == NULL) printf("empty tree");
			else PrintTree(tree);
			printf("\n");
		}
	}
	return 0;
}