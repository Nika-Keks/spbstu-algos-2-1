typedef struct Node {
	char* value;
	struct Node* next;
} Node;

Node* listCreate();

Node* listLast(Node* head);

Node* listAt(Node* head, int index);

void listPush(Node* head, char* value);

void listForEach(Node* head, void (*callBack)(char*));
