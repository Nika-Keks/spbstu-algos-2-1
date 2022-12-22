#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#include<locale.h>
#pragma warning(disable:4996)

void Insert(int r, tree** Tree) {
	if (*Tree == NULL) {
		tree* ptr = (tree*)malloc(sizeof(tree));
		ptr->left = NULL;
		ptr->right = NULL;
		ptr->val = r;
		*Tree = ptr;
		return;
	}
	if (r < (*Tree)->val) {
		Insert(r, &((*Tree)->left));
	}
	else Insert(r, &((*Tree)->right));
}

tree* build(int n) {
	tree* Tree = NULL;
	for (int i = 0; i < n; i++) {
		int r = rand() % 10;
		Insert(r, &Tree);
	}
	return Tree;
}

//fill tree
void Fill(int level, tree* Tree) {
	if (Tree == NULL) return;
	if (Tree->left == NULL && Tree->right == NULL) {
		Tree->val = level;
		return;
	}
	if (Tree->right == NULL) {
		Fill(level + 1, Tree->left);
		Tree->val = Tree->left->val;
		return;
	}
	if (Tree->left == NULL) {
		Fill(level + 1, Tree->right);
		Tree->val = Tree->right->val;
		return;
	}
	//case: left&right are not NULL
	Fill(level + 1, Tree->left);
	Fill(level + 1, Tree->right);
	if (Tree->left->val < Tree->right->val) {
		Tree->val = Tree->left->val;
	}
	else Tree->val = Tree->right->val;
}

//return the depth of tree
int Depth(tree* Tree, int c) {
	if (Tree == NULL) return c;
	if (Tree->left == NULL && Tree->right == NULL) {
		return c;
	}
	else {
		c += 1;
		int c1 = Depth(Tree->left, c);
		int c2 = Depth(Tree->right, c);
		c = (c1 < c2 ? c2 : c1);
		return c;
	}
}

//test function of print
void Print(tree* Tree) {
	if (Tree != NULL) {
		printf("%d ", Tree->val);
		Print(Tree->left);
		Print(Tree->right);
	}
}

//create helping matrix...
int** CreateMatrix(tree* Tree, int n, int m) {
	int** matrix = (int**)malloc(n * sizeof(int*));
	if (matrix == NULL) return NULL;
	for (int i = 0; i < n; i++) {
		matrix[i] = (int)malloc(m * sizeof(int));
		for (int j = 0; j < m; j++) {
			matrix[i][j] = -1;
		}
	}
	return matrix;
}

//...and then fill it...
void FillMatrix(tree* Tree, int** matrix, int n, int level, int delta) {
	if (Tree == NULL) return;
	matrix[n][level] = Tree->val;
	delta = delta / 2; //delta for not print next branch right under node
	FillMatrix(Tree->left, matrix, n - delta, level + 1, delta);
	FillMatrix(Tree->right, matrix, n + delta, level + 1, delta);
	return;
}

//...and finally print it
void PrintMatrix(int** matrix, int n, int m) {
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			if (matrix[i][j] < 0) printf(" ");
			else printf("%d", matrix[i][j]);
		}
		printf("\n");
	}
}