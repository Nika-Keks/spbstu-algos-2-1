#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#include<locale.h>
#pragma warning(disable:4996)

int Min(int a, int b) {
	return (a < b ? a : b);
}

int*** createMap(int n) {
	int*** matrix = (int***)malloc(n * sizeof(int**));
	for (int i = 0; i < n; i++) {
		matrix[i] = (int**)malloc(n * sizeof(int*));
	}
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			matrix[i][j] = (int*)malloc(2 * sizeof(int)); // [][][0] - time, [][][1] - cost
			matrix[i][j][0] = (i == j ? 0 : rand() % 10);
			matrix[i][j][1] = (i == j ? 0 : rand() % 10);

			if (i != j) {
				matrix[j][i] = (int*)malloc(2 * sizeof(int));
				matrix[j][i][0] = matrix[i][j][0]; //cause matrix are symmetric
				matrix[j][i][1] = matrix[i][j][1];
			}
		}

	}
	return matrix;
}

void recur(int*** matrix, int* town, int idx, int n, int time,
	int* timeMin, int money, int FixMoney, int* been, int* way) {
	if (time >= *timeMin || money > FixMoney) {
		return;
	}
	if (idx == n) {
		*timeMin = Min(time + matrix[town[idx - 1]][0][0], *timeMin);
		for (int i = 0; i < n; i++) {
			way[i] = town[i];
		}
		return;
	}
	for (int i = 1; i < n; i++) {
		if (been[i] == 1) continue;
		been[i] = 1;
		town[idx] = i;
		time += matrix[town[idx - 1]][town[idx]][0];
		money += matrix[town[idx - 1]][town[idx]][1];
		recur(matrix, town, idx + 1, n, time, &timeMin, money, FixMoney, been, way);
		been[i] = 0;//cause when go back to start this town must be "un-been"
	}

}