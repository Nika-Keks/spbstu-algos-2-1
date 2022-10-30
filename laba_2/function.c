#include <stdio.h>
#include <malloc.h>
#include "function.h"

int amount_element = 8; // ���������� ���������� �� ���-�� ��������� � �����
list* ptr = NULL; //������� ��������� �� ��������� �������

/*
* ������� ���� ������ �������� ������ ������ �����
* ��������� ���������� �� ������
* ����� ���������� � ����� ��������
* ���������� ��������� �� ����
*/
list* malloc_block(size_t size) //��������� ������ �����
{
    size_t block_size = amount_element * size;
    list* head = (list*)(malloc(block_size));
    if (head == NULL) // �������� ���������� �� ������
    {
        printf("Error");
        exit(1);
    }
    list* list_n = head;
    for (int i = 0; i < amount_element - 1; ++i) // ���������� ����� �� ��������
    {
        list_n->next = (list*)((char*)(list_n) + size);
        list_n = list_n->next;
    }
    list_n->next = NULL;
    return head;
}
/*
* ������� ��������� ������ ������� ����������� �������
* ������� �������� ������ ������ �������� �����
* ��������� ���� �� ��������� �������
* ����� �������� ��������� �� ���� ������� ������������
* � ������������� ���� ��������� 1
*/
list* malloc_new(size_t size) // ������� ��������� ������ ������� ����������� �������
{
    if (ptr == NULL) //�������� ���� �� ��������� �����, ���� ��� ���������� ��� ���� ����
    {
        ptr = malloc_block(size);

    }
    
    list* user_element = ptr;
    ptr->flag = 1;
    ptr= ptr->next;
    return user_element;
}
/*
* �������� ��������� �� �������
* ��������� ��� � ������ ���������� ������������
* ������������� ���� ��������� 0 
*/
void free_new(list* user_element) // ������� ���������� �������� � ������ ���������� ������������
{
    (list*)(user_element->next) = ptr;
    ptr = (list*)(user_element);
    ptr->flag = 0;
}



void push(list** list_n, int ch, size_t size) // ������� ���������� �������� � ������
{
    list* sup = (list*)malloc_new(size);
    sup->chislo = ch;
    sup->next = *list_n;
    *list_n = sup;
}

list* create_node( int ch,size_t size) //������� �������� ���� ������
{
    list* node = (list*)malloc_new(size);
    node->chislo = ch;
    node->next = NULL;
    return node;

}

void print(list* list_n) // ������� ������ ������ �� �����
{
    list* test_1 = list_n;
    do
    {
        printf("%i  ", test_1->chislo);
        test_1 = test_1->next;
    } while (test_1 != NULL);
}

list* delete(list* list_n) // ������� �������� �������� �� ������
{
    list* test_1=list_n->next;
    free_new(list_n);
    return(test_1);
}



