#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "list.h"

//Проверка повторения ходов
int Check_repetition(Node* path_head, int x, int y) {
  while (path_head) {
    if (path_head->x == x && path_head->y == y) {
      return 1;
    }
    path_head = path_head->next;
  }
  return 0;
}

//Рекурсивно находим кротчайший путь
void Find_shortest_path_rec(
  int width,
  int height,
  int target_x,
  int target_y,
  int steps_quantity,
  Node* path_head,
  int* smallest_steps_quantity,
  Node** shortest_path_head
) {
  if (steps_quantity > *smallest_steps_quantity) {
    List_destroy(path_head);
    return;
  }

  Node* last_move = List_last(path_head);

  if (last_move->x == target_x && last_move->y == target_y) {
    *smallest_steps_quantity = steps_quantity;
    *shortest_path_head = path_head;
    return;
  }

  int possible_dx[8] = {-2, -1, 1, 2, -2, -1, 1, 2};
  int possible_dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

  for (int i = 0; i < 8; i += 1) {
    int dx = possible_dx[i];
    int dy = possible_dy[i];
    int next_x = last_move->x + dx;
    int next_y = last_move->y + dy;

    if (Check_repetition(path_head, next_x, next_y) || next_x < 0 || next_y < 0 || next_x > width - 1 || next_y > height - 1) {
      continue;
    }

    Node* cloned_path_head = List_clone(path_head);
    List_append(cloned_path_head, last_move->x + dx, last_move->y + dy);

    Find_shortest_path_rec(
      width,
      height,
      target_x,
      target_y,
      steps_quantity + 1,
      cloned_path_head,
      smallest_steps_quantity,
      shortest_path_head
    );
  }
}

//Вызов рекурсивной функции для нахождения кратчайшего пути
Node* Find_shortest_path(
  int width,
  int height,
  int x,
  int y,
  int target_x,
  int target_y
) {
  int smallest_steps_quantity = INT_MAX;
  Node* shortest_path_head = NULL;

  Node* initial_path_head = List_create();
  List_append(initial_path_head, x, y);

  Find_shortest_path_rec(
    width,
    height,
    target_x,
    target_y,
    0,
    initial_path_head,
    &smallest_steps_quantity,
    &shortest_path_head
  );

  return shortest_path_head;
}

//Вывод истории ходов
void Print_path(Node* head) {
  if (head == NULL)
  {
    printf("Неудалось найти");
    return;
  }

  int step = 1;

  while (head) {
    printf("%d. x = %d, y = %d \n", step, head->x, head->y);
    step += 1;
    head = head->next;
  }
}

//Получение размеров доски 
void Get_board_size(int* width_ptr, int* height_ptr) {
  int width, height;

  printf("Введите длину и ширину доски: ");

  scanf("%d %d", &width, &height);

  while (width < 1 || height < 1) {
    printf("Неверный размер\n");
    printf("Введите длину и ширину доски: ");
    scanf("%d %d", &width, &height);
  }

  *width_ptr = width;
  *height_ptr = height;
}

//Получение координат начальной позиции
void Get_initial_position(int *x_ptr, int *y_ptr, int width, int height) {
  int x, y;

  printf("Введите исходные координаты (x, y): ");

  scanf("%d %d", &x, &y);

  while (x < 0 || y < 0 || x > width - 1 || y > height - 1) {
    printf("Неверные координаты\n");
    printf("Введите исходные координаты (x, y): ");
    scanf("%d %d", &x, &y);
  }

  *x_ptr = x;
  *y_ptr = y;
}

//Получение координат конечной позиции
void Get_target_position(int *x_ptr, int *y_ptr, int width, int height) {
  int x, y;

  printf("Введите конечные координаты (x, y): ");

  scanf("%d %d", &x, &y);

  while (x < 0 || y < 1 || x > width - 1 || y > height - 1) {
    printf("Неверные координаты\n");
    printf("Введите конечные координаты (x, y): ");
    scanf("%d %d", &x, &y);
  }

  *x_ptr = x;
  *y_ptr = y;
}
