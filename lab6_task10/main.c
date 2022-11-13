#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "binaryTree.h"
#include "utils.h"

void findNodeByValueUtil(Node* node, int value, Node** resultNode) {
  if (!node || *resultNode) {
    return;
  }

  if (node->value == value) {
    *resultNode = node;
  } else if (node->value > value) {
    findNodeByValueUtil(node->leftChild, value, resultNode);
  } else {
    findNodeByValueUtil(node->rightChild, value, resultNode);
  }
}

Node* findNodeByValue(Node* rootNode, int value) {
  Node* resultNode = NULL;

  findNodeByValueUtil(rootNode, value, &resultNode);

  return resultNode;
}

void findValueWithDifferentOrderUtil(Node* node, int length, Node** resultNode) {
  if (!node || *resultNode) {
    return;
  }

  int nodeLength = getNumberLength(node->value);

  if (nodeLength == length) {
    *resultNode = node;
  } else if (nodeLength > length) {
    findValueWithDifferentOrderUtil(node->leftChild, length, resultNode);
  } else {
    findValueWithDifferentOrderUtil(node->rightChild, length, resultNode);
  }
}

Node* findValueWithDifferentOrder(Node* rootNode, int value, int k) {
  Node* resultNode = NULL;

  findValueWithDifferentOrderUtil(rootNode, getNumberLength(value) - k, &resultNode);

  return resultNode;
}

Node* getNode(Node* rootNode) {
  int number;
  Node* node;

  printf("Enter number from the binary tree: ");
  scanf("%d", &number);

  while (!(node = findNodeByValue(rootNode, number))) {
    printf("This number does not exist in the binary tree \n");
    printf("Enter number: ");
    scanf("%d", &number);
  }

  return node;
}

int getK() {
  int k;

  printf("Enter K: ");
  scanf("%d", &k);

  return k;
}
