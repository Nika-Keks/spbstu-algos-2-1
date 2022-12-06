#include "toposort.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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

FILE* fileOpen(char* name, char* mode) {
	return (FILE*)NotNull(fopen(name, mode));
}

void fileClose(FILE* file) {
	fclose(file);
}

Order* orderCreate(Node* front) {
	Order* order = SafeMalloc(sizeof(Order));
	order->front = front;
	order->front->refs += 1;
	order->next = NULL;
	return order;
}

void orderDestroy(Order* order) {
	order->front->refs -= 1;
	free(order);
}

void orderDestroyList(Order* head) {
	if (head != NULL) {
		Order* prev = head, * cur = head->next;
		orderDestroy(prev);
		while (cur != NULL) {
			prev = cur;
			cur = cur->next;
			orderDestroy(prev);
		}
	}
}

Node* nodeCreate(char name) {
	Node* node = SafeMalloc(sizeof(Node));
	node->name = name;
	node->next = NULL;
	node->order = NULL;
	node->refs = 0;
	return node;
}

void nodeDestroy(Node* node) {
	orderDestroyList(node->order);
	free(node);
}

Node* insertNode(Node* head, Node* node) {
	if (node->name < head->name) {
		node->next = head;
		return node;
	}
	Node* cur = head;
	while ((cur->next != NULL) && (node->name > cur->next->name)) {
		cur = cur->next;
	}
	node->next = cur->next;
	cur->next = node;
	return head;
}

Node* findNode(Node* head, char name) {
	Node* cur = head;
	while (cur != NULL) {
		if (cur->name == name) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

Order* lastOrderForNode(Node* node) {
	Order* cur = node->order;
	//printf("\n cur is %p\n", cur);
	if (cur == NULL) {
		return NULL;
	}
	while (cur->next != NULL) {
		cur = cur->next;
	}
	return cur;
}

void addCondition(Node* behind, Node* front) {
	Order* order = orderCreate(front);
	if (behind->order == NULL) {
		behind->order = order;
	}
	else {
		lastOrderForNode(behind)->next = order;
	}
}

Node* nodePairFromFile(FILE* file, Node* head, int* read) {
	char bch, ach;
	Node* behind, * front;
	if ((fscanf(file, "%c<%c\n", &bch, &ach)) != EOF) {
		*read = 1;
		if (head == NULL) {
			behind = nodeCreate(bch);
			front = nodeCreate(ach);
			head = insertNode(behind, front);
		}
		else {
			behind = findNode(head, bch);
			if (behind == NULL) {
				behind = nodeCreate(bch);
				head = insertNode(head, behind);
			}
			front = findNode(head, ach);
			if (front == NULL) {
				front = nodeCreate(ach);
				head = insertNode(head, front);
			}
		}
		addCondition(behind, front);
		/*Node* behind = nodeCreate(bch);
		Node* front = nodeCreate(ach);
		behind->next = front;
		addCondition(behind, front);
		return behind;*/
	}
	else {
		*read = 0;
	}
	return head;
}

Node* conditionsFromFile(FILE* file) {
	/*Node* behind = nodeFromFile(file);
	fscanf(file, ">");
	Node* front = nodeFromFile(file);
	fscanf(file, "\n");
	printf("%c %c", behind->name, front->name);*/
	int read;
	Node* head = nodePairFromFile(file, NULL, &read);
	while (read == 1) {
		head = nodePairFromFile(file, head, &read);
	}
	/*Node* head = nodePairFromFile(file, NULL);
	Node* prev = head;
	Node* cur = nodePairFromFile(file, head);
	while (cur != NULL) {
		prev->next->next = cur;
		prev = prev->next->next;
		cur = nodePairFromFile(file, head);
	}*/
	return head;
}

Node* conditionsFromFileByName(char* name) {
	FILE* file = fopen(name, "r");
	Node* head = conditionsFromFile(file);
	fclose(file);
	return head;
}

void printOrderList(Order* head) {
	Order* cur = head;
	while (cur != NULL) {
		printf("%c ", cur->front->name);
		cur = cur->next;
	}
	printf("\n");
}

void printNode(Node* node) {
	printf("%c\n", node->name);
}

void printNodeList(Node* head) {
	Node* cur = head;
	while (cur != NULL) {
		printf("%c with %i ref count is before: ", cur->name, cur->refs);
		printOrderList(cur->order);
		cur = cur->next;
	}
}

Node* printTopological(Node* head) {
	Node* cur = head;
	Node* printed;
	if (head->refs == 0) {
		head = head->next;
		printNode(cur);
		nodeDestroy(cur);
		return head;
	}
	while (cur->next != NULL) {
		if (cur->next->refs == 0) {
			printed = cur->next;
			cur->next = cur->next->next;
			printNode(printed);
			nodeDestroy(printed);
			return head;
		}
		cur = cur->next;
	}
}

void printTopologicalList(Node* head) {
	Node* cur = head;
	while (cur != NULL) {
		cur = printTopological(cur);
	}
}