#include <stdio.h>
#include <stdlib.h>
#include "main.c"

int main() {

  Node* data = Read_file("data.txt");

  for (Node* head = data; head != NULL; head = head->next) {
    printf("%s %d\n", head->word, head->number);
  }

  char input[200];

  do {

    printf("Enter to search: ");
    scanf("%s", input);

    // Если пользователь ввел число, ищем элементы по числу
    // иначе по слову
    if (Is_number(input)) {
      int number = String_to_number(input);
      int found = 0;
      Node* head = data;
      while (head) {
        if (head->number == number) {
          found = 1;
          printf("%s %d \n", head->word, head->number);
        }
        head = head->next;
      }
      if (!found) {
        printf("Not found \n");
      }
    } else {
      Node *node = Search_by_word(data, input);
      if (node) {
        printf("%s %d \n", node->word, node->number);
      } else {
        printf("Not found \n");
      }
    }
  } while (input[0] != '\n');

  return 0;
}
