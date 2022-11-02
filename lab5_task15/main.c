#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

typedef struct Node {
  int value;
	struct Node* parent;
	struct Node* leftChild;
	struct Node* rightChild;
} Node;

Node* treeCreateNode(int value) {
  Node* root = malloc(sizeof(Node));
  root->value = value;
  return root;
}

void treeDeleteNode(Node* node) {
  if (node->leftChild) {
    treeDeleteNode(node->leftChild);
  }
  if (node->rightChild) {
    treeDeleteNode(node->rightChild);
  }
  if (node->parent) {
    node->parent = NULL;
  }
  free(node);
}

int getNodeValueWidth(Node* node) {
  return node == NULL ? 0 : getNumberLength(node->value);
}

void displayNode(Node* node) {
  int parentWidth = getNodeValueWidth(node->parent);
  int nodeWidth = getNodeValueWidth(node);
  int leftWidth = getNodeValueWidth(node->leftChild);
  int rightWidth = getNodeValueWidth(node->rightChild);
  int childrenWidth = leftWidth + 3 + rightWidth;
  int maxWidth = max(max(parentWidth, nodeWidth), childrenWidth);
  int gapPadding = 3;

  printf("\n");

  if (node->parent) {
    int parentDelta = maxWidth - parentWidth;

    int numberPaddingLength = gapPadding + (parentDelta >= 0 ? parentDelta / 2 : 0);
    char *numberPadding = repeat(' ', numberPaddingLength);

    int edgePaddingLength = gapPadding + maxWidth / 2;
    char *edgePadding = repeat(' ', edgePaddingLength);

    printf("%s%d\n", numberPadding, node->parent->value);
    printf("%s|\n", edgePadding);

    free(numberPadding);
    free(edgePadding);
  }

  int nodeDelta = maxWidth - nodeWidth;

  int numberPaddingLength = gapPadding + (nodeDelta >= 0 ? nodeDelta / 2 : 0);
  char* numberPadding = repeat(' ', numberPaddingLength);

  printf("%s%d\n", numberPadding, node->value);

  free(numberPadding);

  if (node->leftChild || node->rightChild) {
    int edgesPaddingLength = gapPadding + maxWidth / 2 - 2;
    char* edgesPadding = repeat(' ', edgesPaddingLength);
    char leftEdge = node->leftChild ? '/' : ' ';
    char rightEdge = node->rightChild ? '\\' : ' ';

    printf("%s%c %c\n", edgesPadding, leftEdge, rightEdge);

    free(edgesPadding);

    int childrenDelta = maxWidth - childrenWidth;

    int childrenPaddingLength = childrenDelta >= 0 ? nodeDelta / 2 : 0;
    char* childrenPadding = repeat(' ', childrenPaddingLength);

    if (node->leftChild && node->rightChild) {
      printf("%s%d   %d\n", childrenPadding, node->leftChild->value, node->rightChild->value);
    } else if (node->leftChild) {
      printf("%s%d\n", childrenPadding, node->leftChild->value);
    } else {
      printf("%s    %d\n", childrenPadding, node->rightChild->value);
    }
  }

  printf("\n");
}

int getAction() {
  printf("Choose action:\n");
  printf("0 - exit\n");
  printf("1 - go to parent\n");
  printf("2 - go to left child\n");
  printf("3 - go to right child\n");
  printf("4 - create left child\n");
  printf("5 - create right child\n");
  printf("6 - delete left child\n");
  printf("7 - delete right child\n");
  printf("8 - delete current node\n");

  int action;

  scanf("%d", &action);

  return action;
}

int getNodeValue() {
  int root;
  printf("Enter value of the node: ");;
  scanf("%d", &root);
  return root;
}

void processAction(int action, Node** currentNode) {
  if (action == 1) {
    if (!(*currentNode)->parent) {
      printf("There is no parent\n");
      return;
    }
    *currentNode = (*currentNode)->parent;
  } else if (action == 2) {
    if (!(*currentNode)->leftChild) {
      printf("There is no left child\n");
      return;
    }
    *currentNode = (*currentNode)->leftChild;
  } else if (action == 3) {
    if (!(*currentNode)->rightChild) {
      printf("There is no right child\n");
      return;
    }
    *currentNode = (*currentNode)->rightChild;
  } else if (action == 4) {
    if ((*currentNode)->leftChild) {
      printf("There is already a left child. Delete it first\n");
      return;
    }
    int value = getNodeValue();
    (*currentNode)->leftChild = treeCreateNode(value);
    (*currentNode)->leftChild->parent = *currentNode;
  } else if (action == 5) {
    if ((*currentNode)->rightChild) {
      printf("There is already a right child. Delete it first\n");
      return;
    }
    int value = getNodeValue();
    (*currentNode)->rightChild = treeCreateNode(value);
    (*currentNode)->rightChild->parent = *currentNode;
  } else if (action == 6) {
    if (!(*currentNode)->leftChild) {
      printf("There is no left child\n");
      return;
    }
    treeDeleteNode((*currentNode)->leftChild);
  } else if (action == 7) {
    if (!(*currentNode)->rightChild) {
      printf("There is no right child\n");
      return;
    }
    treeDeleteNode((*currentNode)->rightChild);
  } else if (action == 7) {
    treeDeleteNode((*currentNode));
  }
}
