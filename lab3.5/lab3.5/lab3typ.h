#pragma once
#pragma once
typedef struct _row {//list for table row
	long int value;//the value of the string element is non-zero
	int number;//column number of a non-zero element
	struct _row* next;//the next element in the list
} row;

typedef struct _rowf
{
	struct _row* first;//to store the beginning of the list
} rowf;

rowf** CreateMas(int countrow);
/*countrow-the number of rows of the matrix, taking into account the row with the name of the matrix
*the function allocates memory for an array of lists
*/

int PushElement(rowf** list, int val, int num);//writing an item to the end of the list
/*list-the list to which we add the element
* val-the value of the matrix element being written to the list
* num-the column number of the matrix element to be written to the list
*/
void DeleteRow(rowf** list);//deleting a list from the first item

void DeleteMas(rowf* maslis[], int countrow);//deleting an array of lists
/*maslis[]-array of lists
* couòtrow-the number of rows of the matrix, taking into account the row with the name of the matrix
*/

int Compare(int c1, int c2);//to compare the sizes of matrices, since if the matrices are not of the same size, then they cannot be folded

void CountRowAndCol(char* filename, int* r1, int* r2, int* count);//a function to count the number of rows in matrices and the maximum number of elements in a row
/*filename-file name
* r1-number of rows of the first matrix
* r2-number of rows of the second matrix
* count-the maximum number of elements in a row is stored in this variable
*/

int ReadCreateMas(char* filename, rowf* maslist[], int countrow, int* countcolu, int inl, int count);//creating an array of lists from a file
/*filename-file name
* masliså[]-array of lists
* countrow-the number of rows of the matrix, taking into account the row with the name of the matrix
* countcol-number of columns in the matrix
* inl-the line from which the filling of the array of lists begins
* count-the maximum number of elements in a row is stored in this variable
*/
int SumMas(rowf* A[], rowf* B[], rowf* C[], int rowc, int col);//for matrix summation
/*A[]-array of lists for the first matrix
* B[]-array of lists for the second matrix
* C[]-an array of lists resulting from the addition of two matrices
* rowc-the number of rows of the matrix, taking into account the row with the name of the matrix
* col-number of matrix columns
*/

void PrintfMas(rowf* C[], int row);
/*C[]
* row-the number of rows of the matrix, taking into account the row with the name of the matrix
*/