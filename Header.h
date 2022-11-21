#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#pragma warning(disable:4996)

typedef struct {
	char* line;
	int len;
	struct lines* next;
} lines;

int isEmpty(lines* sPtr);

void Print(char* a, int n);

void PrintList(lines* current);

void PrintList_n(lines* current, int n);


void PrintList_10(lines* start);

void Insert(lines* new, lines** Ptr);

lines* StructFill(char* filename);
