#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#pragma warning(disable:4996)



int main(void) {
	FILE* f;
	f = fopen("Matrix.txt", "r");
	if (f != NULL) {
		int n;
		fscanf(f, "%d", &n);
		int a;
		/*создаем массив списков
		элемент-список - матрица*/
		MatrixPtr array[4] = { NULL, NULL, NULL, NULL };
		for (int k = 0; k < 4; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					fscanf(f, "%d", &a);
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

		/*освобождаем память для большой матрицы 
		и заполняем нулями*/
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
		MatrixToPrint(array[0], p);
		if (p != NULL) {
			for (int i = 0; i < 2 * n; i++) {
				if (p[i] != NULL) {
					for (int j = 0; j < 2 * n; j++) {
						printf("%d ", p[i][j]);
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