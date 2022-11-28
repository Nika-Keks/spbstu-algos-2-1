#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba6.h"
#pragma warning(disable:4996)

/*
* The function of adding a node to the tree : descends in priority to the left
* child nodeand at the same time maintains differences in nodes(left->diff - right->diff).
* We have that if diff < 0, then there are more elements in the right subtreeand 
* we need to add a node to the left subtreeand vice versa.
*/
void Insert_Tree(Tree** A, int val) {
	if (*A == NULL) {
		*A = (Tree*)malloc(sizeof(Tree));
		if (*A == NULL) {
			puts("No memory abailable");
			return;
		}
		(*A)->diff = 0;
		(*A)->val = val;
		(*A)->right = NULL;
		(*A)->left = NULL;
		return;
	}
	// If there is no sheet on the left
	if ((*A)->left == NULL) {
		(*A)->diff++;
		Insert_Tree(&((*A)->left), val);
	}
	// If there is no sheet on the right
	else if ((*A)->right == NULL) {
		(*A)->diff--;
		Insert_Tree(&((*A)->right), val);
	}
	// else we go down to the side where there are more nodes
	else {
		if ((*A)->diff > 0) {
			(*A)->diff--;
			Insert_Tree(&((*A)->right), val);
		}
		else {
			(*A)->diff++;
			Insert_Tree(&((*A)->left), val);
		}
	}
}

/*
* Finds a node in the treeand writes
* a reference to it to the variable a
*/
void Find_Tree(Tree** A, int val, Tree*** a) {
	if ((*a) != NULL || (*A) == NULL) return;
	if ((*A)->val == val) {
		(*a) = A;
		return;
	}
	Find_Tree(&((*A)->left), val, a);
	Find_Tree(&((*A)->right), val, a);
}


/*
* Deleting a node
* First we find the node that needs to be deleted, and
* then we find the leaf of the tree
*/
void Remove_Tree(Tree** A, int val) {
	Tree** a = NULL;
	Find_Tree(A, val, &a);
	if (a == NULL) {
		puts("Not such value");
		return;
	}
	// find the leaf of the tree we want to delete
	Tree** sheet = A; 
	while (!((*sheet)->left == NULL && (*sheet)->right == NULL)) {
		if ((*sheet)->diff >= 0) {
			(*sheet)->diff--;    // correcting the difference
			sheet = &((*sheet)->left);
		}
		else {
			(*sheet)->diff++;    // correcting the difference
			sheet = &((*sheet)->right);
		}
	}
	(*a)->val = (*sheet)->val;     // Swapping the leaf and the node we want to delete
	free((*sheet));   // removal
	(*sheet) = NULL;  // Now there is no leaf, write NULL instead
}


void Print_Tree_val(Tree* A) {
	if (A != NULL)
	{
		printf("%d ", A->val);
		Print_Tree_val(A->left);
		Print_Tree_val(A->right);
	}
}


void Print_Tree_diff(Tree* A) {
	if (A != NULL)
	{
		printf("%d ", A->diff);
		Print_Tree_diff(A->left);
		Print_Tree_diff(A->right);
	}
}