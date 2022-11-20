#pragma once

typedef struct Polinom {
	int* numbers;
	int length;
} Polinom;

void Polynom_destroy(Polinom* polynom);

Polinom* Polynom_parse(char* string);

Polinom* Polynom_read(char* File_name);

void Polynom_write(char* File_name, Polinom* polynom);

Polinom* Polynom_sum(Polinom* p1, Polinom* p2);

Polinom *Polynom_sub(Polinom *p1, Polinom *p2);

Polinom* Polynom_mul(Polinom* p1, Polinom* p2);
