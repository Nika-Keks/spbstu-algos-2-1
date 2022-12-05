#pragma warning(disable : 4996)
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int count = 0; //number of words
int count_word = 0; //number of non-repeating words
int count_string = 0; //number of rows
/*
* a function that reads words from a file into an array
*/
char** full_arr(char* filename)
{
	FILE* file = fopen(filename, "r");
	char** test = malloc(100 * sizeof(char*));
	if (test) {
		for (int i = 0; i < 100; i++)
		{
			test[i] = malloc(sizeof(char));
		}
		count = 0;
		while (fscanf(file, "%s", test[count]) != EOF) //reading words from a file into an array cell
		{
			count++;
		}
		char** tmp = realloc(test, count * sizeof(char*));
		if (tmp != NULL)
		{
			test = tmp;
		}
		fclose(file);
		return test;
	}
	exit(-1);
}

/*
* a function that creates an array of non-repeating words from an array of words
*/
char** arr_of_words(char** mas)
{
	char** arr = malloc(count * sizeof(char*));
	if (arr) {
		for (int i = 0; i < count; i++)
		{
			arr[i] = malloc(sizeof(char));
			arr[i] = "n";
		}
		for (int i = 0; i < count; i++)
		{
			if (is_repeat(mas[i], arr) == -1) // we check whether the word was written to the array
			{
				arr[count_word] = mas[i];
				count_word++;
			}
		}
		char** tmp = realloc(arr, count_word * sizeof(char*));
		if (tmp != NULL)
		{
			arr = tmp;
		}
		free(mas);
		return arr;
	}
	exit(-1);
}
/*
* a function that checks whether a word has been written to an array
*/
int is_repeat(char* mas, char** arr)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(mas, arr[i]) == 0)
			return 1;
	}
	return -1;
}
/*
* the function reads strings from a file into an array
*/
char** arr_of_strings(char* filename)
{
	FILE* file = fopen(filename, "r");
	char** test = malloc(10 * sizeof(char*));
	for (int i = 0; i < 10; i++)
	{
		test[i] = malloc(50 * sizeof(char));
	}
	while (fgets(test[count_string], 50 * sizeof(char), file) != NULL)
	{
		count_string++;
	}
	char** tmp = realloc(test, count_string * sizeof(char*));
	if (tmp != NULL)
	{
		test = tmp;
	}
	fclose(file);
	return test;
}
/*
* a function that creates a tree node
*/
tree* create_Node(char* el, char** text) {
	tree* tmp = (tree*)malloc(sizeof(tree));
	if (!tmp)
		exit(-1);
	tmp->l = tmp->r = NULL;
	tmp->word = el; // node key
	int k = 0;
	int* number = malloc(count_string * 2 * sizeof(int));
	if (!number)
		exit(-1);
	for (int i = 0; i < count_string; i++)// we look at which lines the word was found in and create an array of line numbers
	{
		if (strstr(text[i], el) != NULL)
		{
			number[k] = i + 1;
			k++;
		}
	}
	number[k] = -1;// the final element for convenient output of elements is not a line number
	int* sup = realloc(number, (k + 1) * sizeof(int));
	if (sup != NULL)
	{
		number = sup;
	}
	tmp->number = number;
	return tmp;
}
/*
* the function inserts elements into the tree
*/
void insert_node(tree** head, char* el, char** text)
{
	tree* tmp = NULL;
	tmp = *head;
	while (tmp)
	{
		if (strcmp(el, tmp->word) > 0) //compare the character codes, or the size of the words, if the element is larger than the word in the node, then add it to the right branch
		{
			if (tmp->r)//we continue until the node is free
			{
				tmp = tmp->r;
				continue;
			}
			else
			{
				tmp->r = create_Node(el, text);
				return;
			}
		}
		if (strcmp(el, tmp->word) < 0)//compare the character codes, or the size of the words, if the element is smaller than the word in the node, then add it to the left branch
		{
			if (tmp->l) // we continue until the node is free
			{
				tmp = tmp->l;
				continue;
			}
			else
			{
				tmp->l = create_Node(el, text);
				return;
			}
		}
	}
}
/*
* the function creates a binary tree, the input data is a text file
*/
tree* create_tree(char* filename)
{
	//printf("Words  Strings\n");
	char** word_arr = arr_of_words(full_arr(filename));
	char** str = arr_of_strings(filename);
	tree* tree_n = create_Node(word_arr[0], str);//creating the root of the tree
	for (int i = 1; i < count_word; i++)
	{
		insert_node(&tree_n, word_arr[i], str);//inserting elements
	}
	free(str);
	free(word_arr);
	return tree_n;
}
/*
* the function displays the word from the test example, and then the number of lines where this word occurred
*/
void print(tree* node,short* flag)
{
	if (*flag == 1) {
		printf("Words - Strings\n");
		printf("---------------\n");
		*flag = 0;
	}
	if (node == NULL)
	{
		return;
	}
	print(node->l,flag);
	printf("%s - ", node->word);
	int i = 0;
	while (node->number[i] != -1)
	{
		printf("%d ", node->number[i]);
		i++;
	}
	printf("\n");
	print(node->r,flag);
}
/*
* memory cleaning function
*/
void free_n(tree* node)
{
	if (node == NULL)
	{
		return;
	}
	free_n(node->l);
	free(node->number);
	free_n(node->r);
}