#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fs.h"

int getNumberLength(int number) {
  if (number == 0)
    return 1;
  return log10(abs(number)) + 1;
}

int charToInt(char ch) {
  return ch - '0';
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
// number - изначалаьное число в виде строки
// target - число, которое нужно получить
// index - индекс цифры в чсиле. Все рекурсивные вызовы backtrack
// прибавляют 1 к index
// total - результат полученного выражения
// expression - само выражение в виде строки (например, "1+22/2")
// currentNumber - нужен для "слияния" цифр (когда между цифрами
// не стоит никаких знаков, и оно воспринмиается как единое число).
// Все рекурсивные вызовы backtrack, кроме одного, ставят currentNumber равным 0
// buffer - нужен для оптимизации высчитывания total, так как
// считать expression каждый раз было бы затратно
void backtrack(
  char* number,
  int target,
  int index,
  double total,
  char* expression,
  int currentNumber,
  double buffer
) {
  // Если дошли до конца и currentNumber не равен 0 или сумма не равна нужной,
  // то прекращаем перебор в этой ветке
  if (index == strlen(number) && (currentNumber || total != target))
    return;
  // Если сумма равна нужной, выводим и прекращаем перебор
  if (index == strlen(number) && total == target)
  {
    printf("%s\n", expression);
    return;
  }
  // Следующее число при слиянии с соседним
  const int nextNumber = currentNumber * 10 + charToInt(number[index]);
  char* nextNumberStr = intToString(nextNumber);
  // Совмещение двух соседних цифр в одно чилсо
  if (nextNumber)
      backtrack(number, target, index + 1, total, expression, nextNumber, buffer);
  // Сложение. Мы начинаем с этой операции, потому что мы можем расставлять
  // знаки только между цифрами, и, потому, не можем в самом начале
  // использовать другие операции кроме сложения
  backtrack(
    number,
    target,
    index + 1,
    total + nextNumber,
    strlen(expression)
      ? concat(concat(expression, "+"), nextNumberStr)
      : concat(expression, nextNumberStr),
    0,
    nextNumber
  );
  // Если это не самый первый вызов функции backtrack и мы уже имеем
  // хотя бы одну цифру в expression, то можем использовать другие операции
  if (!strlen(expression))
    return;
  // Минус
  backtrack(
    number,
    target,
    index + 1,
    total - nextNumber,
    concat(concat(expression, "-"), nextNumberStr),
    0,
    -nextNumber
  );
  // Умножение
  backtrack(
    number,
    target,
    index + 1,
    total - buffer + (buffer * nextNumber),
    concat(concat(expression, "*"), nextNumberStr),
    0,
    buffer * nextNumber
  );
  // Деление
  backtrack(
    number,
    target,
    index + 1,
    total - buffer + (buffer / (double)nextNumber),
    concat(concat(expression, "/"), nextNumberStr),
    0,
    buffer / (double)nextNumber
  );
}

int main() {
  // Читаем числа из файла
  int* numbers = readNumbers("input.txt");
  int number = numbers[0];
  int target = numbers[1];

  backtrack(intToString(number), target, 0, 0, "", 0, 0);

  return 0;
}
