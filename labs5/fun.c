#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Header.h"
#pragma warning(disable:4996)


//the function inserts an element into the tree
//the tree is implemented as a binary search tree
//so if the element is smaller than the ancestor, it is sent to the left node
void InsertNode(TreeNodePtr* TreePtr, int value) {

	if (*TreePtr == NULL) {
		*TreePtr = (TreeNodePtr)malloc(sizeof(TreePtr));
		if (*TreePtr != NULL) {
			(*TreePtr)->data = value;
			(*TreePtr)->Right = NULL;
			(*TreePtr)->Left = NULL;
		}
		else {
			printf("NO memory available");
			return;
		}

	}
	else {
		if (value <= ((*TreePtr)->data)) {
			InsertNode(&((*TreePtr)->Left), value);
		}
		if (value > ((*TreePtr)->data)) {
			InsertNode(&((*TreePtr)->Right), value);
		}
	}
}

/*
The Pre Order function performs a crawl in three stages :
1) processes the node value;
2) calls preOrder to traverse the left subtree;
3) calls preOrder to traverse the right subtree;
*/
void Preorder(TreeNodePtr TreePtr) {
	if (TreePtr != NULL) {
		printf("%d ", TreePtr->data);
		Preorder(TreePtr->Left);
		Preorder(TreePtr->Right);
	}
}

/*
The pre Order 2 function performs a three-step crawl :
1) processes the node value;
2) calls preOrder to traverse the left subtree;
3) calls preOrder to traverse the right subtree;
it outputs the number of leaves for each node
*/
void Preorder2(TreeNodePtr TreePtr) {
	if (TreePtr != NULL) {
		printf("for %d a %d lists\n", TreePtr->data, TreePtr->lists);
		Preorder2(TreePtr->Left);
		Preorder2(TreePtr->Right);
	}
}

//the function recursively counts the number of leaves for each node
int leafSum(TreeNodePtr TreePtr) {
	if (TreePtr == NULL) {
		return 0;
	}
	if (TreePtr->Left == NULL && TreePtr->Right == NULL) {
		TreePtr->lists = 1;
		return 1;
	}
	else {
		TreePtr->lists = leafSum(TreePtr->Left) + leafSum(TreePtr->Right);
		return TreePtr->lists;
	}
}

//the function fills in a matrix whose size is equal to the largest value of all
//that we could get using rand()
//mas[i][j] = 1 if i is ancestor of j
//mas[i][j] = 0, otherwise

int ancestorMatrixRec(TreeNodePtr TreePtr, int mas[][Inf])
{
	if (TreePtr == NULL) return 0;;

	int l = ancestorMatrixRec(TreePtr->Left, mas);
	int r = ancestorMatrixRec(TreePtr->Right, mas);
	if (TreePtr->Left != NULL) {
		mas[TreePtr->data][l] = 1;
	}
	if (TreePtr->Right != NULL) {
		mas[TreePtr->data][r] = 1;
	}
	return TreePtr->data;
}

//the function outputs the ancestral matrix
void ancestorMatrix(TreeNodePtr TreePtr, int mas[][Inf])
{
	for (int i = 0; i < Inf; i++)
	{
		for (int j = 0; j < Inf; j++) {
			printf("%d ", mas[i][j]);
		}
		puts("");
	}
}

