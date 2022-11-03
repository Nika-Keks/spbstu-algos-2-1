#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"
#include <stdlib.h>
#define LINE_LENGTH 100
#define NUMBER_GROUPS 5

list* Create_Node(char* group, char* surname, char* name, char* patronymic, int mark1, int mark2, int mark3)
{
	list* node = (list*)malloc(sizeof(list));
	node->group = group;
	node->surname = surname;
	node->name = name;
	node->patronymic = patronymic;
	node->mark1 = mark1;
	node->mark2 = mark2;
	node->mark3 = mark3;
	node->next = NULL;
	return node;

}
//function to create a list node

list* Create_Node_From_File(FILE* file, char* format)
{
	int mark1;
	int mark2;
	int mark3;
	char* group = malloc(LINE_LENGTH * sizeof(char));
	char* surname = malloc(LINE_LENGTH * sizeof(char));
	char* name = malloc(LINE_LENGTH * sizeof(char));
	char* patronymic = malloc(LINE_LENGTH * sizeof(char));

	if (fscanf(file, format, group, surname, name, patronymic, &mark1, &mark2, &mark3) != EOF)
		return Create_Node(group, surname, name, patronymic, mark1, mark2, mark3);

	return NULL;
}
//function to create a list node from a file

list* Insert(list* list_1, list* list_2)
{
	list* sup = list_1;
	if (strcmp(list_2->surname, sup->surname) < 0)
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
			if (strcmp(list_2->surname, sup->next->surname) < 0)
			{
				list_2->next = sup->next;
				sup->next = list_2;
				break;
			}
			else
				if (strcmp(list_2->surname, sup->next->surname) == 0)
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
//function to sort the list

list* Create_List_From_File(FILE* file)
{
	list* head = NULL;
	list* cur = NULL;
	char* format = "%s %s %s %s %d %d %d";
	head = Create_Node_From_File(file, format);
	cur = Create_Node_From_File(file, format);
	while (cur != NULL)
	{
		head = Insert(head, cur);
		cur = Create_Node_From_File(file, format);
	}
	return head;
}
//function to create a list from a file

void Print_List(list* head)
{
	printf("\n");
	for (list* node = head; node != NULL; node = node->next)
	{
		printf("%s %s %s %s %d %d %d\n", node->group, node->surname, node->name, node->patronymic, node->mark1, node->mark2, node->mark3);
	}

}
//function to print the list to the console

void Print_Massive_List(list** head, int q)
{
	for (int i = 0; i < q; i++)
	{
		list* test_1 = head[i];
		if (test_1 != NULL)
		{
			Print_List(test_1);
			printf("\n");
		}
	}

}
//function to output an array of lists

void Push_Back(list* head_ref, char* group, char* surname, char* name, char* patronymic, int mark1, int mark2, int mark3)
{

	list* new_node = (list*)malloc(sizeof(list));
	list* last = head_ref;

	new_node->group = group;
	new_node->surname = surname;
	new_node->name = name;
	new_node->patronymic = patronymic;
	new_node->mark1 = mark1;
	new_node->mark2 = mark2;
	new_node->mark3 = mark3;

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
//function to insert a new node into the list (at the end of the list)


list** Create_And_Print_Massive_List(list* head)
{
	char* groups_massive[100];
	list* head1 = head;
	int i = 0;
	int k = 0;

	while (head1 != NULL)
	{
		groups_massive[i] = head1->group;
		head1 = head1->next;
		i++;

	}

	//sort group numbers
	char* tmp;
	for (int p = 0; p < i - 1; p++)
	{
		//compare two neighboring elements
		for (int j = 0; j < i - p - 1; j++)
		{
			if (strcmp(groups_massive[j], groups_massive[j + 1]) > 0)
			{
				// if they are in the wrong order, then swap them
				tmp = groups_massive[j];
				groups_massive[j] = groups_massive[j + 1];
				groups_massive[j + 1] = tmp;
			}
		}
	}
	groups_massive[i] = '\0';

	char* groups_massive_dif[100]; //group numbers without repeats

	int g = 0;
	int q = 0; //number of groups
	while (g < i)
	{
		for (g = 0; g < i; g++)
		{
			if (groups_massive[g + 1] != '\0')
			{
				if (strcmp(groups_massive[g], groups_massive[g + 1]) != 0)
				{
					groups_massive_dif[q] = groups_massive[g];
					q++;
				}
			}
			else
			{
				groups_massive_dif[q] = groups_massive[g];
				q++;
			}
		}
	}
	
	list* massive_list[NUMBER_GROUPS];//an array of lists (each list in it is students from the same group)

	//now fill the array of lists with elements (lists)
	int m = 0;
	list* head2 = head;
	int flag_1 = 0;
	for (int n = 0; n < q; n++)
	{
		while (head2 != NULL)
		{
			if (strcmp(head2->group, groups_massive_dif[m]) == 0)
			{
				massive_list[n] = Create_Node(head2->group, head2->surname, head2->name, head2->patronymic, head2->mark1, head2->mark2, head2->mark3);
				head2 = head2->next;
				while (head2 != NULL)
				{
					flag_1 = 1;
					if (strcmp(head2->group, groups_massive_dif[m]) == 0)
					{
						Push_Back(massive_list[n], head2->group, head2->surname, head2->name, head2->patronymic, head2->mark1, head2->mark2, head2->mark3);
					}
					head2 = head2->next;
				}
				m++;

			}
		    if ((flag_1 != 1) && (head2 != NULL))
				head2 = head2->next;
		}

		head2 = head;
		flag_1 = 0;

	}

	Print_Massive_List(massive_list, q);

}
//a function to create an array of lists and output it to the console

void Add_Student(list* head)
{
	int mark1;
	int mark2;
	int mark3;
	char* group = malloc(LINE_LENGTH * sizeof(char));
	char* surname = malloc(LINE_LENGTH * sizeof(char));
	char* name = malloc(LINE_LENGTH * sizeof(char));
	char* patronymic = malloc(LINE_LENGTH * sizeof(char));
	group = "3";
	surname = "Pushkin";
	name = "Alexander";
	patronymic = "Sergeevich";
	mark1 = 1;
	mark2 = 2;
	mark3 = 3;

	Push_Back(head, group, surname, name, patronymic, mark1, mark2, mark3);
	Create_And_Print_Massive_List(head);
}
//a function to add a student to an array of lists and output the resulting array to the console

void Delete_Student(list* head)
{
	list* head1 = head;
	int mark1_del;
	int mark2_del;
	int mark3_del;
	char* group_del = malloc(LINE_LENGTH * sizeof(char));
	char* surname_del = malloc(LINE_LENGTH * sizeof(char));
	char* name_del = malloc(LINE_LENGTH * sizeof(char));
	char* patronymic_del = malloc(LINE_LENGTH * sizeof(char));
	group_del = "5";
	surname_del = "Ivchenko";
	name_del = "Alexey";
	patronymic_del = "Vladimirovich";
	mark1_del = 3;
	mark2_del = 3;
	mark3_del = 4;
	int flag = 0;

	while (head1 != NULL)
	{
		while (flag != 1)
		{

			if ((strcmp(head1->next->group, group_del) == 0) && (strcmp(head1->next->surname, surname_del) == 0) && (strcmp(head1->next->name, name_del) == 0) && (strcmp(head1->next->patronymic, patronymic_del) == 0) && (head1->next->mark1 == mark1_del) && (head1->next->mark2 == mark2_del) && (head1->next->mark3 == mark3_del))
			{
				list* head1_del = head1->next;
				if (head1->next != NULL)
				    head1->next = head1->next->next;
				free(head1_del);
				flag = 1;
			}
			if (flag != 1)
				head1 = head1->next;
		}
		break;
	}
	Create_And_Print_Massive_List(head);
}
//a function for deleting a student into an array of lists and outputting the resulting array to the console


void Stipendia(list* head)
{
	int flag = 0;
	list* stipendia = (list*)malloc(sizeof(list));
	
		list* head1 = head;
		while (head1 != NULL)
		{


			if ((flag > 0) && (((head1->mark1) + (head1->mark2) + (head1->mark3)) / 3 > 3.5))
			{
				Push_Back(stipendia, head1->group, head1->surname, head1->name, head1->patronymic, head1->mark1, head1->mark2, head1->mark3);
			}
			if ((flag == 0) && (((head1->mark1) + (head1->mark2) + (head1->mark3)) / 3 > 3.5))
			{
				stipendia = Create_Node(head1->group, head1->surname, head1->name, head1->patronymic, head1->mark1, head1->mark2, head1->mark3);
				flag++;

			}

			head1 = head1->next;
		}
	
	Create_And_Print_Massive_List(stipendia);
	free(stipendia);
}
//a function to get an array of lists of students whose score is higher than 3.5 (scholarship) and output the resulting array to the console

void Otchislenie(list* head)
{
	int flag = 0;
	list* otchislenie = (list*)malloc(sizeof(list));

	list* head1 = head;
	while (head1 != NULL)
	{
		if ((flag > 0) && (((head1->mark1) + (head1->mark2) + (head1->mark3)) / 3 < 2.5))
		{
			Push_Back(otchislenie, head1->group, head1->surname, head1->name, head1->patronymic, head1->mark1, head1->mark2, head1->mark3);
		}
		if ((flag == 0) && (((head1->mark1) + (head1->mark2) + (head1->mark3)) / 3 < 2.5))
		{
			otchislenie = Create_Node(head1->group, head1->surname, head1->name, head1->patronymic, head1->mark1, head1->mark2, head1->mark3);
			flag++;

		}
		head1 = head1->next;
	}

	Create_And_Print_Massive_List(otchislenie);
	free(otchislenie);
}
//a function to get an array of lists of students whose score is below 2.5 (dropout) and output the resulting array to the console


void All_Operations(FILE* file)
{
	list* list_1 = Create_List_From_File(file);
	printf("List from file (group number, full name, 3 marks):\n");
	Print_List(list_1);
	printf("--------------------------------------------------------------------\n");
	printf("Output of an array of lists (sorted by groups, in each group alphabetically):\n");
	Create_And_Print_Massive_List(list_1);
	printf("--------------------------------------------------------------------\n");
	printf("Output of an array of lists with the addition of a student (3 Pushkin Alexander Sergeevich 1 2 3):\n");
	Add_Student(list_1);
	printf("--------------------------------------------------------------------\n");
	printf("Output of an array of lists with the deleting of a student (5 Ivchenko Alexey Vladimirovich 3 3 4):\n");
	Delete_Student(list_1);
	printf("--------------------------------------------------------------------\n");
	printf("Output an array of lists with students whose average mark is >3.5 (scholarship):\n");
	Stipendia(list_1);
	printf("--------------------------------------------------------------------\n");
	printf("Output an array of lists with students whose average mark <2.5 (drop out):\n");
	Otchislenie(list_1);
	printf("--------------------------------------------------------------------\n");

	free(list_1);
	fclose(file);
}
//function to call all other functions