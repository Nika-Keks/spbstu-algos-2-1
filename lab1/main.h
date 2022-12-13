#pragma once
#include "list.h"

// Чтение файла и сортировка
Node *Read_file(char const *fileName);

// Проверка, является ли строка числом
int Is_number(char *string);

// Ищем элемент в списке по слову
Node *Search_by_word(Node *head, char *word);

// Строка в число
int String_to_number(char *string);
