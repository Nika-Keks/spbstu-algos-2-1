#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "lab2_5type.h"
#pragma warning (disable:4996)
#define sizeblock 2048//the size of the entire block

size_t* createBlock() {
	size_t* tmp = (size_t*)malloc(sizeblock);//allocating dynamic memory
	if (tmp == NULL)//if memory allocation is unsuccessful
	{
		printf("Ошибка выделения памяти");
	}
	return tmp;
}

dis* CreateList(size_t** start, size_t** last)//инициализируем список свободной памяти
{
	dis* list = (dis*)malloc(sizeof(dis));//memory under the head of the list
	size_t* m = createBlock();//we allocate memory for the entire block
	if (list != NULL)
	{
		list->head = (Node*)m;//we allocate memory for the entire block
		list->head->size1 = sizeblock;
		list->head->prev = list->head->next = NULL;
		Node2* busy = (Node2*)((uintptr_t)(list->head) + (list->head->size1) - sizeof(Node2));//we put a pointer to the block's occupancy
		busy->size2 = (int)(list->head->size1);//initially, the block is free
		list->tail = list->head;
		*start = (size_t*)(list->head);//we remember the address of the employment of the initial memory block
		*last = (size_t*)busy;//we remember the beginning of the memory block
	}

	return list;
}

void DeleteList(dis** FreeList, size_t** start)
{
	free(*start);//we clear the memory block we have allocated by pointing to the beginning of the block
	(*start) = NULL;
	free(*FreeList);//memory under head and tail
	(*FreeList) = NULL;
}
void DeleteEl(Node* q, dis** List)
{
	//we do not do free, because when writing an element to the list, memory was not allocated for it and the entire record was through pointers
	Node* prev, * next;
	if (q == (*List)->head)//removing the head element
	{
		if (q->next != NULL)//so it can be if the list consists of one element
		{
			(*List)->head = q->next;
			(*List)->head->prev = NULL;
		}
		else((*List)->head = (*List)->tail = NULL);
	}
	else if (q == (*List)->tail)//removing the tail element
	{
		(*List)->tail = q->prev;
		(*List)->tail->next = NULL;
	}
	else//removing the middle element
	{
		prev = q->prev; // node preceding q
		next = q->next; // the node following q
		if (prev != NULL)
			prev->next = q->next; // rearranging the pointer
		if (next != NULL)
			next->prev = q->prev; // rearranging the pointer
	}
	return;
}
void pushback(dis** he, Node* q)
{
	q->prev = (*he)->tail;
	if ((*he)->tail != NULL) {//check that the tail is not zero
		(*he)->tail->next = q;//the next element after the tail is the one we want to add
	}
	(*he)->tail = q;//now the end of the list is our insertion element q

	if ((*he)->head == NULL) {//if the head is zero (there are no elements), then the list will refer to our last element q
		(*he)->head = q;//if there were no elements, then the head refers to the element we inserted
	}
}
Node* FillMem(size_t size, Node** q, dis** List)
{
	Node* zan = NULL;
	int si = (int)size;
	if (size != (*q)->size1)//if the size of the allocated block is not equal to the size of the free
	{//we add the occupied element to the end of the free block so that there are no problems with pointers in the list
		(*q)->size1 = (*q)->size1 - size;//changing the size of the free block
		Node2* busy = (Node2*)((uintptr_t)(*q) + ((*q)->size1) - sizeof(Node2));//we put a busy pointer for a free block
		busy->size2 = (int)((*q)->size1);
		//the size is based on the descriptor, so the transition will only be to the size of the modified free block
		zan = (Node*)((uintptr_t)(*q) + (*q)->size1);
		//the occupied elements have no pointers to the previous and next elements
		zan->next = NULL;
		zan->prev = NULL;
		zan->size1 = size;
		busy = (Node2*)((uintptr_t)(zan)+(zan->size1) - sizeof(Node2));//we put a pointer to the block's occupancy
		busy->size2 = -(int)(zan->size1);//the employment value will be negative
	}
	else
	{
		//found a free block of the same size as the filled block
		zan = (Node*)((uintptr_t)(*q));
		DeleteEl(*q, List);//since the free element is filled in completely, it must be removed from the list
		zan->next = NULL;
		zan->prev = NULL;
		zan->size1 = size;
		Node2* busy = (Node2*)((uintptr_t)(zan)+(zan->size1) - sizeof(Node2));//we put a pointer to the block's occupancy
		busy->size2 = -(int)(zan->size1);

	};
	return zan;
}
Node* Fistfit(size_t size, dis** FreeList, int* i)
{
	Node* zan = NULL;//the memory block that will be given to the user
	dis* kol = (*FreeList);
	size_t si = size + sizeof(Node) + sizeof(Node2);//block size considering descriptors
	if ((*i) == 1)//in one direction we go from the beginning to the end of the list
	{
		Node* q = (kol)->head;//go to the first item in the list
		while ((q != NULL))
		{
			if (q->size1 >= si)//if there is a free block h larger than the required size
			{
				(*i) = -1;//changing direction
				zan = FillMem(si, &q, FreeList);//calling the function to write to the memory block and dividing the free block into subblocks
				return zan;
			}
			else zan = NULL;
			q = q->next;
		}
		if (q != NULL)
		{
			zan = NULL;
			(*i) = -1;//changing direction
		}
	}
	else
	{
		Node* q = (kol)->tail;//search direction: from the end to the beginning of the list
		while ( (q != NULL))
		{
			if (q->size1 >= si)//if there is a free block h larger than the required size
			{
				(*i) = 1;//changing direction
				zan = FillMem(si, &q, FreeList);//calling the function to write to the memory block and dividing the free block into subblocks
				return zan;
			}
			else zan = NULL;
			q = q->prev;
		}
		if (q != NULL)
		{
			zan = NULL;
			(*i) = 1;//changing direction
		}
	}
	return zan;
}
Node* Unifbefore(Node** q, dis** List, size_t** last)
{
	//before the free memory block
	//to find out if a free block is the first and/or last in the list
	int m = 0;
	int n = 0;

	if (*q != NULL)
	{
		Node2* qb = (Node2*)((uintptr_t)(*q) + ((*q)->size1) - sizeof(Node2));//we go to the address on the block's occupancy after the released one
		if (qb != (Node2*)(*last))//we check that we are not in the last place of the memory block
		{
			Node* k = (Node*)((uintptr_t)(*q) + ((*q)->size1));//moved to the value of the size following the released block
			if ((*List)->head == k) m = 1;
			if ((*List)->tail == k) n = 1;
			Node2* p = (Node2*)((uintptr_t)(k)+(k->size1) - sizeof(Node2));//we throw the pointer to the block's occupancy
			int si = p->size2;//let's find out what is the value of the number showing the busy memory
			if (si > 0)
			{
				(*q)->size1 = k->size1 + (*q)->size1;//changing the size of the free block taking into account the descriptor
				if (m != 1) k->prev->next = (*q);//we throw the link of the previous free element (it previously pointed to the free element that we found) to the element that we want to add
				p = (Node2*)((uintptr_t)(*q) + ((*q)->size1) - sizeof(Node2));//we throw the pointer to the block's occupancy
				p->size2 = (int)((*q)->size1);//now employment is greater than zero with a larger size
				if (((m == 1) && (n == 1)) || (n == 1)) pushback(List, (*q));//If the element was the first and last in the list, or only the last, then we change the end of the doubly linked list
			}

		}
	}
	return(*q);
}
Node* Unifafter(Node** q, dis** List, size_t** start)
{
	//released memory after a free block
	Node* qb = (Node*)((uintptr_t)(*q));//to check that the block being released is not the first in the entire memory, if so, there is no free block in front of it
	if (qb != (Node*)(*start))//check that we are not on the first element of the block
	{
		Node* ko = NULL;
		int* p = (int*)((uintptr_t)(*q) - sizeof(Node2));//we turn to the value of employment to the block to the left of the one being released
		int si = *p;//let's find out what is the value of the number showing the busy memory
		if (si > 0)//if positive, then it is necessary to combine the blocks
		{
			ko = (Node*)((uintptr_t)(p)-si + sizeof(Node2));//go to the beginning of the block before the block being released, add sizeof(Node2)) more, since si also stores a part of the busy descriptor
			ko->size1 = ko->size1 + (*q)->size1;//we change the size of the free block, there is one descriptor left. the increase is due to the actual size of the block and the no longer needed descriptor for the second block
			Node2* busy = (Node2*)((uintptr_t)(ko)+(ko->size1) - sizeof(Node2));//we put a pointer to employment
			busy->size2 = (int)(ko->size1);//changing the employment value to a positive number and greater than before the merger
			(*q) = ko;//changing the value of the pointer q
		}
	}
	return(*q);
}

