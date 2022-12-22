#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#pragma warning(disable:4996)

Tree* CreateNode(Tree* father) {
	Tree* node = (Tree*)malloc(sizeof(Tree));
	if (node == NULL) {
		printf("memory allocation error");
		exit(1);
	}
	node->left = NULL;
	node->right = NULL;
	node->father = father;
	node->number = 0;
	return node;
}

void Add(Tree** tree) {
	if (*tree == NULL) {
		Tree* root = CreateNode(NULL);
		*tree = root;
		return;
	}
	Tree* cur_node = *tree;
	while ((cur_node)->left != NULL || (cur_node)->right != NULL) {
		if ((cur_node)->left == NULL) {
			Tree* leaf = CreateNode(cur_node);
			cur_node->number++;
			cur_node->left = leaf;
			return;
		}
		if (cur_node->right == NULL) {
			Tree* leaf = CreateNode(cur_node);
			cur_node->number--;
			cur_node->right = leaf;
			return;
		}
		if ((cur_node)->number <= 0) {
			(cur_node)->number++;
			cur_node = (cur_node)->left;
		}
		else {
			(cur_node)->number--;
			cur_node = (cur_node)->right;
		}
	}
	Tree* leaf = CreateNode(cur_node);
	cur_node->number++;
	cur_node->left = leaf;
}


void Delete(Tree** tree) {
	if (*tree == NULL) {
		printf("empty tree\n");
		return;
	}
	Tree** cur_node = tree;
	while ((*cur_node)->left != NULL || (*cur_node)->right != NULL) {
		if ((*cur_node)->left == NULL) {
			(*cur_node)->number++;
			cur_node = &((*cur_node)->right);
			continue;
		}
		if ((*cur_node)->right == NULL) {
			(*cur_node)->number--;
			cur_node = &((*cur_node)->left);
			continue;
		}
		if ((*cur_node)->number >= 0) {
			(*cur_node)->number--;
			cur_node = &((*cur_node)->left);
		}
		else {
			(*cur_node)->number++;
			cur_node = &((*cur_node)->right);
		}
	}
	free(*cur_node);
	*cur_node = NULL;
}

void PrintTree(Tree* tree) {
	if (tree != NULL) {
		PrintTree(tree->left);
		printf("%d ", tree->number);
		PrintTree(tree->right);
	}
}
