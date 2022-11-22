#include"main.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#pragma warning(disable:4996)

int SymbolCheck(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1;
	return 0;
}

int CompareStructures(Date* date_current, Date* date_next) {
	int pointer = 0;
	if (date_next->year > date_current->year) pointer = 1; // next > current
	if (date_next->year < date_current->year) pointer = -1; // next < current
	if (date_next->year == date_current->year) {
		if (date_next->month > date_current->month) pointer = 1; // next > current
		if (date_next->month < date_current->month) pointer = -1; // next < current
		if (date_next->month == date_current->month) {
			if (date_next->day > date_current->day) pointer = 1; // next > current
			if (date_next->day < date_current->day) pointer = -1; // next < current
			if (date_next->day == date_current->day) pointer = 0; // next = current
		}
	}
	return pointer;
}

void PrintListField(List* list) {
	char* s = list->profile->surname;
	int i = 0;
	while (SymbolCheck(s[i]) == 1) {
		printf("%c", s[i]);
		i++;
	}
	printf(" ");
	s = list->profile->name;
	i = 0;
	while (SymbolCheck(s[i]) == 1) {
		printf("%c", s[i]);
		i++;
	}
	printf(" ");
	s = list->profile->patronymic;
	i = 0;
	while (SymbolCheck(s[i]) == 1) {
		printf("%c", s[i]);
		i++;
	}
	printf(" ");
	printf("%i %i %i", list->date->day, list->date->month, list->date->year);
	printf("\n");
}

void PrintListComplited(List* list) {
	if (list == NULL) {
		puts("empty list");
	}
	else {
		while (list != NULL) {
			PrintListField(list);
			(List*)list = (List*)list->next;
		}
	}
}

void InsertListField(Profile* profile, Date* date, List** inp) {
	List* new, * prev, * cur;

	new = (List*)malloc(sizeof(List));
	if (new == NULL) {
		printf("memory allocation error\n");
		exit(1);
	}

	new->profile = profile;
	new->date = date;
	new->next = NULL;
	prev = NULL;
	cur = *inp;

	while (cur != NULL && (CompareStructures(date, cur->date) == -1))
	{
		prev = cur;
		cur = cur->next;
	}

	if (prev == NULL) {
		new->next = *inp;
		*inp = new;
	}
	else {
		prev->next = new;
		new->next = cur;
	}
}

int StrCounter(char const* filename) {
	FILE* file;
	if ((file = fopen(filename, "r")) == NULL) {
		printf("cannot open file\n");
		exit(1);
	}

	int counter = 0;
	char sym;
	while (!feof(file)) {
		sym = fgetc(file);
		if (sym == '\n') counter++;
	}
	return counter;
}

List* AlterationListFromFile(char const* filename, int board) {
	List* list = NULL; 
	FILE* file;

	int length = 0; 
	char* str = NULL;
	char temp;

	if ((file = fopen(filename, "r")) == NULL) {
		printf("cannot open file\n");
		exit(1);
	}

	str = (char*)malloc(sizeof(char));
	if (str == NULL) {
		printf("memory allocation error\n");
		exit(1);
	}

	for (int k = 1; k <= board; k++) {
		Profile* profile = (Profile*)malloc(sizeof(Profile));
		if (profile == NULL) {
			printf("memory allocation error\n");
			exit(1);
		}

		Date* date = (Date*)malloc(sizeof(Date));
		if (date == NULL) {
			printf("memory allocation error\n");
			exit(1);
		}

		int i = 0;
		while ((i <= 2) && (fscanf(file, "%c", &temp) == 1)) {
			if (SymbolCheck(temp) == 1) {
				length++;

				char* str_temp = (char*)realloc(str, length * sizeof(char));
				if (str_temp == NULL) {
					printf("memory allocation error\n");
					exit(1);
				}

				str = str_temp;
				str[length - 1] = temp;
			}
			else {
				if (SymbolCheck(str[0]) == 1) { //если встречает конец стоки '\n', не считывает его как фамилию, а возвращается в цикл и считывает первую букву со следующей строчки
					length++;

					char* str_temp = (char*)realloc(str, length * sizeof(char));
					if (str_temp == NULL) {
						printf("memory allocation error\n");
						exit(1);
					}

					str = str_temp;
					str[length - 1] = '\0';

					if (i == 0) profile->surname = str;
					if (i == 1) profile->name = str;
					if (i == 2) profile->patronymic = str;

					length = 0;

					str = (char*)malloc(sizeof(char));
					if (str == NULL) {
						printf("memory allocation error\n");
						exit(1);
					}

					i++;
				}
			}
		}
		if (!fscanf(file, "%i %i %i", &date->day, &date->month, &date->year)) exit(1);
		InsertListField(profile, date, &list);
	}
	fclose(file);
	return list;
}

void CheckDate(List* list, Date* input_date) {
	int count = 0;
	while (list != NULL) {
		if ((list->date->day == input_date->day) && (list->date->month == input_date->month) && (list->date->year == input_date->year)) {
			count++;
			if (count == 1) printf("\ncoincidences\n");
			PrintListField(list);
		}
		list = list->next;
	}
	printf("\nnumber of coincidences: %i\n", count);
}

Date* InputFromScreen() {
	Date* input_date = (Date*)malloc(sizeof(Date));
	if (input_date == NULL) {
		printf("memory allocation error\n");
		exit(1);
	}

	printf("put the day: ");
	if(!scanf("%i", &input_date->day)) exit(1);
	printf("put the month: ");
	if (!scanf("%i", &input_date->month)) exit(1);
	printf("put the year: ");
	if (!scanf("%i", &input_date->year)) exit(1);

	return input_date;
}
