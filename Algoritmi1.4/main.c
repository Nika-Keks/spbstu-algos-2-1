#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 255 

struct Person 
{
	char surname[MAX]; 
	char name[MAX]; 
	char patr[MAX]; 
};


int personCmp(struct Person p1, struct Person p2)
{
	
	int surCmp = strcmp(p1.surname, p2.surname);
	
	if (surCmp == 0)
	{
		
		int nameCmp = strcmp(p1.name, p2.name);
		
		if (nameCmp == 0)
			return strcmp(p1.patr, p2.patr);
		return nameCmp;
	}
	return surCmp;
}

struct Node 
{
	struct Person value; 
	struct Node* next; 
};

struct Node* head = NULL; 

void add(struct Person p);
void _add(struct Node** n, struct Person p);
void print();
void _print(struct Node* n);
int startsWith(const char* a, const char* b);
void checkStarts(char* mask);
void _checkStarts(struct Node* n, char* surname, char* name, char* patr);

void add(struct Person p)
{
	_add(&head, p);
}

void _add(struct Node** n, struct Person p)
{
	if (!(*n))
	{
		*n = (struct Node*)malloc(sizeof(struct Node));
		(*n)->value = p;
		(*n)->next = NULL;
	}
	else if (personCmp((*n)->value, p) < 0)
		_add(&((*n)->next), p);
	else
	{
		struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
		n1->value = p;
		n1->next = *n;
		*n = n1;
	}
}

void print()
{
	printf("Список всех фамилий:\n");
	_print(head);
}

void _print(struct Node* n)
{
	if (!n)
		return;
	printf("%s\n", n->value.surname);
	_print(n->next);
}

int startsWith(const char* a, const char* b)
{
	return strncmp(a, b, strlen(b)) == 0;
}

void checkStarts(char* mask)
{
	char* surname = strtok(mask, " ");
	char* surname2 = malloc(strlen(surname) - 2);
	strncpy(surname2, surname + 1, strlen(surname) - 2);
	char* name = strtok(NULL, " ");
	char* name2 = malloc(strlen(name) - 2);
	strncpy(name2, name + 1, strlen(name) - 2);
	char* patr = strtok(NULL, " ");
	char* patr2 = malloc(strlen(patr) - 2);
	strncpy(patr2, patr + 1, strlen(patr) - 2);

	printf("Подходящие по маске:\n");
	_checkStarts(head, surname2, name2, patr2);
}

void _checkStarts(struct Node* n, char* surname, char* name, char* patr)
{
	// Если текущий узел пуст
	if (!n)
		return;
	if (startsWith(n->value.surname, surname) && startsWith(n->value.name, name)
		&& startsWith(n->value.patr, patr))
		printf("%s\n", n->value.surname);
	_checkStarts(n->next, surname, name, patr);
}

int main()
{
	FILE* fp = fopen("names.txt", "r");
	char buf[MAX];
	while (fgets(buf, MAX, fp))
	{
		struct Person* p = (struct Person*)malloc(sizeof(struct Person));
		char* ptr = strtok(buf, " ");
		strcpy(p->surname, ptr);
		ptr = strtok(NULL, " ");
		strcpy(p->name, ptr);
		ptr = strtok(NULL, " ");
		strcpy(p->patr, ptr);
		add(*p);
	}
	fclose(fp);

	print();

	char* mask = malloc(MAX);
	printf("\nВведите маску поиска в формате \"Ф\" \"И\" \"О\": ");
	scanf("%[^\n]", mask);
	checkStarts(mask);

	return 0;
}
