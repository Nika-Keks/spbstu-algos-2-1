#include <math.h>

int getNumberLength(int number) {
  if (number == 0)
    return 1;
  return log10(abs(number)) + 1;
}

char* intToString(int number) {
  char* string = malloc(sizeof(char) * getNumberLength(number));
  sprintf(string, "%d", number);
  return string;
}
