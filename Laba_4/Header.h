#pragma once

/*
* function returns the number of columns in the maze column matrix from the file
*/

int CountOfColumns(FILE * file);

/*
* function returns the number of lines in the maze matrix from the file
*/
int CountOfLines(FILE* file);

/*
* the function checks whether it is possible to move to the given cell
*/
int Is_Node(int x, int y, int** steps, int** matrix, int n, int m);


/*
* the function calculates the minimum path len in the maze
*/
void Steps(int x, int y, int end_x, int end_y, int** steps, int len, int** matrix, int* min_len,short* flag);

/*
* function creates a two-dimensional dynamic array filled with zeros
*/
int** CreateArray(int n, int m);

/*
* function cleans up the memory allocated for a two-dimensional dynamic array
*/
void FreeArray(int** Array, int n);

/*
* function prints a matrix
*/
void PrintMatrix(int** Matrix, int n, int m);

/*
* function creates a two-dimensional dynamic array
*/
int** CreateArrayFromFile(FILE* file, int n, int m);



