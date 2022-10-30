#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
	
    int size = 50;
    int n = 16;
    list* test = create_node(n,size); // создаем узел
    for (int i = 1; i < n; i++) // добавляем элементы в список
    {
        push(test,i,size);
    }
    print(test);
    printf("\n");
   
    test=delete(test); //удаляем один элемент из спика
    print(test);
}