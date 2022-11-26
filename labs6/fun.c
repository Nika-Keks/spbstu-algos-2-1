#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#pragma warning (disable:4996)

//the function inserts a new node into the tree
void InsertNode(TreeNodePtr* TreePtr, int value) {

	if (*TreePtr == NULL) {//when we go down to the very bottom we need to insert a sheet
		*TreePtr = (TreeNodePtr)malloc(sizeof(TreeNode));
		if (*TreePtr != NULL) {
			(*TreePtr)->data = value;
			(*TreePtr)->Right = NULL;
			(*TreePtr)->Left = NULL;
			(*TreePtr)->deltanode = 0; //the difference of nodes in the subtrees is zero since it is a leaf
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
		else if ((*TreePtr)->Right == NULL) {//the node is inserted into the right subtree if it is an empty subtree
			(*TreePtr)->deltanode--;
			InsertNode(&((*TreePtr)->Right), value);
		}
		else if ((*TreePtr)->deltanode <= 0) {//here we compare the number of nodes in two subtrees if there are fewer
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

//the function is engaged in finding the node that contains the value that we want to remove from the tree
void Search(TreeNodePtr* TreePtr, int value, TreeNodePtr** tmp) {
	if (*tmp) {
		return;
	}
	if (*TreePtr != NULL) {
		if ((*TreePtr)->data == value) {
			*tmp = TreePtr;
		}
		Search(&((*TreePtr)->Left), value, tmp);
		Search(&((*TreePtr)->Right), value, tmp);
	}
}

//the function removes an element from a subtree whose vertex is a node in
//which contains the value we want to delete
//in this subtree, a leaf that lies on the lowest of all sublevels is deleted
//we delete this leaf and rewrite the value from this leaf to the main node of our subtree
//thereby deleting the value that the user enters in order to delete it
void Delete(TreeNodePtr* TreePtr, TreeNodePtr* tmp) {
	//here we descend through recursion to the bottom of the subtree to the lowest level
//if there are more sheets in the left subtree, then remove the node from it
	if ((*TreePtr)->deltanode >= 0 && (*TreePtr)->Left) {
		(*TreePtr)->deltanode--;//we control the difference of nodes in the left and right subtrees
		Delete(&((*TreePtr)->Left), tmp);
	}
	else if ((*TreePtr)->Right && (*TreePtr)->deltanode <= 0) {
		(*TreePtr)->deltanode++;
		Delete(&((*TreePtr)->Right), tmp);
	}
	else {
		(*tmp)->data = (*TreePtr)->data;
		free(*TreePtr);//we are clearing the sheet that we are deleting
		*TreePtr = NULL;
	}
}

//traversing the tree and printing it
void preOrder(TreeNodePtr treePtr) {
	if (treePtr != NULL) {
		printf("%d ", treePtr->data);
		preOrder(treePtr->Left);
		preOrder(treePtr->Right);
	}
}

