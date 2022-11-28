#include "Header.h"
#include <math.h>
#include <stdio.h>
#pragma warning (disable:4996)

int IsLetter(char w)//checking whether a character is a letter
{
	if (((w >= 'A') && (w <= 'Z')) || ((w >= 'a') && (w <= 'z'))) return 1;
	else return 0;
}

void ReadWord(char const* filename, int* length, String** ptr)//writing a word and counting the number of characters
{
	FILE* f;
	f = fopen(filename, "r+");
	int len = 0;
	char* word = (char*)malloc(sizeof(char));
	char letter;

	if (f == NULL)
	{
		printf("Error1");
		return NULL;
	}
	int key = 1;
	while (key == 1)
	{
		int len = 0;
		char* word = (char*)malloc(sizeof(char));
		if ((fscanf_s(f, "%c", &letter) == 1) && (IsLetter(letter) == 1))
		{
			do
			{
				len++;
				char* nword = (char*)realloc(word, sizeof(char) * len);
				if (nword == NULL)
				{
					printf("Not enought memory");
					return;
				}
				word = nword;
				word[len - 1] = letter;
			} while ((fscanf_s(f, "%c", &letter) == 1) && (IsLetter(letter) == 1));
			*length = len;

			Insert(ptr, word, *length);
		}
		if (feof(f) != 0) key = 2;//вся проблема в том чтобы выйти из цикла в конце файла
	}
	
}

int Compare(char* new, char* cur, int length)//comparing the lengths of two words
{
	for (int i = 0; i < length; i++)
	{
		if (new[i] > cur[i]) return 1; //new should be placed after cur
		if (new[i] < cur[i]) return 2; //new should be placed before cur
	}
	return 0; //entered words are indentical
}

int Desicion(String* new, String* prev, String* cur)// returns 1 if the new word was succesfully inserted, 2 - if needs to go further
{
	if (cur == NULL)
	{
		prev->next = new;
		return 1;
	}
	//Comparing the lengths of words
	if (new->length < cur->length)
	{
		new->next = cur;
		prev->next = new;
		return 1;
	}
	if (new->length > cur->length)
	{
		return 2;
	}
	if (new->length == cur->length)
	{
		if (Compare(new->word, cur->word, new->length) != 1)
		{
			new->next = cur;
			prev->next = new;
			return 1;
		}
		else return 2;
	}

}

void Insert(String** ptr, char* word, int length)//inserting a word into an array
{

	String* prev;
	String* cur;
	String* new;
	new = (String*)malloc(sizeof(String));
	if (new == NULL) return;
	new->word = word;
	new->length = length;
	new->next = NULL;

	if (*ptr == NULL)//the case of an empty array
	{
		(*ptr) = (String*)malloc(sizeof(String));
		(*ptr)->next = NULL;
		(*ptr)->word = new->word;
		(*ptr)->length = new->length;
		
		return;
	}
	prev = *ptr;
	cur = prev->next;

	if (cur == NULL)//the case of an array with one word
	{
		if (new->length < prev->length)
		{
			new->next = prev;
			*ptr = new;
			return;
		}
		if (new->length > prev->length)
		{
			prev->next = new;
			return;
		}
		else
		{
			if (Compare(new->word, prev->word, length) != 1)
			{
				new->next = prev;
				*ptr = new;
				return;
			}
			else
			{
				prev->next = new;
				return;
			}
		}
	}
	if ((*ptr)->length > new->length || (((*ptr)->length == new->length) && Compare(new, *ptr, length) != 1)) //if necessary to add in the begining
	{
		new->next = prev;
		*ptr = new;
		return;
	}

	while (Desicion(new, prev, cur) == 2)//checking every single word in array for correct insertion
	{
		prev = cur;
		cur = cur->next;
	}

}
void StringPrint(String* ptr, int standard, int key) //line output, key = 1 is for first task, 2 - is for second
{
	String* cur = ptr;
	if (key == 1)
	{
		while (cur != NULL)
		{
			if (cur->length > N)
			{
				for (int i = 0; i < cur->length; i++) printf("%c", cur->word[i]);
				printf(" ");
			}
			cur = cur->next;
		}
		printf("\n");
		return;
	}
	if (key == 2)
	{
		while (cur != NULL)
		{
			if (cur->length == standard)
			{
				for (int i = 0; i < cur->length; i++) printf("%c", cur->word[i]);
				printf(" ");
			}
			cur = cur->next;
		}
		printf("\n");
		return;
	}
	else printf("Incorrect key\n");
	return;
}