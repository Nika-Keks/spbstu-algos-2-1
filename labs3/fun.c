#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#pragma warning(disable:4996)





//the function is engaged in inserting non-zero elements into the list simply one after another
void Insert(listNodePtr* sPtr, int a, int i, int j) {
	listNodePtr newPtr; // pointer to a new node
	listNodePtr previousPtr; // pointer to the previous node in the list
	listNodePtr currentPtr; // pointer to the current node in the list

	newPtr = (listNodePtr)malloc(sizeof(listNode)); // создать узел

	if (newPtr != NULL) { // if memory is allocated
		newPtr->row = i; // write the value to the node
		newPtr->col = j;
		newPtr->value = a;
		newPtr->nextPtr = NULL; // the node is not yet connected to another node

		previousPtr = NULL;
		currentPtr = *sPtr;
		// find a place in the list to insert a new node
		while (currentPtr != NULL) {
			previousPtr = currentPtr; // go to ...
			currentPtr = currentPtr->nextPtr; // ... to the next node

		}

		// insert a new node at the top of the list
		if (previousPtr == NULL) {
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;

		}
		else { // insert a new node between previousPtr and currentPtr
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;

		}

	}
	else {
		printf("No memory available.\n");

	}
}

//checking whether the list is empty
int isEmpty(listNodePtr sPtr)
{
	return sPtr == NULL;
}

// outputs a list
void printList(listNodePtr currentPtr)
{
	if (isEmpty(currentPtr)) {
		puts("List is empty.\n");
	}
	else {
		puts("The list is:");
		while (currentPtr != NULL) {
			printf("%d %d %d--> ", currentPtr->row, currentPtr->col, currentPtr->value);
			puts("");
			currentPtr = currentPtr->nextPtr;
		}
		puts("NULL\n");
	}
}


//the function is engaged in shifting either columns
//or rows of each matrix by n positions in order to further combine them into one large matrix
void Create(listNodePtr currentPtr, int idx, int n) {
	listNodePtr previousPtr;
	if (idx == 1) {
		while (currentPtr != NULL) {
			currentPtr->col = currentPtr->col + n;
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
	}
	if (idx == 2) {
		while (currentPtr != NULL) {
			currentPtr->row = currentPtr->row + n;
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
	}
	if (idx == 3) {
		while (currentPtr != NULL) {
			currentPtr->col = currentPtr->col + n;
			currentPtr->row = currentPtr->row + n;
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
	}
}

//the function combines four lists into one large corresponding to the final matrix 2*n by 2*n
void Union(listNodePtr* array) {
	listNodePtr currentPtr = array[0];
	while (currentPtr->nextPtr != NULL) {
		currentPtr = currentPtr->nextPtr;
	}

	currentPtr->nextPtr = array[1];

	while (currentPtr->nextPtr != NULL) {
		currentPtr = currentPtr->nextPtr;
	}
	currentPtr->nextPtr = array[2];

	while (currentPtr->nextPtr != NULL) {
		currentPtr = currentPtr->nextPtr;
	}
	currentPtr->nextPtr = array[3];
}

//the function is engaged in writing values from the combined list to a two-dimensional array p
void PtintMatrix(listNodePtr currentPtr, int** p) {
	while (currentPtr != NULL) {
		p[currentPtr->row][currentPtr->col] = currentPtr->value;
		currentPtr = currentPtr->nextPtr;
	}
}

//the function clears the merged list
void FREE(listNodePtr currentPtr) {
	listNodePtr tempNext;
	while (currentPtr != NULL) {
		tempNext = currentPtr;
		currentPtr = currentPtr->nextPtr;
		free(tempNext);
	}
}