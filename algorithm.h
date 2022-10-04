#pragma warning(disable : 4996)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "./structure.h"

int Number_lines();
void Array_Data_Creation(int lines_count, char** array);
void Array_Words_Creation(char** array, int lines_count, char** arr_words);
void Array_Numbers_String(char** array, int lines_count, char** arr_numbers);
void Array_Numbers_Int(int* arr_numbers_int, char** arr_numbers, int lines_count);
void Sort(int* arr_numbers_int, char** arr_numbers, int lines_count, char** arr_words);
void Create_And_Print_List(char** arr_words, char** arr_numbers, int lines_count);
void Check_Word(char word[], char** arr_words, int lines_count, char** arr_numbers);
void Check_Number(char number[], char** arr_words, int lines_count, char** arr_numbers);

//function description

int Number_lines()
{
	int lines_count = 0;
	FILE* file = fopen("spisok.txt", "r");
	if (file == NULL)
	{
	    printf("File is empty.\n");
	}
	else
	{
		while (!feof(file))
		{
			if (fgetc(file) == '\n')
				lines_count++;
		}
		lines_count++;
		fclose(file);
		return lines_count;
	}
}

void Array_Data_Creation(int lines_count, char** array)
{
	FILE* file = fopen("spisok.txt", "r");
	char line[40];
	int j = 0;
	for (int k = 0; k < lines_count; k++)
	{
		array[k] = (char*)malloc(sizeof(char) * 40);
	}
	for (int i = 0; i < lines_count; i++)
	{
		fgets(line, 40, file);

		memcpy(array[i], line, 40);	

		memset(line, 0, strlen(line));
		j = 0;
	}
}

void Array_Words_Creation(char** array, int lines_count, char** arr_words)
{


	int j_1 = 0;
	for (int q = 0; q < lines_count; q++)
	{
		arr_words[q] = (char*)malloc(sizeof(char) * 40);
	}
	for (int i_1 = 0; i_1 < lines_count; i_1++)
	{
		while (array[i_1][j_1] != ' ')
		{
			arr_words[i_1][j_1] = array[i_1][j_1];
			j_1++;

		}
		arr_words[i_1][j_1] = '\0';
		j_1 = 0;
	}
}

void Array_Numbers_String(char** array, int lines_count, char** arr_numbers)
{
	int j_2 = 0;
	for (int q = 0; q < lines_count; q++)
	{
		arr_numbers[q] = (char*)malloc(sizeof(char) * 40);
	}
	int f;
	int i_3 = 0;
	char num;
	for (int i_2 = 0; i_2 < lines_count; i_2++)
	{
		f = 0;
		while (array[i_2][f] != '\0')
		{
			f++;
		}
		while (array[i_2][f - 1 - i_3] != ' ')
		{
			i_3++;
		}
		while (array[i_2][f - j_2 - 1] != ' ')
		{
			arr_numbers[i_2][j_2] = array[i_2][f + j_2 - i_3];
			j_2++;

		}
		arr_numbers[i_2][j_2] = '\0';
		j_2 = 0;
		i_3 = 0;
	}
}

void Array_Numbers_Int(int* arr_numbers_int, char** arr_numbers, int lines_count)
{
	for (int q = 0; q < lines_count; q++)
	{
		arr_numbers_int[q] = (int*)malloc(sizeof(int) * 40);
	}
	for (int i_4 = 0; i_4 < lines_count; i_4++)
	{

		arr_numbers_int[i_4] = atoi(arr_numbers[i_4]);
	}
}

void Sort(int* arr_numbers_int, char** arr_numbers, int lines_count, char** arr_words)
{
	char str[40];
	int cont = 0;
	for (int i_5 = 1; i_5 < lines_count; i_5++)
	{
		for (int j_5 = 0; j_5 < lines_count - i_5; j_5++)
		{
			if (strcmp(arr_words[j_5], arr_words[j_5 + 1]) > 0)
			{
				strcpy(str, arr_words[j_5]);
				cont = arr_numbers_int[j_5];

				strcpy(arr_words[j_5], arr_words[j_5 + 1]);
				arr_numbers_int[j_5] = arr_numbers_int[j_5 + 1];

				strcpy(arr_words[j_5 + 1], str);
				arr_numbers_int[j_5 + 1] = cont;

			}
		}

	}

	int s_1 = 0;
	int k_1 = 0;
	int u_1 = 0;
	int p_1 = 0;
	int p_2 = 0;

	for (u_1 = 0; u_1 < lines_count; u_1++)
	{
		if (strcmp(arr_words[u_1], "") != 0)
		{
			if (strcmp(arr_words[u_1], arr_words[u_1 + 1]) == 0)
			{
				k_1 = u_1;
				while (strcmp(arr_words[k_1], arr_words[k_1 + 1]) == 0)
				{
					s_1++;
					k_1++;
				}
				p_1 = 0;
				while (p_1 < s_1)
				{
					for (int g_1 = u_1; g_1 < lines_count - 1; g_1++)
					{
						for (int r_1 = 0; r_1 < 20; r_1++)
						{
							arr_words[g_1][r_1] = arr_words[g_1 + 1][r_1];
						}
					}

					arr_numbers_int[u_1] += arr_numbers_int[u_1 + 1];
					for (int g_1_1 = u_1 + 1; g_1_1 < lines_count - 1; g_1_1++)
					{


						arr_numbers_int[g_1_1] = arr_numbers_int[g_1_1 + 1];

					}

					p_1++;
					memset(arr_words[lines_count - p_1], 0, strlen(arr_words[lines_count - p_1]));
					arr_numbers_int[lines_count - p_1] = 0;

				}
			}
		}
		s_1 = 0;
		k_1 = 0;
		p_1 = 0;
	}

	
	for (int i_6 = 0; i_6 < lines_count; i_6++)
	{

		itoa(arr_numbers_int[i_6], arr_numbers[i_6], 10);

	}
	for (int i_6 = 0; i_6 < lines_count; i_6++)
	{
		if (arr_numbers_int[i_6] == 0)
			memset(arr_numbers[i_6], 0, strlen(arr_numbers[i_6]));
	}
}

void Create_And_Print_List(char** arr_words, char** arr_numbers, int lines_count)
{
	t_List* List = create_node(arr_words[lines_count], arr_numbers[lines_count]);

	for (int h = lines_count - 1; h >= 0; h--)
	{
		push_front(&List, arr_words[h], arr_numbers[h]);
	}

	int u = 0;
	while (u < lines_count)
	{
		printf("%s   %s\n", List->word, List->number);
		List = List->next;
		u++;
	}
}

void Check_Word(char word[], char** arr_words, int lines_count, char** arr_numbers)
{
	int k = 0;

	for (int i = 0; i < lines_count; i++)
	{
		if (strcmp(arr_words[i], word) == 0)
		{
			k++;
			printf("\nSuch a word exists. His number %s.\n\n", arr_numbers[i]);
			break;
		}
	}

	if (k == 0)
		printf("\nSuch a word does not exist.\n");

}

void Check_Number(char number[], char** arr_words, int lines_count, char** arr_numbers)
{
	int k = 0;

	for (int i = 0; i < lines_count; i++)
	{
		if (strcmp(arr_numbers[i], number) == 0)
		{
			k++;
			if (k <= 1)
				printf("\nSuch a number exists. His words: %s\n", arr_words[i]);
			if (k > 1)
				printf("                                 %s\n", arr_words[i]);
		}
	}

	if (k == 0)
		printf("\nSuch a number does not exist.\n");

}
