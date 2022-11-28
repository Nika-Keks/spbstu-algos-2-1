#pragma once
typedef struct tree
{
    char* word;
    int* number;
    struct tree* right;
    struct tree* left;
}tree;

int Words_count(char* filename); //count number of all words in file
int Line_count(char* filename); //count number of lines
char** read_file(char* filename, int number_of_words);  //read words from file and write them as an array
check_repeatability(char* word, char** arr, int number_of_words);  //check up if this word has been written to an array before
char** change_array(char** text, int number_of_words); //creat new array with non-repeating words
char** lines(char* filename, int count_lines); //read lines from file into an array
tree* add_element(char* element, char** text, int count_lines); //add element to the tree
void choose_place(tree** root, char* el, char** text, int count_string); //choose place for new element
void print_tree(tree* Tree); // print tree in internal order
