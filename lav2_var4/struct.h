#pragma once

typedef struct _List {
	int  size;//size of memory
	int flag; //if flag = -1 memory is allocated, if flag = 1 memory ia free
	struct _Direction* next;
	struct _Direction* prev;
}List;

List* create_memory(int ch, size_t size); //create free space list
void pick_out_memory(size_t size, List* list); // allocate memory to a user from the free space list
void print(List* list_n); // print the list on the screen
void insert_before(List* head);// the function inserts an element into the free space list and concatenates it with the previous one
void insert_after(List* head);// the function inserts an element into the free space list and concatenates it with the next one
List* delete(List* list, int n);//the function inserts an element into the free space list
void checkup(List* list_n); //check up integrity


