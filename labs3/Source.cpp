#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)


//the node of the sheet in which the position of the 
//element in the matrix and the value of this element are recorded
struct listNode {
	int row;
	int col;
	int value;
	struct listNode* nextPtr;
};

typedef struct listNode listNode;
typedef struct listNode* listNodePtr;


void Insert(listNodePtr* sPtr, int a, int i, int j);
void printList(listNodePtr currentPtr);
int isEmpty(listNodePtr sPtr);
void Create(listNodePtr currentPtr, int idx, int n);
void Union(listNodePtr* array);
void PtintMatrix(listNodePtr currentPtr, int** p);
void FREE(listNodePtr currentPtr);

int main(void) {
	FILE* f;
	f = fopen("Matrix.txt", "r");
	if (f != NULL) {
		int n;
		fscanf_s(f, "%d", &n);
		int a;
		//creating an array of lists
        //each element of the array is a list to which the matrix corresponds
		listNodePtr array[4] = { NULL, NULL, NULL, NULL };
		for (int k = 0; k < 4; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					fscanf_s(f, "%d", &a);
					if (a != 0) {
						Insert(&array[k], a, i, j);
					}
					else {
						continue;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			printList(array[i]);
		}
		for (int i = 0; i < 4; i++) {
			Create(array[i], i, n);
		}
		Union(array);

		//we allocate memory for a matrix of size 2n by 2n
        //and fill it with zeros
		int** p = NULL;
		p = (int**)malloc(2 * n * sizeof(int*));
		if (p != NULL) {
			for (int i = 0; i < 2 * n; i++) {
				p[i] = (int*)malloc(2 * n * sizeof(int));
			}
			for (int i = 0; i < 2 * n; i++) {
				if (p[i] != NULL) {
					for (int j = 0; j < 2 * n; j++) {
						p[i][j] = 0;
					}
				}
			}
		}
		PtintMatrix(array[0], p);
		if (p != NULL) {
			for (int i = 0; i < 2 * n; i++) {
				if (p[i] != NULL) {
					for (int j = 0; j < 2 * n; j++) {
						printf("%d", p[i][j]);
					}
				}
				puts("");
			}
		}
		FREE(array[0]);
		fclose(f);
	}
	else {
		printf("Error");
	}
	return 0;
}

