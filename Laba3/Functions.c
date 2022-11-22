#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba3.h"
#pragma warning(disable:4996)

/*
* The function of adding a node to the list
*/
void Insert(int x, int y, int val, List* Ptr) {
	List new, prev, cur;

	new = (List)malloc(sizeof(Node));
	if (new == NULL) printf("No memory avaible.\n");
	else {
		new->x = x;
		new->y = y;
		new->val = val;
		new->next = NULL;

		prev = NULL;
		cur = *Ptr;
		while (cur != NULL)
		{
			prev = cur;
			cur = cur->next;
		}

		if (prev == NULL) {
			new->next = *Ptr;
			*Ptr = new;
		}
		else {
			prev->next = new;
			new->next = cur;
		}
	}
}


/*
* The function checks whether the pointer is equal to the first pointer NULL (whether the list is empty)
*/
int isEmpty(List sPtr) {
	return sPtr == NULL;
}

/*
* Outputs all elements of the coordinate list
* If the list is empty, it displays an error message*/
void PrintList(List* MyList) {
	List CurrentPtr = (*MyList);
	if (isEmpty(CurrentPtr)) {
		puts("List is empty.");
	}
	else {
		puts("The list is:");
		while (CurrentPtr != NULL) {
			printf("row: %d\ncol: %d\nvalue: %d\n", CurrentPtr->x, CurrentPtr->y, CurrentPtr->val);
			CurrentPtr = CurrentPtr->next;
		}
	}
}

/*
* Combining 4 matrices into one (shifting coordinates)
*/
void Unitity(List** M, int len_M, int n) {
	for (int i = 0; i < len_M; i++) {
		List prev = NULL;
		List cur = *(M[i]);
		while (cur != NULL)
		{
			prev = cur;
			cur = cur->next;
			if (i == 1) prev->y += n;
			if (i == 2) prev->x += n;
			if (i == 3) {
				prev->x += n;
				prev->y += n;
			}
		}
		if (i != 3 && prev != NULL) prev->next = *(M[i + 1]);
	}
}


/*
* creates a dynamic array of size N*M
*/
int** dynamic_array_alloc(int N, int M) {    
	int** A = (int**)malloc(N * sizeof(int*));
	if (A == NULL) return NULL;
	for (int i = 0; i < N; i++) {
		A[i] = (int*)calloc(M, sizeof(int));
		if (A == NULL) return NULL;
	}
	return A;
}

/*
* Clearing a two-dimensional array
*/
void dynamic_array_free(int** A, int N) {
	for (int i = 0; i < N; i++) free(A[i]);
	free(A);
}


/*
* Clearing an array of lists (if you need to clear one list, then N = 1)
*/
void List_free(List** A, int N) {
	for (int i = 0; i < N; i++) {
		List cur = *(A[i]);
		List prev = NULL;
		while (cur != NULL)
		{
			prev = cur;
			cur = cur->next;
			free(prev);
		}
	}
	free(A);
}

/*
* Outputs a matrix (as a two-dimensional array)
*/
void PrintMatrix(List* Matrix, int n) {
	List cur = *Matrix;
	int** A = dynamic_array_alloc(n, n);
	while (cur != NULL) {
		A[cur->x][cur->y] = cur->val;
		cur = cur->next;
	}
	puts("Union Matrix:");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", A[i][j]);
		}
		puts("");
	}
	dynamic_array_free(A, n);
}

/*
* The function reads four matrices from the file, returns an array (in each cell there is a matrix)
*/
List** ReadText(char const* filename, int* n) { 
	
	FILE* f = fopen(filename, "r");
	if (f == NULL) return NULL;
	List** M = (List**)malloc(sizeof(List*) * 4);
	if (M == NULL) { printf("No memory avaible.\n"); return; }
	int value;
	fscanf(f, "%d", n);
	for (int k = 0; k < 4; k++) {
		List* Matrix = (List*)malloc(sizeof(List));
		if (Matrix == NULL) { printf("No memory avaible.\n"); return; }
		(*Matrix) = NULL;

		for (int i = 0; i < *n; i++) {
			for (int j = 0; j < *n; j++) {
				fscanf(f, "%d", &value);
				if (value != 0)
					Insert(i, j, value, Matrix);
			}
		}
		M[k] = Matrix;
	}
	fclose(f);
	return M;
}