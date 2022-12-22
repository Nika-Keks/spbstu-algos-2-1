#pragma once

#include "binaryTree.h"

void findNodeByValueUtil(Node* node, int value, Node** resultNode);

Node* findNodeByValue(Node* rootNode, int value);

void findValueWithDifferentOrderUtil(Node* node, int length, Node** resultNode);

Node* findValueWithDifferentOrder(Node* rootNode, int value, int k);

Node* getNode(Node* rootNode);

int getK();
