#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "struct.h"

int Words_count(char* filename) //count number of all words in file
{
	FILE* fin;
	fin = fopen(filename, "r");
	int _Space = 1;
	int _Count = 0;
	char ch[2] = { 0 };
	while (!feof(fin))
	{
		fgets(ch, 2, fin);
		if (ch[0] > 41)
			_Space = 0;
		else if (0 == _Space)
		{
			_Count++;
			_Space = 1;
		}
		ch[0] = 0;
	}
	fclose(fin);
	return _Count;
}

int Line_count(char* filename) //count number of lines
{
	FILE* fin;
	fin = fopen(filename, "r");
	int lines_count = 0; // lines counter
	while (!feof(fin))
	{
		if (fgetc(fin) == '\n')
			lines_count++;
	}
	lines_count++;
	fclose(fin);
	return lines_count;
}

char** read_file(char* filename, int number_of_words)  //read words from file and write them as an array
{
	FILE* fin;
	fin = fopen(filename, "r");
	char** arr = malloc(100 * sizeof(char*));
	for (int i = 0; i < 50; i++)  //create array
	{
		arr[i] = malloc(sizeof(char));
	}
	int n = 0; //counter
	while (fscanf(fin, "%s", arr[n]) != EOF) //read words 
	{
		n++;
	}
	char** mem = realloc(arr, (number_of_words) * sizeof(char*)); //check up and change memory
	arr = mem;
	fclose(fin);
	return arr;
}

int check_repeatability(char* word, char** arr, int number_of_words)  //check up if this word has been written to an array before
{
	for (int i = 0; i < number_of_words; i++)
	{
		if (strcmp(word, arr[i]) == 0)
			return 1;
	}
	return -1;
}

char** change_array(char** text, int number_of_words) //creat new array with non-repeating words
{
	char** arr = malloc(number_of_words * sizeof(char*));
	int i = 0;
	for (i; i < number_of_words; i++)
	{
		arr[i] = malloc(sizeof(char));
		arr[i] = "n";
	}
	int i_arr = 0; //counter for new array
	i = 0; //counter for previous array
	for (i; i < number_of_words; i++)
	{
		if (check_repeatability(text[i], arr, number_of_words) == -1) //check up if this word has been written to an array before
		{
			arr[i_arr] = text[i];
			i_arr++;
		}
	}
	char** mem = realloc(arr, i_arr * sizeof(char*)); //check up and change memory
	arr = mem;
	free(text);
	return arr;
}


char** lines(char* filename, int count_lines) //read lines from file into an array
{
	FILE* fin;
	fin = fopen(filename, "r");
	char** arr = malloc(count_lines * 2 * sizeof(char*));
	for (int i = 0; i < 10; i++)
	{
		arr[i] = malloc(50 * sizeof(char));
	}
	int i = 0; //counter
	while (fgets(arr[i], 50 * sizeof(char), fin) != NULL)
	{
		i++;
	}
	fclose(fin);
	return arr;
}

tree* add_element(char* element, char** text, int count_lines) //add element to the tree
{
	tree* tmp = (tree*)malloc(sizeof(tree));
	tmp->left = tmp->right = NULL;
	tmp->word = element; // node key
	int* number = malloc(15 * sizeof(int)); //create an array of lines numbers
	int k = 0;//counter for 
	int i = 0; //counter for lines
	for (i; i < count_lines; i++) {
		if (strstr(text[i], element) != NULL) //add to an array numbers of lines in which this word occurs
		{
			number[k] = i + 1;
			k++;
		}
	}
	number[k] = -1;
	int* mem = realloc(number, (k + 1) * sizeof(int));
	number = mem;
	tmp->number = number;
	return tmp;
}

void choose_place(tree** root, char* el, char** text, int count_string) //choose place for new element
{
	tree* tmp = NULL;
	tmp = *root;
	while (tmp)
	{
		//compare the size of the words,
		if (strcmp(el, tmp->word) > 0) //smaller word than previous
		{
			//go to the right while it is possible
			if (tmp->right != NULL) {
				tmp = tmp->right;
			}
			else
			{
				tmp->right = add_element(el, text, count_string); //add element to the tree
				return;
			}
		}
		if (strcmp(el, tmp->word) < 0)//larger word than previous
		{
			//go to the left while it is possible
			if (tmp->left != NULL) {
				tmp = tmp->left;
			}
			else
			{
				tmp->left = add_element(el, text, count_string); //add element to the tree
				return;
			}
		}
	}
}

void print_tree(tree* Tree) // print tree in internal order
{
	if (Tree == NULL)
	{
		return;
	}
	print_tree(Tree->left);
	printf("The word ' % s ' occurs in lines: ", Tree->word);
	int i = 0;
	while (Tree->number[i] != -1)
	{
		printf("%d ", Tree->number[i]);
		i++;
	}
	printf("\n");
	print_tree(Tree->right);
}
