#pragma once
#include "tree.h"

int Get_number_length(int number);
void Find_node_by_value_rec(Node *node, int value, Node **result_node);
Node *Find_node_by_value(Node *rootNode, int value);
void Find_node_by_order_rec(Node *node, int length, Node **result_node);
Node *Find_node_by_order(Node *rootNode, int value, int k);
Node *Get_node(Node *rootNode);
int Get_k();
