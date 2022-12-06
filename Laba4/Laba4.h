#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#pragma warning(disable:4996)

void WriteText(char const* filename, int* arr, int len);
int* ReadText(char const* filename, int* B, int* N);
void solve(int i, int S, int* a, int* answer, int len, int* key);