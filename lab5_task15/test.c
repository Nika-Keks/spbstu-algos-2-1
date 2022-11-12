#include "main.h"

int main() {
  int rootValue = getNodeValue();
  Node* currentNode = treeCreateNode(rootValue);

  displayNode(currentNode);

  while (1) {
    int action = getAction();

    if (action == 0) {
      break;
    } else {
      processAction(action, &currentNode);
    }

    displayNode(currentNode);
  }

  return 0;
}
