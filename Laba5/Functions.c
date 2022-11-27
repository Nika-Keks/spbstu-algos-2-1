#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba5.h"
#pragma warning(disable:4996)

/*
* Build a tree, according to the principle: I do not go below 
* the log2(n) level and add exactly n elements
* (First, the left subtree is completely built)
*/
Tree* Build_Tree(int i, int n, int* count) {
	if (i > log2(n) || (*count) >= n) return NULL;
	Tree* A = (Tree*)malloc(sizeof(Tree));
	if (A == NULL) return NULL;
	A->left = NULL;
	A->right = NULL;
	(*count)++;

	A->left = Build_Tree(i+1, n, count);
	A->right = Build_Tree(i+1, n, count);

	return A;
}

/*
* Fills in the number of leaves in each node: first I go down to the leaves, 
* and then each ancestor will be equal to the sum of the leaves of his children
*/
void Tree_leaves(int i, int n, Tree* B) {
	if (B == NULL) return;

	Tree_leaves(i, n, B->left);
	Tree_leaves(i, n, B->right);
	if (B->left == NULL && B->right == NULL) B->count = 1;
	else if (B->left == NULL) B->count = B->right->count;
	else if (B->right == NULL) B->count = B->left->count;
	else B->count = B->left->count + B->right->count;
}

/*
* Combining Build_Tree and Tree_leaves
*/
Tree* Create_Tree(int n) {
	int count = 0;
	Tree* tree = Build_Tree(0, n, &count);
	Tree_leaves(0, n, tree);
	return tree;
}

/*
* Fills the auxiliary matrix with tree values
*/
void Take_elems(Tree* A, int** arr, int level, int left, int right) {
	if (A == NULL) return;
	arr[level][(right+left)/2] = A->count;
	Take_elems(A->left, arr, level+1, left, (right+left)/2);
	Take_elems(A->right, arr, level+1, (right+left)/2, right);
}

int** dynamic_array_alloc(int N, int M) {     // massive N*M
	int** A = (int**)malloc(N * sizeof(int*));
	if (A == NULL) return NULL;
	for (int i = 0; i < N; i++) {
		A[i] = (int*)malloc(M*sizeof(int));
		if (A[i] == NULL) return NULL;
		for (int j = 0; j < M; j++) A[i][j] = -1;
	}
	return A;
}

void dynamic_array_free(int** A, int N) {
	for (int i = 0; i < N; i++) free(A[i]);
	free(A);
}


/*
* Outputs a tree written to an auxiliary matrix 
* (initially the matrix is filled with "-1", but spaces are displayed instead)
*/
void Print_Tree(Tree* A, int n) {
	int hight = (int)log2(n) + 1;
	int width = (int)pow(2, (int)log2(n)+1) - 1;
	int** Matrix = dynamic_array_alloc(hight, width);
	Take_elems(A, Matrix, 0, 0, width);
	puts("Ваше дерево:");
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++)
			(Matrix[i][j] == -1) ? printf(" ") : printf("%d", Matrix[i][j]);
		puts("");
	}
	dynamic_array_free(Matrix, hight);
}
