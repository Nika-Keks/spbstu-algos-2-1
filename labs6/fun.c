#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#pragma warning (disable:4996)

//the function inserts nodes into the tree 
void InsertNode(TreeNodePtr* TreePtr, int value) {

	if (*TreePtr == NULL) {//when we go down to the very bottom we need to insert a sheet
		*TreePtr = (TreeNodePtr)malloc(sizeof(TreeNode));
		if (*TreePtr != NULL) {
			(*TreePtr)->data = value;
			(*TreePtr)->Right = NULL;
			(*TreePtr)->Left = NULL;
			(*TreePtr)->deltanode = 0;//the difference of nodes in the subtrees is zero since it is a leaf
		}
		else {
			printf("NO memory available");
			return;
		}
	}
	else {
		if ((*TreePtr)->Left == NULL) {//the node is inserted to the left if the left subtree is empty
			(*TreePtr)->deltanode++;
			InsertNode(&((*TreePtr)->Left), value);
		}
		else if ((*TreePtr)->Right == NULL) {
			// the node is inserted into the right subtree if it is an empty subtree
			(*TreePtr)->deltanode--;
			InsertNode(&((*TreePtr)->Right), value);
		}
		else if ((*TreePtr)->deltanode <= 0) {
			//here we compare the number of nodes in two subtrees if there are fewer
			//nodes in the left or as many as in the right then the node is sent there
			(*TreePtr)->deltanode++;
			InsertNode(&((*TreePtr)->Left), value);
		}
		else {
			(*TreePtr)->deltanode--;
			InsertNode(&((*TreePtr)->Right), value);
		}
	}
}

//checking whether the tree is empty
int isEmpty(TreeNodePtr topPtr) {
	return topPtr == NULL;
}


//the function finds the node where the value we want to delete lies
void Search(TreeNodePtr TreePtr, int value, TreeNodePtr* tmp) {
	if (*tmp) {
		return;
	}
	if (TreePtr != NULL) {
		if (TreePtr->data == value) {
			*tmp = TreePtr;
		}
		Search(TreePtr->Left, value, tmp);
		Search(TreePtr->Right, value, tmp);
	}
}

//the function removes an element from the tree according to the following algorithm
// if the nodes on the left of the tree are greater or equal to the nodes on the right
//otherwise we delete from the right
// deletion occurs so that we go down to the lowest level
// from there we delete the leaf and remember its value to write to the node
//where the value lies which we want to delete
void Delete(TreeNodePtr* TreePtr, TreeNodePtr* tmp) {

	if ((*TreePtr)->deltanode >= 0 && (*TreePtr)->Left) {
		(*TreePtr)->deltanode--;//controlling the difference of nodes in subtrees
		Delete(&((*TreePtr)->Left), tmp);
	}
	else if ((*TreePtr)->Right && (*TreePtr)->deltanode <= 0) {
		(*TreePtr)->deltanode++;
		Delete(&((*TreePtr)->Right), tmp);
	}
	else {
		(*tmp)->data = (*TreePtr)->data;
		free(*TreePtr);
		*TreePtr = NULL;
	}
}


/*
The Pre Order function performs a crawl in three stages :
1) processes the node value;
2) calls preOrder to traverse the left subtree;
3) calls preOrder to traverse the right subtree;
*/
void preOrder(TreeNodePtr treePtr) {
	if (treePtr != NULL) {
		printf("%d ", treePtr->data);
		preOrder(treePtr->Left);
		preOrder(treePtr->Right);
	}
}


