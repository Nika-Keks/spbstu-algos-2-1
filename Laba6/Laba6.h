#pragma once

typedef struct _Tree {
	int val;
	int diff;
	struct _Tree* left;
	struct _Tree* right;
} Tree;

void Insert_Tree(Tree** A, int val);
void Remove_Tree(Tree** A, int val);
void Print_Tree_val(Tree* A);
void Print_Tree_diff(Tree* A);