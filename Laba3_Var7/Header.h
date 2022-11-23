#pragma once


//the node of the sheet in which the position of the 
//element in the matrix and the value of this element are recorded
struct Matrix {
	int x;
	int y;
	int val;
	struct Matrix* nextPtr;
};

typedef struct Matrix Matrix;
typedef struct Matrix* MatrixPtr;


void Insert(MatrixPtr* sPtr, int a, int i, int j);
void printList(MatrixPtr currentPtr);
int isEmpty(MatrixPtr sPtr);
void Create(MatrixPtr currentPtr, int idx, int n);
void Union(MatrixPtr* array);
void MatrixToPrint(MatrixPtr currentPtr, int** p);
void FREE(MatrixPtr currentPtr);