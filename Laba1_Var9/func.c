#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#pragma warning(disable:4996)

#include "Header.h"

int isEmpty(lines* sPtr) {
	return sPtr == NULL;
}

void Print(char* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%c", a[i]);
	}
	puts("");
}

void PrintList(lines* current) {
	if (isEmpty(current)) {
		puts("List is empty.");
	}
	else {
		puts("The list is:");
		while (current != NULL) {
			Print(current->line, current->len);
			current = current->next;
		}
	}
}

void PrintList_n(lines* current, int n) {
	if (isEmpty(current)) {
		puts("List is empty");
	}
	else {
		int flag = 1;
		while (current != NULL) {
			if (current->len == n) {
				Print(current->line, current->len);
				flag = 0;
			}
			current = current->next;
		}
		if (flag) puts("No such lines");
	}
}


void PrintList_10(lines* start) {
	if (isEmpty(start)) {
		puts("List is empty");
	}
	else {
		puts("Top 10:");
		lines* buf = NULL;
		for (int i = 0; i < 10 && buf != start; i++) {
			lines* current = start;
			while (current->next != buf) {
				current = current->next;
			}
			buf = current;
			Print(current->line, current->len);
		}
	}
}


void Insert(lines* new, lines** Ptr) {
	lines* prev;
	lines* current;

	prev = NULL;
	current = *Ptr;
	while (current != NULL && new->len >= current->len)
	{
		prev = current;
		current = current->next;
	}

	if (prev == NULL) {
		new->next = *Ptr;
		*Ptr = new;
	}
	else {
		prev->next = new;
		new->next = current;
	}
}


lines* StructFill(char* filename) {
	lines* main = NULL;
	int len = 0;
	char t;
	FILE* f = fopen(filename, "r");
	if (f == NULL) return NULL;
	char* a = (char*)malloc(sizeof(char));
	if (a == NULL) return NULL;

	while (fscanf(f, "%c", &t) == 1) {
		if (t != '\n') {
			len++;
			char* p = (char*)realloc(a, len * sizeof(char));
			if (p == NULL) return NULL;
			a = p;
			a[len - 1] = t;
		}
		else {
			lines* ptr = (lines*)malloc(sizeof(lines));
			ptr->line = a;
			ptr->len = len;
			ptr->next = NULL;
			Insert(ptr, &main);
			len = 0;
			a = (char*)malloc(sizeof(char));
			if (a == NULL) return NULL;
		}
	}
	lines* ptr = (lines*)malloc(sizeof(lines));
	ptr->line = a;
	ptr->len = len;
	ptr->next = NULL;
	Insert(ptr, &main);
	return main;
}