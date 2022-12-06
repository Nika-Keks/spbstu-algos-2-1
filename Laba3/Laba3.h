#pragma once

typedef struct Node Node;
typedef struct Node* List;

struct Node {
	int x;
	int y;
	int val;
	struct Node* next;
};

void List_free(List** A, int N);
void Unitity(List** M, int len_M, int n);
void PrintMatrix(List* Matrix, int n);
List** ReadText(char const* filename, int* n);
