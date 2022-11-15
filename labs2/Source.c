#include<stdio.h>
#include<stdlib.h>
#define INF 1000000000
#include"Header.h"
#pragma warning (disable:4996)


int main(void) {
	printf("Enter the number of data blocks: ");
	int n;
	//user enters the number of user requests
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {

		Listptr tmp = (Listptr)malloc(sizeof(List));
		if (tmp != NULL) {
			tmp->size = 0;
			tmp->tail = NULL;
			tmp->head = NULL;
		}
		else { printf("No memory available\n"); }//memory is not allocated
		//the user enters the number of memory blocks allocated for processes
		//for each memory block size in bytes
		int m;
		printf("Enter the number of memory blocks: ");
		scanf_s("%d", &m);
		printf("Enter blocks of memory: ");
		for (int j = 0; j < m; j++) {
			int size;
			void* memory;
			scanf_s("%d", &size);
			memory = (void*)malloc(size);
			Insert(tmp, j - 1, size, memory);
		}
		//the user enters the number of processes
		printf("Enter the number of processes: ");
		scanf_s("%d", &m);
		printf("Enter processes: ");
		for (int j = 0; j < m; j++)
		{
			int value;//the complexity of each process expressed in bytes
			scanf_s("%d", &value);
			bestfit(tmp, value);
		}
		if (tmp != NULL) {
			PrintList(tmp->head);
		}
		DeleteList(&tmp);
	}
	return 0;
}


