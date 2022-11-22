#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <malloc.h>
#include <locale.h>
#include <stdbool.h>
#pragma warning(disable:4996)
 
FILE* OpenFile(char* name, char* mode);// function for safe file's opening
void FileClose(FILE* file);// function for file's closing
int Size(char* name);// getting size of field
int** MemAllocation(int N);// allocation memory for two-dimensional array
bool* MemBoolAllocation(int N);// allocation memory for bool-type array
void Printer(int** arr, int N);// output on display for checking coordinates
void WritingToFile(char* output_file, int N, int** board);//writing coordinates to file
//checking a place for possible variant of quenn's setting
bool Insertion(int x, int y, int** diag1, int** diag2, bool* lines, bool* numdiag1, bool* numdiag2);
//algorithm of recursion
bool Recursion(int N, int** board, int y, int** diag1, int** diag2, bool* lines, bool* numdiag1, bool* numdiag2);
//function for union all functions
void Arrangment(char* data_file, char* output_file);