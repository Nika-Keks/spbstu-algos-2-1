#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#pragma warning(disable:4996)

#include "Header.h"

/*
Считать из текстового файла все строчки и заполнить список, содержащий следующую информацию: текст строки и его длина. 
Список должен заполняться таким образом, чтобы длины строк располагались в порядке возрастания. 
Вывести на экран 10 самых длинных строк. 
Ввести с клавиатуры число и проверить, есть ли в списке строка (или строки), имеющие такую длину.
Вывести их на экран.
*/


int main() {
	char* filename = "test.txt";
	lines* List = StructFill(filename);
	PrintList(List);
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	PrintList_n(List, n);
	PrintList_10(List);
	return 0;
}
