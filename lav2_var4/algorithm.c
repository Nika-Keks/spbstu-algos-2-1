#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"



//create free space list
List* create_memory(int ch, size_t size) {
	List* memory = (List*)malloc(size);
	memory->next = NULL;
	memory->flag = 1;
	memory->size = size;
	memory->prev = NULL;
	return memory;
}

// allocate memory to a user from the free space list
void pick_out_memory(size_t size, List* list) {
	List* head = (List*)malloc(sizeof(List));
	head = list;
	//checking if there is free space in the free space list
	while (head->next != NULL) {
		if ((head->flag == 1) && (head->size > size)) {
			break;
		}
		head = head->next;
	}

	//if there is not enough memory
	if ((head->next == NULL) && ((head->flag == -1) || (head->size < size))) {
		printf("Not enough memory\n");
	}

	//give memory to user
	if (head->size == size) {
		head->flag = -1;
		printf("Memory of size %d is allocated  with address:  % p\n", size, head);
	}
	else if (head->size > size) {
		List* tmp = (List*)malloc(sizeof(List));
		int t = head->size;
		tmp->size = t - size;
		tmp->flag = 1;
		tmp->next = head->next;
		tmp->prev = head;
		head->next = tmp;
		head->size = size;
		head->flag = -1;
		printf("Memory of size %d is allocated  with address:  % p\n", size, head);
		head = head->next;
	}
}

// print the list on the screen
void print(List* list_n) {
	List* tmp = list_n;
	do
	{
		printf("Area of size %d with address %p ", tmp->size, tmp);
		if (tmp->flag == -1) printf("is allocated to the user\n");
		else if (tmp->flag == 1) printf("is free\n");
		tmp = tmp->next;
	} while (tmp != NULL);
}

// the function inserts an element into the free space list and concatenates it with the previous one
void insert_before(List* head) {
	int y = head->size;
	List* t = head->next;
	head = head->prev;
	head->size = y + head->size;
	head->next = t;
}

// the function inserts an element into the free space list and concatenates it with the next one
void insert_after(List* head) {
	head = head->next;
	int y = head->size;
	List* t = head->next;
	head = head->prev;
	head->size = y + head->size;
	head->next = t;
	head->flag = 1;
	t = head;
	head = head->next;
	head->prev = t;
}

//the function inserts an element into the free space list
List* delete(List* list, int n) {
	List* head = (List*)malloc(sizeof(List));
	head = list;
	int i = 1;

	//find the element before the element that should be inserted into the free space list
	while (i < (n - 1)) {
		head = head->next;
		i++;
	}

	//before the inserted element the memory is free
	if (head->flag == 1) {
		head = head->next;
		insert_before(head);
		head = head->next;

		//after the inserted element the memory is free
		if (head->flag == 1) {
			insert_after(head);
		}

		//there is no free memory after the inserted element
		else {
			head = head->prev;
			head->flag = 1;
		}
	}
	else {
		head = head->next;
		head = head->next;

		//after the inserted element the memory is free
		if (head->flag == 1) {
			head = head->prev;
			insert_after(head);
		}

		//there is no free memory near to the inserted element at all
		else {
			head = head->prev;
			head->flag = 1;
		}
	}
	return list;
}

//check up integrity
void checkup(List* list_n) {
	List* tmp = list_n;
	int all = 0; //all memory
	int applied = 0;//applied memory
	int free = 0;//free memory
	do {
		if (tmp->flag == 1) free = free + tmp->size;
		if (tmp->flag == -1) applied = applied + tmp->size;
		all = all + tmp->size;
		tmp = tmp->next;

	} while (tmp != NULL);

	printf("Free memory: %d\n", free);
	printf("Applied memory: %d\n", applied);
	printf("All  memory : %d\n", all);
	int loosed = all - applied - free;
	printf("Loosed memory: %d - %d - %d = %d\n", all, applied, free, loosed);
}

