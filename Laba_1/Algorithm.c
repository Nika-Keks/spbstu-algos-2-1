#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include "List.h"
#pragma warning(disable:4996)

List* NewList(char* str, int len)
{
	List* list;
	if (!(list = (List*)malloc(sizeof(List))))
	{
		printf("Allocation error.");
		exit(1);
	}
	len = SizeOfString(str);
	list->str = str;
	list->len = len;
	list->next = NULL;
	return list;
}

List* InsertList(List* current, List* list)
{
	List* ptr = current;
	if (list->len < ptr->len)
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
			if (list->len < ptr->next->len)
			{
				list->next = ptr->next;
				ptr->next = list;
				break;
			}
			ptr = ptr->next;
		}
	}
	return current;
}
///////////////////////////////////////////////////////////////////////


int SizeOfString(char* str) {
	if (str == NULL) {
		printf("Ошибка с выделением памяти ");
		exit(1);
	}
	int count = 0;
	char ch = str[count];
	while (ch != '\0') {
		ch = str[count++];
	}
	return count - 1;
}

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
	int len;
	char* str;
	if (!(str = (char*)malloc(256 * sizeof(char))))
	{
		printf("Allocation error.");
		exit(1);
	}
	if ((fscanf(file, format, str, &len)) != EOF)
	{
		return NewList(str, len);
	}
	return NULL;
}

void PrintList(List* list)
{
	printf("%s %i\n", list->str, list->len);
}

void Matching(List* current, int num)
{
	List* ptr = current;
	while (ptr != NULL)
	{
		if (ptr->len == num)
		{
			PrintList(ptr);
		}
		ptr = ptr->next;
	}
}

void Input(List* head)
{
	int num;
	printf("Введите, пожалуйста, какой длины вы хотите вывести строки: \n");
	scanf("%i", &num);
	Matching(head, num);
}

int KolvoStrok(List* list) {
	int j = 0; // сколько всего строк
	List* ptr = list;
	while (ptr != NULL)
	{
		j++;
		ptr = ptr->next;
	}
	return j;
}

void Printer(List* list, int n, int cnt) {
	List* ptr = list;
	int k = 0;
	for (int i = 0; i < n - cnt; i++) {
		ptr = ptr->next;
		k++;
	}
	for (int p = k; p < n; p++) {
		PrintList(ptr);
		ptr = ptr->next;
	}
}

List* CreationFromFile(FILE* file)
{
	List* head = NULL;
	List* current = NULL;
	char* format = "%[^\n]\n";
	head = NewListFromFile(file, format);
	current = NewListFromFile(file, format);
	while (current != NULL)
	{
		head = InsertList(head, current);
		current = NewListFromFile(file, format);
	}
	return head;
}
