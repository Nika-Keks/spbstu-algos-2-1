#pragma once

typedef struct _Node {//structure for a doubly linked free space list
	size_t size1;//the size of the block taking into account the descriptor
	struct _Node* next;//the next item in the list
	struct _Node* prev;//previous list item
} Node;
typedef struct _Node2 {//for the correct storage of the employment address

	int size2;//to determine the occupancy of a memory block: =size 1 if the block is free, =-size 1 if occupied
}Node2;
typedef struct _dis {//to store links to the first and last items of the list
	Node* head;//link to the first element
	Node* tail;//link to the tail of the list
} dis;
size_t* createBlock();//function for allocating a memory block
dis* CreateList(size_t** start, size_t** last);/*function for creating a doubly linked list
start-to save the address of the beginning of the block
last-to save the address with the occupation of the original empty block
*/
void DeleteList(dis** FreeList, size_t** start);/*function to delete the allocated memory block
FreeList-a doubly linked list of free memory
start-address of the start of the allocated memory block
*/
void DeleteEl(Node* q, dis** List);/*function for removing free memory from the list
q-the item to be removed from the list
List-a doubly linked list of free memory
*/
void pushback(dis** he, Node* q);/*the function of adding to the end of the list
he-a doubly linked list of free memory
q-the element to add
*/
Node* FillMem(size_t size, Node** q, dis** List);/*0free memory filling function
size-the size of the block that the user enters, taking into account the descriptor
q-block from the free space list
List-a doubly linked list of free memory
*/
Node* Fistfit(size_t size, dis** FreeList, int* i);/*The function of searching for the first suitable free block in different directions
size-the size of the block that the user enters, taking into account the descriptor
FreeList-a doubly linked list of free memory
i-saves the direction of the list in which the search has already been performed
*/
Node* Unifbefore(Node** q, dis** List, size_t** last);/*Function for checking the existence of a free block after the block being addedand when it exists by combining blocks
q-the block that needs to be released
List-a doubly linked list of free memory
last-to save the address with the occupation of the original empty block
*/
Node* Unifafter(Node** q, dis** List, size_t** start);/*A function for checking the existence of a free block before the block being addedand when it exists of block unions
q-the block that needs to be released
List-a doubly linked list of free memory
start-address of the start of the allocated memory block
*/
void FreeMem(Node** q, dis** FreeList, size_t** start, size_t** last);/*memory block release function
q-the block that needs to be released
FreeList-a doubly linked list of free memory
start-to save the address of the beginning of the block
last-to save the address with the occupation of the original empty block
*/
void checkup(size_t** start, size_t** last);/*Function for checking memory leaks
start-to save the address of the beginning of the block
last-to save the address with the occupation of the original empty block
*/