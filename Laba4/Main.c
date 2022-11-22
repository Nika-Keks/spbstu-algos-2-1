#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba4.h"
#pragma warning(disable:4996)

int main() {
	setlocale(LC_ALL, "Rus");
	int B, N, key = 1;
	int* a = ReadText("input.txt", &B, &N);
	int* answer = (int*)malloc(sizeof(int) * N);
	if (answer == NULL) { printf("Error"); return 0; }

	solve(N - 1, B, a, answer, 0, &key);
	if (key) {
		answer[0] = 0;
		WriteText("output.txt", answer, 1);
	}

	free(a);
	free(answer);
	return 0;
}