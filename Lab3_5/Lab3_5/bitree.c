#include <stdio.h>
#include <stdlib.h>
#include "bitree.h"

#pragma warning(disable:4996)

#define NotNull(ptr) notNull(ptr, __LINE__)
#define SafeMalloc(size) safeMalloc(size, __LINE__)

void* notNull(void* ptr, int line) {
	if (ptr == NULL) {
		printf("Null pointer at %i\n", line);
		exit(1);
	}
	return ptr;
}

void* safeMalloc(int size, int line) {
	return notNull(malloc(size), line);
}

Node* nodeCreate(int data) {
	Node* node = SafeMalloc(sizeof(Node));
	node->data = data;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int nodeDigits(Node* node) {
	if (node == NULL) {
		return 0;
	}
	if (node->data == 0) {
		return 1;
	}
	int digits = 0;
	int num = node->data;
	while (num > 0) {
		num /= 10;
		digits += 1;
	}
	return digits;
}

int maxNum(int* nums, int n) {
	int max = nums[0];
	for (int i = 1; i < n; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
	}
	return max;
}

void nodePrintData(Node* node) {
	if (node != NULL) {
		printf("%i\n", node->data);
	}
}

void printSpaces(int n) {
	for (int i = 0; i < n; i++) {
		printf(" ");
	}
}

void printNodeAndItsRelatives(Node* node) {
	int digits[] = {
		nodeDigits(node->parent) / 2,
		nodeDigits(node) / 2,
		nodeDigits(node->left) + 2
	};
	int max = maxNum(digits, 4);
	//printf("max = %i", max);
	printSpaces(max - digits[0]);
	nodePrintData(node->parent);
	if (node->parent != NULL) {
		printSpaces(max);
		printf("|\n");
	}
	else {
		printf("\n");
	}
	printSpaces(max - digits[1]);
	nodePrintData(node);
	printSpaces(max - 2);
	printf("/   \\\n");
	printSpaces(max - digits[2]);
	if (node->left != NULL) {
		printf("%i   ", node->left->data);
	}
	else {
		printSpaces(max + 5);
	}
	if (node->right != NULL) {
		printf("%i\n", node->right->data);
	}
	else {
		printf("\n");
	}
}

Node* nodeEither(Node* node, Node* def, char* message) {
	if (node == NULL) {
		printf(message);
		return def;
	}
	return node;
}

Node* parent(Node* node) {
	return nodeEither(node->parent, node, "Parent element is NULL, unable to get it.\n");
}

Node* leftChild(Node* node) {
	return nodeEither(node->left, node, "Left child is NULL, unable to get it.\n");
}

Node* rightChild(Node* node) {
	return nodeEither(node->right, node, "Right child is NULL, unable to get it.\n");
}

void nodeDestroy(Node* node) {
	if (node != NULL) {
		nodeDestroy(node->left);
		nodeDestroy(node->right);
		free(node);
	}
}

Node* nodeAdd(Node* tree, Node* node) {
	if (tree == NULL) {
		return node;
	}
	if (node->data < tree->data) {
		tree->left = nodeAdd(tree->left, node);
		tree->left->parent = tree;
	}
	else {
		tree->right = nodeAdd(tree->right, node);
		tree->right->parent = tree;
	}
	return tree;
}

void nodeRemove(Node* node) {
	if (node != NULL && node->parent != NULL) {
		if (node->parent->left == node) {
			printf("Node is equal to parent left\n");
			node->parent->left = NULL;
		}
		else {
			printf("Node is equal to parent right\n");
			node->parent->right = NULL;
		}
	}
	nodeDestroy(node);
}