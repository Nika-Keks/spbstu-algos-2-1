#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#include<locale.h>
#include<math.h>
#pragma warning(disable:4996)

int main() {
	//int n = 15;
	int n;
	scanf("%d", &n); //enter the acount of elements
	tree* Tree = build(n);
	Fill(1, Tree);
	int depth = Depth(Tree, 0) + 1; //n can be to big to be adequate depth
	int width = pow(2, depth + 1) - 1; //the worst case then matrix look like pyramide full of elements
	int** matrix = CreateMatrix(Tree, width, depth);
	FillMatrix(Tree, matrix, width / 2, 0, pow(2, depth - 1)); //start condition level=0, n=width/2, delta = 2^(d-1)
	PrintMatrix(matrix, width, depth);
	return 0;
}