#include <stdlib.h>
#include <math.h>

int getNumberLength(int number) {
  if (number == 0)
    return 1;
  return log10(abs(number)) + 1;
}
