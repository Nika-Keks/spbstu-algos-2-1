#pragma once
typedef struct List
{
    int number;
    int flag;
    struct List* next;
}List;

List* m_alloc_block(size_t size, int N);// allocation memory for a block
List* m_alloc(size_t size, int N);//allocation memory by equal blocks
List* m_creation(int number, size_t size, int N);// creation new element of list
void m_free(List* lister);// pushing elemet into free space
void push(List** head, int number, size_t size, int N); // pushing new element into list
List* delete(List* lister);// delete the element
void printer(List* lister);// output