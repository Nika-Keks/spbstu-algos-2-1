#pragma warning(disable : 4996)
#include <stdio.h>
#include "struct.h"

int main() {  
    char* FILETXTA = "MatrixA.txt";    //file from which we will read the first matrix
    int* n_a = Line_count(FILETXTA);  //count the number of rows in the matrix
    int* m_a = Colomns_count(FILETXTA, n_a);  //count the number of columns in the matrix
    List** MatrixA = Read_Matrix(FILETXTA, &n_a, &m_a);  //read the first matrix 
    printf("First matrix:\n"); 
    print_Matrix(MatrixA, &n_a, &m_a);//write the first matrix
    printf("\n");
    char* FILETXTB = "MatrixB.txt";  //file from which we will read the second matrix
    int* n_b = Line_count(FILETXTB);  //count the number of rows in the matrix   
    int* m_b = Colomns_count(FILETXTB, n_b); //count the number of columns in the matrix
    List** MatrixB = Read_Matrix(FILETXTB, &n_b, &m_b); //read the second matrix
    printf("Second matrix:\n");
    print_Matrix(MatrixB, &n_b, &m_b);  //write the second matrix 
    
    if ((*n_a == *n_b) && (*m_a == *m_b)) { //check that the matrices have the same size, otherwise they cannot be summed
        printf("\n");
        printf("Sum of matrices:\n");
        List** Matrix_Sum = Sum_Matrix(MatrixA, MatrixB, &n_a, &m_a); //sum two matrices, write the result as a new matrix
        print_Matrix(Matrix_Sum, &n_a, &m_a); //write the resulting matrix
        DeleteMas(Matrix_Sum, &n_a); //clear the memory
    }
    else { printf("Matrix addition is not possible."); } //do not add the matrices, because they have different sizes

    //clear the memory
    DeleteMas(MatrixA, &n_a);
    DeleteMas(MatrixB, &n_b);    
}