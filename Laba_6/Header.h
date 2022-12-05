#pragma once
typedef struct tree
{
    char* word;
    int* number;
    struct tree* r;
    struct tree* l;
}tree;

char** full_arr(char* filename);
char** arr_of_words(char** mas);
int is_repeat(char* mas, char** arr);
char** arr_of_strings(char* filename);
tree* create_tree(char* filename);
void insert_node(tree** head, char* el, char** text);
void print(tree* node, short* flag);
void free_n(tree* node);