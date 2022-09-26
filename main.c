#pragma warning(disable : 4996)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "./algorithm.c"

int main()
{
	setlocale(LC_CTYPE, "Rus");

	int lines_count;

	lines_count = Number_lines();
	char** array = (char**)malloc(sizeof(char*) * lines_count); 
	Array_Data_Creation(lines_count, array);

	char** arr_words = (char**)malloc(sizeof(char*) * lines_count);
	Array_Words_Creation(array, lines_count, arr_words);

	char** arr_numbers = (char**)malloc(sizeof(char*) * lines_count);
	Array_Numbers_String(array, lines_count, arr_numbers);

	int* arr_numbers_int = (int*)malloc(sizeof(int) * lines_count);
	Array_Numbers_Int(arr_numbers_int, arr_numbers, lines_count);

	Sort(arr_numbers_int, arr_numbers, lines_count, arr_words);

	Create_And_Print_List(arr_words, arr_numbers, lines_count);

	char word[40];
	printf("¬ведите слово: ");
	scanf("%s", &word);

	Check_Word(word, arr_words, lines_count, arr_numbers);

	char number[40];
	printf("¬ведите число: ");
	scanf("%s", &number);

	Check_Number(number, arr_words, lines_count, arr_numbers);

	free(array);
	free(arr_words);
	free(arr_numbers);
	free(arr_numbers_int);

	return 0;
}