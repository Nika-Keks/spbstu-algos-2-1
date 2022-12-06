#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
	char* FILE_TXT = "Tree.txt";
	int N = Numbers_count(FILE_TXT);
	int* Massiv = (int*)malloc(N * sizeof(int));
	ReadMassiv(FILE_TXT, Massiv, N); //scan data from txt file to Massiv
	tree* Res = (tree*)malloc(sizeof(tree));
	int* i = (int*)malloc(sizeof(int));
	*i = 0;
	Res = ReadTree(FILE_TXT, Massiv, i);	//write data from Massiv to tree
	int f = N / 3; //number of nodes
	int  h = Tree_Height(Res);//height of tree
	int** Mas = fill_array(f, h);
	int* t = (int*)malloc(sizeof(int));
	*t = 0;
	PrintTree(Mas, Res, 0, t); //nodes and widths of nodes are written to an array
	printf("The program scan the tree from the txt file, calculates the height of each node, look at ():\n");
	Print_Massiv(Mas, f, 2 * h); //print array in console
}