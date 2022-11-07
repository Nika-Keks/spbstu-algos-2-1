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
    char* format = "%d %s %s %s %lf\n";
    int group;
    char* surname=malloc(WORD_LENGTH * sizeof(char));
    char* firstname  = malloc(WORD_LENGTH * sizeof(char));
    char* secondname = malloc(WORD_LENGTH * sizeof(char));
    double mark;


    if (fscanf(file, format, &group, surname, firstname, secondname, &mark) != EOF)
        return create_node(group, surname, firstname, secondname, mark);
   
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
the function creates creates an array of lists from the data read from the file
*/

list** create_mass(char* file_name, int n)
{
    FILE* file = fopen(file_name, "r");
    list* list_n = ListFile(file);
    list* sup = list_n;
    int* mass_int = (int*)malloc(n * sizeof(int)); // we allocate memory to the array where we will store the group numbers
    if (!mass_int)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)  // we fill the array with numbers that cannot have groups
    {
        mass_int[i] = -1;
    }

    while(sup!=NULL)
    {
        if (comp(mass_int, sup->group, n)==0)  // check whether a certain place in the array is assigned to the encountered group, if not, then add the group to mass_int
        {
            for (int i = 0; i < n; i++)
            {
                if (mass_int[i] == -1)
                {
                    mass_int[i] = sup->group;
                    break;
                }
                
            }
        }
        sup = sup->next;
    }
    
    list** mass = (list**)malloc(n*sizeof(list*));
    if (!mass)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (mass_int[i] == -1) // if there are fewer groups, then we will not use the remaining space
        {
            mass[i] = NULL;
            continue;
        }

        sup = list_n;
        
            if (sup->group == mass_int[i]) // adding elements to the array first creating a node
            {
                mass[i] = create_node(sup->group, sup->surname, sup->firstname, sup->secondname, sup->mark);



                sup = sup->next;
            }
            else
            {
                
                while (sup->group != mass_int[i])
                {
                    sup = sup->next;
                }
                mass[i] = create_node(sup->group, sup->surname, sup->firstname, sup->secondname, sup->mark);
                sup = sup->next;
            }
        
            while (sup != NULL) // adding items to the lists, nodes have already been created
            {
                if (sup->group == mass_int[i])
                    push_el((mass[i]), create_node(sup->group, sup->surname, sup->firstname, sup->secondname, sup->mark));
                sup = sup->next;
            }
    }
    free(mass_int);
    return mass;
}
/*
a function that checks whether there is a group number in the array
*/

