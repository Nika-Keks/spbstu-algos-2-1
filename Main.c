#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include "./Func.c"
#pragma warning(disable:4996)

int main()
{
	system("chcp 1251");
	setlocale(LC_CTYPE, "RUSSIAN");
	FILE* file = OpenFile("lister.txt", "r");
	List* head = CreationFromFile(file);
	Printer(head);
	Input(head);
	FileClose(file);
}