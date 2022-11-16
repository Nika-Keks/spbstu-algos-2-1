#pragma warning(disable : 4996)

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

#define WORD_LENGTH 32 // max word's length 


/*
the function creates a list node from the data read from the file
*/
list* NodeFile(FILE* file)
{
    char* format = "%s %llu\n";
    char* surname = malloc(WORD_LENGTH * sizeof(char));
    unsigned long long phone;


    if (fscanf(file, format,surname, &phone) != EOF)
        return create_node(surname, phone);

    return NULL;
}

/*
the function creates a list from the data read from the file
*/
list* ListFile(FILE* file)
{
    list* head = NULL;
    list* cur = NULL;
    head = NodeFile(file);
    cur = NodeFile(file);
    while (cur != NULL)
    {
        push_list(head, cur);
        cur = NodeFile(file);
    }
    return head;
}

/*
the function creates an array of lists from the data read from the file
*/
list** create_mass(char* file_name, int n)
{
    FILE* file = fopen(file_name, "r");
    list* list_n = ListFile(file);
    list* sup = list_n;
    char* mass_char = (char*)malloc(n * sizeof(char)); // we allocate memory to the array where we will store the group numbers
    if (!mass_char)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)  // we fill the array with numbers that cannot have groups
    {
        mass_char[i] = ' ';
    }

    while (sup != NULL)
    {
        if (comp(mass_char, sup->surname, n) == 0)  // check whether a certain place in the array is assigned to the encountered letter, if not, then add the letter to mass_char
        {
            for (int i = 0; i < n; i++)
            {
                if (mass_char[i] == ' ')
                {
                    mass_char[i] = sup->surname[0];
                    break;
                }

            }
        }
        sup = sup->next;
    }

    list** mass = (list**)malloc(n * sizeof(list*));
    if (!mass)
    {
        return 0;
    }

    sort_M(mass_char, n);

    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        if (mass_char[i] == ' ') // if there are fewer groups, then we will not use the remaining space
        {
            mass[i] = NULL;
            continue;
            cnt++;
        }
        sup = list_n;


        if (sup->surname[0] == mass_char[i]) // adding elements to the array first creating a node
        {
            mass[i] = create_node(sup->surname, sup->phone);
            sup = sup->next;
        }
        else
        {

            while (sup->surname[0] != mass_char[i])
            {
                sup = sup->next;
            }
            mass[i] = create_node(sup->surname, sup->phone);
            sup = sup->next;
        }

        while (sup != NULL) // adding items to the lists, nodes have already been created
        {
            if (sup->surname[0] == mass_char[i])
                push_el((mass[i]), create_node(sup->surname, sup->phone));
            sup = sup->next;
        }
    }
    free(mass_char);
    return mass;
}
/*
a function that checks whether there is a group number in the array
*/
int comp(char* mass, char* surname, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (mass[i] == surname[0])
            return 1;
    }
    return 0;
}
/*
the function creates a list node
*/
list* create_node(char* surname_i,unsigned long long phone_i)
{
    list* node = (list*)malloc(sizeof(list));

    if (!node)
    {
        return 0;
    }
    node->surname = surname_i;
    node->phone = phone_i;
    node->next = NULL;
    return node;

}
/*
a function that adds one list to the end of the second
*/
void push_list(list* mass, list* add)
{
    list* last_el = last_list(mass);

    if (add)
    {
        last_el->next = add;
    }
}

/*
a function that adds a list node to the end of another list
*/
void push_el(list* list_n, list* list_1)
{
    list* last_el = last_list(list_n);
    list* add = (list*)malloc(sizeof(list*));
    add = list_1;
    if (add)
    {

        last_el->next = add;
    }
}
/*
a function that adds an element to an array of lists, to the list of the corresponding group
*/
void push_el_m(list** mass, char* surname_i, unsigned long long phone_i, int n)
{
    char* surname = malloc(WORD_LENGTH * sizeof(char));
    if (!surname )
    {
        exit(0);
    }
    strcpy(surname, surname_i);

    list* add = create_node(surname, phone_i);
    for (int i = 0; i < n; i++)
    {
        list* test_1 = mass[i];
        if (test_1) {
            if (test_1->surname[0] == surname_i[0])
            {
                push_el(test_1, add);

            }
        }
    }
}
/*
a function that defines the final element of the list and returns a pointer to it
*/
list* last_list(list* list_n)
{
    list* cur = list_n;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    return cur;
}

