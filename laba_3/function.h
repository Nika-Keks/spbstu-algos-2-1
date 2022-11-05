#pragma once
typedef struct list 
{
    struct list* next;
    char* surname;
    char* firstname;
    char* secondname;
    double mark; // average mark
    int group;

    
}list;
typedef struct position
{
    int pos_1;
    int pos_2;


}position; // stores information about position element

void push_el_m(list** mass, int group_i, char* surname_i, char* firstname_i, char* secondname_i, double mark_i, int n);
void print_m(list** mass, int n);
list* NodeFile(FILE* file);
int comp(int* mass, int group, int n);
list* ListFile(FILE* file);
list* last_list(list* list_n);
list* create_node(int group_i, char* surname_i, char* firstname_i, char* secondname_i, double mark_i);
void push_list(list* mass, list* add);
void print(list* list_n);
list** create_mass(char* file_name, int n);
void push_el(list* mass, list* list_1);
list* sort(list* list_n);
void delete(list** list_n, position pos);
void sort_m(list** mass, int n);
void delete_m(list** mass, int group_i, char* surname_i, char* firstname_i, char* secondname_i, double mark_i, int n);
void clear_mass(list** mass, int n);
void clear_list(list* list_n);
list* list_stip(list** mass, int n);
list* list_otch(list** mass, int n);
position find_n(list** mass, list* list_n, int n);
void clear_listandchar(list* list_n);