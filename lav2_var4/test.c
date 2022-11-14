#pragma warning(disable : 4996)
#include <stdio.h>
#include "struct.h"

int main() {
	int size = 100;
	int n = 14;
	List* p = create_memory(1, size); //create free space list
	int i = 1;
	printf("Firstly 100 bytes of memory were allocated for the free space list. We will alternately allocate pieces of memory of arbitrary size to the user:\n");
	printf("If there is not enough memory to allocate, the program writes 'Not enough memory'\n");
	for (i; i <= n; i++) { //allocate memory to a user from the free space list for several times
		pick_out_memory(i, p);
	}

	printf("\n");
	printf("The memory looks like now:\n");
	print(p);
	printf("\n");

	printf("The user wants to return to the list of free space  a memory cell number 7 which size is 7 bytes. The memory looks like now:\n");
	p = delete(p, 7); 
	print(p);
	printf("\n");

	printf("The user wants to return to the list of free space  a memory cell number 6 which size is 6 bytes. The memory looks like now:\n");
	p = delete(p, 6);
	print(p);
	printf("\n");

	printf("The user wants to return to the list of free space  a memory cell number 7 which size is 8 bytes. The memory looks like now:\n");
	p = delete(p, 7);
	print(p);
	printf("\n");

	printf("The user asked to allocate him a memory cell which size is 5 bytes. We will allocate it with the help of “first fit” strategy.\n");
	pick_out_memory(5, p);
	printf("\n");

	printf("The memory looks like now:\n");
	print(p);
	printf("\n");

	printf("Check up the integrity:\n");
	checkup(p);
}

