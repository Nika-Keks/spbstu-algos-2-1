#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "Lib.h"

int main(void)
{
	//creation of a tree
	/* The tree looks like this:
	      0
	    /   \
	  1       3
	   \     /  \
	    2   4    5
		  /	  \
	     7     6
	    /
       8
	*/
	Node* node0 = NewNode();
	Node* node1 = NewNode();
	Node* node2 = NewNode();
	Node* node3 = NewNode();
	Node* node4 = NewNode();
	Node* node5 = NewNode();
	Node* node6 = NewNode();
	Node* node7 = NewNode();
	Node* node8 = NewNode();
	node0->left = node1;
	node1->right = node2;
	node0->right = node3;
	node3->left = node4;
	node3->right = node5;
	node4->right = node6;
	node4->left = node7;
	node7->left = node8;
	node0->number = 0;
	node1->number = 1;
	node2->number = 2;
	node3->number = 3;
	node4->number = 4;
	node5->number = 5;
	node6->number = 6;
	node7->number = 7;
	node8->number = 8;
	Tree_Print(node0, Tree_Height(node0)); 
	printf("\nFuther output represents nodes with every child-tree :\n");
	printf("--------------------\n");
	Nodes_Tree_Print(node0, Tree_Height(node0));
	printf("\nOutput every node with only child nodes\n");
	Nodes_Only_Print(node0, Tree_Height(node0));
}
