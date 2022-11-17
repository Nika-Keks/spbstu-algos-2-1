#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#pragma warning(disable:4996)
#include "Header.h"



/*the function inserts a new node into our list,
the insertion takes place immediately, taking into account the length of the word
if the words are of the same length, the insertion occurs in lexicographic order
*/

void insert(ListNodePtr* sPtr, char* a, int lenght) {
	ListNodePtr newPtr;
	ListNodePtr previousPtr;
	ListNodePtr currentPtr;

	newPtr = (ListNodePtr)malloc(sizeof(listNode));

	if (newPtr != NULL)//if it was possible to allocate memory, we write the string and the length of the string into the structure
	{
		newPtr->string = a;
		newPtr->n = lenght;
		newPtr->nextptr = NULL;

		previousPtr = NULL;
		currentPtr = *sPtr;
		while (currentPtr != NULL && lenght > currentPtr->n)// we run through the list until the length of our word is greater than the length in the node

		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextptr;
		}
		while (currentPtr != NULL && !Compare(a, currentPtr->string, lenght) && lenght == currentPtr->n)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextptr;
		}
		if (previousPtr == NULL) {
			newPtr->nextptr = *sPtr;
			*sPtr = newPtr;
		}
		else {
			previousPtr->nextptr = newPtr;
			newPtr->nextptr = currentPtr;
		}
	}
	else {
		printf("No memory available.\n");
	}
}

/*The function checks whether the list is empty*/
int isEmpty(ListNodePtr sPtr) {
	return sPtr == NULL;
}

/*The function prints a linked list, that is, all the words in the list*/
void printList(ListNodePtr currentPtr) {
	if (isEmpty(currentPtr)) {
		puts("List is empty.\n");
	}
	else {
		puts("The list is:");
		while (currentPtr != NULL) {
			Print(currentPtr->string, currentPtr->n);
			currentPtr = currentPtr->nextptr;
		}
	}
}

/*compares words in lexicographic order (using an ASCII table)*/
int Compare(char* a, char* b, int c) {
	for (int i = 0; i < c; i++) {
		if (a[i] < b[i]) {
			return 1;
		}
		if (a[i] > b[i]) {
			return 0;
		}
	}
	return 0;
}

/*prints one word that is in the node*/
void Print(char* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%c", a[i]);
	}
	puts("");
}

/*performs character-by-character reading from a file*/
ListNodePtr ReadText(char const* filename) {
	ListNodePtr StartPtr = NULL;
	FILE* f;
	int length = 0;//string length
	char a[4000];//two buffers for reading from a file
	char b[4000];
	int j = 0;//word length counter
	f = fopen(filename, "r+");
	if (f != NULL) {//if it was possible to open the file
		while (fgets(a, 4000, f)) {
			length = strlen(a);
			for (int i = 0; i < length; i++) {
				if (IsAlNum(a[i])) {//if the character is not a separator
					b[j] = a[i];
					j++;
				}
				else {
					if (j != 0) {
						char* word = (char*)malloc(j * sizeof(char));
						strncpy(word, b, j);
						insert(&StartPtr, word, j);
						j = 0;
					}
				}
			}
			if (j != 0) {//if there is a word at the end that needs to be written to the list
				char* word = (char*)malloc(j * sizeof(char));
				if (word != NULL) {
					strncpy(word, b, j);
					insert(&StartPtr, word, j);
					j = 0;
				}
			}
			j = 0;
		}
		fclose(f);
	}
	else {
		printf("Error.");//if the file could not be opened
	}
	return StartPtr;
}

/*Checks whether the character is a letter or a separating character
if yes then we return zero if not then 1*/
int IsAlNum(char c) {
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))return 1;
	return 0;
}

/*you enter a number and the function outputs all words having a length greater than this number*/
void first(ListNodePtr currentPtr, int N)
{
	if (isEmpty(currentPtr)) {
		puts("List is empty.\n");
	}
	else {
		puts("The list is:");
		while (currentPtr != NULL) {
			if (currentPtr->n > N)
				Print(currentPtr->string, currentPtr->n);
			currentPtr = currentPtr->nextptr;
		}
	}
}

/*you enter a number and the function outputs all words having a length equal to this number*/
void second(ListNodePtr currentPtr, int N)
{
	if (isEmpty(currentPtr)) {//checking whether the list is empty
		puts("List is empty.\n");
	}
	else {
		puts("The list is:");
		while (currentPtr != NULL) {
			if (currentPtr->n == N)
				Print(currentPtr->string, currentPtr->n);
			currentPtr = currentPtr->nextptr;
		}
	}
}