
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
Node* Min_Node(Node* node);
void Push_Node(Node* node);
void Change_Values(Node* node);
Node* DeleteNode(Node* node, int val);
