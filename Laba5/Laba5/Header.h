#pragma once

typedef struct _tree {
	int val;
	struct _tree* left;
	struct _tree* right;
} tree;

//insert elements as leaf of tree
void Insert(int r, tree** Tree);
//I choose binary tree of searching
tree* build(int n);
//fill tree
void Fill(int level, tree* Tree);
//return the depth of tree
int Depth(tree* Tree, int c);
//test function of print
void Print(tree* Tree);
//create helping matrix...
int** CreateMatrix(tree* Tree, int n, int m);
//...and then fill it...
void FillMatrix(tree* Tree, int** matrix, int n, int level, int delta);
//...and finally print it
void PrintMatrix(int** matrix, int n, int m);
