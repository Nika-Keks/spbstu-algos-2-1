#pragma once

typedef struct Node {
  int value;
	struct Node* parent;
	struct Node* leftChild;
	struct Node* rightChild;
} Node;

Node* treeCreateNode(int value);

void treeDeleteNode(Node* node);

int getNodeValueWidth(Node* node);

void displayNode(Node* node);

int getAction();

int getNodeValue();

void processAction(int action, Node** currentNode);
