#pragma warning(disable : 4996)
#include <locale.h>
#include <stdio.h>
#include "List.h"
int main()
{
	setlocale(LC_CTYPE, "RUSSIAN");
	int n;
	FILE* file = OpenFile("Test.txt", "r");
	List* head = CreationFromFile(file);
	int cnt = KolvoStrok(head);
	printf("�������, ����������, ������� ����� �� ������ �������? (����� � ����� %d �����) \n", cnt);
	scanf("%d", &n);
	Printer(head, cnt, n);
	Input(head);
	FileClose(file);
}