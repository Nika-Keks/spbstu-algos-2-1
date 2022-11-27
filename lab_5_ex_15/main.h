#pragma once

typedef struct Node {
    int value;
	struct Node* parent;
	struct Node* leftChild;
	struct Node* rightChild;
} Node;

void Find_node_by_id_rec(Node *node, int id, Node **found_node);
Node *Find_node_by_id(Node *tree, int id);
int Get_action();
int Get_id();
int Get_node_value();