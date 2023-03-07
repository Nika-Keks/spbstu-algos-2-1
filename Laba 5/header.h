#pragma once
struct Node
{
	char* item;

	struct Node* Left;
	struct Node* Right;
};
typedef struct Node Node;
typedef struct Node* NodePtr;

void Insert(char item[100], char quality[100], NodePtr* tree);
NodePtr Creation(void);