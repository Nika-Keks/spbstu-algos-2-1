#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include "Header.h"
#pragma warning(disable:4996)




int main(void) {
	setlocale(0, "");
	ListNodePtr startPtr = ReadText("file.txt");
	printf("The main point\n");
		printList(startPtr);
	int F;
	printf("Enter the length of the word and you will see all words larger than this word.");
	scanf("%d", &F);
	first(startPtr, F);
	int S;
	printf("Enter the length of the word and you will get all the words of the same length .");
	scanf("%d", &S);
	second(startPtr, S);
	return 0;
}