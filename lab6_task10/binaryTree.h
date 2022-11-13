#pragma once

typedef struct Node {
  int value;
  struct Node* parent;
  struct Node* leftChild;
  struct Node* rightChild;
} Node;

int randomInt(int min, int max);

Node* generateRandomNode(int depth, int minValue, int maxValue);

Node* generateRandomBinarySearchTree();

void printBinaryTreeUtil(Node* root, int space);

void printBinaryTree(Node* root);
