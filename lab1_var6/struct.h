#pragma once

//create a structure in which we will write dates
typedef struct _Date {
	int day; 
	int month; 
	int year; 
}Date;

//create a structure in which we will write the date and the average temperature on that day for a singly linked list
typedef struct _weather {
	Date date;
	double  grad; //average temperature
	struct _weather* next; // pointer to the next member of the list
}weather;

void insert_first(weather** head, weather* A); //insert element as first in list
void insert(weather* head, unsigned n, weather* A); //insert n-th element into list
int Sort_date(weather* A, weather* B); // sort by date of two elements
int Sort_grad(weather* head, weather* A); // the function looks for what number the read element in the list should be
void ReadText(weather** head, char* filename, int** N); // reading a file into a list
void printLinkedList(weather* head, int N); //print the list
void below_zero(weather* head, int N); //write out information about the days in which the temperature was less than '0'
void check_temperature(weather* head, int* N); //check if there is a day in the list with an average temperature entered from the keyboard
void ListDestroy(weather* A); //clearing memory