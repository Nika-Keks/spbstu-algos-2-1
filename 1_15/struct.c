#include <stdlib.h>
#include <assert.h>

typedef struct Node {
	char* value;
	struct Node* next;
} Node;

Node* listCreate() {
	Node* head = malloc(sizeof(Node));

	head->value = NULL;
	head->next = NULL;

	return head;
}

Node* listLast(Node* head) {
	Node* currentNode = head;

	while (currentNode->next != NULL) {
		currentNode = currentNode->next;
	}

	return currentNode;
}

Node* listAt(Node* head, int index) {
	Node* currentNode = head;
	int currentIndex = 0;

	while (currentIndex != index) {
		if (currentNode->next == NULL)
			assert(0);

		currentNode = currentNode->next;
		currentIndex += 1;
	}

	return currentNode;
}

void listPush(Node* head, char* value) {
	Node* lastNode = listLast(head);

	if (lastNode->value == NULL) {
		lastNode->value = value;
	}
	else {
		Node* node = malloc(sizeof(Node));

		node->value = value;
		lastNode->next = node;
	}
}

void listForEach(Node* head, void (*callBack)(char*)) {
	for (Node* node = head; node != NULL; node = node->next) {
		callBack(node->value);
	}
}