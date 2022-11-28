#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"

int Line_count(char* filename) //count strings
{
    FILE* fin;// define file pointer
    fin = fopen(filename, "r");
    int lines_count = 0; // strings counter
    while (!feof(fin))
    {
        if (fgetc(fin) == '\n')
            lines_count++;
    }
    lines_count++;
    fclose(fin);
    return lines_count;
}

List** Read_Matrix(char* filename, int N) //read and create matrix
{
    FILE* fin;
    fin = fopen(filename, "r");
    List** Matr; //create an array to store stacks  
    Matr = (List**)malloc((N) * sizeof(List*));
    if (Matr == NULL)  printf("Memory allocation error");
    List* head = (List*)malloc(sizeof(List)); //the pointer which we run through the lines
    if (head == NULL)  printf("Memory allocation error");
    int y = 0; //strings counter
    int p; //variable into which we read elements
    int i; //number counter
    int position = 0;//element count in line
    for (y; y < N; y++) {
        position = -1;
        p = 0;
        int r = -1;

        while (p == 0) { // find the first non-zero element
            fscanf(fin, "%d ", &p);
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

        for (i = 1 + r; i < (N); i++) { //write down all subsequent non-zero elements of the string
            fscanf(fin, "%d ", &p);
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
    fclose(fin);
    return Matr;
}

void print_Matrix(List** Matr, int N) //print the matrix
{
    List* head = (List*)malloc(sizeof(List)); //the pointer which we run through the lines
    if (head == NULL)  printf("Memory allocation error");
    int pos; //element number counter
    for (int i = 0; i < N; i++) { //run through all the lines
        head = Matr[i]; //return a pointer to the beginning of a new string
        pos = 0;
        for (int y = 0; y < N; y++) {//run through all columns
            if (head->position != pos) {//write 0 if there is no value for this position
                printf("%d  ", 0);
            }
            else {
                printf("%d  ", head->value);
                if (head->next != NULL) {//write the value for this position
                    head = head->next;
                }
            }
            pos++;
        }
        printf("\n");
    }
}


//k - city previous
// i - city next
//Matrix_availability - initial data
int neighbours(int k, int i, List** Matrix_availability) // chack if there is a road between city k and city i
{
    List* head = (List*)malloc(sizeof(List)); //the pointer which we run through the lines
    if (head == NULL)  printf("Memory allocation error");
    head = Matrix_availability[k];
    int w = 0;
    for (int y = 0; y < (i + 1); y++) {
        if (head->position == i) {
            w = 1;
            break;
        }
        else {
            if (head->next != NULL) {
                head = head->next;
            }
        }
    }
    return w;

}

//k - city previous
// i - city next
//Matrix_time - initial data
int check_time(int k, int i, List** Matrix_time) //what time it takes to go from city k to i 
{
    List* head = (List*)malloc(sizeof(List)); //the pointer which we run through the lines
    if (head == NULL)  printf("Memory allocation error");
    head = Matrix_time[k];
    while (head->position != i) {
        head = head->next;
    }
    int C = head->value;
    return C;
}

//k - city previous
// i - city next
//Matrix_prices - initial data
int prices(int k, int i, List** Matrix_prices) // what it costs to go from city k to i
{
    List* head = (List*)malloc(sizeof(List)); //the pointer which we run through the lines
    if (head == NULL)  printf("Memory allocation error");
    head = Matrix_prices[k];
    while (head->position != i) {
        head = head->next;
    }
    int C = head->value;
    return C;
}

// i - new element
//queue - stack
void add_el(City* queue, int i) //add element to the end of the stack
{

    //go to the end of the stack
    while (queue->next != NULL) {
        queue = queue->next;
    }

    //add new element
    City* tmp = (City*)malloc(sizeof(City));
    tmp->number = i;
    tmp->next = NULL;
    queue->next = tmp;
    queue = queue->next;
}

//queue - stack
void delete_el(City* queue) //deletelast element fron the stack
{

    //go to the end of the stack
    while (queue->next != NULL)
    {
        queue = queue->next;
    }

    //delete last element
    City* n = queue;
    queue = queue->next;
    free(queue);
    n->next = NULL;
}


//queue - stack
// i - number of city
int attendance(int i, City* queue) //check up have we been to city number i or not. (if thete is city i in stack queue) 
{
    int flag = 0;
    if (queue->number == i) {
        flag = 1;
    }
    while (queue->next != NULL) {
        queue = queue->next;
        if (queue->number == i) {
            flag = 1;
            break;
        }
    }
    return flag;

}

//queue - stack
int CountCity(City* queue) //count cities in stack
{
    int flag = 1;
    if (queue->next == NULL) {
        flag = 1;
    }
    while (queue->next != NULL) {
        queue = queue->next;
        flag++;
    }
    return flag;
}


//v - city in which we are now
// N - total number of cities
// Matrix_availability, Matrix_time, Matrix_prices - initial data
// first - first city
// time_min - time it takes to get to destination
// time - time it takes to get to current city
// cost_max - given max cost
// cost - current cost
//Path - path we traveled
// Path_min - best path we traveled
void salesman(int v, int N, List** Matrix_availability, List** Matrix_time, List** Matrix_prices, int first, int** time_min, int time, int cost_max, int cost, City* Path, City* Path_min) {
    int i = 0;//counter. city where we want to go
    for (i = 0; i < N; i++) //check up all cities
    {
        int neighbour = neighbours(v, i, Matrix_availability); //check up if there is a road from city v to city i
        if (neighbour == 1) //if we found the road
        {
            int duration = check_time(v, i, Matrix_time);
            int  price = prices(v, i, Matrix_prices);
            if (((time + duration) < *time_min) && (cost < cost_max)) {
                int d = CountCity(Path);//counted the number of cities in stack
                if (i == first && d == N) {
                    *time_min = time + duration;
                    Path_min = Path;
                }
                else {
                    int T = attendance(i, Path);
                    if (T == 0)
                    {
                        add_el(Path, i);
                        time = time + duration;
                        cost = cost + price;
                        salesman(i, N, Matrix_availability, Matrix_time, Matrix_prices, first, time_min, time, cost_max, cost, Path, Path_min);
                        delete_el(Path);
                        time = time - duration;
                        cost = cost - price;
                    }
                }
            }
        }
    }
}

//S - stack
void print_result(City* S) //print a sequence of cities
{
    printf("\nBest route:\n");
    int S_first = S->number;
    int i = 1; //counter
    printf("%d city: %d\n", i, S->number);
    while (S->next != NULL) {
        S = S->next;
        i++;
        printf("%d city: %d\n", i, S->number);
    }
    printf("destination: %d\n", S_first);
}


//S - stack
int count_final_cost(City* S, List** Matrix_prices) // count final cost
{
    int S_prev = S->number; //remember previous number
    int S_first = S->number;
    int cost; //to find cost
    int i = 0;//counter
    while (S->next != NULL) {
        S = S->next;
        cost = prices(S_prev, S->number, Matrix_prices);
        i = i + cost;
        S_prev = S->number;
    }
    cost = prices(S_prev, S_first, Matrix_prices);
    i = i + cost;
    return i;
}