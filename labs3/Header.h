#pragma once



//the node of the sheet in which the position of the 
//element in the matrix and the value of this element are recorded
struct listNode {
	int row;
	int col;
	int value;
	struct listNode* nextPtr;
};

typedef struct listNode listNode;
typedef struct listNode* listNodePtr;


void Insert(listNodePtr* sPtr, int a, int i, int j);
void printList(listNodePtr currentPtr);
int isEmpty(listNodePtr sPtr);
void Create(listNodePtr currentPtr, int idx, int n);
void Union(listNodePtr* array);
void PtintMatrix(listNodePtr currentPtr, int** p);
void FREE(listNodePtr currentPtr);