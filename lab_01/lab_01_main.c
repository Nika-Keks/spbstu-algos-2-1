#pragma warning(disable : 4996)
#include <stdio.h>
#include "struct.h"


int main() {
	int* N; //The number of lines in the document being read.
	weather* head = (weather*)malloc(sizeof(weather)); //Create a pointer to the first element of the future list.	
	if (head == NULL)  printf("Memory allocation error");
	char* FILETXT = "List.txt";
	ReadText(&head, FILETXT, &N); //Reading a file into a list.
	printLinkedList(head, N); //Printing the List.
	below_zero(head, N); //Write out information about the days in which the temperature was less than '0'.
	check_temperature(head, N); //Check if there is a day in the list with an average temperature entered from the keyboard.
	if (head != NULL) {
		ListDestroy(head); //Clearing memory.
	}
}