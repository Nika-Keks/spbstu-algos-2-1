#pragma warning(disable : 4996)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>


typedef struct s_List
{
	char* word;
	char* number;

	struct s_List* next;

}t_List;

t_List* create_node(char* set_word, char* set_number)
{
	t_List* node = (t_List*)malloc(sizeof(t_List));
	node->word = set_word;
	node->number = set_number;
	node->next = NULL;

	return node;

}

void push_front(t_List** list, char* set_word, char* set_number)
{
	t_List* new_element = create_node(set_word, set_number);

	new_element->next = *list;
	*list = new_element;
}






