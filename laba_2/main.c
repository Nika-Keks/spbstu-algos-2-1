#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
	
    int size = 50;
    int n = 16;
    list* test = create_node(1,size); // create node
    for (int i = 2; i <= n; i++) // push elements into list
    {
        push(&test,i,size);
    }
    print(test);
    printf("\n");
   
    test=delete(test); //delete one element from list
    print(test);
}
