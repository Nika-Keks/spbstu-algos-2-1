#pragma once

typedef struct Node
{
    int value;
    struct Node *parent;
    struct Node *left_child;
    struct Node *right_child;
} Node;

Node *Tree_create_node(int value, Node *parent, Node *left_child, Node *right_child);
int Random_int(int min, int max);
Node *Tree_generate_random_node(int depth, int min, int max);
Node *Tree_generate_random();
void Tree_print_rec(Node *node, int space);
void Tree_print(Node *node);