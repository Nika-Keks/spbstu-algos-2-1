#pragma once
#include "stdbool.h"
typedef struct _list//list of subset elements
{
	int data;//element value
	struct list* next;//link to the next element
}list;
int AddElem(int dat, list** k);/*the function of adding elements with the dat value included in the subset to the list k*/
int* ReadFile(char* name, int* B, int* n);/*function of reading from a file of elements of a set
name-file name
B is the desired subset sum
n is the number of elements in the set
*/
bool SetSum(int A[], int n, int B, list** k);/*a recursive function that returns true if a subset is found, false if not
B is the desired subset sum
n is the number of elements in the set
k-list of subset elements
*/
int Write(char* name, list** k,bool ko);/*write a subset of r to a file with the name name, if it is true and if it is false, then enter 0 in the file*/
int Serch(int A[], int n, int B);/*Search for the necessary subset of the set A with the number of elements n b calling the write function to the file*/