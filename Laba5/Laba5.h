#pragma once

typedef struct _Tree{
	int count;
	struct _Tree* left;
	struct _Tree* right;
} Tree;


Tree* Create_Tree(int n);
void Print_Tree(Tree* A, int n);