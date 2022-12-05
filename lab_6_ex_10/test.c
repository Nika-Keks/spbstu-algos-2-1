#include "main.h"
#include <locale.h>

int main() {
  setlocale(LC_CTYPE, "Russian");

  Node* root_node = Tree_generate_random();

  Tree_print(root_node);

  Node* node = Get_node(root_node);
  int k = Get_k();

  Node* result_node = Find_node_by_order(root_node, node->value, k);

  if (result_node) {
    printf("Результат: %d", result_node->value);
  } else {
    printf("Не найдено");
  }

  return 0;
}