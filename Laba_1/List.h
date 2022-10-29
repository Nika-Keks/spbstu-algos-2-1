
#pragma once

typedef struct List {
	char* str;
	int len;
	struct List* next;
} List;

FILE* OpenFile(char* name, char* mode);//открытие файла для работы с ним
void FileClose(FILE* file);//закрытие файла
List* NewListFromFile(FILE* file, char* format);//создание узла считывая строку из файла
void PrintList(List* list);//вывод узла
void Matching(List* current, int num);//поиск узла с определенной длиной
void Input(List* head);//запрос у пользователя длины
void Printer(List* list, int n, int cnt);//вывод узла
List* CreationFromFile(FILE* file);//создание списка
int SizeOfString(char* str);//возвращает длину строки
