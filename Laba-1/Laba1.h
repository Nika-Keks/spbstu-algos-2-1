#pragma once

typedef struct Node List;
typedef List* Listptr;

struct Node {
	char* a;
	int length;
	struct Node* next;
};

void list_free(MyList);
void PrintList(Listptr currentPtr);
void FIRST(Listptr currentPtr);
void SECOND(Listptr currentPtr);
Listptr ReadText(char const* filename);
int LEN(char* a);
int isEmpty(Listptr sPtr);
int comp(char* first, char* second, int length);
void Insert(char* a, int length, Listptr* Ptr);