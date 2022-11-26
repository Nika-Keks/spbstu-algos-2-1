#pragma once

struct TreeNode {
	int data;
	int deltanode;
	struct TreeNode* Right;
	struct TreeNode* Left;
};

typedef struct TreeNode TreeNode;
typedef TreeNode* TreeNodePtr;

void InsertNode(TreeNodePtr* TreePtr, int value);
int isEmpty(TreeNodePtr topPtr);
void Search(TreeNodePtr* TreePtr, int value, TreeNodePtr** tmp);
void Delete(TreeNodePtr* TreePtr, TreeNodePtr* tmp);
void preOrder(TreeNodePtr treePtr);