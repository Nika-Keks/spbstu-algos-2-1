#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tree.h"

int Get_number_length(int number) {
  int length = 1;
  while (number >= 10) {
    length++;
    number /= 10;
  }
  return length;
}

void Find_node_by_value_rec(Node* node, int value, Node** result_node) {
  if (!node || *result_node) {
    return;
  }

  if (node->value == value) {
    *result_node = node;
  } else if (node->value > value) {
    Find_node_by_value_rec(node->left_child, value, result_node);
  } else {
    Find_node_by_value_rec(node->right_child, value, result_node);
  }
}

Node* Find_node_by_value(Node* rootNode, int value) {
  Node* result_node = NULL;

  Find_node_by_value_rec(rootNode, value, &result_node);

  return result_node;
}

void Find_node_by_order_rec(Node* node, int length, Node** result_node) {
  if (!node || *result_node) {
    return;
  }

  int nodeLength = Get_number_length(node->value);

  if (nodeLength == length) {
    *result_node = node;
  } else if (nodeLength > length) {
    Find_node_by_order_rec(node->left_child, length, result_node);
  } else {
    Find_node_by_order_rec(node->right_child, length, result_node);
  }
}

Node* Find_node_by_order(Node* rootNode, int value, int k) {
  Node* result_node = NULL;

  Find_node_by_order_rec(rootNode, Get_number_length(value) - k, &result_node);

  return result_node;
}

Node* Get_node(Node* rootNode) {
  int number;
  Node* node;

  printf("Введите число из бинарного дерева: ");
  scanf("%d", &number);

  while (!(node = Find_node_by_value(rootNode, number))) {
    printf("Это число не существует\n");
    printf("Введите число: ");
    scanf("%d", &number);
  }

  return node;
}

int Get_k() {
  int k;

  printf("Введдите K: ");
  scanf("%d", &k);

  return k;
}