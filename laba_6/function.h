#pragma once
typedef struct tree
{
    char* word;
    int* number;
    struct tree* r;
    struct tree* l;
}tree;

char** full_arr(char* filename);
char** arr_word(char** mas);
int repeat(char* mas, char** arr);
char** string_arr(char* filename);
tree* create_tree(char* filename);
void insert(tree** head, char* el, char** text);
void print(tree* node);
void free_n(tree* node);