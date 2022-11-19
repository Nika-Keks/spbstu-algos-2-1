#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"
#include "stdbool.h"
#include"Type.h"
#pragma warning (disable:4996) 
int AddElem(int dat, list** k)
{
	list* p = (list*)malloc(sizeof(list));//we allocate memory for the list item
	if (p != NULL)
	{
		list* q = (*k);
		if (p != NULL)
		{//adding an item to the top of the list
			p->data = dat;//filling the element with the value
			p->next = q;//the element being added refers to the list
			(*k) = p;//now the list starts with the item being added
		}
	}
	else {
		printf("Error");
		return -1;
	}
	return 0;
}
int* ReadFile(char* name, int* B, int* n)
{
	FILE* fin;
	// opening the file for reading
	fin = fopen(name, "r");
	if (fin == NULL)
	{
		printf("Could not open the file");
		return NULL;
	}
	fscanf(fin, "%d", B);//reading the value of the required amount
	fscanf(fin, "%d", n);//reading the number of elements
	int* A = (int*)malloc((*n) * sizeof(int));//we allocate memory for an array
	if (A == NULL)
	{
		printf("memory allocation error");
		return A;
	}
	for (int i = (*n) - 1; i >= 0; i--)//we write the opposite to the array, because further in the recursion we will go in the reverse order of the elements, and thus in the recursion we will go not from the last element but from the first
	{
		fscanf(fin, "%d", &A[i]);
	}
	fclose(fin);
	return A;
}
bool SetSum(int A[], int n, int B, list** k, int* er)
{
	if (B == 0) return true;//When the sum became equal to 0, then we found a subset
	if ((n < 0) || (B < 0)) return false;//we have reached (we go from the end) to the beginning of array A, or our sum has become less than 0 (it makes no sense to select elements further, since the sum of elements is already greater than the required amount)
	/*next, we will call the same function, if the element is included in the desired subset, then it will be written to the list
	*to find out which elements are included or not, incl will be called first, it will reach the end of the array (which is written in reverse order compared to the original array from the file) and if true, the last number will be written to the list
	* moreover, at first they will be called only for incl and only when we reach the end of the list and find out true or false, excl will be called and this condition will be checked
	* note that if the branch for inclusion was false, then when excl is called, we get that we will call incl again first and at the same time we will get a different sum of the elements of the subset and another subset
	* Also, you will not have to delete items from the list, since they are written only if the incl function returned true
	* access to excl will be performed only if the element is not included in the subset, because we need to find only one subset and it makes no sense to go through all the options*/
	bool incl;
	incl = SetSum(A, n - 1, B - A[n], k,er);//the element is included in the subset, here we reduce the number of the array element by 1, since we call recursion for the next element of the array, we change the amount by the value of the element size
	bool excl;
	if (incl == true)//if true, then the element is included in our desired subset
	{
		int dat = A[n];
		if (AddElem(dat, k)==-1) (*er)=-1;//we write the found element to the list for a subset
	}
	else excl = SetSum(A, n - 1, B, k,er);//the element is not included in the subset
	return (incl || excl);//this return works for those recursion calls that result from a subsequent function call, and false returns only if both values were false
}
int Write(char* name, list** k,bool ko)
{
	FILE* fin;
	fin = fopen(name, "w");//open the file for recording
	if (fin == NULL)
	{
		printf("Could not open the file");
		return -1;
	}
	if (ko == true)//a subset was found
	{
		while ((*k) != NULL)
		{
			fprintf(fin, "%d ", (*k)->data);//writing the list to a file
			(*k) = (*k)->next;
		}
	}
	else
	{
		fprintf(fin,"Subset not found\n");//subsets were not found
		fprintf(fin, "%d ", 0);
	}
	fclose(fin);
	return 0;
}
int Serch(int A[], int n, int B)
{
	list* k = NULL;
	//in recursion, an error can occur only when adding a new element, so the recursion can find everything correctly, 
	//but not write to the file, so we enter the error variable to find out if there was an error in adding an element
	int error = 0;
	bool ko;//to save what the recursive function returned
	char* nam2 = "output.txt";
	ko = SetSum(A, n - 1, B, &k,&error);//calling a recursive function, n-1 since the array starts with 0
	if (error == -1) return -1;
	if (Write(nam2, &k,ko) == -1) return -1;//calling the function to write to the file
	return 0;
}