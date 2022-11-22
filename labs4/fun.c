#include"Header.h"
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int SearchSet(int* a, int* arr, int n, int sum, int* main_key) {
	if (*main_key == 1) {
		return 1;
	}

	if (sum == 0) {
		*main_key = 1;
		return 1;
	}
	if (n < 0 || sum < 0) {
		return 0;
	}

	int  key = SearchSet(a, arr, n - 1, sum - a[n], main_key);
	if (key) arr[n] = a[n];

	int key1 = SearchSet(a, arr, n - 1, sum, main_key);

	return key || key1;
}

void WriteText(char const* filename, int* arr, int len) {
	FILE* f;
	f = fopen(filename, "w");
	if (f == NULL) return;
	for (int i = 0; i < len; i++) {
		if (arr[i] != 0)
			fprintf(f, "%d ", arr[i]);
	}
	fclose(f);
}

int* ReadText(char const* filename, int* B, int* N) {
	FILE* f;
	f = fopen(filename, "r");
	if (f == NULL) return NULL;
	if (fscanf(f, "%d%d", B, N) != 2) return NULL;
	int* arr = (int*)malloc(sizeof(int) * (*N));
	if (arr == NULL) return NULL;
	for (int i = 0; i < *N; i++) fscanf_s(f, "%d ", &arr[i]);
	fclose(f);
	return arr;
}