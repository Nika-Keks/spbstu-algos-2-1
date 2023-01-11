#pragma once
typedef struct _tree//structure of the search tree with additional information
{
	int key;//node data
	int pos;//the number of positive elements in the tree
	int nonp;//the number of non-positive elements in the tree
	struct _tree* left;//link to the left subtree
	struct _tree* right;//link to the right subtree
}tree;
int ReadConsol(tree** t);//filling the tree with elements entered in the console
int AddElem(tree** t, int x);//adding element x to the binary search tree
tree* Kmin(tree* t, int k);//finding the smallest positive element
void PrintTree(tree* t, int key, int k);//Output of positive elements smaller than the kth positive even element
void FreeTree(tree** t);//freeing up the memory allocated for the tree