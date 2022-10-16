#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./fs.c"

int getNumberLength(int number) {
  if (number == 0)
    return 1;
  return log10(abs(number)) + 1;
}

int charToInt(char ch) {
  return ch - '0';
}

int stringToInt(char* string) {
  return atoi(string);
}

char* intToString(int number) {
  char* string = malloc(sizeof(char) * getNumberLength(number));
  sprintf(string, "%d", number);
  return string;
}

// Конкатенация двух строк
char* concat(char* firstString, char* secondString) {
  char* string = malloc(sizeof(char) * 256);
  strcpy(string, firstString);
  strcat(string, secondString);
  return string;
}

// Рекурсивный перебор всех возможных комбинаций.
// buffer нужен для оптимизации высчитывания total, так как
// считать expression каждый раз было бы очень затратно по времени
void backtrack(
  char* number,
  int target,
  int index,
  double total,
  char* expression,
  int currentNumber,
  double buffer
) {
  // Если дошли до конца и currentNumber не равен 0 или сумма не рована нужной,
  // то прекращаем перебор в этой ветке
  if (index == getNumberLength(stringToInt(number)) && (currentNumber || total != target))
    return;
  // Если сумма равна нужной, выводим и прекращаем перебор
  if (index == getNumberLength(stringToInt(number)) && total == target)
  {
    printf("%s\n", expression);
    return;
  }
  // Следующее число при слиянии с соседним
  const int nextNumber = currentNumber * 10 + charToInt(number[index]);
  if (nextNumber)
    backtrack(number, target, index + 1, total, expression, nextNumber, buffer);
  // Совмещение двух соседних цифр в одно чилсо
  backtrack(
    number,
    target,
    index + 1,
    total + nextNumber,
    strlen(expression)
      ? concat(concat(expression, "+"), intToString(nextNumber))
      : concat(expression, intToString(nextNumber)),
    0,
    nextNumber
  );
  if (!strlen(expression))
    return;
  // Минус
  backtrack(
    number,
    target,
    index + 1,
    total - nextNumber,
    concat(concat(expression, "-"), intToString(nextNumber)),
    0,
    -nextNumber
  );
  // Умножение
  backtrack(
    number,
    target,
    index + 1,
    total - buffer + (buffer * nextNumber),
    concat(concat(expression, "*"), intToString(nextNumber)),
    0,
    buffer * nextNumber
  );
  // Деление
  backtrack(
    number,
    target,
    index + 1,
    total - buffer + (buffer / (double)nextNumber),
    concat(concat(expression, "/"), intToString(nextNumber)),
    0,
    buffer / (double)nextNumber
  );
}

int main() {
  // Читаем числа из файла
  int* numbers = readNumbers("input.txt");
  int number = numbers[0];
  int target = numbers[1];
  // Создаем строку для конечного выражения
  char* expression = malloc(sizeof(char) * 256);

  backtrack(intToString(number), target, 0, 0, expression, 0, 0);

  return 0;
}
