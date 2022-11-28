#pragma once

typedef struct _List {
    int position; //number of colomn
    int value; //value
    struct _List* next; // pointer to the next member of the list
}List; // structure for matrix

typedef struct _City {
    int number; //number of city
    struct _City* next; // pointer to the next member of the list
}City; // structure for path


int Line_count(char* filename); //count strings
List** Read_Matrix(char* filename, int N); //read and create matrix
void print_Matrix(List** Matr, int N); //print the matrix
int neighbours(int k, int i, List** Matrix_availability); // chack if there is a road between city k and city i
int check_time(int k, int i, List** Matrix_time); //what time it takes to go from city k to i 
int prices(int k, int i, List** Matrix_prices); // what it costs to go from city k to i
void add_el(City* queue, int i); //add element to the end of the stack
void delete_el(City* queue); //deletelast element fron the stack
int attendance(int i, City* queue); //check up have we been to city number i or not. (if thete is city i in stack queue) 
int CountCity(City* queue); //count cities in stack
void salesman(int v, int N, List** Matrix_availability, List** Matrix_time, List** Matrix_prices, int first, int** time_min, int time, int cost_max, int cost, City* Path, City* Path_min);//recursion
void print_result(City* S); //print a sequence of cities
int count_final_cost(City* S, List** Matrix_prices); // count final cost