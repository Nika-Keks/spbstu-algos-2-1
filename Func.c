#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include "./LIST.c"

#pragma warning(disable:4996)

FILE* OpenFile(char* name, char* mode);
void FileClose(FILE* file);
List* NewListFromFile(FILE* file, char* format);
void PrintList(List* list);
void Matching(List* current, int num);
void Input(List* head);
void Printer(List* list);
List* CreationFromFile(FILE* file);

FILE* OpenFile(char* name, char* mode)
{
	FILE* fp;
	if ((fp = fopen(name, mode)) == NULL)
	{
		printf("Failed to open file");
		exit(1);
	}
	return fp;
}

void FileClose(FILE* file)
{
	fclose(file);
}
List* NewListFromFile(FILE* file, char* format)
{
	int number;
	char* word;
	if (!(word = (char*)malloc(32 * sizeof(char))))
	{
		printf("Allocation error.");
		exit(1);
	}
	if ((fscanf(file, format, word, &number)) != EOF)
	{
		return NewList(word, number);
	}
	return NULL;
}
void PrintList(List* list)
{
	printf("%s %i\n", list->word, list->number);
}

void Matching(List* current, int num)
{
	List* ptr = current;
	while (ptr != NULL)
	{
		if (ptr->number == num)
		{
			PrintList(ptr);
			break;
		}
		ptr = ptr->next;
	}

}
void Input(List* head)
{
	int num;
	printf("Please enter key number: \n");
	scanf("%i", &num);
	Matching(head, num);
}

void Printer(List* list)
{
	if (list)
	{
		PrintList(list);
		Printer(list->next);
	}
}

List* CreationFromFile(FILE* file)
{
	List* head = NULL;
	List* current = NULL;
	char* format = "%s %i";
	head = NewListFromFile(file, format);
	current = NewListFromFile(file, format);
	while (current != NULL)
	{
		head = InsertList(head, current);
		current = NewListFromFile(file, format);
	}
	return head;
}