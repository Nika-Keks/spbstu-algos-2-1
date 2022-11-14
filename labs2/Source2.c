#include<stdio.h>
#include<stdlib.h>
#define INF 1000000000
#pragma warning (disable:4996)


//the node of the list that stores the memory
//that we have to perform some process
//and the size in bytes of a piece of allocated memory
//pointers to the trace and the previous node of the list
typedef struct Node {
	void* memory;
	int size;
	struct Node* next;
	struct Node* prev;
}Node;
typedef Node* Nodeptr;


//The "Doubly Linked List" structure will store its size (so as not to recalculate the number of elements each time),
//as well as the head pointer referring to the first element and the tail pointer referring to the last element
typedef struct List {
	size_t size;
	Nodeptr tail;
	Nodeptr head;
}List;
typedef struct List* Listptr;

//the function creates our sheet
Listptr CreateList() {
	Listptr tmp = (Listptr)malloc(sizeof(List));
	if (tmp != NULL) {
		tmp->size = 0;
		tmp->tail = tmp->head = NULL;
	}
	return tmp;
}

// At the same time, we will describe the function that deletes the list
void DeleteList(Listptr* list) {
	Nodeptr tmp = (*list)->head;
	Nodeptr next = NULL;
	while (tmp != NULL) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}


//the function is needed in order to insert an item at the beginning of the list
void pushFront(Listptr list, void* data, int size) {
	Nodeptr tmp = (Nodeptr)malloc(sizeof(Node));
	if (tmp == NULL) {
		printf("no memory available.\n");
	}
	else {
		tmp->memory = data;
		tmp->size = size;
		tmp->prev = NULL;
		tmp->next = list->head;

		if (list->head) {
			list->head->prev = tmp;
		}
		list->head = tmp;
		if (list->tail == NULL) {
			list->tail = tmp;
		}
		list->size++;
	}
}



//the function is needed in order to insert an item at the end of the list
void pushBack(Listptr list, void* value, int size) {
	Nodeptr tmp = (Nodeptr)malloc(sizeof(Node));
	if (tmp == NULL) {
		printf("No memory available.");
	}
	else {
		tmp->memory = value;
		tmp->size = size;
		tmp->next = NULL;
		tmp->prev = list->tail;
		if (list->tail) {
			list->tail->next = tmp;
		}
		list->tail = tmp;

		if (list->head == NULL) {
			list->head = tmp;
		}
		list->size++;
	}
}

//Getting the nth item in the list
Nodeptr GetNth(Listptr list, int index) {
	Nodeptr tmp = list->head;
	int i = 0;
	while (tmp != NULL && i < index) {
		tmp = tmp->next;
		i++;
	}
	return tmp;
}

//a universal function for inserting a node into a list that takes as input
//a pointer to a sheet, the position where the node should be inserted and the memory allocated for the process with its size
void Insert(Listptr list, int index, int size, void* value) {
	Nodeptr elm = NULL;//pointer to the element after which we will insert a new node
	Nodeptr ins = NULL;//pointer to a new node
	if (list->size == 0) {//if the list size is 0, then we call the function
						  //push front which adds a node to the top of the list
		pushFront(list, value, size);
	}
	else {

		elm = GetNth(list, index);
		if (elm == NULL) {//if the function returns a pointer to NULL, then insert the node at the end of the list
			pushBack(list, value, size);
		}
		else {
			ins = (Nodeptr)malloc(sizeof(Node));
			if (ins != NULL) {
				ins->memory = value;
				ins->size = size;
				ins->prev = elm;
				ins->next = elm->next;
				if (elm->next) {
					elm->next->prev = ins;
				}
				elm->next = ins;

				if (!elm->prev) {
					list->head = elm;
				}
				if (!elm->next) {
					list->tail = elm;
				}
			}
			else {
				printf("No memory available.");
			}
		}
	}
	list->size++;
}

//the function prints our list
void PrintList(Nodeptr current) {
	if (IsEmpty(current)) {
		printf("The list is empty.\n");
	}
	else {
		printf("The list is: ");
		while (current != NULL) {
			printf("%d ", current->size);
			current = current->next;
		}
		puts("");
	}
}

//checks if the list is empty
int IsEmpty(Nodeptr Sptr) {
	return (int)(Sptr == NULL);
}

//a function that allocates memory for some processes
// that require memory, the memory spent on these processes
// is allocated for them according to the best fit principle
void bestfit(Listptr list, int value)
{
	Nodeptr ptr = NULL;
	int min = INF;
	int tmp;
	Nodeptr currentPtr = list->head;
	//in this loop, we are trying to determine which memory block has the smallest size in bytes
    //and at the same time it still has no less memory than is required for the process
	while (currentPtr != NULL) {
		tmp = currentPtr->size - value;
		if (min > tmp && tmp >= 0) {
			min = tmp;
			ptr = currentPtr;
		}
		currentPtr = currentPtr->next;
	}
	if (min == INF) { printf("No suitable memory block\n"); }
	//here we take away the amount of memory in bytes from the block that passed the selection described above
    //consumed by the process
	else {
		ptr->size = ptr->size - value;
		if (ptr->size == 0) {
			ptr->memory = NULL;
		}
		else {
			//reallocating memory to control the amount of memory that remains
			void* PTR = (void*)realloc(ptr->memory, ptr->size);
			if (PTR != NULL) {
				ptr->memory = PTR;
			}
			else { printf("Memory is not reallocted\n"); }
		}
	}
}