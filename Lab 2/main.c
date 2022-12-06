#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "Lib.h"

int main(void)
{
    int size = 100;
    int n = 24;
    int N = 9;
    List* head;
    for (int i = 1; i < n; i++) // filling list 
    {
        if (i == 1)
        {
            head = m_creation(1, size, N);
            continue;
        }
        push(&head, i, size, N);
    }
    printer(head);
    head = delete(head); //delete one element
    printer(head);
}