#include<stdio.h>
#include<stdlib.h>
#include"Header.h"
#include<locale.h>
#pragma warning(disable:4996)

int main() {
	int n = 10;
	int timeMin = 100000;//something very big
	int FixMoney = 60;
	int*** matrixOfRoads = createMap(n);
	printf("The matrix is\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", matrixOfRoads[i][j][1]);
		}
		printf("\n");
	}
	printf("The way is\n");
	int* town = (int*)malloc(n * sizeof(int)); //my towns
	int* way = (int*)malloc(n * sizeof(int)); //my best way!!!
	way[0] = -1; //its for case when we can't found way
	town[0] = 0; //i start for 0th town
	int* been = (int*)calloc(n , sizeof(int)); //towns i've been
	recur(matrixOfRoads, town, 1, n, 0, &timeMin, 0, FixMoney, been, way);
	if (way[0] == -1) printf("oh no! there's no enough money to travel(");
	else {
		for (int i = 0; i < n; i++) {
			printf("%d->", way[i]);
		}
		printf("0");
	}


	return 0;
}