void FreeMem(Node** q, dis** FreeList, size_t** start, size_t** last)
{
	size_t k = (*q)->size1;//we remember the initial size of the occupied block
	//move the pointer to the area where the pointer to the block's occupancy will be stored
	Node2* busy = (Node2*)((uintptr_t)(*q) + ((*q)->size1) - sizeof(Node2));// we move on to the next block by adding ((*q)->size1), and then return to the place where there should be a pointer to employment, subtracting sizeof(Node2)
	if (busy->size2 > 0)//if we are trying to free up memory that has already been freed
	{
		printf("Have you already allocated this memory block\n");
		return;
	}
	busy->size2 = (int)((*q)->size1);//the block becomes free, so the occupancy is equal to the value of the size of the entire block (including descriptors)
	*q = Unifafter(q, FreeList, start);//we check whether there is already a free element before the released element, if there is, then merge these elements into one to avoid large fragmentation
	*q = Unifbefore(q, FreeList, last);//we check whether there is already a free element after the released element, if there is, then merge these elements into one
	if (k == (*q)->size1)//if the block has not changed, then just add it to the end of the doubly linked list
	{
		pushback(FreeList, (*q));
	}
	printf("_Memory is released\n");
}
//check up integrity
void checkup(size_t** start, size_t** last) {
	Node* tmp = (Node*)(*start);
	Node2* bu = NULL;
	int all = 0; //all memory
	int busy = 0;//busy memory
	int free = 0;//free memory
	do {
		bu = (Node2*)((uintptr_t)(tmp)+tmp->size1 - sizeof(Node2));//find out the block occupancy value
		if (bu->size2 > 0) free = free + (int)tmp->size1;
		if (bu->size2 < 0) busy = busy + tmp->size1;
		all = all + tmp->size1;
		tmp = (Node*)((uintptr_t)(tmp)+tmp->size1);
	} while (bu != (Node2*)(*last));

	printf("Free memory: %d\n", free);
	printf("Applied memory: %d\n", busy);
	printf("All  memory : %d\n", all);
	int loosed = sizeblock - all;
	printf("Loosed memory: %d\n", loosed);
}