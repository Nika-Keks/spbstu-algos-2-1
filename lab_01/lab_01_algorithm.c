#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"

//insert element as first in list
void insert_first(weather** head, weather* A) {
	A->next = (*head);
	(*head) = A;
}

//insert n-th element into list
void insert(weather* head, unsigned n, weather* A) {
	int i = 2;
	weather* tmp = NULL;
	//Find the required element. If we went beyond the limits of the list, then we exit the loop. There will be no error, it will insert at the end.
	while (i < n && head->next) {
		head = head->next;
		i++;
	}
	tmp = (weather*)malloc(sizeof(weather));
	tmp = A;
	//If this is not the last element, then move next to the next node
	if (head->next) {
		tmp->next = head->next;
	}
	//otherwise to NULL
	else {
		tmp->next = NULL;
	}
	head->next = tmp;
}

// sort by date of two elements
int Sort_date(weather* A, weather* B) {
	int n = 0;
	if (A->date.year > B->date.year) n = 1;
	else if (A->date.year < B->date.year) n = -1;
	else if (A->date.year = B->date.year) {
		if (A->date.month > B->date.month) n = 1;
		else if (A->date.month < B->date.month) n = -1;
		else if (A->date.month = B->date.month) {
			if (A->date.day > B->date.day) n = 1;
			else if (A->date.day < B->date.day) n = -1;
		}
	}
	return n;
}

// the function looks for what number the read element in the list should be
int Sort_grad(weather* head, weather* A) {
	int n = 1;
	if (head->grad == A->grad) {
		if (Sort_date(A, head) == -1) n = 1;
		else {
			while (Sort_date(A, head) == 1) {
				n++;
				if (head->next == NULL) break;
				else {
					head = head->next;
				}
			}
		}
	}
	else {
		if (head->grad > A->grad)n = 1;
		else {
			n = 1;
			while (head->grad < A->grad) {
				n++;
				if (head->next == NULL) break;
				else head = head->next;
				if (head->grad == A->grad) {
					if (Sort_date(A, head) == -1) break;
					else {
						head = head->next;
						n++;
						while ((head->grad == A->grad) && (Sort_date(A, head) == 1) && head->next != NULL) {
							head = head->next;
							n++;
						}
					}
				}
			}
		}
	}
	return n;
}

// reading a file into a list
void ReadText(weather** head, char* filename, int** N) {
	FILE* fin;// define file pointer
	fopen_s(&fin, filename, "r"); // open the file for reading
	if (fin == NULL) {
		printf("File open error");
		return -1;
	}
	((*head))->next = NULL;
	weather* first = (weather*)malloc(sizeof(weather));
	first = (*head);
	fscanf(fin, "%d.%d.%d  %lf", &first->date.day, &first->date.month, &first->date.year, &first->grad);
	int i = 1;
	while (!feof(fin)) {
		weather* tmp = (weather*)malloc(sizeof(weather));
		tmp->next = NULL;
		fscanf(fin, "%d.%d.%d  %lf ", &(tmp->date.day), &tmp->date.month, &tmp->date.year, &tmp->grad);
		int n;
		n = Sort_grad((first), tmp);
		if (n == 1) { insert_first((&first), tmp); }
		else { insert((first), n, tmp); }
		i++;
	}
	*N = i;
	fclose(fin);
	(*head) = first;
	return 0;
}

// print the list
void printLinkedList(weather* head, int N) {
	for (int i = 0; i < N; i++) {
		printf("%d.%d.%d  %lf\n", head->date.day, head->date.month, head->date.year, head->grad);
		head = head->next;
	}
	printf("\n");
}

// write out information about the days in which the temperature was less than '0'
void below_zero(weather* head, int N) {
	int i = 0;
	if (head->grad >= 0) {
		printf("There were no days when the temperature was less than '0'.\n\n");
	}
	else {
		printf("Information about the days when the temperature was less than '0':\n");
		while ((i < N) && (head->grad < 0)) {
			printf("%d.%d.%d  %lf\n", head->date.day, head->date.month, head->date.year, head->grad);
			head = head->next;
			i++;
		}
	}
	printf("\n");
}

// check if there is a day in the list with an average temperature entered from the keyboard
void check_temperature(weather* head, int* N) {
	printf("Enter a temperature to check if there is a day in the list with this average temperature:\n");
	double A = 0;
	scanf("%lf", &A);
	printf("\n");
	printf("Search:\n");
	int i = 0;
	int n = N;
	int flag = 0;
	while ((i < n) && (A >= (head->grad))) {
		if ((head->grad) == A) {
			printf("%d.%d.%d  %lf\n", head->date.day, head->date.month, head->date.year, head->grad);
			flag++;
		}
		head = head->next;
		i++;
	}
	if (flag == 0) printf("There are no days with the entered temperature in the list.\n");
}

//clearing memory
void ListDestroy(weather* A) {
	weather* number;
	weather* n;
	do {
		number = A;
		n = number->next;
		A = n;
		free(number);
	} while (n != NULL);
	free(A);
}