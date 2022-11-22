#pragma once
/*This command renames the type of our struct ListNode structure to just ListNode */
typedef struct listNode listNode;

/*This command renames the pointer type to the ListNode* structure to just ListNodePtr*/
typedef listNode* ListNodePtr;

/*A structure designed to store data in a list node and a pointer to the next node*/
struct listNode {
	listNode* nextptr;
	char* string;
	int n;
};

/*The function of inserting a new node into the list*/
void insert(ListNodePtr* sPtr, char* a, int lenght);

/*The function checks whether the list is empty*/
int isEmpty(ListNodePtr sPtr);

/*prints one word that is in the node*/
void Print(char* a, int n);

/*The function prints a linked list, that is, all the words in the list */
void printList(ListNodePtr currentPtr);

/*Checks whether the character is a letter or a separating character*/
int IsAlNum(char c);

/*compares words in lexicographic order (using an ASCII table)*/
int Compare(char* a, char* b, int c);

/*you enter a number and the function outputs all words having a length greater than this number*/
void first(ListNodePtr currentPtr, int N);

/*you enter a number and the function outputs all words having a length equal to this number*/
void second(ListNodePtr currentPtr, int N);

/*performs character-by-character reading from a file*/
ListNodePtr ReadText(char const* filename);
