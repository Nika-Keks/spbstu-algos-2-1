#pragma once

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


Listptr CreateList();
void DeleteList(Listptr* list);
void pushFront(Listptr list, void* data, int size);
void pushBack(Listptr list, void* value, int size);
Nodeptr GetNth(Listptr list, int index);
void Insert(Listptr list, int index, int size, void* value);
void PrintList(Nodeptr current);
int IsEmpty(Nodeptr Sptr);
void bestfit(Listptr list, int value);






