#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
	
    int size = 50;
    int n = 16;
    list* test = create_node(n,size); // ������� ����
    for (int i = 1; i < n; i++) // ��������� �������� � ������
    {
        push(test,i,size);
    }
    print(test);
    printf("\n");
   
    test=delete(test); //������� ���� ������� �� �����
    print(test);
}