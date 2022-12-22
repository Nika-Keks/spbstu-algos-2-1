#include "toposort.h"

#pragma warning(disable:4996)

int main() {
	printf("Goryunov Maxim 5030102/10002 Lab 3 Variant 14\n");
	Node* head = conditionsFromFileByName("conds.txt");
	printTopologicalList(head);
	/*printNodeList(head);
	printf("----------\n");
	head = printTopological(head);
	printf("----------\n");
	printNodeList(head);*/
	return 0;
}