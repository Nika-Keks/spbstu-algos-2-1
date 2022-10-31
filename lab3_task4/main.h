#pragma once

typedef struct Polynomial {
	int* powers;
	int degree;
} Polynomial;

void polynomialDestroy(Polynomial* polynomial);

Polynomial* polynomialParse(char* string);

Polynomial* polynomialRead(char* fileName);

void polynomialWrite(char* fileName, Polynomial* polynomial);

Polynomial* polynomialSum(Polynomial* p1, Polynomial* p2);

Polynomial* polynomialMulInt(Polynomial* polynomial, int k);

Polynomial* polynomialSub(Polynomial* p1, Polynomial* p2);

Polynomial* polynomialMul(Polynomial* p1, Polynomial* p2);
