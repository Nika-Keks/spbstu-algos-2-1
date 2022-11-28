#pragma once
#define N 4
struct String
{
	char* word;
	int length;
	struct String* next;
};
typedef struct String String;

int IsLetter(char w);
void ReadWord(char const* filename, int* length, String** ptr);
int Compare(char* new, char* cur, int length);
int Desicion(String* new, String* prev, String* cur);
void Insert(String** ptr, char* word, int length);
void StringPrint(String* ptr, int standard, int key);	