#include <math.h>
#include <stdio.h>
#define N 4
#pragma warning (disable:4996)


struct String
{
	char* word;
	int length;
	struct String* next;
};
typedef struct String String;

int IsLetter(char w)
{
	if (((w >= 'A') && (w <= 'Z')) || ((w >= 'a') && (w <= 'z'))) return 1;
	else return 0;
}

char* ReadWord(FILE* f, int* length)
{
	int len = 0;
	char* word = (char*)malloc(sizeof(char));
	char letter;


	if (f == NULL)
	{
		printf("Error1");
		return NULL;
	}


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

		return word;
	}
	else return NULL;
}

int Compare(char* new, char* cur, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (new[i] > cur[i]) return 1; //new should be placed after cur
		if (new[i] < cur[i]) return 2; //new should be placed before cur
	}
	return 0; //entered words are indentical
}

int SpecialInsert(String** ptr, String* prev, String* new, int length)//1 = success
{
	String* cur = prev->next;
	if (cur->length < new->length)
	{
		if (cur->next == NULL)
		{
			cur->next = new;
			return 1;
		}
		return 2; //continue
	}
	if (cur->length > new->length)
	{
		new->next = cur;
		prev->next = new;
		return 1;
	}
	if (cur->length == new->length)
	{
		if (Compare(new->word, cur->word, length) == 1)
		{
			if (cur->next == NULL)
			{
				cur->next = new;
				return 1;
			}
			if (cur->next->length > new->length)
			{
				new->next = cur->next;
				cur->next = new;
				return 1;
			}
			if (cur->next->length == new->length)
			{
				if (Compare(new, cur->next, length) == 1) return 2;
				else
				{
					new->next = cur->next;
					cur->next = new;
					return 1;
				}
			}
			return 2;
		}
		else
		{
			new->next = cur;
			prev->next = new;
			return 1;
		}
	}
}

void Insert(String** ptr, char* word, int length)
{
	String* prev;
	String* cur;
	String* new;
	new = (String*)malloc(sizeof(String));
	if (new == NULL) return;
	prev = *ptr;
	new->word = word;
	new->length = length;
	new->next = NULL;

	if (prev->next == NULL)
	{
		prev->next = new;
		return;
	}

	do
	{
		if (SpecialInsert(ptr, prev, new, length) == 1) return;
		prev = prev->next;
	} while (prev != NULL);
	//prev = new;
	/*while (prev->length < new->length)
		{

			prev = cur;
			cur= cur->next;
		}

	//cur = prev->next;
	*/
	/*if ((new->length < prev->length) || ((new->length == prev->length) && (Compare(new->word, prev->word, length) == 2)))//necessary to put new word on first place
	{
		*ptr = new;
		new->next = prev;
		return;
	}
	if (cur == NULL)
	{
		if (Compare(new->word, prev->word, length) == 1)
		{
			prev->next = new;
			return;
		}
		else
		{
			*ptr = new;
			new->next = prev;
			return;
		}
	}
	while ((cur->length < new->length) && (cur->next != NULL))
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur->length > new->length)
	{
		prev->next = new;
		new->next = cur;
	}
	if (cur->length < new->length)
	{
		cur->next = new;
		return;
	}
	if (cur->length == new->length)
	{
		if (Compare(new->word, cur->word, length) == 1)
		{
			new->next = cur->next;
			cur->next = new;
			return;
		}
		if ((Compare(new->word, cur->word, length) == 2)||(Compare(new->word, cur->word, length) == 0))
		{
			new->next = prev->next;
			prev->next = new;
			return;
		}
	}*/
}

void StringPrint(String* ptr, int number)
{
	int flag = 0;
	String* cur = ptr->next;
	while (cur != NULL)
	{
		for (int i = 0; i < cur->length; i++) 
		{ 
			if (cur->length == number) printf("%c", cur->word[i]); 
		}
		if (cur->length == number)
		{
			printf(" ");
			flag = 1;
		}
		cur = cur->next;
	}
	if (flag == 0) printf("No words of length %d were found", number);
	printf("\n");
}
void StringPrint_N(String* ptr)
{
	int flag = 0;
	String* cur = ptr->next;
	while (cur != NULL)
	{
		for (int i = 0; i < cur->length; i++)
		{
			if (cur->length > N) printf("%c", cur->word[i]);
		}
		if (cur->length > N) 
		{
			printf(" ");
			flag = 1;
		}
		cur = cur->next;
	}
	if (flag == 0) printf("No words of length greater than %d were found", N);
	printf("\n");
}


int main(void)
{
	FILE* f;
	f = fopen("file.txt", "r");
	int* length = (int*)malloc(sizeof(int));
	char* word = ReadWord(f, length);
	String* ptr = NULL;
	String* first = (String*)malloc(sizeof(String));
	first->word = "a";
	first->length = 1;
	first->next = NULL;
	ptr = first;
	while (word != NULL)
	{
		Insert(&ptr, word, *length);
		word = ReadWord(f, length);
	}
	int count;
	StringPrint_N(ptr);
	scanf_s("%d", &count);
	StringPrint(ptr, count);

	return 0;
}
