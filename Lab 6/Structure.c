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
	Node* node1 = node;
	int l, r;
	if (node1 != NULL)
	{
		l = (node1->left != NULL) ? Tree_Height(node1->left) : 0;
		r = (node1->right != NULL) ? Tree_Height(node1->right) : 0;
		return l + r + 1;
	}
	return 0;
}

void Tree_Print(Node* node, int n)// output the whole tree by root
{
	Node* node1 = node;
	if (node1 !=NULL)
	{
		Tree_Print(node1->right, n + 3);
		for (int i = 0; i < n; i++)
			printf(" ");
		printf("%d\n", node1->number);
		Tree_Print(node1->left, n + 3);
	}
}

Node* Min_Node(Node* node)
{
	Node* node1  = node;
	if (node1 != NULL)
	{
		if (node1->number == 1)
			return node1;
		else if(node1->left == NULL)
			Min_Node(node1->right);
		else if(node1->right == NULL)
			Min_Node(node1->left);
		else if (node1->left->number >= node1->right->number)
			Min_Node(node1->right);
		else
			Min_Node(node1->left);
	}
}
void Push_Node(Node* node)
{
	Node* node1 = node;
	Node* node2 = NULL;
	node2 = NewNode();
	node2->number = 1;
	if (node1->left == NULL)
		node1->left = node2;
}

void Change_Values(Node* node)
{
	Node* node1 = node;
	if (node1 != NULL)
	{
		node1->number = Tree_Height(node1);
		Change_Values(node1->left);
		Change_Values(node1->right);
	}
}


Node* DeleteNode(Node* node, int n) 
{
	if (node == NULL)
		return node;
	if (n == node->number) 
	{
		Node* tmp;
		if (node->right == NULL)
			tmp = node->left;
		else 
		{
			Node* node1 = node->right;
			if (node1->left == NULL)
			{
				node1->left = node->left;
				tmp = node1;
			}
			else 
			{
				Node* pmin = node1->left;
				while (pmin->left != NULL) 
				{
					node1 = pmin;
					pmin = node1->left;
				}
				node1->left = pmin->right;
				pmin->left = node->left;
				pmin->right = node->right;
				tmp = pmin;
			}
		}
		free(node);
		return tmp;
	}
	else if (node->left != NULL && n <= node->left->number)
		node->left = DeleteNode(node->left, n);
	else
		if (node->right != NULL)
		node->right = DeleteNode(node->right, n);
	return node;

}

