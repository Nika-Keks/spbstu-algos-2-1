#pragma once

typedef struct _Node {
    void* memory;
    int size;
    struct _Node* next;
    struct _Node* prev;
} Node;

typedef Node* Node_ptr;

typedef struct _Listlink {
    int size;
    Node_ptr head;
    Node_ptr tail;
} Listlink;

typedef Listlink* List;

void Print_List(List list);
List Create_List();
void Delete_List(List* list);
void Insert(List list, int idx, void* memory, int size);
void BestFit(List list, int bytes);
