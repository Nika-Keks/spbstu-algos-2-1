#pragma once
typedef struct _tree {//tree structure
	int data;//tree data entered by the user
	int weight;//width of subtrees
	struct _tree* left;//link to the left subtree
	struct _tree* right;//link to the right subtree
}tree;
int ReadTreeConsole(tree** t, int* n);/*function for filling the tree with data
t-binary tree
n-number of nodes in the tree
*/
int CountNum(int x);//the function of counting the number of characters at the nodes of the tree
int CreateTree(int x, tree** k);//the function of adding a node to the tree,x-the number we want to add to the tree k
int CountH(tree** t);//function for determining the height of the tree
void ReadReverseOrder(tree** t);//traversing the tree in reverse order and changing the width under the trees if they are not leaves
int** InitAuxTable(int str, int sto);//Initializing the auxiliary table, str-number of rows, sto-number of columns
void CreateAuxTable(tree** t, int y, int** A,int*x);/*the function creates a matrix that we will print
t is a binary tree
y is the string in which we enter the value
A-auxiliary matrix
x-to determine the column of the matrix to which we add the element*/
void PrintAuxTable(int** B, int str, int sto);//to better view the structure of the tree
void FreeAuxTable(int** B, int sto);//we release the memory allocated for the auxiliary matrix
void FreeTree(tree** t);//freeing the memory that was allocated for the tree