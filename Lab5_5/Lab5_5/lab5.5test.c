#include "TypeLab5.5.h"
#include <stdlib.h>
#include <stdio.h>
int main()
{
	tree* k = NULL;
	int y = 0;
	int n = 0;
	int x = 0;
	ReadTreeConsole(&k,&n);//we fill the tree with the read data
	int l = CountH(&k);//we consider the height of the tree, do not forget that the leaves have a height of 0, to create an array, the number of rows for these trees without taking into account the width will be l+1
	int** B = InitAuxTable(2*(l+1),n);//creating an auxiliary matrix, the rows in the table will be height +1 and multiplied by 2, since we will also output the width for each element of the tree
	if (B == NULL) return -1;
	ReadReverseOrder(&k);//
	CreateAuxTable(&k,y,B,&x);//We fill the auxiliary matrix with elements from the tree
	PrintAuxTable(B,2*(l+1), n);//We display an auxiliary table on the screen
	FreeAuxTable(B,2*(l+1));//Clearing the memory allocated for the matrix
	FreeTree(&k);//freeing up the memory occupied by the tree
	return 0;
}
