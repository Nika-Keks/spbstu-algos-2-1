#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TypeLab5.5.h"
#pragma warning (disable:4996)

int ReadTreeConsole(tree** t, int* n)
{
	int k = 0;//Number of nodes in the tree
	int i = 0;
	int p = 0;
	printf("Enter the number of nodes\n");
	scanf("%d", &k);
	*n = k;
	printf("Enter the future nodes of the tree\n");
	while (i < k)
	{
		scanf("%d", &p);//reading the number from the console
		if (CreateTree(p, t) == -1) return-1;//adding this number to the tree
		i++;
	}
	return 0;
}

int CountNum(int x)
{
	int num = 0;//number of characters
	if (x < 0)//if the number is negative
	{
		num = 1;
		x = -x;//we change the sign to the opposite
	}
	if (x == 0) num = 1;//initially, the number is 0
	while (x != 0)
	{
		num++;
		x = x / 10;//"discarding" the last digit
	}
	return num;
}
int CreateTree(int x, tree** k)//we create a binary tree, in which the nodes of the subtree of some node P are smaller in size than the node p itself, and for the right subtree the opposite is true
{
	if ((*k) == NULL)//if a sheet is passed
	{
		*k = (tree*)malloc(sizeof(tree));//allocating memory
		if ((*k) != NULL)//fill in the data
		{
			(*k)->data = x;
			(*k)->weight = CountNum(x);//we immediately determine the number of characters in the number, then we will change it
			(*k)->left = NULL;
			(*k)->right = NULL;
		}
		else
		{
			printf("Error\n");
			return -1;
		}
	}
	else
	{
		if (x < ((*k)->data))//condition for adding a left child
		{
			CreateTree(x, &((*k)->left));
		}
		else//condition for adding a right child
		{
			CreateTree(x, &((*k)->right));
		}
	}
	return 0;
}
int CountH(tree** t)
{
	int r1, r2, r;
	if ((*t) == NULL) return 0;
	else
	{
		if ((*t)->left == NULL && (*t)->right == NULL) return 0;//if both subtree are null, then it is a leaf, then its height is 0
		else
		{
			r1 = CountH(&((*t)->left));//first we reach the end of the left subtree from the root
			r2 = CountH(&((*t)->right));//after we reach the end of the left subtree, we go to the right subtree and perform the same actions for it as before
			if (r1 > r2) r = r1;//compare the two obtained values and write the maximum of them in r, since the height of the subtree is the maximum path from the root to one of the leaves of this tree
			else r = r2;
			return r + 1;
		}
	}
}

void ReadReverseOrder(tree** t)
{
	if ((*t) != NULL)
	{
		ReadReverseOrder(&((*t)->left));//First we go to the left subtree
		ReadReverseOrder(&((*t)->right));//then we move to the right subtree and repeat the steps
		if ((*t)->left != NULL)//if a node has a left subtree, then we change the width of this node by the width of the left subtree
		{
			tree* le = (*t)->left;
			(*t)->weight = (*t)->weight + le->weight;
		}
		if ((*t)->right != NULL)//if a node has a right subtree, then we change the width of this node by the width of the right subtree
		{
			tree* ri = (*t)->right;
			(*t)->weight = (*t)->weight + ri->weight;
		}
	}
}

int** InitAuxTable(int str, int sto)
{
	int i = 0;
	int j = 0;
	int** B = (int**)malloc(str * sizeof(int*));//allocation of memory for substring pointers
	if (B != NULL)
	{
		for (i = 0; i < str; i++)  // loop by lines
		{
			B[i] = (int*)malloc(sto * sizeof(int));//allocation of memory for storing strings
		}
		for (i = 0; i < str; i++)  // loop by lines
		{
			for (j = 0; j < sto; j++)  // cycle by columns
			{
				B[i][j] = 0;//fill the matrix with zeros
			}
		}
	}
	else {
		printf("Error\n");
	}
	return B;
}
void CreateAuxTable(tree** t, int y, int** A,int*x)
{
	if ((*t) != NULL)
	{
		CreateAuxTable(&((*t)->left), y + 2, A,x);//First we go to the end of the left subtree, increasing the row number by 2 (since we will also write the width of the subtree to the table)
		A[y][*x] = (*t)->data;//We fill the element of the auxiliary matrix with node data
		A[y + 1][*x] = (*t)->weight;//in the next row, but in the same column, we write the width of the node in question
		(*x)++;//increasing the column number
		CreateAuxTable(&((*t)->right), y + 2, A,x);//go to the right subtree
	}
}
void PrintAuxTable(int** B, int str, int sto)
{
	printf("Your tree\n");
	for (int i = 0; i < str; i++)  // loop by lines
	{
		for (int j = 0; j < sto; j++)  // cycle by columns
		{
			if (B[i][j] == 0) printf("______");//to better view the structure of the tree
			else printf("%6d", B[i][j]);
		}
		printf("\n");
	}
}
void FreeAuxTable(int** B, int str)
{
	int p = 0;
	for (p; (p < str); p++)
	{
		free(B[p]); //freeing up the memory allocated for each row
	}
	free(B);//freeing up memory allocated for pointers under strings
}
void FreeTree(tree** t) {//first we go to the left subtree, then to the right and clear the memory allocated for nodes
	if ((*t)->left)   FreeTree(&((*t)->left));
	if ((*t)->right)  FreeTree((&(*t)->right));
	free(*t);
}