#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba6.h"
#pragma warning(disable:4996)

int main() {
	setlocale(LC_ALL, "Rus");
	int val, a;
	Tree* MyTree = NULL;
	printf("�������:\n1 - �������� �������\n2 - ������� �������\n3 - ������� ������\n4 - ��������� ������\n");
	scanf("%d", &a);
	while (a != 4) {
		if (a == 1) {
			printf("������� ��������: ");
			scanf("%d", &val);
			Insert_Tree(&MyTree, val);
		}
		else if (a == 2) {
			printf("������� ��������: ");
			scanf("%d", &val);
			Remove_Tree(&MyTree, val);
		}
		else if (a == 3) {
			if (MyTree == NULL) puts("������ �����");
			else {
				printf("�������� � ������: ");
				Print_Tree_val(MyTree);
				printf("\n������� � ������: ");
				Print_Tree_diff(MyTree);
				puts("");
			}
		}
		else {
			puts("�������� ��������");
		}
		printf("�������:\n1 - �������� �������\n2 - ������� �������\n3 - ������� ������\n4 - ��������� ������\n");
		scanf("%d", &a);
	}
	return 0;
}