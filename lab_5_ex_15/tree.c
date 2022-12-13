#include <stdlib.h>
#include "tree.h"

int id = 0;

Node* Tree_create_node(int value, Node* parent, Node* leftChild, Node* rightChild) {
  Node* root = malloc(sizeof(Node));
  root->id = id++;
  root->value = value;
  root->parent = parent;
  root->leftChild = leftChild;
  root->rightChild = rightChild;
  return root;
}

void Tree_delete_node(Node* node) {
  if (node->leftChild) {
    Tree_delete_node(node->leftChild);
  }
  if (node->rightChild) {
    Tree_delete_node(node->rightChild);
  }

  if (node->parent) {
    if (node->parent->leftChild == node) {
      node->parent->leftChild = NULL;
    } else if (node->parent->rightChild == node) {
      node->parent->rightChild = NULL;
    }
    node->parent = NULL;
  }

  free(node);
}

void Tree_print_rec(Node* node, int space) {
  if (!node) {
    return;
  }

  space += 10;

  Tree_print_rec(node->rightChild, space);

  printf("\n");
  for (int i = 10; i < space; i += 1) {
    printf(" ");
  }

  printf("%d (%d)\n", node->value, node->id);

  Tree_print_rec(node->leftChild, space);
}

void Tree_print(Node* node) {
  Tree_print_rec(node, 0);
}
