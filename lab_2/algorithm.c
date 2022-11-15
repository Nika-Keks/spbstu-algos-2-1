#include <stdio.h>
#include <malloc.h>
#include "struct.h"

#define number_elem 10  //number of elements in a block
#define size_elem 20    //size of one block element
list* p = NULL;         //current pointer

list* Create_Node(char block_name)
{
    list* node = m_alloc(size_elem);  //allocate the first memory block of size "size" for the list node
    node->block_name = block_name;
    node->next = NULL;

    return node;
}
//list node creation function

list* m_alloc() 
{
    if (p == NULL)
    {    
        list* head = malloc(number_elem * size_elem);
        list* head1 = head;
        for (int i = 0; i < number_elem - 1; i++) 
        {
            if (head1 != NULL)
            {
                head1->next = (int*)head1 + size_elem;
                head1 = head1->next;
            }
        }
        head1->next = NULL;
        p = head;
    }

    list* p1 = p;
    p->flag = 1; //a block with elements has been created, set the busy flag to it 1
    p = p->next;

    return p1;
}
//function to allocate memory in blocks of the same size

list* m_free(list* head)
{
    list* head1 = head->next;
    head->next = p;
    p->flag = 0;  //the block with elements is deleted, set the busy flag 0 to it
    return(head1);
}
//function to delete a block from the list

void Push_Block(list** head, char block_name) 
{
    list* sup = m_alloc();
    sup->block_name = block_name;
    sup->next = *head;
    *head = sup;
}
//function to add a block to the list

void Print(list* head)
{
    list* head1 = head;

    while (head1 != NULL)
    {
        printf("%c ", head1->block_name);
        head1 = head1->next;
    }
}
//list print function
