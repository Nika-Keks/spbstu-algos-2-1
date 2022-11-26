#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#pragma warning (disable:4996)


int main(void) {
	int choice;
	int value;
	TreeNodePtr* tmp = NULL;//double pointer to the value we want to remove from the tree
	TreeNodePtr rootPtr = NULL;//root node
	printf("printf 1 if you want to add value,\n");
	printf("printf 2 if you want to delete value, and 3 to finish.\n");
	printf("%s", "? ");
	scanf("%d", &choice);
	while (choice != 3) {
		switch (choice) {
		case 1:
			printf("%s", "Enter a value: ");
			scanf("\n%d", &value);
			InsertNode(&rootPtr, value);
			puts("the tree is:");
			preOrder(rootPtr);
			puts("");
			break;
		case 2:
			if (!isEmpty(rootPtr)) {
				printf("%s", "Enter character to be deleted: ");
				scanf("\n%d", &value);
				Search(&rootPtr, value, &tmp);
				if (tmp) {
					Delete(tmp, tmp);
					printf("%d deleted.\n", value);
					tmp = NULL;
				}
				else {
					printf("%d not found.\n\n", value);
				}
				puts("the tree is:");
				preOrder(rootPtr);
				printf("\n");
			}
			else {
				puts("Tree is empty.\n");
			}
			break;
		default:
			puts("Invalid choice.\n");
			break;
		}
		printf("%s", "? ");
		scanf("%d", &choice);
	}
	return 0;
}
