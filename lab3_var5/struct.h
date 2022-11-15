#pragma once
typedef struct _List {
    int position; //номер столбца
    double value; //значение 
    struct _List* next; // pointer to the next member of the list
}List;

int* Line_count(char* filename);//counm strings
int* Colomns_count(char* filename, int* n);//counm colomns
List** Read_Matrix(char* filename, int** N, int** M); //read and create matrix
void print_Matrix(List** Matr, int** N, int** M); //print the matrix
List** Sum_Matrix(List** Matr_A, List** Matr_B, int** N, int** M); //sum the matrix Matr_A with the matrix Matr_B
void Delete_String(List** list); //delete string
void DeleteMas(List* Matr[], int** N); //delete matrix