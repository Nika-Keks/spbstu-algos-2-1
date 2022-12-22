#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)
#include "Header.h"

int main(void)
{
	TreeNodePtr ptr, necessary;
	ptr = NULL;
	int number;
	int choice;
	puts("Type 1 for insert");
	puts("Type 2 for delete");
	puts("type 3 for exit");
	puts("Enter a number");
	scanf("%d", &choice);

	while (choice != 0)
	{

		switch (choice)
		{
		case 1:
			puts("Enter a number which you want to insert");
			scanf("%d", &number);

			InsertNode(&ptr, number);
			puts("Output");
			OutputNode(ptr);
			break;
		case 2:
			if (ptr == NULL)
			{
				printf("The tree is empty");
				break;
			}
			
			puts("Enter a number which you want to delete");
			scanf("%d", &number);
			necessary = NULL;
			Seeker(ptr, number, &necessary);
			if (necessary == NULL)
			{
				puts("This number wasn't found");
				break;
			}
			DeleteNode(&ptr, &necessary);
			if (ptr == NULL)
			{
				printf("The tree is empty");
				break;
			}
			puts("Output");
			OutputNode(ptr);
			break;
		case 3:
			return 0;
		}
		puts("\nEnter a number");
		scanf("%d", &choice);

	}
	return 0;
}

