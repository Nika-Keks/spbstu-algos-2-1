#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#pragma warning(disable : 4996)

int SymbolCounter(char const* filename) {
	FILE* file;
	file = fopen(filename, "r");
	int counter = 0;
	while (!feof(file)) if (fgetc(file) == ' ') counter++;
	counter++;
	fclose(file);
	return counter;
}

Node* CreateNode(int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		printf("memory allocation error");
		exit(1);
	}
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return(node);
}

int SubtreeHeight(Node* node) {
	int left, right;
	if (node != NULL) {
		left = (node->left != NULL) ? SubtreeHeight(node->left) : 0;
		right = (node->right != NULL) ? SubtreeHeight(node->right) : 0;
		return ((left > right) ? left : right) + 1;
	}
	return 0;
}

void ReadArray(char const* filename, int* Array, int N) {
	FILE* file;
	file = fopen(filename, "r");
	for (int i = 0; i < N; i++) {
		int a;
		if (!fscanf(file, "%i ", &a)) exit(1);
		Array[i] = a;
	}
	fclose(file);
}

Node* FillTreeFromArray(char const* filename, int* Array, int* i) {
	int node, node_left, node_right;
	node = Array[*i];
	node_left = Array[*i + 1];
	node_right = Array[*i + 2];
	Node* tree = CreateNode(node);
	if (node_left != 0) {
		(*i) += 3;
		tree->left = FillTreeFromArray(filename, Array, i);
	}
	if (node_right != 0) {
		(*i) += 3;
		tree->right = FillTreeFromArray(filename, Array, i);
	}
	return tree;
}

int** CreateAuxMartix(int m, int n) {
	int** Matrix = (int**)malloc(n * sizeof(int*));
	if (Matrix == NULL) {
		printf("memory allocation error\n");
		exit(1);
	}
	for (int i = 0; i < n; i++) {
		Matrix[i] = (int*)malloc(m * sizeof(int));
		if (Matrix[i] == NULL) {
			printf("memory allocation error\n");
			exit(1);
		}
	}
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) Matrix[i][j] = -1;
	return Matrix;
}

void FillAuxMartix(Node* tree, int j, int* i, int** Matrix) {
	if (tree != NULL) {
		FillAuxMartix(tree->left, j + 2, i, Matrix);
		Matrix[j][*i] = tree->data;
		Matrix[j + 1][*i] = abs(SubtreeHeight(tree->left) - SubtreeHeight(tree->right));
		(*i)++;
		FillAuxMartix(tree->right, j + 2, i, Matrix);
	}
}

void PrintTree(int** Matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i % 2 != 0) {
				if (Matrix[i][j] == -1) printf("   ");
				else printf("[%i]", Matrix[i][j]);
			}
			else {
				if (Matrix[i][j] == -1) printf("   ");
				else printf(" %i ", Matrix[i][j]);
			}
		}
		printf("\n");
	}
}

void General(char const* filename) {
	int n = SymbolCounter(filename);
	int* Array = (int*)malloc(n * sizeof(int));
	Node* tree = (Node*)malloc(sizeof(Node));

	int i = 0;

	ReadArray(filename, Array, n);
	tree = FillTreeFromArray(filename, Array, &i);

	int size = (SubtreeHeight(tree->left) > SubtreeHeight(tree->right)) ? SubtreeHeight(tree->left) : SubtreeHeight(tree->right);
	size = (size + 2) * 2;

	int** aux_matrix = CreateAuxMartix(n, size);
	i = 0;
	FillAuxMartix(tree, 0, &i, aux_matrix);
	PrintTree(aux_matrix, size, n);
}