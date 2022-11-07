#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#pragma warning(disable:4996)

typedef struct listNode listNode;
typedef listNode* ListNodePtr;
struct listNode {
	listNode* nextptr;
	char* string;
	int n;
};

void insert(ListNodePtr* sPtr, char* a, int lenght);
int isEmpty(ListNodePtr sPtr);
void Print(char* a, int n);
void printList(ListNodePtr currentPtr);
int IsAlNum(char c);
int Compare(char* a, char* b, int c);
void first(ListNodePtr currentPtr, int N);
void second(ListNodePtr currentPtr, int N);
ListNodePtr ReadText(char const* filename);


int main(void) {
	setlocale(0, "");
	ListNodePtr startPtr = ReadText("file.txt");
	printf("The main point".\n");
	printList(startPtr);
	int F;
	printf("Enter the length of the word and you will see all words larger than this word.");
	scanf_s("%d", &F);
	first(startPtr, F);
	int S;
	printf("Enter the length of the word and you will get all the words of the same length .");
	scanf_s("%d", &S);
	second(startPtr, S);
	return 0;
}

