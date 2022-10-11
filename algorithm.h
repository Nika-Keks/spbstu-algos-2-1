#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"
#define LINE_LENGTH 40

list* Create_Node(char* word, int number)
{
	list* node = (list*)malloc(sizeof(list));
	node->word = word;
	node->number = number;
	node->next = NULL;
	return node;

}

list* Create_Node_From_File(FILE* file, char* format)
{
	int number;
	char* word = malloc(LINE_LENGTH * sizeof(char));

	if (fscanf(file, format, word, &number) != EOF)
		return Create_Node(word, number);

	return NULL;
}

list* Insert(list* list_1, list* list_2)
{

	list* sup = list_1;
	if (strcmp(list_2->word, sup->word) < 0)
	{
		list_2->next = sup;
		return list_2;
	}
	while (sup != NULL)
	{
		if (sup->next == NULL)
		{
			sup->next = list_2;
			break;
		}
		else
		{
			if (strcmp(list_2->word, sup->next->word) < 0)
			{
				list_2->next = sup->next;
				sup->next = list_2;
				break;
			}
			else
				if (strcmp(list_2->word, sup->next->word) == 0)
				{
					list_2->next = sup->next;
					sup->next = list_2;
					break;
				}
			sup = sup->next;
		}
	}
	return list_1;
}

list* Create_List_From_File(FILE* file)
{
	list* head = NULL;
	list* cur = NULL;
	char* format = "%s %d";
	head = Create_Node_From_File(file, format);
	cur = Create_Node_From_File(file, format);
	while (cur != NULL)
	{
		head = Insert(head, cur);
		cur = Create_Node_From_File(file, format);
	}
	return head;
}

void Print_List(list* head)
{
	printf("\n");
	for (list* node = head; node != NULL; node = node->next)
	{
		printf("%s %d\n", node->word, node->number);
	}
}

void Checkword(list* head, char word[])
{
	int flag_1 = 0;
	while (head != NULL)
	{
		if (strcmp(head->word, word) == 0)
		{
			printf("\nYes, this word exists. His number: %d\n", head->number);
			flag_1++;
		}
		head = head->next;
	}
	if (flag_1 == 0)
		printf("\nThere is no such word.\n");
}

void SearchWords(list* head, int num)
{
	int flag_2 = 0;
	int flag_3 = 0;
	while (head != NULL)
	{
		if ((head->number == num) && (flag_2 == 0))
		{
			printf("\nYes, this number exists. His words: %s\n", head->word);
			flag_2++;
			flag_3++;
		}
		if ((head->number == num) && (flag_2 != 0) && (flag_3 == 0))
		{
			printf("                                    %s\n", head->word);
			flag_2++;
		}
		head = head->next;
		flag_3 = 0;
	}
	if (flag_2 == 0)
		printf("\nThere is no such number.\n");
}

void Push_Back(list* head_ref, char* word, int number)
{

	list* new_node = (list*)malloc(sizeof(list));
	list* last = head_ref;

	new_node->word = word;
	new_node->number = number;

	new_node->next = NULL;

	if (head_ref == NULL)
	{
		head_ref = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
	return;
}

list* Combine_Words_List(list* head)
{
	list* cur = head;
	list* sup = head->next;
	list* prom = sup;
	list* list_3 = NULL;
	int flag = 0;
	while (sup != NULL)
	{

		if ((strcmp(cur->word, sup->word) == 0))
		{

			while ((sup != NULL) && (strcmp(cur->word, sup->word) == 0))
			{
				cur->number += sup->number;
				prom = sup->next;
				free(sup);
				sup = prom;
			}

		}

		if (flag == 0)
			list_3 = Create_Node(cur->word, cur->number);
		else
			Push_Back(list_3, cur->word, cur->number);
		flag++;
		cur = sup;
		sup = sup->next;
	}
	Push_Back(list_3, cur->word, cur->number);
	return list_3;
}

void Sort_And_Search(FILE* file)
{
	char word[40] = "";
	int num = 0;
	list* list_1 = Create_List_From_File(file);
	list* list_3 = Combine_Words_List(list_1);
	Print_List(list_3);
	printf("\nEnter a word: ");
	scanf("%s", &word);
	Checkword(list_3, word);
	printf("\nEnter a number: ");
	scanf("%d", &num);
	SearchWords(list_3, num);
	free(list_1);
	free(list_3);
	fclose(file);
}
