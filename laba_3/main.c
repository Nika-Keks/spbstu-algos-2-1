#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(void)
{
    int n = 5; // amounts of groups
 
   list** mass = create_mass("test.txt",n);
   print_m(mass,n);
   
   push_el_m(mass,34,"Arhipov","Misha","Saphronovich",5,n);
   delete_m(mass, 34, "Solovieva", "Katya", "Sergeevna", 1.8,n);
   print_m(mass, n);
   
   sort_m(mass,n);
   print_m(mass, n);

   list* stip = list_stip(mass, n);
   print(stip);
   printf("\n\n");
   list* otch = list_otch(mass, n);
   print(otch);

   clear_mass(mass,n);
   clear_list(stip);
   clear_list(otch);
 
  
   
}