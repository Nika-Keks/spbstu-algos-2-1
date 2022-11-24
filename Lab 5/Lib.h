#pragma once
typedef struct Node
{
	int number;
	struct Node* left;
	struct Node* right;

}Node;
Node* NewNode();//creation a new node
int Tree_Height(Node* node);// getting the height of the tree
void Tree_Print(Node* node, int n);// output the whole tree by root
void Nodes_Print(Node* node, int n);//output branhces of the node
void Nodes_Tree_Print(Node* node, int n);//output every node