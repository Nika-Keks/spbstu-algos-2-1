#pragma warning(disable : 4996)

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

/*
* a function that implements the search for the root of the tree
* run through the matrix column, if everything is 0 then this is the root, if there is no root, we return -1
*/

int tree_node(int** mas,int height)
{
	int n = -1;
	int size =height;

	for (int j = 0; j < size; j++)
	{
		int count = 0;
		for (int i = 0; i < size; i++)
			if (mas[i][j] == 0) 
			{
				count++;
			}
		if (count == size)
		{
			n = j;
			break;
		}
	}
	return n;
}
/*
* a function that implements the display of the tree node in order on the screen
*/

void print(tree* node)
{
	if (node == NULL)
	{
		return;
	}
	print(node->l);
	printf("%d ",node->number);
	print(node->r);
	
}

/*
* a function that creates a tree according to the adjacency matrix, the root of the tree and the length of the matrix line
*/

tree* create_tree(int** mas, int k,int length)
{

	tree* tree_n = malloc(sizeof(tree)); // node memory allocation
	if (!tree_n)
	{
		exit(-1);

	}
	tree_n->l = NULL;
	tree_n->r = NULL;
	tree_n->number = k;
	
	
	int flag = 1; // a variable that helps keep track of which part to add a node to

	for (int j = 0; j < length; j++)
	{
		if (mas[k][j] == 1) // the loop is triggered if the root has a connection to another node, i.e. 1 in the adjacency matrix
		{
			
			if (flag == 1)
			{
				tree_n->l = create_tree(mas, j,length);
			}
			else if (flag == 2) 
			{
				tree_n->r = create_tree(mas, j,length);
			}
			flag++;
		}
	}

	return tree_n;
}

