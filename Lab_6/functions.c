#include "Header.h"
#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)

void InsertNode(TreeNodePtr* TreePtr, int value) //inserts a new value into the shortest branch
{
	if (*TreePtr == NULL)//The case of an empy tree
	{
		*TreePtr = (TreeNodePtr)malloc(sizeof(TreeNode));
		if (*TreePtr != NULL)
		{
			(*TreePtr)->value = value;
			(*TreePtr)->Right = NULL;
			(*TreePtr)->Left = NULL;
			(*TreePtr)->node_difference = 0;
		}
		else {
			printf("No enough memory");
			return;
		}
	}
	else
	{
		if ((*TreePtr)->Left == NULL) //left branch is empty
		{
			(*TreePtr)->node_difference++;
			InsertNode(&((*TreePtr)->Left), value);
		}
		else if ((*TreePtr)->Right == NULL)//right branch is empty
		{
			(*TreePtr)->node_difference--;
			InsertNode(&((*TreePtr)->Right), value);
		}
		else if ((*TreePtr)->Left->node_difference <= (*TreePtr)->Right->node_difference) //left branch contains less amount of nodes then right
		{
			(*TreePtr)->node_difference++;
			InsertNode(&((*TreePtr)->Left), value);
		}
		else//right branch contains less amount of nodes then left
		{
			(*TreePtr)->node_difference--;
			InsertNode(&((*TreePtr)->Right), value);
		}
	}
}


void DeleteNode(TreeNodePtr* TreePtr, TreeNodePtr* necessary)//replaces the desired value in the tree and replaces it with the longest leaf
{
	if ((*TreePtr)->node_difference >= 0 && (*TreePtr)->Left)
	{
		(*TreePtr)->node_difference--;
		DeleteNode(&((*TreePtr)->Left), necessary);
	}
	else if ((*TreePtr)->node_difference < 0 && (*TreePtr)->Right)
	{
		(*TreePtr)->node_difference++;
		DeleteNode(&((*TreePtr)->Right), necessary);
	}
	else if ((*TreePtr)->Left == NULL && (*TreePtr)->Right == NULL)
	{
		(*necessary)->value = (*TreePtr)->value;
		free((*TreePtr));
		*TreePtr = NULL;
	}
}

void Seeker(TreeNodePtr TreePtr, int value, TreeNodePtr* necessary)//returns the address of the node with the desired value
{
	if (*necessary) return;//if necessary node was successfully found
	if (TreePtr != NULL)
	{
		if (TreePtr->value == value)
		{
			*necessary = TreePtr;
		}
		Seeker(TreePtr->Left, value, necessary);
		Seeker(TreePtr->Right, value, necessary);
	}
}

void OutputNode(TreeNodePtr TreePtr)//ptrints values of nodes
{
	if (TreePtr != NULL)
	{
		OutputNode(TreePtr->Left);
		OutputNode(TreePtr->Right);
		printf("%d ", TreePtr->value);
	}
}
