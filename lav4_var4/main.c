#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"






int main() {
    //scan all data
    char* FILETXT_availability = "road_availability.txt";  //file from which we will read the matrix which lists all the roads connecting the cities. 1 - there is a road. 0 - no roads
    char* FILETXT_time = "time.txt";  //file from which we will read the time it takes to get from one city to another
    char* FILETXT_prices = "prices.txt";  //file from which we will read the roads fares 
    int n = Line_count(FILETXT_availability);
    List** Matrix_availability = Read_Matrix(FILETXT_availability, n);
    printf("This matrix shows which cities are connected:\n");
    print_Matrix(Matrix_availability, n);
    List** Matrix_time = Read_Matrix(FILETXT_time, n);
    printf("\n\nThis matrix shows that time it takes to get from one city to another:\n");
    print_Matrix(Matrix_time, n);
    List** Matrix_prices = Read_Matrix(FILETXT_prices, n);
    printf("\n\nThis matrix shows how much it costs to get from one city to another:\n");
    print_Matrix(Matrix_prices, n);

    //recursion algorithm
    City* S = (City*)malloc(sizeof(City));
    S->number = 0;
    S->next = NULL;
    City* Smin = (City*)malloc(sizeof(City));
    int** Lmin = 50;
    int cost_max = 210;
    int cost = 0;
    salesman(0, n, Matrix_availability, Matrix_time, Matrix_prices, 0, &Lmin, 0, cost_max, cost, S, Smin);

    //print results
    int cost_final = count_final_cost(S, Matrix_prices);
    printf("\n\nResults:\n\nCost limit: %d\nFinal cost: %d\nAll the time: %d\n", cost_max, cost_final, Lmin);    
    print_result(S);
    printf("\nIt would be possible to visite all the cities in less time, following the path 0 - 1 - 2 - 4 - 5 - 3 - 0, but it would cost 340. The program has a cost limit, so another path was chosen.\n\n");
}