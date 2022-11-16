#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(void)
{
    int n = 26; // amounts of letters

    list** mass = create_mass("test.txt", n);
    //print_m(mass, n);

    push_el_m(mass, "Frolov", 84451515545, n);
    //print_m(mass, n);
    delete_m(mass, "Frolov", 84451515545, n);
    //print_m(mass, n);

    sort_m(mass, n);
    print_m(mass, n);

    print_to_FILE(mass, "output.txt",n);
    
    clear_mass(mass, n);

    return 0;

}