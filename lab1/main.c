#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Чтение файла и сортировка
Node* Read_file(char const *fileName) {

  FILE* fileStream = fopen(fileName, "r");

  if (!fileStream) {
    printf("Не удалось открыть файл %s", fileName);
    exit(0);
  }

  Node* list = List_create();
  // a и b - два элемента, между которыми вставят новый
  // Один из них может быть NULL
  Node* a = NULL;
  Node* b = list;
  // Максимальная длина слвоа - 128 символов
  const int wordSize = sizeof(char) * 128;
  char* buffer = malloc(wordSize);
  char* word = malloc(wordSize);
  int number;

  // читаем новую строчку
  while (fscanf(fileStream, "%s %d\n", buffer, &number) != EOF) {
    // Копируем слово, чтобы оно не заменилось по ссылке при следующем чтении
    memcpy(word, buffer, wordSize);

    // Если первое слово, то записыаем инвормацию в первые и единственный элемент
    if (!b->word) {
      b->word = word;
      b->number = number;
      word = malloc(wordSize);
      continue;
    }

    // Ищем два элемента a и b, между которыми вставим новое слово
    while (b && strcmp(b->word, word) < 0) {
      a = b;
      b = b->next;
    }

    // Если уже существует такое слово, то прибавляем число
    if (b && strcmp(b->word, word) == 0) {
      b->number += number;
    } else {
      // Создаем новые элемент списка
      Node* node = malloc(sizeof(Node));

      node->word = word;
      node->number = number;

      node->next = b;
      if (a) {
        a->next = node;
      }

      // Если вставили элемент в самое начало, то заменяем head
      if (!a) {
        list = node;
      }
    }

    // Обнуляем
    a = NULL;
    b = list;
    word = malloc(wordSize);
  }

  fclose(fileStream);

  return list;
}

// Проверка, является ли строка числом
int Is_number(char* string) {

  for (int index = 0; index < strlen(string); index += 1) {
    if (string[index] < '0' || string[index] > '9') {
      return 0;
    }
  }

  return 1;
}

// Ищем элемент в списке по слову
Node* Search_by_word(Node* head, char* word) {

  while (head && strcmp(head->word, word) != 0) {
    head = head->next;
  }
  return head;
}

// Строка в число
int String_to_number(char* string) {

  int number;
  sscanf(string, "%d", &number);
  return number;
}
