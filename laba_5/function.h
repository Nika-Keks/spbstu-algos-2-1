#pragma once
typedef struct tree
{
    int number;
    struct tree* r;
    struct tree* l;
}tree;

int tree_node(int** mas, int height);
tree* create_tree(int** mas, int k, int length);
void print(tree* node);
