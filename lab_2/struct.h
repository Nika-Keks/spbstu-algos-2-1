#pragma once
typedef struct list 
{
    char block_name;
    int flag;
    struct list* next;
}list;

list* m_alloc();
list* m_free(list* head);
list* Create_Node(char block_name);
void Push_Block(list** head, char block_name);
void Print(list* head);
