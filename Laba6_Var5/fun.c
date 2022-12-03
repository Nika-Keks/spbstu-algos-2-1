#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Header.h"

void Add(tree** Tree) {
	if (*Tree == NULL) {
		tree* leaf = (tree*)malloc(sizeof(tree));
		leaf->left = NULL;
		leaf->right = NULL;
		leaf->dad = NULL;
		leaf->val = 1;
		*Tree = leaf;
		return;
	}
	(*Tree)->val++;
	tree* curTree = *Tree;
	while (!((curTree)->left == NULL && (curTree)->right == NULL)) {
		if ((curTree)->left == NULL) {
			tree* leaf = (tree*)malloc(sizeof(tree));
			leaf->left = NULL;
			leaf->right = NULL;
			leaf->dad = curTree;
			leaf->val = 1;
			(curTree)->left = leaf;
			return;
		}
		if ((curTree)->right == NULL) {
			tree* leaf = (tree*)malloc(sizeof(tree));
			leaf->left = NULL;
			leaf->right = NULL;
			leaf->dad = curTree;
			leaf->val = 1;
			(curTree)->right = leaf;
			return;
		}
		if ((curTree)->left->val <= (curTree)->right->val)//we go to deeper one
		{
			(curTree)->left->val++;
			curTree = (curTree)->left;
		}
		else {
			(curTree)->right->val++;
			curTree = (curTree)->right;
		}
	}
	tree* leaf = (tree*)malloc(sizeof(tree));
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->dad = curTree;
	leaf->val = 1;
	(curTree)->left = leaf;
	return;
}

//I decided to delete the deepest leaf
void Delete(tree** Tree) {
	if (*Tree == NULL) {
		printf("how you dare!? tree is empty\n");
		return;
	}
	(*Tree)->val--;
	tree** curTree = Tree;
	while (!((*curTree)->left == NULL && (*curTree)->right == NULL)) {
		if ((*curTree)->left == NULL) {
			curTree = &((*curTree)->right);
			continue;
		}
		if ((*curTree)->right == NULL) {
			curTree = &((*curTree)->left);
			continue;
		}
		if ((*curTree)->left->val > (*curTree)->right->val) {
			(*curTree)->left->val--;
			curTree = &((*curTree)->left);
		}
		else {
			(*curTree)->right->val--;
			curTree = &((*curTree)->right);
		}
	}
	free(*curTree);
	*curTree = NULL;
}

//function of print can be recursive cause it don't relate to the task
void Print(tree* Tree) {
	if (Tree != NULL) {
		printf("%d ", Tree->val);
		Print(Tree->left);
		Print(Tree->right);
	}
}