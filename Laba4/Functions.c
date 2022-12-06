#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba4.h"
#pragma warning(disable:4996)


void WriteText(char const* filename, int* arr, int len) {
	FILE* f = fopen(filename, "w");
	if (f == NULL) return;
	if (arr[0] == 0) fprintf(f, "%d ", arr[0]);
	for (int i = 0; i < len; i++) {
		if (arr[i] != 0)
			fprintf(f, "%d ", arr[i]);
	}
	fclose(f);
}

/*
* the function iterates through the options recursively.
* The task is to dial the required amount S (in this implementation, to reach S = 0),
* every time I add an element to the set, it is written to the array, otherwise 0 will be written to this position,
* which I will not output (0 means that I did not take the ith element).
* If the condition is met, the global counter is triggered,
* the array is written to a file and the program is terminated.
* asymptotics: O(N*2^N)
*/
void solve(int i, int S, int* a, int* answer, int len, int* key) {
	if (S < 0 || i < 0 || !(*key)) return;
	if (a[i] == S && (*key)) {
		answer[i] = a[i];
		*key = 0;
		WriteText("output.txt", answer, len + 1);
		return;
	}
	answer[i] = a[i];
	solve(i - 1, S - a[i], a, answer, len + 1, key);
	if (!(*key)) return;
	answer[i] = 0;
	solve(i - 1, S, a, answer, len + 1, key);
}



int* ReadText(char const* filename, int* B, int* N) {
	FILE* f = fopen(filename, "r");
	if (f == NULL) return NULL;
	if (fscanf(f, "%d%d", B, N) != 2) return NULL;
	int* arr = (int*)malloc(sizeof(int) * (*N));
	if (arr == NULL) return NULL;
	for (int i = 0; i < *N; i++) fscanf(f, "%d ", &arr[i]);
	fclose(f);
	return arr;
}