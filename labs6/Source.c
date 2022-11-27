#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#pragma warning (disable:4996)


int main(void) {
	int choice;
	int value;
	TreeNodePtr tmp = NULL;//a pointer to the node containing the value we want to delete
	TreeNodePtr rootPtr = NULL;
	printf("Enter 1 to add a value.\n");
	printf("Enter 2 to delete a value.\n");
	printf("Enter 3 to finish.\n");
	printf("%s", "? ");
	scanf_s("%d", &choice);
	while (choice != 3) {
		switch (choice) {
		case 1:
			printf("%s", "Enter a value: ");
			scanf_s("\n%d", &value);
			InsertNode(&rootPtr, value);
			preOrder(rootPtr);
			puts("");
			break;
		case 2:
			if (!isEmpty(rootPtr)) {
				printf("%s", "Enter character to be deleted: ");
				scanf_s("\n%d", &value);
				Search(rootPtr, value, &tmp);
				if (tmp) {
					Delete(&rootPtr, &tmp);
					printf("%d deleted.\n", value);
					tmp = NULL;
				}
				else {
					printf("%d not found.\n\n", value);
				}
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
		scanf_s("%d", &choice);
	}
	return 0;
}

