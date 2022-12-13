#pragma once

typedef struct Node
{
    int id;
    int value;
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *Tree_create_node(int value, Node *parent, Node *leftChild, Node *rightChild);
void Tree_delete_node(Node *node); 
void Tree_print_rec(Node *node, int space);
void Tree_print(Node *node);