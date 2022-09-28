#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>

#pragma warning(disable:4996)

typedef struct List {
	char* word;
	int number;
	struct List* next;
} List;

List* NewList(char* word, int number)
{
	List* list;
	if (!(list = (List*)malloc(2 * sizeof(List))))
	{
		printf("Allocation error.");
		exit(1);
	}
	list->word = word;
	list->number = number;
	list->next = NULL;
	return list;
}

List* InsertList(List* current, List* list)
{
	List* ptr = current;
	if (list->number < ptr->number)
	{
		list->next = ptr;
		return list;
	}
	while (ptr != NULL)
	{
		if (ptr->next == NULL)
		{
			ptr->next = list;
			break;
		}
		else
		{
			if (list->number < ptr->next->number)
			{
				list->next = ptr->next;
				ptr->next = list;
				break;
			}
			else if (list->number == ptr->next->number)
			{
				if (strcmp(list->word, ptr->next->word) == 0)
				{
					printf("The same words correspond to the same key numbers");
					exit(1);
				}
				list->next = ptr->next;
				ptr->next = list;
				break;
			}
			ptr = ptr->next;
		}
	}
	return current;
}