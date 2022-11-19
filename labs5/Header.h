#pragma once

#define Inf 10
struct TreeNode {
	int data;
	int lists;
	struct TreeNode* Right;
	struct TreeNode* Left;
};

typedef struct TreeNode TreeNode;
typedef TreeNode* TreeNodePtr;

void InsertNode(TreeNodePtr* TreePtr, int value);
void Preorder(TreeNodePtr TreePtr);
int leafSum(TreeNodePtr TreePtr);
void Preorder2(TreeNodePtr TreePtr);
int ancestorMatrixRec(TreeNodePtr TreePtr, int mas[][Inf]);
void ancestorMatrix(TreeNodePtr TreePtr, int mas[][Inf]);