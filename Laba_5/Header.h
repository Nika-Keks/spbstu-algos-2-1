#pragma once

typedef struct _tree {
	int number;
	struct _tree* left;
	struct _tree* right;
}tree;

int Numbers_count(char* filename); //count numbers from txt file
int length_of_number(int n); //count amount of figures in number
void ReadMassiv(char* filename, int* Massiv, int N); //scan data from txt file to Massiv
tree* ReadTree(char* filename, int* Massiv, int* i); //write data from Massiv to tree
int** fill_array(int f, int high); //create array and fill it with 0
void PrintTree(int** Massiv, tree* Res, int y, int* x); //nodes and widths of nodes are written to an array
int Tree_Height(tree* tr); // count height of tree
void Print_Massiv(int** Massiv, int columns, int lines); //print array in console
