#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lab3typ.h"

rowf** CreateMas(int countrow)
{
	rowf** C = (rowf**)malloc((countrow - 1) * sizeof(rowf*));//allocation of memory for pointers to strings
	if (C == NULL)//if the memory is not allocated, then we inform the user about it
	{
		printf("no memory allocated");
		return C;
	}
	return C;
}

int PushElement(rowf** list, int val, int num)//writing an item to the end of the list
{
	row* q = (row*)malloc(sizeof(row));//we allocate memory for the item we want to add to the list
	if (q == NULL)//if the memory is not allocated, then we inform the user about it
	{
		printf("no memory allocated");
		return -1;
	}
	//fill in the element we want to add
	q->next = NULL;
	q->number = num;
	q->value = val;
	if ((*list)->first != NULL)//if the first element already exists (it is not NULL), then add the element to the end of the list
	{
		row* loc = (*list)->first;//select the pointer to reach the end of the list
		while (loc->next != NULL)//we are executing until we reach the last item in the list
		{
			loc = loc->next;//go to the next item in the list
		}
		loc->next = q;//when the last value is reached, we equate it to the element being added
	}
	else
	{
		(*list)->first = q;//the first element of the list is equal to the additional element
	}
	return 0;
}

void DeleteRow(rowf** list)
{
	row* nex;//to save items after the first
	row* now;//pointer to the list before clearing
	if (((*list)->first) != NULL)
	{
		do
		{
			now = (*list)->first;//assign the value of the first element
			nex = now->next;//assign the value of the element following the first one
			(*list)->first = nex;//changing the first element of the list
			free(now);//deleting an element
		} while (nex != NULL);//until the end of the list
	}
}
void DeleteMas(rowf* maslis[], int countrow)
{
	int i = 0;
	for (i; (i < countrow - 1); i++)
	{
		DeleteRow(&maslis[i]);//deleting the contents of the line
		free(maslis[i]);//we delete the memory allocated for the line
	}
	free(maslis);//deleting the remnants of the array
}
int Compare(int c1, int c2)
{
	if (c1 == c2)//check for equality of values
	{
		return 0;
	}
	else
	{
		printf("The sizes of the matrices are different, it is impossible to add the matrices");
		return -1;
	}
}

