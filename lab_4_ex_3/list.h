#pragma once

//Узел списка, в котором храняться координаты
//Используется для истории ходов
typedef struct Node
{
    int x;
    int y;
    struct Node *next;
} Node;

Node *List_create();

Node *List_last(Node *head);

void List_append(Node *head, int x, int y);

void List_destroy(Node *head);

Node *List_clone(Node *head);