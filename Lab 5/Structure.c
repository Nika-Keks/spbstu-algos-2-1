#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "Lib.h"

Node* NewNode()//creation a new node
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	return node;
}

int Tree_Height(Node* node)// getting the height of the tree
{
	int l, r;
	if (node != NULL) 
	{
		l = (node->left != NULL) ? Tree_Height(node->left) : 0;
		r = (node->right != NULL) ? Tree_Height(node->right) : 0;
		return ((l > r) ? l : r) + 1;
	}
	return 0;
}

void Tree_Print(Node* node, int n)// output the whole tree by root
{
	Node* node1 = node;
	if (node1)
	{
		Tree_Print(node1->right, n + 3);
		for (int i = 0; i < n; i++)
			printf(" ");
		printf("%d\n", node1->number);
		Tree_Print(node1->left, n + 3);
	}
}

void Nodes_Print(Node* node, int n)//output branhces of the node
{
	int N = n;
	Node* node1 = node;
	if (node1)
	{
		if (node1->left)
		{
			Tree_Print(node1->left, N);
			printf("--------------------\n");
		}
		if (node1->right)
		{
			Tree_Print(node1->right, N);
			printf("--------------------\n");
		}
	}
}

void Nodes_Tree_Print(Node* node, int n)//output every node
{

	int N = n;
	Node* node1 = node;
	if (node1)
	{
		Nodes_Print(node1, N);
		N--;
		Nodes_Tree_Print(node1->left, N);
		Nodes_Tree_Print(node1->right, N);
	}
}

void Nodes_Only_Print(Node* node)//output every node only with child nodes
{
	Node* node1 = node;
	if (node1)
	{
		if (node1->right)
		{
			for (int i = 0; i < 3; i++)
				printf(" ");			
			printf("%d\n", node1->right->number);			
		}
		printf("%d\n", node1->number);
		if (node1->left)
		{
			for (int i = 0; i < 3; i++)
				printf(" ");
			printf("%d\n", node1->left->number);	
		}
		printf("--------------------\n");
		Nodes_Only_Print(node1->left);
		Nodes_Only_Print(node1->right);

	}
}
