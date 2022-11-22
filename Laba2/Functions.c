#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba2.h"
#pragma warning(disable:4996)

/*
* The function checks if the list is empty
*/
int isEmpty(Node_ptr a) {
    return a == NULL;
}

void Print(int a) {
    printf("%d\n", a);
}

/*
* Outputs all the words of the list (starting with the pointer that we will pass)
* If the list is empty, it outputs an error message
*/
void Print_List(List list) {
    Node_ptr cur = list->head;
    if (isEmpty(cur)) {
        puts("List is empty.");
    }
    else {
        puts("The list is:");
        while (cur != NULL) {
            Print(cur->size);
            cur = cur->next;
        }
    }
}

/*
* Creating a List
*/
List Create_List() {
    List tmp = (List)malloc(sizeof(Listlink));
    if (tmp == NULL) { printf("No memory avaible.\n"); return NULL; }
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}

/*
* Clearing the List
*/
void Delete_List(List* list) {
    Node_ptr tmp = (*list)->head;
    Node_ptr next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

/*
* Returns the nth element (if there is no such element, it will output to the last one)
*/
Node_ptr GetNth(List list, int idx) {
    if (idx < 0 || idx >= list->size) return NULL;
    Node_ptr tmp = list->head;
    for (int i = 0; tmp && i < idx; i++) tmp = tmp->next;

    return tmp;
}

/*
* Inserts the element after the idx element
* If idx = -1, it will insert at the beginning
* If idx = size, it will insert at the end
*/
void Insert(List list, int idx, void* memory, int size) {
    Node_ptr new_element = (Node_ptr)malloc(sizeof(Node));
    if (new_element == NULL) { printf("No memory avaible.\n"); return; }

    if (list->size == 0) { //inserting into an empty list
        new_element->memory = memory;
        new_element->size = size;
        new_element->prev = NULL;
        new_element->next = NULL;

        list->head = new_element;
        list->tail = new_element;
        list->size++;
        return;
    }
    if (idx == -1) { //insert at the beginning
        new_element->memory = memory;
        new_element->size = size;
        new_element->prev = NULL;
        new_element->next = list->head;

        list->head->prev = new_element;
        list->head = new_element;
        list->size++;
        return;
    }
    if (idx >= list->size) { // insert at the end
        new_element->memory = memory;
        new_element->size = size;
        new_element->prev = list->tail;
        new_element->next = NULL;

        list->tail->next = new_element;
        list->tail = new_element;
        list->size++;
        return;
    }

    // insert in the middle of the list
    Node_ptr prev_element = GetNth(list, idx);
    new_element->memory = memory;
    new_element->size = size;
    new_element->prev = prev_element;
    new_element->next = prev_element->next;

    if (prev_element->next) prev_element->next->prev = new_element;
    prev_element->next = new_element;

    list->size++;
}

// best fit memory allocation
void BestFit(List list, int bytes) {
    int MIN = INT_MAX;
    Node_ptr best = NULL;
    Node_ptr cur = list->head;
    while (cur) {
        if ((cur->size < MIN) && (cur->size >= bytes)) {
            MIN = cur->size;
            best = cur;
        }
        cur = cur->next;
    }
    if (best == NULL) printf("No suitble memory blocks.\n");
    else {
        best->size -= bytes;
        if (best->size == 0) { best->memory = NULL; return; }
        void* p = (void*)realloc(best->memory, best->size);
        if (p == NULL) printf("No memory reallocted");
        else best->memory = p;
    }
}