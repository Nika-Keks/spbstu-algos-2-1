#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

#define number_blocks 5 //number of blocks

int main()
{
    printf("Initial list of blocks         : ");
    char block[number_blocks] = {'E', 'D', 'C', 'B', 'A'}; //array of block names (A, B, C, D, E), each block is an element of the list
    list* head = NULL; //block list

    for (int i = 0; i < number_blocks; i++)                //create other blocks
    {
        if (i == 0)
            head = Create_Node(block[0]);                  //create a list node (block E)
        else
            Push_Block(&head, block[i]);                   //add a block to the list 
    }

    Print(head); 
    printf("\n");

    printf("List after deleting one block  : ");
    head = m_free(head); //delete one block (block A)
    Print(head);
    printf("\n");

}