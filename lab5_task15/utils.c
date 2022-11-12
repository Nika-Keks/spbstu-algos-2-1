#include <math.h>

int max(int a, int b) {
  return a > b ? a : b;
}

int getNumberLength(int number) {
  if (number == 0)
    return 1;
  return log10(abs(number)) + 1;
}

char* repeat(char ch, int length) {
  char* string = malloc(sizeof(char) * (length + 1));

  for (int index = 0; index < length; index += 1) {
    string[index] = ch;
  }

  string[length] = '\0';

  return string;
}
