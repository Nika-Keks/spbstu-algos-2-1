#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void main(void) {
	char* FILETXT = "Text.txt";
	int number_of_lines = Line_count(FILETXT);
	int number_of_words = Words_count(FILETXT);
	char** all_words = read_file(FILETXT, number_of_words); //read all words
	char** arr = change_array(all_words, number_of_words); //creat an array with non-repeating words
	char** Lines = lines(FILETXT, number_of_lines); //read lines from file into an array
	tree* Tree = add_element(arr[0], Lines, number_of_lines);  //create root
	for (int i = 1; i < 7; i++)
	{
		choose_place(&Tree, arr[i], Lines, number_of_lines); //add elements from array to tree
	}
	print_tree(Tree); //print
}