#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"

//counm strings
int* Line_count(char* filename) {
    FILE* fin;// define file pointer
    fopen_s(&fin, filename, "r"); // open the file for reading
    int lines_count = 0; // strings counter
    while (!feof(fin))
    {
        if (fgetc(fin) == '\n')
            lines_count++;
    }
    lines_count++;
    fclose(fin);  // close file 
    int* final = (int*)malloc(sizeof(int));
    *final = lines_count;
    return final;
}

//counm colomns
int* Colomns_count(char* filename, int* n) {
    FILE* fin;// define file pointer
    fopen_s(&fin, filename, "r"); // open the file for reading
    char ch, flag = -1;
    int w = 0; // number counter
    while ((ch = fgetc(fin)) != EOF) {
        if (ch == ' ' || ch == '\n')
            flag = -1;
        else if (flag == -1) {
            flag = 1;
            w++;
        }
    }
    fclose(fin); // close file 
    w = w / (*n);
    int* final = (int*)malloc(sizeof(int));
    *final = w;
    return final;
}

//read and create matrix
List** Read_Matrix(char* filename, int** N, int** M) {
    FILE* fin;
    fopen_s(&fin, filename, "r");//open file
    List** Matr; //create an array to store stacks  
    Matr = (List**)malloc((**N) * sizeof(List*));
    if (Matr == NULL)  printf("Memory allocation error");
    List* head; //the pointer which we run through the lines
    head = (List*)malloc(sizeof(List));
    if (head == NULL)  printf("Memory allocation error");
    int y = 0; //strings counter
    double p; //variable into which we read elements
    int i; //number counter
    int position = 0;//element count in line
    for (y; y < **N; y++) {
        position = -1;
        p = 0;
        int r = -1;

        while (p == 0) { // find the first non-zero element
            fscanf(fin, "%lf ", &p);
            r++;
            position++;
        }

        //write the first element of the string
        List* tm = (List*)malloc(sizeof(List));
        if (tm == NULL)  printf("Memory allocation error");
        tm->next = NULL;
        tm->value = p;
        tm->position = position;
        head = tm;
        Matr[y] = head;

        for (i = 1 + r; i < (**N + 1); i++) { //write down all subsequent non-zero elements of the string
            fscanf(fin, "%lf ", &p);
            position++;
            if (p != 0) {
                List* tmp = (List*)malloc(sizeof(List));
                if (tmp == NULL)  printf("Memory allocation error");
                tmp->next = NULL;
                tmp->value = p;
                tmp->position = position;
                head->next = tmp;
                head = head->next;
            }
        }
    }
    fclose(fin); //close the file
    return Matr;
}

//print the matrix
void print_Matrix(List** Matr, int** N, int** M) {
    List* head = (List*)malloc(sizeof(List)); //the pointer which we run through the lines
    if (head == NULL)  printf("Memory allocation error");
    int pos; //element number counter
    for (int i = 0; i < **N; i++) { //run through all the lines
        head = Matr[i]; //return a pointer to the beginning of a new string
        pos = 0;
        for (int y = 0; y < **M; y++) {//run through all columns
            if (head->position != pos) {//write 0 if there is no value for this position
                printf("%lf  ", 0);
            }
            else {
                printf("%lf  ", head->value);
                if (head->next != NULL) {//write the value for this position
                    head = head->next;
                }
            }
            pos++;
        }
        printf("\n");
    }
}