void CountRowAndCol(char* filename, int* r1, int* r2, int* count)
{
	int max = 0;//to store the maximum number of row elements
	char c;//for a string character
	int n = 0;//to count the number of items in a row
	FILE* fin;
	fopen_s(&fin, filename, "r");//opening the file for reading
	if (fin == NULL)
	{
		printf("could not open the file");
		return;
	}
	c = fgetc(fin);//reading a character from a file
	while (c != 'B')//until we reached the name of the second matrix
	{
		if (c == 'A') c = fgetc(fin);//If in the row with the matrix name, read the following elements
		while (c != '\n')//until the end of the line, we read the elements and count their number
		{
			n++;
			c = fgetc(fin);//reading a character from a file
		}
		if (n >= max) max = n;//saving the maximum number of row elements
		n = 0;
		c = fgetc(fin);//reading a character from a file
		(*r1)++;//we count the number of rows in the matrix, taking into account the row with the name of the matrix
	}
	while (c != '\n')//until there are two transitions to the next line
	{
		if (c == 'B') c = fgetc(fin);//If in the row with the matrix name, read the following elements
		while (c != '\n')//until the end of the line, we read the elements and count their number
		{
			n++;
			c = fgetc(fin);//reading a character from a file
		}
		if (n >= max) max = n;//saving the maximum number of row elements
		n = 0;
		c = fgetc(fin);//reading a character from a file
		(*r2)++;//we count the number of rows in the matrix, taking into account the row with the name of the matrix
	}
	*count = max;//we pass the maximum number of line elements further into the program
	fclose(fin);//closing the file
}
int ReadCreateMas(char* filename, rowf* maslist[], int countrow, int* countcolu, int inl, int count)
{
	int countcol = 0;
	int i;
	int k = 1;//for the number of rows read
	rowf* list;
	FILE* fin;
	fopen_s(&fin, filename, "r");//opening the file for reading
	if (fin == NULL)
	{
		printf("could not open the file");
		return -1;
	}
	char* str = (char*)malloc((count + 2) * sizeof(char));//we allocate memory for the read string
	if (str == NULL)
	{
		printf("no memory allocated");
		return -1;
	}
	while (k < inl)//to count rows up to the first row of the matrix
	{
		k++;
		fgets(str, count * 2, fin);//reading a line from the file, we perform a count of *2 so that all elements of the string are read, including the terminating element
	}
	i = 0;
	while ((k <= inl + countrow - 2) && (k >= inl))//until all the rows of the matrix have been filled in
	{
		char* istr = NULL;//to save a substring
		countcol = 0;
		list = (rowf*)malloc(sizeof(rowf));//we allocate memory for the list
		if (list == NULL)
		{
			printf("no memory allocated");
			return -1;
		}
		list->first = NULL;//before filling in the first element is empty
		fgets(str, count * 2, fin);//reading a line from the file
		istr = strtok(str, " ");//splitting the string into substrings by space
		while (istr != NULL)//we are not counting the last substring yet
		{
			countcol++;//increasing the number of columns
			if (atoi(istr) != 0)//atoi-converts a string to a numeric series, the list is filled with only non-zero elements
			{
				PushElement(&list, atoi(istr), countcol);
			}
			istr = strtok(NULL, " ");//in the function, the first element is NULL to continue dividing into substrings of the original string
		}
		k++;//increasing the number of lines read
		maslist[i] = list;//filling the array with a list
		i++;//increasing the number of recorded lines
	}
	*countcolu = countcol;//the calculated number of lines is passed on to the program
	fclose(fin);//closing the file
	return 0;
}
int SumMas(rowf* A[], rowf* B[], rowf* C[], int rowc, int col)
{
	int n = 0;//counter for rows
	int i = 1;//counter for columns
	int sum;
	row* AA, * BB;
	while (n < rowc - 1)
	{
		rowf* list = (rowf*)malloc(sizeof(rowf));//we allocate memory for the list
		if (list == NULL)
		{
			printf("no memory allocated");
			return -1;
		}
		list->first = NULL;//before filling in the first element is empty
		AA = A[n]->first;//moving on to the first element of the n row of the array for the first matrix
		BB = B[n]->first;//moving on to the first element of the n row of the array for the second matrix
		if (AA == NULL)//if there was a zero row in the unloaded matrix (a row with only zeros in it)
		{
			AA = (row*)malloc(sizeof(row));//we allocate memory to go further into the loop
			if (AA == NULL)
			{
				return -1;
			}
		}
		if (BB == NULL)//if there was a zero row in the unloaded matrix (a row with only zeros in it)
		{
			BB = (row*)malloc(sizeof(row));//we allocate memory to go further into the loop
			if (BB == NULL)
			{
				return -1;
			}
		}
		while (i <= col)//we go through the columns of the matrices
		{
			if ((AA->number == i) && (BB->number == i))//if the column numbers of the elements of the two lists are equal to the column number of the sum matrix
			{
				sum = (AA->value) + (BB->value);//the sum of the matrix elements is equal to the sum of these elements
				PushElement(&list, sum, i);//adding an item to the end of the list
				if (AA != NULL) AA = AA->next;//we move on to the next element of the list, if this element is not zero
				if (BB != NULL) BB = BB->next;//we move on to the next element of the list, if this element is not zero
			}
			else if ((AA->number == i) && (BB->number != i))//if only one matrix has a column number that matches the column number of the resulting matrix
			{
				sum = (AA->value);// the element of the resulting matrix is equal to the element of the matrix that has the same column number
				PushElement(&list, sum, i);
				if (AA != NULL) AA = AA->next;//we move on to the next element of the list, if this element is not zero
				//For another list, we do not go to the next element, because if the numbers do not match now, they will match further down the list, because the elements in the list are stored starting from the first column
			}
			else if ((AA->number != i) && (BB->number == i))//if only one matrix has a column number that matches the column number of the resulting matrix
			{
				sum = (BB->value);// the element of the resulting matrix is equal to the element of the matrix that has the same column number
				PushElement(&list, sum, i);
				if (BB != NULL) BB = BB->next;//we move on to the next element of the list, if this element is not zero
				//For another list, we do not go to the next element, because if the numbers do not match now, they will match further down the list, because the elements in the list are stored starting from the first column
			}
			else if ((AA->number != i) && (BB->number != i))//if both matrices have an element column number that does not match the column number of the resulting matrix
			{
				sum = 0;//under this condition, the element of the resulting matrix will be equal to 0
				PushElement(&list, sum, i);
			}
			if (AA == NULL)//if in a sparse matrix, we have reached the end, but there is still a number of unfilled columns, then we allocate memory so that we can continue reading
			{
				AA = (row*)malloc(sizeof(row));
				if (AA == NULL)
				{
					return -1;
				}
			}
			if (BB == NULL)//if in a sparse matrix, we have reached the end, but there is still a number of unfilled columns, then we allocate memory so that we can continue reading
			{
				BB = (row*)malloc(sizeof(row));
				if (BB == NULL)
				{
					return -1;
				}
			}
			i++;
		}
		free(AA);//freeing up the memory allocated for the list items
		free(BB);//freeing up the memory allocated for the list items
		C[n] = list;//we fill the array of lists with the result of the sum of the matrices
		n++;
		i = 1;//go back to the first column
	}
	return 0;
}
void PrintfMas(rowf* C[], int row1)
{
	int i = 0;
	row* CC;////select the pointer to reach the end of the list
	while (i < row1 - 1)//we go through all the rows of the matrix
	{
		CC = C[i]->first;//moving on to the first element of the i row of the array
		while (CC != NULL)//until the end of the list
		{
			printf("%d ", CC->value);//printing the value of the list item
			CC = CC->next;//go to the next item in the list
		}
		printf("\n");//go to the next line for output
		i++;
	}
}