#pragma warning(disable : 4996)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include "Lib.h"

int main()
{
	setlocale(LC_ALL, ".1251");
	FILE* file = OpenFile("data.txt", "r");
	Rasterize(CreationFromFile(file));
	FileClose(file);
}