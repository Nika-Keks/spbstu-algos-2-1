#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Object representing the polynomial object
typedef struct Polynomial {
  // List of degrees
	int* powers;
  // Degree of the polynomial, which is the highest of the degrees of the
  // polynomial's monomials (individual terms) with non-zero coefficients
  // deg(-x^3 + 6x^2 + 8) = 3
  int degree;
} Polynomial;

// Clean up the memory
void polynomialDestroy(Polynomial* polynomial) {
  free(polynomial->powers);
  free(polynomial);
}

// Parse polynomial from a string
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
      string += 1;
    }
  }

  return polynomial;
}

// Read polynomial from a file
Polynomial* polynomialRead(char* fileName) {
  FILE *fileStream = fopen(fileName, "r");

  if (!fileStream) {
    printf("Could not open the file %s", fileName);
    exit(0);
  }

  // Read the whole file as a plain stirng
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

  // Parse polynomial from the file's content
  Polynomial* polynomial = polynomialParse(content);

  fclose(fileStream);

  return polynomial;
}

// Save a polynomial into a file
void polynomialWrite(char* fileName, Polynomial* polynomial) {
  FILE* fileStream = fopen(fileName, "w");

  for (int index = 0; index < polynomial->degree + 1; index += 1) {
    fprintf(fileStream, "%d ", polynomial->powers[index]);
  }

  fclose(fileStream);
}

// Sum two polynomials
Polynomial* polynomialSum(Polynomial* p1, Polynomial* p2) {
  Polynomial* polynomial = malloc(sizeof(Polynomial));
  polynomial->degree = max(p1->degree, p2->degree);
  polynomial->powers = malloc(sizeof(int) * (polynomial->degree + 1));

  // Add first polynomial
  for (int index = 0; index < p1->degree + 1; index += 1) {
    polynomial->powers[polynomial->degree - index] = p1->powers[p1->degree - index];
  }

  // Add second polynomial
  for (int index = 0; index < p2->degree + 1; index += 1) {
    polynomial->powers[polynomial->degree - index] += p2->powers[p2->degree - index];
  }

  return polynomial;
}

// Multiply polynomial by an integer
Polynomial* polynomialMulInt(Polynomial* polynomial, int k) {
  Polynomial* copy = malloc(sizeof(Polynomial));
  copy->degree = polynomial->degree;
  copy->powers = malloc(sizeof(int) * copy->degree);

  // Multiply every coefficient by the integer
  for (int index = 0; index < polynomial->degree + 1; index += 1) {
    copy->powers[index] = polynomial->powers[index] * k;
  }

  return copy;
}

// Subtract a polynomial from another one
Polynomial* polynomialSub(Polynomial* p1, Polynomial* p2) {
  // Same as adding negative polynomial
  return polynomialSum(p1, polynomialMulInt(p2, -1));
}

// Multiply two polynomials
Polynomial* polynomialMul(Polynomial* p1, Polynomial* p2) {
  Polynomial* polynomial = malloc(sizeof(Polynomial));
  polynomial->degree = p1->degree + p2->degree;
  polynomial->powers = malloc(sizeof(int) * polynomial->degree);

  // Multiply corresponding coefficients
  for (int i = 0; i < p1->degree + 1; i += 1) {
    for (int j = 0; j < p2->degree + 1; j += 1) {
      polynomial->powers[polynomial->degree - i - j] += p1->powers[p1->degree - i] * p2->powers[p2->degree - j];
    }
  }

  return polynomial;
}
