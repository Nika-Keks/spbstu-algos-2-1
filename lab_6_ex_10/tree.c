#include <stdlib.h>
#include "tree.h"

Node* Tree_create_node(int value, Node* parent, Node* left_child, Node* right_child) {
  Node* root = malloc(sizeof(Node));
  root->value = value;
  root->parent = parent;
  root->left_child = left_child;
  root->right_child = right_child;
  return root;
}

int Random_int(int min, int max) {
  return min + ((double)rand() / (double)RAND_MAX) * (max - min + 1);
}

Node* Tree_generate_random_node(int depth, int min, int max) {
  if (depth > 5) {
    return NULL;
  }

  Node* node = malloc(sizeof(Node));
  node->value = Random_int(min, max);

  node->left_child = Tree_generate_random_node(depth + 1, min, node->value - 1);
  node->right_child = Tree_generate_random_node(depth + 1, node->value, max);

  return node;
}

Node* Tree_generate_random() {
  srand(time(NULL));

  return Tree_generate_random_node(0, 0, 1000000);
}

void Tree_print_rec(Node* node, int space) {
  if (!node) {
    return;
  }

  space += 10;

  Tree_print_rec(node->right_child, space);

  printf("\n");
  for (int i = 10; i < space; i += 1) {
    printf(" ");
  }

  printf("%d\n", node->value);

  Tree_print_rec(node->left_child, space);
}

void Tree_print(Node* node) {
  Tree_print_rec(node, 0);
}