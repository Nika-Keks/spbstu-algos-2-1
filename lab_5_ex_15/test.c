#include "main.c"

int main() {
  int root_value = Get_node_value();
  Node* tree = Tree_create_node(root_value, NULL, NULL, NULL);

  Tree_print(tree);

  while (1) {
    int action = Get_action();

    if (action == 0) {
      break;
    } else if (action == 1) {
      int id = Get_id();
      Node* node = Find_node_by_id(tree, id);
      if (!node) {
        printf("Узла не существует\n");
        continue;
      }
      int value = Get_node_value();
      Node* child = Tree_create_node(value, node, NULL, NULL);
      node->leftChild = child;
    } else if (action == 2) {
      int id = Get_id();
      Node* node = Find_node_by_id(tree, id);
      if (!node) {
        printf("Узла не существует\n");
        continue;
      }
      int value = Get_node_value();
      Node* child = Tree_create_node(value, node, NULL, NULL);
      node->rightChild = child;
    } else if (action == 3) {
      int id = Get_id();
      Node* node = Find_node_by_id(tree, id);
      if (!node) {
        printf("Узла не существует\n");
        continue;
      }
      Tree_delete_node(node);
    }

    printf("\n");
    Tree_print(tree);
  }

  return 0;
}
