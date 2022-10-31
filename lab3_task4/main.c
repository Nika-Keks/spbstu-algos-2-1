#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct Polynomial {
	int* powers;
	int degree;
} Polynomial;

void polynomialDestroy(Polynomial* polynomial) {
  free(polynomial->powers);
  free(polynomial);
}

Polynomial* polynomialParse(char* string) {
  Polynomial* polynomial = malloc(sizeof(Polynomial));
  polynomial->powers = malloc(0);
  polynomial->degree = -1;

  while (*string) {
    if (isDigit(*string) || ((*string == '-' || *string == '+') && isDigit(*(string+1)))) {
      int power = strtol(string, &string, 10);
      polynomial->degree += 1;
      polynomial->powers = realloc(polynomial->powers, sizeof(int) * (polynomial->degree + 1));
      polynomial->powers[polynomial->degree] = power;
    } else {
      string++;
    }
  }

  return polynomial;
}

Polynomial* polynomialRead(char* fileName) {
  FILE *fileStream = fopen(fileName, "r");

  if (!fileStream) {
    printf("Could not open the file %s", fileName);
    exit(0);
  }

  int length;
  char* content;
  fseek(fileStream, 0, SEEK_END);
  length = ftell(fileStream);
  fseek(fileStream, 0, SEEK_SET);
  content = malloc(length);

  if (!content) {
    printf("Could not allocate memory");
    exit(0);
  }

  fread(content, 1, length, fileStream);

  Polynomial* polynomial = polynomialParse(content);

  fclose(fileStream);

  return polynomial;
}

void polynomialWrite(char* fileName, Polynomial* polynomial) {
  FILE* fileStream = fopen(fileName, "w");

  for (int index = 0; index < polynomial->degree + 1; index += 1) {
    fprintf(fileStream, "%d ", polynomial->powers[index]);
  }

  fclose(fileStream);
}

Polynomial* polynomialSum(Polynomial* p1, Polynomial* p2) {
  Polynomial* polynomial = malloc(sizeof(Polynomial));
  polynomial->degree = max(p1->degree, p2->degree);
  polynomial->powers = malloc(sizeof(int) * (polynomial->degree + 1));

  for (int index = 0; index < p1->degree + 1; index += 1) {
    polynomial->powers[polynomial->degree - index] = p1->powers[p1->degree - index];
  }

  for (int index = 0; index < p2->degree + 1; index += 1) {
    polynomial->powers[polynomial->degree - index] += p2->powers[p2->degree - index];
  }

  return polynomial;
}

Polynomial* polynomialMulInt(Polynomial* polynomial, int k) {
  Polynomial* copy = malloc(sizeof(Polynomial));
  copy->degree = polynomial->degree;
  copy->powers = malloc(sizeof(int) * copy->degree);

  for (int index = 0; index < polynomial->degree + 1; index += 1) {
    copy->powers[index] = polynomial->powers[index] * k;
  }

  return copy;
}

Polynomial* polynomialSub(Polynomial* p1, Polynomial* p2) {
  return polynomialSum(p1, polynomialMulInt(p2, -1));
}

Polynomial* polynomialMul(Polynomial* p1, Polynomial* p2) {
  Polynomial* polynomial = malloc(sizeof(Polynomial));
  polynomial->degree = p1->degree + p2->degree;
  polynomial->powers = malloc(sizeof(int) * polynomial->degree);

  for (int i = 0; i < p1->degree + 1; i += 1) {
    for (int j = 0; j < p2->degree + 1; j += 1) {
      if (!polynomial->powers[polynomial->degree - i - j])
        polynomial->powers[polynomial->degree - i - j] = 0;
      polynomial->powers[polynomial->degree - i - j] += p1->powers[p1->degree - i] * p2->powers[p2->degree - j];
    }
  }

  return polynomial;
}
