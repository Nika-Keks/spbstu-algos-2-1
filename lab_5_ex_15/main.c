#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tree.c"

void Find_node_by_id_rec(Node* node, int id, Node** found_node) {
  if (*found_node || !node) {
    return;
  }

  if (node->id == id) {
    *found_node = node;
    return;
  }

  Find_node_by_id_rec(node->leftChild, id, found_node);
  Find_node_by_id_rec(node->rightChild, id, found_node);
}

Node* Find_node_by_id(Node* tree, int id) {
  Node* found_node = NULL;

  Find_node_by_id_rec(tree, id, &found_node);

  return found_node;
}

int Get_action() {
  printf("Выберите действие:\n");
  printf("0 - Создать\n");
  printf("1 - Создать левого наследника\n");
  printf("2 - Создать правого наследника\n");
  printf("3 - Удалить\n");
  int action;
  scanf("%d", &action);
  return action;
}

int Get_id() {
  printf("Введите номер узла: ");
  int id;
  scanf("%d", &id);
  return id;
}

int Get_node_value() {
  int root;
  printf("Введите значение узла: ");
  scanf("%d", &root);
  return root;
}