int comp(int* mass, int group,int n)
{
    for (int i = 0; i < n; i++)
    {
        if (mass[i] == group)
            return 1;
    }
    return 0;
}
/*
the function creates a list node
*/
list* create_node(int group_i, char* surname_i, char* firstname_i, char* secondname_i, double mark_i)
{
    list* node = (list*)malloc(sizeof(list));
   
    if (!node)
    {
        return 0;
    }
    node->surname = surname_i;
    node->firstname = firstname_i;
    node->secondname = secondname_i;
    node->group = group_i;
    node->mark = mark_i;
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
void push_el_m(list** mass, int group_i,char* surname_i, char* firstname_i, char* secondname_i, double mark_i,int n)
{
    char* surname = malloc(WORD_LENGTH * sizeof(char));  
    char* firstname = malloc(WORD_LENGTH * sizeof(char));
    char* secondname = malloc(WORD_LENGTH * sizeof(char));
    if (!surname || !firstname || !secondname)
    {
        exit(0);
    }
    strcpy(surname,surname_i);
    strcpy(firstname, firstname_i);
    strcpy(secondname, secondname_i);
   
    list* add = create_node(group_i, surname, firstname,  secondname,  mark_i);
    for (int i = 0; i < n; i++)
    {
        list* test_1 = mass[i];
        if (test_1) {
            if (test_1->group == group_i)
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
    if (*list_n!=NULL)
    {

        list* cur = NULL;
        list* prev = NULL;

        cur = *list_n;
        
        for(int i=0;i<pos.pos_2 ;i++) // defining the element to be deleted
        {
            prev = cur;
            cur = cur->next;
        }

        if (prev == NULL)
        {
            *list_n = (*list_n)->next;
            free(cur->surname);
            free(cur->firstname);
            free(cur->secondname);
            free(cur);
           
        }
        else
        {
            prev->next = cur->next;
            free(cur->surname);
            free(cur->firstname);
            free(cur->secondname);
            free(cur);
        }
    }
}
/*
a function that removes an element from a list located in an array of matches, the position of the element is an input parameter
*/
void delete_m(list** mass, int group_i, char* surname_i, char* firstname_i, char* secondname_i, double mark_i, int n)
{
    list* list_test = create_node(group_i, surname_i, firstname_i, secondname_i, mark_i);
    position pos = find_n(mass, list_test, n);

    if (pos.pos_1 == -1)
    {
        exit(-1);
    }
    list* test = mass[pos.pos_1];
    delete(&test,pos);
   
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
       if (new==NULL || (strcmp(new->surname, sup->surname) > 0))
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
void sort_m(list** mass,int n)
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
    char* format = "%d %s %s %s %lf\n"; // output format
    list* test_1 = list_n;
    do
    {
        printf(format, test_1->group, test_1->surname, test_1->firstname, test_1->secondname, test_1->mark);
        test_1 = test_1->next;
    } while (test_1 != NULL);
}
/*
a function that displays an array of lists on the screen
*/
void print_m(list** mass,int n)
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

/*
the function makes a list of people applying for a scholarship based on an array of lists
*/
list* list_stip(list** mass, int n)
{
    int flag = 0;
    list* stip = (list*)malloc(sizeof(list));
    for (int i = 0; i < n; i++)
    {
        list* test_1 = mass[i];
        while (test_1 != NULL)
        {
            
            
            if ((flag > 0) && (test_1->mark > 3.5)) // adding items to the list
            {
                list* add = create_node(test_1->group, test_1->surname, test_1->firstname, test_1->secondname, test_1->mark);
                push_el(stip, add);
            }
            if ((flag == 0) && (test_1->mark > 3.5)) // creating a list node
            {
                stip = create_node(test_1->group, test_1->surname, test_1->firstname, test_1->secondname, test_1->mark);
                flag++;

            }
            test_1 = test_1->next;
        }
    }
    return stip;
}

/*
the function makes a list of people applying for deduction based on an array of lists
*/

list* list_otch(list** mass, int n)
{
    int flag = 0;
    list* otch = (list*)malloc(sizeof(list));
    for (int i = 0; i < n; i++)
    {
        list* test_1 = mass[i];
        while (test_1 != NULL)
        {


            if ((flag > 0) && (test_1->mark < 2.5))
            {
                list* add = create_node(test_1->group, test_1->surname, test_1->firstname, test_1->secondname, test_1->mark);
                push_el(otch, add);
            }
            if ((flag == 0) && (test_1->mark < 2.5))
            {
                otch = create_node(test_1->group, test_1->surname, test_1->firstname, test_1->secondname, test_1->mark);
                flag++;

            }
            test_1 = test_1->next;
        }
    }
    return otch;
}

/*
a function that determines the position of an element in the list of arrays
*/

position find_n(list** mass, list* list_n,int n)
{
    position pos;
    pos.pos_1 = -1;
    pos.pos_2 = -1;
    int number = 0;
   
   
    if ((mass)&&(list_n))
    {
        
        for (int i=0;i<n;i++)
        {
           list* test = mass[i];
            number = 0;
            while (test != NULL)
            {
                if ( ( ( test->group) == (list_n->group) ) && (strcmp(test->surname,(list_n->surname))==0) && (strcmp(test->firstname,(list_n->firstname))==0) && (strcmp(test->secondname, (list_n->secondname))==0) && (test->mark == (list_n->mark))) // we check whether we need this elementì
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
            free(sup->firstname);
            free(sup->secondname);
            free(sup);

        }
        list* sup = list_n;
        free(sup->surname);
        free(sup->firstname);
        free(sup->secondname);
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

