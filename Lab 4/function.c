#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <malloc.h>
#include <locale.h>
#include <stdbool.h>
#include "./Lib.h"

#pragma warning(disable:4996)

FILE* OpenFile(char* name, char* mode)// function for safe file's opening
{
	FILE* fp;
	if ((fp = fopen(name, mode)) == NULL)
	{
		printf("Failed to open file");
		exit(1);
	}
	return fp;
}

void FileClose(FILE* file)// function for file's closing
{
	fclose(file);
}

int Size(char* name)// getting size of field
{
	FILE* file;
	file = OpenFile(name, "r");
	int N = 0;
	fscanf(file, "%d", &N);
	FileClose(file);
	return N;
}

int** MemAllocation(int N)// allocation memory for two-dimensional array
{
	int** arr = (int**)malloc(N * sizeof(int*));
	for (int k = 0; k < N; k++) 
		arr[k] = (int*)malloc(N * sizeof(int));
	return arr;
}

bool* MemBoolAllocation(int N)// allocation memory for bool-type array
{
	bool* arr = (bool*)malloc(N * sizeof(bool));
	for (int i = 0;i < N;i++)
		arr[i] = false;
	return arr;
}

void Printer(int** arr, int N)// output on display for checking coordinates
{
	for (int i = N-1; i >= 0; i--)
	{
		for (int j = 0; j < N; j++)
			printf("%2d ", arr[i][j]);
		printf("\n");
	}
}

void WritingToFile(char* output_file, int N, int** board)//writing coordinates to file
{
	FILE* file;
	file = OpenFile(output_file, "w");
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (board[i][j] == 1)
			{
				fprintf(file, "%3d", j);
				fprintf(file, "%3d", i);
				fprintf(file, "\n");
			}
		}
	}
	FileClose(file);
}

//checking a place for possible variant of quenn's setting
bool Insertion(int x, int y, int** diag1, int** diag2, bool* lines, bool* numdiag1, bool* numdiag2)
{
	//checking lines and diagonals
	if (numdiag1[diag1[x][y]] == true || numdiag2[diag2[x][y]] == true || lines[x] == true)
		return false;
	else
		return true;
}
//algorithm of recursion
bool Recursion(int N, int** board, int y, int** diag1, int** diag2, bool* lines, bool* numdiag1, bool* numdiag2)
{
	if (y >= N)//end of recursion
	{
		return true;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			//checking a place for possible variant of quenn's setting
			if (Insertion(i, y, diag1, diag2, lines, numdiag1, numdiag2) == true)
			{
				//setting a queen
				board[i][y] = 1;
				lines[i] = true;
				numdiag1[diag1[i][y]] = true;
				numdiag2[diag2[i][y]] = true;
				//continue process of recurtion
				if (Recursion(N, board, y + 1, diag1, diag2, lines, numdiag1, numdiag2))
				{
					return true;
				}
				else
				{
					//removing a queen
					board[i][y] = 0;
					lines[i] = false;
					numdiag1[diag1[i][y]] = false;
					numdiag2[diag2[i][y]] = false;
				}
			}
		}
		return false;
	}
}

void Arrangment(char* data_file, char* output_file)
{
	int N = Size(data_file);
	int** board = MemAllocation(N);
	int** diag1 = MemAllocation(N);
	int** diag2 = MemAllocation(N);
	//auxiliary arrays with numbers of diagonals and lines
	bool* lines = MemBoolAllocation(N);
	bool* numdiag1 = MemBoolAllocation(2 * N - 1);// 2 * n -1 is number of diagonals
	bool* numdiag2 = MemBoolAllocation(2 * N - 1);
	//filling arrays : every diagonal has unique number
	for (int k = 0; k < N; k++)
		for (int c = 0; c < N; c++) 
		{
			diag1[k][c] = k + c;
			diag2[k][c] = k - c + N - 1;
			board[k][c] = 0;
		}
	if (Recursion(N, board, 0, diag1, diag2, lines, numdiag1, numdiag2))
	{	
		WritingToFile(output_file, N, board);
		Printer(board, N);
	}
	else
	{
		printf("For this N =  %d  solution does not exist", N);
	}
	
}

