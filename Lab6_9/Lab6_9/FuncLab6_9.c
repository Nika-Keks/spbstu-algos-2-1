#include <stdlib.h>
#include <stdio.h>
#include "TypeLab6_9.h"
#pragma warning (disable:4996)
int ReadConsol(tree** t)
{
	int k = 0;
	int i = 0;
	int p = 0;
	printf("Enter the amount of data to be entered into the console\n");
	scanf("%d", &k);//the amount of data entered into the console for nodes
	printf("Enter the future nodes of the tree\n");
	while (i < k)
	{
		scanf("%d", &p);//reading an item from the console
		if (AddElem(t, p) == -1)//adding the read element to the binary search tree
		{
			printf("Error\n");
			return -1;
		}
		i++;
	}
	printf("\n");
	return 0;
}
int AddElem(tree** t, int x)
{
	int flag;//to check whether there is such an element in the tree or not, determines whether the element has been added
	if ((*t) == NULL)//if this node is a leaf
	{
		(*t) = (tree*)malloc(sizeof(tree));//we allocate memory for the node
		if ((*t) != NULL)
		{
			(*t)->key = x;
			(*t)->left = (*t)->right = NULL;
			if (x <= 0)//if the element is not positive
			{
				(*t)->nonp = 1;
				(*t)->pos = 0;
			}
			else//if the element is positive
			{
				(*t)->nonp = 0;
				(*t)->pos = 1;
			}
			flag = 1;//the element was added to the tree
		}
		else return -1;
	}
	else
	{
		//adding an element to a place that fits the conditions and there is no node there yet
		if (x < (*t)->key)//condition adding to the left subtree
		{
			flag = AddElem(&((*t)->left), x);
			if (flag > 0)//successfully adding a node to the tree
			{
				if (x <= 0) (*t)->nonp = (*t)->nonp + 1;
				else (*t)->pos = (*t)->pos + 1;//we increase the number of positive or non-positive elements, depending on which number was added to the tree

			}
		}
		else
		{
			if (x > (*t)->key)//condition for adding to the right subtree
			{
				flag = AddElem(&((*t)->right), x);
				if (flag > 0)//successfully adding a node to the tree
				{
					if (x <= 0) (*t)->nonp = (*t)->nonp + 1;
					else (*t)->pos = (*t)->pos + 1;//we increase the number of positive or non-positive elements, depending on which number was added to the tree
				}
			}
			else flag = 0;//if the element being added is equal to the number already written to the tree, then such an element should not be added to the tree, since it is already there
		}
	}
	return flag;
}
tree* Kmin(tree* t, int k)
{
	int r = 0;//the order of the node we are currently on is in ascending order (the elements in the left subtree will have less order than the right subtree)
	if (t != NULL)
	{
		if (t->key > 0)//if the element is positive, then for it we consider what it is from the end of the sequence of positive elements in the tree
		{
			if (t->left != NULL)
			{
				r = t->left->pos + 1;
			}
			else r = 1;
		}
		else r = 0;//for all non-positive elements, we assume that the order for them is 0
		if (r != k)
		{
			if (k < r)
				t = Kmin(t->left, k);//we pass k, because if we go to the left branch, it means that the element we are looking for is in the left branch, since the current order we found earlier was greater than the one we were looking for
			else
				t = Kmin(t->right, k - r);//when we go to the right branch, we change the order of K because r is calculated through the number of nodes in the subtree, and the leaves on the right and on the left are the same and equal to 1 if they are positive
		}
	}
	else t = NULL;
	return t;
}

int kol = 0;//a global variable to complete the recursion if all elements less than the kth have already been output
void PrintTree(tree* t, int key, int k)//traversal for output in internal order
{
	if (t != NULL)
	{
		if (t->pos > 0)//the number of positive elements greater than 0 means that there is at least one positive element and it will be possible to print it
		{
			PrintTree(t->left, key, k);//we start the passage from the left subtree
			if (t->key < key)//the number is less than found
			{
				if (t->key > 0)//this condition is necessary in order not to count the number of non-positive numbers and not to output a negative number if it is in the same branch with the output positive number, but will stand at a level higher than it is
				{
					printf("%d\n", t->key);
					kol++;
				}
			}
			if (kol == k) return;//we exit the recursion so that it does not pass through the entire tree as soon as the elements smaller than key have ended, and these are k elements
			PrintTree(t->right, key, k);//then we go to the right subtree
		}

	}
}
void FreeTree(tree** t)////first we go to the left subtree, then to the right and clear the memory allocated for nodes
{
	if ((*t)->left)   FreeTree(&((*t)->left));
	if ((*t)->right)  FreeTree((&(*t)->right));
	free(*t);
}