#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lab3typ.h"

int main()
{
	int row1 = 0;//for the number of rows of the first matrix, taking into account its name
	int row2 = 0;//for the number of rows of the second matrix, taking into account its name
	int count = 0;//maximum number of characters per line
	int col1 = 0;//for the number of columns of the first matrix
	int col2 = 0;//for the number of columns of the second matrix
	int r;//for errors
	CountRowAndCol("matrix.txt", &row1, &row2, &count);
	if ((r = Compare(row1, row2)) != 0)//check for equality of the number of rows of matrices
	{
		return -1;//if they are not equal, then it is impossible to add matrices
	}
	rowf** A = CreateMas(row1);//we allocate memory for an array of pointers
	if (A == NULL)
	{
		return -1;//an error occurred in creating an array
	}
	rowf** B = CreateMas(row2);//we allocate memory for an array of pointers
	if (B == NULL)
	{
		return -1;//an error occurred in creating an array
	}
	r = ReadCreateMas("matrix.txt", A, row1, &col1, 2, count);//filling in the array of lists for the first matrix, for the first matrix, the rows with the value start from the second line of the file
	if (r != 0)
	{
		return -1;//an error occurred in filling the array
	}
	r = ReadCreateMas("matrix.txt", B, row2, &col2, 2 + row1, count);//filling in the array of lists for the second matrix, for the second matrix, the rows in the file with the value begin with a number that is equal to the sum of the rows from which the first matrix begins and the number of rows of the first matrix (2+row1)
	if (r != 0)
	{
		return -1;//an error occurred in filling the array
	}
	if ((r = Compare(col1, col2)) != 0)//check the equality of the number of columns of the matrices
	{
		return -1;//if they are not equal, then it is impossible to add matrices
	}
	int i = 0;
	rowf** C = CreateMas(row1);//we allocate memory for an array of pointers
	if (C == NULL)
	{
		return -1;//an error occurred in creating an array
	}
	r = SumMas(A, B, C, row1, col1);//filling in the array of lists
	if (r != 0)
	{
		return -1;//an error occurred in filling the array
	}
	PrintfMas(C, row1);//we output the matrix that turned out to be the sum of two matrices
	DeleteMas(A, row1);//deleting an array of lists
	DeleteMas(B, row2);//deleting an array of lists
	DeleteMas(C, row1);//deleting an array of lists
	return 0;
}