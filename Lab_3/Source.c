#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#pragma warning(disable:4996)

typedef struct LIST
{
	int value;
	int col_number;
	int str_number;
	struct LIST* next;
} list;

void MatrixRead(char const* filename, list** matrix, int* strintgs_number, int* columns_number);
list* MatrixInsert(int i, int j, int item, list** current);
void MatrixPrint(list* matrix, int a, int b);

int main()
{
	list* matrix[3] = { NULL };
	int columns_number, strings_number;
	
	MatrixRead("file.txt", matrix, &strings_number, &columns_number);//спросить у Макса как записать в массив списки внутри функции
	MatrixPrint(matrix[0], &columns_number, &strings_number);
	return 0;
}

void MatrixRead(char const* filename, list** matrix, int* a, int* b)//writing matrices from a file
{
	FILE* f;
	f = fopen(filename, "r+");
	int item, col_quantity, str_quantity;
	fscanf(f, "%d %d", &col_quantity, &str_quantity);
	*a = str_quantity;
	list* current1 = (list*)malloc(sizeof(list));
	list* saved = current1;
	list* prev = (list*)malloc(sizeof(list));
	for (int i = 0; i < col_quantity; i++)
	{
		for (int j = 0; j < str_quantity; j++)
		{
			fscanf(f, "%d", &item);
			if (item != 0)
			{
				prev = MatrixInsert(j, i, item, &current1);
			}
		}
	}
	prev->next = NULL;
	matrix[0] = saved;//first matrix

	fscanf(f, "%d %d", &col_quantity, &str_quantity);
	*b = col_quantity;
	list* current2 = (list*)malloc(sizeof(list));
	saved = current2;
	
	for (int i = 0; i < col_quantity; i++)
	{
		for (int j = 0; j < str_quantity; j++)
		{
			fscanf(f, "%d", &item);
			if (item != 0)
			{
				prev = MatrixInsert(i, j, item, &current2);
			}
		}
	}
	prev->next = NULL;
	matrix[1] = saved;//second matrix
}
list* MatrixInsert(int i, int j, int item, list** current)
{
	list* prev;
	(*current)->col_number = i;
	(*current)->str_number = j;
	(*current)->value = item;
	(*current)->next = (list*)malloc(sizeof(list));
	if ((*current)->next != NULL)
	{
		prev = *current;
		(*current) = (*current)->next;
		return prev;
	}	
	else printf("Not enough memory");
}

void MatrixPrint(list* matrix, int columns_number, int strings_number)
{
	list* current = matrix;//only one matrix
	for (int i = 0; i < strings_number; i++)
	{
		for (int j = 0; j < columns_number; j++)
		{
			if ((j == current->col_number) && (i == current->str_number))
			{
				printf("%d ", current->value);
				current = current->next;
			}
			else printf("0 ");
		}
		printf("\n");
	}
}