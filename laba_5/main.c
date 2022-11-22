#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void main(void)
{ 
	/*allocate memory and fill the adjacency matrix with the first example for the test (two-dimensional array represents the adjacency matrix)
	011
	000
	000
	*/
	int** mas = malloc(3 * sizeof(int*));
	if (!mas)
	{
		exit(-1);

	}
	for (int j=0;j<3;j++)
	{
		mas[j] = malloc(3 * sizeof(int*));
		if (!mas[j])
		{
			exit(-1);

		}
		for (int k = 0; k < 3; k++)
		{
			mas[j][k] = 0;
		}
	}
	mas[0][1] = 1;
	mas[0][2] = 1;


	int i = tree_node(mas,3);
	tree* test = create_tree(mas,i,3);
	print(test);
	printf("\n\n");
	for (int j = 0; j < 3; j++)
	{
			free(mas[j]);	
	}
	/*allocate memory and fill the adjacency matrix with the second example for the test (two-dimensional array represents the adjacency matrix)
	0000000000
	0001100000
	0000010000
	1000000100
	0010001000
	0000000000
	0000000000
	0000000011
	0000000000
	0000000000
	*/
	int** mas_1 = malloc(10 * sizeof(int*));
	if (!mas_1)
	{
		exit(-1);

	}
	for (int j = 0; j < 10; j++)
	{
		mas_1[j] = malloc(10 * sizeof(int*));
		if (!mas_1[j])
		{
			exit(-1);

		}
		for (int k = 0; k < 10; k++)
		{
			mas_1[j][k] = 0;
		}
	}
	mas_1[1][3] = 1;
	mas_1[1][4] = 1;
	mas_1[2][5] = 1;
	mas_1[3][0] = 1;
	mas_1[3][7] = 1;
	mas_1[7][9] = 1;
	mas_1[7][8] = 1;
	mas_1[4][2] = 1;
	mas_1[4][6] = 1;
	int i_1 = tree_node(mas_1,10);
	tree* test_1 = create_tree(mas_1, i_1,10);
	print(test_1);
	for (int j = 0; j < 10; j++)
	{
			free(mas_1[j]);
	}
}