#include <stdlib.h>

//Создание нового списка
Node* List_create() {
  Node* head = malloc(sizeof(Node));
  return head;
}

//Получение последнего элемента списка
Node* List_last(Node* head) {
  while (head->next) {
    head = head->next;
  }
  return head;
}

//Добавление элемента в конец списка
void List_append(Node* head, int x, int y) {
  if (!head->x && !head->y) {
    head->x = x;
    head->y = y;
  } else {
    Node* last = List_last(head);
    Node* next = malloc(sizeof(Node));
    next->x = x;
    next->y = y;
    last->next = next;
  }
}

//Удаление списка
void List_destroy(Node *head){
  Node *temp;

  while (head)
  {
    temp = head;
    head = head->next;
    free(temp);
  }
}

//Копирование списка
Node* List_clone(Node* head) {
  Node* clone_head = List_create();

  while (head) {
    List_append(clone_head, head->x, head->y);
    head = head->next;
  }

  return clone_head;
}
