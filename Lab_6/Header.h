#pragma once
struct TreeNode
{
	int value;
	int node_difference;
	struct TreeNode* Right;
	struct TreeNode* Left;
};

typedef struct TreeNode TreeNode;
typedef TreeNode* TreeNodePtr;

void InsertNode(TreeNodePtr* TreePtr, int value);
void DeleteNode(TreeNodePtr* TreePtr, TreeNodePtr* necessary);
void Seeker(TreeNodePtr TreePtr, int value, TreeNodePtr* necessary);
void OutputNode(TreeNodePtr TreePtr);
