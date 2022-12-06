#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba5.h"
#pragma warning(disable:4996)

int main() {
	setlocale(LC_ALL, "Rus");
	int n;
	printf("Введите кол-во элементов: n = ");
	scanf("%d", &n);
	while (n <= 0) {
		printf("Введите коректное кол-во элементов (n >= 1): n = ");
		scanf("%d", &n);
	}
	Tree* MyTree = Create_Tree(n);
	Print_Tree(MyTree, n);
	return 0;
}