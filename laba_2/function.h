#pragma once
typedef struct list // create stucture list
{
    struct list* next;
    int chislo;
    int flag;
}list;


void free_new(list* user_element); 
list* malloc_new(size_t size);
list* malloc_block(size_t size);
void push(list** list_n, int ch, size_t size);
list* create_node(int ch, size_t size);
void print(list* list_n);
list* delete(list* list_n);
