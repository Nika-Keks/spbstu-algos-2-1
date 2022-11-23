#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#pragma warning(disable:4996)




void Insert(MatrixPtr* sPtr, int a, int i, int j) {
	MatrixPtr newPtr; 
	MatrixPtr previousPtr; 
	MatrixPtr currentPtr;
	/*����� ������� ��� ��������� ������ � ����������
	��� ��������� ��� ����������� �� ������ �� �����*/

	newPtr = (MatrixPtr)malloc(sizeof(Matrix));

	if (newPtr != NULL) {
		newPtr->x = i;
		newPtr->y = j;
		newPtr->val = a;
		newPtr->nextPtr = NULL;

		previousPtr = NULL;
		currentPtr = *sPtr;
		while (currentPtr != NULL) {
			previousPtr = currentPtr; 
			currentPtr = currentPtr->nextPtr; 

		}

		if (previousPtr == NULL) {
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;

		}
		else {
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;

		}

	}
	else {
		printf("������ ������\n");

	}
}

int isEmpty(MatrixPtr sPtr)
{
	return sPtr == NULL;
}

void printList(MatrixPtr currentPtr)
{
	if (isEmpty(currentPtr)) {
		puts("List is empty.\n");
	}
	else {
		puts("The list is:");
		while (currentPtr != NULL) {
			printf("%d %d %d--> ", currentPtr->x, currentPtr->y, currentPtr->val);
			puts("");
			currentPtr = currentPtr->nextPtr;
		}
		puts("NULL\n");
	}
}


//�������������� ������ ��� ���������� � ���� �������
void Create(MatrixPtr currentPtr, int idx, int n) {
	MatrixPtr previousPtr;
	if (idx == 1) {
		while (currentPtr != NULL) {
			currentPtr->y = currentPtr->y + n;
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
	}
	if (idx == 2) {
		while (currentPtr != NULL) {
			currentPtr->x = currentPtr->x + n;
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
	}
	if (idx == 3) {
		while (currentPtr != NULL) {
			currentPtr->y = currentPtr->y + n;
			currentPtr->x = currentPtr->x + n;
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
	}
}

//����������
void Union(MatrixPtr* array) {
	MatrixPtr currentPtr = array[0];
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

//���������� ������� � ��������� ������ ��� ������
void MatrixToPrint(MatrixPtr currentPtr, int** p) {
	while (currentPtr != NULL) {
		p[currentPtr->x][currentPtr->y] = currentPtr->val;
		currentPtr = currentPtr->nextPtr;
	}
}

void FREE(MatrixPtr currentPtr) {
	MatrixPtr tempNext;
	while (currentPtr != NULL) {
		tempNext = currentPtr;
		currentPtr = currentPtr->nextPtr;
		free(tempNext);
	}
}