//sum the matrix Matr_A with the matrix Matr_B
List** Sum_Matrix(List** Matr_A, List** Matr_B, int** N, int** M) {
    List** Matr; //create a new matrix in which we write the resulting sum
    Matr = (List**)malloc((**N) * sizeof(List*));
    if (Matr == NULL)  printf("Memory allocation error");
    List* head_A = (List*)malloc(sizeof(List)); //the pointer with which we run through the lines
    if (head_A == NULL)  printf("Memory allocation error");
    List* head_B = (List*)malloc(sizeof(List));  //the pointer with which we run through the lines
    if (head_B == NULL)  printf("Memory allocation error");
    int pos;  //element number count in string
    for (int i = 0; i < **N; i++) { //the loop is done for N rows

        pos = 0; //counter points to the element number in the string
        List* head_sum = (List*)malloc(sizeof(List));
        if (head_sum == NULL)  printf("Memory allocation error");
        head_sum->next = NULL;
        head_A = Matr_A[i]; //pointer to the first row element of the matrix Matr_A
        head_B = Matr_B[i];//pointer to the first row element of the matrix Matr_B

        //write the first element in the row for the new matrix
        if (head_A->position == head_B->position) {
            head_sum->value = head_A->value + head_B->value;
            head_sum->position = head_A->position;
            pos = head_A->position;
            head_A = head_A->next;
            head_B = head_B->next;
            pos++;
        }
        else if (head_A->position < head_B->position) {
            head_sum->value = head_A->value;
            head_sum->position = head_A->position;
            pos = head_A->position;
            head_A = head_A->next;
            pos++;
        }
        else if (head_A->position > head_B->position) {
            head_sum->value = head_B->value;
            head_sum->position = head_B->position;
            pos = head_B->position;
            head_B = head_B->next;
            pos++;
        }

        int flag = 0; //the flag is needed to terminate correctly after exiting the next loop
        Matr[i] = head_sum;
        for (int j = 0; j < **M; j++) { //the loop is done for all M columns
            //if the positions of the elements in two matrices are equal to the current position, write the sum of values for this position
            if ((head_A->position == head_B->position) && (head_A->position == pos)) {
                List* tmp = (List*)malloc(sizeof(List));
                if (tmp == NULL)  printf("Memory allocation error");
                tmp->next = NULL;
                tmp->value = head_A->value + head_B->value;
                tmp->position = pos;
                head_sum->next = tmp;
                if (head_A->next == NULL) {
                    flag = 1;
                    break;
                }
                else if (head_B->next == NULL) {
                    flag = -1;
                    break;
                }
                head_sum = head_sum->next;
                head_A = head_A->next;
                head_B = head_B->next;
            }

            //if only one of the elements is equal to the current position, write its value
            else if ((head_A->position == pos) && (head_B->position != pos)) {
                flag = 1;
                List* tmp = (List*)malloc(sizeof(List));
                if (tmp == NULL)  printf("Memory allocation error");
                tmp->next = NULL;
                tmp->value = head_A->value;
                tmp->position = head_A->position;
                head_sum->next = tmp;
                if (head_A->next == NULL) break;
                head_sum = head_sum->next;
                head_A = head_A->next;
            }

            //if only one of the elements is equal to the current position, write its value 
            else if ((head_A->position != pos) && (head_B->position == pos)) {
                flag = -1;
                List* tmp = (List*)malloc(sizeof(List));
                if (tmp == NULL)  printf("Memory allocation error");
                tmp->next = NULL;
                tmp->value = head_B->value;
                tmp->position = head_B->position;
                head_sum->next = tmp;
                if (head_B->next == NULL) break;
                head_sum = head_sum->next;
                head_B = head_B->next;
            }
            pos++;
        }

        //flag == 1 if both matrices run out of rows. in this case, the following conditions are not met
        if (flag == -1) { //flag == -1 if the row of matrix B has ended
            head_sum = head_sum->next;
            head_A = head_A->next;
            head_sum->next = head_A;
        }
        else if ((flag == 1) && (head_B->next != NULL)) { //flag == 1 if the row of matrix A has ended
            head_sum = head_sum->next;
            head_B = head_B->next;
            head_sum->next = head_B;
        }
    }
    return Matr;
}

//delete string
void Delete_String(List** list) {
    List* del; //removed element
    List* afterdel; //element after the removed element
    List* head; //the pointer which we run through the lines
    head = (List*)malloc(sizeof(List));
    int i = 0;
    if (head == NULL)  printf("Memory allocation error");
    do {
        del = head;  //assign the value of the first element
        afterdel = head->next;//assign the value of the element following the first one
        head = afterdel;//changing the first element of the list
        free(del);//deleting an element
        i++;
    } while (afterdel != NULL);//until the end of the list

}

//delete matrix
void DeleteMas(List* Matr[], int** N) {
    int i = 0;
    for (i; (i < **N - 1); i++) {
        Delete_String(&Matr[i]);  //delete the content of the string
        free(Matr[i]);  //delete the memory allocated for the string
    }
    free(Matr);
}
