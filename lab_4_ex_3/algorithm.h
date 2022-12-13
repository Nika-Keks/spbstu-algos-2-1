#pragma once
#include "list.h"

int Check_repetition(Node *path_head, int x, int y);

void Find_shortest_path_rec(
    int width,
    int height,
    int target_x,
    int target_y,
    int steps_quantity,
    Node *path_head,
    int *smallest_steps_quantity,
    Node **shortest_path_head);

Node *Find_shortest_path(
    int width,
    int height,
    int x,
    int y,
    int target_x,
    int target_y);

void Print_path(Node *head);

void Get_board_size(int *width_ptr, int *height_ptr);

void Get_initial_position(int *x_ptr, int *y_ptr, int width, int height);

void Get_target_position(int *x_ptr, int *y_ptr, int width, int height);

