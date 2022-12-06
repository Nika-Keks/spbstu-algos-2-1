#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "Lib.h"

int main(void)
{
	//creation of a tree
	/* The tree looks like this:
		  n0
		/   \
	  n1       n3
	   \     /  \
	   n2   n4  n5
		   /   \
		 n7     n6
		/
	   n8
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
	node0->number = Tree_Height(node0);
	node1->number = Tree_Height(node1);
	node2->number = Tree_Height(node2);
	node3->number = Tree_Height(node3);
	node4->number = Tree_Height(node4);
	node5->number = Tree_Height(node5);
	node6->number = Tree_Height(node6);
	node7->number = Tree_Height(node7);
	node8->number = Tree_Height(node8);
	Tree_Print(node0, Tree_Height(node0));
	Push_Node(Min_Node(node0));
	printf("-----------Addition-----------\n");
	Change_Values(node0);
	Tree_Print(node0, Tree_Height(node0));
	printf("-----------Delete(6)-----------\n");
	DeleteNode(node0, 6);
	Tree_Print(node0, Tree_Height(node0));
	printf("---------Changing values---------\n");
	Change_Values(node0);
	Tree_Print(node0, Tree_Height(node0));
}