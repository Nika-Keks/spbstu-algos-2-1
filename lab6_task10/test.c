#include "main.h"

int main() {
  Node* rootNode = generateRandomBinarySearchTree();

  printBinaryTree(rootNode);

  Node* node = getNode(rootNode);
  int k = getK();

  Node* result = findValueWithDifferentOrder(rootNode, node->value, k);

  if (result) {
    printf("Result is %d", result->value);
  } else {
    printf("Not found");
  }

  return 0;
}
