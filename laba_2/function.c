#include <stdio.h>
#include <malloc.h>
#include "function.h"

int amount_element = 8; // переменная отвечающая за кол-во элементов в блоке
list* ptr = NULL; //текущий указатель на свободный элемент

/*
* создаем узел списка выделяем память целого блока
* проверяем выделилась ли память
* затем резервирую в блоке элементы
* возвращаем указатель на блок
*/
list* malloc_block(size_t size) //выделение памяти блоку
{
    size_t block_size = amount_element * size;
    list* head = (list*)(malloc(block_size));
    if (head == NULL) // проверка выделилась ли память
    {
        printf("Error");
        exit(1);
    }
    list* list_n = head;
    for (int i = 0; i < amount_element - 1; ++i) // разделение блока на элементы
    {
        list_n->next = (list*)((char*)(list_n) + size);
        list_n = list_n->next;
    }
    list_n->next = NULL;
    return head;
}
/*
* функция выделения памяти блоками одинакового размера
* входной параметр размер одного элемента блока
* проверяем есть ли свободный элемент
* затем передаем указатель на этот элемент пользователю
* и устанавливаем флаг занятости 1
*/
list* malloc_new(size_t size) // функция выделения памяти блоками одинакового размера
{
    if (ptr == NULL) //проверка есть ли свободное место, еслт нет выделяется еще один блок
    {
        ptr = malloc_block(size);

    }
    
    list* user_element = ptr;
    ptr->flag = 1;
    ptr= ptr->next;
    return user_element;
}
/*
* получаем указатель на элемент
* добавляем его в список свободного пространства
* устанавливаем флаг занятости 0 
*/
void free_new(list* user_element) // функция добавления элемента в список свободного пространства
{
    user_element->next = ptr;
    ptr =user_element;
    ptr->flag = 0;
}



void push(list** list_n, int ch, size_t size) // функция добавления элемента в список
{
    list* sup = (list*)malloc_new(size);
    sup->chislo = ch;
    sup->next = *list_n;
    *list_n = sup;
}

list* create_node( int ch,size_t size) //функция создания узла списка
{
    list* node = (list*)malloc_new(size);
    node->chislo = ch;
    node->next = NULL;
    return node;

}

void print(list* list_n) // функция вывода списка на экран
{
    list* test_1 = list_n;
    do
    {
        printf("%i  ", test_1->chislo);
        test_1 = test_1->next;
    } while (test_1 != NULL);
}

list* delete(list* list_n) // функция удаления элемента из спсика
{
    list* test_1=list_n->next;
    free_new(list_n);
    return(test_1);
}



