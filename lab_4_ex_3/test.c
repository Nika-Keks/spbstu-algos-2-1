#include "algorithm.h"

int main() {
  int width, height;
  int x, y;
  int target_x, target_y;

  Get_board_size(&width, &height);
  Get_initial_position(&x, &y, width, height);
  Get_target_position(&target_x, &target_y, width, height);

  Node* head = Find_shortest_path(width, height, x, y, target_x, target_y);

  Print_path(head);

  return 0;
}
