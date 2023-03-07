#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "function.h"
#pragma warning (disable:4996)
int main()
{
	size_t* start = NULL, * last = NULL;//To save the address of the beginning of the memory block and the address on the busy memory block for further work with the release of memory
	dis* list = CreateList(&start, &last);//creating a doubly linked list
	int i = 1;//the variable remembers the directions of searching for a free block
	int t = 0;//for the user's work
	size_t me;//for the block size entered by the user
	printf("Enter 1 if you want to get a piece of memory\nEnter 0 if you want to free up memory\nEnter - 1 if you want to shut down\n");
	do
	{
		printf("Enter a value(1 or 0 or -1)=");
		scanf("%d", &t);
		if (t == 1)
		{
			printf("_Enter memory size=");
			scanf("%Iu", &me);
			Node* k = Fistfit(me, &list, &i);//looking for a free memory block
			if (k != NULL)
			{
				//we give the user a pointer only to the part with the filled memory without a descriptor
				Node* adr = (Node*)((uintptr_t)(k)+sizeof(Node));
				printf("__Adress memory=%p \n", adr);
			}
			else
			{
				printf("There was no free memory for this size\nIf you want to continue filling, try requesting a smaller memory or free up memory.\n");
			}
			if ((list->head == NULL) && (list->tail) == NULL) printf("All free memory is full or the size of the required block cannot be allocated, try to change the size of the required block, or free up memory, or shut down the memory.\n");
		}
		if (t == 0)
		{
			Node* pos = NULL;
			printf("_Carefully enter the address\n");
			printf("___Enter the memory address=");
			scanf("%p", &pos);
			Node* posadr = (Node*)((uintptr_t)(pos)-sizeof(Node));//since the user passes a pointer to his occupied part without a descriptor
			FreeMem(&posadr, &list, &start, &last);//freeing a busy block
		}
	} while (t != -1);
	checkup(&start, &last);
	DeleteList(&list, &start);//deleting a list and a memory block
	return 0;
}