#pragma once

typedef struct Node
{

    char *word;
    int number;
    struct Node *next;

} Node;

// Создаем один пустой элемент списка
Node *List_create();
