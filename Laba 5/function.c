#include "header.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable:4996)
void Insert(char* item, char* quality, NodePtr* tree)
{
	int answer;
	if (*tree == NULL)
	{
		*tree = (NodePtr)malloc(sizeof(Node));
		(*tree)->Left = NULL;
		(*tree)->Right = NULL;
		(*tree)->item = (char*)malloc(sizeof(char) * 100);
	}
	if ((*tree)->Left == NULL && (*tree)->Right == NULL)//check if  node a list
	{
		printf("Is new animal a %s\n 1 = yes\n 0 = no\n", (*tree)->item);
		scanf("%d", &answer);
		if (answer == 1) return;
		else
		{
			char* saved = (*tree)->item;
			(*tree)->item = (char*)malloc(sizeof(char) * 100);
			for (int i = 0; i <= 100; i++) (*tree)->item[i] = quality[i];
			(*tree)->Left = (NodePtr)malloc(sizeof(Node));
			(*tree)->Right = (NodePtr)malloc(sizeof(Node));
			(*tree)->Left->item = (char*)malloc(sizeof(char) * 100);
			for (int i = 0; i <= 100; i++) (*tree)->Left->item[i] = item[i];
			(*tree)->Right->item = saved;
			(*tree)->Left->Left = NULL;
			(*tree)->Left->Right = NULL;
			(*tree)->Right->Left = NULL;
			(*tree)->Right->Right = NULL;
			return;
		}
	}

	printf("does it have the following quality: %s?\n 1 = yes\n 0 = no\n", (*tree)->item);
	scanf("%d", &answer);
	if (answer == 1) Insert(item, quality, &(*tree)->Left);
	else Insert(item, quality, &(*tree)->Right);
}

NodePtr Creation(void)
{
	NodePtr tree = (NodePtr)malloc(sizeof(Node));
	tree->item = "wool";
	tree->Left = (NodePtr)malloc(sizeof(Node));
	tree->Right = (NodePtr)malloc(sizeof(Node));
	tree->Left->item = "bear";
	tree->Right->item = "pig";
	tree->Left->Left = NULL;
	tree->Left->Right = NULL;
	tree->Right->Left = NULL;
	tree->Right->Right = NULL;
	return tree;
}