/*
a function that removes an item from the list, the item position is an input parameter
*/
void delete(list** list_n, position pos)
{
    if (*list_n != NULL)
    {

        list* cur = NULL;
        list* prev = NULL;

        cur = *list_n;

        for (int i = 0; i < pos.pos_2; i++) // defining the element to be deleted
        {
            prev = cur;
            cur = cur->next;
        }

        if (prev == NULL)
        {
            *list_n = (*list_n)->next;
            free(cur->surname);
            free(cur);

        }
        else
        {
            prev->next = cur->next;
            free(cur->surname);
            free(cur);
        }
    }
}
/*
a function that removes an element from a list located in an array of matches, the position of the element is an input parameter
*/
void delete_m(list** mass, char* surname_i, unsigned long long phone_i, int n)
{
    list* list_test = create_node(surname_i, phone_i);
    position pos = find_n(mass, list_test, n);

    if (pos.pos_1 == -1)
    {
        exit(-1);
    }
    list* test = mass[pos.pos_1];
    delete(&test, pos);

}
/*
a function that sorts the list by the insertion method
*/
list* sort(list* list_n)
{
    list* new = NULL;

    while (list_n != NULL)
    {
        list* sup = list_n;
        list_n = list_n->next;
        if (new == NULL || (strcmp(new->surname, sup->surname) > 0))
        {
            sup->next = new;
            new = sup;
        }
        else
        {
            list* cur = new;
            while (cur->next != NULL && (strcmp(sup->surname, cur->next->surname) >= 0))
            {
                cur = cur->next;
            }
            sup->next = cur->next;
            cur->next = sup;
        }

    }
    return new;

}


/*
a function that sorts an array of lists
*/
void sort_m(list** mass, int n)
{
    for (int i = 0; i < n; i++)
    {
        mass[i] = sort(mass[i]);
    }
}

/*
a function that displays a list on the screen
*/
void print(list* list_n)
{
    char* format = "%s %llu\n"; // output format
    list* test_1 = list_n;
    printf("%c\n", test_1->surname[0]);
    do
    {
        printf(format, test_1->surname, test_1->phone);
        test_1 = test_1->next;
    } while (test_1 != NULL);
}
/*
a function that displays an array of lists on the screen
*/
void print_m(list** mass, int n)
{
    for (int i = 0; i < n; i++)
    {
        list* test_1 = mass[i];
        if (test_1 != NULL)
        {
            print(test_1);
            printf("\n");
        }
    }
    printf("\n\n");
}


position find_n(list** mass, list* list_n, int n)
{
    position pos;
    pos.pos_1 = -1;
    pos.pos_2 = -1;
    int number = 0;


    if ((mass) && (list_n))
    {

        for (int i = 0; i < n; i++)
        {
            list* test = mass[i];
            number = 0;
            while (test != NULL)
            {
                if (((test->surname[0]) == (list_n->surname[0])) && (strcmp(test->surname, (list_n->surname)) == 0) && (test->phone == (list_n->phone))) // we check whether we need this element
                {
                    pos.pos_1 = i;
                    pos.pos_2 = number;
                }
                number++;
                test = test->next;
            }
        }
    }
    return pos;
}

/*
the function of clearing the memory of an array of lists
*/
void clear_mass(list** mass, int n)
{
    for (int i = 0; i < n; i++)
    {
        clear_listandchar(mass[i]);
    }
    free(mass);
}
/*
the function of clearing the memory of a list containing rows for which memory was allocated
*/
void clear_listandchar(list* list_n)
{
    if (list_n) {
        list* cur = list_n->next;
        while (cur)
        {
            list* sup = cur;
            cur = cur->next;
            free(sup->surname);
            free(sup);

        }
        list* sup = list_n;
        free(sup->surname);
        free(sup);
    }

}
/*
the function of clearing the memory of a list containing rows for which no memory was allocated
*/
void clear_list(list* list_n)
{
    if (list_n) {
        list* cur = list_n->next;
        while (cur)
        {
            list* sup = cur;
            cur = cur->next;

            free(sup);

        }
        list* sup = list_n;

        free(sup);
    }
}

/*
the function that sorts an array of letters
*/
void sort_M(char* mass_char, int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((mass_char[j] == ' ') || (mass_char[j+1] == ' ')) { break; }
            if (mass_char[j] > mass_char[j + 1]) {
                char ch = mass_char[j];
                mass_char[j] = mass_char[j + 1];
                mass_char[j + 1] = ch;
            }
        }
    }
}
/*
the function that write sand saves list to a file
*/
void print_str_to_File(FILE* file, list* list_n)
{
    char* format = "%s %llu\n"; // output format
    list* test_1 = list_n;
    fprintf(file, "%c\n", test_1->surname[0]);
    do
    {
        fprintf(file, format, test_1->surname, test_1->phone);
        test_1 = test_1->next;
    } while (test_1 != NULL);
}

/*
the function that write sand saves an array of lists to a file
*/
void print_to_FILE(list** mass, char* file_name, int n)
{
    FILE* file = fopen(file_name, "w");
    for (int i = 0; i < n; i++)
    {
        list* test_1 = mass[i];
        if (test_1 != NULL)
        {
            print_str_to_File(file,test_1);
            fprintf(file, "\n");
        }
    }
    fprintf(file, "\n\n");
    fclose(file);
}
