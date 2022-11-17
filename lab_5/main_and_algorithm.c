#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"

# define N 5


node* Binary_Tree(int relationship[N][N])
{

	node* Arr_nodes[N]; //create an array of nodes

	for (int i = 0; i < N; i++)
	{
		Arr_nodes[i] = (node*)malloc(sizeof(node));
		Arr_nodes[i]->value = i;
		Arr_nodes[i]->left = NULL;
		Arr_nodes[i]->right = NULL;
	}
	node* root = NULL;


	int cur_parent;

	//for the child, we are looking for direct parents moving along the matrix to all other parents

	for (int j = 0; j < N; j++) 
	{
		cur_parent = 0; //initially for the child in the j column there is no current parent

		for (int i = 0; i < N; i++) //go through the rows of the matrix in search of the parent
		{
			if (relationship[i][j] != 0) 
			{
				if (cur_parent == 0)
				{
					cur_parent = i; //if the current parent has not yet been, then i number in the j column becomes it
				}

				else
				{
					if (relationship[cur_parent][i] == 1) //if the old parent is not direct, then delete the relationship
					{
						relationship[cur_parent][j] = 0;
						cur_parent = i;
					}
					else
					{ 
						// if the old parent is direct, then the new one is the ancestor and break the relationship of that new one
						relationship[i][j] = 0;
					}

				}

			}
		}

		//now the current parent is the j node's direct parent

		if (cur_parent == 0)
		{
			//if no ancestors were found for the node, then it is the root
			root = Arr_nodes[j];

		}
		else
		{
			//distribute to a free branch
			if ((Arr_nodes[cur_parent]->left) == NULL)
			{
				Arr_nodes[cur_parent]->left = Arr_nodes[j];
				
			}
			else
			{
				Arr_nodes[cur_parent]->right = Arr_nodes[j];
				
			}
		}
	}
	return root;
}
//function that creates a binary tree


void Print_Tree(node* root)
{
	if (root != NULL)
	{
		Print_Tree(root->left);
		printf("%d", root->value);
		Print_Tree(root->right);
	}
}
//function that print a binary tree, passing through the nodes

int main()
{
	int matrix[N][N] = 
	{ 
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 0 },

	};

	node* root = Binary_Tree(matrix);
	printf("Binary tree:   ");
	Print_Tree(root);
	printf("\n");
}
