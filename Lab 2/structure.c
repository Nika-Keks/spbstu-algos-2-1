#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Lib.h"

List* ptr = NULL;


List* m_alloc_block(size_t size, int N)// allocation memory for a block
{
	size_t size_block = size * N;
	List* head;
	if (!(head = (List*)malloc(size_block)))
	{
		printf("Allocation error.");
		exit(1);
	}
	List* lister = head;
	for (int i = 1;i < N ;i++)
	{
		lister->next = (List*)((char*)lister + size);
		lister = lister->next;
	}
	lister->next = NULL;
	return head;
}

List* m_alloc(size_t size, int N)//allocation memory by equal blocks
{
	if (ptr == NULL)
		ptr = m_alloc_block(size, N);
	List* head = ptr;
	ptr->flag = 1;
	ptr = ptr->next;
	return head;
}

List* m_creation(int number, size_t size, int N)// creation new element of list
{
	List* lister = m_alloc(size, N);
	lister->number = number;
	lister->next = NULL;
	return lister;
}

void m_free(List* lister)// pushing elemet into free space
{
	lister->next = ptr;
	ptr = lister;
	ptr->flag = 0;
}

void push(List** head, int number, size_t size, int N) // pushing new element into list
{
	List* lister = m_alloc(size, N);
	lister->number = number;
	lister->next = *head;
	*head = lister;
}

List* delete(List* lister)// delete the element
{
	List* head = lister->next;
	m_free(lister);
	return head;
}

void printer(List* lister)// output
{
	List* head = lister;
	while (head != NULL)
	{
		printf(" %d ",head->number);
		head = head->next;
	}
	printf("\n");
}

