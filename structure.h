#pragma once
typedef struct list
{
	char* word;
	int number;
	struct list* next;
}list;

list* Create_Node(char* word, int number);
list* Create_Node_From_File(FILE* file, char* format);
list* Insert(list* list_1, list* list_2);
list* Create_List_From_File(FILE* file);
void Print_List(list* head);
list* Combine_Words_List(list* head);
void Checkword(list* head, char word[]);
void SearchWords(list* head, int num);
void Sort_And_Search(FILE* file);
void Push_Back(list* list, char* set_word, int set_number);
