#include <stdio.h>
#include "bitree.h"

#pragma warning(disable:4996)

void optionsPrint() {
	printf("Options: \n");
	printf("1 - go to left child\n");
	printf("2 - go to right child\n");
	printf("3 - go to parent\n");
	printf("4 - remove left child\n");
	printf("5 - remove right child\n");
	printf("6 - delete current node\n");
	printf("7 - add node\n");
	printf("0 - exit\n");
}

int main() {
	/*Node* node = nodeCreate(1802);
	node->left = nodeCreate(445656354);
	node->right = nodeCreate(2394);
	node->parent = nodeCreate(21548);
	printNodeAndItsRelatives(node);*/
	printf("Goryunov Maxim 5030102/10002 Lab 5 Variant 15\n");
	printf("Input node data: ");
	int data;
	scanf("%i", &data);
	Node* tree = nodeAdd(
		NULL,
		nodeCreate(data)
	);
	printNodeAndItsRelatives(tree);
	optionsPrint();
	int option;
	scanf("%i", &option);
	while (option != 0) {
		if (option == 1) {
			tree = leftChild(tree);
		}
		else if (option == 2) {
			tree = rightChild(tree);
		}
		else if (option == 3) {
			tree = parent(tree);
		}
		else if (option == 4) {
			nodeRemove(tree->left);
		}
		else if (option == 5) {
			printf("calling node remove on right\n");
			nodeRemove(tree->right);
		}
		else if (option == 6) {
			Node* old = tree;
			tree = parent(tree);
			nodeRemove(old);
		}
		else if (option == 7) {
			printf("Input node data: ");
			int data;
			scanf("%i", &data);
			tree = nodeAdd(
				tree,
				nodeCreate(data)
			);
		}
		printNodeAndItsRelatives(tree);
		optionsPrint();
		scanf("%i", &option);
	}
	return 0;
}